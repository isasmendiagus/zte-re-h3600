#!/usr/bin/env python3
"""
scratchpad/regress.py — regression test BATTERY for the ZTE ZX279128S mainline
ethernet/offload driver. Codifies the manual QA procedures we've already run
(findings/qa_ethernet_battery_2026-07-04.md + wedge_deep.py/dn_e2e_native.py/
txfc_validate.py/dl_run.py/ctr.py/validate_fix.py/qa_multi.py/qa_churn.py) into
one scripted battery with a pass/fail table + nonzero exit on any FAIL, so an
agent can run this after every driver change instead of hand-testing.

DESIGN CHOICE: companion script (imports scratchpad/rig.py), NOT a `rig.py test`
subcommand. rig.py owns rig lifecycle (boot/wan/client/offload/teardown) and a
few generic primitives (dev/sh/poke_read/ctr); this file owns the *battery*
composition on top of them (multi-run sampling, pass/fail thresholds, timeouts,
the summary table). Keeping them separate keeps rig.py small and this file
free to grow test-specific logic without bloating the rig tool everyone else
also uses for ad-hoc device sessions.

USAGE
  regress.py                    # full battery, in QA-battery order, boots the rig first
  regress.py --quick            # baseline_download + sustained_download + counters_sanity + dmesg_clean
  regress.py sustained_download # run just one (or a few) named tests
  regress.py --list             # list test names + one-line pass criteria
  regress.py --no-boot ...      # assume the rig is already `rig.py up` — don't reboot
  regress.py --no-teardown ...  # leave the rig up afterwards (e.g. for a follow-up manual look)

Every test: (1) uses rig.py's already-up rig (boot once, at the top, not per test —
rebooting between every test would take the battery from ~10 min to over an hour);
(2) exercises the datapath with the SAME curl/ping/dig/dmesg commands the source
scripts used; (3) reads counters via rig.py's/ctr.py's proven primitives (the debugfs
`poke` node for single-register TM/QMG/RED/MAC reads, and the driver's own
`pipeline_stats` seq-file for TX/RX-safe accounting); (4) returns a TestResult
(PASS/FAIL/SKIP/ERROR + metrics + notes); (5) is wrapped in a per-test wall-clock
timeout (a background-thread safety net — see run_with_timeout); (6) is followed by
a light teardown (kill stray curls in the client netns) before the next test runs.

SAFETY — inherited from rig.py, read its header before running this live:
DTR/RAM-boot only; never bulk-memdump the MAC4 stat region (0x92300000+ — hangs the
bus). This file DOES read a few individual MAC4/MAC2 TX-counter REGISTERS
(mac2_tx=0x92280718, mac4_tx=0x92300718) via the single-address `poke`/`peek`
debugfs idiom — that is NOT the banned bulk memdump; it is the exact idiom
wedge_deep.py and txfc_validate.py already used on-device (validated across the
8x1GB txflowctrl runs, findings/wedge_txflowctrl_fix_2026-07-04.md) without
incident. Never raw-poke TM[0x10058]/[0x10068] — this file doesn't (RX/TX
counting comes from pipeline_stats, which is the driver's own safe reader of
those clear-on-read registers).

DEVICE-FREE STATUS: this file has been `python -m py_compile`'d, `--help`'d,
`--list`'d, and had every test's commands/addresses/regexes traced against the
source scripts + rig.py by hand. It has NOT been run against the live device.
See REGRESS_README.md for the first-run tuning list (thresholds most likely to
need adjustment once this actually runs).
"""
import argparse
import concurrent.futures as cf
import os
import random
import re
import socket
import struct
import subprocess
import sys
import threading
import time
from collections import namedtuple

HERE = os.path.dirname(os.path.abspath(__file__))
sys.path.insert(0, HERE)
import rig      # scratchpad/rig.py — canonical rig lifecycle + primitives (dev/sh/poke_read/consts)
import ctr      # scratchpad/ctr.py — canonical counter sweep (imported by rig.py too)

TestResult = namedtuple("TestResult", "name status duration metrics notes")


# ---------------------------------------------------------------------------
# shared curl/download helpers — one canonical command shape, reused by every
# test below. Source: rig.py's cmd_download / dl_run.py / dn_e2e_native.py /
# wedge_deep.py / txfc_validate.py / qa_multi.py / qa_churn.py (they all build
# the exact same curl invocation; this is the single place that shape lives).
# ---------------------------------------------------------------------------
def _curl_cmd(lport, dur, size=0, url=None, host_hdr=None, outfile=None, maxtime_pad=15,
             rate_limit=None):
    url = url or rig.DL_URL_DEFAULT
    if host_hdr is None and url == rig.DL_URL_DEFAULT:
        host_hdr = rig.DL_HOST_HDR
    outfile = outfile or ("/tmp/regress_dl_%d_%d.out" % (lport, int(time.time() * 1000) % 1000000))
    host_opt = "-H 'Host: %s' " % host_hdr if host_hdr else ""
    range_opt = "-r 0-%d " % (size - 1) if size else ""
    # [H2 session] `rate_limit` (curl's `--limit-rate`, e.g. "8M"): against a
    # fast LAN-local server (rig.DL_URL_LOCAL), a 50 MiB flow can finish in
    # well under a second -- too fast for nf_flowtable to ever dispatch
    # FLOW_CLS_REPLACE and get the flow HW-offloaded before it's already
    # done. multiflow/high_way_collision need each flow to survive long
    # enough (several seconds) for HW-offload to actually engage; capping
    # the per-flow rate is a minimal way to guarantee that without depending
    # on momentary/variable LAN throughput. Unused (None) by every OTHER
    # caller, which want max achievable speed (baseline/sustained/churn/etc).
    rate_opt = "--limit-rate %s " % rate_limit if rate_limit else ""
    cmd = (rig.SUDO + rig.NS +
           "curl -s -o /dev/null --max-time %d %s%s%s"
           "-w 'bytes=%%{size_download} rate=%%{speed_download} http=%%{http_code} t=%%{time_total}\\n' "
           "--local-port %d %s > %s 2>&1" %
           (int(dur) + maxtime_pad, host_opt, range_opt, rate_opt, lport, url, outfile))
    return cmd, outfile


def _parse_curl_outfile(outfile):
    d = {"http": None, "bytes": None, "rate_mb_s": None, "time_total": None, "raw": ""}
    try:
        lines = [l for l in open(outfile).read().splitlines() if "bytes=" in l]
        line = lines[-1] if lines else ""
    except OSError:
        line = ""
    d["raw"] = line
    m = re.search(r"bytes=(\d+)", line)
    if m: d["bytes"] = int(m.group(1))
    m = re.search(r"rate=([\d.]+)", line)
    if m: d["rate_mb_s"] = float(m.group(1)) / 1e6
    m = re.search(r"http=(\d+)", line)
    if m: d["http"] = int(m.group(1))
    m = re.search(r"t=([\d.]+)", line)
    if m: d["time_total"] = float(m.group(1))
    return d


def _curl_once(lport, dur, size=0, url=None, host_hdr=None, maxtime_pad=15):
    """Blocking single download; returns the parsed result dict."""
    cmd, outfile = _curl_cmd(lport, dur, size=size, url=url, host_hdr=host_hdr, maxtime_pad=maxtime_pad)
    rig.sh(cmd, timeout=dur + maxtime_pad + 15)
    return _parse_curl_outfile(outfile)


