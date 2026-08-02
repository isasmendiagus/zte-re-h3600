#!/usr/bin/env python3
"""
scratchpad/rig.py — operational rig for the ZTE ZX279128S / H3600 mainline port.

This is the STABLE, user-facing device tool (the commands that stay as the port
matures): host infra (bridge, tftp), device lifecycle (boot, flash, status) and
WiFi bring-up/test (wifi up/assoc/download). Transient reverse-engineering and
measurement commands (wan/client/offload/download-with-counters/counters/
wifi-ab, and the DTR power-cycle `reset`, which needs the USB-UART relay mod)
live in the companion devtool.py — it imports this file for every shared
constant/helper.

    rig.py bridge                 # host: own /dev/ttyUSB0, expose it on :9999/:9998
    rig.py tftp                   # host: serve tftp/ on 192.168.1.50:69
    rig.py boot [--wifi] [--long] # RAM-boot mainline via DTR->U-Boot->TFTP->bootm
    rig.py status                 # device/host health
    rig.py flash <k|rootfs|both|header> ...   # NAND flash (delegates to the flash tool)
    rig.py wifi up                # bring up the AP on the device (mt7915e + hostapd)
    rig.py wifi assoc             # connect the configured wifi client to the AP
    rig.py wifi download          # measure device->client download throughput

CONFIG (rig.config.json, optional — falls back to these defaults):
    host_nic:        the host NIC cabled to the device (default eth1 / $ZTE_HOST_NIC)
    wifi_client.backend:  adb | usb | manual   (how the AP is tested; adb = an
                     Android phone over adb, so no host WiFi card is needed; usb
                     = a USB WiFi dongle on the host; manual = connect by hand)

SAFETY (do not violate even under agent pressure):
  - DTR / RAM-boot ONLY. Never flash NAND unless you invoke `flash` on purpose,
    never trigger a stock rewrite.
  - NEVER memdump or raw-poke the MAC4 stat region (phys 0x92300000+); it stalls
    the internal bus (a prior agent hard-hung the device). Read MAC4 only via
    pipeline_stats.
  - TM[0x10058]/[0x10068] (UP/DN TX consumed-count) are CLEAR-ON-READ and owned
    by the driver's zx_sw_tx_reclaim_locked() since build #490 — never raw-poke
    them (steals a reclaim event, can reintroduce the TX-ring-overrun wedge).
  - sudo is NEVER persisted: every host-side privileged command goes through
    `echo <pw> | sudo -S ...` inline, one shot at a time.
"""
import argparse
import json
import os
import re
import subprocess
import sys
import threading
import time

HERE = os.path.dirname(os.path.abspath(__file__))
REPO = os.path.dirname(HERE)                        # repo root (…/zte-re-h3600)
sys.path.insert(0, HERE)
sys.path.insert(0, os.path.join(REPO, "lib"))       # for lib/uart.py
import ctr  # scratchpad/ctr.py — canonical counter map + REPL socket helper (:9999)
os.environ.setdefault("UART_TCP", "1")              # all UART goes through the bridge
import uart  # lib/uart.py — UART/bridge driver: DTR, cspstart→U-Boot, TFTP boot

from rich.console import Console
from rich.table import Table

CON = Console()


# ---------------------------------------------------------------------------
# config — optional rig.config.json (device tag + wifi client backend). Env
# vars still win for the few that have them (backwards-compatible).
# ---------------------------------------------------------------------------
def _load_cfg():
    path = os.path.join(HERE, "rig.config.json")
    try:
        with open(path) as f:
            return json.load(f)
    except (OSError, ValueError):
        return {}

CFG = _load_cfg()


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

# 2026-08-02: the container presents the device NIC as eth1 (MAC c8:a3:62:e9:59:00,
# formerly enxc8a362e95900). Override via rig.config.json host_nic or $ZTE_HOST_NIC.
HOST_NIC = os.environ.get("ZTE_HOST_NIC") or CFG.get("host_nic", "eth1")
HOST_IP = "192.168.1.50"
DEVICE_MGMT_IP = "192.168.1.1"

CLIENT_IP = "172.31.9.50"
LAN2_GW = "172.31.9.1"
LAN4_IP = "10.44.66.223"
WAN_GW = "10.44.66.250"

# Internet-download targets for the dev download/regression rig (devtool.py /
# regress.py import these). thinkbroadband is the external WAN target; the
# 10.44.66.133 ones are a LAN-local host http.server on the device's lan4 /24
# (modem-independent) — srv50m for multiflow (small, avoids the server's
# concurrent-conn ceiling), srv6g for sustained (tens of seconds at line rate).
# Full rationale: findings/qa_static_bughunt_2026-07-04.md + REGRESS_README.
DL_URL_DEFAULT = "http://80.249.99.148/1GB.zip"
DL_HOST_HDR = "ipv4.download.thinkbroadband.com"
DL_URL_LOCAL = "http://10.44.66.133:8080/srv50m.bin"
DL_URL_SUSTAINED_LOCAL = "http://10.44.66.133:8080/srv6g.bin"

