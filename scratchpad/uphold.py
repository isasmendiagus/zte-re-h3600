#!/usr/bin/env python3
"""Hold a WiFi UP retransmit flow alive for CLA probing (Stage-3 UP fix).

WHY: upkey.py's capture() tears its flow down after sampling; the UP-offload
discrimination tests (da_known bit, fill520, higher banks) need ONE persistent
fabric-ingress flow retransmitting the same segment for minutes while we poke
CLA state between probes.

start:  host sink on :9099 -> phone nc pushes /dev/zero -> wait for the
        hardfast install (streaming) -> host DROPs INPUT :9099 -> from then on
        the phone retransmits into the fabric (idm1 must be up). The sink
        thread must stay alive => this command BLOCKS; run it in background.
probe:  10 s delta of {tx_injected, cla_acl_fail, cla_up_fwd, qmg_up_*} ->
        prints MISS/HIT verdict for the held flow.
stop:   kill phone nc + remove the DROP rule.
"""
import os
import re
import socket
import subprocess
import sys
import threading
import time
from pathlib import Path

sys.path.insert(0, str(Path(__file__).resolve().parent))
import ab_ctrs  # noqa: E402

HOST_WAN_IP = "10.44.66.133"
TEST_PORT = 9099

CTRS = [
    ("qmg_up_sw",   0x9234c054), ("qmg_up_hw",   0x9234c058),
    ("qmg_up_trap", 0x9234c05c), ("qmg_dn_hw",   0x9234c048),
    ("cla_up_fwd",  0x9238c3c0), ("cla_acl_fail", 0x9238c3c4),
    ("cla_dn_fwd",  0x9238c3cc),
]


def sudo(cmd):
    pw = os.environ.get("ZTE_SUDO_PW", "")
    return subprocess.run("echo %s | sudo -S %s" % (pw, cmd), shell=True,
                          capture_output=True, text=True, timeout=30)


def rd():
    cmds = ["echo %08x > /sys/kernel/debug/zx_eth/poke" % a for _, a in CTRS]
    cmds.append("busybox grep -a tx_injected /sys/kernel/debug/zx_eth/wifi_bind")
    cmds.append("dmesg | busybox grep -a 'peek 0x' | busybox tail -%d" % (len(CTRS) + 4))
    out = ab_ctrs.zc(cmds, wait=3)
    vals = {}
    for name, addr in CTRS:
        m = re.findall(r"peek 0x%08x = 0x([0-9a-f]+)" % addr, out, re.I)
        vals[name] = int(m[-1], 16) if m else None
    m = re.search(r"tx_injected=(\d+)", out)
    vals["tx_injected"] = int(m.group(1)) if m else None
    return vals


def probe(secs=10):
    a = rd()
    time.sleep(secs)
    b = rd()
    print("== probe %ds deltas ==" % secs)
    for k, _ in CTRS + [("tx_injected", 0)]:
        if a.get(k) is not None and b.get(k) is not None:
            print("   d%-12s = %d" % (k, b[k] - a[k]))
    inj = (b.get("tx_injected") or 0) - (a.get("tx_injected") or 0)
    miss = (b.get("cla_acl_fail") or 0) - (a.get("cla_acl_fail") or 0)
    if inj == 0:
        print("   VERDICT: NO INJECTIONS (flow dead? idm1 down?)")
    elif miss >= inj * 0.8:
        print("   VERDICT: MISS (acl_fail tracks injections)")
    else:
        print("   VERDICT: HIT-ish (acl_fail %d << injections %d)" % (miss, inj))


def start():
    sudo("iptables -D INPUT -p tcp --dport %d -j DROP 2>/dev/null" % TEST_PORT)
    srv = socket.socket()
    srv.setsockopt(socket.SOL_SOCKET, socket.SO_REUSEADDR, 1)
    srv.bind((HOST_WAN_IP, TEST_PORT))
    srv.listen(2)
    print("== sink on %s:%d; phone nc /dev/zero ==" % (HOST_WAN_IP, TEST_PORT))
    ph = subprocess.Popen(
        ["adb", "shell", "toybox nc %s %d < /dev/zero" % (HOST_WAN_IP, TEST_PORT)],
        stdout=subprocess.DEVNULL, stderr=subprocess.DEVNULL)
    srv.settimeout(20)
    c, addr = srv.accept()
    print("== connected from %s:%d ==" % addr)

    rx = [0]

    def drain():
        while True:
            try:
                d = c.recv(65536)
            except OSError:
                return
            if not d:
                return
            rx[0] += len(d)

    threading.Thread(target=drain, daemon=True).start()
    time.sleep(4)  # let the hardfast install + some data stream
    print("== streamed %.1f MB; applying ACK blackhole ==" % (rx[0] / 1e6))
    sudo("iptables -A INPUT -p tcp --dport %d -j DROP" % TEST_PORT)
    print("== HOLDING (nc pid %d). Ctrl-C/stop to end ==" % ph.pid)
    try:
        while True:
            time.sleep(30)
            if ph.poll() is not None:
                print("== phone nc exited ==")
                return
    except KeyboardInterrupt:
        pass


def stop():
    subprocess.run(["adb", "shell", "pkill -f 'toybox nc' 2>/dev/null || true"],
                   timeout=15)
    sudo("iptables -D INPUT -p tcp --dport %d -j DROP 2>/dev/null" % TEST_PORT)
    print("== stopped ==")


if __name__ == "__main__":
    {"start": start, "probe": lambda: probe(int(sys.argv[2]) if len(sys.argv) > 2 else 10),
     "stop": stop}[sys.argv[1]]()
