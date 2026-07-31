#!/usr/bin/env python3
"""Fabric-INGRESS wedge probe (WiFi UP HW-offload endurance), 2026-07-31.

Implements the verified first probe of
findings/wifi_stage3_fabric_ingress_wedge_candidates_VERIFY_2026-07-28.md:
drive sustained fabric-ingress (phone -> WAN host uploads, ftwifi=1) in
CHUNKED bursts so every gauge round samples a quiescent fabric, and read:
  - e->tx_pending (stats debugfs) + IDM TX_STATUS 0x921c8044  <- THE FORK:
    pinned at 0x200 => admission wall upstream (candidates 1/2);
    free-flowing while throughput is dead => corruption primary (candidate 3)
  - SIPC 0x921cc004 (drop nibbles) + 0x921cc008/18/1c/20 (FIFO gauges)
  - SMCT 0x921d0040 (free-level) / 0x921d004c (doorbell) [candidate 1b]
  - RED ram1 out-queue occupancy, FULL row space (rows 0-15, 0x10-0x4f,
    (40+p)*8) via the red_probe indirect recipe [candidate 2, corrected rows]
  - gparsehashkey 0x9238c260 head words continuously [candidate 3 onset shape]
  - SADM pass/drop + QMG/CLA verdict counters (free riders / wedge detector)
One-time boot check (done manually 2026-07-31): 0x921d0004 POR = 0xA vs
stock 0xB -> the 1b parity-gap fix candidate is REAL.

Usage:
  wedge_probe.py sample            # one gauge round
  wedge_probe.py ram1 [full]      # RED ram1 sweep (light|full), nonzero rows
  wedge_probe.py run [max_bursts] [burst_mb]   # the probe loop
  wedge_probe.py wedgecap          # full wedge-signature capture
Preconditions: wifi_up.py all --adb --offload done; idm1 up; host return
route 192.168.50.0/24 via 10.44.66.223 dev wlo1.
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
import ab_ctrs  # noqa: E402  (paced zc — console-safe)

# WSINK override (2026-07-31): the LAN-egress control test sinks on a
# directly-cabled LAN-port host NIC instead of the WAN/modem path.
HOST_WAN_IP = os.environ.get("WSINK", "10.44.66.133")
TEST_PORT = 9099
POKE = "/sys/kernel/debug/zx_eth/poke"

GAUGES = [
    ("sipc_drop", 0x921cc004), ("sipc_g008", 0x921cc008),
    ("sipc_g018", 0x921cc018), ("sipc_g01c", 0x921cc01c),
    ("sipc_g020", 0x921cc020),
    ("smct_free", 0x921d0040), ("smct_bell", 0x921d004c),
    ("idm_txsts", 0x921c8044),
    ("cla_up_fwd", 0x9238c3c0), ("cla_acl_fail", 0x9238c3c4),
    ("qmg_up_sw", 0x9234c054), ("qmg_up_hw", 0x9234c058),
    ("qmg_up_trap", 0x9234c05c), ("qmg_dn_hw", 0x9234c048),
    ("sadm_pass", 0x921c4200), ("sadm_drop", 0x921c4208),
    ("gkey0", 0x9238c260), ("gkey1", 0x9238c264),
]
LO16 = {"cla_up_fwd", "cla_acl_fail"}

# RED indirect (red_probe.py recipe, live-proven in the churn fix)
RED_CMD, RED_DONE, RED_DATA0 = 0x92344014, 0x92344018, 0x9234401c
ROWS_LIGHT = list(range(0, 16)) + [(40 + p) * 8 for p in range(5)]
ROWS_FULL = list(range(0, 16)) + list(range(0x10, 0x50)) + \
    [(40 + p) * 8 for p in range(5)]

GKEY = 0x9238c260


def sample():
    """One paced gauge round. Returns dict incl. tx_pending/tx_injected."""
    cmds = ["echo %08x > %s" % (a, POKE) for _, a in GAUGES]
    cmds.append("dmesg | busybox grep -a 'peek 0x' | busybox tail -%d"
                % (len(GAUGES) + 4))
    cmds.append("busybox grep -aE 'tx_idx / tx_done|bmu_free' "
                "/sys/kernel/debug/zx_eth/stats")
    cmds.append("busybox grep -a tx_injected /sys/kernel/debug/zx_eth/wifi_bind")
    out = ab_ctrs.zc(cmds, wait=3, hardcap=60)
    v = {}
    for name, addr in GAUGES:
        m = re.findall(r"peek 0x%08x = 0x([0-9a-f]+)" % addr, out, re.I)
        v[name] = int(m[-1], 16) if m else None
    m = re.search(r"pending=(-?\d+)", out)
    v["tx_pending"] = int(m.group(1)) if m else None
    m = re.search(r"tm_bmu_free_ok\s*=\s*(\d+)", out)
    v["bmu_free_ok"] = int(m.group(1)) if m else None
    m = re.search(r"tm_bmu_free_fail\s*=\s*(\d+)", out)
    v["bmu_free_fail"] = int(m.group(1)) if m else None
    m = re.search(r"tx_injected=(\d+)", out)
    v["tx_injected"] = int(m.group(1)) if m else None
    return v


def show(v, tag=""):
    print("== SAMPLE %s ==" % tag)
    print("  inj=%s pend=%s idm_txsts=%s bmu_ok=%s/fail=%s" % (
        v.get("tx_injected"), v.get("tx_pending"),
        hx(v.get("idm_txsts")), v.get("bmu_free_ok"), v.get("bmu_free_fail")))
    print("  sipc drop=%s g008=%s g018=%s g01c=%s g020=%s" % tuple(
        hx(v.get(k)) for k in ("sipc_drop", "sipc_g008", "sipc_g018",
                               "sipc_g01c", "sipc_g020")))
    print("  smct free=%s bell=%s | sadm pass=%s drop=%s" % tuple(
        hx(v.get(k)) for k in ("smct_free", "smct_bell", "sadm_pass",
                               "sadm_drop")))
    print("  cla up_fwd=%s acl_fail=%s | qmg up sw=%s hw=%s trap=%s dn_hw=%s"
          % tuple(hx(v.get(k)) for k in
                  ("cla_up_fwd", "cla_acl_fail", "qmg_up_sw", "qmg_up_hw",
                   "qmg_up_trap", "qmg_dn_hw")))
    print("  gkey0=%s gkey1=%s" % (hx(v.get("gkey0")), hx(v.get("gkey1"))))
    sys.stdout.flush()


def hx(x):
    return ("0x%x" % x) if x is not None else "?"


def d16(b, a):
    """lo16 counter delta with wrap."""
    if a is None or b is None:
        return None
    return ((b & 0xffff) - (a & 0xffff)) & 0xffff


def ram1_sweep(rows, label=""):
    """RED ram1 used_space for rows. 3 cmds/row, chunks of 10 rows."""
    vals = {}
    for i in range(0, len(rows), 10):
        chunk = rows[i:i + 10]
        cmds = []
        for q in chunk:
            cmdval = q | (1 << 22) | (1 << 27)
            cmds.append("echo %08x %08x > %s" % (RED_CMD, cmdval, POKE))
            cmds.append("echo %08x > %s" % (RED_DONE, POKE))
            cmds.append("echo %08x > %s" % (RED_DATA0, POKE))
        cmds.append("dmesg | busybox grep -a 'peek 0x' | busybox tail -%d"
                    % (len(cmds) + 6))
        out = ab_ctrs.zc(cmds, wait=3, hardcap=60)
        data = re.findall(r"peek 0x%08x = 0x([0-9a-f]+)" % RED_DATA0, out, re.I)
        if len(data) >= len(chunk):
            for j, q in enumerate(chunk):
                vals[q] = int(data[len(data) - len(chunk) + j], 16)
        else:
            for q in chunk:
                vals[q] = None
    nz = {q: v for q, v in vals.items() if v}
    print("== RAM1 %s: %d rows, nonzero: %s ==" % (
        label, len(rows),
        " ".join("r%d=0x%x(g%d,s%d)" % (q, v, v & 0x7ff, (v >> 11) & 0x7fff)
                 for q, v in sorted(nz.items())) or "NONE"))
    sys.stdout.flush()
    return vals


class Sink(threading.Thread):
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


def burst(sink, mb):
    """One phone->host push of mb MiB over a FRESH connection. toybox nc
    never exits on stdin EOF (upab kills it by timer), so poll the sink
    byte counter and kill as soon as all bytes land or the flow stalls 6 s.
    Returns (bytes_received, seconds — up to the last byte, not the kill)."""
    with sink.lock:
        start = sink.rx
    p = subprocess.Popen(
        ["adb", "shell",
         "toybox dd if=/dev/zero bs=1048576 count=%d 2>/dev/null | "
         "toybox nc %s %d" % (mb, HOST_WAN_IP, TEST_PORT)],
        stdout=subprocess.DEVNULL, stderr=subprocess.DEVNULL)
    t0 = time.time()
    target = mb * 1048576
    got, t_last, got_last = 0, time.time(), 0
    while time.time() - t0 < 90:
        time.sleep(0.3)
        with sink.lock:
            got = sink.rx - start
        if got >= target:
            break
        if got != got_last:
            got_last, t_last = got, time.time()
        elif time.time() - t_last > 6:
            break  # stalled 6 s — wedge candidate or dead flow
    el = (time.time() - t0) if got >= target else (t_last - t0)
    p.kill()
    subprocess.run(["adb", "shell",
                    "pkill -f 'toybox nc' 2>/dev/null || true"],
                   stdout=subprocess.DEVNULL, stderr=subprocess.DEVNULL,
                   timeout=15)
    time.sleep(1.5)  # drain tail
    with sink.lock:
        got = sink.rx - start
    return got, max(el, 0.1)


def gkey12():
    addrs = [GKEY + i * 4 for i in range(12)]
    cmds = ["echo %08x > %s" % (a, POKE) for a in addrs]
    cmds.append("dmesg | busybox grep -a 'peek 0x' | busybox tail -16")
    out = ab_ctrs.zc(cmds, wait=3, hardcap=60)
    w = []
    for a in addrs:
        m = re.findall(r"peek 0x%08x = 0x([0-9a-f]+)" % a, out, re.I)
        w.append(int(m[-1], 16) if m else 0)
    return w


def wedgecap():
    print("==== WEDGE SIGNATURE CAPTURE ====")
    v1 = sample()
    show(v1, "wedge-A")
    for i in range(3):
        w = gkey12()
        print("  gkey12[%d]: %s" % (i, " ".join("%08x" % x for x in w)))
    ram1_sweep(ROWS_FULL, "wedge-FULL")
    time.sleep(10)
    v2 = sample()
    show(v2, "wedge-B (+10s)")
    pend = v2.get("tx_pending")
    sts1, sts2 = v1.get("idm_txsts"), v2.get("idm_txsts")
    print("==== FORK VERDICT ====")
    if pend is not None and pend >= 0x200:
        print("  tx_pending PINNED at 0x%x => ADMISSION WALL (candidates 1/2)"
              % pend)
    elif pend is not None:
        print("  tx_pending=%d (< 0x200, flowing) => CORRUPTION PRIMARY "
              "(candidate 3)" % pend)
    print("  IDM TX_STATUS %s -> %s (%s)" % (
        hx(sts1), hx(sts2), "frozen" if sts1 == sts2 else "moving"))
    return v1


def run(max_bursts=60, burst_mb=3):
    sink = Sink()
    sink.start()
    print("=== wedge_probe run: %d x %dMB bursts, sink %s:%d ==="
          % (max_bursts, burst_mb, HOST_WAN_IP, TEST_PORT))
    base = sample()
    show(base, "baseline")
    ram1_sweep(ROWS_FULL, "baseline-FULL")
    prev = base
    for n in range(1, max_bursts + 1):
        got, el = burst(sink, burst_mb)
        rate = got / el / 1e6 if el else 0
        cur = sample()
        dinj = (cur.get("tx_injected") or 0) - (prev.get("tx_injected") or 0)
        dfwd = d16(cur.get("cla_up_fwd"), prev.get("cla_up_fwd"))
        dmiss = d16(cur.get("cla_acl_fail"), prev.get("cla_acl_fail"))
        print("-- burst %d: %.2f MB in %.1fs (%.2f MB/s) | dinj=%d dfwd=%s "
              "dmiss=%s inj_total=%s pend=%s" %
              (n, got / 1e6, el, rate, dinj, dfwd, dmiss,
               cur.get("tx_injected"), cur.get("tx_pending")))
        show(cur, "after burst %d" % n)
        if n % 5 == 0:
            ram1_sweep(ROWS_LIGHT, "round %d" % n)
        wedged = False
        why = []
        if got < burst_mb * 1e6 * 0.2:
            wedged = True
            why.append("throughput collapsed (%.2f MB)" % (got / 1e6))
        if dinj > 500 and dmiss is not None and dmiss >= dinj * 0.8:
            wedged = True
            why.append("acl_fail tracks injections (dmiss=%s dinj=%d)"
                       % (dmiss, dinj))
        if wedged:
            print("!!!! WEDGE SUSPECTED at burst %d: %s !!!!" % (n, "; ".join(why)))
            wedgecap()
            # persistence check: one more burst then recapture
            got2, el2 = burst(sink, burst_mb)
            print("-- persistence burst: %.2f MB in %.1fs" % (got2 / 1e6, el2))
            if got2 < burst_mb * 1e6 * 0.2:
                print("!!!! WEDGE CONFIRMED (persists) !!!!")
                wedgecap()
                return
            print("-- recovered?? continuing --")
        prev = cur
    print("=== run complete, NO wedge in %d bursts (inj_total=%s) ==="
          % (max_bursts, prev.get("tx_injected")))


def lite_sample():
    """Light round: injected/fwd/miss + the SIPC drop nibbles only."""
    # gauge-trace set (2026-07-31): the 0x9238c28x/c29x live parse-pipeline
    # words (stock-under-traffic fc/5b/18/3d) + BMU alloc-result — hunting a
    # monotonic drain that freezes at wedge (the RED-1024 signature).
    names = (("cla_up_fwd", 0x9238c3c0), ("cla_acl_fail", 0x9238c3c4),
             ("cla_dn_fwd", 0x9238c3cc),   # LAN-egress forwards count HERE
             ("qmg_up_trap", 0x9234c05c), ("sipc_drop", 0x921cc004),
             ("tm_irq", 0x92340100),
             ("g280", 0x9238c280), ("g284", 0x9238c284), ("g290", 0x9238c290),
             ("g294", 0x9238c294), ("g298", 0x9238c298), ("g29c", 0x9238c29c),
             ("bmu_res", 0x9234800c))
    cmds = ["echo %08x > /sys/kernel/debug/zx_eth/poke" % a for _, a in names]
    cmds.append("dmesg | busybox grep -a 'peek 0x' | busybox tail -%d"
                % (len(names) + 4))
    cmds.append("busybox grep -a tx_injected /sys/kernel/debug/zx_eth/wifi_bind")
    out = ab_ctrs.zc(cmds, wait=2.5, hardcap=45)
    v = {}
    for name, addr in names:
        m = re.findall(r"peek 0x%08x = 0x([0-9a-f]+)" % addr, out, re.I)
        v[name] = int(m[-1], 16) if m else None
    m = re.search(r"tx_injected=(\d+)", out)
    v["tx_injected"] = int(m.group(1)) if m else None
    return v


def endur(target_frames=150000, burst_mb=8):
    """Endurance run: sustained fabric-ingress until target_frames injected
    (or wedge). Light sampling; full wedgecap on suspicion."""
    sink = Sink()
    sink.start()
    prev = lite_sample()
    print("=== endurance: target %d frames, %dMB bursts | start inj=%s ==="
          % (target_frames, burst_mb, prev.get("tx_injected")))
    n = 0
    while True:
        n += 1
        got, el = burst(sink, burst_mb)
        cur = lite_sample()
        dinj = (cur.get("tx_injected") or 0) - (prev.get("tx_injected") or 0)
        dfwd = d16(cur.get("cla_up_fwd"), prev.get("cla_up_fwd"))
        dmiss = d16(cur.get("cla_acl_fail"), prev.get("cla_acl_fail"))
        print("-- burst %d: %.2f MB @ %.2f MB/s | dinj=%d dfwd=%s dmiss=%s "
              "inj_total=%s sipc=%s" %
              (n, got / 1e6, got / el / 1e6, dinj, dfwd, dmiss,
               cur.get("tx_injected"), hx(cur.get("sipc_drop"))))
        sys.stdout.flush()
        bad = (got < burst_mb * 1e6 * 0.2) or \
              (dinj > 500 and dmiss is not None and dmiss >= dinj * 0.8)
        if bad:
            print("!!!! WEDGE SUSPECTED at burst %d (inj_total=%s) !!!!"
                  % (n, cur.get("tx_injected")))
            wedgecap()
            got2, _ = burst(sink, burst_mb)
            print("-- persistence burst: %.2f MB" % (got2 / 1e6))
            if got2 < burst_mb * 1e6 * 0.2:
                print("!!!! WEDGE CONFIRMED (persists) — endurance FAILED !!!!")
                return
            print("-- recovered (flake), continuing --")
        if (cur.get("tx_injected") or 0) >= target_frames:
            print("=== ENDURANCE PASSED: inj_total=%s >= %d, no wedge ==="
                  % (cur.get("tx_injected"), target_frames))
            return
        prev = cur


def _flow_start(sink, rate_kbps=800):
    """Continuous throttled phone->host push (one persistent connection)."""
    blk, n = 131072, max(1, rate_kbps // 400)
    p = subprocess.Popen(
        ["adb", "shell",
         "while true; do toybox dd if=/dev/zero bs=%d count=%d 2>/dev/null; "
         "toybox sleep 0.3; done | toybox nc %s %d" % (blk, n, HOST_WAN_IP,
                                                       TEST_PORT)],
        stdout=subprocess.DEVNULL, stderr=subprocess.DEVNULL)
    return p


def _flow_health(sink, secs=12):
    """(bytes_in_window, dinj, dfwd, dmiss) over secs."""
    with sink.lock:
        r0 = sink.rx
    a = lite_sample()
    time.sleep(secs)
    b = lite_sample()
    with sink.lock:
        r1 = sink.rx
    # fwd = UP counter + DN counter (a LAN egress counts in DN, a WAN egress
    # in UP) so the health gate works for BOTH egress paths.
    fu = d16(b.get("cla_up_fwd"), a.get("cla_up_fwd")) or 0
    fd = d16(b.get("cla_dn_fwd"), a.get("cla_dn_fwd")) or 0
    return (r1 - r0,
            (b.get("tx_injected") or 0) - (a.get("tx_injected") or 0),
            fu + fd,
            d16(b.get("cla_acl_fail"), a.get("cla_acl_fail")), b)


def discrim():
    """Phased collision discriminator on ONE continuous fabric-ingress flow:
    A) hashcalc bursts (shared HW hash engine, no CLA writes)
    B) fttest install/destroy churn (CLA indirect writes, unrelated slots)
    C) volume control to 100k frames (no SW collisions at all)
    Wedge after A => hash-engine sharing is the trigger; after B => indirect
    writes; only during C => volume/flow-transitions after all."""
    sink = Sink()
    sink.start()
    p = _flow_start(sink)
    print("=== discrim: continuous flow started, waiting for install ===")
    time.sleep(20)
    got, dinj, dfwd, dmiss, cur = _flow_health(sink, 12)
    print("-- phase0 baseline: %.2f MB dinj=%d dfwd=%s dmiss=%s inj=%s" %
          (got / 1e6, dinj, dfwd, dmiss, cur.get("tx_injected")))
    if got < 1e5 or dinj < 100:
        print("!! flow not healthy at baseline — aborting (rig problem?)")
        p.kill()
        return
    if dfwd is None or dfwd < dinj * 0.5:
        # NOHWGATE=1 (2026-07-31): deliberately run the SW-forward variant —
        # same fabric INJECTION volume via zx_idm_xmit, no CLA HW-forward
        # match. If this wedges too, the wedge is in the inject/admit path,
        # not in HW forwarding or egress back-pressure.
        if os.environ.get("NOHWGATE") != "1":
            print("!! flow not HW-offloaded (dfwd=%s dinj=%d) — aborting"
                  % (dfwd, dinj))
            p.kill()
            return
        print("!! NOT HW-offloaded (dfwd=%s) — continuing anyway per NOHWGATE "
              "(SW-forward injection-only variant)" % dfwd)

    def check(tag):
        got, dinj, dfwd, dmiss, cur = _flow_health(sink, 12)
        print("-- after %s: %.2f MB dinj=%d dfwd=%s dmiss=%s inj=%s" %
              (tag, got / 1e6, dinj, dfwd, dmiss, cur.get("tx_injected")))
        sys.stdout.flush()
        if got < 5e4:
            print("!!!! WEDGE after %s !!!!" % tag)
            wedgecap()
            p.kill()
            subprocess.run(["adb", "shell",
                            "pkill -f 'toybox nc' 2>/dev/null || true"],
                           stdout=subprocess.DEVNULL,
                           stderr=subprocess.DEVNULL, timeout=15)
            return False
        return True

    # phase C FIRST (2026-07-31 reorder): hands-off volume control. If the
    # flow wedges with ZERO SW ops beyond its own single install, the
    # SW-collision theory is wrong; if it survives to 100k, THEN inject
    # collisions (A/B) into the same still-healthy flow.
    print("== phase C: hands-off volume run to 100k frames ==")
    while True:
        time.sleep(30)
        got, dinj, dfwd, dmiss, cur = _flow_health(sink, 12)
        print("-- C: %.2f MB dinj=%d dfwd=%s dmiss=%s inj=%s tm_irq=%s | "
              "g28x %s %s %s %s %s %s bmu=%s" %
              (got / 1e6, dinj, dfwd, dmiss, cur.get("tx_injected"),
               hx(cur.get("tm_irq")), hx(cur.get("g280")), hx(cur.get("g284")),
               hx(cur.get("g290")), hx(cur.get("g294")), hx(cur.get("g298")),
               hx(cur.get("g29c")), hx(cur.get("bmu_res"))))
        sys.stdout.flush()
        if got < 5e4:
            print("!!!! WEDGE during phase C (inj=%s) — NO SW collision "
                  "needed !!!!" % cur.get("tx_injected"))
            wedgecap()
            p.kill()
            subprocess.run(["adb", "shell",
                            "pkill -f 'toybox nc' 2>/dev/null || true"],
                           stdout=subprocess.DEVNULL,
                           stderr=subprocess.DEVNULL, timeout=15)
            return
        if (cur.get("tx_injected") or 0) >= 100000:
            print("=== phase C PASSED: 100k+ frames, no wedge ===")
            break

    # phase A: hashcalc x20 under live traffic
    print("== phase A: 20x hashcalc under traffic ==")
    for _ in range(4):
        ab_ctrs.zc(["echo 11 22 33 44 55 66 77 88 99 aa bb cc > "
                    "/sys/kernel/debug/zx_eth/hashcalc"] * 5, wait=1.5,
                   hardcap=30)
    if not check("phase A (hashcalc)"):
        return

    # phase B: fttest install/destroy churn on synthetic tuples
    print("== phase B: 8x fttest install/destroy under traffic ==")
    for i in range(8):
        ck = 0x0fabc000 + i
        ab_ctrs.zc(["echo 'install %x c0a83263 0a2c4263 %x %x 5 38' > "
                    "/sys/kernel/debug/zx_eth/fttest" % (ck, 51000 + i,
                                                         9200 + i),
                    "echo 'destroy %x' > /sys/kernel/debug/zx_eth/fttest" % ck],
                   wait=1.5, hardcap=30)
    if not check("phase B (fttest churn)"):
        return

    print("=== discrim COMPLETE: flow survived C (100k) + A (hashcalc) + "
          "B (fttest churn) — no wedge ===")
    p.kill()
    subprocess.run(["adb", "shell", "pkill -f 'toybox nc' 2>/dev/null || true"],
                   stdout=subprocess.DEVNULL, stderr=subprocess.DEVNULL,
                   timeout=15)


if __name__ == "__main__":
    cmd = sys.argv[1] if len(sys.argv) > 1 else "sample"
    if cmd == "sample":
        show(sample(), "one-shot")
    elif cmd == "ram1":
        rows = ROWS_FULL if (len(sys.argv) > 2 and sys.argv[2] == "full") \
            else ROWS_LIGHT
        ram1_sweep(rows, cmd)
    elif cmd == "wedgecap":
        wedgecap()
    elif cmd == "run":
        mb = int(sys.argv[3]) if len(sys.argv) > 3 else 3
        run(int(sys.argv[2]) if len(sys.argv) > 2 else 60, mb)
    elif cmd == "endur":
        tgt = int(sys.argv[2]) if len(sys.argv) > 2 else 150000
        mb = int(sys.argv[3]) if len(sys.argv) > 3 else 8
        endur(tgt, mb)
    elif cmd == "discrim":
        discrim()
    else:
        sys.exit("unknown cmd %r" % cmd)