REPL_MARKER_ALIVE = "RIG_ALIVE_%d" % (time.time() % 100000)

# Canonical counter addresses (byte-identical to ctr.py's CTRS). Kept here so
# the dev download sampler can read a SHORT list without the full sweep.
TS_CTRS = [
    ("acl_fail",    0x9238c3b8, True),   # CLA lookup-miss lo16
    ("cla_dn_fwd",  0x9238c3cc, True),   # CLA DN forward verdict lo16
    ("qmg_dn_hw",   0x9234c048, False),  # QMG DN hw_fwd (HW-forward enqueue)
    ("qmg_dn_trap", 0x9234c04c, False),  # QMG DN hw_trap-to-CPU (cumulative admit; see status)
]
DESOUT_BASE = 0x9238c394  # 9-word egress descriptor decode (validate_fix.py)

# nft flowtable HW-offload rig (devtool.py offload + regress.py import this).
OFFLOAD_CMDS = [
    "nft flush ruleset",
    "nft add table inet ft",
    "nft 'add flowtable inet ft f { hook ingress priority 0; devices = { lan2, lan4 }; flags offload; }'",
    "nft 'add chain inet ft ftfwd { type filter hook forward priority filter; }'",
    "nft 'add rule inet ft ftfwd ct state established ip protocol tcp flow add @f'",
]

# --- host-side infra (bridge + tftp) ---------------------------------------
TFTP_DIR = os.path.join(REPO, "tftp")
TFTP_LISTEN = "%s:69" % HOST_IP
BRIDGE_SCRIPT = os.path.join(REPO, "tasks/00.04.02.uart-bridge/uart_bridge.py")
BRIDGE_DATA_PORT, BRIDGE_CTL_PORT = 9999, 9998
FLASH_TOOL = os.path.join(REPO, "tasks/00.04.flash-tool/flash.py")

# --- boot images / bootargs ------------------------------------------------
BOOT_IMAGE = "zImage_dtb.uimg"
# WiFi bootargs: pci=nomsi + pcie_aspm=off MUST lead (MSI never delivers the
# MT7915 IRQ on this SoC; ZTE U-Boot corrupts the LAST bootarg). Proven 2026-05
# (docs/WIFI_STATUS.md). Eth boot uses U-Boot's default jffs2 line.
WIFI_BOOTARGS = ("pci=nomsi pcie_aspm=off console=ttyAMA0,115200n8 mem=256M "
                 "ignore_loglevel")

# --- WiFi AP (wifi up) -----------------------------------------------------
_wc = CFG.get("wifi_client", {})
AP_SSID = _wc.get("ssid", "H3600-AP-Test")
AP_PASS = _wc.get("pass", "h3600aptest")
AP_IP = "192.168.50.1"
MODULE_CHAIN = [                     # exact order; mt7915e loads firmware (~20s)
    ("pcie-zx279128s.ko", 6), ("cfg80211.ko", 4), ("mac80211.ko", 4),
    ("mt76.ko", 4), ("mt76-connac-lib.ko", 4), ("mt7915e.ko", 25),
]
HOSTAPD_CONF = [
    "interface=wlan1", "driver=nl80211", "ssid=%s" % AP_SSID,
    "country_code=ES", "hw_mode=a", "channel=36",
    "ieee80211n=1", "ieee80211ac=1",
    "ht_capab=[HT40+][HT40-][SHORT-GI-20][SHORT-GI-40]",
    "wmm_enabled=1", "auth_algs=1", "wpa=2", "wpa_key_mgmt=WPA-PSK",
    "rsn_pairwise=CCMP", "wpa_passphrase=%s" % AP_PASS,
]
UDHCPD_CONF = [
    "interface wlan1", "start 192.168.50.10", "end 192.168.50.100",
    "opt subnet 255.255.255.0", "opt router %s" % AP_IP,
    "opt lease 86400", "lease_file /tmp/udhcpd.leases", "max_leases 32",
]
WIFI_DL_HTTP_PORT = 8080
WIFI_DL_SIZE_MB = 64


