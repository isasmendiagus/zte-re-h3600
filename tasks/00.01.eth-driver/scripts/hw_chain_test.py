#!/usr/bin/env python3
# Phase 6 Stage 2b: enable the full CLA classification chain (ram0 extract + ram1 rule
# + ram2 fwd entry) and test whether a real flow HW-forwards (hw_trap flat).
# ram0/ram1 from the captured stock hardfast; ram2 = my flow at the inport-candidate buckets.
import subprocess, re

REPO = "/home/ubuntu/Projects/MYSELF/ZTE"
ZCON = "/tmp/zcon.py"
SUDO_PW = "45788798"
HW_TRAP = "9234c060"

RAM0_09 = "93929190 97969594 9b9a9998 9f9e9d9c 00150051"
RAM1_98 = "22038608 000058a1 0 0 f00ff000 ffffffff ffffffff 0fffffff 0 0 0 0 0 0 00700000 00092492 0"
ENTRY   = "3005044 fa11c000 608 80000000 6000009 32c0a800 32ac1f09 519c4009 14 0 0 0 0 0 0"
BUCKETS = [0x89, 0x6a, 0x41, 0xa2, 0xc6, 0x25]
SPORT, DPORT, DST = 40000, 5201, "172.31.9.50"


def zcon(cmd, wait=3):
    return subprocess.run(["python3", ZCON, cmd, str(wait)],
                          capture_output=True, text=True, cwd=REPO).stdout


def read_trap():
    out = zcon("echo %s > /sys/kernel/debug/zx_eth/poke" % HW_TRAP, 3)
    m = re.search(r"peek 0x9234c060 = 0x([0-9a-f]+)", out)
    return int(m.group(1), 16) if m else None


def hping(n, sport):
    subprocess.run("echo %s | sudo -S hping3 -S -c %d -i u15000 -s %d -k -p %d %s "
                   ">/dev/null 2>&1" % (SUDO_PW, n, sport, DPORT, DST), shell=True, cwd=REPO)


if __name__ == "__main__":
    print("== save ram1[0x98] (pre) ==")
    print(" ", zcon("echo 1 98 > /sys/kernel/debug/zx_eth/clapeek", 3).strip().splitlines()[-2:])
    print("== write ram0[0x09] extract ==")
    zcon("echo 0 9 %s > /sys/kernel/debug/zx_eth/clawrite" % RAM0_09, 3)
    print("== write ram1[0x98] rule ==")
    zcon("echo 1 98 %s > /sys/kernel/debug/zx_eth/clawrite" % RAM1_98, 3)
    print("== (re)write ram2 fwd entry at candidate buckets ==")
    for b in BUCKETS:
        zcon("echo 2 %x %s > /sys/kernel/debug/zx_eth/clawrite" % (b, ENTRY), 3)
    print("== verify ram0[0x09] readback ==")
    print(" ", zcon("echo 0 9 > /sys/kernel/debug/zx_eth/clapeek", 3).strip().splitlines()[-2:])
    t0 = read_trap(); print("== baseline hw_trap = 0x%x ==" % t0)
    print("== 60 SYNs MATCHED flow (sport %d) ==" % SPORT)
    hping(60, SPORT); t1 = read_trap()
    print("   delta = %d (for 60 pkts)" % (t1 - t0))
    print("== 60 SYNs CONTROL (sport 49999) ==")
    hping(60, 49999); t2 = read_trap()
    print("   delta = %d (for 60 pkts)" % (t2 - t1))
    print("== VERDICT: matched=%d control=%d (HW-fwd if matched<<control) ==" % (t1 - t0, t2 - t1))
