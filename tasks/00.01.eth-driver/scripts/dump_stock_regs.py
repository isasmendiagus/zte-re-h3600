#!/usr/bin/env python3
"""Dump a range of FPGA registers from stock via `fpga -r` + /dev/logger_main capture.

Usage:
  dump_stock_regs.py START_OFF END_OFF [STEP]
e.g.
  dump_stock_regs.py 0xD0000 0xE0000   # full TM region (256 KB, 65k regs)
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

def run(sh, cmd, t=300):
    sh.send(cmd + '\n')
    out = bytearray()
    deadline = time.time() + t
    while time.time() < deadline:
        if sh.recv_ready():
            out.extend(sh.recv(65536))
            if out.rstrip().endswith(b'# '):
                break
        time.sleep(0.1)
    return out.decode('utf-8', 'replace')

if __name__ == '__main__':
    if len(sys.argv) < 3:
        print('usage: START_OFF END_OFF [STEP]', file=sys.stderr); sys.exit(2)
    start = int(sys.argv[1], 0)
    end   = int(sys.argv[2], 0)
    step  = int(sys.argv[3], 0) if len(sys.argv) > 3 else 1

    c, sh = conn()
    try:
        run(sh, 'logctrl -m -p /dev/console -g 3 > /dev/null 2>&1')
        # Build one giant shell loop using `for a in ...; do fpga -r $a 1; done`
        # but shell args are limited. Use seq with printf.
        # We'll batch by chunks of 4096 regs per ssh round-trip.
        BATCH = 4096
        all_lines = []
        for batch_start in range(start, end, BATCH * step):
            batch_end = min(batch_start + BATCH * step, end)
            n = (batch_end - batch_start) // step
            print(f'# batch 0x{batch_start:x}..0x{batch_end:x} ({n} regs)', flush=True)
            # Build address list inline (won't fit if huge — but 4096 is ok)
            # Use awk to gen list of offsets
            cmd = (
                f'rm -f /tmp/r.bin; (cat /dev/logger_main > /tmp/r.bin 2>&1 &) ; sleep 0.3; '
                f'a={batch_start}; while [ $a -lt {batch_end} ]; do '
                f'  fpga -r $(printf 0x%x $a) 1 > /dev/null 2>&1; '
                f'  a=$((a + {step})); '
                f'done; '
                f'sleep 0.5; killall cat 2>/dev/null; '
                f'grep -aE "fpga read:" /tmp/r.bin > /tmp/r.txt; wc -l /tmp/r.txt'
            )
            out = run(sh, cmd, t=BATCH * 0.05 + 60)
            # pull the parsed lines
            data = run(sh, 'cat /tmp/r.txt', t=60)
            for ln in data.splitlines():
                m = re.match(r"fpga read: reg=0x([0-9a-f]+), value=0x([0-9a-f]+)", ln)
                if m:
                    all_lines.append((int(m.group(1), 16), int(m.group(2), 16)))

        # dedupe (keep last)
        regs = {}
        for off, val in all_lines:
            regs[off] = val
        print(f'\n# === captured {len(regs)} unique regs from 0x{start:x}..0x{end:x} ===')
        for off in sorted(regs):
            print(f'0x{off:08x}: 0x{regs[off]:08x}')
    finally:
        sh.close(); c.close()