# ---------------------------------------------------------------------------
# rich UI — spinners, colour, tables (degrades to plain output off-terminal).
# ---------------------------------------------------------------------------
class step:
    """Live spinner for a long op, then a ✓/✗ line. `with step("…"): …`."""
    def __init__(self, title):
        self.title, self._status = title, None
        self._outcome, self._note = "ok", ""

    def __enter__(self):
        self._status = CON.status("[bold cyan]%s[/]" % self.title, spinner="dots")
        self._status.start()
        return self

    def fail(self, note=""): self._outcome, self._note = "fail", note
    def note(self, note): self._note = note

    def __exit__(self, exc_type, exc, tb):
        self._status.stop()
        if exc_type is not None:
            CON.print("[bold red]✗[/] %s [dim](%s)[/]" % (self.title, exc)); return False
        mark = "[bold green]✓[/]" if self._outcome == "ok" else "[bold red]✗[/]"
        extra = " [dim]%s[/]" % self._note if self._note else ""
        CON.print("%s %s%s" % (mark, self.title, extra)); return False


def ok(msg):   CON.print("[bold green]✓[/] %s" % msg)
def warn(msg): CON.print("[bold yellow]![/] %s" % msg)
def fail(msg): CON.print("[bold red]✗[/] %s" % msg)
def info(msg): CON.print("[dim]·[/] %s" % msg)
def hdr(title): CON.rule("[bold]%s" % title)


# ---------------------------------------------------------------------------
# shared low-level helpers (devtool.py + regress.py import these).
# ---------------------------------------------------------------------------
def sh(cmd, timeout=60):
    """Host-side shell command. Returns (rc, stdout+stderr)."""
    r = subprocess.run(cmd, shell=True, capture_output=True, text=True, timeout=timeout)
    return r.returncode, (r.stdout or "") + (r.stderr or "")


def dev(cmds, wait=2.5):
    """Send shell commands to the device REPL over the UART bridge (:9999)."""
    if isinstance(cmds, str):
        cmds = [cmds]
    return ctr.zc(cmds, wait=wait)


def poke_read(addrs, wait=1.5):
    """Multi-address poke/peek read via the debugfs poke node + dmesg. Returns
    {addr: u32_or_None}. NOT for TM[0x10058]/[0x10068] — see SAFETY."""
    cmds = ["echo %08x > /sys/kernel/debug/zx_eth/poke" % a for a in addrs]
    cmds.append("dmesg | grep -a 'peek 0x' | tail -%d" % (len(addrs) + 2))
    out = dev(cmds, wait=wait)
    vals = {}
    for a in addrs:
        m = re.findall(r"peek 0x%08x = 0x([0-9a-f]+)" % a, out, re.I)
        vals[a] = int(m[-1], 16) if m else None
    return vals


def which_ns(nic):
    """Is `nic` in the root netns, netns 'client', or missing?"""
    rc, out = sh("ip -o link show %s 2>/dev/null" % nic)
    if rc == 0 and out.strip():
        return "root"
    rc, out = sh(SUDO + "ip netns exec client ip -o link show %s 2>/dev/null" % nic)
    if rc == 0 and out.strip():
        return "client"
    return "missing"


# --- netns client helpers (inlined from the former netns_up/down.sh) --------
def netns_usable():
    """True iff `ip netns exec` actually works here. Some containers create a
    netns fine but can't enter it (mount of /sys blocked). Probes a THROWAWAY
    netns so we never risk HOST_NIC."""
    sh(SUDO + "ip netns del _probe 2>/dev/null")
    sh(SUDO + "ip netns add _probe 2>/dev/null")
    rc, _ = sh(SUDO + "ip netns exec _probe true")
    sh(SUDO + "ip netns del _probe 2>/dev/null")
    return rc == 0


def netns_up():
    """Move HOST_NIC into netns 'client' on device lan2 (CLIENT_IP).

    SAFETY (2026-08-02): moving a passed-through NIC into a named netns and then
    failing makes the PHYSICAL NIC ESCAPE to the host on netns deletion — it
    vanishes from the container and only a container restart brings it back.
    This container can't `ip netns exec` (mount of /sys is blocked), so verify
    netns is fully usable BEFORE touching HOST_NIC."""
    if not netns_usable():
        fail("netns is unusable in this environment (ip netns exec fails) — "
             "NOT moving %s, it would escape the container. Configure the host "
             "NIC directly in the root ns instead." % HOST_NIC)
        return ""
    for c in [
        "ip netns add client",
        "ip link set %s netns client" % HOST_NIC,
        "ip netns exec client ip link set lo up",
        "ip netns exec client ip addr add %s/24 dev %s" % (CLIENT_IP, HOST_NIC),
        "ip netns exec client ip link set %s up" % HOST_NIC,
    ]:
        sh(SUDO + c)
    time.sleep(2)
    sh(SUDO + "ip netns exec client ip route add default via %s dev %s" % (LAN2_GW, HOST_NIC))
    _, out = sh(SUDO + "ip netns exec client ip route show")
    return out


