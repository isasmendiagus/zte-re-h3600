#!/usr/bin/env python3
"""
scratchpad/rig.py — CANONICAL mainline test rig for the ZTE ZX279128S / H3600.

This is a CONSOLIDATION tool: every subcommand below assembles steps that were
already proven working in other one-off scripts in this directory (see the
"source" comment on each subcommand). It invents nothing new. Use this instead
of re-deriving the rig procedure from memory/findings on every session.

USAGE
  rig.py boot [--long]                          # DTR-boot mainline, wait for REPL
  rig.py wan                                     # device: lan4 WAN + NAT + verify modem ping
  rig.py client                                  # host: netns client on lan2 (anti-wifi-leak)
  rig.py offload                                 # device: nft flowtable {lan2,lan4} flags offload
  rig.py download [--url U] [--dur S] [--lport P] [--counters]
  rig.py counters                                # one-shot decoded pipeline-counter dump
  rig.py teardown [--skip-device]                # netns_down (mandatory) + device nft flush
  rig.py up [--long]                             # boot + wan + client + offload
  rig.py status                                  # device alive? modem 0%? wedged? host route ok?

TOPOLOGY (current cabling, 2026-07 sessions)
  Host NIC enxc8a362e95900 is TIME-SHARED between two roles and must be moved
  by `rig.py client` / `rig.py teardown`:
    - idle / boot / mgmt role:  root netns, 192.168.1.50/24  (talks to device
      mgmt IP 192.168.1.1 and serves TFTP for `boot`)
    - client role:              netns "client", 172.31.9.50/24 on device lan2
      (simulates a downstream LAN device; this is what `download` drives)
  Device: lan1 = mgmt (rc.router leaves an IP here — WRONG port, must be
  flushed), lan2 = client-facing (172.31.9.1 gw), lan4 = WAN via the DIGI
  modem (10.44.66.223/24, gw 10.44.66.250).

SAFETY (bake these in, do not violate even under agent pressure)
  - DTR / RAM-boot ONLY. Never flash NAND, never trigger a stock rewrite.
  - NEVER memdump or raw-poke the MAC4 stat region (phys 0x92300000+, i.e.
    npp_base+0x140000+). A prior agent hard-hung the device doing this — it
    stalls the internal bus. Read MAC4 counters ONLY via pipeline_stats.
  - TM[0x10058]/[0x10068] (UP/DN TX consumed-count) are CLEAR-ON-READ and, as
    of build #490 (the txflowctrl fix), are owned exclusively by the driver's
    own zx_sw_tx_reclaim_locked(). A raw poke of these addresses STEALS the
    reclaim event from the driver and can reintroduce the TX-ring-overrun
    wedge. This tool never pokes them — `counters`/`download --counters` read
    the equivalent sw_tx_pending/reclaimed/full_drops fields from
    /sys/kernel/debug/zx_eth/pipeline_stats instead.
  - Some fpga-indirect debug counters (sw_alcecnt/*_erlscnt/bmu_bperr,
    qmg_fifo_err, red_reg_up_dbg, smct...) read back CONSTANT GARBAGE via a
    raw `poke` (they need the stock latch protocol that isn't wired on
    mainline) — do not trust them; this tool doesn't expose them.
  - sudo is NEVER persisted: every host-side privileged command goes through
    `echo <pw> | sudo -S ...` inline, one shot at a time.

This tool is DEVICE-FREE to *write* (it doesn't touch the device by itself
outside of what you invoke) but every subcommand except `status`/`counters`
DOES drive the live device/host when run. Do not run it unless you are the
agent that owns the device for this session.
"""
import argparse
import os
import re
import subprocess
import sys
import threading
import time

HERE = os.path.dirname(os.path.abspath(__file__))
sys.path.insert(0, HERE)
import ctr  # scratchpad/ctr.py — canonical counter map + REPL socket helper (:9999)

