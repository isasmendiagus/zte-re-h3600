#!/usr/bin/env python3
"""Robust live register reader v2.

LESSONS (verified empirically this session):
  * Only the FIRST `tail -c +N` read on a FRESH TCP connection is reliable;
    subsequent reads in the same connection are corrupt.  => reconnect per read.
  * The seek lands at requested_offset + err where err in ~[0,110] bytes and
    VARIES per connection.  The stream after the seek IS contiguous & faithful.
  * UART is glitchy => read each window twice (two connections) and keep the
    capture that aligns; cross-check.

CALIBRATION (no in-window MAC anchor needed for far windows):
  Slide the captured buffer against the STOCK dump values for the requested
  window over candidate err in [0..ERRMAX]; pick the err that maximizes the
  count of u32s matching stock.  Because nearly all regs equal stock (only a
  handful diverge), the true alignment wins decisively.  We require a clear
  winner (>= MIN_MATCH matches and a margin over 2nd best) else we discard.
"""
import socket, time, sys
from pathlib import Path
from collections import Counter

HOST, PORT = 'localhost', 9999
BASE = 0x921c0000
ERRMAX = 140
HDR = 0x80  # bytes of slop we read before the target

_STOCK = None
def stock():
    global _STOCK
    if _STOCK is None:
        _STOCK = {}
        p = Path(__file__).with_name('stock_eth_2mib.txt')
        for line in p.read_text().splitlines():
            line = line.strip()
            if not line: continue
            try:
                a, v = line.split()
                _STOCK[int(a,16)] = int(v,16)
            except ValueError:
                pass
    return _STOCK

def connect():
    s = socket.socket(); s.settimeout(10); s.connect((HOST, PORT))
    time.sleep(0.25)
    try:
        s.settimeout(0.4)
        while s.recv(65536): pass
    except Exception: pass
    s.settimeout(10)
    return s

def read_once(mem_off, settle=10.0, max_bytes=20000):
    """One read on a fresh connection. Returns payload bytes."""
    s = connect()
    N = mem_off + 1
    cmd = f"tail -c +{N} /sys/kernel/debug/zx_eth/mem".encode()
    s.sendall(cmd + b'\r')
    buf = b''; end = time.time() + settle; s.settimeout(2.0); idle = 0
    while time.time() < end:
        try:
            d = s.recv(65536)
        except socket.timeout:
            idle += 1
            if buf.find(b'[exit=') >= 0 or idle >= 4: break
            continue
        if not d: break
        idle = 0; buf += d
        if len(buf) > max_bytes or buf.find(b'[exit=') >= 0: break
    s.close()
    idx = buf.find(cmd)
    if idx >= 0:
        nl = buf.find(b'\n', idx + len(cmd))
        payload = buf[nl+1:] if nl >= 0 else buf[idx+len(cmd):]
    else:
        payload = buf
    e = payload.rfind(b'[exit=')
    if e >= 0: payload = payload[:e]
    return payload

def u32(buf, i):
    return buf[i] | (buf[i+1]<<8) | (buf[i+2]<<16) | (buf[i+3]<<24)

def calibrate(buf, target_phys, count):
    """Find err in [0,ERRMAX] s.t. buf byte (HDR-... ) maps target.
    We read from (target - HDR); so byte j -> phys = (target-HDR) + err + j.
    target u-th reg phys = target + 4u -> byte index = HDR - err + 4u.
    Score = #u32 matching stock over the window."""
    st = stock()
    best = (-1, None)  # (score, err)
    scores = []
    for err in range(0, ERRMAX+1):
        sc = 0; tot = 0
        for u in range(count):
            bi = HDR - err + 4*u
            if bi < 0 or bi+4 > len(buf): continue
            phys = target_phys + 4*u
            if phys not in st: continue
            tot += 1
            if u32(buf, bi) == st[phys]:
                sc += 1
        scores.append((sc, tot, err))
        if sc > best[0]:
            best = (sc, err)
    scores.sort(reverse=True)
    return best[1], scores[:3]