def netns_down():
    """Return HOST_NIC to root ns @ HOST_IP + restore the TFTP route
    (idempotent). Mandatory pre-boot / teardown host restore."""
    sh(SUDO + "ip netns exec client ip link set %s netns 1" % HOST_NIC)
    sh(SUDO + "ip netns del client")
    time.sleep(1)
    sh(SUDO + "ip addr add %s/24 dev %s" % (HOST_IP, HOST_NIC))
    sh(SUDO + "ip link set %s up" % HOST_NIC)
    time.sleep(1)
    sh(SUDO + "ip route replace 192.168.1.0/24 dev %s src %s" % (HOST_NIC, HOST_IP))
    _, out = sh("ip -o addr show %s" % HOST_NIC)
    return out


# ---------------------------------------------------------------------------
# bridge / tftp — host infra. Idempotent: start only if not already up.
# ---------------------------------------------------------------------------
def _listening(port):
    _, out = sh("ss -ltn 2>/dev/null | grep ':%d '" % port)
    return bool(out.strip())


def cmd_bridge(args):
    if _listening(BRIDGE_DATA_PORT):
        ok("uart-bridge already listening on :%d/:%d." % (BRIDGE_DATA_PORT, BRIDGE_CTL_PORT))
        return 0
    with step("bridge: start uart_bridge (own /dev/ttyUSB0, expose :%d/:%d)" %
              (BRIDGE_DATA_PORT, BRIDGE_CTL_PORT)) as s:
        subprocess.Popen([sys.executable, BRIDGE_SCRIPT],
                         stdout=open("/tmp/uart_bridge.stdout.log", "ab"),
                         stderr=subprocess.STDOUT, start_new_session=True)
        for _ in range(20):
            if _listening(BRIDGE_DATA_PORT):
                break
            time.sleep(0.3)
        else:
            s.fail("did not come up")
            return 1
    ok("uart-bridge up.")
    return 0


def cmd_tftp(args):
    _, out = sh("ps -ef | grep '[i]n.tftpd' | grep -F '%s'" % TFTP_DIR)
    if out.strip():
        ok("tftpd already serving %s on %s." % (TFTP_DIR, TFTP_LISTEN))
        return 0
    with step("tftp: start in.tftpd serving %s on %s" % (TFTP_DIR, TFTP_LISTEN)):
        sh(SUDO + "pkill -f 'in.tftpd' ; true")
        time.sleep(1)
        subprocess.Popen(
            "%s in.tftpd -L --secure --create -a %s %s" % (SUDO, TFTP_LISTEN, TFTP_DIR),
            shell=True, stdout=open("/tmp/tftpd.log", "ab"),
            stderr=subprocess.STDOUT, start_new_session=True)
        time.sleep(1)
    _, out = sh("ps -ef | grep '[i]n.tftpd'")
    (ok if out.strip() else fail)("tftpd %s" % ("up" if out.strip() else "failed to start"))
    return 0 if out.strip() else 1


# ---------------------------------------------------------------------------
# boot — RAM-boot a mainline image via TFTP+U-Boot (DTR cold-reset first).
# Inlined from the former reboot_mainline*.py using lib/uart.py.
# ---------------------------------------------------------------------------
def _boot_eth(long_dtr):
    if long_dtr:
        uart.bridge_dtr_pulse.__defaults__ = ("localhost", BRIDGE_CTL_PORT, 10.0)
    ser = uart.open_port()
    return uart.flash_image_to_ram(ser, image_name=BOOT_IMAGE,
                                   kernel_ready_marker="REPL ready",
                                   kernel_ready_timeout=150, max_retries=3)


def _boot_wifi(long_dtr):
    hold = 10.0 if long_dtr else 2.0
    ser = uart.open_port()
    for attempt in range(1, 4):
        info("wifi boot attempt %d/3" % attempt)
        try:
            uart.bridge_dtr_pulse(hold_secs=hold)
        except Exception as e:
            warn("DTR pulse failed: %s" % e); continue
        if not uart.drive_cspstart_to_uboot(ser, password="Boot4128s!"):
            warn("could not reach U-Boot after DTR"); continue
        try:
            log_off = os.path.getsize(uart.LOG)
        except OSError:
            log_off = 0
        res = uart.run_uboot_seq(ser, [
            ("tftp 0x42000000 %s" % BOOT_IMAGE, 180),
            ("setenv bootargs '%s'" % WIFI_BOOTARGS, 5),
            ("bootm 0x42000000", 5),
        ], wait_for_prompt=True, prompt_timeout=180)
        if res["status"] != "ok":
            warn("U-Boot seq failed: %s" % res["status"])
            if res["status"] in ("tftp_fail", "timeout"):
                uart.recover_stuck_nic(os.environ.get("ZTE_TFTP_NIC", HOST_NIC))
            continue
        _fout = open(uart.LOG, "ab"); _stop = threading.Event()
        _t = threading.Thread(target=uart.log_loop, args=(ser, _fout, _stop, True),
                              daemon=True); _t.start()
        found = uart.wait_for_marker("REPL ready", timeout=240, start_offset=log_off)
        _stop.set(); _t.join(3)
        try: _fout.close()
        except Exception: pass
        if found:
            return True
        warn("kernel marker not seen — retry")
    return False