# ---------------------------------------------------------------------------
# Known-good constants (from memory/zte-device-access.md, zte-roadmap.md,
# zte-redwedge-unicast-cpu.md and the scripts consolidated below). Change here
# once if the rig topology changes — every subcommand reads from these.
# ---------------------------------------------------------------------------
# Host sudo password: kept OUT of git. Provide via $ZTE_SUDO_PW or the
# git-ignored one-line file scratchpad/.sudo_pw (chmod 600). netns_up.sh /
# netns_down.sh read the same two sources.
def _read_sudo_pw():
    pw = os.environ.get("ZTE_SUDO_PW", "")
    if not pw:
        try:
            with open(os.path.join(HERE, ".sudo_pw")) as f:
                pw = f.read().strip()
        except OSError:
            pw = ""
    if not pw:
        sys.stderr.write("rig.py: WARNING: no sudo password — set $ZTE_SUDO_PW "
                         "or create scratchpad/.sudo_pw\n")
    return pw

SUDO_PW = _read_sudo_pw()
SUDO = "echo %s | sudo -S " % SUDO_PW
NS = "ip netns exec client "

HOST_NIC = "enxc8a362e95900"
HOST_IP = "192.168.1.50"
DEVICE_MGMT_IP = "192.168.1.1"

CLIENT_IP = "172.31.9.50"
LAN2_GW = "172.31.9.1"
LAN4_IP = "10.44.66.223"
WAN_GW = "10.44.66.250"

DL_URL_DEFAULT = "http://80.249.99.148/1GB.zip"
DL_HOST_HDR = "ipv4.download.thinkbroadband.com"

# [H2 multiflow-validity fix 2026-07-04] A LAN-local alternative to
# DL_URL_DEFAULT: a plain `python3 -m http.server 8080 --bind 10.44.66.133`
# on the HOST's wlo1-side address (same /24 as the device's lan4 WAN IP,
# LAN4_IP=10.44.66.223 -- no modem hop needed), serving from /tmp/httproot/
# (srv1g.bin/srv6g.bin, already used by scratchpad/sustained6g_validate.py
# for the same "avoid the flaky/rate-limited external modem path" reason).
# The external thinkbroadband server has a concurrent-connection ceiling
# that makes >1 simultaneous flow unreliable from this rig (H1 session:
# multiflow got 1/5 real connects, http=000 on the rest -- confirmed NOT a
# driver bug, see findings/qa_static_bughunt_2026-07-04.md's H1 session note
# and REGRESS_README). Traffic to this URL still transits the full real
# device path (client netns -> lan2 -> routing -> lan4 WAN -> host), so it
# exercises the SAME WAN-ingress DN HW-offload path as DL_URL_DEFAULT -- a
# LAN-local substitute for the flaky/rate-limited leg, not a shortcut around
# the driver.
#
# Points at srv50m.bin (50 MiB), NOT srv1g.bin/srv6g.bin: `python3 -m
# http.server` (SimpleHTTPRequestHandler) does NOT implement HTTP Range --
# it always serves the whole file with 200 (never 206), ignoring any `-r`/
# Range request. That means every concurrent-flow test that tries to
# Range-cap its per-flow size (regress.py's multiflow/high_way_collision)
# actually downloads the WHOLE file regardless -- against srv1g.bin (1 GiB)
# and this office WiFi hop (host is on wlo1, occasionally lossy -- observed
# 10-66% ICMP loss across the H2 session, unrelated to the driver), 5
# concurrent unbounded 1 GB fetches reliably saturated/starved the link (2
# flows completed at line rate, the other 3 got a clean http=000 at exactly
# --max-time, confirmed a link-contention timeout, not a driver issue or the
# instant-fail cold-path signature this file already handles elsewhere).
# 50 MiB keeps aggregate concurrent demand modest enough to finish reliably
# over an imperfect WiFi hop while still exercising a real multi-second
# HW-offloaded flow. If /tmp/httproot/srv50m.bin doesn't exist or the server
# isn't running, start one: `mkdir -p /tmp/httproot && cd /tmp/httproot &&
# dd if=/dev/urandom of=srv50m.bin bs=1M count=50 && python3 -m http.server
# 8080 --bind 10.44.66.133 &` (srv1g.bin/srv6g.bin, if present from an
# earlier sustained-download validation session, are unaffected -- this
# constant is the only thing that changed which file regress.py points at).
DL_URL_LOCAL = "http://10.44.66.133:8080/srv50m.bin"

