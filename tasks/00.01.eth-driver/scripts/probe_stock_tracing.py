#!/usr/bin/env python3
"""Probe stock for ANY kernel tracing/debug infrastructure available.
No mounts assumed — check what's already there."""
import paramiko, time

HOST, USER, PASS = '192.168.1.1', 'admin', 'UkuGPeyRDU'

def run(sh, cmd, wait=4):
    sh.send(cmd + '\n')
    deadline = time.time() + wait
    buf = b''
    while time.time() < deadline:
        if sh.recv_ready():
            buf += sh.recv(32768)
            if buf.rstrip().endswith(b'# '):
                break
        time.sleep(0.05)
    return buf.decode('utf-8', 'replace')

c = paramiko.SSHClient()
c.set_missing_host_key_policy(paramiko.AutoAddPolicy())
c.connect(HOST, username=USER, password=PASS, allow_agent=False, look_for_keys=False, timeout=10)
sh = c.invoke_shell(width=240, height=50)
time.sleep(1.0)
while sh.recv_ready(): sh.recv(16384)

probes = [
    "echo === current mounts ===; mount | grep -E 'debug|trace|proc|sys' 2>&1",
    "echo === /sys/kernel ===; ls /sys/kernel/ 2>&1",
    "echo === /sys/kernel/debug ===; ls -la /sys/kernel/debug/ 2>&1",
    "echo === /sys/kernel/debug/tracing ===; ls /sys/kernel/debug/tracing/ 2>&1",
    "echo === /sys/kernel/tracing ===; ls /sys/kernel/tracing/ 2>&1",
    "echo === /proc/sys/kernel ===; ls /proc/sys/kernel/ 2>&1 | grep -i -E '(trace|kprobe|ftrace|perf|debug)'",
    "echo === /proc/config ===; ls /proc/config* 2>&1",
    "echo === /proc/kallsyms grep trace/kprobe ===; cat /proc/kallsyms 2>/dev/null | grep -iE '(kprobe|ftrace|register_trace)' | head -20",
    "echo === /proc/modules ===; cat /proc/modules 2>/dev/null | head -10",
    "echo === uname -a ===; uname -a",
    "echo === /proc/version ===; cat /proc/version 2>&1",
    "echo === all top-level /sys/kernel ===; find /sys/kernel -maxdepth 2 -type d 2>/dev/null | head -30",
    "echo === any kprobe/ftrace anywhere? ===; find /sys /proc -name 'kprobe*' -o -name 'ftrace*' -o -name 'tracing' 2>/dev/null | head -20",
    "echo === stock proc/tm/shell ===; ls /proc/tm/ 2>&1",
    "echo === /dev/logger_main ===; ls -la /dev/logger_main 2>&1",
    "echo === g_tm_debug_level via /proc/tm/shell ===; echo g_tm_debug_level > /proc/tm/shell 2>&1; sleep 1; echo done",
]
for p in probes:
    print(run(sh, p, wait=3))
sh.close(); c.close()
