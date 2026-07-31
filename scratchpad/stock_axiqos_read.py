#!/usr/bin/env python3
"""Read the SoC AXI bus-matrix/QoS block (phys 0x00a20000) + sys_ctrl from a
LIVE STOCK box over SSH, to verify the values [A09] replicates.

WHY: [A09] (zx-pon-plat.c zx_soc_axi_qos_init) was derived from STATIC RE of
stock's vmlinux zx279128_init_machine ([vm-05] in
static_analysis_vmlinux_platform_init.md). Static RE can be wrong about
ordering/masking, and the block is outside every register window our stock
captures cover. This confirms the live stock values so the fix is grounded in
measurement, not just decompilation.

SAFETY (hard rules for a live stock box, learned the hard way):
  * READ-ONLY. No writes at all.
  * NEVER touch TM 0x92340128 / 0x92340130 — writing them killed the datapath
    instantly on a live stock box in a previous session.
  * NEVER bulk-dump the 0x92000000 region / MAC4.
This script only reads 0x00a20000 (SoC AXI block), 0x94000000 (top_crm) and
0x94100000 (sys_ctrl) — none are in the datapath window.

Usage: stock_axiqos_read.py
"""
import re
import sys
import time

import paramiko

HOST, USER, PW = "192.168.1.1", "admin", "UkuGPeyRDU"

# (label, phys, dword_count)
BLOCKS = [
    ("AXI_QOS  0x00a20000", 0x00A20000, 0x40),
    ("TOPCRM   0x94000000", 0x94000000, 0x20),
    ("SYS_CTRL 0x94100000", 0x94100000, 0x20),
]


def sh(ch, cmd, t=1.2):
    ch.send(cmd + "\n")
    out, end = "", time.time() + t
    while time.time() < end:
        if ch.recv_ready():
            out += ch.recv(65536).decode(errors="replace")
            end = time.time() + t
        else:
            time.sleep(0.04)
    return out


def main():
    c = paramiko.SSHClient()
    c.set_missing_host_key_policy(paramiko.AutoAddPolicy())
    c.connect(HOST, username=USER, password=PW, timeout=15,
              allow_agent=False, look_for_keys=False)
    ch = c.invoke_shell(width=200, height=20000)
    time.sleep(1.0)
    # cspd installs a LAN-SSH drop rule shortly after boot; clear it so the
    # session survives (documented in CLAUDE.md "SSH gotchas").
    sh(ch, "iptables -F srvcntrl 2>/dev/null; echo ok", 1.5)

    tool = None
    for cand in ("/bin/memdump", "memdump", "devmem2"):
        out = sh(ch, "which %s 2>/dev/null || ls %s 2>/dev/null" % (cand, cand), 1.0)
        if cand in out and "No such" not in out:
            tool = cand
            break
    print("# reader tool on stock: %s" % tool)
    if tool is None:
        print("!! no memdump/devmem2 on this stock rootfs — cannot read")
        return 1

    for label, base, n in BLOCKS:
        print("\n=== %s (%d dwords) ===" % (label, n))
        if "memdump" in tool:
            out = sh(ch, "%s 0x%x 0x%x" % (tool, base, n * 4), 3.0)
            for m in re.finditer(r"^([0-9a-f]{8})\s+([0-9a-f]{8})\s*$",
                                 out, re.M | re.I):
                print("%s %s" % (m.group(1), m.group(2)))
        else:
            for i in range(n):
                out = sh(ch, "%s 0x%x w" % (tool, base + i * 4), 0.6)
                m = re.search(r"): 0x([0-9A-Fa-f]+)", out)
                print("%08x %s" % (base + i * 4,
                                   m.group(1).lower() if m else "MISSING"))
    ch.close()
    c.close()
    return 0


if __name__ == "__main__":
    sys.exit(main())