# [H3 session, sustained_download test-validity fix 2026-07-04] Same host,
# same LAN-local hop as DL_URL_LOCAL (device lan4 -> host's 10.44.66.133,
# modem-INDEPENDENT — the real upstream/internet link is never touched), but
# a MUCH bigger file: sustained_download needs several tens of seconds of
# genuinely sustained line-rate transfer to be a meaningful wedge-regression
# guard (a 50 MiB file finishes in well under a second at this rig's ~90 MB/s
# LAN-local throughput — see DL_URL_LOCAL's own comment on why multiflow
# deliberately stays small; sustained_download deliberately wants the
# opposite). srv6g.bin (6 GiB) mirrors the file scratchpad/
# sustained6g_validate.py already validated a multi-GB sustained run against
# pre-H3 (same http.server, same host, same bind address); regenerate with
# `dd if=/dev/urandom of=/tmp/httproot/srv6g.bin bs=1M count=6144` if it's
# ever missing. Before this fix sustained_download used rig.DL_URL_DEFAULT
# (the external thinkbroadband 1 GB file over the real WAN modem) — a modem
# hiccup mid-run (observed repeatedly this project, e.g. the "a modem drop is
# not a driver bug" distinction throughout STATE.md/memory) failed the test
# for a reason that has nothing to do with the driver. regress.py's
# --sustained-modem flag restores the old external/modem-dependent target for
# a deliberate real-world spot check.
DL_URL_SUSTAINED_LOCAL = "http://10.44.66.133:8080/srv6g.bin"

REPL_MARKER_ALIVE = "RIG_ALIVE_%d" % (time.time() % 100000)

# Canonical counter addresses (byte-identical to scratchpad/ctr.py's CTRS and
# the *_e2e_native.py / wedge_run.py time-series list — DO NOT invent new
# addresses here, only reuse). Kept local too so `download --counters` can
# sample a SHORT list quickly without pulling the full ~28-counter sweep.
TS_CTRS = [
    ("acl_fail",    0x9238c3b8, True),   # CLA lookup-miss lo16
    ("cla_dn_fwd",  0x9238c3cc, True),   # CLA DN forward verdict lo16
    ("qmg_dn_hw",   0x9234c048, False),  # QMG DN hw_fwd (HW-forward enqueue)
    ("qmg_dn_trap", 0x9234c04c, False),  # QMG DN hw_trap-to-CPU (saturates @1024 = wedge signature)
]
DESOUT_BASE = 0x9238c394  # 9-word egress descriptor decode (validate_fix.py)


# ---------------------------------------------------------------------------
# small helpers
# ---------------------------------------------------------------------------
def hdr(title):
    print("\n=== %s ===" % title, flush=True)


def sh(cmd, timeout=60):
    """Host-side shell command. Returns (rc, stdout+stderr)."""
    r = subprocess.run(cmd, shell=True, capture_output=True, text=True, timeout=timeout)
    return r.returncode, (r.stdout or "") + (r.stderr or "")


def dev(cmds, wait=2.5):
    """Send a list of shell commands to the device REPL over the UART bridge
    (:9999, scratchpad/ctr.py's zc()). Returns the raw echoed text."""
    if isinstance(cmds, str):
        cmds = [cmds]
    return ctr.zc(cmds, wait=wait)


