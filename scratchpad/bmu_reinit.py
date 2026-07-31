#!/usr/bin/env python3
"""Live BMU engine re-init probe (wedge #2 fix hunt, 2026-07-31e).

WHY: mainline's BMU never produces its DDR BP pool (bppe_cnt @0x92348080
reads 0 vs stock's 8112) so HW-forwarded fabric frames leak BPs off a
~15-entry on-chip margin -> fabric starvation halt at ~1k frames
(findings/wifi_stage3_wedge_bmu_pool_2026-07-28.md).

Every *value* parity write has been refuted, so this probe attacks the
ENGINE state machine instead: drive the documented disable -> reconfigure
-> prime -> enable edge live (all in poke range) and watch whether the
DDR->on-chip prefetch finally runs. Paced through ab_ctrs.zc because a
fast poke batch overruns the UART console and hangs the CPU.

Usage: bmu_reinit.py [seq]
  seq = which experiment: reinit | kick | initsat | all
"""
import re
import sys
import time

import ab_ctrs

TM = 0x92340000
BMU = TM + 0x8000
STRIDE = 0x400
INSTS = [BMU + i * STRIDE for i in range(5)]

POOL = 8192
JUMBO = 0x66


def poke(addr, val=None):
    if val is None:
        return "echo %08x > /sys/kernel/debug/zx_eth/poke" % addr
    return "echo %08x %08x > /sys/kernel/debug/zx_eth/poke" % (addr, val)


def read_regs(pairs, wait=2.5):
    """pairs = [(name, addr)] -> {name: value}"""
    cmds = [poke(a) for _, a in pairs]
    cmds.append("dmesg | busybox grep -a 'peek 0x' | busybox tail -%d"
                % (len(pairs) + 4))
    out = ab_ctrs.zc(cmds, wait=wait, hardcap=90)
    vals = {}
    for name, addr in pairs:
        m = re.findall(r"peek 0x%08x = 0x([0-9a-f]+)" % addr, out, re.I)
        vals[name] = int(m[-1], 16) if m else None
    return vals


STATE = [("init", BMU + 0x0000), ("bppi_ptr", BMU + 0x0040),
         ("r8044", BMU + 0x0044), ("bppe_ptr", BMU + 0x0048),
         ("bppe_cnt", BMU + 0x0080), ("r8084", BMU + 0x0084),
         ("bppi_cnt", BMU + 0x0088), ("bpstat", BMU + 0x00dc),
         ("r8050", BMU + 0x0050), ("r8054", BMU + 0x0054),
         ("r80e0", BMU + 0x00e0), ("r80e4", BMU + 0x00e4)]


def show(tag):
    v = read_regs(STATE)
    print("[%s] " % tag + " ".join(
        "%s=%s" % (n, ("0x%x" % v[n]) if v[n] is not None else "?")
        for n, _ in STATE))
    sys.stdout.flush()
    return v


def do_reinit():
    """Full disable -> reconfigure -> prime -> enable edge, all 5 instances."""
    cmds = []
    for b in INSTS:
        cmds.append(poke(b + 0x0000, 0))            # BMU_INIT = 0 (disable)
    for b in INSTS:
        cmds.append(poke(b + 0x0004, 0x104C040))    # CTRL1
        cmds.append(poke(b + 0x0008, 0x104C040))    # CTRL2
        cmds.append(poke(b + 0x0058, (POOL >> 5) - 1))
        cmds.append(poke(b + 0x005C, (JUMBO >> 5) - 1))
    # producer cursors: instance 0 only (stock parity)
    cmds.append(poke(BMU + 0x0048, POOL << 16))
    cmds.append(poke(BMU + 0x004C, JUMBO << 16))
    for b in INSTS:
        cmds.append(poke(b + 0x0000, 1))            # BMU_INIT = 1 (enable)
    # paced in chunks so the console never floods
    for i in range(0, len(cmds), 8):
        ab_ctrs.zc(cmds[i:i + 8], wait=1.2, hardcap=40)
    time.sleep(0.5)


def do_kick(n=4):
    """Alloc-kick tm[0x8014]=1 — does the on-chip FIFO refill from DDR now?"""
    for _ in range(n):
        ab_ctrs.zc([poke(BMU + 0x0014, 1)], wait=0.8, hardcap=20)
        time.sleep(0.2)


def do_initsat():
    """0x80a0 bp-initsat + enable retoggle (previously inert; retest post-AXI)."""
    cmds = [poke(BMU + 0x00A0, 1), poke(BMU + 0x0000, 0), poke(BMU + 0x0000, 1)]
    ab_ctrs.zc(cmds, wait=1.2, hardcap=40)


if __name__ == "__main__":
    seq = sys.argv[1] if len(sys.argv) > 1 else "reinit"
    show("baseline")
    if seq in ("reinit", "all"):
        print(">>> full BMU re-init edge (disable/reconfig/prime/enable)")
        do_reinit()
        show("post-reinit")
    if seq in ("kick", "all"):
        print(">>> alloc-kick x4")
        do_kick()
        show("post-kick")
    if seq in ("initsat", "all"):
        print(">>> initsat + enable retoggle")
        do_initsat()
        show("post-initsat")
