#!/usr/bin/env python3
# Phase 6 Stage 2b slot-sweep runner: write the forward ram2 entry at candidate
# buckets, drive a fixed-5-tuple TCP stream, measure hw_trap delta. FLAT = HW forward.
import subprocess, re, time, sys

REPO = "/home/ubuntu/Projects/MYSELF/ZTE"
ZCON = "/tmp/zcon.py"
SUDO_PW = "45788798"
HW_TRAP = "9234c060"

ENTRY = "3005044 fa11c000 608 80000000 6000009 32c0a800 32ac1f09 519c4009 14 0 0 0 0 0 0"
BUCKETS = [0x89, 0x6a, 0x41, 0xa2, 0xc6, 0x25]      # mask 0xff, inport 5..0
# flow: 192.168.9.50:40000 -> 172.31.9.50:5201 TCP, ingress lan4
SPORT, DPORT, DST = 40000, 5201, "172.31.9.50"


def zcon(cmd, wait=3):
    out = subprocess.run(["python3", ZCON, cmd, str(wait)],
                         capture_output=True, text=True, cwd=REPO).stdout
    return out


def read_trap():
    out = zcon("echo %s > /sys/kernel/debug/zx_eth/poke" % HW_TRAP, 3)
    m = re.search(r"peek 0x9234c060 = 0x([0-9a-f]+)", out)
    return int(m.group(1), 16) if m else None


def clapeek(bucket):
    out = zcon("echo 2 %x > /sys/kernel/debug/zx_eth/clapeek" % bucket, 3)
    m = re.search(r"clapeek ram2 addr0x%x: ([0-9a-f ]+)" % bucket, out)
    return m.group(1).strip() if m else "?"


def clawrite(bucket):
    zcon("echo 2 %x %s > /sys/kernel/debug/zx_eth/clawrite" % (bucket, ENTRY), 3)


def hping(n, sport):
    subprocess.run("echo %s | sudo -S hping3 -S -c %d -i u15000 -s %d -k -p %d %s "
                   ">/dev/null 2>&1" % (SUDO_PW, n, sport, DPORT, DST),
                   shell=True, cwd=REPO)


if __name__ == "__main__":
    print("== pre-write clapeek of candidate buckets (what we overwrite) ==")
    for b in BUCKETS:
        print("  ram2[0x%02x]: %s" % (b, clapeek(b)))
    print("== writing forward entry at all %d candidate buckets ==" % len(BUCKETS))
    for b in BUCKETS:
        clawrite(b)
    # control flow (different sport -> different bucket, NOT written) to prove specificity
    print("== baseline hw_trap ==")
    t0 = read_trap(); print("  t0 = 0x%x" % t0)
    print("== sending 60 SYNs on the MATCHED 5-tuple (sport %d) ==" % SPORT)
    hping(60, SPORT)
    t1 = read_trap(); print("  t1 = 0x%x  (delta %d for 60 pkts)" % (t1, t1 - t0))
    print("== control: 60 SYNs on a NON-written sport (49999) ==")
    hping(60, 49999)
    t2 = read_trap(); print("  t2 = 0x%x  (delta %d for 60 pkts)" % (t2, t2 - t1))
    print("== VERDICT ==")
    print("  matched-flow delta = %d, control delta = %d" % (t1 - t0, t2 - t1))
    print("  HW-FORWARD if matched delta << control delta (matched ~0, control ~60)")