def poke_read(addrs, wait=1.5):
    """Generic multi-address poke/peek read via the debugfs poke node + dmesg
    (same idiom as validate_fix.py/wedge_deep.py/stock_entry_test.py). Returns
    {addr: raw_u32_or_None}. Do NOT use this for TM[0x10058]/[0x10068] — see
    the SAFETY header."""
    cmds = ["echo %08x > /sys/kernel/debug/zx_eth/poke" % a for a in addrs]
    cmds.append("dmesg | grep -a 'peek 0x' | tail -%d" % (len(addrs) + 2))
    out = dev(cmds, wait=wait)
    vals = {}
    for a in addrs:
        m = re.findall(r"peek 0x%08x = 0x([0-9a-f]+)" % a, out, re.I)
        vals[a] = int(m[-1], 16) if m else None
    return vals


def which_ns(nic):
    """Is `nic` currently in the root netns or inside netns 'client'? Returns
    'root', 'client', or 'missing'."""
    rc, out = sh("ip -o link show %s 2>/dev/null" % nic)
    if rc == 0 and out.strip():
        return "root"
    rc, out = sh(SUDO + "ip netns exec client ip -o link show %s 2>/dev/null" % nic)
    if rc == 0 and out.strip():
        return "client"
    return "missing"


# ---------------------------------------------------------------------------
# boot — source: scratchpad/reboot_mainline.py + reboot_mainline_longdtr.py
# ---------------------------------------------------------------------------
def cmd_boot(args):
    hdr("boot: restore host NIC to root ns (idempotent, required before TFTP)")
    _host_restore()

    hdr("boot: DTR power-cycle -> U-Boot -> TFTP mainline -> bootm (%s)" %
        ("LONG DTR / modem-revive" if args.long_dtr else "normal DTR"))
    script = "reboot_mainline_longdtr.py" if args.long_dtr else "reboot_mainline.py"
    # [rig.py boot fix 2026-07-04] The underlying reboot script pipes raw
    # UART/serial bytes straight through to its own stdout (U-Boot/kernel
    # console noise during the DTR power-cycle, not just clean printable
    # text) — `text=True` with no `encoding`/`errors` decodes with the
    # platform default codec in STRICT mode, so a single non-UTF-8 byte on
    # the wire (garbled boot-time serial framing, binary console garbage
    # during the bootm handoff, etc.) raised UnicodeDecodeError and killed
    # this whole boot flow before it could ever see "BOOT_OK". Decode
    # permissively instead: errors="replace" swaps any undecodable byte for
    # U+FFFD rather than raising, so a single glitchy byte can never abort
    # the boot-status parse below.
    proc = subprocess.Popen([sys.executable, os.path.join(HERE, script)],
                             stdout=subprocess.PIPE, stderr=subprocess.STDOUT,
                             text=True, bufsize=1, encoding="utf-8",
                             errors="replace")
    out_lines = []
    for line in proc.stdout:
        print(line, end="", flush=True)
        out_lines.append(line)
    proc.wait()
    out = "".join(out_lines)
    if "BOOT_OK" not in out:
        print("\n[FAIL] boot script did not report BOOT_OK — device may be wedged "
              "mid-recovery. Do NOT proceed to wan/client/offload.")
        return 1

    hdr("boot: waiting 27s post-'REPL ready' — rc.router overwrites early net "
        "config if you configure too soon")
    time.sleep(27)

    out = dev(["echo %s" % REPL_MARKER_ALIVE], wait=3.0)
    if REPL_MARKER_ALIVE in out:
        print("[OK] REPL responsive post-settle.")
        return 0
    print("[WARN] boot script said BOOT_OK but REPL didn't answer the settle-check. "
          "Retry `rig.py status` before configuring.")
    return 1


def _host_restore():
    """Idempotent: move HOST_NIC back to root ns @ HOST_IP + restore the TFTP
    route. Source: scratchpad/netns_down.sh (called as-is)."""
    rc, out = sh("bash %s" % os.path.join(HERE, "netns_down.sh"), timeout=30)
    print(out.strip())
    return rc


