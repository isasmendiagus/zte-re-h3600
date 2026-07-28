#!/usr/bin/env python3
"""Fabric-ingress CLA key forensics (WiFi UP-offload lookup-miss, 2026-07-28).

WHY: the UP hardfast entry installs (raw ok, rc=0) but the CLA lookup misses
100% for fabric-ingress (idm/WLAN) frames. Need a CLEAN single-packet capture
of the HW-extracted hash key (gparsehashkey latch) for a genuine fabric-ingress
TCP data frame, to byte-diff against zx_ft_build_key()'s stored-key model.

Anti-chimera primitive: the latch (phys 0x9238c260..28c, 12 words) is re-latched
per parsed packet; reading it word-by-word over the UART mixes packets
(findings/wifi_stage3_up_offload_groundwork_2026-07-28.md). Here each snapshot
is ONE 48-byte read of debugfs zx_eth/mem (single memcpy_fromio in zx_mem_read)
=> atomic at the us scale:  dd bs=48 skip=39266 count=1   (0x1cc260/48 == 39266).

Traffic isolation: retransmit-storm trick (mirror of the 2026-07-03
kill-client-retransmit trick, UP direction): phone connects via the AP
(nc to the host's WAN-subnet IP), first segment ACKs normally, then the host
firewalls INPUT for that port -> every subsequent phone data segment gets NO
ACK -> TCP retransmits the SAME data frame with backoff -> the only repeating
CLA-parsed packet carrying our tuple is the FABRIC-INGRESS frame (idm1 up =
zx_wifi_rx_handler injects TCP data via zx_idm_xmit).

Usage:
  upkey.py model                # print zx_ft_build_key mirror for the test tuple
  upkey.py idle [N]             # N latch snapshots on the quiet rig (background chars)
  upkey.py capture [--secs S]   # full retransmit-rig capture (phone+host+device)
  upkey.py decode w0 w1 .. w11  # decode a captured 12-word key
"""
import argparse
import os
import re
import socket
import subprocess
import sys
import threading
import time
from pathlib import Path

HERE = Path(__file__).resolve().parent
sys.path.insert(0, str(HERE))
import ctr  # noqa: E402  (UART bridge REPL transport, :9999)

HOST_WAN_IP = "10.44.66.133"     # host wlo1 on the modem subnet
DEV_LAN4_IP = "10.44.66.223"
PHONE_IP = "192.168.50.10"       # udhcpd lease for the adb Galaxy
TEST_PORT = 9099

# gparsehashkey latch: phys 0x9238c260, zx_eth/mem offset 0x1cc260 = 48*39266
DD_KEY = ("busybox dd if=/sys/kernel/debug/zx_eth/mem bs=48 skip=39266 "
          "count=1 2>/dev/null | busybox od -A n -t x4")


def _sudo():
    pw = os.environ.get("ZTE_SUDO_PW", "")
    if not pw:
        f = HERE / ".sudo_pw"
        if f.exists():
            pw = f.read_text().strip()
    return "echo %s | sudo -S " % pw


# ---------------- key model (mirror of zx_ft_build_key) ----------------

def build_key(proto, sip, dip, sport, dport, is_wan):
    """Byte-exact mirror of zx-eth-main.c zx_ft_build_key()."""
    s = ip2u32(sip)
    d = ip2u32(dip)
    fields = [proto, (s >> 16) & 0xffff, s & 0xffff,
              (d >> 16) & 0xffff, d & 0xffff, sport, dport]
    kb = bytearray(48)
    kb[3] = 0x48
    if is_wan:
        kb[4] |= 1
    for n, f in enumerate(fields):
        base = 33 + 16 * n
        for i in range(16):
            if f & (1 << i):
                pos = base + i
                kb[pos >> 3] |= 1 << (pos & 7)
    return [int.from_bytes(kb[4 * i:4 * i + 4], "little") for i in range(12)]


def ip2u32(ip):
    a, b, c, d = (int(x) for x in ip.split("."))
    return (a << 24) | (b << 16) | (c << 8) | d


def u32_2ip(v):
    return ".".join(str((v >> s) & 0xff) for s in (24, 16, 8, 0))


def decode(words):
    """Decode a 12-word latch capture under the rule-0x90 field model."""
    kb = bytearray()
    for w in words:
        kb += int(w).to_bytes(4, "little")

    def bits(pos, n):
        v = 0
        for i in range(n):
            p = pos + i
            if kb[p >> 3] & (1 << (p & 7)):
                v |= 1 << i
        return v

    d = {
        "word0": words[0],
        "ex_rule_id": (words[0] >> 23) & 0xff,
        "outport": words[0] & 0x1f,
        "inport": (words[0] >> 5) & 0xfff,
        "pos32": bits(32, 1),
        "fields": [bits(33 + 16 * n, 16) for n in range(7)],
    }
    f = d["fields"]
    d["proto"] = f[0]
    d["sip"] = u32_2ip((f[1] << 16) | f[2])
    d["dip"] = u32_2ip((f[3] << 16) | f[4])
    d["sport"], d["dport"] = f[5], f[6]
    return d


def fmt(words):
    d = decode(words)
    return ("%s | rule=0x%02x inport=%d pos32=%d proto=%d %s:%d -> %s:%d"
            % (" ".join("%08x" % w for w in words), d["ex_rule_id"],
               d["inport"], d["pos32"], d["proto"], d["sip"], d["sport"],
               d["dip"], d["dport"]))


# ---------------- device sampling ----------------

