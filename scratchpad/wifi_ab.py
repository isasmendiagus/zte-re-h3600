#!/usr/bin/env python3
# Phase-C R1 validation A/B: one run = set ftwifi, phone HTTP GET dur s,
# (repo home: scratchpad/wifi_ab.py — the Phase-C WiFi DN A/B harness, see findings/wifi_stage3_phaseC_R1_validation_2026-07-25.md)
# slow-paced counter snapshots pre/post (ab_ctrs pacing — console-safe),
# stats-node idm/dispatch counters, dmesg install lines, restore ftwifi=0.
# Usage: ab_run.py <label> <ftwifi 0|1> [dur]
import sys, time, re, subprocess, threading
sys.path.insert(0, str(__import__("pathlib").Path(__file__).resolve().parent))
import ab_ctrs

label, ftw = sys.argv[1], sys.argv[2]
dur = int(sys.argv[3]) if len(sys.argv) > 3 else 40

CTRS = list(ab_ctrs.CTRS) + [("cla_dn_fwd", 0x9238c3cc)]

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
        'busybox grep -E "idm_rx_count|idm_rx_per_ssid" /sys/kernel/debug/zx_eth/stats',
        'busybox grep -aE "rx_dispatched|tm_rx_fabric" /sys/kernel/debug/zx_eth/wifi_bind'], wait=3)
    v = {}
    m = re.search(r"idm_rx_count\s*=\s*(\d+)", out); v["idm_rx_count"] = int(m.group(1)) if m else None
    m = re.search(r"idm_rx_per_ssid 0\.\.7 = ((?:\d+ ?)+)", out)
    v["idm_rx_ssid4"] = int(m.group(1).split()[4]) if m else None
    m = re.search(r"rx_dispatched=(\d+) rx_nobind=(\d+) tx_injected=(\d+)", out)
    if m: v["rx_dispatched"], v["rx_nobind"], v["tx_injected"] = map(int, m.groups())
    m = re.search(r"tm_rx_fabric=(\d+) tm_rx_dispatched=(\d+)", out)
    if m: v["tm_rx_fabric"], v["tm_rx_dispatched"] = map(int, m.groups())
    return v

def snap(tag):
    p = rd_pokes(); s = rd_stats(); p.update(s)
    print("== SNAP %s %s ==" % (label, tag))
    print("  " + " ".join("%s=%s" % (k, x if x is not None else "?") for k, x in p.items()))
    return p

print(ab_ctrs.zc(["echo %s > /sys/kernel/debug/zx_eth/ftwifi; cat /sys/kernel/debug/zx_eth/ftwifi" % ftw], wait=2)[-40:])
a = snap("PRE")

result = {}
def dl():
    t0 = time.time()
    p = subprocess.run(["adb", "shell",
        'echo -e "GET /big.bin HTTP/1.0\\r\\nHost: x\\r\\n\\r\\n" | toybox timeout %d toybox nc 10.44.66.133 8080 | toybox wc -c' % dur],
        capture_output=True, text=True, timeout=dur + 25)
    result["bytes"] = p.stdout.strip()
    result["secs"] = time.time() - t0

t = threading.Thread(target=dl); t.start()
t.join()
time.sleep(3)
b = snap("POST")

try:
    nbytes = int(result["bytes"])
    print("== DL %s: %d bytes in %.0f s = %.2f MB/s" % (label, nbytes, result["secs"], nbytes / result["secs"] / 1e6))
except Exception:
    print("== DL %s: bytes=%r" % (label, result.get("bytes")))

print("== DELTAS %s ==" % label)
for k in a:
    if a.get(k) is not None and b.get(k) is not None and b[k] != a[k]:
        print("  %-16s +%d" % (k, (b[k] - a[k]) & 0xffffffff))

if ftw == "1":
    out = ab_ctrs.zc(['dmesg | busybox grep -aE "phaseC/ft|phase6/ft" | busybox tail -4'], wait=3)
    i = out.find("[phase")
    print(out[i:i + 600] if i >= 0 else out[-300:])
print(ab_ctrs.zc(["echo 0 > /sys/kernel/debug/zx_eth/ftwifi"], wait=2)[-30:])