# ---------------------------------------------------------------------------
# wan — source: scratchpad/rig.py's prior SETUP/CHECK lists (device-side NAT
# router config), extended with the modem-ping verification the roadmap calls
# out as the mandatory post-check.
# ---------------------------------------------------------------------------
WAN_SETUP_CMDS = [
    "ip addr flush dev lan1",  # rc.router leaves the LAN mgmt IP here = WRONG port
    "ip addr add %s/24 dev lan2 2>/dev/null; ip link set lan2 up" % LAN2_GW,
    "ip addr add %s/24 dev lan4 2>/dev/null; ip link set lan4 up" % LAN4_IP,
    "ip route add default via %s 2>/dev/null" % WAN_GW,
    "echo 1 > /proc/sys/net/ipv4/ip_forward",
    "iptables -t nat -F; iptables -F FORWARD; iptables -P FORWARD ACCEPT",
    "iptables -t nat -A POSTROUTING -o lan4 -j MASQUERADE",
]


def cmd_wan(args):
    hdr("wan: device lan4 WAN + MASQUERADE + FORWARD accept lan2<->lan4")
    out = dev(WAN_SETUP_CMDS, wait=4.0)
    print(out[-1500:])

    hdr("wan: verify modem reachability (ping %s)" % WAN_GW)
    out = dev(["ping -c 3 -W 2 %s" % WAN_GW], wait=5.0)
    print(out[-500:])
    m = re.search(r"(\d+)% packet loss", out)
    if m and m.group(1) == "0":
        print("[OK] modem 0%% loss.")
        return 0
    print("[FAIL] modem NOT reachable (%s). If this persists, `rig.py boot --long` "
          "power-cycles the modem for >=10s and usually revives it "
          "(memory/zte-device-access.md)." % (m.group(0) if m else "no ping reply"))
    return 1


# ---------------------------------------------------------------------------
# client — source: scratchpad/netns_up.sh (called as-is)
# ---------------------------------------------------------------------------
def cmd_client(args):
    hdr("client: move %s into netns 'client' on lan2 (%s/24) — "
        "ANTI-WIFI-LEAK: traffic must go device<->modem, not the host's wifi" %
        (HOST_NIC, CLIENT_IP))
    rc, out = sh("bash %s" % os.path.join(HERE, "netns_up.sh"), timeout=30)
    print(out.strip())
    if "default" in out and LAN2_GW in out:
        print("[OK] client netns has a default route via the device.")
        return 0
    print("[WARN] could not confirm the default route in netns 'client' — "
          "check `ip netns exec client ip route`.")
    return 1


# ---------------------------------------------------------------------------
# offload — source: scratchpad/rig.py's prior NFT list (nft flowtable, load
# BEFORE the download per the roadmap).
# ---------------------------------------------------------------------------
OFFLOAD_CMDS = [
    "nft flush ruleset",
    "nft add table inet ft",
    "nft 'add flowtable inet ft f { hook ingress priority 0; devices = { lan2, lan4 }; flags offload; }'",
    "nft 'add chain inet ft ftfwd { type filter hook forward priority filter; }'",
    "nft 'add rule inet ft ftfwd ct state established ip protocol tcp flow add @f'",
]


def cmd_offload(args):
    hdr("offload: nft flowtable {lan2,lan4} flags offload — load BEFORE download")
    out = dev(OFFLOAD_CMDS, wait=4.0)
    out += dev(["nft list ruleset | head -20"], wait=2.0)
    print(out[-1500:])
    if "flowtable" in out:
        print("[OK] flowtable installed.")
        return 0
    print("[WARN] could not confirm flowtable in `nft list ruleset` output.")
    return 1