def parse_od(out):
    """Parse repeated 12-word od blocks out of REPL output -> list of tuples."""
    words = [int(x, 16) for x in re.findall(r"\b[0-9a-f]{8}\b", out)]
    keys, i = [], 0
    # od prints 3 lines x 4 words per snapshot; re-chunk into 12s
    while i + 12 <= len(words):
        keys.append(tuple(words[i:i + 12]))
        i += 12
    return keys


def burst(n, gap, wait_extra=8):
    """n atomic latch snapshots, gap seconds apart, in ONE device-side loop."""
    cmd = ("for i in $(busybox seq 1 %d); do %s; busybox sleep %s; done"
           % (n, DD_KEY, gap))
    out = ctr.zc([cmd], wait=n * (float(gap) + 0.3) + wait_extra)
    # strip the echoed command (contains no od-style lines with leading space)
    lines = [l for l in out.splitlines()
             if re.match(r"^\s+[0-9a-f]{8}( [0-9a-f]{8}){1,3}\s*$", l)]
    return parse_od("\n".join(lines))


# ---------------- capture rig ----------------

class Listener(threading.Thread):
    """Host-side accept-only TCP sink on the WAN-subnet IP."""

    def __init__(self):
        super().__init__(daemon=True)
        self.sock = socket.socket()
        self.sock.setsockopt(socket.SOL_SOCKET, socket.SO_REUSEADDR, 1)
        self.sock.bind((HOST_WAN_IP, TEST_PORT))
        self.sock.listen(4)
        self.peers = []

    def run(self):
        while True:
            try:
                c, a = self.sock.accept()
            except OSError:
                return
            self.peers.append(a)
            threading.Thread(target=self._drain, args=(c,),
                             daemon=True).start()

    def _drain(self, c):
        try:
            while c.recv(4096):
                pass
        except OSError:
            pass


def sh(cmd):
    p = subprocess.run(cmd, shell=True, capture_output=True, text=True,
                       timeout=60)
    return p.returncode, (p.stdout + p.stderr).strip()


def capture(secs):
    sudo = _sudo()
    print("== host: return-route + clean firewall")
    sh(sudo + "ip route replace 192.168.50.0/24 via %s dev wlo1" % DEV_LAN4_IP)
    sh(sudo + "iptables -D INPUT -p tcp --dport %d -j DROP 2>/dev/null" % TEST_PORT)

    lst = Listener()
    lst.start()
    print("== host: listener on %s:%d" % (HOST_WAN_IP, TEST_PORT))

    print("== device: idm1 up (activates rx_handler injection)")
    print(ctr.zc(["busybox ip link set idm1 up",
                  "busybox grep -a tx_injected /sys/kernel/debug/zx_eth/wifi_bind"],
                 wait=3)[-300:])

    print("== phone: connect + first (ACKed) segment")
    nc = subprocess.Popen(["adb", "shell", "toybox", "nc", HOST_WAN_IP,
                           str(TEST_PORT)], stdin=subprocess.PIPE)
    nc.stdin.write(b"hello-upkey-1\n")
    nc.stdin.flush()
    t0 = time.time()
    while not lst.peers and time.time() - t0 < 15:
        time.sleep(0.5)
    if not lst.peers:
        print("!! phone never connected -- check assoc/adb")
        nc.kill()
        return
    print("   connected from %s:%d (post-forward tuple)" % lst.peers[-1])

    print("== host: DROP INPUT :%d (ACK blackhole) + unACKed segment" % TEST_PORT)
    sh(sudo + "iptables -A INPUT -p tcp --dport %d -j DROP" % TEST_PORT)
    time.sleep(1)
    nc.stdin.write(b"RETRANSMIT-ME-" + b"U" * 400 + b"\n")
    nc.stdin.flush()

    print("== device: sampling latch for ~%ds" % secs)
    seen = {}
    n = max(4, secs // 8)
    for r in range(n):
        for k in burst(6, 1):
            seen[k] = seen.get(k, 0) + 1
    print("== phone: teardown")
    nc.kill()
    sh(sudo + "iptables -D INPUT -p tcp --dport %d -j DROP" % TEST_PORT)
    print(ctr.zc(["busybox ip link set idm1 down",
                  "busybox grep -a tx_injected /sys/kernel/debug/zx_eth/wifi_bind"],
                 wait=3)[-300:])
    lst.sock.close()

    print("== distinct keys (count desc):")
    for k, c in sorted(seen.items(), key=lambda kv: -kv[1]):
        print("%3dx %s" % (c, fmt(list(k))))
    return seen


# ---------------- cli ----------------

def main():
    ap = argparse.ArgumentParser(description=__doc__.splitlines()[0])
    ap.add_argument("cmd", choices=["model", "idle", "capture", "decode"])
    ap.add_argument("args", nargs="*")
    ap.add_argument("--secs", type=int, default=48)
    ap.add_argument("--sport", type=int, default=0)
    a = ap.parse_args()
    if a.cmd == "model":
        sport = a.sport or 44444
        for wan in (False, True):
            k = build_key(6, PHONE_IP, HOST_WAN_IP, sport, TEST_PORT, wan)
            print("build_key(is_wan=%d): %s" % (wan, fmt(k)))
    elif a.cmd == "idle":
        n = int(a.args[0]) if a.args else 8
        for k in burst(n, 1):
            print(fmt(list(k)))
    elif a.cmd == "decode":
        print(fmt([int(x, 16) for x in a.args]))
    elif a.cmd == "capture":
        capture(a.secs)


if __name__ == "__main__":
    main()