def read_window(target_phys, count, tries=3, settle=12.0):
    """Return dict {phys:value}. Reads from a point well before the target,
    calibrates b0 vs stock, merges multiple tries by majority.

    Seek error is large/variable (seen up to ~200B) so we read from
    target-SLOP and a buffer big enough to contain the full window even with
    a large positive seek error."""
    SLOP = 0x2000  # `tail -c +N` over-skips by up to ~1KB+; read from well before
    target_mem = target_phys - BASE
    read_from = max(0, target_mem - SLOP)
    need = SLOP + count*4 + 2000  # absorb seek over-skip + glitches
    # If the requested window contains the host-MAC anchor (PP 0x80a8/0x80ac),
    # we can pin b0 exactly from the MAC signature (most reliable).
    MAC_PHYS = 0x923880a8
    MAC_SIG = bytes([0x00,0x59,0xe9,0x62, 0xa3,0xc8])  # 0x80a8,0x80ac low6
    mac_u = None
    if target_phys <= MAC_PHYS < target_phys + count*4:
        mac_u = (MAC_PHYS - target_phys)//4
    results = []
    diags = []
    for _ in range(tries):
        buf = read_once(read_from, settle=settle, max_bytes=need)
        if len(buf) < count*4:
            diags.append(f"short({len(buf)})")
            time.sleep(0.2); continue
        b0 = None; top = None
        if mac_u is not None:
            si = buf.find(MAC_SIG)
            if si >= 0:
                b0 = si - 4*mac_u  # byte index of target_phys
                top = f"MAC@{si}"
        if b0 is None:
            b0, top = _calib(buf, target_phys, count, 0)
        if b0 is None or b0 < 0:
            diags.append(f"nocal(len={len(buf)},{top if isinstance(top,str) else top[:2] if top else None})"); time.sleep(0.2); continue
        d = {}
        for u in range(count):
            bi = b0 + 4*u
            if 0 <= bi and bi+4 <= len(buf):
                d[target_phys + 4*u] = u32(buf, bi)
        results.append(d)
        diags.append(f"b0={b0} top={top[:2]}")
        time.sleep(0.2)
    out = {}
    for u in range(count):
        phys = target_phys + 4*u
        vs = [d[phys] for d in results if phys in d]
        if not vs: continue
        c = Counter(vs)
        val, freq = c.most_common(1)[0]
        if len(results) == 1 or freq >= 2:
            out[phys] = val
    return out, diags

def _calib(buf, target_phys, count, hdr_eff):
    """Find the byte index 'b0' in buf that corresponds to target_phys, by
    sliding over ALL 4-aligned positions and scoring matches on stock-NONZERO
    registers.  (Seek error is large & variable, so search the whole buffer.)
    Returns (b0, top_scores) where target u-th reg = u32(buf, b0 + 4u)."""
    st = stock()
    best = (-1e9, None); scores = []
    maxb0 = len(buf) - count*4
    if maxb0 < 0:
        maxb0 = len(buf) - 4
    # search every byte offset (alignment unknown — seek may be non-dword)
    for b0 in range(0, maxb0+1):
        sc = 0; miss = 0
        for u in range(count):
            bi = b0 + 4*u
            if bi+4 > len(buf): break
            phys = target_phys + 4*u
            sv = st.get(phys)
            if sv is None or sv == 0: continue
            if u32(buf, bi) == sv: sc += 1
            else: miss += 1
        score = sc*10 - miss
        if score > best[0]:
            best = (score, b0)
        scores.append((score, sc, b0))
    scores.sort(reverse=True)
    if best[1] is None or scores[0][1] < 2:
        return None, scores[:4]
    return best[1], scores[:4]

if __name__ == '__main__':
    # self-test: PP host-MAC region, expect divergences vs stock minimal
    tphys = 0x923880a0
    d, diag = read_window(tphys, 8, tries=3)
    print("diag:", diag)
    st = stock()
    for phys in sorted(d):
        sv = st.get(phys)
        mark = '' if sv==d[phys] else '  <-- DIFF stock=%08x'%(sv if sv is not None else 0)
        print(f"  {phys:08x} = {d[phys]:08x}{mark}")