# ---------------------------------------------------------------------------
# download — source: scratchpad/dl_run.py (bytes/rate/http + before/after
# counter delta) + dn_e2e_native.py / wedge_run.py (the counter TIME SERIES
# variant).
# ---------------------------------------------------------------------------
def cmd_download(args):
    dlout = "/tmp/rig_dl_%d.out" % int(time.time())
    url = args.url
    host_hdr = DL_HOST_HDR if url == DL_URL_DEFAULT else None

    hdr("download: kill stale curl in netns client, clear TIME_WAIT on lport %d" % args.lport)
    sh(SUDO + NS + "pkill -9 curl 2>/dev/null; true")
    time.sleep(0.5)

    b0 = ctr.read()
    print("B0:", " ".join("%s=%s" % (k, hex(v) if v is not None else "?") for k, v in b0.items()))

    series = []
    stop = threading.Event()

    def sampler(t0):
        while not stop.is_set():
            addrs = [a for _, a, _ in TS_CTRS]
            raw = poke_read(addrs, wait=1.0)
            row = {}
            for name, a, lo16 in TS_CTRS:
                v = raw.get(a)
                row[name] = (v & 0xffff) if (v is not None and lo16) else v
            series.append((time.time() - t0, row))
            stop.wait(2.0)

    t0 = time.time()
    if args.counters:
        th = threading.Thread(target=sampler, args=(t0,)); th.start()

    hdr("download: curl (netns client, --local-port %d, --max-time %ds) %s" %
        (args.lport, args.dur, url))
    host_opt = "-H 'Host: %s' " % host_hdr if host_hdr else ""
    range_opt = "-r 0-%d " % (args.size - 1) if args.size else ""
    curl_cmd = (SUDO + NS +
                "curl -s -o /dev/null --max-time %d %s%s"
                "-w 'bytes=%%{size_download} rate=%%{speed_download} http=%%{http_code} t=%%{time_total}\\n' "
                "--local-port %d %s > %s 2>&1" %
                (int(args.dur) + 15, host_opt, range_opt, args.lport, url, dlout))
    rc, _ = sh(curl_cmd, timeout=args.dur + 30)

    if args.counters:
        stop.set(); th.join(timeout=10)

    b1 = ctr.read()
    print("B1:", " ".join("%s=%s" % (k, hex(v) if v is not None else "?") for k, v in b1.items()))
    print("DELTA:", " ".join("%s=%+d" % (k, b1[k] - b0[k]) for k in b0
                              if b0.get(k) is not None and b1.get(k) is not None))

    try:
        lines = [l for l in open(dlout).read().splitlines() if "bytes=" in l]
        client_line = lines[-1] if lines else "(no bytes= line — curl likely failed)"
    except OSError:
        client_line = "(no output file)"
    print("CLIENT:", client_line)

    if args.counters and series:
        print("--- t | %s ---" % " ".join(n for n, _, _ in TS_CTRS))
        prev = None
        for t, row in series:
            vals = [row.get(n) for n, _, _ in TS_CTRS]
            d = ""
            if prev and all(v is not None for v in vals) and all(v is not None for v in prev):
                d = "  d(" + " ".join("%+d" % (a - b) for a, b in zip(vals, prev)) + ")"
            print("t=%6.2f " % t + " ".join(str(v) for v in vals) + d)
            if all(v is not None for v in vals):
                prev = vals
        last_trap = next((row.get("qmg_dn_trap") for _, row in reversed(series)
                           if row.get("qmg_dn_trap") is not None), None)
        if last_trap is not None and last_trap >= 1024:
            print("[note] qmg_dn_trap=%d exceeds 1024 — HEALTHY since the [red-arm "
                  "2026-07-04] RED_CFG bit6 fix (cumulative admit counter; the old "
                  "pinned-at-1024 wedge is fixed — see findings/"
                  "fix_churn_red_dnbank_2026-07-04.md)." % last_trap)

    m = re.search(r"http=(\d+)", client_line)
    ok = bool(m and m.group(1) == "200")
    print("[%s] download %s" % ("OK" if ok else "CHECK", "completed http=200" if ok else "did not confirm http=200"))
    return 0 if ok else 1


