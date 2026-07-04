#!/usr/bin/env python3
"""red_probe.py — read RED out-queue used_space (indirect RAM) + the RX-desc
release port, for the DN-bank trap-credit-return hypothesis
(findings/red_trap_credit_return_re_2026-07-04.md).

RED block phys 0x92344000 (safe TM range):
  CMD   0x92344014 = q | (ram<<22) | (rw<<27)   rw=1 read
  DONE  0x92344018 bit0 == 1 -> idle/done
  DATA0 0x9234401c   ram1: guart_used=[10:0], share_used=[25:11]
                     ram5: used_space=[15:0]
  RED out-queue index: 0-7 = cpuUp bank, 8-15 = cpuDn bank (stock red_info_store).

Release port (also RED block):
  KICK  0x92344064 bit0==0 -> idle; write 1 to kick
  WORD  0x92344068 = bank<<14 | count<<4 | qid[2:0] | sop<<3   (count <= 0x3ff!)

All access via the driver poke debugfs (echo addr [val] > poke; result in dmesg),
same idiom as adm_probe.py / ctr.py.
"""
import argparse
import os
import re
import sys
import time

HERE = os.path.dirname(os.path.abspath(__file__))
sys.path.insert(0, HERE)
import ctr

CMD = 0x92344014
DONE = 0x92344018
DATA0 = 0x9234401c
REL_KICK = 0x92344064
REL_WORD = 0x92344068
QMG_DN_TRAP = 0x9234c04c
QMG_UP_TRAP = 0x9234c05c


def _parse(out, addr, last=True):
    m = re.findall(r"(?:peek|poke) 0x%08x = 0x([0-9a-f]+)" % addr, out, re.I)
    if not m:
        return None
    return int(m[-1] if last else m[0], 16)


def read_used(qs, ram=1, wait=None):
    """Read RED out-queue used_space for each q in qs via indirect ram<ram>.
    Returns {q: raw_DATA0_or_None}. One REPL round-trip for the whole sweep:
    for each q: peek DONE, write CMD, peek DONE, peek DATA0. We tag each q's
    DATA0 read by ordering (grep all DATA0 peeks, one per q, in order)."""
    cmds = []
    for q in qs:
        cmdval = q | (ram << 22) | (1 << 27)
        cmds.append("echo %08x > /sys/kernel/debug/zx_eth/poke" % DONE)
        cmds.append("echo %08x %08x > /sys/kernel/debug/zx_eth/poke" % (CMD, cmdval))
        cmds.append("echo %08x > /sys/kernel/debug/zx_eth/poke" % DONE)
        cmds.append("echo %08x > /sys/kernel/debug/zx_eth/poke" % DATA0)
    cmds.append("dmesg | grep -aE 'peek 0x|poke 0x' | tail -%d" % (len(cmds) + 8))
    if wait is None:
        wait = 1.5 + 0.15 * len(cmds)
    out = ctr.zc(cmds, wait=wait)
    # collect DATA0 peeks in order
    data = re.findall(r"peek 0x%08x = 0x([0-9a-f]+)" % DATA0, out, re.I)
    dones = re.findall(r"peek 0x%08x = 0x([0-9a-f]+)" % DONE, out, re.I)
    vals = {}
    if len(data) >= len(qs):
        for i, q in enumerate(qs):
            vals[q] = int(data[len(data) - len(qs) + i], 16)
    else:
        for q in qs:
            vals[q] = None
    return vals, dones


def read_traps():
    cmds = ["echo %08x > /sys/kernel/debug/zx_eth/poke" % QMG_DN_TRAP,
            "echo %08x > /sys/kernel/debug/zx_eth/poke" % QMG_UP_TRAP,
            "dmesg | grep -a 'peek 0x' | tail -6"]
    out = ctr.zc(cmds, wait=2.0)
    return _parse(out, QMG_DN_TRAP), _parse(out, QMG_UP_TRAP)


