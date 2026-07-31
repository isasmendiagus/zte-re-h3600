#!/usr/bin/env python3
"""Cold-start wedge tracer (wedge #2, 2026-07-31f).

WHY THIS EXISTS — the reframing that makes the wedge cheap to study:
every post-fix-#1 onset on record is EARLY, within ~1-2k HW-forwarded
frames of the flow starting on a fresh boot (967, ~965, 1755), while a run
that entered already 82k frames deep survived 205k. So wedge #2 looks like
a COLD-START hazard, not a cumulative leak. That means we do not need
hour-long endurance runs: boot fresh, start the flow, and the verdict
arrives in under a minute.

This tracer samples a DELIBERATELY SMALL register set (9 regs, ~2-3 s per
round, console-safe) from flow start until forward progress freezes, so we
can read off WHICH stage stops first. `endur2`/`lite_sample` sample 27 regs
per round (~7 s) which is far too coarse to resolve a 1-2k-frame window.

Watched, and why:
  cla_up_fwd  0x9238c3c0  forward progress (the thing that freezes)
  cla_acl_fail0x9238c3c4  lookup misses (does it start missing before dying?)
  sipc_drop   0x921cc004  SIPC drop counter
  sipc_g008   0x921cc008  ** LEAD: this FIFO gauge stepped 0x111011 ->
                          0x222211 at one previous onset (fabric-ingress
                          FIFO filling and never draining)
  sipc_g044   0x921cc044  ** LEAD: SIPC->SPA handoff counter (the
                          predecessor doc's per-stage localization step)
  bmu_80e0/e4 0x923480e0/e4  mainline-only "distress" counters (0 on stock,
                          climb with traffic)
  red_fwd_in  0x92344204  RED ingress admission
  qmg_dn_trap 0x9234c04c  the wedge discriminator (frozen == true wedge)

Usage:
  wedge_coldstart.py [max_rounds] [--noflow]
    --noflow = assume a flow is already running (just trace)

Safety: read-only pokes (peek path); never touches TM 0x92340128/0x130 and
never bulk-dumps the 0x92000000 region.
"""
import re
import sys
import time
from pathlib import Path

sys.path.insert(0, str(Path(__file__).resolve().parent))
import ab_ctrs  # noqa: E402
import wedge_probe as wp  # noqa: E402

REGS = (
    ("up_fwd",   0x9238C3C0),
    ("acl_fail", 0x9238C3C4),
    ("sipc_drop", 0x921CC004),
    ("sipc_008", 0x921CC008),
    ("sipc_044", 0x921CC044),
    ("bmu_e0",   0x923480E0),
    ("bmu_e4",   0x923480E4),
    ("red_in",   0x92344204),
    ("dn_trap",  0x9234C04C),
)


def sample():
    cmds = ["echo %08x > /sys/kernel/debug/zx_eth/poke" % a for _, a in REGS]
    cmds.append("dmesg | busybox grep -a 'peek 0x' | busybox tail -%d"
                % (len(REGS) + 3))
    cmds.append("busybox grep -a tx_injected /sys/kernel/debug/zx_eth/wifi_bind")
    out = ab_ctrs.zc(cmds, wait=1.6, hardcap=30)
    v = {}
    for name, addr in REGS:
        m = re.findall(r"peek 0x%08x = 0x([0-9a-f]+)" % addr, out, re.I)
        v[name] = int(m[-1], 16) if m else None
    m = re.search(r"tx_injected=(\d+)", out)
    v["inj"] = int(m.group(1)) if m else None
    return v


def fmt(v, prev):
    parts = []
    for name, _ in REGS:
        cur = v.get(name)
        if cur is None:
            parts.append("%s=?" % name)
            continue
        p = prev.get(name) if prev else None
        d = ("+%d" % (cur - p)) if (p is not None and cur != p) else ""
        parts.append("%s=0x%x%s" % (name, cur, d))
    return "inj=%s | %s" % (v.get("inj"), " ".join(parts))


def main(max_rounds=90, noflow=False):
    sink = wp.Sink()
    sink.start()
    flow = None
    if not noflow:
        flow = wp._flow_start(sink, rate_kbps=1000)
        print("=== coldstart tracer: flow started, tracing from t0 ===")
    else:
        print("=== coldstart tracer: --noflow, tracing existing flow ===")
    sys.stdout.flush()

    prev = None
    stuck = 0
    hist = []
    try:
        for n in range(1, max_rounds + 1):
            v = sample()
            line = "r%-3d %s" % (n, fmt(v, prev))
            print(line)
            sys.stdout.flush()
            hist.append(line)

            if prev is not None:
                adv = ((v.get("up_fwd") or 0) != (prev.get("up_fwd") or 0))
                trap_adv = ((v.get("dn_trap") or 0) != (prev.get("dn_trap") or 0))
                if not adv and not trap_adv:
                    stuck += 1
                else:
                    stuck = 0
                # 3 consecutive frozen rounds with a flow running == wedge
                if stuck >= 3 and (v.get("inj") or 0) > 200:
                    print("\n!!!! FORWARD PROGRESS FROZEN (wedge) at inj=%s !!!!"
                          % v.get("inj"))
                    print("---- last 6 rounds before/at freeze ----")
                    for h in hist[-6:]:
                        print(h)
                    print("\n---- full wedge signature ----")
                    sys.stdout.flush()
                    wp.wedgecap()
                    return 2
            prev = v
        print("\n=== traced %d rounds with no freeze (inj=%s) ==="
              % (max_rounds, prev.get("inj") if prev else "?"))
        return 0
    finally:
        if flow is not None:
            flow.kill()


if __name__ == "__main__":
    args = [a for a in sys.argv[1:] if not a.startswith("--")]
    main(int(args[0]) if args else 90, noflow="--noflow" in sys.argv)