def cmd_boot(args):
    with step("boot: restore host NIC to root ns (required before TFTP)"):
        netns_down()
    kind = "WiFi (pci=nomsi)" if args.wifi else "eth (default jffs2)"
    dtr = "LONG 10s DTR / modem-revive" if args.long_dtr else "normal 2s DTR"
    hdr("boot: %s image via DTR→U-Boot→TFTP→bootm (%s)" % (kind, dtr))
    booter = _boot_wifi if args.wifi else _boot_eth
    if not booter(args.long_dtr):
        fail("boot did not reach 'REPL ready' — device may be wedged. "
             "Try `rig.py boot --long` (revives the WAN modem too).")
        return 1
    ok("kernel up (REPL ready)")
    # Condition-based settle (not a blind timer): rc.router rewrites early net
    # config AFTER 'REPL ready', so wait until it's GONE *and* the REPL echoes
    # back, polling instead of sleeping a fixed 27s.
    with step("boot: wait for REPL responsive + rc.router finished") as s:
        settled = False
        for _ in range(30):  # ~60s cap
            out = dev(["echo %s" % REPL_MARKER_ALIVE,
                       "busybox ps 2>/dev/null | busybox grep -c '[r]c.router'"], wait=2.0)
            alive = REPL_MARKER_ALIVE in out
            rc_running = bool(re.search(r"(?m)^\s*[1-9]\d*\s*$", out.split(REPL_MARKER_ALIVE)[-1]))
            if alive and not rc_running:
                settled = True
                break
            time.sleep(2)
        if not settled:
            s.fail("REPL not settled")
    if settled:
        ok("REPL responsive, rc.router finished")
        return 0
    warn("REPL didn't settle in time — run `rig.py status`")
    return 1


# ---------------------------------------------------------------------------
# flash — NAND flasher. Delegates to the proven tasks/00.04.flash-tool/flash.py
# (kernel|rootfs|both|header). Migrated here as a subcommand; do NOT run without
# intent (it writes NAND). Passes every extra arg straight through.
# ---------------------------------------------------------------------------
def cmd_flash(args):
    if not os.path.exists(FLASH_TOOL):
        fail("flash tool not found: %s" % FLASH_TOOL)
        return 1
    warn("NAND flash writes persistent storage — never touch the bootloader "
         "region and keep slot B intact (see tasks/00.04.flash-tool/README.md).")
    cmd = [sys.executable, FLASH_TOOL] + args.flash_args
    info("delegating: %s" % " ".join(cmd))
    return subprocess.call(cmd)


# ---------------------------------------------------------------------------
# WiFi AP bring-up (device) — inlined from the former wifi_up.py phases.
# ---------------------------------------------------------------------------
def _devrun(cmds, wait, label):
    out = dev(cmds, wait=wait)
    info("%s" % label)
    return out


def wifi_up_ap():
    with step("wifi up: sanity (mount proc/sys/debugfs, lo up, quiet printk)"):
        _devrun(["mkdir -p /proc /sys/kernel/debug /tmp 2>/dev/null",
                 "mount -t proc none /proc 2>/dev/null",
                 "mount -t sysfs none /sys 2>/dev/null",
                 "mount -t debugfs none /sys/kernel/debug 2>/dev/null",
                 "mount -t tmpfs none /tmp 2>/dev/null",
                 "busybox ip link set lo up",
                 "echo 1 > /proc/sys/kernel/printk"], 3, "mounted")
    already = dev(["iw dev 2>/dev/null | busybox grep -c Interface"], wait=3)
    if "2" in already[-8:]:
        info("wlan already present — skipping module load")
    else:
        for ko, w in MODULE_CHAIN:
            with step("wifi up: insmod %s" % ko):
                dev(["busybox insmod /lib/modules/%s 2>&1 | busybox head -1" % ko], wait=w)
    with step("wifi up: lan4 WAN addr + hostapd + udhcpd"):
        dev(["busybox ip addr add %s/24 dev lan4 2>/dev/null; busybox ip link set lan4 up" % LAN4_IP], wait=3)
        cmds = ["rm -f /tmp/hostapd.conf /tmp/udhcpd.conf"]
        cmds += ["echo '%s' >> /tmp/hostapd.conf" % l for l in HOSTAPD_CONF]
        cmds += ["echo '%s' >> /tmp/udhcpd.conf" % l for l in UDHCPD_CONF]
        cmds += ["touch /tmp/udhcpd.leases",
                 "ip addr add %s/24 dev wlan1 2>/dev/null; ip link set wlan1 up" % AP_IP,
                 "/bin/hostapd -B -t -f /tmp/hostapd.log /tmp/hostapd.conf",
                 "busybox udhcpd -f /tmp/udhcpd.conf > /tmp/udhcpd.log 2>&1 &"]
        dev(cmds, wait=12)
    out = dev(["iw dev wlan1 info | busybox grep -aE 'ssid|channel'",
               "busybox ps | busybox grep -aE 'hostapd|udhcpd' | busybox grep -av grep"], wait=4)
    for ln in out.splitlines():
        if "ssid" in ln or "channel" in ln or "hostapd" in ln or "udhcpd" in ln:
            info(ln.strip())
    okhap = "hostapd" in out and "H3600" in out
    (ok if okhap else warn)("AP %s" % ("up (SSID %s)" % AP_SSID if okhap else "not confirmed"))
    return 0 if okhap else 1


