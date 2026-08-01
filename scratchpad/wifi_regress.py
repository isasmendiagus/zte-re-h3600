#!/usr/bin/env python3
"""
scratchpad/wifi_regress.py -- traffic-free WiFi hardening Tier 1 tests.

9 white-box, traffic-free tests for the WiFi offload debugfs surface
(zx_wifi_bind / zx_stats / ftwifi).  No AP/client/rig needed -- just the UART
bridge REPL (127.0.0.1:9999 via scratchpad/ctr.py) and a booted mainline
kernel with zx_eth.ko loaded.

Each test mounts proc + debugfs itself (idempotent minimal init), reads from
or writes to debugfs nodes under /sys/kernel/debug/zx_eth/, and returns a
TestResult.  The bottom-of-file main() runs all 9 and prints a pass/fail table.

Usage:
  wifi_regress.py             # run all 9 tests, print table
  wifi_regress.py --list      # list test names + descriptions
"""

import re
import sys
import time
from collections import namedtuple
from pathlib import Path

sys.path.insert(0, str(Path(__file__).resolve().parent))
import ctr

TestResult = namedtuple("TestResult", "name status duration notes")

WIFI_BIND = "/sys/kernel/debug/zx_eth/wifi_bind"
FTWIFI    = "/sys/kernel/debug/zx_eth/ftwifi"
STATS     = "/sys/kernel/debug/zx_eth/stats"

_MOUNT_CMDS = [
    "mkdir -p /proc /sys/kernel/debug 2>/dev/null",
    "mount -t proc none /proc 2>/dev/null",
    "mount -t debugfs none /sys/kernel/debug 2>/dev/null",
]


def dev(cmds, wait=3.0):
    """Single REPL round-trip: mount preamble + user commands, parse output."""
    return ctr.zc(_MOUNT_CMDS + list(cmds), wait=wait)


# ---------------------------------------------------------------------------
# helpers
# ---------------------------------------------------------------------------
def _exit_code(out):
    """Parse the REPL's [exit=N] trailer."""
    m = re.search(r"^\[exit=(-?\d+)\]", out, re.M)
    return int(m.group(1)) if m else None


def _bind_dmesg_rc(out):
    """Parse wifi_bind dmesg line for the return code (e.g. '= 0' or '= -16')."""
    m = re.search(r"wifi_bind:.*=\s*(-?\d+)", out)
    return int(m.group(1)) if m else None


def _dev_cmds_with_dmesg_tail(write_cmds, grep_pat, read_cmds=(), tail=8, wait=4.0):
    """Write, then dmesg|grep|tail + optional read commands, one round-trip."""
    cmds = list(write_cmds)
    if read_cmds:
        cmds.extend(read_cmds)
    cmds.append("dmesg | busybox grep -a '%s' | busybox tail -%d" % (grep_pat, tail))
    return dev(cmds, wait=wait)


# ---------------------------------------------------------------------------
# 1. wifi_bind_smoke
# ---------------------------------------------------------------------------
def test_wifi_bind_smoke():
    t0 = time.time()
    out = _dev_cmds_with_dmesg_tail(
        ["echo 'wlan1 1 4' > %s" % WIFI_BIND],
        "wifi_bind",
        ["cat %s" % WIFI_BIND],
    )
    in_table = "wlan1" in out and "idm1" in out
    rc = _bind_dmesg_rc(out)
    ok = in_table and rc == 0
    return TestResult(
        "wifi_bind_smoke",
        "PASS" if ok else "FAIL", time.time() - t0,
        "" if ok else "wlan1 not in table or rc=%s" % rc,
    )


# ---------------------------------------------------------------------------
# 2. wifi_unbind
# ---------------------------------------------------------------------------
def test_wifi_unbind():
    t0 = time.time()
    _dev_cmds_with_dmesg_tail(
        ["echo 'wlan1 1 4' > %s" % WIFI_BIND],
        "wifi_bind",
        wait=2.5,
    )
    out = _dev_cmds_with_dmesg_tail(
        ["echo 'del 1 4' > %s" % WIFI_BIND],
        "wifi_bind",
        ["cat %s" % WIFI_BIND],
    )
    in_table = "wlan1" in out
    rc = _bind_dmesg_rc(out)
    ok = not in_table and rc == 0
    return TestResult(
        "wifi_unbind",
        "PASS" if ok else "FAIL", time.time() - t0,
        "" if ok else "wlan1 still in table or rc=%s" % rc,
    )


