#!/usr/bin/env python3
"""WiFi UP-direction (phone -> WAN host) offload A/B run.

WHY: wifi_ab.py measures the DN direction (phone HTTP GET). The Stage-3 UP
fix (fabric key_hdr 0x38 / rule 0x70, findings/wifi_stage3_up_cla_keymiss_
forensics_2026-07-28.md) needs an UPLOAD throughput + counter A/B: host
listener on the WAN subnet measures actually-received bytes/s while the adb
phone pushes /dev/zero over TCP; qmg_up_* + wifi_bind counters are snapshotted
pre/post with ab_ctrs pacing (console-safe).

Usage: upab.py <label> <ftwifi 0|1> [dur_s]
Preconditions: wifi_up.py all --adb done; nft flowtable rig loaded; idm1 up;
host return-route 192.168.50.0/24 via 10.44.66.223 dev wlo1.
"""
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

CTRS = list(ab_ctrs.CTRS) + [("cla_dn_fwd", 0x9238c3cc), ("cla_acl_fail", 0x9238c3c4)]


def rd_pokes():
    cmds = ["echo %08x > /sys/kernel/debug/zx_eth/poke" % a for _, a in CTRS]
    cmds.append("dmesg | busybox grep -a 'peek 0x' | busybox tail -%d" % (len(CTRS) + 4))
    out = ab_ctrs.zc(cmds, wait=3)
    vals = {}
    for name, addr in CTRS:
        m = re.findall(r"peek 0x%08x = 0x([0-9a-f]+)" % addr, out, re.I)
        vals[name] = int(m[-1], 16) if m else None
    return vals


def rd_stats():
    out = ab_ctrs.zc([
        'busybox grep -aE "rx_dispatched|tm_rx_fabric" /sys/kernel/debug/zx_eth/wifi_bind'],
        wait=3)
    v = {}
    m = re.search(r"rx_dispatched=(\d+) rx_nobind=(\d+) tx_injected=(\d+)", out)
    if m:
        v["rx_dispatched"], v["rx_nobind"], v["tx_injected"] = map(int, m.groups())
    m = re.search(r"tm_rx_fabric=(\d+) tm_rx_dispatched=(\d+)", out)
    if m:
        v["tm_rx_fabric"], v["tm_rx_dispatched"] = map(int, m.groups())
    return v


def snap(label, tag):
    p = rd_pokes()
    p.update(rd_stats())
    print("== SNAP %s %s ==" % (label, tag))
    print("  " + " ".join("%s=%s" % (k, ("0x%x" % x) if k.startswith(("qmg", "red", "pp",
          "sadm", "mac", "tmq", "cla")) and x is not None else x)
          for k, x in p.items()))
    return p


class Sink(threading.Thread):
    """Accept-and-drain listener; counts received bytes."""

    def __init__(self):
        super().__init__(daemon=True)
        self.sock = socket.socket()
        self.sock.setsockopt(socket.SOL_SOCKET, socket.SO_REUSEADDR, 1)
        self.sock.bind((HOST_WAN_IP, TEST_PORT))
        self.sock.listen(4)
        self.rx = 0
        self.lock = threading.Lock()

    def run(self):
        while True:
            try:
                c, _ = self.sock.accept()
            except OSError:
                return
            threading.Thread(target=self._drain, args=(c,), daemon=True).start()

    def _drain(self, c):
        while True:
            try:
                d = c.recv(65536)
            except OSError:
                return
            if not d:
                return
            with self.lock:
                self.rx += len(d)


def main():
    label, ftw = sys.argv[1], sys.argv[2]
    dur = int(sys.argv[3]) if len(sys.argv) > 3 else 30

    print(ab_ctrs.zc(["echo %s > /sys/kernel/debug/zx_eth/ftwifi; "
                      "cat /sys/kernel/debug/zx_eth/ftwifi" % ftw], wait=2)[-40:])
    pre = snap(label, "PRE")

    sink = Sink()
    sink.start()
    print("== %s: phone push /dev/zero -> %s:%d for %ds ==" %
          (label, HOST_WAN_IP, TEST_PORT, dur))
    ph = subprocess.Popen(
        ["adb", "shell",
         "toybox nc %s %d < /dev/zero" % (HOST_WAN_IP, TEST_PORT)],
        stdout=subprocess.DEVNULL, stderr=subprocess.DEVNULL)
    t0 = time.time()
    last = 0
    while time.time() - t0 < dur:
        time.sleep(5)
        with sink.lock:
            cur = sink.rx
        print("   t=%4.0fs rx=%.1f MB (+%.2f MB/s)" %
              (time.time() - t0, cur / 1e6, (cur - last) / 5e6))
        last = cur
    ph.kill()
    subprocess.run(["adb", "shell", "pkill -f 'toybox nc' 2>/dev/null || true"],
                   timeout=15)
    el = time.time() - t0
    with sink.lock:
        total = sink.rx
    sink.sock.close()

    post = snap(label, "POST")
    print("== %s RESULT: %.1f MB in %.0fs = %.2f MB/s ==" %
          (label, total / 1e6, el, total / el / 1e6))
    for k in ("qmg_up_sw", "qmg_up_hw", "qmg_up_trap", "qmg_dn_hw",
              "qmg_dn_trap", "tx_injected", "tm_rx_fabric", "cla_acl_fail"):
        a, b = pre.get(k), post.get(k)
        if a is not None and b is not None:
            print("   d%-13s = %d" % (k, b - a))
    out = ab_ctrs.zc(["dmesg | busybox grep -aE 'phaseC/ft|phase6/ft' | busybox tail -8"],
                     wait=3)
    print("== install log tail ==")
    print("\n".join(out.splitlines()[-10:]))


if __name__ == "__main__":
    main()
