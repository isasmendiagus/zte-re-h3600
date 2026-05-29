#!/usr/bin/env python3
"""EMPIRICAL CPU->LAN egress trace capture on factory stock.

Enables stock's own debug logging (g_tm_debug_level / g_switch_debug_level /
g_phy_dbg_lvl via /proc/tm/shell -- SAFE, datapath untouched), captures
/dev/logger_main while the HOST pings the device (device echoes ICMP replies
out MAC2/LAN = the CPU->LAN egress we want to trace), then pulls + parses the
log for the egress-path function-call sequence and every fpga_write_reg ID.

Only /proc/tm/shell debug knobs are written. No hardware registers written.
Device left on stock, SSH closed cleanly.
"""
import sys, re, time, subprocess, paramiko

HOST, USER, PASS = '192.168.1.1', 'admin', 'UkuGPeyRDU'
OUTDIR = '/home/ubuntu/Projects/MYSELF/ZTE/tasks/00.10.02.re-stock-kmods/findings'


def conn():
    c = paramiko.SSHClient()
    c.set_missing_host_key_policy(paramiko.AutoAddPolicy())
    c.connect(HOST, username=USER, password=PASS, allow_agent=False,
              look_for_keys=False, timeout=15)
    sh = c.invoke_shell(width=240, height=60)
    time.sleep(1.0)
    while sh.recv_ready():
        sh.recv(65536)
    return c, sh


def run(sh, cmd, t=12):
    sh.send(cmd + '\n')
    out = bytearray()
    dl = time.time() + t
    while time.time() < dl:
        if sh.recv_ready():
            out.extend(sh.recv(65536))
            if out.rstrip().endswith(b'# '):
                break
        time.sleep(0.03)
    return out.decode('utf-8', 'replace')


def main():
    c, sh = conn()
    try:
        # 1. Enable stock debug knobs (SAFE - no datapath/registers touched)
        print('# enabling debug levels via /proc/tm/shell', flush=True)
        for knob in ('g_tm_debug_level=4', 'g_switch_debug_level=4',
                     'g_phy_dbg_lvl=4'):
            print(run(sh, f'echo {knob} > /proc/tm/shell 2>&1').strip(),
                  flush=True)

        # 2. Capture logger_main during a SMALL host ping. The device-side
        #    cat backgrounds; the host ping happens from THIS machine in
        #    parallel (see runner below). Here we just arm + window the cat.
        print('# arming logger_main capture (device side)', flush=True)
        run(sh, 'rm -f /tmp/eg.bin; (cat /dev/logger_main > /tmp/eg.bin 2>&1 &); '
                'echo ARMED', t=8)
        time.sleep(0.8)  # let cat attach
        # host-side ping: device echoes 3 ICMP replies out MAC2/LAN = CPU->LAN egress
        print('# host ping -c 3 192.168.1.1 (generates the egress)', flush=True)
        try:
            r = subprocess.run(['ping', '-c', '3', '-i', '0.5', '192.168.1.1'],
                               capture_output=True, text=True, timeout=15)
            print(r.stdout.strip().splitlines()[-2:] and
                  '\n'.join(r.stdout.strip().splitlines()[-2:]), flush=True)
        except Exception as e:
            print('# host ping err', e, flush=True)
        time.sleep(2)  # let the verbose log flush
        run(sh, 'pkill -f "cat /dev/logger_main"; sync; ls -la /tmp/eg.bin', t=8)
        sz = run(sh, 'wc -c /tmp/eg.bin', t=8)
        print('# capture size:', sz.strip().splitlines()[-2] if len(sz.splitlines()) > 1 else sz.strip(),
              flush=True)

        # 3. Disable debug knobs again (leave device quiet)
        for knob in ('g_tm_debug_level=0', 'g_switch_debug_level=0',
                     'g_phy_dbg_lvl=0'):
            run(sh, f'echo {knob} > /proc/tm/shell 2>&1', t=6)

        # 4. Pull the raw log via SFTP (more reliable than shell echo)
        sftp = c.open_sftp()
        sftp.get('/tmp/eg.bin', OUTDIR + '/eg_raw.bin')
        sftp.close()
        print('# pulled /tmp/eg.bin ->', OUTDIR + '/eg_raw.bin', flush=True)
    finally:
        sh.close(); c.close()


if __name__ == '__main__':
    main()