# ---------------------------------------------------------------------------
# 3. wifi_rebind
# ---------------------------------------------------------------------------
def test_wifi_rebind():
    t0 = time.time()
    out = dev([
        "echo 'del 1 4' > %s" % WIFI_BIND,
        "cat %s" % WIFI_BIND,
        "echo 'wlan1 1 4' > %s" % WIFI_BIND,
        "cat %s" % WIFI_BIND,
        "dmesg | busybox grep -a 'wifi_bind' | busybox tail -4",
    ], wait=6.0)

    sections = out.split("echo 'wlan1 1 4'")
    before = sections[0] if len(sections) > 1 else ""
    after  = sections[-1] if len(sections) > 1 else out

    gook = "wlan1" not in before
    bok  = "wlan1" in after
    del_rc = _bind_dmesg_rc(out)
    add_rc = None
    for m in re.finditer(r"wifi_bind:.*=\s*(-?\d+)", out):
        add_rc = int(m.group(1))
    ok = gook and bok and del_rc == 0 and add_rc == 0

    notes = []
    if not gook: notes.append("unbind did not remove wlan1")
    if not bok:  notes.append("rebind did not restore wlan1")
    if del_rc != 0: notes.append("del rc=%s" % del_rc)
    if add_rc != 0: notes.append("bind rc=%s" % add_rc)

    return TestResult(
        "wifi_rebind",
        "PASS" if ok else "FAIL", time.time() - t0,
        "; ".join(notes),
    )


# ---------------------------------------------------------------------------
# 4. wifi_bind_invalid
# ---------------------------------------------------------------------------
def test_wifi_bind_invalid():
    t0 = time.time()
    out = dev(["echo 'nonexist 0 0' > %s" % WIFI_BIND], wait=3.0)
    ec = _exit_code(out)
    ok = ec is not None and ec != 0
    return TestResult(
        "wifi_bind_invalid",
        "PASS" if ok else "FAIL", time.time() - t0,
        "" if ok else "exit=%s, expected nonzero" % ec,
    )