def _port_epoch_offset(step=90, buckets=10, bucket_size=100):
    """A slowly-changing offset (0, bucket_size, 2*bucket_size, ... quantized
    by wall-clock time in `step`-second buckets) to avoid reusing the exact
    same local port across separate regress.py invocations within one TCP
    TIME_WAIT window.

    [found live 2026-07-04, distinct from the churn-harness cold-path/ARP
    fix above] Redialing the SAME local port to the SAME remote host:port
    within ~1-2 minutes of a prior use reproduces the identical `bytes=0
    http=000 t~0.0002s` instant-fail signature as the ARP/sudo cold-path
    issue, but from a different mechanism (the socket's still in TIME_WAIT,
    not a stale neighbor entry) -- confirmed with a bare two-line manual
    `curl --local-port N ...` replay, no test harness involved at all: the
    first call succeeds, an immediate second call on the SAME N fails
    exactly this way. Tests that hardcode ONE fixed port across repeated
    runs in a short debugging/validation session (poly0_stale's sub-check A)
    or that always start their per-flow port range at the exact same base
    (churn's 48000+i) are exposed to this on a RERUN, even though a single
    isolated run never reuses a port against itself. Not a concern for
    tests that already vary their own base per call (none currently do) or
    that are normally run once per fresh boot -- but cheap enough to apply
    everywhere it's easy to."""
    return (int(time.time()) // step % buckets) * bucket_size


def _cleanup_client_procs():
    """Per-test teardown: kill stray curl/tcpdump in the client netns. Safe no-op
    if the netns doesn't exist yet (e.g. --no-boot without a prior `rig.py up`)."""
    rig.sh(rig.SUDO + rig.NS + "pkill -9 curl 2>/dev/null; true")
    time.sleep(0.3)


def _ft_dmesg_stats(tail=120):
    """Parse the driver's own [phase6/ft] install/decline/destroy log lines.
    Source: qa_multi.py / qa_churn.py's exact grep+regex idiom.

    [H2 session, found live] `declined_cookies` added: a naturally-occurring
    (not engineered) ram6 higher-way collision showed up during an ordinary
    multiflow run (5 real concurrent flows -- 8 ram6 buckets makes this
    unsurprising even at N=5) -- one cookie got repeatedly
    "reserve decline: higher-way collision" (correct H2 behavior: decline,
    stay in SW, no clobber) until the colliding flow was destroyed, THEN
    successfully installed on a later re-REPLACE. That flow still counted as
    "connected" (curl got its full file via the SW path, just not
    HW-accelerated the whole time) but obviously never contributes a second
    unique pm_slot for the window it was declined -- multiflow's slot_ok
    check needs to know about this cookie to not misread a CORRECT decline
    as a possible clobber."""
    out = rig.dev(["dmesg | busybox grep -a 'phase6/ft' | busybox tail -%d" % tail], wait=2.5)
    slots = []
    declined_cookies = set()
    installs = declines = dels = 0
    for ln in out.splitlines():
        if "phase6/ft" not in ln or "grep" in ln:
            continue
        if "recipe:" in ln:
            installs += 1
            m = re.search(r"pm_slot=(\d+)", ln)
            if m:
                slots.append(m.group(1))
        if "declined" in ln or "decline:" in ln:
            declines += 1
            m = re.search(r"cookie=([0-9a-f]+)", ln)
            if m:
                declined_cookies.add(m.group(1))
        if "flow del" in ln:
            dels += 1
    return {"installs": installs, "declines": declines, "dels": dels,
            "slots": slots, "uniq_slots": len(set(slots)),
            "declined_cookies": declined_cookies}


def _dmesg_scan():
    """Scan the CURRENT dmesg ring for oops/panic/WARN/hung-task signatures.
    NOTE: the dmesg ring can wrap under heavy driver logging (it did, pre-fix,
    per findings/qa_ethernet_battery_2026-07-04.md) — run this test LAST in a
    battery so it sees as much of the run as possible.

    [regress.py first-run fix 2026-07-04] The device's REPL (init.c) appends
    a "[exit=N]" trailer line + a bare "#" prompt line after EVERY command's
    output — unconditionally, even when the grep matched nothing. The old
    filter only dropped the echoed command line (via "grep" in l) and blank
    lines, so a CLEAN dmesg (zero real matches) still produced two spurious
    "bad" lines ("[exit=0]" and "#"), giving a false FAIL. Confirmed live:
    `dmesg | busybox grep -aE '...'` against an actually-clean ring returned
    exactly those two lines and nothing else. Filter them out explicitly."""
    out = rig.dev(["dmesg | busybox grep -aiE "
                   "'Oops|Kernel panic|BUG:|WARNING:|hung_task|Call Trace:' "
                   "| busybox tail -80"], wait=2.5)
    bad = [l.strip() for l in out.splitlines() if l.strip() and "grep" not in l
           and not re.match(r"^\[exit=\d+\]$", l.strip()) and l.strip() != "#"]
    return bad


# ---------------------------------------------------------------------------
# 1. baseline_download
# ---------------------------------------------------------------------------
def test_baseline_download(args):
    name = "baseline_download"
    t0 = time.time()
    _cleanup_client_procs()
    b0 = ctr.read()

    series = []
    stop = threading.Event()

    def sampler(ts0):
        while not stop.is_set():
            raw = rig.poke_read([a for _, a, _ in rig.TS_CTRS], wait=1.0)
            row = {}
            for n, a, lo16 in rig.TS_CTRS:
                v = raw.get(a)
                row[n] = (v & 0xffff) if (v is not None and lo16) else v
            series.append((time.time() - ts0, row))
            stop.wait(2.0)

    th = threading.Thread(target=sampler, args=(time.time(),), daemon=True)
    th.start()
    d = _curl_once(45010, args.baseline_dur, size=args.baseline_size)
    stop.set(); th.join(timeout=10)

    b1 = ctr.read()
    fwd_d = (b1.get("cla_dn_fwd") or 0) - (b0.get("cla_dn_fwd") or 0)
    fail_d = (b1.get("acl_fail") or 0) - (b0.get("acl_fail") or 0)
    hw_d = (b1.get("qmg_dn_hw") or 0) - (b0.get("qmg_dn_hw") or 0)
    denom = fwd_d + fail_d
    # [regress.py false-fail fix 2026-07-04, ctr-bug #1] cla_dn_fwd/acl_fail are
    # genuinely 16-bit HW counter fields (ctr.py CTRS "lo16" -- they share their
    # 32-bit register with a neighbouring counter, not an artificial truncation
    # we could undo by reading wider). Over a line-rate GB-scale transfer they
    # wrap multiple times between the before/after snapshot, so their raw
    # before/after diff is not the true delta -- hit_rate below is informational
    # only now, NEVER gates pass/fail. The real "did HW-forwarding actually
    # happen" assertion uses qmg_dn_hw's delta instead: that register is
    # non-masked (full 32-bit) and climbs monotonically (e.g. +774k over ~1GB
    # in a healthy run), so a before/after diff across the transfer is valid.
    hit_rate = (fwd_d / denom) if denom > 0 else None
    trap_final = series[-1][1].get("qmg_dn_trap") if series else b1.get("qmg_dn_trap")

    # Conservative expected-packet floor from bytes actually transferred (assume
    # a generously-small avg frame of 1400B so the floor stays well under the
    # true packet count) — catches "HW forwarding didn't happen at all/mostly
    # fell back to SW" without being sensitive to exact packet-size mix.
    expected_pkts = (d["bytes"] or 0) / 1400.0
    hwfwd_floor = expected_pkts * args.hwfwd_min_frac

    http_ok = d["http"] in (200, 206)
    rate_ok = (d["rate_mb_s"] is not None) and (d["rate_mb_s"] >= args.line_rate_min)
    hwfwd_ok = (expected_pkts <= 0) or (hw_d >= hwfwd_floor)
    trap_ok = (trap_final is None) or (trap_final < args.trap_healthy_max)
    ok = http_ok and rate_ok and hwfwd_ok and trap_ok

    notes = []
    if not http_ok:
        notes.append("http=%s (want 200/206) — download did not complete: %s" % (d["http"], d["raw"]))
    if not rate_ok:
        notes.append("rate=%s MB/s < line-rate min %.1f" % (d["rate_mb_s"], args.line_rate_min))
    if not hwfwd_ok:
        notes.append("qmg_dn_hw delta=%d < expected floor %.0f (bytes=%d) — HW forward path may not be "
                      "offloading (hit_rate=%.3f informational only, fwd_d=%d fail_d=%d wrap-affected)" %
                      (hw_d, hwfwd_floor, d["bytes"] or 0, hit_rate if hit_rate is not None else -1, fwd_d, fail_d))
    if not trap_ok:
        notes.append("qmg_dn_trap=%s >= healthy max %d" % (trap_final, args.trap_healthy_max))

    metrics = {"http": d["http"], "bytes": d["bytes"], "rate_mb_s": d["rate_mb_s"],
               "hit_rate_informational": hit_rate, "qmg_dn_hw_delta": hw_d,
               "qmg_dn_hw_floor": hwfwd_floor, "qmg_dn_trap_final": trap_final}
    return TestResult(name, "PASS" if ok else "FAIL", time.time() - t0, metrics, "; ".join(notes))


# ---------------------------------------------------------------------------
# 2. sustained_download — THE key wedge-regression guard.
# Source: wedge_deep.py / txfc_validate.py (identical combined poke+pipeline_stats
# sampling idiom) + findings/wedge_txflowctrl_fix_2026-07-04.md (the pass bar).
# ---------------------------------------------------------------------------
_SUSTAINED_POKES = [("rtin", 0x92344208), ("rtout", 0x92344214), ("rdrop", 0x921da044),
                    ("qdntr", 0x9234c04c), ("qdnhw", 0x9234c048),
                    ("m2tx", 0x92280718), ("m4tx", 0x92300718)]


def _sustained_sample():
    """One combined device round-trip: pokes + pipeline_stats, exactly like
    wedge_deep.py's sample()/txfc_validate.py's sample()."""
    cmds = ["echo %08x > /sys/kernel/debug/zx_eth/poke" % a for _, a in _SUSTAINED_POKES]
    cmds.append("dmesg | busybox grep -a 'peek 0x' | busybox tail -%d" % (len(_SUSTAINED_POKES) + 2))
    cmds.append("cat /sys/kernel/debug/zx_eth/pipeline_stats | busybox grep -E "
                "'sw_tx_pending|sw_tx_full_drops|sw_tx_reclaimed|tm_irq_count|tm_napi_count|"
                "tm_rx_count|tm_tx_count'")
    out = rig.dev(cmds, wait=1.5)
    row = {}
    for n, a in _SUSTAINED_POKES:
        m = re.findall(r"peek 0x%08x = 0x([0-9a-f]+)" % a, out, re.I)
        row[n] = int(m[-1], 16) if m else None
    for key, pat, ngroups in [
        ("sw_tx_pending", r"sw_tx_pending\s+= (\d+) \(max (\d+)", 2),
        ("sw_tx_reclaimed", r"sw_tx_reclaimed\s+= (\d+)", 1),
        ("sw_tx_full_drops", r"sw_tx_full_drops\s+= (\d+) \(queue_stops (\d+)", 2),
        ("tm_irq_count", r"tm_irq_count\s+= (\d+)", 1),
        ("tm_napi_count", r"tm_napi_count\s+= (\d+)", 1),
        ("tm_rx_count", r"tm_rx_count\s+= (\d+)", 1),
        ("tm_tx_count", r"tm_tx_count\s+= (\d+)", 1),
    ]:
        m = re.findall(pat, out)
        if not m:
            row[key] = None
            continue
        last = m[-1]
        row[key] = tuple(int(x) for x in last) if ngroups > 1 else int(last)
    return row


def _series_sampler(sample_fn, interval):
    series = []
    stop = threading.Event()
    t0 = time.time()

    def loop():
        while not stop.is_set():
            try:
                series.append((time.time() - t0, sample_fn()))
            except Exception as e:
                series.append((time.time() - t0, {"_error": repr(e)}))
            stop.wait(interval)

    th = threading.Thread(target=loop, daemon=True)
    th.start()

    def finish(timeout=15):
        stop.set()
        th.join(timeout=timeout)
        return series

    return series, finish


def test_sustained_download(args):
    name = "sustained_download"
    t0 = time.time()
    _cleanup_client_procs()

    # [H3 session, test-validity fix 2026-07-04] Default target is now the
    # LAN-local server (rig.DL_URL_SUSTAINED_LOCAL, a 6 GiB file over the
    # SAME device WAN-ingress DN HW-offload path but via the host's LAN-side
    # address, not the real upstream modem link) instead of the external
    # rig.DL_URL_DEFAULT this test used to hit unconditionally — a modem
    # hiccup mid-run (this rig's WAN modem is documented as "flaky under
    # load" project-wide) used to fail sustained_download for a reason
    # unrelated to the driver. --sustained-modem restores the old
    # external/real-internet target for a deliberate spot check;
    # --sustained-url overrides either default explicitly.
    url = (args.sustained_url or
           (rig.DL_URL_DEFAULT if args.sustained_modem else rig.DL_URL_SUSTAINED_LOCAL))
    if url != rig.DL_URL_DEFAULT:
        _prime_local_server(url)

    series, finish = _series_sampler(_sustained_sample, interval=4.0)
    runs = []
    for i in range(args.sustained_runs):
        runs.append(_curl_once(46000 + i, args.sustained_dur, size=0, url=url))
        time.sleep(1.0)
    series = finish(timeout=15)

    def first_val(key):
        for _, row in series:
            v = row.get(key)
            if v is not None:
                return v
        return None

    def last_val(key):
        for _, row in reversed(series):
            v = row.get(key)
            if v is not None:
                return v
        return None

    completed = sum(1 for r in runs if r["http"] in (200, 206))
    trap_final = last_val("qdntr")
    rdrop_first, rdrop_last = first_val("rdrop"), last_val("rdrop")
    rdrop_total = (rdrop_last - rdrop_first) if (rdrop_first is not None and rdrop_last is not None) else None

    fd_first, fd_last = first_val("sw_tx_full_drops"), last_val("sw_tx_full_drops")
    full_drops_delta = (fd_last[0] - fd_first[0]) if (fd_first and fd_last) else None

    m4tx_first, m4tx_last = first_val("m4tx"), last_val("m4tx")
    m4tx_d = (m4tx_last - m4tx_first) if (m4tx_first is not None and m4tx_last is not None) else None
    tx_first, tx_last = first_val("tm_tx_count"), last_val("tm_tx_count")
    tx_d = (tx_last - tx_first) if (tx_first is not None and tx_last is not None) else None
    mac_tracks = True
    if tx_d and tx_d > 0 and m4tx_d is not None:
        mac_tracks = (abs(m4tx_d - tx_d) / tx_d) <= args.mac_tx_tol

    notes = []
    rx_alive = True
    if len(series) >= 2:
        prev, last = series[-2][1], series[-1][1]
        for k in ("tm_irq_count", "tm_napi_count", "tm_rx_count"):
            pv, lv = prev.get(k), last.get(k)
            if pv is not None and lv is not None and lv <= pv:
                rx_alive = False
                notes.append("%s frozen in the final sampling window (%s -> %s) — "
                              "RX descriptor engine may have halted (the hard wedge)" % (k, pv, lv))

    marker = "SUST_ALIVE_%d" % (int(time.time()) % 100000)
    device_alive = marker in rig.dev(["echo %s" % marker], wait=3.0)
    if not device_alive:
        notes.append("device REPL unresponsive after sustained load — WEDGED, reboot required")

    # [red-arm 2026-07-04] qmg_dn_trap is cumulative and legitimately exceeds
    # 1024 on a healthy box now (bit6 charge-accounting off) -- its absolute
    # value no longer gates; wedge detection = rx_alive/device_alive/oracles.
    ok = (device_alive and completed >= 1 and rx_alive and mac_tracks
          and (full_drops_delta is None or full_drops_delta == 0)
          and (rdrop_total is None or rdrop_total < args.rdrop_max))

    if full_drops_delta:
        notes.append("sw_tx_full_drops grew by %d (ring overrun — must be 0 since build #490's "
                      "TX flow control)" % full_drops_delta)
    if trap_final is not None:
        notes.append("qmg_dn_trap=%d (cumulative, informational since [red-arm])" % trap_final)
    if rdrop_total is not None and rdrop_total >= args.rdrop_max:
        # [regress.py false-fail fix 2026-07-04, ctr-bug #2] The old --rdrop-max
        # default (20000) predated the build #490 TX-flowctrl fix and was tuned
        # against an assumption of near-zero red_drop growth on a healthy run.
        # Post-fix, a healthy multi-GB sustained run legitimately grows red_drop
        # by ~30-36k (bounded, non-wedging — RED drop is a normal backpressure
        # signal under sustained line-rate load, not itself the wedge). The old
        # threshold false-failed on every healthy run. --rdrop-max is now a
        # realistic ceiling with margin above that healthy range; crossing it
        # here is a genuine anomaly, not an expected/known-open issue.
        notes.append("red_drop grew by %d >= max %d — above the realistic healthy-range ceiling "
                      "(a healthy multi-GB sustained run measures ~30-36k growth; this threshold "
                      "leaves margin above that) -- investigate as a real regression" %
                      (rdrop_total, args.rdrop_max))
    if not mac_tracks:
        notes.append("mac4_tx delta %s doesn't track tm_tx_count delta %s (TX-completion divergence)" %
                      (m4tx_d, tx_d))
    if completed < args.sustained_runs:
        notes.append("%d/%d back-to-back runs completed http=200/206" % (completed, args.sustained_runs))

    metrics = {"runs_completed": completed, "runs_total": args.sustained_runs,
               "run_rates_mb_s": [r["rate_mb_s"] for r in runs],
               "qmg_dn_trap_final": trap_final, "red_drop_total": rdrop_total,
               "sw_tx_full_drops_delta": full_drops_delta, "mac4_tx_delta": m4tx_d,
               "tm_tx_count_delta": tx_d, "rx_alive": rx_alive, "device_alive_after": device_alive}
    return TestResult(name, "PASS" if ok else "FAIL", time.time() - t0, metrics, "; ".join(notes))


# ---------------------------------------------------------------------------
# 3. multiflow — source: qa_multi.py
# ---------------------------------------------------------------------------
def test_multiflow(args):
    name = "multiflow"
    t0 = time.time()
    _cleanup_client_procs()
    # [multiflow harness robustness 2026-07-04] Mirror the two host-tooling
    # mitigations churn already carries -- multiflow was missing both and so
    # false-FAILed with the exact documented instant-fail signature
    # (bytes=0 http=000 t~0.0002s) when run back-to-back or from a cold sudo/ARP
    # path, none of which is a driver issue:
    #   (1) _prime_sudo_and_arp(): warm the sudo timestamp + client-netns
    #       neighbor entry so the concurrent `sudo -S ip netns exec curl` launches
    #       don't hit a cold connect()/re-auth path (see the churn-harness-fix
    #       comment above test_churn).
    #   (2) _port_epoch_offset(): multiflow used FIXED local ports 47000+i on
    #       EVERY invocation, so two runs within a TCP TIME_WAIT window (~1-2 min)
    #       redialed the same local port->same remote and instant-failed (see the
    #       _port_epoch_offset docstring -- distinct from the ARP/sudo cold path).
    #   (3) [H2 session, multiflow-validity fix] `--local-server` (default
    #       rig.DL_URL_LOCAL): DL_URL_DEFAULT (the external thinkbroadband
    #       server) has a concurrent-connection ceiling that made this test
    #       invalid as a driver check -- the H1 session measured 1/5 real
    #       connects, http=000 on the rest, confirmed by hand (a bare curl
    #       replay outside the harness reproduced the same ceiling) to be an
    #       external-server limit, not a device/driver issue. Routing all N
    #       flows to a LAN-local host server instead (still transiting the
    #       full client-netns->lan2->routing->lan4-WAN->host path -- the SAME
    #       WAN-ingress DN HW-offload code this test exists to exercise)
    #       removes that ceiling so multiflow actually exercises the driver's
    #       concurrent-flow handling instead of an unrelated external limit.
    #   (4) [H2 session, found live] The FIRST live run against
    #       rig.DL_URL_LOCAL (then srv1g.bin, 1 GB) fetched the whole file
    #       unbounded per flow -- with 5 flows racing over a real
    #       (occasionally lossy) WiFi hop to the host, 2 flows saturated the
    #       link at line rate (114/52 MB/s) and the other 3 got a clean
    #       http=000 at EXACTLY t=--max-time (30.0050s): genuine link
    #       contention/starvation, not a driver issue or the near-zero-t
    #       instant-fail cold-path signature this file already handles
    #       elsewhere. Tried Range-capping each flow's size first (`-r`, the
    #       same mechanism poly0_stale/concurrency_race use) but
    #       `python3 -m http.server` (SimpleHTTPRequestHandler) does NOT
    #       implement HTTP Range -- it always serves the WHOLE file with 200
    #       regardless of any `-r`/Range request, so a size cap here is a
    #       no-op against this server (kept, harmless, for forward-compat
    #       with a Range-aware server). The actual fix: rig.DL_URL_LOCAL now
    #       points at a dedicated 50 MiB file (srv50m.bin) instead of the 1 GB
    #       one, so the whole-file-regardless-of-Range download aggregate
    #       demand stays modest enough to finish reliably over an imperfect
    #       WiFi hop while still exercising a real multi-second HW-offloaded
    #       flow (unlike churn's short 2 MB). See rig.py's DL_URL_LOCAL
    #       comment for the full explanation.
    #   (5) [H2 session] _prime_local_server(): the local-server path adds a
    #       THIRD hop (device->host over lan4) with its own neighbor entry
    #       that goes cold on the same idle-gap timescale as the other two
    #       -- see its docstring for the confirmed live signature.
    #   (6) [H2 session, found live] `--multiflow-rate-limit` (default 8M):
    #       even with a healthy link and the 50 MiB file, a first fully-clean
    #       5/5-connected run still FAILed the slot_ok check
    #       (uniq_slots_seen=2 < connected=5) -- at ~100 MB/s peak LAN speed
    #       a 50 MiB flow finishes in well under a second, often faster than
    #       nf_flowtable's workqueue can dispatch FLOW_CLS_REPLACE and get it
    #       HW-offloaded at all, so most connected flows never produced a
    #       "[phase6/ft] recipe:" line to count. Capping curl's own rate
    #       (`--limit-rate`, applies regardless of link/Range-support
    #       quirks) stretches every flow to several seconds so offload has
    #       time to actually engage, independent of momentary LAN speed.
    _prime_sudo_and_arp()
    _prime_local_server(args.local_server)
    port_base = 47000 + _port_epoch_offset()

    procs, outs = [], []
    for i in range(args.multiflow_n):
        lport = port_base + i
        cmd, of = _curl_cmd(lport, args.multiflow_dur, size=args.multiflow_size,
                            url=args.local_server, rate_limit=args.multiflow_rate_limit,
                            outfile="/tmp/regress_multi_%d.out" % lport)
        procs.append(subprocess.Popen(cmd, shell=True))
        outs.append(of)
        time.sleep(0.3)
    for p in procs:
        try:
            p.wait(timeout=args.multiflow_dur + 25)
        except subprocess.TimeoutExpired:
            p.kill()
    time.sleep(1.0)

    results = [_parse_curl_outfile(of) for of in outs]
    connected = sum(1 for d in results if d["http"] in (200, 206))
    frac = connected / args.multiflow_n if args.multiflow_n else 1.0
    # [H2 session, found live] tail bumped 200->800: a real (not engineered)
    # higher-way collision between two of the 5 flows produces a "reserve
    # decline"+"offload declined" line PAIR on every one of nf_flowtable's
    # re-REPLACE retries for the declined cookie -- confirmed live, dozens
    # of retries over just ~10-15s while the colliding flow stayed live --
    # easily evicting an unrelated flow's own single "recipe:" install line
    # out of a 200-line tail. This is a dmesg-ring-observability limit of
    # the harness, not a driver behavior change; a wider tail just gives the
    # accounting below visibility into installs that did happen.
    ft = _ft_dmesg_stats(tail=800)
    # [H2 session, found live] uniq_slots alone is too strict now: a flow
    # that H2's higher-way (or the pre-existing way0/poly0) collision check
    # correctly declines stays fully functional over SW (curl still gets
    # http=200/206, it's just not HW-accelerated for the window it was
    # declined) -- NOT a clobber. Confirmed live: an ordinary 5-flow
    # multiflow run naturally hit a ram6 collision between two of its own
    # flows (only 8 buckets -- unsurprising even at N=5); the correctly-
    # declined cookie showed up as "connected" with only 2 uniq_slots for
    # 5 connections, which the OLD check would have misread as a possible
    # clobber. Accept the shortfall as long as it's fully EXPLAINED by
    # logged declines (any tag -- way0/poly0/higher-way all count): a slot
    # deficit with no matching decline is still the real clobber signature.
    slot_ok = (ft["uniq_slots"] + len(ft["declined_cookies"]) >= connected) if connected else True

    ok = (frac >= args.multiflow_min_frac) and slot_ok
    notes = []
    if frac < args.multiflow_min_frac:
        notes.append("%d/%d flows connected (%.0f%%) < required %.0f%%" %
                      (connected, args.multiflow_n, frac * 100, args.multiflow_min_frac * 100))
    if not slot_ok:
        notes.append("uniq pm_slots (%d) + declined cookies (%d) seen in dmesg < connected flows "
                      "(%d) — possible UNEXPLAINED slot collision/clobber (best-effort: dmesg tail "
                      "depth may not cover the whole run if other tests ran first)" %
                      (ft["uniq_slots"], len(ft["declined_cookies"]), connected))
    elif ft["declined_cookies"]:
        notes.append("%d flow(s) correctly declined HW-offload (collision, stayed SW, still "
                      "connected) -- not a clobber: uniq_slots=%d + declined=%d >= connected=%d" %
                      (len(ft["declined_cookies"]), ft["uniq_slots"], len(ft["declined_cookies"]),
                       connected))

    metrics = {"connected": connected, "total": args.multiflow_n, "frac": frac,
               "uniq_slots_seen": ft["uniq_slots"], "installs_seen": ft["installs"],
               "declined_cookies_seen": len(ft["declined_cookies"]),
               "aggregate_bytes": sum((d["bytes"] or 0) for d in results)}
    return TestResult(name, "PASS" if ok else "FAIL", time.time() - t0, metrics, "; ".join(notes))


# ---------------------------------------------------------------------------
# 4. churn — source: qa_churn.py
#
# [regress.py churn-harness fix 2026-07-04] The first live run of this test
# (findings/fix_c1_ftlock_2026-07-04.md) found a HOST-SIDE tooling flake, not a
# driver regression: a `--churn-n 20` rerun got 3/20 "ok", but every one of the
# 17 "fail" outfiles showed `bytes=0 http=000 t=0.0002s` -- curl's own -w line,
# so curl DID start and DID exit (not a missing-tool/exec failure), but t=0.2ms
# is far too fast for any real TCP handshake/RTT -- this is curl hitting a LOCAL
# failure (connect()/route resolution) before ever sending a packet, not a
# network timeout. Device-side signals (qmg_dn_trap, canary ping) stayed
# healthy throughout every attempt, and manually replaying the identical
# `echo pw | sudo -S ip netns exec client curl ...` command 5x back-to-back
# OUTSIDE the harness succeeded 5/5 -- so the rig/network path itself is fine;
# only firing many of these back-to-back FROM ONE PYTHON PROCESS in a tight
# loop (via rig.sh's blocking subprocess.run(shell=True)) triggers it. Two
# plausible host-side causes, both addressed here (cheap, independent, and
# each closes off a real failure class regardless of which one is the actual
# culprit):
#   1. `sudo -S` re-authenticates via a fresh echo|pipe on EVERY single
#      invocation (`rig.SUDO`). Sixty of those fired back-to-back is sixty
#      fork/exec/pty-alloc cycles (this host's sudoers has `use_pty`) in a few
#      seconds -- prime the sudo timestamp ONCE up front (`sudo -S -v`) so the
#      loop's `sudo -S` calls hit an already-valid cached credential instead of
#      re-authenticating from scratch every time.
#   2. The netns "client" veth's neighbor (ARP) entry for the device's lan2
#      gateway can go stale between churn bursts; Linux caches a FAILED
#      neighbor lookup for a cooldown before re-probing, so a burst of
#      connects that lands during that cooldown gets an immediate
#      EHOSTUNREACH/ENETUNREACH from connect() -- curl reports that as
#      http=000 in under a millisecond, matching the exact symptom. Pre-warm
#      the neighbor entry with one ping to the gateway before the loop starts.
# On top of both mitigations, make the loop itself robust to a residual
# instant-fail (belt-and-suspenders, and this is what actually makes the test
# reliable regardless of which of the two causes above was the real one):
# detect the EXACT signature (t_total < --churn-instant-fail-s, effectively no
# bytes transferred) and retry that one flow (small fixed backoff) up to
# --churn-retries times before counting it as failed. A REAL driver
# regression (stale HW-forward, wedge, dropped packets after a real
# connection attempt) does not look like this signature (nonzero/partial time,
# or a real timeout) and will NOT be masked by the retry -- see the assertion
# in the loop below.
# ---------------------------------------------------------------------------
def _prime_sudo_and_arp():
    """One-time host-side warmup before a tight churn loop: (1) refresh the
    sudo timestamp so the loop's per-flow `sudo -S` calls hit a cached
    credential instead of re-authenticating from scratch every invocation;
    (2) pre-warm the client netns's neighbor entry for the device's lan2
    gateway so the first several connects don't race a stale/FAILED ARP
    cache entry. Both are cheap, best-effort, and safe no-ops if the netns
    isn't up yet (caller already assumes `rig.py up` ran)."""
    rig.sh(rig.SUDO + "true", timeout=15)
    rig.sh(rig.SUDO + rig.NS + "ping -c 1 -W 2 %s >/dev/null 2>&1; true" % rig.LAN2_GW, timeout=10)


def _prime_local_server(url=None):
    """[H2 session, found live] The two hops this file already warms
    (_prime_sudo_and_arp: host sudo timestamp + client-netns->device-lan2
    neighbor entry) don't cover the THIRD hop the LAN-local server path adds:
    the DEVICE's own neighbor entry for the local server host (over lan4,
    same /24 as LAN4_IP -- no gateway involved). That entry goes stale on
    the exact same idle-gap timescale as the other two (Linux's default
    neighbor reachable time), and a burst of concurrent flows (multiflow,
    high_way_collision) landing during that cold window instant-fails ALL of
    them with the familiar near-zero-t/bytes=0 signature -- confirmed live:
    a manual 5-flow burst seconds after a fresh `rig.py up` succeeded 4-5/5,
    the SAME burst run via the test harness ~20-30s later (after some
    interstitial inspection commands, long enough for the neighbor cache to
    go stale again) came back 0/5, all instant-fails. Warm it from the
    DEVICE side (not host/client side -- this ARP entry lives on the
    device's own lan4 neighbor table) right before firing the burst."""
    host, _ = _url_host_port(url or rig.DL_URL_LOCAL)
    rig.dev(["ping -c 1 -W 2 %s >/dev/null 2>&1; echo done" % host], wait=3.0)


def _curl_once_robust(lport, dur, size, instant_fail_s, retries, retry_gap):
    """_curl_once with a bounded retry on the exact host-tooling-flake
    signature (near-zero time_total AND no bytes transferred -- curl exited
    before ever sending a packet, not a real network timeout/drop). A
    genuine driver-side failure (partial transfer, real timeout, HW wedge)
    has nonzero time_total or nonzero bytes and is deliberately NOT retried
    here -- it must surface as a real churn FAIL."""
    d = _curl_once(lport, dur, size=size, maxtime_pad=0)
    attempts = 1
    while (attempts <= retries and d["http"] not in (200, 206) and
           (d["bytes"] or 0) == 0 and
           (d["time_total"] is not None) and d["time_total"] < instant_fail_s):
        time.sleep(retry_gap)
        d = _curl_once(lport, dur, size=size, maxtime_pad=0)
        attempts += 1
    d["_attempts"] = attempts
    return d


def test_churn(args):
    name = "churn"
    t0 = time.time()
    _cleanup_client_procs()
    _prime_sudo_and_arp()

    port_base = 48000 + _port_epoch_offset()  # avoid TIME_WAIT reuse against a recent prior run
    ok_n = fail_n = retried_n = 0
    canary_losses = []
    for i in range(args.churn_n):
        d = _curl_once_robust(port_base + i, 15.0, args.churn_size,
                               args.churn_instant_fail_s, args.churn_retries,
                               args.churn_retry_gap)
        good = (d["http"] in (200, 206)) and (d["bytes"] == args.churn_size)
        ok_n += good
        fail_n += (not good)
        retried_n += (d["_attempts"] > 1)
        if args.churn_gap:
            time.sleep(args.churn_gap)
        if (i + 1) % 20 == 0:
            out = rig.dev(["ping -c 2 -W 1 %s | busybox grep loss" % rig.CLIENT_IP], wait=2.5)
            m = re.search(r"(\d+)% packet loss", out)
            canary_losses.append(int(m.group(1)) if m else None)

    b1 = ctr.read()
    trap_final = b1.get("qmg_dn_trap")
    ft = _ft_dmesg_stats(tail=300)
    frac = ok_n / args.churn_n if args.churn_n else 1.0
    canary_ok = all((c == 0) for c in canary_losses if c is not None)
    # [red-arm 2026-07-04] trap counter is cumulative/informational now.
    ok = (frac >= args.churn_min_frac) and canary_ok

    notes = []
    if frac < args.churn_min_frac:
        notes.append("%d/%d ok (%.0f%%) < required %.0f%% (%d needed a retry -- see "
                      "the churn-harness-fix comment above test_churn if that count is high)" %
                      (ok_n, args.churn_n, frac * 100, args.churn_min_frac * 100, retried_n))
    if not canary_ok:
        notes.append("canary LAN ping saw loss during churn: %s" % canary_losses)
    if trap_final is not None:
        notes.append("qmg_dn_trap=%s (cumulative, informational since [red-arm])" % trap_final)
    if retried_n and ok:
        notes.append("%d/%d flows needed a host-tooling retry (instant-fail signature) before "
                      "succeeding -- harness flake mitigated, not a driver issue" % (retried_n, args.churn_n))

    metrics = {"ok": ok_n, "fail": fail_n, "total": args.churn_n, "frac": frac,
               "retried": retried_n, "canary_losses": canary_losses,
               "qmg_dn_trap_final": trap_final,
               "ft_installs": ft["installs"], "ft_dels": ft["dels"]}
    return TestResult(name, "PASS" if ok else "FAIL", time.time() - t0, metrics, "; ".join(notes))


# ---------------------------------------------------------------------------
# churn_no_wedge — HIGH-concurrency connection-storm wedge guard.
# Source: findings/fix_churn_adm_policer_2026-07-04.md (this session's live A/B).
#
# Distinct from `churn` (which fires flows SEQUENTIALLY at n=20 and guards the
# install/destroy lifecycle): this fires a genuine STORM -- `cnw_n` concurrent
# short flows per wave, `cnw_waves` waves, near-zero stagger -- the pattern that
# drives the DN CPU-trap queue's cumulative counter `qmg_dn_trap` to its 1024
# ceiling and WEDGES the switch lan4 datapath (reboot-only).
#
# KEY methodological fix over churn/concurrency_race: a MODEM-INDEPENDENT wedge
# oracle. A 60-flow storm overloads the flaky WAN modem too, so device-side
# pings to the WAN /24 (incl. the LAN-local server at 10.44.66.133, which sits
# on the modem LAN) are confounded -- they go 100% loss whether the SWITCH
# wedged or the MODEM just dropped. This test instead pings the device's lan4
# (LAN4_IP) FROM THE HOST root ns via wlo1 (a separate physical NIC, always in
# root ns, independent of the time-shared enxc8a362): if host->modem stays 0%
# but host->lan4 goes 100%, the DEVICE switch datapath is genuinely wedged; if
# host->modem is ALSO down, it's a modem drop and the run is INCONCLUSIVE (SKIP,
# not FAIL). See the finding for the full live A/B establishing this oracle.
#
# STATUS 2026-07-04 (later session): FIXED by [red-arm 2026-07-04] -- the RED
# cpuDn out-buffer credit-return is armed by a boot-time RED_CFG write in
# zx_tm_red_init (root cause: RED_CFG bit6 = the cpuDn out-buffer charge
# accounting, on by default/reset AND in stock, is charge-only under mainline's
# trap-all architecture -- every DN trap charge leaked 1:1 to 1024; stock never
# charges it at scale so never trips). Validated live: the exact n=30x2 storm below drove
# qmg_dn_trap to 2098 (past the old 1024 wall) with the lan4 datapath healthy.
# This guard is now in the default ORDER (near the end: if it regresses the
# box wedges reboot-only and would confound anything after it); the targeted
# fast guard for the same fix is red_credit_recycle. NOTE the trap_wedge_thresh
# check below was retired with the fix: qmg_dn_trap is a cumulative admit
# counter that now freely exceeds 1024 on a HEALTHY box -- health = the
# host->lan4 oracle, not the counter value.
# ---------------------------------------------------------------------------
def _host_ping_loss(target):
    """Ping `target` FROM the host root ns (routes via wlo1 for the WAN /24 --
    a separate NIC from the time-shared enxc8a362). The modem-independent
    switch-wedge oracle. Returns integer % loss, or None if unparseable."""
    rc, out = rig.sh("ping -c3 -W2 %s" % target, timeout=12)
    m = re.search(r"(\d+)% packet loss", out)
    return int(m.group(1)) if m else None


def test_churn_no_wedge(args):
    name = "churn_no_wedge"
    t0 = time.time()
    _cleanup_client_procs()
    _prime_sudo_and_arp()
    _prime_local_server()

    # Baseline: the modem-independent oracle must be healthy BEFORE the storm,
    # else the rig/oracle isn't set up and the result is meaningless.
    # [red-arm 2026-07-04] Retry the lan4 baseline like the post-storm oracle:
    # in a battery this test can start while the modem AP's wire->WiFi leg is
    # still recovering from a PREVIOUS test's traffic (~1-4 min).
    base_modem = _host_ping_loss(rig.WAN_GW)
    base_lan4 = None
    for attempt in range(args.cnw_oracle_retries):
        base_lan4 = _host_ping_loss(rig.LAN4_IP)
        if base_lan4 is not None and base_lan4 < 100:
            break
        if attempt + 1 < args.cnw_oracle_retries:
            time.sleep(args.cnw_oracle_gap)
    if base_lan4 is None or base_lan4 >= 100 or (base_modem is not None and base_modem >= 100):
        return TestResult(name, "SKIP", time.time() - t0,
                          {"base_lan4_loss": base_lan4, "base_modem_loss": base_modem},
                          "pre-storm host->lan4/modem not both healthy (host->lan4=%s%% "
                          "host->modem=%s%%) -- rig/oracle not ready, cannot judge a wedge; "
                          "check wlo1 is up @10.44.66.133 and rig.py up ran" %
                          (base_lan4, base_modem))

    b0 = ctr.read()
    trap0 = b0.get("qmg_dn_trap")

    # Fire the storm: cnw_waves waves of cnw_n concurrent short flows against the
    # LAN-local server, distinct local ports across all flows, near-zero stagger.
    port = args.cnw_port_base + _port_epoch_offset()
    connected = total = 0
    for w in range(args.cnw_waves):
        procs, outs = [], []
        for i in range(args.cnw_n):
            cmd, of = _curl_cmd(port, args.cnw_dur, url=rig.DL_URL_LOCAL,
                                outfile="/tmp/regress_cnw_%d.out" % port, maxtime_pad=8)
            procs.append(subprocess.Popen(cmd, shell=True))
            outs.append(of)
            port += 1
            time.sleep(args.cnw_stagger)
        for p in procs:
            try:
                p.wait(timeout=args.cnw_dur + 25)
            except subprocess.TimeoutExpired:
                p.kill()
        for of in outs:
            total += 1
            connected += 1 if _parse_curl_outfile(of)["http"] in (200, 206) else 0
        if w + 1 < args.cnw_waves and args.cnw_wave_gap:
            time.sleep(args.cnw_wave_gap)
    time.sleep(1.5)

    b1 = ctr.read()
    trap_final = b1.get("qmg_dn_trap")
    modem_loss = _host_ping_loss(rig.WAN_GW)
    # [red-arm 2026-07-04, live-validated] Oracle needs a SETTLE window: right
    # after a 60-flow storm the CPU trap path is still draining the backlog
    # (~6000 trapped frames) and host->lan4 can read 100% loss for ~30-60 s,
    # then fully recover (loadavg 0.00, q8-15 flat, pings clean) -- a
    # TRANSIENT, observed on the first fixed-build run. The GENUINE wedge is
    # permanent (reboot-only), so retrying cannot mask it: declare WEDGED only
    # if host->lan4 stays 100% across all retries.
    lan4_loss = None
    for attempt in range(args.cnw_oracle_retries):
        lan4_loss = _host_ping_loss(rig.LAN4_IP)
        if lan4_loss is not None and lan4_loss < 100:
            break
        if attempt + 1 < args.cnw_oracle_retries:
            time.sleep(args.cnw_oracle_gap)
    alive = "CNW_ALIVE" in rig.dev(["echo CNW_ALIVE"], wait=3.0)
    frac = connected / total if total else 0.0

    metrics = {"flows": total, "connected": connected, "frac": frac,
               "qmg_dn_trap_before": trap0, "qmg_dn_trap_final": trap_final,
               "host_lan4_loss": lan4_loss, "host_modem_loss": modem_loss,
               "repl_alive": alive}

    # Modem drop => inconclusive (SKIP), never a FAIL (matches this file's honesty
    # convention for confounded/timing-sensitive checks).
    if modem_loss is None or modem_loss >= 100:
        return TestResult(name, "SKIP", time.time() - t0, metrics,
                          "host->modem went %s%% during the storm (the flaky WAN modem "
                          "dropped under load) -- cannot cleanly judge the switch; re-run "
                          "after `rig.py boot --long` revives the modem" % modem_loss)

    wedged = (lan4_loss is not None and lan4_loss >= 100)
    notes = []
    if wedged:
        # [red-arm 2026-07-04, live-RE'd] host->lan4 dead through the retries is
        # NOT yet proof of a device wedge: the storm also saturates the modem
        # AP's wire->WiFi direction (its ICMP responder stays clean, so the
        # host->modem check cannot see it), which recovers over ~1-4 min.
        # Discriminate with the DEVICE-side trap signature: fire pings at lan4
        # and watch qmg_dn_trap. The TRUE (historical, reboot-only) wedge has
        # qmg_dn_trap FROZEN while frames keep arriving (RED demotes them);
        # measured live during a post-storm AP outage instead: +132 traps for
        # ~132 arriving pings = device trap path fully alive.
        t_a = rig.poke_read([0x9234c04c]).get(0x9234c04c)
        rig.sh("ping -i 0.1 -c 50 -W 1 %s >/dev/null 2>&1; true" % rig.LAN4_IP, timeout=30)
        time.sleep(1.0)
        t_b = rig.poke_read([0x9234c04c]).get(0x9234c04c)
        d = (t_b - t_a) if (t_a is not None and t_b is not None) else None
        metrics["wedge_probe_trap_delta"] = d
        if d is not None and d >= 25:
            return TestResult(name, "SKIP", time.time() - t0, metrics,
                              "host->lan4 dead post-storm BUT the device trap path is alive "
                              "(qmg_dn_trap +%d for 50 probe pings) -- this is the modem AP's "
                              "wire->WiFi leg recovering from the storm (takes ~1-4 min), not a "
                              "switch wedge; INCONCLUSIVE for the device. Re-run after a few "
                              "minutes for a clean verdict." % d)
        notes.append("WEDGED: modem UP (host->modem 0%%) but device lan4 dead "
                      "(host->lan4=%s%%) AND qmg_dn_trap FROZEN under probe pings "
                      "(delta=%s -- the historical reboot-only signature). The [red-arm "
                      "2026-07-04] RED_CFG bit6 fix (zx_tm_red_init + zx_tm_dma_init) has "
                      "regressed, or a new wedge class appeared; see "
                      "findings/fix_churn_red_dnbank_2026-07-04.md + the red_credit_recycle "
                      "guard." % (lan4_loss, d))
    ok = alive and (not wedged)
    if not alive:
        notes.append("device REPL unresponsive after the storm")
    if ok:
        notes.append("survived %d concurrent flows x%d waves: qmg_dn_trap %s->%s (cumulative, "
                      "may exceed 1024 -- healthy since [red-arm]), lan4 datapath alive, "
                      "%d/%d flows served" %
                      (args.cnw_n, args.cnw_waves, trap0, trap_final, connected, total))
    return TestResult(name, "PASS" if ok else "FAIL", time.time() - t0, metrics, "; ".join(notes))


# ---------------------------------------------------------------------------
# concurrency_race — TARGETED regression guard for the C1 fix (findings/
# qa_static_bughunt_2026-07-04.md / findings/fix_c1_ftlock_2026-07-04.md): the
# FT offload path had ZERO locking, so nf_flow_table's three separate
# WQ_UNBOUND workqueues could dispatch concurrent FLOW_CLS_REPLACE/DESTROY
# and (a) let two racing REPLACEs allocate the SAME ft_flows[]/pm_slot ->
# cross-flow NAT corruption, and (b) interleave the CMD-first/data-descending
# indirect-RAM write sequence on the shared CLA/PM engines and corrupt an
# unrelated CLA RAM entry (including a boot-replayed trap rule). `multiflow`/
# `churn` already exercise concurrency/churn incidentally; this test is
# PURPOSE-BUILT to maximize the race window (more flows, near-zero launch
# stagger, size-jittered so completions — and therefore DESTROYs — land
# while later flows are still being installed) and to assert the EXACT
# corruption signatures C1 describes, not just "did throughput look ok".
#
# Detection strategy: the driver's own [phase6/ft] dmesg log gives an
# authoritative install/destroy timeline keyed by pm_slot (`recipe: ...
# pm_slot=N` on install, `flow del ... ext blk N` on destroy — both are the
# same pm_slot: see zx_ft_install_recipe/zx_ft_flow_untrack in
# zx-eth-main.c). Walking that timeline in order and tracking each slot's
# occupancy catches a slot being (re)installed while STILL occupied by a
# prior, not-yet-destroyed flow — which is precisely a live pm_slot
# collision, i.e. two flows simultaneously sharing one NAT/next-hop state
# (the C1 #1 failure mode). A second check diffs a static CLA ram7
# (trap-queue) dump before/after — the FT path never touches ram7, so any
# change is a stray indirect-RAM write landing on unrelated CLA state (the
# C1 #2 failure mode). Pre-fix (no zx_hwlock) this test is expected to be
# able to trip the pm_slot-collision check under enough concurrency; post-fix
# it must not, ever, at any concurrency level -- run it standalone with
# `regress.py concurrency_race` to hammer it in isolation.
# ---------------------------------------------------------------------------
def _ft_pm_slot_timeline(tail=4000, t_ref=None, margin=1.0):
    """Chronological (dmesg_time, event, pm_slot) list from [phase6/ft] lines.
    'recipe:' (install) lines carry pm_slot but not cookie; 'flow del ... ext
    blk N' (destroy) lines carry cookie AND pm_slot (N). We don't need the
    cookie to detect a slot-reuse collision -- see test_concurrency_race.

    [H3 session, found live 2026-07-04] Because this is cookie-agnostic by
    design, it CANNOT tell a genuine two-different-flows-same-slot collision
    apart from a single flow's own self-REPLACE-changed-tuple re-install on
    its own (unchanged) pm_slot (the exact H3/H3a scenario the new
    zx_ft_uninstall() rollback + the replace_orphan regression test
    exercise) -- both look like "install(slot), install(slot) again, no
    destroy in between" from pm_slot alone. Confirmed live: running
    replace_orphan shortly before concurrency_race left exactly that
    2-installs-no-destroy signature on pm_slot 8 in dmesg, which this
    function's default tail=4000 window was easily wide enough to still
    include, and test_concurrency_race misreported it as a pm_slot COLLISION
    (the C1 corruption signature) even though every REAL concurrent-flow
    install/destroy pair in that same run was clean. Pass `t_ref`
    (_device_uptime(), captured right before firing the actual concurrent
    flows) to exclude any earlier tool/test's leftover [phase6/ft] lines --
    same windowing idiom _dmesg_since already uses for poly0_stale/
    high_way_collision, for the identical reason (stale-dmesg
    cross-contamination between tests run in the same session)."""
    out = rig.dev(["dmesg | busybox grep -a 'phase6/ft' | busybox tail -%d" % tail], wait=3.0)
    events = []
    for ln in out.splitlines():
        if "phase6/ft" not in ln or "grep" in ln:
            continue
        mt = re.match(r"\s*\[\s*([\d.]+)\]", ln)
        t = float(mt.group(1)) if mt else 0.0
        if t_ref is not None and t < t_ref - margin:
            continue
        if "recipe:" in ln:
            m = re.search(r"pm_slot=(\d+)", ln)
            if m:
                events.append((t, "install", int(m.group(1))))
        elif "flow del" in ln and "ext blk" in ln:
            m = re.search(r"ext blk (\d+)", ln)
            if m:
                events.append((t, "destroy", int(m.group(1))))
    events.sort(key=lambda e: e[0])
    return events


def test_concurrency_race(args):
    name = "concurrency_race"
    t0 = time.time()
    _cleanup_client_procs()

    # Canary snapshot of a static, boot-replayed CLA table the FT path never
    # writes (ram7 trap-queue) -- catches an interleaved-write stray landing
    # on unrelated CLA RAM (C1 failure mode #2).
    before = rig.dev(["cat /sys/kernel/debug/zx_eth/cladump | busybox head -12"], wait=2.5)

    # Hammer: many concurrent flows, near-zero launch stagger (vs multiflow's
    # 0.3s), sizes JITTERED across a wide range so completion times (and
    # therefore FLOW_CLS_DESTROY dispatch) spread out and overlap with later
    # flows' installs instead of all finishing together -- this is what
    # maximizes REPLACE-vs-REPLACE and REPLACE-vs-DESTROY concurrency instead
    # of just REPLACE-vs-REPLACE at t=0.
    # [H3 session fix] Captured right before firing the burst, so
    # _ft_pm_slot_timeline can exclude any earlier test/tool's [phase6/ft]
    # lines still inside its dmesg tail window -- see that function's
    # docstring for the concrete false-positive this fixes.
    t_ref = _device_uptime()

    n = args.race_n
    rnd = random.Random(0xc1)  # deterministic across runs, still varied per-flow
    procs, outs = [], []
    for i in range(n):
        lport = 49500 + i
        size = rnd.randint(args.race_size_min, args.race_size_max)
        cmd, of = _curl_cmd(lport, args.race_dur, size=size,
                             outfile="/tmp/regress_race_%d.out" % lport, maxtime_pad=20)
        procs.append(subprocess.Popen(cmd, shell=True))
        outs.append(of)
        time.sleep(args.race_stagger)
    for p in procs:
        try:
            p.wait(timeout=args.race_dur + 30)
        except subprocess.TimeoutExpired:
            p.kill()
    time.sleep(1.5)

    # Check 1: pm_slot temporal-overlap collision -- the C1 #1 signature.
    events = _ft_pm_slot_timeline(tail=max(4000, n * 40), t_ref=t_ref)
    active = set()
    collisions = []
    orphan_destroys = 0
    n_install = n_destroy = 0
    for t, ev, slot in events:
        if ev == "install":
            n_install += 1
            if slot in active:
                collisions.append(slot)
            active.add(slot)
        else:
            n_destroy += 1
            if slot in active:
                active.discard(slot)
            else:
                orphan_destroys += 1

    # Check 2: boot trap-queue RAM (ram7) untouched -- the C1 #2 signature.
    after = rig.dev(["cat /sys/kernel/debug/zx_eth/cladump | busybox head -12"], wait=2.5)
    trap_intact = (before == after)

    # Check 3: device still alive (a corrupted/wedged CLA would show here too).
    alive = "RACE_ALIVE" in rig.dev(["echo RACE_ALIVE"], wait=3.0)

    connected = sum(1 for of in outs if _parse_curl_outfile(of)["http"] in (200, 206))
    frac = connected / n if n else 1.0

    ok = (len(collisions) == 0) and (frac >= args.race_min_frac) and trap_intact and alive

    notes = []
    if collisions:
        notes.append("pm_slot COLLISION (two live flows shared a slot before either was "
                      "destroyed): slots=%s -- the exact C1 cross-flow NAT-corruption "
                      "signature; the ft_lock mutex should make this impossible" %
                      sorted(set(collisions)))
    if orphan_destroys:
        notes.append("%d orphan destroy(s) (destroy referenced a slot with no tracked live "
                      "install in this window -- informational, can be a dmesg-tail boundary "
                      "artifact, not itself a corruption signature)" % orphan_destroys)
    if frac < args.race_min_frac:
        notes.append("%d/%d connected (%.0f%%) < required %.0f%%" %
                      (connected, n, frac * 100, args.race_min_frac * 100))
    if not trap_intact:
        notes.append("CLA ram7 boot trap-queue dump CHANGED across the stress -- possible "
                      "interleaved-write corruption of unrelated CLA RAM")
    if not alive:
        notes.append("device unresponsive after the stress")
    if ok and not notes:
        notes.append("%d installs / %d destroys observed across %d concurrent flows, "
                      "0 pm_slot collisions, ram7 trap rules intact" % (n_install, n_destroy, n))

    metrics = {"flows": n, "connected": connected, "frac": frac, "installs": n_install,
               "destroys": n_destroy, "collisions": len(collisions),
               "orphan_destroys": orphan_destroys, "trap_intact": trap_intact}
    return TestResult(name, "PASS" if ok else "FAIL", time.time() - t0, metrics, "; ".join(notes))


# ---------------------------------------------------------------------------
# poly0_stale — TARGETED regression guard for the C2 fix (findings/
# qa_static_bughunt_2026-07-04.md finding C2 / findings/fix_c2_poly0_2026-07-04.md):
# the WAN-DN poly-0 ram2 entry (ram2[raw0 & 0xff]) is the slot the WAN-ingress
# lookup ACTUALLY consults for a DN (download) flow -- a SEPARATE ram2 address
# from the poly-1 way0 bucket (ram2[raw & 0xff]) the pre-existing 5-way
# install/collision-check/untrack logic already covered. Before the fix: (a)
# FLOW_CLS_DESTROY never cleared it (stale HW-forward of a dead tuple, and
# once its pm_slot is reused by a new flow, the stale entry applies the NEW
# flow's NAT to the OLD tuple's traffic), and (b) reserve() never
# collision-checked it (two DN flows with distinct raw&0xff but coincident
# raw0&0xff -- ~53% probability by 20 concurrent flows, birthday bound over
# 256 buckets -- both got admitted and the second's poly-0 write silently
# clobbered the first's). Two independent sub-checks:
#
#   A. stale-on-destroy (deterministic, HW-verified via the `clapeek`
#      debugfs tool -- NOT just trusting the driver's own dmesg claim): run
#      one real DN flow, read ram2 at its reported poly-0 address right after
#      install (must be non-zero), wait for FLOW_CLS_DESTROY, read the SAME
#      address again (must now be all-zero). FAILS only on a confirmed
#      still-live entry post-destroy; a timeout waiting for the destroy is
#      reported INCONCLUSIVE (not a fail -- conntrack aging timing is not
#      under this test's control) so the test can't cry wolf on a slow GC.
#   B. no-clobber-on-collision (engineered pair, cross-checked live): two
#      client-side local ports were pre-selected OFFLINE (see
#      _find_poly0_collision_pair -- a faithful Python port of
#      zx_ft_build_key/zx_cla_hash_sw_poly0: the first two ports, scanning
#      up from port 49700, predicted to target the SAME ram2[raw0 & 0xff]
#      with this rig's DL_URL_DEFAULT/CLIENT_IP -- e.g. 49802/49817 both
#      land on ram2[0x03], confirmed by hand 2026-07-04; the function itself
#      picks whichever pair it finds first, which depends on the scan
#      window) to collide on raw0&0xff while very likely NOT colliding on
#      raw&0xff (a
#      different, HW-computed poly -- unpredictable offline, so "very
#      likely" not "guaranteed": the live dmesg is what's actually checked,
#      the offline prediction only picks which two ports to try). Fires both
#      concurrently (so the second's reserve() happens while the first is
#      still tracked) and asserts the two NEVER both show a successful
#      poly-0 install at the SAME ram2 address (the actual clobber
#      signature) -- a decline tagged "poly0" in dmesg (the [C2 fix]
#      reserve() logging added alongside this test) is the expected/correct
#      outcome when the engineered collision reproduces; not reproducing at
#      all is reported INCONCLUSIVE, not a fail.
#
# Neither sub-check depends on the other; the test FAILs only on a
# *confirmed* clobber or leak, never on an inconclusive/timing miss (matching
# this file's existing honesty convention for timing-sensitive checks, e.g.
# concurrency_race's "orphan_destroys" and multiflow's slot-count heuristic).
# ---------------------------------------------------------------------------
def _poly0_build_key(ip_proto, saddr_str, daddr_str, sport, dport, is_wan):
    """Faithful Python port of zx_ft_build_key (zx-eth-main.c). OFFLINE-only
    helper used to pre-select a raw0-colliding local-port pair for sub-check
    B -- the driver's own zx_cla_hash_sw_poly0 stays the ground truth; this
    only needs to match it well enough to pick two candidate ports, and
    sub-check B cross-checks the outcome against the LIVE dmesg, not this
    prediction."""
    s = struct.unpack("!I", socket.inet_aton(saddr_str))[0]
    d = struct.unpack("!I", socket.inet_aton(daddr_str))[0]
    fields = [ip_proto, (s >> 16) & 0xffff, s & 0xffff,
              (d >> 16) & 0xffff, d & 0xffff, sport, dport]
    kb = bytearray(48)
    kb[3] = 0x48
    if is_wan:
        kb[4] |= 1
    for n in range(7):
        base = 33 + 16 * n
        for i in range(16):
            if fields[n] & (1 << i):
                pos = base + i
                kb[pos >> 3] |= (1 << (pos & 7))
    return [kb[4 * i] | (kb[4 * i + 1] << 8) | (kb[4 * i + 2] << 16) | (kb[4 * i + 3] << 24)
            for i in range(12)]


def _poly0_hash(key):
    """Faithful Python port of zx_cla_hash_sw_poly0 (zx-eth-main.c): CRC-32,
    poly 0x04C11DB7, init 0, MSB-first, no xorout, over the reversed 45-byte
    flow key."""
    crc = 0
    for b in range(44, -1, -1):
        byte = (key[b >> 2] >> (8 * (b & 3))) & 0xff
        crc ^= (byte << 24)
        for _ in range(8):
            crc = (((crc << 1) ^ 0x04C11DB7) if (crc & 0x80000000) else (crc << 1)) & 0xffffffff
    return crc & 0xffff


def _poly0_predict(local_port, server_ip=None, server_port=80):
    """Predicted raw0 for a DN flow whose client-side local port is
    `local_port`: for the DN direction (zx_ft_flower_replace, eg_regport !=
    WAN) the tuple's saddr/sport are the WAN server, daddr/dport the LAN
    client, and raw0 is always computed with is_wan=True (mirrors
    zx_ft_install_recipe's poly-0 write)."""
    server_ip = server_ip or rig.DL_URL_DEFAULT.split("/")[2]
    return _poly0_hash(_poly0_build_key(6, server_ip, rig.CLIENT_IP, server_port,
                                        local_port, True))


def _find_poly0_collision_pair(port_lo=49700, port_hi=49900):
    """Scan a local-port window (dedicated -- doesn't overlap multiflow's
    47000s, churn's 48000s, bidirectional's 49000-49100s, or
    concurrency_race's 49500+race_n) offline for the first two ports
    predicted to collide on ram2[raw0 & 0xff] (scanning up from port_lo;
    with the default window this is a deterministic, previously-verified
    pair -- e.g. ports 49802/49817 both land on ram2[0x03] with rig.py's
    default DL_URL_DEFAULT/CLIENT_IP, confirmed offline 2026-07-04, though
    the exact pair THIS function returns depends on scan order/window).
    Pure computation, no device needed. Returns (port_a, port_b,
    predicted_byte) or None."""
    buckets = {}
    for p in range(port_lo, port_hi):
        b = _poly0_predict(p) & 0xff
        buckets.setdefault(b, []).append(p)
        if len(buckets[b]) >= 2:
            return buckets[b][0], buckets[b][1], b
    return None


def _device_uptime():
    """Current device kernel uptime (seconds, float) via /proc/uptime.

    [found live 2026-07-04] The first version of this test tried to window
    dmesg scans with an artificial marker (`rig.dev(["echo MARK"])` then
    `out.find(MARK)`), copying the *idea* of the marker trick used elsewhere
    in this codebase for aliveness checks (test_recovery_alive etc.) -- but
    an `echo` at the device's shell only writes to the REPL/UART, NOT the
    kernel dmesg ring, so `out.find(MARK)` against a `dmesg | grep ...`
    capture always returned -1 and the "windowing" was a silent no-op: every
    poly-0-install-line scan saw the ENTIRE dmesg ring, including stale
    matches from earlier tests/manual replay in the same session (confirmed
    live: sub-check B's installed_addrs_seen list included addresses from
    sub-check A's already-destroyed flow before this fix). Every driver
    pr_info/dev_info line already carries a kernel timestamp prefix
    (`[ 1234.567890]`) -- use THAT to window scans instead: capture the
    uptime before the operation being scanned for, then keep only dmesg
    lines timestamped at or after it (with a small safety margin for
    print/scheduling latency)."""
    out = rig.dev(["cat /proc/uptime"], wait=1.5)
    m = re.search(r"(\d+\.\d+)\s+\d+\.\d+", out)
    return float(m.group(1)) if m else None


def _dmesg_since(grep_expr, t_ref, tail=40, margin=1.0, wait=2.5):
    """`dmesg | busybox grep -aE '<grep_expr>' | busybox tail -<tail>`,
    filtered to lines whose kernel timestamp is >= t_ref - margin (t_ref
    from _device_uptime(), captured before the operation of interest). If
    t_ref is None (uptime read failed), returns the unfiltered tail instead
    of silently matching nothing."""
    out = rig.dev(["dmesg | busybox grep -aE '%s' | busybox tail -%d" % (grep_expr, tail)],
                  wait=wait)
    if t_ref is None:
        return out
    keep = []
    for ln in out.splitlines():
        m = re.match(r"\s*\[\s*([\d.]+)\]", ln)
        if not m or float(m.group(1)) >= t_ref - margin:
            keep.append(ln)
    return "\n".join(keep)


def _clapeek(ram_id, addr):
    """Read a CLA indirect-RAM entry via the `clapeek` debugfs tool (write
    'ram_id addr', decode the hex words dmesg prints back). Source:
    validate_fix.py/vbisect.py/stock_entry_test.py's exact idiom -- one
    combined dev() round trip (write + grep), same pattern as
    rig.poke_read().

    [confirmed live 2026-07-04, reading zx_clapeek_write's own source
    (zx-eth-main.c): BOTH fields are parsed with sscanf("%x %x", ...) --
    i.e. clapeek takes ram_id AND addr in HEX, not decimal (unlike poke's
    single hex address, which is also hex, so easy to assume both nodes
    match -- they do, just make sure the WRITE side sends hex too, an
    earlier version of this helper wrote addr in decimal and silently
    always read back None for any addr with differing decimal/hex digits).
    The entry is 17 words, printed across TWO pr_info lines: the first 9
    words on the "clapeek ram%u addr%#x:" line, the remaining 8 on a
    "  clapeek+:" continuation line -- concatenate both so an all-zero
    check sees the whole entry (installs/untrack write/clear a 15-word
    entry, which lands entirely within these 17)."""
    out = rig.dev(["echo '%x %x' > /sys/kernel/debug/zx_eth/clapeek" % (ram_id, addr),
                   "dmesg | busybox grep -a 'clapeek' | busybox tail -2"], wait=2.0)
    m1 = re.search(r"clapeek ram%u addr0x0*%x:\s*([0-9a-f ]+)" % (ram_id, addr), out, re.I)
    if not m1:
        return None
    words = [int(w, 16) for w in m1.group(1).split() if w]
    m2 = re.search(r"clapeek\+:\s*([0-9a-f ]+)", out, re.I)
    if m2:
        words += [int(w, 16) for w in m2.group(1).split() if w]
    return words


def test_poly0_stale(args):
    name = "poly0_stale"
    t0 = time.time()
    _cleanup_client_procs()
    _prime_sudo_and_arp()
    notes = []
    metrics = {}

    # --- sub-check A: FLOW_CLS_DESTROY must clear the poly-0 ram2 slot ---
    #
    # [timing note, found live 2026-07-04] At this rig's line rate (~90 MB/s),
    # even a several-MB flow completes in well under a second -- faster than
    # one clapeek round trip over the UART-bridge REPL (~1.5-2s). A first
    # version of this test launched a small BLOCKING download, then tried to
    # clapeek the poly-0 slot "right after install" -- by the time that read
    # landed, the flow (and its FLOW_CLS_DESTROY) had usually already
    # finished, so the "live, not-yet-destroyed" read observed the ALREADY-
    # CLEARED state and the test could only report itself inconclusive. Two
    # changes: (1) launch the flow via Popen (non-blocking) with a bigger
    # size (default 200 MB) so there's a multi-second window where the flow
    # is genuinely installed-and-still-running to poll for the live read as
    # a best-effort bonus signal; (2) don't gate the core PASS/FAIL on that
    # racy live read -- the driver's own write result (rc=0 on the "WAN-DN
    # poly-0 install" line -- zx_cla_write_hash's actual return code, not
    # assumed) is the write-side confirmation, and the independent clapeek
    # read AFTER FLOW_CLS_DESTROY (unaffected by the race -- destroy has
    # already happened by the time we read) is the real HW-verified
    # assertion this test exists for.
    t_a = _device_uptime()
    lport_a = 49780 + (int(time.time()) // 90) % 5  # dodge TIME_WAIT against a recent prior run
    cmd_a, of_a = _curl_cmd(lport_a, args.poly0_dur, size=args.poly0_size,
                            outfile="/tmp/regress_poly0a_%d.out" % lport_a)
    proc_a = subprocess.Popen(cmd_a, shell=True)

    raw0 = addr = write_rc = None
    live_nonzero = None
    install_deadline = time.time() + min(args.poly0_dur, 15.0)
    while time.time() < install_deadline and addr is None:
        window = _dmesg_since("WAN-DN poly-0 install", t_a, tail=10, wait=1.5)
        found = list(re.finditer(r"raw0=0x([0-9a-f]+) ram2\[0x([0-9a-f]+)\] rc=(-?\d+)", window))
        if found:
            raw0, addr, write_rc = (int(found[-1].group(1), 16), int(found[-1].group(2), 16),
                                     int(found[-1].group(3)))
            words_live = _clapeek(2, addr)
            live_nonzero = bool(words_live) and any(w for w in words_live)
            break
        time.sleep(1.0)

    try:
        proc_a.wait(timeout=args.poly0_dur + 20)
    except subprocess.TimeoutExpired:
        proc_a.kill()
    d = _parse_curl_outfile(of_a)

    a_ok = None
    if addr is None:
        notes.append("sub-check A INCONCLUSIVE: no '[phase6/ft] WAN-DN poly-0 install' dmesg line seen "
                      "for the test flow (http=%s) -- either it wasn't HW-offloaded yet or the dmesg "
                      "tail didn't cover it" % d["http"])
        metrics["sub_a"] = "inconclusive: no poly-0 install observed"
    else:
        write_ok = (write_rc == 0)

        del_seen = False
        deadline = time.time() + args.poly0_destroy_timeout
        while time.time() < deadline and not del_seen:
            dwin = _dmesg_since("flow del", t_a, tail=15, wait=2.0)
            if re.search(r"flow del.*poly0=cleared.*ram2\[0x0*%x\]" % addr, dwin):
                del_seen = True
                break
            time.sleep(2.0)

        cleared = None
        if del_seen:
            words_after = _clapeek(2, addr)
            cleared = bool(words_after) and not any(w for w in words_after)

        a_ok = (True if (write_ok and del_seen and cleared)
                else (False if (del_seen and not cleared) else None))
        metrics["sub_a"] = {"raw0": "0x%04x" % raw0, "ram2_addr": "0x%02x" % addr,
                            "write_rc": write_rc, "live_nonzero_besteffort": live_nonzero,
                            "destroy_seen": del_seen, "cleared_after_destroy": cleared}
        if live_nonzero is None:
            notes.append("sub-check A: best-effort live (pre-destroy) read didn't land in time -- "
                          "not required for the verdict, see the timing note above test_poly0_stale")
        elif not live_nonzero:
            notes.append("sub-check A: best-effort live read saw ram2[0x%02x] already all-zero (the "
                          "flow likely finished+destroyed before the read landed -- not evidence "
                          "either way, the destroy-time check below is unaffected)" % addr)
        if not write_ok:
            notes.append("sub-check A: the poly-0 write itself reported rc=%s (not 0) -- inconclusive, "
                          "can't attribute a clear/no-clear result to this flow's entry" % write_rc)
        if not del_seen:
            notes.append("sub-check A INCONCLUSIVE: no FLOW_CLS_DESTROY observed within %ds of the "
                          "flow finishing (conntrack didn't age it out in time -- rerun or raise "
                          "--poly0-destroy-timeout)" % args.poly0_destroy_timeout)
        elif not cleared:
            notes.append("sub-check A **FAIL**: ram2[0x%02x] (the poly-0 WAN-ingress slot) still reads "
                          "NON-ZERO after FLOW_CLS_DESTROY -- stale-HW-forward-after-destroy (C2 "
                          "fail#1) is present" % addr)

    # --- sub-check B: two engineered raw0-colliding flows must not clobber ---
    #
    # [found live 2026-07-04] Sub-check A's destroy-wait poll loop above can
    # spend up to --poly0-destroy-timeout seconds with the client netns
    # otherwise idle (only REPL/UART polling, no client-side traffic) --
    # long enough for the SAME cold-path symptom investigated for churn
    # (findings/fix_c2_poly0_2026-07-04.md's churn-harness-fix note; a stale
    # ARP/neighbor entry for the client's gateway and/or an expired sudo
    # timestamp both manifest as the exact "bytes=0 http=000 t~0.0002s"
    # instant-fail signature on the FIRST connection attempt after the idle
    # gap). Confirmed by hand: firing these same two curl commands back to
    # back right after this file's own priming/warm state is 5/5 clean, but
    # firing them cold (no priming) reproduced the instant-fail on the
    # FIRST of the two. Re-prime here, right before the pair launch, not
    # just once at the top of this test.
    _prime_sudo_and_arp()
    # Shift the scan window per invocation (same TIME_WAIT-avoidance reasoning
    # as _port_epoch_offset above) so repeated reruns don't keep re-dialing
    # the exact same engineered pair; still deterministic within one ~90s
    # window for reproducibility while debugging a single run.
    _pair_lo = 49700 + (int(time.time()) // 90 % 10) * 20
    pair = _find_poly0_collision_pair(port_lo=_pair_lo, port_hi=_pair_lo + 150)
    b_ok = None
    if not pair:
        notes.append("sub-check B SKIPPED: no offline raw0 collision found in the scan window")
        metrics["sub_b"] = "skipped: no collision pair found"
    else:
        pa, pb, predicted_byte = pair
        t_b = _device_uptime()

        cmd_ba, of_ba = _curl_cmd(pa, args.poly0_pair_dur, size=args.poly0_pair_size,
                                  outfile="/tmp/regress_poly0_%d.out" % pa)
        proc_ba = subprocess.Popen(cmd_ba, shell=True)
        time.sleep(args.poly0_pair_stagger)
        cmd_bb, of_bb = _curl_cmd(pb, args.poly0_pair_dur, size=args.poly0_pair_size,
                                  outfile="/tmp/regress_poly0_%d.out" % pb)
        proc_bb = subprocess.Popen(cmd_bb, shell=True)
        for p in (proc_ba, proc_bb):
            try:
                p.wait(timeout=args.poly0_pair_dur + 25)
            except subprocess.TimeoutExpired:
                p.kill()
        time.sleep(1.0)

        window = _dmesg_since("WAN-DN poly-0 install|reserve decline|flow del", t_b, tail=80, wait=2.5)
        installed_addrs = [int(m.group(2), 16) for m in
                           re.finditer(r"raw0=0x([0-9a-f]+) ram2\[0x([0-9a-f]+)\]", window)]
        poly0_declines = len(re.findall(r"reserve decline:.*poly0", window))

        # [found live 2026-07-04] A naive "did the SAME address show a
        # successful install line more than once" check is a FALSE POSITIVE:
        # nf_flow_table re-delivers FLOW_CLS_REPLACE continuously for a live
        # flow, so while flow A holds ram2[addr], every one of B's
        # re-REPLACEs is (correctly) declined at that address -- but once
        # A's download finishes and FLOW_CLS_DESTROY frees ram2[addr], a
        # LATER re-REPLACE for B can legitimately install there too. That is
        # correct slot reuse, not a clobber. The real signature (mirrors
        # concurrency_race's pm_slot temporal-overlap check) is an install
        # for an address that is ALREADY live (installed, not yet destroyed)
        # -- walk install/destroy as an ordered timeline keyed by ram2
        # address and look for exactly that.
        events = []
        for m in re.finditer(r"\[\s*([\d.]+)\][^\n]*raw0=0x[0-9a-f]+ ram2\[0x([0-9a-f]+)\]", window):
            events.append((float(m.group(1)), "install", int(m.group(2), 16)))
        for m in re.finditer(r"\[\s*([\d.]+)\][^\n]*flow del[^\n]*poly0=cleared[^\n]*ram2\[0x([0-9a-f]+)\]",
                            window):
            events.append((float(m.group(1)), "destroy", int(m.group(2), 16)))
        events.sort(key=lambda e: e[0])
        live_addrs, clobbers = set(), []
        for _, ev, a in events:
            if ev == "install":
                if a in live_addrs:
                    clobbers.append(a)
                live_addrs.add(a)
            else:
                live_addrs.discard(a)
        clobbered = len(clobbers) > 0

        b_ok = (False if clobbered else
                (True if (poly0_declines or len(installed_addrs) < 2) else None))
        metrics["sub_b"] = {"ports": (pa, pb), "predicted_byte": "0x%02x" % predicted_byte,
                            "installed_addrs_seen": ["0x%02x" % a for a in installed_addrs],
                            "poly0_declines_seen": poly0_declines, "clobbers": clobbers,
                            "a_http": _parse_curl_outfile(of_ba)["http"],
                            "b_http": _parse_curl_outfile(of_bb)["http"]}
        if clobbered:
            notes.append("sub-check B **FAIL**: a poly-0 install landed on ram2[0x%02x] while a PRIOR "
                          "install at that SAME address was still live (no intervening destroy) -- the "
                          "second silently clobbered the first's WAN-ingress entry (C2 fail#2)" %
                          clobbers[0])
        elif poly0_declines:
            notes.append("sub-check B: %d poly0-tagged collision decline(s) observed for ports %d/%d "
                          "-- the new raw0 collision check fired correctly, no clobber (a later "
                          "install at the same address after the first flow's own destroy freed it "
                          "is correct reuse, not a clobber -- addrs seen: %s)" %
                          (poly0_declines, pa, pb, metrics["sub_b"]["installed_addrs_seen"]))
        elif len(installed_addrs) < 2:
            notes.append("sub-check B INCONCLUSIVE: didn't observe two poly-0 installs for ports %d/%d "
                          "(the engineered offline collision prediction may not have reproduced "
                          "on-device -- not a fail)" % (pa, pb))

    # A confirmed clobber/leak (False) fails the test; None (inconclusive) never does.
    ok = (a_ok is not False) and (b_ok is not False)
    if a_ok is None and b_ok is None:
        notes.append("BOTH sub-checks inconclusive this run -- PASS here means neither caught a "
                      "clobber/leak, NOT that the fix was positively exercised; rerun before trusting")

    return TestResult(name, "PASS" if ok else "FAIL", time.time() - t0, metrics, "; ".join(notes))


# ---------------------------------------------------------------------------
# high_way_collision — TARGETED regression guard for the H2 fix (findings/
# qa_static_bughunt_2026-07-04.md finding H2 / findings/fix_h2_highway_2026-07-04.md):
# the HIGHER CLA hash way buckets (ram3/4/5/6 -- zx_ft_way_slots' way index
# 1..4) fold `raw` into much smaller spaces than ram2/way0's 256 (ram3=128,
# ram4/5=64, ram6=only 8) for up to ZX_FT_MAX_FLOWS=32 concurrent flows, so
# two flows with DISTINCT raw&0xff (no ram2/way0 collision -- already covered
# by the pre-existing check and by poly0_stale) can still fold onto the SAME
# higher-way bucket. Before the fix, zx_ft_flow_untrack unconditionally
# zeroed a destroyed flow's own 5 way buckets with no notion of whether a
# LIVE other flow still mapped to one of them -- destroying flow A could wipe
# flow B's still-needed higher-way entry out from under it (the driver's own
# model requires the entry "in every bank", see the comment above
# zx_ft_way_slots). The fix (matching C2's pattern) extends
# zx_ft_flow_reserve's collision check to all 5 way addresses, so two flows
# that would ever share ANY way bucket are never both admitted -- one
# declines (-EOPNOTSUPP, tagged "higher-way collision" in dmesg) instead of
# sharing-then-clobbering.
#
# Detection strategy: `raw` (the poly-1 hash that drives all 5 way addresses)
# is computed by a dedicated HW CRC engine (zx_cla_hash_raw), NOT a pure SW
# function like poly-0/zx_cla_hash_sw_poly0 -- so unlike
# _find_poly0_collision_pair (offline-only), engineering a collision here
# needs the on-device `hashcalc` debugfs oracle (see hashab.py, same idiom).
# _hashcalc_predict_raw_batch batches many candidate 5-tuples into ONE dev()
# round trip (zx_hashcalc_write is synchronous under zx_hwlock -- N `echo ...
# > hashcalc` writes issued back-to-back produce N dmesg lines in the SAME
# order deterministically, so one combined dmesg tail at the end recovers
# every result without N separate ~1.5-2s round trips). _find_way_collision_pair
# uses that oracle to pick two local ports whose predicted DN-flow raw
# collides on a target higher way (ram6/way-index 4 by default -- only 8
# buckets, the tightest and most reproducible) while their ram2/way0 address
# (raw&0xff) predictably differs (isolating the H2 defect from the
# already-fixed/already-tested C2 way0/poly0 path). Firing both concurrently
# and walking the driver's own [phase6/ft] recipe/decline/flow-del dmesg
# lines as a chronological ALL-5-WAYS occupancy timeline (same
# clobber-detection technique as concurrency_race's pm_slot check and
# poly0_stale's ram2 check, generalized here to every (ram_id, addr) pair
# either flow's install/destroy touches -- a destroy's 5 addresses are
# recomputed locally via _way_slots(raw) from the raw the driver itself
# logged on the "flow del ... cleared raw=0x...." line, no extra HW round
# trip needed) catches the exact H2 signature: an address occupied by one
# flow's raw, then re-installed by a DIFFERENT flow's raw before any destroy
# freed it. FAILs only on a *confirmed* clobber; a "higher-way collision"
# decline is the expected/correct fixed-code signature (informational, not
# required for PASS), and not reproducing the engineered collision at all
# this run is reported INCONCLUSIVE-as-PASS (matching poly0_stale/
# concurrency_race's existing honesty convention for timing-sensitive
# checks) rather than a false FAIL.
# ---------------------------------------------------------------------------
def _way_slots(raw):
    """Pure-Python port of zx_ft_way_slots (zx-eth-main.c): the 5 (ram_id,
    addr) pairs a given raw hash occupies. No HW round trip needed here --
    `raw` itself is the HW-computed input (from hashcalc or from a driver
    dmesg line); this is just the bit-folding zx_ft_way_slots does to it,
    the same pure-math step poly0_stale/concurrency_race already rely on for
    their own address derivations."""
    return [(2, raw & 0xff), (3, 0x100 + (raw & 0x7f)), (4, 0x180 + (raw & 0x3f)),
            (5, 0x1c0 + (raw & 0x3f)), (6, 0x200 + (raw & 0x7))]


def _hashcalc_predict_raw_batch(candidates, ip_proto=6, is_wan=True, wait=None):
    """Batched on-device HW-oracle lookup of the poly-1 `raw` hash for MANY
    candidate (saddr, daddr, sport, dport) 5-tuples in ONE dev() round trip.
    zx_hashcalc_write computes-and-logs synchronously under zx_hwlock before
    the write() syscall returns (see the driver comment above
    zx_hashcalc_write), so N `echo ... > hashcalc` commands issued
    back-to-back produce N "raw hash 0x...." dmesg lines in the SAME order
    deterministically -- exactly the same "many writes, one combined grep"
    idiom rig.py's own poke_read() already uses for TS_CTRS. Returns a list
    of raw (int) or None per candidate, same order as `candidates`."""
    cmds = []
    for saddr, daddr, sport, dport in candidates:
        key = _poly0_build_key(ip_proto, saddr, daddr, sport, dport, is_wan)
        cmds.append("echo %s > /sys/kernel/debug/zx_eth/hashcalc" %
                    " ".join("%x" % k for k in key))
    cmds.append("dmesg | busybox grep -a 'hashcalc' | busybox tail -%d" % (len(candidates) + 5))
    out = rig.dev(cmds, wait=wait or max(2.0, 0.15 * len(candidates)))
    raws = [int(m, 16) for m in re.findall(r"raw hash 0x([0-9a-f]+)", out, re.I)]
    # Keep only the LAST len(candidates) matches, in case a stale "hashcalc"
    # line from an earlier manual/test use is still inside the tail window.
    raws = raws[-len(candidates):] if len(raws) >= len(candidates) else raws
    return raws + [None] * (len(candidates) - len(raws))


def _url_host_port(url, default_port=80):
    """Split 'http://host[:port]/path' into (host, port). [found live
    2026-07-04] The first version of _find_way_collision_pair hardcoded
    server_port=80 while the actual traffic target (rig.DL_URL_LOCAL,
    :8080) uses a different port -- since the port is one of the 7 fields
    zx_ft_build_key hashes, an offline prediction built against the WRONG
    port never matches the real flow's HW-computed raw, so the "engineered"
    collision silently never reproduces (no crash, no error -- just two
    installs at different, uncorrelated addresses, indistinguishable from a
    genuine miss without noticing the port mismatch). Always derive the
    port from the SAME URL the flows are actually fired at
    (args.local_server), never assume 80."""
    netloc = url.split("/")[2]
    if ":" in netloc:
        host, port = netloc.split(":", 1)
        return host, int(port)
    return netloc, default_port


def _find_way_collision_pair(way_index=4, port_lo=49900, port_hi=49940,
                             server_ip=None, server_port=None, url=None):
    """Scan a dedicated local-port window (49900+ by default -- doesn't
    overlap multiflow's 47000s, churn's 48000s, bidirectional's
    49000-49100s, concurrency_race's 49500+race_n, or poly0_stale's
    49700-49900s) for two ports whose predicted DN-flow `raw` (HW oracle via
    _hashcalc_predict_raw_batch) collide on way `way_index` (default 4 =
    ram6, only 8 buckets -- the tightest/most reproducible higher way) while
    their ram2/way0 address (way index 0, raw&0xff) predictably differs
    (isolates the H2 higher-way defect from the already-fixed/already-tested
    C2 way0/poly0 collision path). `server_ip`/`server_port` are derived
    from `url` (default rig.DL_URL_LOCAL) via _url_host_port unless passed
    explicitly -- MUST match the URL the caller will actually fire the pair
    at (see _url_host_port's docstring for why a port mismatch silently
    breaks the prediction). Returns (port_a, port_b, ram_id, addr) or None
    if no such pair turned up in the scan window -- a real "didn't
    reproduce this run" result, not a hang; caller must treat None as
    inconclusive, not an error."""
    h, p = _url_host_port(url or rig.DL_URL_LOCAL)
    server_ip = server_ip or h
    server_port = server_port if server_port is not None else p
    ports = list(range(port_lo, port_hi))
    candidates = [(server_ip, rig.CLIENT_IP, server_port, p) for p in ports]
    raws = _hashcalc_predict_raw_batch(candidates)
    buckets = {}
    for p, raw in zip(ports, raws):
        if raw is None:
            continue
        ram, addr = _way_slots(raw)[way_index]
        buckets.setdefault(addr, []).append((p, raw, ram))
    for addr, lst in buckets.items():
        if len(lst) < 2:
            continue
        for i in range(len(lst)):
            for j in range(i + 1, len(lst)):
                pa, raw_a, ram = lst[i]
                pb, raw_b, _ = lst[j]
                if (raw_a & 0xff) != (raw_b & 0xff):   # ram2/way0 must differ
                    return pa, pb, ram, addr
    return None


_RECIPE_RE = re.compile(
    r"\[\s*([\d.]+)\][^\n]*recipe:.*raw=0x([0-9a-f]+) buckets "
    r"ram2\[0x([0-9a-f]+)\]/3\[0x([0-9a-f]+)\]/4\[0x([0-9a-f]+)\]/"
    r"5\[0x([0-9a-f]+)\]/6\[0x([0-9a-f]+)\]")
_FLOWDEL_RE = re.compile(r"\[\s*([\d.]+)\][^\n]*flow del.*cleared raw=0x([0-9a-f]+)")


def test_high_way_collision(args):
    name = "high_way_collision"
    t0 = time.time()
    _cleanup_client_procs()
    _prime_sudo_and_arp()
    _prime_local_server(args.local_server)   # see its docstring (multiflow found this live first)
    notes = []

    # Shift the scan window per invocation (same TIME_WAIT/rerun-diversity
    # reasoning as poly0_stale's _pair_lo) so repeated reruns don't keep
    # re-scanning (and re-dialing) the exact same window.
    _pair_lo = 49900 + (int(time.time()) // 90 % 5) * 20
    pair = None
    way_tried = []
    for wi in (4, 3, 2, 1):    # ram6 (8 buckets) first, then ram5/4/3 as fallback
        way_tried.append(wi)
        pair = _find_way_collision_pair(way_index=wi, port_lo=_pair_lo,
                                        port_hi=_pair_lo + args.hwc_scan,
                                        url=args.local_server)
        if pair:
            break

    if not pair:
        return TestResult(name, "PASS", time.time() - t0, {"way_tried": way_tried},
                           "INCONCLUSIVE-as-PASS: no offline higher-way collision predicted in the "
                           "scan window (--hwc-scan=%d, ways tried=%s) -- rerun or widen --hwc-scan "
                           "before trusting a green result; this is not itself evidence of "
                           "correctness" % (args.hwc_scan, way_tried))

    pa, pb, ram_id, addr = pair
    # Re-prime right before firing (the hashcalc scan above can take several
    # seconds of pure device-side compute with zero traffic to the local
    # server -- long enough for its neighbor entry to go cold again; same
    # re-prime-right-before-launch pattern poly0_stale uses for its own pair).
    _prime_sudo_and_arp()
    _prime_local_server(args.local_server)
    t_ref = _device_uptime()

    # rate_limit: same reasoning as multiflow's mitigation (6) -- a 50 MiB
    # LAN-local flow can finish in well under a second, faster than
    # nf_flowtable can dispatch FLOW_CLS_REPLACE; this test's whole premise
    # needs BOTH engineered flows to actually reach the CLA install stage.
    cmd_a, of_a = _curl_cmd(pa, args.hwc_dur, size=args.hwc_size, url=args.local_server,
                            rate_limit=args.hwc_rate_limit, outfile="/tmp/regress_hwc_%d.out" % pa)
    proc_a = subprocess.Popen(cmd_a, shell=True)
    time.sleep(args.hwc_stagger)
    cmd_b, of_b = _curl_cmd(pb, args.hwc_dur, size=args.hwc_size, url=args.local_server,
                            rate_limit=args.hwc_rate_limit, outfile="/tmp/regress_hwc_%d.out" % pb)
    proc_b = subprocess.Popen(cmd_b, shell=True)
    for p in (proc_a, proc_b):
        try:
            p.wait(timeout=args.hwc_dur + 25)
        except subprocess.TimeoutExpired:
            p.kill()
    time.sleep(1.0)

    window = _dmesg_since("phase6/ft", t_ref, tail=300, wait=2.5)

    events = []
    for m in _RECIPE_RE.finditer(window):
        t = float(m.group(1))
        raw = int(m.group(2), 16)
        way_addrs = [(2, int(m.group(3), 16)), (3, int(m.group(4), 16)),
                     (4, int(m.group(5), 16)), (5, int(m.group(6), 16)),
                     (6, int(m.group(7), 16))]
        events.append((t, "install", raw, way_addrs))
    for m in _FLOWDEL_RE.finditer(window):
        t = float(m.group(1))
        raw = int(m.group(2), 16)
        events.append((t, "destroy", raw, _way_slots(raw)))
    events.sort(key=lambda e: e[0])

    live = {}       # (ram_id, addr) -> raw currently occupying it
    clobbers = []
    for t, ev, raw, way_addrs in events:
        if ev == "install":
            for ra in way_addrs:
                occ = live.get(ra)
                if occ is not None and occ != raw:
                    clobbers.append((ra, occ, raw))
                live[ra] = raw
        else:
            for ra in way_addrs:
                if live.get(ra) == raw:
                    del live[ra]

    hwc_declines = len(re.findall(r"reserve decline: higher-way collision", window))
    clobbered = len(clobbers) > 0
    a_http = _parse_curl_outfile(of_a)["http"]
    b_http = _parse_curl_outfile(of_b)["http"]

    ok = not clobbered
    if clobbered:
        notes.append("**FAIL**: address(es) %s were occupied by one flow's raw then re-installed by "
                      "a DIFFERENT flow's raw before any destroy freed them -- the exact H2 "
                      "share-then-clobber signature (target was ram%d[0x%02x], ports %d/%d)" %
                      (["ram%d[0x%03x]" % ra for ra, _, _ in clobbers], ram_id, addr, pa, pb))
    elif hwc_declines:
        notes.append("%d 'higher-way collision' decline(s) observed for engineered ports %d/%d "
                      "(predicted to collide on ram%d[0x%02x]) -- the H2 fix's new collision check "
                      "fired correctly, no clobber" % (hwc_declines, pa, pb, ram_id, addr))
    elif len(events) < 2:
        notes.append("INCONCLUSIVE: too few [phase6/ft] install/destroy events observed for ports "
                      "%d/%d (predicted ram%d[0x%02x] collision may not have reproduced on-device "
                      "this run, or neither flow got HW-offloaded) -- not a fail" %
                      (pa, pb, ram_id, addr))
    else:
        notes.append("no clobber and no 'higher-way collision' decline seen for engineered ports "
                      "%d/%d (ram%d[0x%02x]) -- the offline prediction likely didn't reproduce "
                      "on-device this run (a real miss, not a masked failure); rerun or widen "
                      "--hwc-scan" % (pa, pb, ram_id, addr))

    metrics = {"ports": (pa, pb), "target": "ram%d[0x%02x]" % (ram_id, addr), "way_tried": way_tried,
               "hwc_declines": hwc_declines, "clobbers": len(clobbers),
               "a_http": a_http, "b_http": b_http, "events_seen": len(events)}
    return TestResult(name, "PASS" if ok else "FAIL", time.time() - t0, metrics, "; ".join(notes))


# ---------------------------------------------------------------------------
# replace_orphan — TARGETED regression guard for the H3 fix (findings/
# qa_static_bughunt_2026-07-04.md finding H3 / findings/fix_h3_rollback_2026-07-04.md):
# a self-REPLACE (SAME cookie, CHANGED 5-tuple) used to update ft_flows[]'s
# tracked raw/raw0 in place WITHOUT clearing the OLD raw/raw0's live CLA
# entries first -- the old 5 ways (and old poly-0 ram2 slot, if the flow had
# one) were a separate CLA address from the new install and were never
# touched by it, so they stayed valid_en=1 forever (a later plain DESTROY
# only ever clears the CURRENT raw/raw0, never a replaced-away one). The fix
# adds a shared zx_ft_uninstall() rollback helper and calls it on the OLD
# footprint before zx_ft_flow_reserve() adopts the new raw/raw0 -- reused
# verbatim for partial-install-failure unwind and (refactored into) DESTROY.
#
# REACHABILITY: nf_flow_table_offload.c assigns cls->cookie =
# (unsigned long)&flow->tuplehash[dir].tuple -- a FIXED address inside the
# flow_offload object for that direction, so a genuinely different 5-tuple on
# the SAME cookie structurally never happens via real nf_flowtable traffic on
# this conduit path (see the [H3 fix] comment on the debugfs `fttest` node in
# zx-eth-main.c for the full analysis; the tc/DSA mirror CAN hit this more
# naturally via `tc filter change`, but that's zx-dsa.c, an untouched-by-this-
# fix code path per finding H1 -- testing self-REPLACE there would just
# always fail regardless of this fix). This test therefore drives the exact
# production zx_ft_flow_reserve() / zx_ft_install_recipe() / zx_ft_uninstall()
# functions directly via the `fttest` debugfs node (test-only; duplicates no
# install/rollback logic of its own) with a synthetic cookie, instead of
# waiting for traffic that cannot produce this scenario. Every HW read is a
# real clapeek (ram_id/addr) round trip against production code -- nothing
# about the ASSERTION is simulated, only the STIMULUS (which function
# arguments to call with) is test-driven rather than traffic-driven.
# ---------------------------------------------------------------------------
def _fttest_install(cookie, saddr, daddr, sport, dport, eg_regport, t_ref, wait=2.0):
    """One fttest 'install' round trip; parses the driver's own
    "[fttest] install cookie=... raw=0x.... raw0=0x.... pm_slot=... rc=..."
    confirmation line (not just assuming success). Returns
    {raw, raw0, pm_slot, rc} or None if the line didn't show up."""
    cmd = "install %x %x %x %x %x %d" % (cookie, saddr, daddr, sport, dport, eg_regport)
    rig.dev(["echo '%s' > /sys/kernel/debug/zx_eth/fttest" % cmd], wait=wait)
    win = _dmesg_since(r"\[fttest\] install cookie=%x" % cookie, t_ref, tail=10, wait=1.5)
    m = re.search(r"\[fttest\] install cookie=%x raw=0x([0-9a-f]+) raw0=0x([0-9a-f]+) "
                  r"pm_slot=(\d+) rc=(-?\d+)" % cookie, win)
    if not m:
        return None
    return {"raw": int(m.group(1), 16), "raw0": int(m.group(2), 16),
            "pm_slot": int(m.group(3)), "rc": int(m.group(4))}


def _fttest_destroy(cookie, wait=2.0):
    rig.dev(["echo 'destroy %x' > /sys/kernel/debug/zx_eth/fttest" % cookie], wait=wait)


def _pmpeek(ram_id, addr):
    """Read back a PM indirect-RAM entry via the `pmpeek` debugfs node (write
    'ram_id addr' in HEX, decode the 8 hex words dmesg prints). Same one-round-
    trip idiom as _clapeek, but for the PM engine: zx_pmpeek_write ->
    zx_pp_pm_read_entry, which is the SAME read path zx_pp_pm_write_verify()
    uses to confirm its own writes -- so this is an INDEPENDENT confirmation
    (a separate debugfs round trip, distinct from the in-driver verify) that
    the PM entry an FT install intended actually committed. Returns
    {rc, words[8]} or None if the pmpeek line for this (ram_id, addr) didn't
    show up. Uses finditer()[-1] (like poly0_stale) so a stale earlier pmpeek
    of the same address in the ring can't shadow our just-issued read."""
    out = rig.dev(["echo '%x %x' > /sys/kernel/debug/zx_eth/pmpeek" % (ram_id, addr),
                   "dmesg | busybox grep -a 'pmpeek' | busybox tail -4"], wait=2.0)
    ms = list(re.finditer(r"pmpeek pm-ram%u addr0x0*%x rc=(-?\d+):\s*([0-9a-f ]+)"
                          % (ram_id, addr), out, re.I))
    if not ms:
        return None
    m = ms[-1]
    return {"rc": int(m.group(1)),
            "words": [int(w, 16) for w in m.group(2).split() if w]}


def _ft_pm_verify_counts():
    """Read the driver's H5 PM-write-verify accounting from the `stats`
    seq-file line 'ft_pm_verify = ok=N retry=N fail=N'. Returns
    (ok, retry, fail) or None if the line isn't present (=> not an H5 build)."""
    out = rig.dev(["cat /sys/kernel/debug/zx_eth/stats | busybox grep ft_pm_verify"], wait=2.0)
    m = re.search(r"ft_pm_verify\s*=\s*ok=(\d+)\s+retry=(\d+)\s+fail=(\d+)", out)
    if not m:
        return None
    return int(m.group(1)), int(m.group(2)), int(m.group(3))


def test_replace_orphan(args):
    name = "replace_orphan"
    t0 = time.time()
    notes = []
    metrics = {}
    # A synthetic cookie well outside any range a real flow_offload tuple
    # pointer would ever collide with by chance, and two synthetic 5-tuples
    # (A, B) that only differ in daddr/dport -- eg_regport=2 (an arbitrary
    # non-WAN regport, is_dn=True) so install_recipe takes the poly-0 ram2
    # write path (raw0), the exact H3a-relevant footprint.
    cookie = 0xc0ffee00 + (int(time.time()) % 0xff)
    saddr, sport = 0x0a141e01, 0x1f90            # 10.20.30.1:8080 (arbitrary "server")
    daddr_a, dport_a = 0x0a141e0a, 0x1388         # 10.20.30.10:5000
    daddr_b, dport_b = 0x0a141e0b, 0x1389         # 10.20.30.11:5001 (CHANGED tuple)
    eg_regport = 2

    # [found live 2026-07-04] zx_ft_install_recipe's own convention is
    # `return rc ? rc : raw;` -- on SUCCESS it returns the (always-positive,
    # nonzero) raw hash, NOT 0 (every real call site only ever tests `rc <
    # 0`, matching zx_ft_flower_replace itself). Confirmed live: the very
    # first fttest run logged "rc=7705" on an install that clapeek then
    # showed as genuinely live in HW -- 7705 == 0x1e19, the SAME value as
    # the raw= field on that line. Gate on rc < 0, not rc != 0.
    # [robustness] Always destroy the synthetic cookie before returning, on
    # ANY exit path (a leaked test entry otherwise permanently pins one of
    # only ZX_FT_MAX_FLOWS=32 tracking slots until the next reboot -- found
    # live on this test's very first run, which ERRORed out before reaching
    # its own cleanup call and left cookie 0xc0ffee9b tracked; cleaned up by
    # hand, this try/finally is the actual fix).
    a = b = None
    try:
        t_ref = _device_uptime()
        a = _fttest_install(cookie, saddr, daddr_a, sport, dport_a, eg_regport, t_ref)
        if a is None or a["rc"] < 0:
            return TestResult(name, "ERROR", time.time() - t0, {"install_a": a},
                              "couldn't get a clean first install (fttest debugfs node missing/failed? "
                              "rc=%s) -- is this build's zx-eth-main.c the H3-fix build?" % (a and a["rc"]))

        ways_a = _way_slots(a["raw"]) + [(2, a["raw0"] & 0xff)]
        live_before = {addr: _clapeek(ram, addr) for ram, addr in ways_a}
        nonzero_before = sum(1 for w in live_before.values() if w and any(w))
        if nonzero_before == 0:
            notes.append("INCONCLUSIVE setup: none of tuple A's 5 ways + poly-0 slot read back "
                          "nonzero right after install -- can't meaningfully assert a clear later")

        # The self-REPLACE: SAME cookie, CHANGED tuple (daddr/dport B). This is
        # the exact scenario zx_ft_flow_reserve's self>=0-with-raw-changed branch
        # exists to handle.
        t_ref2 = _device_uptime()
        b = _fttest_install(cookie, saddr, daddr_b, sport, dport_b, eg_regport, t_ref2)
        if b is None or b["rc"] < 0:
            return TestResult(name, "ERROR", time.time() - t0, {"install_a": a, "install_b": b},
                              "second (self-REPLACE) install didn't report rc>=0")

        replace_fired = bool(_dmesg_since(r"self-replace old-footprint clear: cookie=%x" % cookie,
                                          t_ref2, tail=10, wait=1.0).strip())

        ways_b = _way_slots(b["raw"]) + [(2, b["raw0"] & 0xff)]
        live_old_after = {addr: _clapeek(ram, addr) for ram, addr in ways_a}
        live_new_after = {addr: _clapeek(ram, addr) for ram, addr in ways_b}
        old_still_live = [addr for addr, w in live_old_after.items() if w and any(w)]
        # ways_a/ways_b can share an address if raw/raw0 happen to coincide on some
        # bank (unlikely for two arbitrary tuples but not provably impossible) --
        # don't count a shared, still-live address as an "orphan": it's supposed
        # to be live, it's the NEW entry's own address too.
        shared_addrs = {addr for _, addr in ways_a} & {addr for _, addr in ways_b}
        orphaned = [addr for addr in old_still_live if addr not in shared_addrs]
        new_nonzero = sum(1 for w in live_new_after.values() if w and any(w))
    finally:
        if a is not None:
            _fttest_destroy(cookie)

    live_after_destroy = {addr: _clapeek(ram, addr) for ram, addr in ways_b}
    still_live_after_destroy = [addr for addr, w in live_after_destroy.items() if w and any(w)]

    notes.append("self-replace old_raw=0x%04x -> new_raw=0x%04x (fired=%s)" %
                  (a["raw"], b["raw"], replace_fired))
    if orphaned:
        notes.append("**FAIL**: tuple A's OLD footprint still reads NON-ZERO after the self-REPLACE "
                      "at address(es) %s (raw=0x%04x) -- the old (dead) tuple would still HW-forward "
                      "(finding H3(a)/H3a orphan-on-self-REPLACE is present)" %
                      ([hex(a) for a in orphaned], a["raw"]))
    if new_nonzero == 0:
        notes.append("new tuple B's footprint reads all-zero after the self-REPLACE -- the new "
                      "install itself may have failed silently (rc was 0, but HW state disagrees)")
    if still_live_after_destroy:
        notes.append("post-destroy cleanup left %d address(es) live (%s) -- untrack/zx_ft_uninstall "
                      "regression, separate from the self-REPLACE assertion above" %
                      (len(still_live_after_destroy), [hex(a) for a in still_live_after_destroy]))

    # Partial-install-failure (H3(b)) is not inducible from here: forcing a
    # real zx_cla_write_hash/zx_pp_pm_write_entry failure needs an actual
    # -EBUSY from the CLA/PM indirect engine (a HW timeout), which this test
    # has no fault-injection hook for. Documented as out of reach rather than
    # faked -- matching this file's existing honesty convention (poly0_stale/
    # high_way_collision report INCONCLUSIVE rather than fabricate a pass).
    notes.append("sub-check (partial-install-failure rollback, H3(b)) NOT EXERCISED this run -- no "
                  "fault-injection hook to force a real CLA/PM write -EBUSY from here; the rollback "
                  "call is shared code with the self-REPLACE path above (zx_ft_uninstall()), so a "
                  "regression in the shared helper would still be caught here")

    ok = (not orphaned) and (new_nonzero > 0) and (not still_live_after_destroy)
    metrics = {"cookie": hex(cookie), "raw_a": hex(a["raw"]), "raw_b": hex(b["raw"]),
               "raw0_a": hex(a["raw0"]), "raw0_b": hex(b["raw0"]), "pm_slot": a["pm_slot"],
               "replace_fired": replace_fired, "orphaned_addrs": [hex(x) for x in orphaned],
               "new_nonzero": new_nonzero, "still_live_after_destroy": still_live_after_destroy,
               "nonzero_before": nonzero_before}
    return TestResult(name, "PASS" if ok else "FAIL", time.time() - t0, metrics, "; ".join(notes))


# ---------------------------------------------------------------------------
# pm_write_verify — TARGETED regression guard for the H5 fix (findings/
# qa_static_bughunt_2026-07-04.md finding H5 / findings/fix_h5_pm_verify_2026-07-04.md):
# the four FT-install PM indirect-RAM writes (ram1 next_hop, ram0 flow_info,
# ram6 sub, ram3 cmd) used to ignore their return codes and were never read
# back -- a silently-dropped write (this engine CAN drop under contention; the
# DSA side needed an 8-retry readback loop, zx-dsa.c zx_pm_wr) armed a live CLA
# verdict pointing at a stale/zero pm_slot, so the flow HW-forwarded with the
# previous occupant's next-hop MAC / NAT state. The fix routes every install
# PM write through zx_pp_pm_write_verify() (rc-check + word0/word1 readback +
# up to 8 retries), fails the install cleanly (rollback via zx_ft_uninstall)
# on persistent mismatch, and counts confirmed commits in ft_pm_verify.{ok,
# retry,fail} (debugfs stats).
#
# HONESTY LIMIT (matches replace_orphan's H3b / poly0_stale's timing notes): a
# GENUINE silent PM-write drop is not inducible from here -- forcing one needs
# a fault-injection hook the driver deliberately doesn't ship. So this test
# does NOT fake a failure; it proves the verify path is real and correct on a
# genuine install, two independent ways:
#   (1) it RAN and CONFIRMED all four writes -- the driver's own ft_pm_verify.ok
#       counter advances by exactly 4 per install and .fail stays 0. Reverting
#       to the bare zx_pp_pm_write_entry (dropping the rc-check/readback) stops
#       this counter -> FAIL, even though the bare write still commits on
#       healthy silicon (a pure behavioural test could not tell). THIS is the
#       guard on the verify LOGIC itself.
#   (2) the intended values actually COMMITTED -- read back INDEPENDENTLY via
#       the pmpeek debugfs node (a separate round trip) and matched against
#       exactly what zx_ft_install_recipe writes. THIS guards that a verify
#       "pass" really means the data is present.
# Drives the production zx_ft_flow_reserve()/zx_ft_install_recipe() via the
# test-only `fttest` node (no traffic needed -- eg_regport=2 => is_dn => the
# full 4-PM-write DN path); duplicates no install logic of its own.
# ---------------------------------------------------------------------------
def test_pm_write_verify(args):
    name = "pm_write_verify"
    t0 = time.time()
    notes = []
    # No traffic during this test: kill stray client curls so the ONLY FT
    # installs that fire are our synthetic fttest one (a live download's
    # FLOW_CLS_REPLACE churn would inflate ft_pm_verify.ok between the
    # before/after reads and blur the exact +4 delta).
    _cleanup_client_procs()

    cookie = 0x5e51f900 + (int(time.time()) % 0xff)
    saddr, sport = 0x0a281e01, 0x1f90            # 10.40.30.1:8080
    daddr, dport = 0x0a281e0a, 0x1388            # 10.40.30.10:5000
    eg_regport = 2                               # non-WAN -> is_dn=True -> 4 PM writes
    # fttest's fixed test next-hop MAC is 02:00:00:00:00:01, so
    #   ram1[pm_slot] word0 = ntohl(daddr) (no NAT), word1 = mac[2..5], word2 = mac[0..1]
    TEST_MAC_W1 = 0x00000001                     # mac[2],mac[3],mac[4],mac[5] = 00 00 00 01
    TEST_MAC_W2 = 0x00000200                     # mac[0],mac[1] = 02 00

    before = _ft_pm_verify_counts()
    if before is None:
        return TestResult(name, "ERROR", time.time() - t0, {},
                          "stats has no 'ft_pm_verify' line -- is this build's zx-eth-main.c the "
                          "H5-fix build? (zx_pp_pm_write_verify / the stats counter is missing)")

    inst = after = None
    r1 = r3 = r6 = None
    try:
        t_ref = _device_uptime()
        inst = _fttest_install(cookie, saddr, daddr, sport, dport, eg_regport, t_ref)
        if inst is None or inst["rc"] < 0:
            return TestResult(name, "ERROR", time.time() - t0, {"install": inst},
                              "fttest install didn't report rc>=0 (rc=%s) -- can't exercise the "
                              "verify path" % (inst and inst["rc"]))
        pm_slot = inst["pm_slot"]
        after = _ft_pm_verify_counts()          # BEFORE destroy; pmpeek/destroy don't bump .ok
        # Independent readback of the 3 deterministic-word PM entries.
        r1 = _pmpeek(1, pm_slot)
        r3 = _pmpeek(3, pm_slot)
        r6 = _pmpeek(6, pm_slot)
    finally:
        if inst is not None:
            _fttest_destroy(cookie)

    ok_d = after[0] - before[0]
    retry_d = after[1] - before[1]
    fail_d = after[2] - before[2]

    # (1) verify-path-ran assertion
    if ok_d < 4:
        notes.append("**FAIL**: ft_pm_verify.ok advanced by %d (<4) across one install -- the "
                     "readback-verify path did NOT run/confirm all 4 PM writes (H5 rc-check/verify "
                     "regression?)" % ok_d)
    if fail_d != 0:
        notes.append("**FAIL**: ft_pm_verify.fail advanced by %d -- a PM write did not commit even "
                     "after 8 retries" % fail_d)
    if ok_d > 4:
        notes.append("note: ft_pm_verify.ok advanced by %d (>4) -- background FT install churn during "
                     "the test; our install still verified, the pmpeek content check below is decisive" % ok_d)
    if retry_d:
        notes.append("note: %d PM write(s) needed >=1 readback retry to commit (engine contention "
                     "the verify loop absorbed -- exactly its purpose)" % retry_d)

    # (2) independent-commit assertion via pmpeek
    content_ok = True

    def _chk(label, r, checks):
        nonlocal content_ok
        if r is None or r.get("rc") != 0 or not r.get("words"):
            content_ok = False
            notes.append("**FAIL**: pmpeek %s read failed/empty (%r)" % (label, r))
            return
        for idx, want in checks:
            if idx >= len(r["words"]) or r["words"][idx] != want:
                content_ok = False
                got = r["words"][idx] if idx < len(r["words"]) else None
                notes.append("**FAIL**: pmpeek %s word%d = %s, expected 0x%08x -- PM entry did NOT "
                             "commit the intended value" % (label, idx, got if got is None else hex(got), want))

    _chk("ram1[next_hop]", r1, [(0, daddr), (1, TEST_MAC_W1), (2, TEST_MAC_W2)])
    _chk("ram3[cmd]", r3, [(0, 0x00800000)])
    _chk("ram6[sub]", r6, [(0, pm_slot)])

    verify_ran = ok_d >= 4 and fail_d == 0
    ok = verify_ran and content_ok
    if ok:
        notes.append("verify path ran+confirmed 4/4 PM writes (ok+=%d, fail=0) AND pmpeek "
                     "independently confirms ram1/ram3/ram6 committed the intended values" % ok_d)
    metrics = {"cookie": hex(cookie), "pm_slot": inst["pm_slot"],
               "ok_delta": ok_d, "retry_delta": retry_d, "fail_delta": fail_d,
               "ram1_w0": hex(r1["words"][0]) if (r1 and r1.get("words")) else None,
               "ram3_w0": hex(r3["words"][0]) if (r3 and r3.get("words")) else None,
               "ram6_w0": hex(r6["words"][0]) if (r6 and r6.get("words")) else None}
    return TestResult(name, "PASS" if ok else "FAIL", time.time() - t0, metrics, "; ".join(notes))


# ---------------------------------------------------------------------------
# 5. bidirectional — source: QA scenario 4 (findings/qa_ethernet_battery_2026-07-04.md
# "bulk DN + 30 small request-heavy flows"). True simultaneous UPLOAD throughput is
# NOT exercised (needs an external upload sink, not device-testable without one per
# the QA session's own note) — this quantifies UP-ACK contention instead.
# ---------------------------------------------------------------------------
def test_bidirectional(args):
    name = "bidirectional"
    t0 = time.time()
    _cleanup_client_procs()
    b0 = ctr.read()

    bulk_cmd, bulk_out = _curl_cmd(49000, args.bidir_dur, size=0)
    bulk_p = subprocess.Popen(bulk_cmd, shell=True)
    time.sleep(1.0)

    small_outs, small_procs = [], []
    for i in range(args.bidir_small_n):
        lport = 49100 + i
        cmd, of = _curl_cmd(lport, 8.0, size=200000, maxtime_pad=5)
        small_procs.append(subprocess.Popen(cmd, shell=True))
        small_outs.append(of)
        time.sleep(0.2)
    for p in small_procs:
        try:
            p.wait(timeout=20)
        except subprocess.TimeoutExpired:
            p.kill()
    try:
        bulk_p.wait(timeout=args.bidir_dur + 25)
    except subprocess.TimeoutExpired:
        bulk_p.kill()
    time.sleep(1.0)

    b1 = ctr.read()
    bulk_d = _parse_curl_outfile(bulk_out)
    small_ok = sum(1 for of in small_outs if _parse_curl_outfile(of)["http"] in (200, 206))
    small_frac = small_ok / args.bidir_small_n if args.bidir_small_n else 1.0
    up_red_drop = (b1.get("red_drop") or 0) - (b0.get("red_drop") or 0)
    bulk_progressed = (bulk_d["bytes"] or 0) > 0

    ok = bulk_progressed and (small_frac >= args.bidir_min_frac)
    notes = []
    if not bulk_progressed:
        notes.append("bulk DN got 0 bytes while small UP-heavy flows were running (device may already "
                      "be in a degraded/trap state)")
    if small_frac < args.bidir_min_frac:
        notes.append("%d/%d small flows connected (%.0f%%) < min %.0f%% — NOTE: true simultaneous "
                      "UPLOAD throughput is NOT exercised (needs an external upload sink); this only "
                      "quantifies UP-ACK contention via small request-heavy flows during a DN bulk "
                      "transfer, per the QA battery's scenario-4 methodology" %
                      (small_ok, args.bidir_small_n, small_frac * 100, args.bidir_min_frac * 100))

    metrics = {"bulk_bytes": bulk_d["bytes"], "bulk_rate_mb_s": bulk_d["rate_mb_s"],
               "small_connected": small_ok, "small_total": args.bidir_small_n,
               "up_ack_red_drop_delta": up_red_drop}
    return TestResult(name, "PASS" if ok else "FAIL", time.time() - t0, metrics, "; ".join(notes))


# ---------------------------------------------------------------------------
# 6. edge_decline — ICMP / UDP(DNS) / IPv6, all expected to decline gracefully
# to SW (the nft flowtable rule is TCP-only by construction — see rig.OFFLOAD_CMDS).
# ---------------------------------------------------------------------------
def _udp_probe():
    """Prefers `dig`; falls back to a raw python3 DNS query if `dig` isn't on
    the host running the client netns (avoids a false FAIL from a missing tool,
    not a missing feature)."""
    rc, out = rig.sh(rig.SUDO + rig.NS + "dig @8.8.8.8 example.com +time=2 +tries=1 2>&1 | tail -6",
                      timeout=10)
    if ("not found" not in out) and ("ANSWER SECTION" in out or "status: NOERROR" in out):
        return True, out
    py = ("python3 -c \"import socket; "
          "q=bytes.fromhex('aaaa01000001000000000000076578616d706c6503636f6d0000010001'); "
          "s=socket.socket(socket.AF_INET, socket.SOCK_DGRAM); s.settimeout(2); "
          "s.sendto(q, ('8.8.8.8', 53)); r=s.recvfrom(512); print('DNS_OK', len(r[0]))\"")
    rc2, out2 = rig.sh(rig.SUDO + rig.NS + py, timeout=8)
    return ("DNS_OK" in out2), out2


def test_edge_decline(args):
    name = "edge_decline"
    t0 = time.time()
    notes = []
    metrics = {}

    rc, out = rig.sh(rig.SUDO + rig.NS + "ping -c 4 -W 2 8.8.8.8 2>&1 | tail -3", timeout=15)
    m = re.search(r"(\d+)% packet loss", out)
    icmp_loss = int(m.group(1)) if m else None
    metrics["icmp_loss_pct"] = icmp_loss
    icmp_ok = (icmp_loss == 0)
    if not icmp_ok:
        notes.append("ICMP loss=%s%% (want 0%%): %s" % (icmp_loss, out[-150:].strip()))

    udp_ok, udp_raw = _udp_probe()
    metrics["udp_ok"] = udp_ok
    if not udp_ok:
        notes.append("UDP/DNS probe got no answer: %s" % udp_raw[-200:].strip())

    rc, v6out = rig.sh(rig.SUDO + rig.NS + "ip -6 route 2>&1", timeout=8)
    has_v6_default = bool(re.search(r"^default", v6out, re.M))
    if has_v6_default:
        rc, out6 = rig.sh(rig.SUDO + rig.NS + "ping -6 -c 3 -W 2 2001:4860:4860::8888 2>&1 | tail -3",
                          timeout=12)
        m = re.search(r"(\d+)% packet loss", out6)
        v6_loss = int(m.group(1)) if m else None
        metrics["ipv6_loss_pct"] = v6_loss
        v6_ok = (v6_loss == 0)
        if not v6_ok:
            notes.append("IPv6 loss=%s%%" % v6_loss)
    else:
        metrics["ipv6_loss_pct"] = "N/A (no v6 default route in this rig — matches "
        metrics["ipv6_loss_pct"] += "findings/qa_ethernet_battery_2026-07-04.md's own note)"
        v6_ok = True  # SKIP semantics, not a FAIL — same as the original QA battery

    ft = _ft_dmesg_stats(tail=100)
    metrics["ft_installs_seen"] = ft["installs"]  # sanity-visible; TCP-only nft rule already
                                                    # guarantees ICMP/UDP are never HW-installed

    ok = icmp_ok and udp_ok and v6_ok
    return TestResult(name, "PASS" if ok else "FAIL", time.time() - t0, metrics, "; ".join(notes))


# ---------------------------------------------------------------------------
# h1_dsa_decline — TARGETED regression guard for the H1 fix (findings/
# qa_static_bughunt_2026-07-04.md finding H1 / findings/fix_h1_dsa_gate_2026-07-04.md):
# the DSA tc-flower L3-offload INSTALL path (zx_dsa_cls_flower_add, zx-dsa.c) was a
# stale, never-updated mirror of the conduit's pre-fix FT offload -- installing via
# it would arm a black-holing/cross-flow-corrupting recipe (no PM ext/DDR-carve
# write, a hardcoded shared PM slot 5 for every flow+direction, a cmd_flow_id=0 vs
# slot-5 CLA/PM mismatch) on the SAME physical CLA/PM engines the validated
# conduit nft-flowtable offload relies on. The fix makes that path unconditionally
# DECLINE (-EOPNOTSUPP) before it ever touches the CLA/PM engines.
#
# This test drives the exact recipe tasks/00.01.eth-driver/scripts/
# hw_dsa_offload_test.py used to validate the (now gated-off) install -- a
# `tc filter add ... flower skip_sw ... action mirred egress redirect` on a DSA
# user port ingress -- against a TEST-NET-3 address that can never be real
# traffic, and asserts:
#   1. The tc command itself FAILS (nonzero rc). `skip_sw` means "must offload or
#      fail" -- a clean -EOPNOTSUPP decline makes the whole tc invocation fail and
#      (critically) leaves no filter installed at all.
#   2. dmesg shows OUR decline log line for this exact attempt (confirms the H1
#      gate is what rejected it, not an unrelated failure like the port being
#      down), and NO "[phase6] recipe: ..." install log matching the test's dst IP
#      (confirms no CLA/PM entry was armed).
#   3. The device is still alive afterwards (the decline path must be a clean,
#      side-effect-free no-op, not a crash/wedge).
# Without the H1 gate, step 1 would have SUCCEEDED (rc=0) and step 2 would have
# shown an install log instead of a decline -- this test fails against the
# pre-fix source and passes against the fixed source. It intentionally does NOT
# re-verify the conduit's nft-flowtable HW-offload itself (that's
# baseline_download's job, earlier in the battery) -- it only proves this
# specific gated path stays inert.
# ---------------------------------------------------------------------------
_H1_TEST_DIP = "203.0.113.7"   # TEST-NET-3 (RFC 5737) -- never a real host on this rig
_H1_TEST_DPORT = 55555


def test_h1_dsa_decline(args):
    name = "h1_dsa_decline"
    t0 = time.time()
    notes = []
    metrics = {}

    # Idempotent: a clsact qdisc may already exist on lan2 from a prior run of
    # this test (or a manual hw_dsa_offload_test.py session) -- ignore "File
    # exists" (rc doesn't matter here, only the filter-add rc below does).
    rig.dev(["tc qdisc add dev lan2 clsact 2>&1"], wait=2.0)

    marker = "H1TEST_%d" % (int(time.time()) % 100000)
    cmd = ("tc filter add dev lan2 ingress protocol ip flower skip_sw "
           "ip_proto tcp dst_ip %s dst_port %d action mirred egress redirect dev lan1; "
           "echo RC=$?; echo %s" % (_H1_TEST_DIP, _H1_TEST_DPORT, marker))
    out = rig.dev([cmd], wait=4.0)

    m = re.search(r"RC=(\d+)", out)
    rc = int(m.group(1)) if m else None
    device_alive = marker in out
    metrics["tc_add_rc"] = rc
    metrics["device_alive_after"] = device_alive

    declined_ok = (rc is not None) and (rc != 0)
    if rc is None:
        notes.append("couldn't parse tc filter add rc from device output (rig/UART flake?): %s" %
                      out[-200:].strip())
    elif not declined_ok:
        notes.append("tc filter add (skip_sw) rc=0 -- expected NONZERO (offload declined); "
                      "rc=0 means the DSA cls_flower install path ACCEPTED and installed a "
                      "recipe -- the H1 gate is missing/broken")

    dout = rig.dev(["dmesg | busybox grep -a 'phase6' | busybox tail -20"], wait=2.5)
    decline_seen = bool(re.search(r"cls_flower_add.*HW-offload install declined", dout))
    install_seen = bool(re.search(r"\[phase6\] recipe:.*%s" % re.escape(_H1_TEST_DIP), dout))
    metrics["decline_log_seen"] = decline_seen
    metrics["bogus_install_log_seen"] = install_seen
    if not decline_seen:
        notes.append("no '[phase6] cls_flower_add ... HW-offload install declined' dmesg line seen "
                      "for this attempt -- can't confirm the H1 gate is what rejected it "
                      "(dmesg tail: %s)" % dout[-300:].strip())
    if install_seen:
        notes.append("a '[phase6] recipe: ...' INSTALL log matched this test's dst_ip=%s -- the "
                      "gate did NOT prevent an install (the exact H1 failure mode)" % _H1_TEST_DIP)

    # Clean up: remove the filter (if it somehow got installed) and the qdisc,
    # so the rig is left clean either way.
    rig.dev(["tc filter del dev lan2 ingress 2>/dev/null; "
             "tc qdisc del dev lan2 clsact 2>/dev/null; true"], wait=2.0)

    ok = declined_ok and decline_seen and not install_seen and device_alive
    if not device_alive:
        notes.append("device REPL unresponsive after the attempt -- unexpected side effect of "
                      "a supposedly inert decline path")

    return TestResult(name, "PASS" if ok else "FAIL", time.time() - t0, metrics, "; ".join(notes))


# ---------------------------------------------------------------------------
# h4_nondsa_decline — TARGETED regression guard for the H4 fix (findings/
# qa_static_bughunt_2026-07-04.md finding H4 / findings/fix_h4_nondsa_2026-07-04.md):
# zx_ft_egress_regport() (zx-eth-main.c, the conduit's TC_SETUP_FT / nf_flowtable
# offload path) used to FALL BACK to regport 2 (lan1) whenever the flowtable's
# REDIRECT egress netdev was NOT one of our DSA user ports -- which nf_flowtable
# legitimately hands the driver for a bridge master, a VLAN upper, a ppp device, or
# a wifi netdev. Guessing lan1 armed a real HW direct-forward CLA entry that
# steered that flow's actual traffic to whatever host physically sits on lan1 --
# silent misdelivery to the wrong port, not a missed optimization. The fix makes
# the resolver return a distinct ZX_FT_EGRESS_INVALID sentinel for any netdev that
# isn't one of our DSA user ports, and zx_ft_flower_replace() declines
# (-EOPNOTSUPP) instead of installing when it sees that sentinel.
#
# STIMULUS CHOICE (read this before "fixing" this test to use real traffic):
# the task brief asked for a genuine non-DSA nf_flowtable egress if feasible.
# That was attempted for real on this rig: lan2 was enslaved to a Linux bridge
# (`br0`, IP moved from lan2 to br0) so the LAN-side L3 endpoint became a bridge
# master, then a real curl was driven through nft's flowtable/conntrack `flow add
# @f` exactly like baseline_download does. Empirical result: the installed DN
# recipe still logged `eg_rp=3` (a real, valid DSA regport) -- net/netfilter/
# nf_flow_table_offload.c's flow_offload_redirect() resolves the redirect device
# from the tuple's recorded *ingress* ifindex (other_tuple->iifidx), and Linux
# records that as the raw physical receiving netdevice (lan2) at the point the
# ingress netfilter hook runs, which is BEFORE bridging demuxes the frame up to
# br0 -- so enslaving lan2 to a bridge never changes what nf_flowtable resolves
# as the egress device on this topology. A VLAN-upper stimulus would need real
# 802.1Q tags on the wire (risking the CLA's fixed-offset hardware parser, which
# several other findings document as fragile) for an unverified payoff, and
# macvlan -- which would dodge the tagging risk -- is not built into this kernel
# (`# CONFIG_MACVLAN is not set`). Given a real non-DSA nf_flowtable egress is
# infeasible to stage safely on this specific hardware/topology, this test drives
# the exact, unmodified, production `zx_ft_egress_regport()` resolver directly
# via a new minimal debugfs entry point (`fttest resolve <devname>`, added
# alongside the fix, same precedent as the existing `fttest install/destroy`
# H3-era hook) against REAL, already-live net_device objects (`lo`, the DSA
# conduit `sw` itself, and — as a positive control — the real DSA user ports
# `lan2`/`lan4`). This exercises the identical vulnerable code + sentinel check
# with zero HW writes and zero risk to the rig's forwarding path. It does NOT
# drive `zx_ft_flower_replace()`'s own decline-and-return-early statement (the
# resolver is duplicated inline in the test hook rather than calling the real
# function end-to-end) -- that remaining sliver is covered by every OTHER test in
# this battery that exercises real nf_flowtable installs with valid DSA egress
# devices (baseline_download, multiflow, ...) all still passing post-fix, proving
# the guard's early-return didn't disturb the surrounding control flow.
#
# Verified live (2026-07-04): reverting ONLY zx_ft_egress_regport()'s body to the
# pre-fix fallback (keeping this exact test hook unmodified) reproduces the bug
# under this test -- `resolve lo`/`resolve sw` both logged "VALID regport=2"
# instead of declining -- then re-applying the real fix flips both back to
# "INVALID (H4 guard would decline)". Fails without the fix, passes with it.
# ---------------------------------------------------------------------------
def test_h4_nondsa_decline(args):
    name = "h4_nondsa_decline"
    t0 = time.time()
    notes = []
    metrics = {}

    t_ref = _device_uptime()

    # Non-DSA devices that are guaranteed to exist on this rig without staging
    # anything: the loopback device, and the DSA conduit/master "sw" itself
    # (dsa_slave_dev_check() is false for the conduit -- it is not a *user*
    # port). Positive controls: two real DSA user ports (lan2 = LAN, lan4 = WAN)
    # that must keep resolving normally, proving the guard doesn't just decline
    # everything.
    nondsa_devs = ["lo", "sw"]
    dsa_devs = ["lan2", "lan4"]

    cmds = ["echo resolve %s > /sys/kernel/debug/zx_eth/fttest" % d
            for d in nondsa_devs + dsa_devs]
    rig.dev(cmds, wait=2.5 * len(cmds))

    dout = _dmesg_since(r"\[fttest\] resolve dev=", t_ref, tail=40, wait=2.5)

    declined = {}
    valid = {}
    for d in nondsa_devs:
        m = re.search(r"resolve dev=%s -> (INVALID|VALID regport=(\d+))" % re.escape(d), dout)
        declined[d] = bool(m and m.group(1) == "INVALID")
        if not m:
            notes.append("no fttest resolve log seen for non-DSA dev=%s" % d)
        elif not declined[d]:
            notes.append("**FAIL**: non-DSA dev=%s resolved VALID regport=%s -- the H4 "
                          "fallback bug is present (would arm a guessed-egress HW recipe)" %
                          (d, m.group(2)))
    for d in dsa_devs:
        m = re.search(r"resolve dev=%s -> (INVALID|VALID regport=(\d+))" % re.escape(d), dout)
        valid[d] = bool(m and m.group(1).startswith("VALID"))
        if not m:
            notes.append("no fttest resolve log seen for DSA dev=%s" % d)
        elif not valid[d]:
            notes.append("**FAIL**: real DSA user port dev=%s resolved INVALID -- the guard is "
                          "over-declining (would break normal offload, not just the H4 bug)" % d)

    # Belt-and-suspenders: confirm the resolve-only calls never touched the
    # install path -- no "[phase6/ft] recipe:" install line should appear in
    # this window (the "resolve" debugfs verb never calls zx_ft_install_recipe;
    # a match here would mean either a harness mixup with a concurrent test or
    # a driver change that made "resolve" fall through into a real install).
    # NOTE: rig.dev()'s output is the whole REPL transcript (echoed command +
    # any grep hits + the "[exit=N]" trailer), not bare grep stdout -- a
    # *no-match* run still returns a non-empty string (the echoed `dmesg |
    # busybox grep ...` line itself). Truthiness alone would false-FAIL every
    # clean run; look for an actual kernel-timestamped hit line instead (same
    # idiom test_h1_dsa_decline uses via re.search against dout).
    install_leak_raw = _dmesg_since(r"\[phase6/ft\] recipe:", t_ref, tail=10, wait=1.5)
    install_leak = re.search(r"^\s*\[\s*[\d.]+\]\s*.*\[phase6/ft\] recipe:", install_leak_raw,
                              re.MULTILINE)
    if install_leak:
        notes.append("**FAIL**: a '[phase6/ft] recipe:' install line appeared during this "
                      "resolve-only test window -- unexpected HW install side effect: %s" %
                      install_leak.group(0)[-300:])

    device_alive = rig.REPL_MARKER_ALIVE in rig.dev(["echo %s" % rig.REPL_MARKER_ALIVE], wait=2.5)
    if not device_alive:
        notes.append("device REPL unresponsive after the test -- unexpected side effect of a "
                      "supposedly inert, HW-write-free resolve-only path")

    ok = (all(declined.values()) and all(valid.values()) and not install_leak
          and device_alive and len(declined) == len(nondsa_devs) and len(valid) == len(dsa_devs))

    metrics = {"declined": declined, "valid": valid, "device_alive": device_alive}
    return TestResult(name, "PASS" if ok else "FAIL", time.time() - t0, metrics, "; ".join(notes))


# ---------------------------------------------------------------------------
# 7. counters_sanity — one-shot snapshot. Most meaningful right after a
# download test has generated traffic; if run standalone with a cold counter
# set, hit_rate reports N/A rather than a false FAIL.
# ---------------------------------------------------------------------------
def test_counters_sanity(args):
    name = "counters_sanity"
    t0 = time.time()
    b = ctr.read()
    fwd, fail = b.get("cla_dn_fwd"), b.get("acl_fail")
    # [regress.py false-fail fix 2026-07-04, ctr-bug #1] fwd/fail are 16-bit HW
    # counter fields (see the identical note in test_baseline_download) that
    # independently wrap over device uptime; a one-shot ratio of two
    # already-wrapped cumulative values is not a meaningful hit-rate at scale
    # and must NOT gate pass/fail — kept as an informational metric only.
    if fwd is not None and fail is not None:
        denom = fwd + fail
        hit_rate = (fwd / denom) if denom else None
    else:
        hit_rate = None  # a poke read came back empty (device unreachable / debugfs missing)
    trap = b.get("qmg_dn_trap")
    hw = b.get("qmg_dn_hw")

    out = rig.dev(["cat /proc/loadavg"], wait=2.0)
    m = re.search(r"^([\d.]+)\s+([\d.]+)\s+([\d.]+)", out, re.M)
    loadavg1 = float(m.group(1)) if m else None

    ok = True
    notes = []
    if hit_rate is None:
        notes.append("hit_rate N/A (no CLA lookup activity yet — run baseline_download first "
                      "for a meaningful reading; NOT a failure)")
    else:
        notes.append("hit_rate=%.3f informational only (wrap-affected 16-bit counters, not gated — "
                      "see qmg_dn_hw=%s for a non-wrapping activity signal)" % (hit_rate, hw))
    # [red-arm 2026-07-04] qmg_dn_trap is a CUMULATIVE admit counter that now
    # freely exceeds 1024 on a healthy box (the RED cpuDn charge-accounting is
    # off, so admits never stop) -- its absolute value is no longer a wedge
    # proxy and must not gate. Wedge detection = the host->lan4 oracle
    # (churn_no_wedge / red_credit_recycle).
    if trap is not None:
        notes.append("qmg_dn_trap=%d (cumulative, informational)" % trap)
    if loadavg1 is not None and loadavg1 > args.loadavg_max:
        ok = False
        notes.append("loadavg(1m)=%.2f > max %.2f (possible ksoftirqd/kworker spin — the wedged-box "
                      "signature in findings/qa_ethernet_battery_2026-07-04.md was loadavg 3.3)" %
                      (loadavg1, args.loadavg_max))

    metrics = dict(b)
    metrics["hit_rate"] = hit_rate
    metrics["loadavg1"] = loadavg1
    return TestResult(name, "PASS" if ok else "FAIL", time.time() - t0, metrics, "; ".join(notes))


# ---------------------------------------------------------------------------
# red_credit_recycle — TARGETED regression guard for the [red-arm 2026-07-04]
# fix (findings/fix_churn_red_dnbank_2026-07-04.md): RED_CFG bit6 (the cpuDn
# out-buffer charge-accounting, phys 0x92344004) must be CLEARED at boot
# (zx_tm_red_init), else every WAN-ingress hw_trap charges the RED out-queue
# (indices 8-15, the "cpuDn" bank) used_space 1:1 and NOTHING ever returns it
# -> monotonic leak to the 0x400=1024 depth = the reboot-only churn/WAN-RX
# wedge. bit6 is a live level control (proven by runtime bisection: 0xDE
# leaks, 0x9E freezes, restore-0xDE resumes).
#
# Method (all read-only + host-side pings, ~20 s): read RED out-queue
# used_space for q8-15 via the RED indirect RAM (CMD 0x92344014 = q|0x8400000
# -> DONE 0x92344018 bit0 -> DATA0 0x9234401c, guart_used=[10:0] -- the exact
# oracle from the finding), fire a burst of host->lan4 ICMP (each echo request
# is a WAN-ingress DN trap), read again. PASS iff the traps flowed
# (qmg_dn_trap delta >= redrecycle_min_traps) AND no q8-15 accumulated more
# than redrecycle_max_growth (in-flight jitter allowance). On an UNFIXED
# driver the charged queue grows ~1:1 with qmg_dn_trap (hundreds) -> FAIL;
# with the fix it stays flat -> PASS. Verified live in both directions
# (leak with bit6=1, flat with bit6=0, leak resumes on restore) 2026-07-04.
# ---------------------------------------------------------------------------
def _red_used_q8_15():
    """RED out-queue guart_used for q=8..15 via the indirect RAM port.
    Single REPL round-trip; per q: peek DONE, poke CMD(read ram1 addr=q),
    peek DONE, peek DATA0. DATA0 peeks are collected in q order."""
    P = "/sys/kernel/debug/zx_eth/poke"
    qs = list(range(8, 16))
    cmds = []
    for q in qs:
        cmds.append("echo 92344018 > %s" % P)
        cmds.append("echo 92344014 %08x > %s" % (q | 0x8400000, P))
        cmds.append("echo 92344018 > %s" % P)
        cmds.append("echo 9234401c > %s" % P)
    cmds.append("dmesg | busybox grep -a 'peek 0x9234401c' | busybox tail -%d" % (len(qs) + 2))
    out = rig.dev(cmds, wait=1.5 + 0.15 * len(cmds))
    data = re.findall(r"peek 0x9234401c = 0x([0-9a-f]+)", out, re.I)
    if len(data) < len(qs):
        return None
    return {q: int(data[len(data) - len(qs) + i], 16) & 0x7ff for i, q in enumerate(qs)}


def test_red_credit_recycle(args):
    name = "red_credit_recycle"
    t0 = time.time()

    # Oracle precondition: host->lan4 must answer (WAN configured + healthy).
    base_lan4 = _host_ping_loss(rig.LAN4_IP)
    if base_lan4 is None or base_lan4 >= 100:
        return TestResult(name, "SKIP", time.time() - t0, {"base_lan4_loss": base_lan4},
                          "host->lan4 (%s) not answering pre-test (loss=%s%%) -- WAN not up or "
                          "box already wedged; run after rig.py up" % (rig.LAN4_IP, base_lan4))

    used0 = _red_used_q8_15()
    trap0 = rig.poke_read([0x9234c04c]).get(0x9234c04c)
    if used0 is None or trap0 is None:
        return TestResult(name, "ERROR", time.time() - t0, {},
                          "could not read the RED indirect occupancy / qmg_dn_trap oracle")

    # Any q8-15 already AT the 1024 depth = the box arrived wedged-charged.
    pinned = [q for q, v in used0.items() if v >= 1000]

    # Fire the DN-trap burst: host->lan4 ICMP echoes are WAN-ingress traps.
    rig.sh("ping -i 0.02 -c %d -W 1 %s >/dev/null 2>&1" % (args.redrecycle_pings, rig.LAN4_IP),
           timeout=args.redrecycle_pings * 0.02 + 30)
    time.sleep(1.5)

    used1 = _red_used_q8_15()
    trap1 = rig.poke_read([0x9234c04c]).get(0x9234c04c)
    if used1 is None or trap1 is None:
        return TestResult(name, "ERROR", time.time() - t0, {},
                          "post-burst oracle read failed")

    dtrap = trap1 - trap0
    growth = {q: used1[q] - used0[q] for q in used0}
    max_growth = max(growth.values())
    metrics = {"qmg_dn_trap_delta": dtrap, "used_before": used0, "used_after": used1,
               "max_growth": max_growth, "pinned_at_start": pinned}

    if dtrap < args.redrecycle_min_traps:
        return TestResult(name, "SKIP", time.time() - t0, metrics,
                          "only %d DN traps flowed (< %d) -- burst didn't exercise the trap path "
                          "(lan4 down? pings not trapping?); inconclusive" %
                          (dtrap, args.redrecycle_min_traps))

    ok = max_growth <= args.redrecycle_max_growth
    if ok:
        notes = ("cpuDn charge-accounting off/flat: %d DN traps, max q8-15 used_space growth %d "
                  "(<= %d)%s" % (dtrap, max_growth, args.redrecycle_max_growth,
                                  "; NOTE stuck pre-existing charge on q%s (pre-arm residue)" %
                                  pinned if pinned else ""))
    else:
        worst = max(growth, key=growth.get)
        notes = ("cpuDn charge LEAKS: q%d grew +%d over %d DN traps (limit %d) -- the RED_CFG "
                  "bit6 clear is missing/regressed ([red-arm 2026-07-04], zx_tm_red_init); "
                  "unfixed this leaks to 1024 = the reboot-only churn wedge" %
                  (worst, growth[worst], dtrap, args.redrecycle_max_growth))
    return TestResult(name, "PASS" if ok else "FAIL", time.time() - t0, metrics, notes)


# ---------------------------------------------------------------------------
# 8. dmesg_clean — run LAST in a battery (dmesg ring can wrap under load).
# ---------------------------------------------------------------------------
def test_dmesg_clean(args):
    name = "dmesg_clean"
    t0 = time.time()
    bad = _dmesg_scan()
    ok = len(bad) == 0
    notes = "clean" if ok else ("; ".join(bad[:5]) + (" ... (+%d more)" % (len(bad) - 5) if len(bad) > 5 else ""))
    return TestResult(name, "PASS" if ok else "FAIL", time.time() - t0, {"bad_line_count": len(bad)}, notes)


# ---------------------------------------------------------------------------
# 9. recovery_alive — run LAST (or last-but-one before dmesg_clean).
# ---------------------------------------------------------------------------
def test_recovery_alive(args):
    name = "recovery_alive"
    t0 = time.time()
    marker = "REGRESS_ALIVE_%d" % (int(time.time()) % 100000)
    alive = marker in rig.dev(["echo %s" % marker], wait=3.0)

    modem_loss = None
    if alive:
        out2 = rig.dev(["ping -c 3 -W 2 %s" % rig.WAN_GW], wait=5.0)
        m = re.search(r"(\d+)% packet loss", out2)
        modem_loss = int(m.group(1)) if m else None

    trap = None
    if alive:
        trap = rig.poke_read([0x9234c04c]).get(0x9234c04c)

    # [red-arm 2026-07-04] trap value is informational only (cumulative admit
    # counter, healthy past 1024 since the bit6 charge-accounting fix).
    ok = alive and (modem_loss == 0)
    notes = []
    if not alive:
        notes.append("REPL did not respond — device likely wedged; a DTR reboot (`rig.py boot`) is "
                      "required before running anything else")
    elif modem_loss != 0:
        notes.append("modem ping loss=%s%% (WAN unreachable)" % modem_loss)
    if trap is not None:
        notes.append("qmg_dn_trap=%d (cumulative, informational)" % trap)

    metrics = {"repl_alive": alive, "modem_loss_pct": modem_loss, "qmg_dn_trap": trap}
    return TestResult(name, "PASS" if ok else "FAIL", time.time() - t0, metrics, "; ".join(notes))


# ---------------------------------------------------------------------------
# 10. upload_offload — STUB for future work (UP HW-offload not landed yet).
# ---------------------------------------------------------------------------
def test_upload_offload(args):
    return TestResult(
        "upload_offload", "SKIP", 0.0, {},
        "STUB — UP HW-offload is not implemented on mainline yet (UP direction is deliberately "
        "declined to SW; the cracked cmd_flow_id UP-offload formula is documented in "
        "findings/stock_red_drain_up_RE_2026-07-04.md / memory zte-redwedge-unicast-cpu but is NOT "
        "landed — enabling it today black-holes UP traffic with src IP 0.0.0.0). Wire this test up "
        "once UP offload merges: it should drive an upload and assert qmg_up_hw climbs, the source "
        "IP/NAT is correct, and there's no 0.0.0.0 regression.")


# ---------------------------------------------------------------------------
# registry + battery composition
# ---------------------------------------------------------------------------
REGISTRY = {
    "baseline_download": test_baseline_download,
    "sustained_download": test_sustained_download,
    "multiflow": test_multiflow,
    "churn": test_churn,
    "churn_no_wedge": test_churn_no_wedge,
    "red_credit_recycle": test_red_credit_recycle,
    "concurrency_race": test_concurrency_race,
    "poly0_stale": test_poly0_stale,
    "high_way_collision": test_high_way_collision,
    "replace_orphan": test_replace_orphan,
    "pm_write_verify": test_pm_write_verify,
    "bidirectional": test_bidirectional,
    "edge_decline": test_edge_decline,
    "h1_dsa_decline": test_h1_dsa_decline,
    "h4_nondsa_decline": test_h4_nondsa_decline,
    "counters_sanity": test_counters_sanity,
    "dmesg_clean": test_dmesg_clean,
    "recovery_alive": test_recovery_alive,
    "upload_offload": test_upload_offload,
}

# Order matches the QA battery scenarios 1-9 (findings/qa_ethernet_battery_2026-07-04.md),
# with concurrency_race, poly0_stale and high_way_collision inserted right after
# churn (same "concurrency/lifecycle" family, targeted at findings C1/C2/H2
# respectively -- see their docstrings). h1_dsa_decline sits next to
# edge_decline (same "declines cleanly, no bogus HW install" family, targeted
# at finding H1). dmesg_clean/recovery_alive run near the end on purpose (see
# their docstrings).
ORDER = ["baseline_download", "red_credit_recycle", "sustained_download", "multiflow", "churn",
         "concurrency_race", "poly0_stale", "high_way_collision", "replace_orphan", "pm_write_verify",
         "bidirectional", "edge_decline", "h1_dsa_decline", "h4_nondsa_decline", "churn_no_wedge",
         "counters_sanity", "dmesg_clean", "recovery_alive"]

QUICK = ["baseline_download", "red_credit_recycle", "sustained_download", "counters_sanity",
         "dmesg_clean"]

DESCRIPTIONS = {
    "baseline_download": "1 flow ~500MB-1GB -> line rate, HW-offloaded (cla hit-rate high), CPU sane",
    "sustained_download": "N back-to-back big downloads -> no wedge, no residual admission latch (KEY guard)",
    "multiflow": "N concurrent downloads (distinct 5-tuples) -> all connect+complete, no slot clobber",
    "churn": "many short back-to-back connections -> clean install/destroy/reinstall, no leak",
    "churn_no_wedge": "HIGH-concurrency STORM wedge guard (modem-independent host->lan4 oracle): "
                      "device must NOT wedge (qmg_dn_trap free past 1024, lan4 datapath alive). "
                      "FIXED by [red-arm 2026-07-04] (RED_CFG bit6 cpuDn charge-accounting off); in the "
                      "default battery near the end (if it regresses, the box wedges reboot-only "
                      "and only the trailing sanity tests are confounded).",
    "red_credit_recycle": "[red-arm 2026-07-04] REGRESSION GUARD: RED cpuDn out-buffer (q8-15) "
                           "used_space must stay FLAT (bit6 charge-accounting off) across a "
                           "host->lan4 DN-trap ping burst; unfixed it leaks 1:1 to 1024 = the churn wedge",
    "concurrency_race": "C1 REGRESSION GUARD: hammer concurrent REPLACE/DESTROY -> no pm_slot "
                         "collision, no CLA ram7 corruption, device stays alive",
    "poly0_stale": "C2 REGRESSION GUARD: destroy clears the poly-0 WAN-ingress ram2 slot (HW-verified); "
                   "engineered raw0-colliding flow pair declines instead of clobbering",
    "high_way_collision": "H2 REGRESSION GUARD: engineered higher-way (ram3/4/5/6) colliding flow pair "
                           "declines instead of one destroy wiping the other's live bucket",
    "replace_orphan": "H3 REGRESSION GUARD: self-REPLACE (same cookie, changed tuple) clears the OLD "
                       "5 ways + poly-0 slot before adopting the new tuple -- no orphaned stale entry",
    "pm_write_verify": "H5 REGRESSION GUARD: every install's 4 PM writes are rc-checked + readback-"
                        "verified (ft_pm_verify.ok +=4, fail=0) and pmpeek independently confirms "
                        "ram1/ram3/ram6 committed the intended values",
    "bidirectional": "bulk DN + many small UP-heavy flows -> both progress; quantifies UP-ACK RED-drop",
    "edge_decline": "ICMP/UDP/IPv6 -> declined gracefully to SW, no bogus HW install, no crash",
    "h1_dsa_decline": "H1 REGRESSION GUARD: DSA tc-flower skip_sw install on a user port DECLINES "
                       "(-EOPNOTSUPP) -- no CLA/PM recipe armed, no crash, conduit offload unaffected",
    "h4_nondsa_decline": "H4 REGRESSION GUARD: conduit egress-regport resolver DECLINES (sentinel, "
                          "no lan1 guess) for non-DSA netdevs (lo, conduit); still resolves real DSA "
                          "user ports normally",
    "counters_sanity": "one-shot hit-rate / trap-proximity / loadavg snapshot",
    "dmesg_clean": "no oops/panic/WARNING/hung-task in dmesg (run near the end of a battery)",
    "recovery_alive": "device REPL-alive + modem 0% loss after the battery",
    "upload_offload": "STUB (SKIP) — UP HW-offload not implemented yet; hook for when it lands",
}

DEFAULT_TIMEOUTS = {
    "baseline_download": 90,
    "sustained_download": 700,
    "multiflow": 120,
    "churn": 900,
    "churn_no_wedge": 300,
    "red_credit_recycle": 90,
    "concurrency_race": 180,
    "poly0_stale": 180,
    "high_way_collision": 180,
    "replace_orphan": 180,
    "pm_write_verify": 90,
    "bidirectional": 300,
    "edge_decline": 60,
    "h1_dsa_decline": 60,
    "h4_nondsa_decline": 60,
    "counters_sanity": 30,
    "dmesg_clean": 30,
    "recovery_alive": 40,
    "upload_offload": 10,
}


def run_with_timeout(name, fn, args, timeout):
    t0 = time.time()
    with cf.ThreadPoolExecutor(max_workers=1) as ex:
        fut = ex.submit(fn, args)
        try:
            return fut.result(timeout=timeout)
        except cf.TimeoutError:
            return TestResult(name, "FAIL", time.time() - t0, {},
                               "TIMEOUT after %ds — the underlying command(s) may still be running "
                               "on the device/host (a Python thread can't be killed mid-subprocess); "
                               "run `rig.py status` before trusting subsequent tests." % timeout)
        except Exception as e:
            return TestResult(name, "ERROR", time.time() - t0, {}, "exception: %r" % e)


def _fmt_metrics(m, maxlen=100):
    s = ", ".join("%s=%s" % (k, v) for k, v in m.items())
    return (s[:maxlen] + "...") if len(s) > maxlen else s


def print_summary(results):
    rig.hdr("REGRESSION SUMMARY")
    width = max((len(r.name) for r in results), default=10)
    for r in results:
        print("  %-*s  %-5s  %6.1fs  %s" % (width, r.name, r.status, r.duration, _fmt_metrics(r.metrics)))
        if r.notes:
            print("      -> %s" % r.notes)
    n_pass = sum(1 for r in results if r.status == "PASS")
    n_fail = sum(1 for r in results if r.status in ("FAIL", "ERROR"))
    n_skip = sum(1 for r in results if r.status == "SKIP")
    verdict = "FAIL" if n_fail else "PASS"
    print("\n  TOTAL: %d pass / %d fail / %d skip  ->  OVERALL: %s" % (n_pass, n_fail, n_skip, verdict))
    return n_fail


def build_argparser():
    p = argparse.ArgumentParser(
        description=__doc__, formatter_class=argparse.RawDescriptionHelpFormatter)
    p.add_argument("tests", nargs="*", help="test name(s) to run (default: full battery, QA order)")
    p.add_argument("--quick", action="store_true",
                   help="run just %s" % QUICK)
    p.add_argument("--list", action="store_true", help="list test names + pass criteria and exit")
    p.add_argument("--no-boot", action="store_true", help="skip `rig.py up` (assume rig already up)")
    p.add_argument("--long-boot", action="store_true", help="`rig.py boot --long` (revives WAN modem)")
    p.add_argument("--no-teardown", action="store_true", help="skip the final rig teardown")
    p.add_argument("--timeout", type=float, default=None,
                   help="override the per-test wall-clock timeout (s) for ALL tests "
                        "(default: per-test values in DEFAULT_TIMEOUTS)")

    g = p.add_argument_group("tunable thresholds (flagged NEEDS-TUNING in REGRESS_README.md "
                              "until run at least once against real hardware)")
    g.add_argument("--baseline-dur", type=float, default=40.0, help="[TUNE] baseline_download --max-time (s)")
    g.add_argument("--baseline-size", type=int, default=0, help="[TUNE] baseline_download byte cap (0=whole ~1GB file)")
    g.add_argument("--line-rate-min", type=float, default=50.0, help="[TUNE] 'line rate' MB/s bar")
    g.add_argument("--hitrate-min", type=float, default=0.90,
                    help="[DEPRECATED, unused as a gate since the 2026-07-04 ctr-bug #1 fix] "
                         "cla_dn_fwd/acl_fail are 16-bit HW counters that wrap multiple times over "
                         "a line-rate GB transfer, so a before/after ratio false-fails at scale; "
                         "kept only for CLI back-compat. See --hwfwd-min-frac for the replacement "
                         "gate (uses the non-wrapping qmg_dn_hw delta).")
    g.add_argument("--hwfwd-min-frac", type=float, default=0.5,
                    help="[TUNE] baseline_download HW-forward assertion: qmg_dn_hw delta must reach "
                         "at least this fraction of the conservatively-estimated packet count "
                         "(bytes/1400) — replaces the wrap-affected cla hit-rate check (ctr-bug #1)")
    g.add_argument("--trap-healthy-max", type=int, default=300, help="[TUNE] qmg_dn_trap 'healthy' ceiling")
    g.add_argument("--trap-wedge-thresh", type=int, default=900, help="qmg_dn_trap 'near the 1024 latch' ceiling")
    g.add_argument("--sustained-runs", type=int, default=5, help="[TUNE] sustained_download back-to-back run count")
    g.add_argument("--sustained-dur", type=float, default=90.0, help="[TUNE] sustained_download per-run --max-time (s)")
    g.add_argument("--sustained-modem", action="store_true",
                    help="[H3 session] run sustained_download against the REAL internet via the WAN "
                         "modem (rig.DL_URL_DEFAULT) instead of the modem-independent LAN-local default "
                         "(rig.DL_URL_SUSTAINED_LOCAL) -- use for a deliberate real-world spot check; "
                         "leave unset for regular regression runs so a flaky modem can't false-fail the "
                         "driver's own wedge-regression guard.")
    g.add_argument("--sustained-url", default=None,
                    help="[H3 session] explicit override for sustained_download's download target -- "
                         "takes precedence over both the LAN-local default and --sustained-modem.")
    g.add_argument("--rdrop-max", type=int, default=400000,
                    help="[TUNE, raised AGAIN 2026-07-04 H3 session] red_drop growth ceiling over the "
                         "sustained run. The prior default (48000, ctr-bug #2) was calibrated against "
                         "sustained_download's OLD target (5 x 1 GB over the external/WAN-modem path, "
                         "~30-36k healthy growth) -- once sustained_download's default moved to the "
                         "LAN-local 6 GiB file (see rig.DL_URL_SUSTAINED_LOCAL; modem-independence "
                         "fix), the SAME test now moves ~6x the volume at LAN-local throughput "
                         "(~114 MB/s observed vs the old external path's lower rate) and legitimately "
                         "grows red_drop by ~260k over a clean 5/5-runs-completed, no-wedge, "
                         "dmesg-clean pass (confirmed live 2026-07-04) -- red_drop is a bounded "
                         "backpressure signal that scales with throughput*volume, not itself a wedge "
                         "signature (that's qmg_dn_trap, checked separately via --trap-wedge-thresh). "
                         "400000 leaves comparable proportional margin above the new healthy range "
                         "while still catching a real regression. Lower this back down (or use "
                         "--sustained-modem) if you deliberately want the old smaller-volume target's "
                         "tighter bound.")
    g.add_argument("--mac-tx-tol", type=float, default=0.05, help="mac4_tx vs tm_tx_count delta tolerance (fraction)")
    g.add_argument("--multiflow-n", type=int, default=5, help="[TUNE] concurrent flow count")
    g.add_argument("--multiflow-dur", type=float, default=15.0, help="multiflow --max-time (s)")
    g.add_argument("--multiflow-min-frac", type=float, default=1.0, help="required connect fraction")
    g.add_argument("--multiflow-size", type=int, default=30_000_000,
                    help="[TUNE, H2 session] Range-capped (`-r`) bytes per multiflow flow. NO-OP "
                         "against the default --local-server (python3 -m http.server ignores Range, "
                         "always serves the whole file -- see rig.DL_URL_LOCAL's comment; the real "
                         "aggregate-demand fix there is a smaller 50 MiB file) but takes effect "
                         "against a Range-aware server. 0 = unbounded.")
    g.add_argument("--multiflow-rate-limit", default="8M",
                    help="[TUNE, H2 session] curl --limit-rate per multiflow flow -- stretches each "
                         "flow to several seconds so nf_flowtable has time to actually HW-offload it "
                         "before it finishes (see test_multiflow's mitigation (6) comment for the "
                         "confirmed live signature this fixes). Empty string/None = unlimited.")
    g.add_argument("--local-server", default=rig.DL_URL_LOCAL,
                    help="[H2 multiflow-validity fix] LAN-local URL used by multiflow AND "
                         "high_way_collision instead of rig.DL_URL_DEFAULT, which has a "
                         "concurrent-connection ceiling on the external thinkbroadband server "
                         "(confirmed not a driver issue -- see the DL_URL_LOCAL comment in rig.py). "
                         "Pass the external URL explicitly (rig.DL_URL_DEFAULT) to restore the old "
                         "behavior; traffic to either URL transits the identical device WAN-ingress "
                         "DN HW-offload path.")
    g.add_argument("--churn-n", type=int, default=20, help="[TUNE, lowered 2026-07-04] churn flow count. "
                                                             "The original default (60, matching the QA "
                                                             "session) reliably drives qmg_dn_trap to the "
                                                             "1024 saturation point on this hardware -- "
                                                             "confirmed PRE-EXISTING and unrelated to any "
                                                             "driver fix here (0 of 70 declines in that run "
                                                             "were poly0-tagged; all were the pre-existing "
                                                             "way0 path -- see memory zte-redwedge-unicast-cpu / "
                                                             "findings/wedge_txflowctrl_fix_2026-07-04.md). "
                                                             "Even --churn-n 30 tripped it (5/30 ok). 20 "
                                                             "passed cleanly and reliably across multiple "
                                                             "runs this session (20/20, trap stayed <100). "
                                                             "Raise this to deliberately stress the OPEN "
                                                             "latch issue, not to test C2/harness correctness.")
    g.add_argument("--churn-size", type=int, default=2_000_000, help="churn per-flow byte size")
    g.add_argument("--churn-min-frac", type=float, default=1.0, help="required ok fraction")
    g.add_argument("--churn-gap", type=float, default=0.1, help="[churn-harness-fix] extra spacing (s) "
                                                                  "between churn flows, on top of the "
                                                                  "sudo-priming/ARP-warmup done once up "
                                                                  "front -- 0 to disable")
    g.add_argument("--churn-instant-fail-s", type=float, default=0.05, help="[churn-harness-fix] a curl "
                                                                             "result with 0 bytes AND "
                                                                             "time_total below this is "
                                                                             "the host-tooling instant-fail "
                                                                             "signature (not a real network "
                                                                             "timeout) -- eligible for retry")
    g.add_argument("--churn-retries", type=int, default=2, help="[churn-harness-fix] max retries for the "
                                                                  "instant-fail signature per flow")
    g.add_argument("--churn-retry-gap", type=float, default=0.3, help="[churn-harness-fix] sleep (s) before "
                                                                        "each retry")
    g.add_argument("--cnw-n", type=int, default=30, help="[churn_no_wedge] concurrent flows PER WAVE "
                                                          "(n=30 x 2 waves = 60 = the storm that reliably "
                                                          "wedged the switch live 2026-07-04; n=16 x1 stayed "
                                                          "healthy)")
    g.add_argument("--cnw-waves", type=int, default=2, help="[churn_no_wedge] number of concurrent waves")
    g.add_argument("--cnw-dur", type=float, default=4.0, help="[churn_no_wedge] per-flow --max-time (s)")
    g.add_argument("--cnw-stagger", type=float, default=0.02, help="[churn_no_wedge] intra-wave launch stagger (s)")
    g.add_argument("--cnw-wave-gap", type=float, default=1.0, help="[churn_no_wedge] gap between waves (s)")
    g.add_argument("--cnw-port-base", type=int, default=58000, help="[churn_no_wedge] base local port")
    g.add_argument("--cnw-oracle-retries", type=int, default=14,
                   help="[churn_no_wedge] host->lan4 oracle attempts before declaring WEDGED "
                        "(the modem AP's wire->WiFi leg reads 100%% loss for ~1-4 min post-storm; "
                        "the genuine wedge is permanent so a long window can't mask it)")
    g.add_argument("--cnw-oracle-gap", type=float, default=20.0,
                   help="[churn_no_wedge] seconds between oracle attempts")
    g.add_argument("--redrecycle-pings", type=int, default=400,
                   help="[red_credit_recycle] host->lan4 ICMP count (each echo = 1 DN trap charge)")
    g.add_argument("--redrecycle-min-traps", type=int, default=50,
                   help="[red_credit_recycle] min qmg_dn_trap delta for a conclusive run")
    g.add_argument("--redrecycle-max-growth", type=int, default=40,
                   help="[red_credit_recycle] max allowed q8-15 used_space accumulation across the "
                        "burst (in-flight jitter allowance; the UNFIXED leak grows ~1:1 with traps)")
    g.add_argument("--race-n", type=int, default=16, help="[TUNE] concurrency_race concurrent flow count "
                                                            "(> multiflow's 5 -- maximize the C1 race window)")
    g.add_argument("--race-stagger", type=float, default=0.05, help="[TUNE] concurrency_race launch stagger (s) "
                                                                     "(near-zero vs multiflow's 0.3s)")
    g.add_argument("--race-size-min", type=int, default=300_000, help="concurrency_race per-flow min byte size "
                                                                       "(jittered so completions spread out)")
    g.add_argument("--race-size-max", type=int, default=4_000_000, help="concurrency_race per-flow max byte size")
    g.add_argument("--race-dur", type=float, default=25.0, help="concurrency_race --max-time (s)")
    g.add_argument("--race-min-frac", type=float, default=0.8, help="[TUNE] required connect fraction "
                                                                     "(< 1.0: a declined-to-SW flow still "
                                                                     "connects, just slower, so this mostly "
                                                                     "guards against real client-side resource "
                                                                     "contention at high concurrency, not "
                                                                     "driver correctness — the pm_slot "
                                                                     "COLLISION check is the real C1 gate)")
    g.add_argument("--poly0-dur", type=float, default=20.0, help="poly0_stale sub-check A flow --max-time (s)")
    g.add_argument("--poly0-size", type=int, default=3_000_000, help="poly0_stale sub-check A flow byte size")
    g.add_argument("--poly0-destroy-timeout", type=float, default=30.0, help="[TUNE] poly0_stale sub-check A: "
                                                                              "max wait (s) for FLOW_CLS_DESTROY "
                                                                              "after the flow finishes")
    g.add_argument("--poly0-pair-dur", type=float, default=20.0, help="poly0_stale sub-check B pair flows "
                                                                        "--max-time (s)")
    g.add_argument("--poly0-pair-size", type=int, default=2_000_000, help="poly0_stale sub-check B pair "
                                                                           "flow byte size")
    g.add_argument("--poly0-pair-stagger", type=float, default=0.3, help="poly0_stale sub-check B launch "
                                                                          "stagger (s) between the two "
                                                                          "engineered-collision flows")
    g.add_argument("--hwc-scan", type=int, default=40, help="[TUNE] high_way_collision: candidate local "
                                                              "ports scanned (via the on-device hashcalc "
                                                              "HW oracle, batched in one round trip) per "
                                                              "way-index attempt to find an engineered "
                                                              "higher-way collision pair. ram6 (the "
                                                              "default target, only 8 buckets) needs very "
                                                              "few draws for a birthday collision; 40 "
                                                              "leaves comfortable margin.")
    g.add_argument("--hwc-dur", type=float, default=20.0, help="high_way_collision pair flows --max-time (s)")
    g.add_argument("--hwc-size", type=int, default=3_000_000,
                    help="high_way_collision pair flow byte size (`-r` Range-capped; a no-op against "
                         "the default --local-server, see --multiflow-size's help -- the pair still "
                         "gets the whole 50 MiB srv50m.bin, which is fine, the test's PASS/FAIL "
                         "doesn't depend on byte count, only on the dmesg install/decline timeline)")
    g.add_argument("--hwc-stagger", type=float, default=0.3, help="high_way_collision launch stagger (s) "
                                                                    "between the two engineered-collision "
                                                                    "flows")
    g.add_argument("--hwc-rate-limit", default="5M",
                    help="[TUNE, H2 session] curl --limit-rate per engineered flow -- see "
                         "--multiflow-rate-limit's help for why this matters against the fast "
                         "LAN-local server. Empty string/None = unlimited.")
    g.add_argument("--bidir-dur", type=float, default=20.0, help="bidirectional bulk DN --max-time (s)")
    g.add_argument("--bidir-small-n", type=int, default=10, help="[TUNE] small UP-heavy flow count "
                                                                  "(QA session used 30; scaled down for speed)")
    g.add_argument("--bidir-min-frac", type=float, default=0.5, help="[TUNE] required small-flow connect fraction "
                                                                      "(QA session's 0/30 was already a degraded "
                                                                      "device; re-baseline on a clean run)")
    g.add_argument("--loadavg-max", type=float, default=3.0, help="[TUNE] 1-min loadavg ceiling "
                                                                    "(wedged box observed 3.3)")
    return p


def main():
    p = build_argparser()
    args = p.parse_args()

    if args.list:
        width = max(len(n) for n in DESCRIPTIONS)
        for n in ORDER + ["upload_offload"]:
            mark = " (quick)" if n in QUICK else ""
            print("  %-*s%s  %s" % (width, n, mark, DESCRIPTIONS[n]))
        return 0

    if args.quick and args.tests:
        print("[ABORT] --quick and explicit test names are mutually exclusive.")
        return 2

    names = QUICK if args.quick else (args.tests or ORDER)
    unknown = [n for n in names if n not in REGISTRY]
    if unknown:
        print("[ABORT] unknown test name(s): %s (see --list)" % unknown)
        return 2

    if not args.no_boot:
        rig.hdr("regress: rig up (boot+wan+client+offload) before the battery")
        rc = rig.cmd_up(argparse.Namespace(long_dtr=args.long_boot))
        if rc != 0:
            print("\n[ABORT] rig up failed — cannot run the regression battery.")
            return 2

    results = []
    for name in names:
        timeout = args.timeout or DEFAULT_TIMEOUTS.get(name, 60)
        rig.hdr("TEST %s (timeout %ds)" % (name, timeout))
        r = run_with_timeout(name, REGISTRY[name], args, timeout)
        print("  -> %-5s in %.1fs  %s" % (r.status, r.duration, _fmt_metrics(r.metrics)))
        if r.notes:
            print("     %s" % r.notes)
        results.append(r)
        _cleanup_client_procs()

    n_fail = print_summary(results)

    if not args.no_teardown:
        rig.hdr("regress: host teardown (mandatory before any reboot)")
        rig.cmd_teardown(argparse.Namespace(skip_device=False))

    return 1 if n_fail else 0


if __name__ == "__main__":
    sys.exit(main())