# ---------------------------------------------------------------------------
# counters — one-shot decoded pipeline dump.
# source: scratchpad/ctr.py (full sweep) + validate_fix.py (desOut decode) +
# the driver's own pipeline_stats (safe TX/RX accounting; see SAFETY header
# for why TM[0x10058]/[0x10068] are NOT read via raw poke here).
# ---------------------------------------------------------------------------
def cmd_counters(args):
    hdr("counters: full sweep (scratchpad/ctr.py CTRS)")
    v = ctr.read()
    for name, val in v.items():
        print("  %-14s = %s" % (name, hex(val) if val is not None else "?"))

    hdr("counters: acl request/fail split (raw, unmasked 0x9238c3b8)")
    raw = poke_read([0x9238c3b8])
    a = raw.get(0x9238c3b8)
    if a is not None:
        print("  acl_req(hi16)=%d  acl_fail(lo16)=%d" % ((a >> 16) & 0xffff, a & 0xffff))

    hdr("counters: desOut 9-word egress descriptor decode (base 0x%08x)" % DESOUT_BASE)
    addrs = [DESOUT_BASE + i * 4 for i in range(9)]
    w = poke_read(addrs)
    words = [w.get(a) or 0 for a in addrs]
    print("  words:", " ".join("%08x" % x for x in words))
    w2, w5, w6 = words[2], words[5], words[6]
    print("  dir=%d act=%d rsn=0x%x ram=0x%x dak=%d OUT=0x%x" % (
        (w2 >> 20) & 1, (w2 >> 21) & 3, (w2 >> 23) & 0x7f,
        ((w6 & 0x3f) << 1) | (w5 >> 31), (w6 >> 22) & 1, (w6 >> 23) & 0xf))

    hdr("counters: pipeline_stats (driver-safe TX accounting + per-queue RX, "
        "since build #490 the ONLY safe reader of the clear-on-read TM regs)")
    out = dev(["cat /sys/kernel/debug/zx_eth/pipeline_stats | "
               "busybox grep -E 'sw_tx_pending|sw_tx_full_drops|sw_tx_reclaimed|"
               "tm_irq_count|tm_napi_count|tm_rx_count|tm_tx_count|q\\['"],
              wait=2.5)
    for ln in out.splitlines():
        if any(k in ln for k in ("sw_tx", "tm_irq", "tm_napi", "tm_rx_count",
                                  "tm_tx_count", "q[")):
            print("  " + ln.strip())
    return 0


# ---------------------------------------------------------------------------
# teardown — source: scratchpad/netns_down.sh (mandatory host restore) +
# a light device-side nft flush (cosmetic — a fresh RAM boot wipes device
# state anyway, but useful if you want a clean slate without rebooting).
# ---------------------------------------------------------------------------
def cmd_teardown(args):
    hdr("teardown: restore host NIC to root ns (MANDATORY before any reboot)")
    _host_restore()

    if not args.skip_device:
        hdr("teardown: device-side nft flush (best-effort; skip with --skip-device "
            "if the device is already power-cycling/unreachable)")
        try:
            out = dev(["nft flush ruleset", "echo TEARDOWN_DONE"], wait=3.0)
            print(out[-500:])
        except Exception as e:
            print("[WARN] device-side cleanup failed (device may already be down): %s" % e)
    print("[OK] teardown complete.")
    return 0


# ---------------------------------------------------------------------------
# up — boot + wan + client + offload
# ---------------------------------------------------------------------------
def cmd_up(args):
    for name, fn, fn_args in [
        ("boot", cmd_boot, args),
        ("wan", cmd_wan, args),
        ("client", cmd_client, args),
        ("offload", cmd_offload, args),
    ]:
        rc = fn(fn_args)
        if rc != 0:
            print("\n[ABORT] step '%s' failed (rc=%d) — fix before continuing." % (name, rc))
            return rc
    print("\n[OK] rig fully up: boot + wan + client + offload. "
          "Next: `rig.py download --counters`.")
    return 0


