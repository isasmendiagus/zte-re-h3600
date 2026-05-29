#!/usr/bin/env python3
"""Live register window reader for the ZTE device over REPL TCP localhost:9999.

mem_offset = phys - 0x921c0000.  The /sys/kernel/debug/zx_eth/mem file maps
phys 0x921c0000..0x923c0000.  `tail -c +N file` is 1-indexed => N = mem_off+1.

KEY PROBLEM (learned by prior agents AND re-confirmed): `tail -c +N` seeking
DRIFTS by a few bytes and is glitchy.  So we DO NOT trust the nominal offset.
Instead we read a window that we KNOW contains a unique signature, locate the
signature in the captured bytes, and derive the TRUE byte->phys mapping from
the signature position.  We read each window several times and keep bytes that
agree across the majority of captures.

Anchor signature: host MAC stored LE at PP[0x80a8] (mem 0x1c80a8):
  bytes at 0x1c80a8 = 00 59 e9 62 (PP[0x80a8]=0x62e95900)
  bytes at 0x1c80ac = a3 c8 00 00 (PP[0x80ac]=0x0000c8a3)
So the 8-byte signature at mem 0x1c80a8 is: 00 59 e9 62 a3 c8 00 00
"""
import socket, time, sys
from collections import Counter

HOST, PORT = 'localhost', 9999
BASE = 0x921c0000

def connect():
    s = socket.socket()
    s.settimeout(10)
    s.connect((HOST, PORT))
    time.sleep(0.3)
    try:
        s.settimeout(0.5)
        while s.recv(65536):
            pass
    except Exception:
        pass
    s.settimeout(10)
    return s

def read_once(s, mem_off, settle=15.0, max_bytes=200000):
    N = mem_off + 1
    cmd = f"tail -c +{N} /sys/kernel/debug/zx_eth/mem".encode()
    s.sendall(cmd + b'\r')
    buf = b''
    end = time.time() + settle
    s.settimeout(2.5)
    idle = 0
    while time.time() < end:
        try:
            d = s.recv(65536)
        except socket.timeout:
            idle += 1
            # stop only if we already saw the prompt, OR many idle cycles
            if buf.rstrip().endswith(b'# ') or buf.find(b'[exit=') >= 0:
                break
            if idle >= 5:
                break
            continue
        if not d:
            break
        idle = 0
        buf += d
        if len(buf) > max_bytes or buf.find(b'[exit=') >= 0:
            break
    # strip echoed command line: payload starts after FIRST echo of cmd + \r\n.
    # (The REPL echoes the command exactly once, then streams the file payload.)
    idx = buf.find(cmd)
    if idx >= 0:
        nl = buf.find(b'\n', idx + len(cmd))
        payload = buf[nl+1:] if nl >= 0 else buf[idx+len(cmd):]
    else:
        payload = buf
    # strip trailing prompt "\r\n# " and "[exit=...]"
    e = payload.rfind(b'[exit=')
    if e >= 0:
        payload = payload[:e]
    return payload

def majority_merge(caps):
    """Per-byte majority vote across captures of (possibly) different length.
    Returns (data, mask) where mask[i]=1 if a strict majority agreed."""
    n = max((len(c) for c in caps), default=0)
    data = bytearray(n)
    mask = bytearray(n)
    for i in range(n):
        cnt = Counter(c[i] for c in caps if i < len(c))
        if not cnt:
            continue
        val, freq = cnt.most_common(1)[0]
        if freq >= 2 and freq > len(caps)//2:
            data[i] = val
            mask[i] = 1
    return bytes(data), bytes(mask)

# anchor: full 16-byte block at mem 0x1c80a8 (PP 0x80a8..0x80b4)
ANCHOR_OFF = 0x1c80a8
ANCHOR_SIG = bytes([0x00,0x59,0xe9,0x62, 0xa3,0xc8,0x00,0x00])  # 0x80a8,0x80ac

def read_calibrated(s, want_phys_start, want_count_u32, tries=6,
                    anchor_off=ANCHOR_OFF, anchor_sig=ANCHOR_SIG):
    """Read a window that begins a bit before the anchor and extends to cover
    [want_phys_start, want_phys_start + want_count_u32*4).  Locate the anchor,
    derive byte0->phys, then extract requested u32s.

    Returns dict {phys: value} for u32s where a majority agreed."""
    want_mem_start = want_phys_start - BASE
    want_mem_end = want_mem_start + want_count_u32*4
    # We must read from min(anchor_off, want_mem_start) and cover to max(anchor end, want end)
    win_start = min(anchor_off, want_mem_start)
    win_end = max(anchor_off + len(anchor_sig), want_mem_end)
    # add a little slop before in case seek overshoots
    read_from = max(0, win_start - 64)
    need = (win_end - read_from) + 128
    caps = []
    for _ in range(tries):
        p = read_once(s, read_from, settle=2.0 + need/20000.0, max_bytes=need+200000)
        if len(p) >= 16:
            caps.append(p)
        time.sleep(0.15)
    if not caps:
        return {}, "no captures"
    # For each capture, locate anchor sig and align to a common phys frame.
    # Build per-capture phys->byte arrays.
    aligned = []  # list of dict phys->byte
    for c in caps:
        pos = c.find(anchor_sig)
        if pos < 0:
            continue
        # byte at c[pos] corresponds to phys = BASE + anchor_off
        # so byte c[j] -> phys = BASE + anchor_off + (j - pos)
        base_j = pos  # j where phys==anchor_off
        d = {}
        for j in range(len(c)):
            phys = BASE + anchor_off + (j - base_j)
            d[phys] = c[j]
        aligned.append(d)
    if not aligned:
        return {}, f"anchor not found in any of {len(caps)} caps (lens={[len(c) for c in caps]})"
    # majority vote per phys byte
    out = {}
    for u in range(want_count_u32):
        phys = want_phys_start + u*4
        bs = []
        for off in range(4):
            cnt = Counter(d[phys+off] for d in aligned if (phys+off) in d)
            if not cnt:
                bs = None; break
            val, freq = cnt.most_common(1)[0]
            if freq >= 2 and freq > len(aligned)//2:
                bs.append(val)
            else:
                bs = None; break
        if bs is not None:
            out[phys] = bs[0] | (bs[1]<<8) | (bs[2]<<16) | (bs[3]<<24)
    return out, f"ok ({len(aligned)}/{len(caps)} aligned)"

if __name__ == '__main__':
    s = connect()
    # sanity: read PP 0x80a0..0x80c0 calibrated on its own anchor
    vals, status = read_calibrated(s, 0x923880a0, 12, tries=6)
    print("status:", status)
    for phys in sorted(vals):
        print(f"  {phys:08x} = {vals[phys]:08x}")
    s.close()