def wifi_serve_file():
    """Device: create a RAM test file + serve it via busybox httpd (for the
    download throughput test). Idempotent.

    NB: do NOT `pkill -f 'httpd -p 8080'` here — that pattern matches this very
    command line and self-kills the httpd we just started (SIGTERM, exit 15,
    :8080 never comes up). httpd daemonises and persists on its own; a second
    start harmlessly fails to bind if one is already running. (2026-08-02)"""
    dev(["busybox dd if=/dev/zero of=/tmp/testfile bs=1M count=%d 2>/dev/null" % WIFI_DL_SIZE_MB], wait=3)
    up = dev(["busybox netstat -ltn 2>/dev/null | busybox grep -c ':%d '" % WIFI_DL_HTTP_PORT], wait=2)
    if not re.search(r"\n[1-9]", up):
        dev(["busybox httpd -p %d -h /tmp" % WIFI_DL_HTTP_PORT], wait=2)


# ---------------------------------------------------------------------------
# WiFi client backends — how the AP is tested. Selected by rig.config.json
# wifi_client.backend (adb | usb | manual). This is the abstraction that lets
# the same `wifi assoc`/`wifi download` work with an Android phone over adb
# (no host WiFi card needed) OR a USB WiFi dongle OR a hand-connected client.
# ---------------------------------------------------------------------------
class WifiClient:
    name = "base"
    def assoc(self): raise NotImplementedError
    def download_mbps(self):
        """One download of the device's test file; return app-layer Mbps (or 0)."""
        raise NotImplementedError


class AdbWifiClient(WifiClient):
    """Android phone over adb. assoc via `svc wifi` toggle (reconnects the SAVED
    SSID — `cmd wifi connect-network` needs NETWORK_SETTINGS which adb-shell
    uid 2000 lacks). download via `curl --interface <src_ip>` on the phone (the
    src-IP bind is required: Android installs no route for a 'no-internet' WiFi,
    so an unbound socket gets ENETUNREACH). Proven 2026-08-02."""
    name = "adb"
    def __init__(self, cfg):
        self.serial = cfg.get("serial")
        self.src_ip = cfg.get("src_ip", "192.168.50.10")
        self._sflag = "-s %s " % self.serial if self.serial else ""

    def _adb(self, shellcmd, timeout=30):
        return sh("adb %sshell %s" % (self._sflag, shellcmd), timeout=timeout)

    def assoc(self):
        rc, out = sh("adb %sdevices" % self._sflag)
        if "device" not in out.replace("List of devices", ""):
            fail("no adb device — connect the phone (or save SSID %s once by hand)." % AP_SSID)
            return False
        # Persistent state so Android ROUTES to the (no-internet) AP instead of
        # blackholing it (`default dev dummy0`): disable captive-portal probing
        # and cellular data so WiFi is the routing default. Without this the
        # phone associates but every socket gets ENETUNREACH/rc7. Proven 2026-08-02.
        self._adb("'settings put global captive_portal_detection_enabled 0; "
                  "settings put global captive_portal_mode 0; "
                  "svc data disable; svc power stayon true; input keyevent KEYCODE_WAKEUP'")
        self._adb("svc wifi disable"); time.sleep(3)
        self._adb("svc wifi enable")
        for _ in range(8):
            time.sleep(4)
            st = dev(["iw dev wlan1 station dump | busybox grep -a Station"], wait=3)
            _, ip = sh("adb %sshell ip -o -4 addr show wlan0 2>/dev/null" % self._sflag)
            if re.search(r"Station [0-9a-f]{2}:", st) and "inet " in ip:
                return True
        return False

    def download_mbps(self, retries=3):
        for _ in range(retries):
            rc, out = self._adb(
                "\"curl --interface %s -s -o /dev/null -w '%%{speed_download}' "
                "http://%s:%d/testfile\"" % (self.src_ip, AP_IP, WIFI_DL_HTTP_PORT), timeout=60)
            m = re.search(r"([0-9.]+)", out.strip().splitlines()[-1] if out.strip() else "")
            mbps = float(m.group(1)) * 8 / 1e6 if m else 0.0
            if mbps:
                return mbps
            time.sleep(2)  # phone connection flaps on a no-internet AP; give it a beat
        return 0.0