# ---------------------------------------------------------------------------
# status — device-free-safe reads only.
# ---------------------------------------------------------------------------
def cmd_status(args):
    hdr("status: host NIC placement (%s)" % HOST_NIC)
    where = which_ns(HOST_NIC)
    print("  %s is in: %s" % (HOST_NIC, where))
    rc, out = sh("ip route get %s 2>&1 | head -1" % DEVICE_MGMT_IP)
    print("  route to %s: %s" % (DEVICE_MGMT_IP, out.strip()))

    hdr("status: device REPL alive?")
    out = dev(["echo %s" % REPL_MARKER_ALIVE], wait=3.0)
    alive = REPL_MARKER_ALIVE in out
    print("  REPL: %s" % ("ALIVE" if alive else "NO RESPONSE"))
    if not alive:
        print("  (skipping further device checks)")
        return 1

    hdr("status: modem reachable? (ping %s)" % WAN_GW)
    out = dev(["ping -c 2 -W 2 %s" % WAN_GW], wait=4.0)
    m = re.search(r"(\d+)% packet loss", out)
    print("  modem: %s" % (("0%% loss" if m and m.group(1) == "0" else out[-200:].strip())))

    hdr("status: qmg_dn_trap (CUMULATIVE admit counter — since the [red-arm "
        "2026-07-04] RED_CFG bit6 fix it freely exceeds 1024 on a HEALTHY box; "
        "wedge detection = the host->lan4 oracle, regress.py red_credit_recycle)")
    raw = poke_read([0x9234c04c])
    trap = raw.get(0x9234c04c)
    print("  qmg_dn_trap = %s (informational)" % trap)
    return 0


# ---------------------------------------------------------------------------
def main():
    p = argparse.ArgumentParser(description=__doc__,
                                 formatter_class=argparse.RawDescriptionHelpFormatter)
    sub = p.add_subparsers(dest="cmd", required=True)

    sp = sub.add_parser("boot", help="DTR-boot mainline, wait for REPL")
    sp.add_argument("--long", dest="long_dtr", action="store_true",
                     help="10s DTR-off (also revives the WAN modem)")
    sp.set_defaults(func=cmd_boot)

    sp = sub.add_parser("wan", help="device: lan4 WAN + NAT + verify modem ping")
    sp.set_defaults(func=cmd_wan)

    sp = sub.add_parser("client", help="host: netns client on lan2 (anti-wifi-leak)")
    sp.set_defaults(func=cmd_client)

    sp = sub.add_parser("offload", help="device: nft flowtable {lan2,lan4} flags offload")
    sp.set_defaults(func=cmd_offload)

    sp = sub.add_parser("download", help="run a download; measure throughput (+counters)")
    sp.add_argument("--url", default=DL_URL_DEFAULT)
    sp.add_argument("--size", type=int, default=0, help="cap bytes via Range (0 = whole file)")
    sp.add_argument("--dur", type=float, default=20.0, help="--max-time seconds for curl")
    sp.add_argument("--lport", type=int, default=40000)
    sp.add_argument("--counters", action="store_true",
                     help="sample acl_fail/cla_dn_fwd/qmg_dn_hw/qmg_dn_trap as a time series")
    sp.set_defaults(func=cmd_download)

    sp = sub.add_parser("counters", help="one-shot decoded pipeline-counter dump")
    sp.set_defaults(func=cmd_counters)

    sp = sub.add_parser("teardown", help="netns_down (mandatory) + device nft flush")
    sp.add_argument("--skip-device", action="store_true")
    sp.set_defaults(func=cmd_teardown)

    sp = sub.add_parser("up", help="boot + wan + client + offload")
    sp.add_argument("--long", dest="long_dtr", action="store_true")
    sp.set_defaults(func=cmd_up)

    sp = sub.add_parser("status", help="device alive? modem 0%% loss? wedged? host route ok?")
    sp.set_defaults(func=cmd_status)

    args = p.parse_args()
    sys.exit(args.func(args))


if __name__ == "__main__":
    main()
