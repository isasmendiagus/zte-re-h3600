#!/usr/bin/env python3
# Tight A/B counter read (slow-paced pokes, one connection). Usage: ab_ctrs.py [label]
import socket, time, select, re, sys

HOST, PORT = "127.0.0.1", 9999
CTRS = [
    ("qmg_dn_sw",   0x9234c044), ("qmg_dn_hw",   0x9234c048),
    ("qmg_dn_trap", 0x9234c04c), ("qmg_c050",    0x9234c050),
    ("qmg_up_sw",   0x9234c054), ("qmg_up_hw",   0x9234c058),
    ("qmg_up_trap", 0x9234c05c), ("qmg_c060",    0x9234c060),
    ("red_fwd_in",  0x92344204), ("red_trp_in",  0x92344208),
    ("red_fwd_out", 0x92344210), ("red_trp_out", 0x92344214),
    ("pp_drop",     0x921da040), ("red_drop",    0x921da044),
    ("sadm_pass",   0x921c4200), ("sadm_drop",   0x921c4208),
    ("mac2_tx",     0x92280718),
    ("tmq4_status", 0x92350110), ("tmq5_status", 0x92350114),
]

def zc(cmds, wait=2.5, hardcap=40):
    s = socket.create_connection((HOST, PORT), timeout=6); s.setblocking(False)
    t0 = time.time()
    while time.time() - t0 < 0.15:
        r, _, _ = select.select([s], [], [], 0.05)
        if r:
            try: s.recv(65536)
            except BlockingIOError: pass
    for c in cmds:
        s.sendall((c + "\n").encode()); time.sleep(0.25)
    buf = bytearray(); last = time.time()
    while time.time() - last < wait and time.time() - t0 < hardcap:
        r, _, _ = select.select([s], [], [], 0.1)
        if r:
            try:
                d = s.recv(65536)
                if d: buf += d; last = time.time()
            except BlockingIOError: pass
    s.close(); return buf.decode(errors="replace")

def read():
    cmds = ["echo %08x > /sys/kernel/debug/zx_eth/poke" % a for _, a in CTRS]
    cmds.append("dmesg | grep -a 'peek 0x' | tail -%d" % (len(CTRS) + 6))
    out = zc(cmds)
    vals = {}
    for name, addr in CTRS:
        m = re.findall(r"peek 0x%08x = 0x([0-9a-f]+)" % addr, out, re.I)
        vals[name] = int(m[-1], 16) if m else None
    return vals

if __name__ == "__main__":
    label = sys.argv[1] if len(sys.argv) > 1 else "READ"
    v = read()
    for name, _ in CTRS:
        x = v[name]
        print("%s %-13s = %s" % (label, name, ("0x%08x" % x) if x is not None else "MISS"))
