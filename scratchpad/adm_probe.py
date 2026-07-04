#!/usr/bin/env python3
"""adm_probe.py — read/program the ADM per-CPU-queue PPS policer (phys 0x92394000).

Decode source: findings/queue_subsystem_re_2026-07-04.md §B (from stock tm.c
decomp adm_set_policing_enable@17197 / adm_set_pass_pktcnt_persec@17296 /
tm_pon_pp_adm_initial@42773 / zte_api_pp_set_cpu_queue_rate@57522).

Register map (all in the poke MMIO window [0x921c0000,0x923c0000), TM range —
NOT the MAC4 hazard region):
  0x92394000[0]   turnon_enable        (ADM master enable)
  0x92394048[27:0] one_second          (200e6 = 200MHz ticks/sec)
  0x92394080+q*4  UP  pps[20:0] | en<<21   (dir==1 bank)
  0x923940c0+q*4  DN  pps[20:0] | en<<21   (dir==0 bank)
  0x92394100+q*4  DN  PASS counter (RO)
  0x92394140+q*4  UP  PASS counter (RO)
  0x92394180+q*4  DN  DROP counter (RO)  <-- oracle
  0x923941c0+q*4  UP  DROP counter (RO)  <-- oracle

All reads/writes go through the driver's `poke` debugfs node via the UART REPL
(scratchpad/ctr.py zc). Single-address idiom only. Read = `echo <phys>`,
write = `echo <phys> <val>`; readback printed to dmesg as "peek/poke 0x..".
"""
import argparse
import os
import re
import sys
import time

HERE = os.path.dirname(os.path.abspath(__file__))
sys.path.insert(0, HERE)
import ctr

ADM = 0x92394000
TURNON = ADM + 0x000
ONE_SECOND = ADM + 0x048
UP_PPS = ADM + 0x080
DN_PPS = ADM + 0x0c0
DN_PASS = ADM + 0x100
UP_PASS = ADM + 0x140
DN_DROP = ADM + 0x180
UP_DROP = ADM + 0x1c0

ONE_SECOND_VAL = 200_000_000  # 0x0BEBC200
EN = 1 << 21


def poke_read(addrs, wait=1.5):
    cmds = ["echo %08x > /sys/kernel/debug/zx_eth/poke" % a for a in addrs]
    cmds.append("dmesg | grep -aE 'peek 0x|poke 0x' | tail -%d" % (len(addrs) + 4))
    out = ctr.zc(cmds, wait=wait)
    vals = {}
    for a in addrs:
        m = re.findall(r"(?:peek|poke) 0x%08x = 0x([0-9a-f]+)" % a, out, re.I)
        vals[a] = int(m[-1], 16) if m else None
    return vals


def poke_write(pairs, wait=1.5):
    """pairs = [(phys,val),...]"""
    cmds = ["echo %08x %08x > /sys/kernel/debug/zx_eth/poke" % (a, v) for a, v in pairs]
    cmds.append("dmesg | grep -a 'poke 0x' | tail -%d" % (len(pairs) + 2))
    out = ctr.zc(cmds, wait=wait)
    return out


def dump():
    addrs = [TURNON, ONE_SECOND]
    for base in (UP_PPS, DN_PPS, DN_PASS, UP_PASS, DN_DROP, UP_DROP):
        addrs += [base + q * 4 for q in range(8)]
    v = poke_read(addrs, wait=2.5)
    print("turnon      0x%08x = %s" % (TURNON, _h(v[TURNON])))
    print("one_second  0x%08x = %s" % (ONE_SECOND, _h(v[ONE_SECOND])))

    def row(name, base, decode_en=False):
        cells = []
        for q in range(8):
            val = v[base + q * 4]
            if val is None:
                cells.append("q%d=?" % q)
            elif decode_en:
                cells.append("q%d=%s%d" % (q, "E" if (val & EN) else "-", val & 0x1fffff))
            else:
                cells.append("q%d=%d" % (q, val))
        print("%-9s %s" % (name, "  ".join(cells)))

    row("UP_pps", UP_PPS, True)
    row("DN_pps", DN_PPS, True)
    row("DN_pass", DN_PASS)
    row("UP_pass", UP_PASS)
    row("DN_drop", DN_DROP)
    row("UP_drop", UP_DROP)
    return v


def drops(v=None):
    """Return {'q3':(dn,up),...} of the drop counters for the data queues."""
    if v is None:
        addrs = [DN_DROP + q * 4 for q in range(8)] + [UP_DROP + q * 4 for q in range(8)]
        v = poke_read(addrs, wait=2.0)
    out = {}
    for q in range(8):
        out[q] = (v.get(DN_DROP + q * 4), v.get(UP_DROP + q * 4))
    return out


def _h(x):
    return "0x%08x" % x if x is not None else "?"


def program(q_pps, one_sec=True):
    """q_pps = {q: pps}. Sets enable|pps on BOTH UP and DN banks for each q,
    programs one_second + turnon. Mirrors findings recipe #1."""
    pairs = []
    if one_sec:
        pairs.append((ONE_SECOND, ONE_SECOND_VAL))
    for q, pps in sorted(q_pps.items()):
        val = EN | (pps & 0x1fffff)
        pairs.append((UP_PPS + q * 4, val))
        pairs.append((DN_PPS + q * 4, val))
    out = poke_write(pairs, wait=2.5)
    # turnon LAST (master enable)
    poke_write([(TURNON, 1)], wait=1.5)
    return out


def disable():
    """Return every data/storm queue to unlimited (pps=0, enable=0) + turnon=0."""
    pairs = []
    for q in range(8):
        pairs.append((UP_PPS + q * 4, 0))
        pairs.append((DN_PPS + q * 4, 0))
    pairs.append((TURNON, 0))
    return poke_write(pairs, wait=2.5)


if __name__ == "__main__":
    p = argparse.ArgumentParser()
    p.add_argument("action", choices=["dump", "program", "disable", "drops"])
    p.add_argument("--pps", type=int, default=2000, help="pps for data queues q3/q4/q6")
    p.add_argument("--storm", type=int, default=8000, help="pps for storm queues q0/q5")
    p.add_argument("--q", default="3,4,6", help="data queues to cap (comma list)")
    args = p.parse_args()
    if args.action == "dump":
        dump()
    elif args.action == "drops":
        d = drops()
        for q in range(8):
            print("q%d: DN_drop=%s UP_drop=%s" % (q, d[q][0], d[q][1]))
    elif args.action == "program":
        qs = [int(x) for x in args.q.split(",") if x.strip() != ""]
        m = {0: args.storm, 5: args.storm}
        for q in qs:
            m[q] = args.pps
        print("programming: %s" % m)
        program(m)
        time.sleep(0.5)
        dump()
    elif args.action == "disable":
        disable()
        time.sleep(0.5)
        dump()