class UsbWifiClient(WifiClient):
    """USB WiFi dongle on the HOST associates to the AP, then curl over that
    iface. UNTESTED (no dongle on the current rig) — implemented to the same
    interface so it's a drop-in when hardware is present. Needs nmcli or
    wpa_supplicant + a DHCP lease on the iface."""
    name = "usb"
    def __init__(self, cfg):
        self.iface = cfg.get("iface", "wlan0")
        self.src_ip = cfg.get("src_ip")

    def assoc(self):
        rc, out = sh(SUDO + "nmcli dev wifi connect '%s' password '%s' ifname %s"
                     % (AP_SSID, AP_PASS, self.iface), timeout=40)
        if rc != 0:
            warn("nmcli connect failed (%s). Configure %s by hand or install a "
                 "wpa_supplicant profile." % (out.strip()[:120], self.iface))
        return rc == 0

    def download_mbps(self):
        opt = "--interface %s " % (self.src_ip or self.iface)
        rc, out = sh("curl %s-s -o /dev/null -w '%%{speed_download}' "
                     "http://%s:%d/testfile" % (opt, AP_IP, WIFI_DL_HTTP_PORT), timeout=60)
        m = re.search(r"([0-9.]+)", out.strip())
        return float(m.group(1)) * 8 / 1e6 if m else 0.0


class ManualWifiClient(WifiClient):
    """No automation — print the SSID/pass and let a human connect + download."""
    name = "manual"
    def __init__(self, cfg): pass
    def assoc(self):
        warn("Connect your client to SSID '%s' / pass '%s' by hand, then re-run."
             % (AP_SSID, AP_PASS))
        return False
    def download_mbps(self):
        warn("manual backend: measure the download yourself."); return 0.0


_BACKENDS = {"adb": AdbWifiClient, "usb": UsbWifiClient, "manual": ManualWifiClient}


def wifi_client():
    cfg = CFG.get("wifi_client", {})
    backend = cfg.get("backend", "adb")
    cls = _BACKENDS.get(backend)
    if not cls:
        fail("unknown wifi_client.backend %r (valid: %s)" % (backend, ", ".join(_BACKENDS)))
        sys.exit(2)
    return cls(cfg.get(backend, {}))


def cmd_wifi_up(args):
    return wifi_up_ap()


def cmd_wifi_assoc(args):
    client = wifi_client()
    with step("wifi assoc: connect the '%s' client to %s" % (client.name, AP_SSID)) as s:
        okc = client.assoc()
        if not okc:
            s.fail("no station associated")
    if okc:
        out = dev(["iw dev wlan1 station dump | busybox grep -E 'Station|signal|tx bitrate'"], wait=3)
        for ln in out.splitlines():
            if any(k in ln for k in ("Station", "signal", "bitrate")):
                info(ln.strip())
        ok("client associated.")
        return 0
    return 1


def cmd_wifi_download(args):
    client = wifi_client()
    st = dev(["iw dev wlan1 station dump | busybox grep -a Station"], wait=3)
    if not re.search(r"Station [0-9a-f]{2}:", st):
        with step("wifi download: no client associated — connecting first") as s:
            if not client.assoc():
                s.fail("could not associate")
                fail("run `rig.py wifi assoc` (or save the SSID on the client once).")
                return 1
    with step("wifi download: serve %dMB test file on the device (:%d)" %
              (WIFI_DL_SIZE_MB, WIFI_DL_HTTP_PORT)):
        wifi_serve_file()
    hdr("wifi download: %d runs via the '%s' client (device→client TX)" % (args.n, client.name))
    speeds = []
    for i in range(args.n):
        with step("run %d/%d" % (i + 1, args.n)) as s:
            mbps = client.download_mbps()
            if mbps:
                s.note("%.1f Mbps" % mbps); speeds.append(mbps)
            else:
                s.fail("no data")
    if not speeds:
        fail("no successful downloads (client not associated? run `rig.py wifi assoc`).")
        return 1
    avg = sum(speeds) / len(speeds)
    tbl = Table(title="WiFi download (device→%s, %dMB file)" % (client.name, WIFI_DL_SIZE_MB))
    tbl.add_column("metric"); tbl.add_column("Mbps", justify="right"); tbl.add_column("MB/s", justify="right")
    tbl.add_row("average", "%.1f" % avg, "%.1f" % (avg / 8))
    tbl.add_row("peak", "%.1f" % max(speeds), "%.1f" % (max(speeds) / 8))
    tbl.add_row("min", "%.1f" % min(speeds), "%.1f" % (min(speeds) / 8))
    CON.print(tbl)
    ok("WiFi download: avg %.1f Mbps over %d runs." % (avg, len(speeds)))
    return 0


