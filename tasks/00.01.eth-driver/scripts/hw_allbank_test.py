#!/usr/bin/env python3
# DECISIVE: write the forward ram2-6 entry at ALL 520 hash slots across every bank
# (ram2[0..0xff], ram3[0..0x7f], ram4[0..0x3f], ram5[0..0x3f], ram6[0..7]) so it covers
# ANY bucket the HW could compute in any bank. If the flow then HW-forwards, the gap was
# bucket coverage (the bucket was in ram3-6, which the earlier ram2-only sweep missed).
# If it STILL traps, the gate is upstream of the hash lookup (ingress consult), not bucket.
# Destructive; reboot restores. Also restores outspace to the stock value 0x4 first.
import subprocess, re

REPO = "/home/ubuntu/Projects/MYSELF/ZTE"; ZCON = "/tmp/zcon.py"; PW = "45788798"
ENTRY = "3005044 fa11c000 608 80000000 6000009 32c0a800 32ac1f09 519c4009 14 0 0 0 0 0 0"
SPORT, DPORT, DST = 40000, 5201, "172.31.9.50"
BANKS = [(2, 0x100), (3, 0x80), (4, 0x40), (5, 0x40), (6, 8)]  # (ram_id, count)


def zcon(cmd, w=2):
    return subprocess.run(["python3", ZCON, cmd, str(w)], capture_output=True, text=True, cwd=REPO).stdout


def trap():
    m = re.search(r"peek 0x9234c060 = 0x([0-9a-f]+)", zcon("echo 9234c060 > /sys/kernel/debug/zx_eth/poke", 3))
    return int(m.group(1), 16) if m else None


def clafwd():
    m = re.search(r"peek 0x9238c3c0 = 0x([0-9a-f]+)", zcon("echo 9238c3c0 > /sys/kernel/debug/zx_eth/poke", 3))
    return int(m.group(1), 16) if m else None


def hping(n, sp):
    subprocess.run("echo %s | sudo -S hping3 -S -c %d -i u12000 -s %d -k -p %d %s >/dev/null 2>&1"
                   % (PW, n, sp, DPORT, DST), shell=True, cwd=REPO)


if __name__ == "__main__":
    # restore outspace to stock value 0x4 (the agent's build booted it at 0x8)
    zcon("echo 9238c094 4 > /sys/kernel/debug/zx_eth/poke", 2)
    print("writing entry across all 520 slots (ram2-6)...")
    n = 0
    for ram, cnt in BANKS:
        for a in range(cnt):
            zcon("echo %d %x %s > /sys/kernel/debug/zx_eth/clawrite" % (ram, a, ENTRY), 2)
            n += 1
        print("  ram%d done (%d slots)" % (ram, cnt))
    print("total slots written: %d" % n)
    f0, t0 = clafwd(), trap()
    print("baseline: CLA fwd=0x%x hw_trap=0x%x" % (f0, t0))
    hping(80, SPORT)
    f1, t1 = clafwd(), trap()
    print("after matched flow: CLA fwd=0x%x (delta %d) hw_trap=0x%x (delta %d)"
          % (f1, f1 - f0, t1, t1 - t0))
    print("VERDICT: CLA fwd climbs / hw_trap flat -> HW FORWARD (bucket was in ram3-6);"
          " else gate is upstream of the hash consult")
