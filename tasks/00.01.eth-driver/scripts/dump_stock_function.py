#!/usr/bin/env python3
"""Dump N bytes from stock kernel starting at any symbol or addr.
Uses a single shell command that loops on-device for speed."""
import sys, re, paramiko, time

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

def run(sh, cmd, t=15):
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

if __name__ == '__main__':
    target = sys.argv[1] if len(sys.argv) > 1 else 'register_netdevice'
    nbytes = int(sys.argv[2]) if len(sys.argv) > 2 else 256

    c, sh = conn()
    try:
        # Resolve symbol → addr
        if target.startswith('0x'):
            addr = int(target, 16)
        else:
            out = run(sh, f"awk '$3==\"{target}\"{{print $1}}' /proc/kallsyms", 10)
            m = re.search(r"\b([0-9a-f]{8})\b", out)
            if not m:
                print(f'symbol not found: {target}\n{out!r}', file=sys.stderr); sys.exit(1)
            addr = int(m.group(1), 16)
        print(f'# {target} = 0x{addr:08x}', flush=True)

        nwords = (nbytes + 3) // 4
        # Build device-side shell loop: write all addrs to a temp file, then loop with read
        # File approach is fast because the kernel /proc/tm/shell handles each line
        addrs = ' '.join(f'0x{addr + i*4:x}' for i in range(nwords))
        big = (f'(cat /dev/logger_main > /tmp/dump.bin 2>&1 &); '
               f'sleep 0.3; '
               f'for a in {addrs}; do echo -l $a > /proc/tm/shell; done; '
               f'sleep 0.5; '
               f'pkill -f "cat /dev/logger_main"; '
               f'echo CAPTURE_OK')
        print(f'# sending dump command ({len(big)} bytes, {nwords} addrs)', flush=True)
        run(sh, big, t=nwords * 0.05 + 30)

        result = run(sh, "grep -aE 'sym 0x[0-9a-f]+ is' /tmp/dump.bin", 30)
        words = {}
        for m in re.finditer(r"sym 0x([0-9a-f]+) is -?\d+\(0x([0-9a-f]+)\)", result):
            a = int(m.group(1), 16)
            v = int(m.group(2), 16)
            if addr <= a < addr + nbytes:
                words[a - addr] = v

        print(f'# Got {len(words)} of {nwords} words')
        for off in sorted(words):
            print(f'+0x{off:03x}: 0x{words[off]:08x}')
    finally:
        sh.close(); c.close()
