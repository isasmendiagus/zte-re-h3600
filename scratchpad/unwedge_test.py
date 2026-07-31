#!/usr/bin/env python3
"""Try to UNWEDGE a live wedged box by writing SIPC registers to stock values.

WHY: wedge_coldstart.py localized wedge #2 to 0x921cc008 — three 4-bit gauges
that fill in lockstep with HW-forwarded traffic and halt the fabric the moment
they saturate at 0xf (ddd -> eee -> fff -> halt -> wrap 0x111 -> brief
recovery -> halt). Stock reads 0x00000399 there. sipc_diff.py then found 10
differing registers in the block, of which 0x921cc040 (stock 0x01980000 vs
mainline 0x00f80000) and the 0x038/0x03c limit/level pair are the config-shaped
candidates, and NOTHING in mainline writes them (zx_sipcregtable has only two
entries, both at 0x921cc000).

If writing one of these makes a wedged box resume forwarding, that identifies
the mechanism definitively and points straight at the fix.

Order of attempts (each followed by a traffic-progress check):
  1. 0x921cc008 <- 0x00000399   (clear the saturated gauge directly)
  2. 0x921cc040 <- 0x01980000   (stock config value)
  3. 0x921cc03c <- 0x00000318   (stock limit/level)

Usage: unwedge_test.py [--noflow]
Safety: all writes are npp regs inside the poke window; never TM
0x92340128/0x130, never a bulk 0x92000000 dump.
"""
import re
import sys
import time
from pathlib import Path

sys.path.insert(0, str(Path(__file__).resolve().parent))
import ab_ctrs  # noqa: E402
import wedge_probe as wp  # noqa: E402

POKE = "/sys/kernel/debug/zx_eth/poke"
G008 = 0x921CC008
UP_FWD = 0x9238C3C0

ATTEMPTS = [
    ("clear saturated gauge 0x921cc008 -> stock 0x399", 0x921CC008, 0x00000399),
    ("0x921cc040 -> stock 0x01980000", 0x921CC040, 0x01980000),
    ("0x921cc03c -> stock 0x00000318", 0x921CC03C, 0x00000318),
]


def rd(addrs):
    cmds = ["echo %08x > %s" % (a, POKE) for a in addrs]
    cmds.append("dmesg | busybox grep -a 'peek 0x' | busybox tail -%d"
                % (len(addrs) + 3))
    out = ab_ctrs.zc(cmds, wait=1.8, hardcap=30)
    v = {}
    for a in addrs:
        m = re.findall(r"peek 0x%08x = 0x([0-9a-f]+)" % a, out, re.I)
        v[a] = int(m[-1], 16) if m else None
    return v


def wr(addr, val):
    ab_ctrs.zc(["echo %08x %08x > %s" % (addr, val, POKE)],
               wait=1.0, hardcap=20)


def progress(secs=8):
    """Returns (d_up_fwd, g008_before, g008_after)."""
    a = rd([UP_FWD, G008])
    time.sleep(secs)
    b = rd([UP_FWD, G008])
    d = ((b.get(UP_FWD) or 0) - (a.get(UP_FWD) or 0)) & 0xFFFFFFFF
    return d, a.get(G008), b.get(G008)


def main(noflow=False):
    sink = wp.Sink()
    sink.start()
    flow = None
    if not noflow:
        flow = wp._flow_start(sink, rate_kbps=1000)
        print("flow started; letting it settle 20 s")
        time.sleep(20)
    try:
        d, g0, g1 = progress()
        print("baseline: d_up_fwd=%d  g008 0x%x -> 0x%x" % (d, g0 or 0, g1 or 0))
        if d > 200:
            print("!! box is NOT wedged (forwarding fine) — rerun after a wedge")
            return 1
        for label, addr, val in ATTEMPTS:
            print("\n>>> %s" % label)
            wr(addr, val)
            after = rd([addr, G008])
            print("    readback 0x%08x = 0x%x ; g008 = 0x%x"
                  % (addr, after.get(addr) or 0, after.get(G008) or 0))
            d, g0, g1 = progress()
            print("    d_up_fwd=%d  g008 0x%x -> 0x%x" % (d, g0 or 0, g1 or 0))
            if d > 200:
                print("\n**** UNWEDGED by: %s ****" % label)
                print("**** forwarding resumed (+%d in 8 s) ****" % d)
                return 0
        print("\n=== none of the attempts unwedged the box ===")
        return 2
    finally:
        if flow is not None:
            flow.kill()


if __name__ == "__main__":
    sys.exit(main(noflow="--noflow" in sys.argv))