# ---------------------------------------------------------------------------
# 5. wifi_bind_overflow
# ---------------------------------------------------------------------------
def test_wifi_bind_overflow():
    """Fill all 16 (idm,ssid) slots with dummy vifs; verify 17th fails."""
    t0 = time.time()
    notes = []
    slots = [(i // 8, i % 8) for i in range(16)]   # (idm, ssid) 0..15

    # try creating 17 dummy vifs; skip on failure
    create_cmds = []
    for i in range(17):
        create_cmds.append("ip link add dum%d type dummy 2>&1" % i)
        create_cmds.append("ip link set dum%d up 2>/dev/null" % i)
    create_out = dev(create_cmds, wait=8.0)

    dum_up = sum(1 for ln in create_out.splitlines()
                 if "Cannot find device" not in ln
                 and "Usage:" not in ln
                 and "dum" in ln)
    if dum_up < 4:
        cleanup = ["ip link del dum%d 2>/dev/null" % i for i in range(17)]
        dev(cleanup, wait=3.0)
        return TestResult("wifi_bind_overflow", "SKIP", time.time() - t0,
                          "dummy interfaces not available (dum_up=%d) -- CONFIG_DUMMY?" % dum_up)

    # bind 16 unique (idm,ssid) pairs
    n_bound = 0
    for i, (idm, ssid) in enumerate(slots):
        out = _dev_cmds_with_dmesg_tail(
            ["echo 'dum%d %d %d' > %s" % (i, idm, ssid, WIFI_BIND)],
            "wifi_bind",
            tail=3, wait=2.5,
        )
        rc = _bind_dmesg_rc(out)
        if rc == 0:
            n_bound += 1
        else:
            notes.append("bind %d (dum%d idm%d ssid%d) rc=%d" % (i, i, idm, ssid, rc))

    # 17th bind must fail (no free slot)
    out17 = _dev_cmds_with_dmesg_tail(
        ["echo 'dum16 2 2' > %s" % WIFI_BIND],
        "wifi_bind",
        wait=2.5,
    )
    rc17 = _bind_dmesg_rc(out17)
    over_ok = rc17 is not None and rc17 < 0

    if not over_ok:
        notes.append("17th bind unexpectedly succeeded (rc=%s)" % rc17)

    # cleanup: unbind all 16 + delete dummies
    cleanup = []
    for idm, ssid in slots:
        cleanup.append("echo 'del %d %d' > %s" % (idm, ssid, WIFI_BIND))
    cleanup += ["ip link del dum%d 2>/dev/null" % i for i in range(17)]
    dev(cleanup, wait=6.0)

    ok = n_bound == 16 and over_ok and len(notes) == 0
    if n_bound < 16:
        notes.append("only %d/16 slots bound (duplicate idm/ssid or vif busy)" % n_bound)

    return TestResult(
        "wifi_bind_overflow",
        "PASS" if ok else "FAIL", time.time() - t0,
        "; ".join(notes),
    )


# ---------------------------------------------------------------------------
# 6. wifi_tx_injected_sanity
# ---------------------------------------------------------------------------
def test_wifi_tx_injected_sanity():
    t0 = time.time()
    out = dev(["cat %s" % WIFI_BIND], wait=3.0)
    m = re.search(r"tx_injected=(\d+)", out)
    ok = m is not None and int(m.group(1)) >= 0
    return TestResult(
        "wifi_tx_injected_sanity",
        "PASS" if ok else "FAIL", time.time() - t0,
        "" if ok else "tx_injected absent or negative",
    )


# ---------------------------------------------------------------------------
# 7. wifi_default_ftwifi_1
# ---------------------------------------------------------------------------
def test_wifi_default_ftwifi_1():
    t0 = time.time()
    out = dev(["cat %s" % FTWIFI], wait=3.0)
    m = re.search(r"(\d+)", out)
    v = int(m.group(1)) if m else None
    ok = v == 1
    return TestResult(
        "wifi_default_ftwifi_1",
        "PASS" if ok else "FAIL", time.time() - t0,
        "" if ok else "ftwifi=%s, expected 1 (default ON since wedge fix)" % v,
    )


# ---------------------------------------------------------------------------
# 8. wifi_counters_sanity
# ---------------------------------------------------------------------------
def test_wifi_counters_sanity():
    t0 = time.time()
    out = dev([
        "cat %s" % STATS,
        "cat %s" % WIFI_BIND,
    ], wait=4.0)

    required = [
        "ft_pm_verify", "idm_rx_count",
        "rx_dispatched", "rx_nobind", "tx_injected",
        "sw_tx_pending",
    ]
    missing = [f for f in required if f not in out]
    ok = len(missing) == 0
    return TestResult(
        "wifi_counters_sanity",
        "PASS" if ok else "FAIL", time.time() - t0,
        "" if ok else "missing: %s" % ", ".join(missing),
    )


# ---------------------------------------------------------------------------
# 9. wifi_pm_write_verify
# ---------------------------------------------------------------------------
def test_wifi_pm_write_verify():
    t0 = time.time()
    out = dev(["cat %s" % STATS], wait=3.0)
    m = re.search(r"ft_pm_verify\s*=\s*ok=(\d+)\s+retry=(\d+)\s+fail=(\d+)", out)
    if not m:
        return TestResult(
            "wifi_pm_write_verify", "FAIL", time.time() - t0,
            "ft_pm_verify line not found in stats",
        )
    fail = int(m.group(3))
    ok = fail == 0
    return TestResult(
        "wifi_pm_write_verify",
        "PASS" if ok else "FAIL", time.time() - t0,
        "" if ok else "ft_pm_verify_fail=%d, expected 0" % fail,
    )


# ---------------------------------------------------------------------------
# registry + runner
# ---------------------------------------------------------------------------
_TESTS = [
    ("wifi_bind_smoke", "echo 'wlan1 1 4' -> bind verified in table", test_wifi_bind_smoke),
    ("wifi_unbind", "echo 'del 1 4' -> node gone", test_wifi_unbind),
    ("wifi_rebind", "unbind then rebind, both succeed", test_wifi_rebind),
    ("wifi_bind_invalid", "bind nonexistent ifname -> exit != 0", test_wifi_bind_invalid),
    ("wifi_bind_overflow", "fill 16 slots, 17th fails, cleanup", test_wifi_bind_overflow),
    ("wifi_tx_injected_sanity", "tx_injected present and >= 0", test_wifi_tx_injected_sanity),
    ("wifi_default_ftwifi_1", "ftwifi defaults to 1 (ON since wedge fix)", test_wifi_default_ftwifi_1),
    ("wifi_counters_sanity", "required fields in stats + wifi_bind", test_wifi_counters_sanity),
    ("wifi_pm_write_verify", "ft_pm_verify_fail == 0", test_wifi_pm_write_verify),
]


def main():
    if len(sys.argv) > 1 and sys.argv[1] == "--list":
        w = max(len(n) for n, _, _ in _TESTS)
        for n, d, _ in _TESTS:
            print("  %-*s  %s" % (w, n, d))
        return 0

    results = []
    for name, desc, fn in _TESTS:
        print("--- %s ---" % name)
        r = fn()
        print("  -> %-5s  %.1fs  %s" % (r.status, r.duration, r.notes or ""))
        results.append(r)

    print("\n=== WIFI REGRESSION SUMMARY ===")
    w = max(len(r.name) for r in results)
    status_width = max(len(r.status) for r in results)
    for r in results:
        print("  %-*s  %-*s  %6.1fs  %s" %
              (w, r.name, status_width, r.status, r.duration, r.notes or ""))
    n_pass = sum(1 for r in results if r.status == "PASS")
    n_fail = sum(1 for r in results if r.status in ("FAIL", "ERROR"))
    n_skip = sum(1 for r in results if r.status == "SKIP")
    verdict = "FAIL" if n_fail else "PASS"
    print("\n  TOTAL: %d pass / %d fail / %d skip  ->  OVERALL: %s" %
          (n_pass, n_fail, n_skip, verdict))
    return 1 if n_fail else 0


if __name__ == "__main__":
    sys.exit(main())