def sweep(label=""):
    dn, up = read_traps()
    v1, _ = read_used(list(range(16)), ram=1)
    print("[%s] qmg_dn_trap=%s qmg_up_trap=%s" % (label or time.strftime("%H:%M:%S"), dn, up))
    row = []
    for q in range(16):
        raw = v1.get(q)
        if raw is None:
            row.append("q%d=?" % q)
        else:
            row.append("q%d=%d/%d" % (q, raw & 0x7ff, (raw >> 11) & 0x7fff))
    print("  ram1 guart/share: " + "  ".join(row[:8]))
    print("                    " + "  ".join(row[8:]))
    return dn, up, v1


def sweep5(label=""):
    v5, _ = read_used(list(range(16)), ram=5)
    row = ["q%d=%s" % (q, (v5[q] & 0xffff) if v5.get(q) is not None else "?") for q in range(16)]
    print("[%s] ram5 used_space[15:0]:" % (label or time.strftime("%H:%M:%S")))
    print("  " + "  ".join(row[:8]))
    print("  " + "  ".join(row[8:]))
    return v5


def release(qid, count, sop, bank, verify_q=None):
    """Issue one RX-desc release: WORD = bank<<14 | count<<4 | qid | sop<<3.
    count <= 0x3ff enforced (bits [13:4]; overflow into bit14 was the invalid
    2026-07-03 rule-out). Polls kick-idle before; reads back kick after."""
    assert 0 <= count <= 0x3ff, "count must fit bits[13:4]"
    assert 0 <= qid <= 7
    word = (bank << 14) | (count << 4) | qid | (sop << 3)
    cmds = [
        "echo %08x > /sys/kernel/debug/zx_eth/poke" % REL_KICK,          # idle check
        "echo %08x %08x > /sys/kernel/debug/zx_eth/poke" % (REL_WORD, word),
        "echo %08x %08x > /sys/kernel/debug/zx_eth/poke" % (REL_KICK, 1),
        "echo %08x > /sys/kernel/debug/zx_eth/poke" % REL_KICK,          # post state
        "dmesg | grep -aE 'peek 0x|poke 0x' | tail -8",
    ]
    out = ctr.zc(cmds, wait=2.5)
    kicks = re.findall(r"peek 0x%08x = 0x([0-9a-f]+)" % REL_KICK, out, re.I)
    print("release word=0x%04x (bank=%d count=%d qid=%d sop=%d) kick pre/post=%s" % (
        word, bank, count, qid, sop, kicks))
    return out


def ring_dma_regs(qs=range(8)):
    """TM[0x10100+q*4] per-queue pending (HIGH16=ring1/DN, LOW16=ring0/UP) —
    the benign-side-effect watch from the recipe."""
    addrs = [0x92350100 + q * 4 for q in qs]
    cmds = ["echo %08x > /sys/kernel/debug/zx_eth/poke" % a for a in addrs]
    cmds.append("dmesg | grep -a 'peek 0x' | tail -%d" % (len(addrs) + 4))
    out = ctr.zc(cmds, wait=2.5)
    for a, q in zip(addrs, qs):
        v = _parse(out, a)
        print("  TM[0x10100+%d*4] = %s" % (q, "0x%08x" % v if v is not None else "?"))


if __name__ == "__main__":
    p = argparse.ArgumentParser()
    p.add_argument("action", choices=["sweep", "sweep5", "watch", "release", "rings"])
    p.add_argument("--qid", type=int, default=7, help="release qid (0-7, DN queue Q-8)")
    p.add_argument("--count", type=int, default=16)
    p.add_argument("--sop", type=int, default=1)
    p.add_argument("--bank", type=int, default=1)
    p.add_argument("--n", type=int, default=2, help="watch iterations")
    p.add_argument("--gap", type=float, default=30.0)
    args = p.parse_args()
    if args.action == "sweep":
        sweep()
    elif args.action == "sweep5":
        sweep5()
    elif args.action == "watch":
        for i in range(args.n):
            sweep("t%d" % i)
            if i + 1 < args.n:
                time.sleep(args.gap)
    elif args.action == "release":
        release(args.qid, args.count, args.sop, args.bank)
    elif args.action == "rings":
        ring_dma_regs()
