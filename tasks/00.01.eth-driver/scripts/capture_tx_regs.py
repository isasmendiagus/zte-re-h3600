#!/usr/bin/env python3
"""Capture stock register state before+after TX via /proc/tm/shell.

Stock plat.ko exports fpga_read_reg + fpga_write_reg. We call fpga_read_reg
across all relevant register windows, snapshot, trigger TX (ping), snapshot
again, diff. Result: every register stock's TX path touched.

Ranges:
  PON  (npp + idm + tm + pp): offsets 0x0000..0x40000 via NPP base
  TM  : offsets 0x0..0x10000 via TM base (0x92340000)
  PP  : offsets 0x0..0x10000 via PP base (0x92380000)

We use fpga_read_reg's wrapper convention (verified earlier):
  fpga_read_reg(offset) → readl(pon_base + offset*4)
"""
import sys, re, time, paramiko

HOST, USER, PASS = '192.168.1.1', 'admin', 'UkuGPeyRDU'

def conn():
    c = paramiko.SSHClient()
    c.set_missing_host_key_policy(paramiko.AutoAddPolicy())
    c.connect(HOST, username=USER, password=PASS, allow_agent=False,
              look_for_keys=False, timeout=10)
    sh = c.invoke_shell(width=240, height=50)
    time.sleep(0.6)
    while sh.recv_ready(): sh.recv(65536)
    return c, sh

def run(sh, cmd, t=120):
    sh.send(cmd + '\n')
    out = bytearray()
    deadline = time.time() + t
    while time.time() < deadline:
        if sh.recv_ready():
            out.extend(sh.recv(65536))
            if out.rstrip().endswith(b'# '):
                break
        time.sleep(0.05)
    return out.decode('utf-8', 'replace')

def snapshot(sh, label, offsets):
    """Read each offset via fpga_read_reg, capture printk. Returns {off: val}."""
    print(f'# snapshotting {label} ({len(offsets)} regs) ...', flush=True)
    run(sh, 'rm -f /tmp/snap.bin; (cat /dev/logger_main > /tmp/snap.bin 2>&1 &); sleep 0.3')
    BATCH = 32
    for i in range(0, len(offsets), BATCH):
        chunk = offsets[i:i+BATCH]
        c = '; '.join(f'echo -f fpga_read_reg 0x{o:x} > /proc/tm/shell' for o in chunk)
        run(sh, c, t=60)
    run(sh, 'sleep 0.3; pkill -f "cat /dev/logger_main"')
    raw = run(sh, "grep -aE 'call func fpga_read_reg' /tmp/snap.bin")
    # Match each "call func fpga_read_reg, with p OFFSET" + following printk with value
    # Actually /proc/tm/shell prints: "call func fpga_read_reg,with p OFFSET" then "ret xxx"
    # So look at the LAST line after each call
    result = {}
    # Improved parse: look for "with p OFF" and the next "ret VAL"
    text = open('/tmp/snap_local.txt', 'w') if False else None
    # Use a different parse: dump everything and find pairs
    full = run(sh, "cat /tmp/snap.bin", t=10)
    for m in re.finditer(r"call func fpga_read_reg,with p ([0-9a-fA-F]+)", full):
        off = int(m.group(1), 16)
        # We don't have ret value capture in printk, so just mark as queried
        result[off] = 0
    return result, full

if __name__ == '__main__':
    c, sh = conn()
    try:
        # Enable console + debug
        run(sh, 'logctrl -m -p /dev/console -g 3 2>&1 | head -3')
        run(sh, 'echo g_tm_debug_level=4 > /proc/tm/shell')
        run(sh, 'echo g_switch_debug_level=4 > /proc/tm/shell')
        run(sh, 'echo g_phy_dbg_lvl=4 > /proc/tm/shell')

        # Just do a focused TX printk capture with debug levels set
        print('# capturing /dev/logger_main during ping (3s window)...', flush=True)
        run(sh, 'rm -f /tmp/tx.bin; (cat /dev/logger_main > /tmp/tx.bin 2>&1 &); sleep 0.5; '
                'ping -c 3 192.168.1.50 > /dev/null 2>&1; sleep 1; '
                'pkill -f "cat /dev/logger_main"; ls -la /tmp/tx.bin')

        # Pull it
        out = run(sh, "wc -c /tmp/tx.bin", t=10)
        print(out)
        # Show first some lines after parsing
        s = run(sh, "strings /tmp/tx.bin | head -100 2>&1", t=20)
        print('--- captured strings (first 100) ---')
        print(s[-4000:])
    finally:
        sh.close(); c.close()
