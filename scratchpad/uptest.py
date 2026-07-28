#!/usr/bin/env python3
"""One-shot WiFi UP-offload discrimination test (Stage-3 UP fix, 2026-07-28).

Per run: fresh phone->host push flow, wait for the production hardfast install,
optionally modify CLA state (fill520 / per-slot rewrite with field variants),
then measure 25 s of {sink throughput, tx_injected, cla_acl_fail, cla_up_fwd,
qmg_up_*} to tell HIT from MISS for fabric-ingress (WiFi UP) frames.

Modes:
  asis          no modification (baseline: entry only at its own 6 slots)
  fill          fill520 with the flow's exact entry (as the driver packs it)
  fill_dk0      fill520, entry w4 da_known=0 (keep direct)      -> 0x06000067
  fill_nodadir  fill520, entry w4 da_known=0 direct=0           -> 0x06000047
  slots_dk0     rewrite only the flow's own 6 slots, w4 da_known=0
Cleanup: fill520 zeros + kill the phone nc (each run uses a NEW connection).
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
PHONE_IP = "192.168.50.10"
TEST_PORT = 9099

CTRS = [
    ("qmg_up_sw",   0x9234c054), ("qmg_up_hw",   0x9234c058),
    ("qmg_up_trap", 0x9234c05c), ("qmg_dn_hw",   0x9234c048),
    ("cla_up_fwd",  0x9238c3c0), ("cla_acl_fail", 0x9238c3c4),
]


def ip2u32(ip):
    a, b, c, d = (int(x) for x in ip.split("."))
    return (a << 24) | (b << 16) | (c << 8) | d


def pack_cla(proto, sip, dip, sp, dp, flow_id, eg_regport=5, key_hdr=0x38,
             w4_override=None, w3=0):
    """Byte-exact mirror of zx_ft_pack_cla (UP direction: up_idx_fix=1).
    w3: cla[3] override — carries the entry INPORT field
    (inport = (byte0x0e & 0x3f) << 6 | byte0x0d >> 2, zte-cla-ram-layout):
    inport v -> w3 = ((v & 0x3f) << 2) << 8 | ((v >> 6) & 0x3f) << 16.
    byte0xf MUST stay 0 (extr_index high nibble, the 2026-07-02 lesson)."""
    s, d = ip2u32(sip), ip2u32(dip)
    s0, s1, s2, s3 = (s >> 24) & 0xff, (s >> 16) & 0xff, (s >> 8) & 0xff, s & 0xff
    d0, d1, d2, d3 = (d >> 24) & 0xff, (d >> 16) & 0xff, (d >> 8) & 0xff, d & 0xff
    idx_lo = ((flow_id & 0x7f) << 1) | 1
    idx_hi = (flow_id >> 7) & 0xff
    cla = [0] * 15
    cla[0] = (idx_lo << 24) | 0x000044 | ((eg_regport & 0xf) << 12) | \
             (((eg_regport >> 4) & 0xff) << 16)
    cla[1] = (0xfa << 24) | (0x11 << 16) | (0xc0 << 8) | idx_hi
    cla[2] = 0x00000608
    cla[3] = w3
    cla[4] = (proto << 24) | (0x00100060 | (key_hdr >> 3))
    if w4_override is not None:
        cla[4] = (proto << 24) | w4_override
    cla[5] = (s3 << 24) | (s0 << 16) | (s1 << 8)
    cla[6] = (d3 << 24) | (d0 << 16) | (d1 << 8) | s2
    cla[7] = ((dp & 0xff) << 24) | ((sp >> 8) << 16) | ((sp & 0xff) << 8) | d2
    cla[8] = (dp >> 8) & 0xff
    return cla


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


class Sink(threading.Thread):
    def __init__(self):
        super().__init__(daemon=True)
        self.sock = socket.socket()
        self.sock.setsockopt(socket.SOL_SOCKET, socket.SO_REUSEADDR, 1)
        self.sock.bind((HOST_WAN_IP, TEST_PORT))
        self.sock.listen(2)
        self.sock.settimeout(25)
        self.rx = 0

    def run(self):
        try:
            c, _ = self.sock.accept()
        except OSError:
            return
        while True:
            try:
                d = c.recv(65536)
            except OSError:
                return
            if not d:
                return
            self.rx += len(d)


def main():
    mode = sys.argv[1]
    dur = int(sys.argv[2]) if len(sys.argv) > 2 else 25

    subprocess.run(["adb", "shell", "pkill -f 'toybox nc' 2>/dev/null || true"],
                   timeout=15)
    sink = Sink()
    sink.start()
    ph = subprocess.Popen(
        ["adb", "shell", "toybox nc %s %d < /dev/zero" % (HOST_WAN_IP, TEST_PORT)],
        stdout=subprocess.DEVNULL, stderr=subprocess.DEVNULL)
    time.sleep(6)  # connect + hardfast install + streaming

    out = ab_ctrs.zc(
        ["dmesg | busybox grep -a 'recipe: proto=6 192.168.50.10' | busybox tail -1",
         "dmesg | busybox grep -a 'WIFI-UP poly-0' | busybox tail -1"], wait=3)
    m = re.search(r"192\.168\.50\.10:(\d+)->10\.44\.66\.133:9099 .*pm_slot=(\d+).*raw=0x([0-9a-f]+) "
                  r"buckets ram2\[0x([0-9a-f]+)\]/3\[0x([0-9a-f]+)\]/4\[0x([0-9a-f]+)\]"
                  r"/5\[0x([0-9a-f]+)\]/6\[0x([0-9a-f]+)\]", out)
    m0 = re.search(r"raw0=0x([0-9a-f]+) ram2\[0x([0-9a-f]+)\]", out)
    if not m:
        print("!! no UP install line found — flow not offloaded?")
        print(out[-500:])
        ph.kill()
        return
    sp, pm_slot = int(m.group(1)), int(m.group(2))
    raw = int(m.group(3), 16)
    ways = [(2, int(m.group(4), 16)), (3, int(m.group(5), 16)),
            (4, int(m.group(6), 16)), (5, int(m.group(7), 16)),
            (6, int(m.group(8), 16))]
    raw0 = int(m0.group(1), 16) if m0 else None
    print("== flow sport=%d pm_slot=%d raw=0x%04x raw0=%s ways=%s ==" %
          (sp, pm_slot, raw, ("0x%04x" % raw0) if raw0 else "?", ways))

    entry = pack_cla(6, PHONE_IP, HOST_WAN_IP, sp, TEST_PORT, pm_slot)
    if mode.startswith("fill"):
        # fill / fill_dk0 / fill_nodadir / fill_ip<hex inport> (+ _dk0)
        w4o = None
        m_w4 = re.search(r"_w4([0-9a-f]+)", mode)
        if m_w4:
            w4o = int(m_w4.group(1), 16)
        elif "_nodadir" in mode:
            w4o = 0x00000047
        elif "_dk0" in mode:
            w4o = 0x00000067
        w3 = 0
        m_ip = re.search(r"_ip([0-9a-f]+)", mode)
        if m_ip:
            v = int(m_ip.group(1), 16)
            w3 = (((v & 0x3f) << 2) << 8) | (((v >> 6) & 0x3f) << 16)
        entry = pack_cla(6, PHONE_IP, HOST_WAN_IP, sp, TEST_PORT, pm_slot,
                         w4_override=w4o, w3=w3)
        words = " ".join("%x" % w for w in entry)
        out = ab_ctrs.zc(["echo '%s' > /sys/kernel/debug/zx_eth/fill520" % words,
                          "dmesg | busybox grep -a fill520 | busybox tail -1"],
                         wait=4)
        print("== %s applied ==" % mode)
        print("\n".join(out.splitlines()[-3:]))
    elif mode == "slots_dk0":
        entry = pack_cla(6, PHONE_IP, HOST_WAN_IP, sp, TEST_PORT, pm_slot,
                         w4_override=0x00000067)
        words = " ".join("%x" % w for w in entry)
        slots = ways + ([(2, raw0 & 0xff)] if raw0 is not None else [])
        cmds = []
        for ram, addr in slots:  # clawrite quirk: write twice
            cmds += ["echo '%x %x %s' > /sys/kernel/debug/zx_eth/clawrite" %
                     (ram, addr, words)] * 2
        out = ab_ctrs.zc(cmds, wait=4)
        print("== slots_dk0 applied to %s ==" % slots)
    elif mode != "asis":
        sys.exit("unknown mode %r" % mode)

    pre = rd()
    r0 = sink.rx
    t0 = time.time()
    time.sleep(dur)
    el = time.time() - t0
    got = sink.rx - r0
    post = rd()
    ph.kill()
    subprocess.run(["adb", "shell", "pkill -f 'toybox nc' 2>/dev/null || true"],
                   timeout=15)

    print("== %s RESULT: %.2f MB/s over %.0fs ==" % (mode, got / el / 1e6, el))
    for k, _ in CTRS + [("tx_injected", 0)]:
        a, b = pre.get(k), post.get(k)
        if a is not None and b is not None:
            print("   d%-13s = %d" % (k, b - a))
    inj = (post.get("tx_injected") or 0) - (pre.get("tx_injected") or 0)
    miss = (post.get("cla_acl_fail") or 0) - (pre.get("cla_acl_fail") or 0)
    print("   VERDICT: %s" % ("NO-INJ" if inj == 0 else
          "MISS" if miss >= inj * 0.8 else "HIT (miss %d / inj %d)" % (miss, inj)))

    if mode.startswith("fill") :
        ab_ctrs.zc(["echo '0 0 0 0 0 0 0 0 0 0 0 0 0 0 0' > /sys/kernel/debug/zx_eth/fill520"],
                   wait=4)
        print("== fill520 zeroed ==")


if __name__ == "__main__":
    main()
