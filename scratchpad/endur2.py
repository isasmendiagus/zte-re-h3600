#!/usr/bin/env python3
"""Post-fix wedge endurance (2026-07-31): throttled CONTINUOUS fabric-ingress
flow to a target injected-frame count, with the modem-flake discriminator
built in (the plain endur's burst harness false-alarmed on the known
modem-AP wire->WiFi post-storm outage).

- Throttled ~1 MB/s single flow (boot-D shape, the shape that wedged at
  19.6k-71.8k pre-fix) so the modem WiFi leg doesn't collapse under storm.
- Health loop samples lite_sample (incl. BMU ledger al/rl + bp cursors).
- On stall: discriminate via delta qmg_dn_trap under host->lan4 ping
  (frozen => TRUE WEDGE -> wedgecap + exit; moving => modem flake -> wait
  for self-heal, restart the flow, keep counting).
Usage: endur2.py [target_frames] (default 200000)
"""
import subprocess
import sys
import time
from pathlib import Path

sys.path.insert(0, str(Path(__file__).resolve().parent))
import ab_ctrs  # noqa: E402
import wedge_probe as wp  # noqa: E402

DEVICE_WAN_IP = "10.44.66.223"


def dn_trap():
    v = ab_ctrs.read()
    return v.get("qmg_dn_trap")


def true_wedge_probe():
    """Returns True if the box is REALLY wedged (dn_trap frozen under ping)."""
    a = dn_trap()
    subprocess.run(["ping", "-c5", "-W1", DEVICE_WAN_IP],
                   stdout=subprocess.DEVNULL, stderr=subprocess.DEVNULL)
    b = dn_trap()
    print("   [discriminator] qmg_dn_trap %s -> %s under 5 host pings" %
          (wp.hx(a), wp.hx(b)))
    sys.stdout.flush()
    return a is not None and b is not None and a == b


def main(target=200000):
    sink = wp.Sink()
    sink.start()
    flow = wp._flow_start(sink, rate_kbps=1000)
    print("=== endur2: continuous throttled flow, target %d frames ===" % target)
    time.sleep(15)
    prev = wp.lite_sample()
    print("start inj=%s" % prev.get("tx_injected"))
    stall_since = None
    flakes = 0
    n = 0
    while True:
        n += 1
        got, dinj, dfwd, dmiss, cur = wp._flow_health(sink, 15)
        al, rl = cur.get("bmu_al"), cur.get("bmu_rl")
        print("-- r%d: %.2f MB dinj=%d dfwd=%s dmiss=%s inj=%s | ledger d=%s "
              "bp0=%s" % (n, got / 1e6, dinj, dfwd, dmiss,
                          cur.get("tx_injected"),
                          (al - rl) if al is not None and rl is not None
                          else "?",
                          wp.hx(cur.get("bp0"))))
        sys.stdout.flush()
        if (cur.get("tx_injected") or 0) >= target:
            print("=== ENDURANCE PASSED: inj=%s >= %d, no wedge ==="
                  % (cur.get("tx_injected"), target))
            flow.kill()
            return 0
        if got < 5e4:  # stalled window
            if true_wedge_probe():
                print("!!!! TRUE WEDGE (dn_trap frozen) at inj=%s !!!!"
                      % cur.get("tx_injected"))
                wp.wedgecap()
                flow.kill()
                return 2
            flakes += 1
            if stall_since is None:
                stall_since = time.time()
            print("   modem flake #%d (%.0fs in this stall) — waiting for "
                  "self-heal" % (flakes, time.time() - stall_since))
            sys.stdout.flush()
            if time.time() - stall_since > 300:
                # restart the flow (TCP may have died for good)
                print("   stall > 5 min: restarting the flow")
                flow.kill()
                subprocess.run(["adb", "shell",
                                "pkill -f 'toybox nc' 2>/dev/null || true"],
                               stdout=subprocess.DEVNULL,
                               stderr=subprocess.DEVNULL, timeout=15)
                time.sleep(3)
                flow = wp._flow_start(sink, rate_kbps=1000)
                stall_since = None
            time.sleep(10)
        else:
            stall_since = None
        prev = cur


if __name__ == "__main__":
    sys.exit(main(int(sys.argv[1]) if len(sys.argv) > 1 else 200000))