# ---------------------------------------------------------------------------
# status — read-only device/host health.
# ---------------------------------------------------------------------------
def cmd_status(args):
    hdr("status: host NIC placement (%s)" % HOST_NIC)
    info("%s is in: %s" % (HOST_NIC, which_ns(HOST_NIC)))
    _, out = sh("ip route get %s 2>&1 | head -1" % DEVICE_MGMT_IP)
    info("route to %s: %s" % (DEVICE_MGMT_IP, out.strip()))
    info("bridge :%d %s | tftpd %s" % (
        BRIDGE_DATA_PORT, "up" if _listening(BRIDGE_DATA_PORT) else "DOWN",
        "up" if sh("ps -ef | grep '[i]n.tftpd'")[1].strip() else "DOWN"))

    hdr("status: device REPL alive?")
    alive = REPL_MARKER_ALIVE in dev(["echo %s" % REPL_MARKER_ALIVE], wait=3.0)
    (ok if alive else fail)("REPL: %s" % ("ALIVE" if alive else "NO RESPONSE"))
    if not alive:
        return 1

    out = dev(["uname -r", "iw dev wlan1 station dump 2>/dev/null | busybox grep -c Station"], wait=3)
    for ln in out.splitlines():
        if re.match(r"\d+\.\d+", ln.strip()):
            info("kernel: %s" % ln.strip())

    hdr("status: modem reachable? (ping %s)" % WAN_GW)
    out = dev(["ping -c 2 -W 2 %s" % WAN_GW], wait=4.0)
    m = re.search(r"(\d+)% packet loss", out)
    info("modem: %s" % ("0% loss" if m and m.group(1) == "0" else out[-160:].strip()))

    hdr("status: qmg_dn_trap (cumulative admit counter — freely >1024 on a "
        "HEALTHY box since the RED_CFG bit6 fix; not a wedge signal by itself)")
    trap = poke_read([0x9234c04c]).get(0x9234c04c)
    info("qmg_dn_trap = %s (informational)" % trap)
    return 0


# ---------------------------------------------------------------------------
def main():
    p = argparse.ArgumentParser(
        description=__doc__, formatter_class=argparse.RawDescriptionHelpFormatter)
    sub = p.add_subparsers(dest="cmd", required=True)

    sub.add_parser("bridge", help="host: own /dev/ttyUSB0, expose :9999/:9998").set_defaults(func=cmd_bridge)
    sub.add_parser("tftp", help="host: serve tftp/ on 192.168.1.50:69").set_defaults(func=cmd_tftp)

    sp = sub.add_parser("boot", help="RAM-boot mainline (DTR→U-Boot→TFTP→bootm)")
    sp.add_argument("--wifi", action="store_true", help="boot the WiFi image (pci=nomsi bootargs)")
    sp.add_argument("--long", dest="long_dtr", action="store_true", help="10s DTR-off (revives WAN modem)")
    sp.set_defaults(func=cmd_boot)

    sub.add_parser("status", help="device/host health").set_defaults(func=cmd_status)

    sp = sub.add_parser("flash", help="NAND flash (delegates to the flash tool)")
    sp.add_argument("flash_args", nargs=argparse.REMAINDER,
                    help="passed straight to tasks/00.04.flash-tool/flash.py")
    sp.set_defaults(func=cmd_flash)

    wifi = sub.add_parser("wifi", help="AP bring-up / assoc / download test")
    wsub = wifi.add_subparsers(dest="wifi_cmd", required=True)
    wsub.add_parser("up", help="bring up the AP on the device").set_defaults(func=cmd_wifi_up)
    wsub.add_parser("assoc", help="connect the configured client to the AP").set_defaults(func=cmd_wifi_assoc)
    dl = wsub.add_parser("download", help="measure device→client download throughput")
    dl.add_argument("--n", type=int, default=6, help="number of download runs")
    dl.set_defaults(func=cmd_wifi_download)

    args = p.parse_args()
    sys.exit(args.func(args))


if __name__ == "__main__":
    main()
