#!/usr/bin/env python3
# DIAGNOSTIC: write the forward ram2 entry at ALL 256 buckets (0x00-0xff) so it covers
# whatever bucket the HW computes for the flow. If hw_trap then goes flat, the extract
# chain + entry work and only bucket-prediction was wrong. If it still traps, the chain
# isn't triggering for this flow (selection/enable) or the entry tuple doesn't match.
# Destructive (overwrites ram2); reboot restores. UART console independent.
import subprocess, re

REPO = "/home/ubuntu/Projects/MYSELF/ZTE"; ZCON = "/tmp/zcon.py"; PW = "45788798"
ENTRY = "3005044 fa11c000 608 80000000 6000009 32c0a800 32ac1f09 519c4009 14 0 0 0 0 0 0"
SPORT, DPORT, DST = 40000, 5201, "172.31.9.50"


def zcon(cmd, w=3):
    return subprocess.run(["python3", ZCON, cmd, str(w)], capture_output=True, text=True, cwd=REPO).stdout


def trap():
    m = re.search(r"peek 0x9234c060 = 0x([0-9a-f]+)", zcon("echo 9234c060 > /sys/kernel/debug/zx_eth/poke"))
    return int(m.group(1), 16) if m else None


def hping(n, sp):
    subprocess.run("echo %s | sudo -S hping3 -S -c %d -i u15000 -s %d -k -p %d %s >/dev/null 2>&1"
                   % (PW, n, sp, DPORT, DST), shell=True, cwd=REPO)


if __name__ == "__main__":
    print("writing entry at all 256 ram2 buckets...")
    for b in range(256):
        zcon("echo 2 %x %s > /sys/kernel/debug/zx_eth/clawrite" % (b, ENTRY), 2)
        if b % 64 == 63:
            print("  ...wrote through 0x%02x" % b)
    t0 = trap(); print("baseline hw_trap = 0x%x" % t0)
    hping(80, SPORT); t1 = trap(); print("matched (sport %d) delta = %d / 80" % (SPORT, t1 - t0))
    print("VERDICT: if matched << 80 -> chain+entry WORK (bucket was the gap); if ~80 -> chain not triggering")
