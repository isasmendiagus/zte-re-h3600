#!/usr/bin/env python3
"""
scratchpad/devtool.py — DEV / RE experiments for the ZTE ZX279128S / H3600.

Companion to rig.py. rig.py holds the STABLE operational rig (boot, flash,
wifi bring-up, status — the commands that stay as the port matures). This file
holds the TRANSIENT reverse-engineering / measurement commands that exist only
to characterise or debug the driver and will be dropped once things stabilise:
the internet-download NAT rig (wan/client/offload/up/download), the pipeline
counter forensics (counters), the WiFi HW-offload A/B (wifi-ab), and the DTR
power-cycle (reset — dev-only because it needs the USB-UART's DTR→relay mod).

It imports rig.py for every shared constant/helper (rig.dev, rig.sh,
rig.poke_read, rig.netns_up/down, the counter maps, the UI). New one-off RE
probes should be added here as subcommands instead of as new loose scripts, so
the scratchpad doesn't sprawl again.

    devtool.py reset [--long]          # DTR power-cycle the device (relay mod)
    devtool.py wan                     # device: lan4 WAN + NAT + verify modem ping
    devtool.py client                  # host: netns client on lan2 (anti-wifi-leak)
    devtool.py offload                 # device: nft flowtable {lan2,lan4} offload
    devtool.py up [--long]             # boot + wan + client + offload
    devtool.py download [--url U] [--dur S] [--lport P] [--counters]
    devtool.py counters                # one-shot decoded pipeline-counter dump
    devtool.py teardown [--skip-device]# netns restore (mandatory) + device nft flush
    devtool.py wifi-ab [--dur S] [--n N]# WiFi HW-offload A/B (ftwifi on/off)

SAFETY: identical to rig.py's header — DTR/RAM-boot only, never NAND; never
poke the MAC4 stat region or the clear-on-read TM[0x10058]/[0x10068] regs.
"""
import argparse
import os
import re
import sys
import threading
import time

HERE = os.path.dirname(os.path.abspath(__file__))
sys.path.insert(0, HERE)
import rig     # scratchpad/rig.py — shared base (helpers, constants, UI)
import ctr     # scratchpad/ctr.py — counter map + REPL socket

# convenience aliases to rig's shared surface
dev, sh, poke_read, hdr = rig.dev, rig.sh, rig.poke_read, rig.hdr
ok, warn, fail, info, step = rig.ok, rig.warn, rig.fail, rig.info, rig.step
SUDO, NS = rig.SUDO, rig.NS


# ---------------------------------------------------------------------------
# reset — DTR power-cycle. DEV-ONLY: relies on the USB-UART's DTR pin wired to
# a relay that cuts the device's power rail. A user-final unit has no such
# cable, so this never belonged in rig.py.
# ---------------------------------------------------------------------------
def cmd_reset(args):
    hold = 10.0 if args.long_dtr else 2.0
    with step("reset: DTR power-cycle (%.0fs hold%s)" %
              (hold, ", also revives the WAN modem" if args.long_dtr else "")):
        rig.uart.bridge_dtr_pulse(hold_secs=hold)
    ok("DTR pulsed — device is rebooting (drive it with `rig.py boot`).")
    return 0


# ---------------------------------------------------------------------------
# wan — device lan4 WAN + NAT + FORWARD, then the mandatory modem-ping check.
# NOTE 2026-08-02: the mainline build has NO iptables and (on the tested main
# image) no nf_nat hook, so MASQUERADE cannot be installed there — the nft form
# below is the correct tool family and works on a kernel built WITH nf_nat.
# ---------------------------------------------------------------------------
WAN_SETUP_CMDS = [
    "ip addr flush dev lan1",  # rc.router leaves the LAN mgmt IP here = WRONG port
    "ip addr add %s/24 dev lan2 2>/dev/null; ip link set lan2 up" % rig.LAN2_GW,
    "ip addr add %s/24 dev lan4 2>/dev/null; ip link set lan4 up" % rig.LAN4_IP,
    "ip route add default via %s 2>/dev/null" % rig.WAN_GW,
    "echo 1 > /proc/sys/net/ipv4/ip_forward",
    "nft flush ruleset",
    "nft add table ip nat",
    "nft 'add chain ip nat post { type nat hook postrouting priority 100 ; }'",
    "nft 'add rule ip nat post oifname \"lan4\" masquerade'",
]


def cmd_wan(args):
    hdr("wan: device lan4 WAN + nft masquerade + forward")
    out = dev(WAN_SETUP_CMDS, wait=4.0)
    if "No such file or directory" in out or "not found" in out:
        warn("NAT setup errored — this image likely lacks nf_nat (see header).")
    hdr("wan: verify modem reachability (ping %s)" % rig.WAN_GW)
    out = dev(["ping -c 3 -W 2 %s" % rig.WAN_GW], wait=5.0)
    print(out[-400:])
    m = re.search(r"(\d+)% packet loss", out)
    if m and m.group(1) == "0":
        ok("modem 0% loss.")
        return 0
    fail("modem NOT reachable. `devtool.py reset --long` power-cycles it >=10s.")
    return 1


# ---------------------------------------------------------------------------
# client — host NIC into netns 'client' on device lan2 (anti-wifi-leak).
# ---------------------------------------------------------------------------
def cmd_client(args):
    hdr("client: move %s into netns 'client' on lan2 (%s/24)" %
        (rig.HOST_NIC, rig.CLIENT_IP))
    out = rig.netns_up()
    print(out.strip())
    if "default" in out and rig.LAN2_GW in out:
        ok("client netns has a default route via the device.")
        return 0
    warn("could not confirm the default route in netns 'client'.")
    return 1


# ---------------------------------------------------------------------------
# offload — nft flowtable {lan2,lan4} flags offload (load BEFORE the download).
# ---------------------------------------------------------------------------
OFFLOAD_CMDS = [
    "nft flush ruleset",
    "nft add table inet ft",
    "nft 'add flowtable inet ft f { hook ingress priority 0; devices = { lan2, lan4 }; flags offload; }'",
    "nft 'add chain inet ft ftfwd { type filter hook forward priority filter; }'",
    "nft 'add rule inet ft ftfwd ct state established ip protocol tcp flow add @f'",
]


def cmd_offload(args):
    hdr("offload: nft flowtable {lan2,lan4} flags offload")
    out = dev(OFFLOAD_CMDS, wait=4.0)
    out += dev(["nft list ruleset | head -20"], wait=2.0)
    print(out[-1200:])
    if "flowtable" in out:
        ok("flowtable installed.")
        return 0
    warn("could not confirm flowtable in nft ruleset.")
    return 1


# ---------------------------------------------------------------------------
# up — boot(rig) + wan + client + offload
# ---------------------------------------------------------------------------
def cmd_up(args):
    steps = [("boot", rig.cmd_boot, args), ("wan", cmd_wan, args),
             ("client", cmd_client, args), ("offload", cmd_offload, args)]
    for name, fn, a in steps:
        if fn(a) != 0:
            fail("step '%s' failed — fix before continuing." % name)
            return 1
    ok("rig fully up: boot + wan + client + offload. Next: `devtool.py download --counters`.")
    return 0


# ---------------------------------------------------------------------------
# download — internet download through the device + optional counter series.
# ---------------------------------------------------------------------------
def cmd_download(args):
    dlout = "/tmp/dev_dl_%d.out" % int(time.time())
    url = args.url
    host_hdr = rig.DL_HOST_HDR if url == rig.DL_URL_DEFAULT else None

    hdr("download: clear stale curl / TIME_WAIT on lport %d" % args.lport)
    sh(SUDO + NS + "pkill -9 curl 2>/dev/null; true")
    time.sleep(0.5)

    b0 = ctr.read()
    info("B0: " + " ".join("%s=%s" % (k, hex(v) if v is not None else "?") for k, v in b0.items()))

    series, stop = [], threading.Event()

    def sampler(t0):
        while not stop.is_set():
            addrs = [a for _, a, _ in rig.TS_CTRS]
            raw = poke_read(addrs, wait=1.0)
            row = {name: ((raw.get(a) & 0xffff) if (raw.get(a) is not None and lo16) else raw.get(a))
                   for name, a, lo16 in rig.TS_CTRS}
            series.append((time.time() - t0, row))
            stop.wait(2.0)

    t0 = time.time()
    if args.counters:
        th = threading.Thread(target=sampler, args=(t0,)); th.start()

    hdr("download: curl (netns client, --local-port %d, --max-time %ds)" % (args.lport, args.dur))
    host_opt = "-H 'Host: %s' " % host_hdr if host_hdr else ""
    range_opt = "-r 0-%d " % (args.size - 1) if args.size else ""
    curl_cmd = (SUDO + NS + "curl -s -o /dev/null --max-time %d %s%s"
                "-w 'bytes=%%{size_download} rate=%%{speed_download} http=%%{http_code} t=%%{time_total}\\n' "
                "--local-port %d %s > %s 2>&1" %
                (int(args.dur) + 15, host_opt, range_opt, args.lport, url, dlout))
    sh(curl_cmd, timeout=args.dur + 30)

    if args.counters:
        stop.set(); th.join(timeout=10)

    b1 = ctr.read()
    info("B1: " + " ".join("%s=%s" % (k, hex(v) if v is not None else "?") for k, v in b1.items()))
    print("DELTA:", " ".join("%s=%+d" % (k, b1[k] - b0[k]) for k in b0
                             if b0.get(k) is not None and b1.get(k) is not None))
    try:
        lines = [l for l in open(dlout).read().splitlines() if "bytes=" in l]
        client_line = lines[-1] if lines else "(no bytes= line — curl likely failed)"
    except OSError:
        client_line = "(no output file)"
    print("CLIENT:", client_line)

    if args.counters and series:
        tbl = rig.Table(title="pipeline counters (time series)")
        tbl.add_column("t (s)")
        for n, _, _ in rig.TS_CTRS:
            tbl.add_column(n)
        for t, row in series:
            tbl.add_row("%.2f" % t, *[str(row.get(n)) for n, _, _ in rig.TS_CTRS])
        rig.CON.print(tbl)

    m = re.search(r"http=(\d+)", client_line)
    good = bool(m and m.group(1) == "200")
    (ok if good else warn)("download %s" % ("http=200" if good else "did not confirm http=200"))
    return 0 if good else 1


# ---------------------------------------------------------------------------
# counters — one-shot decoded pipeline dump (sweep + acl split + desOut decode
# + driver-safe pipeline_stats).
# ---------------------------------------------------------------------------
def cmd_counters(args):
    hdr("counters: full sweep (ctr.py CTRS)")
    tbl = rig.Table(); tbl.add_column("counter"); tbl.add_column("value", justify="right")
    for name, val in ctr.read().items():
        tbl.add_row(name, hex(val) if val is not None else "?")
    rig.CON.print(tbl)

    hdr("counters: acl request/fail split (0x9238c3b8)")
    a = poke_read([0x9238c3b8]).get(0x9238c3b8)
    if a is not None:
        info("acl_req(hi16)=%d  acl_fail(lo16)=%d" % ((a >> 16) & 0xffff, a & 0xffff))

    hdr("counters: desOut 9-word egress descriptor decode (0x%08x)" % rig.DESOUT_BASE)
    addrs = [rig.DESOUT_BASE + i * 4 for i in range(9)]
    w = poke_read(addrs)
    words = [w.get(x) or 0 for x in addrs]
    info("words: " + " ".join("%08x" % x for x in words))
    w2, w5, w6 = words[2], words[5], words[6]
    info("dir=%d act=%d rsn=0x%x ram=0x%x dak=%d OUT=0x%x" % (
        (w2 >> 20) & 1, (w2 >> 21) & 3, (w2 >> 23) & 0x7f,
        ((w6 & 0x3f) << 1) | (w5 >> 31), (w6 >> 22) & 1, (w6 >> 23) & 0xf))

    hdr("counters: pipeline_stats (driver-safe TX accounting)")
    out = dev(["cat /sys/kernel/debug/zx_eth/pipeline_stats | "
               "busybox grep -E 'sw_tx_pending|sw_tx_full_drops|sw_tx_reclaimed|"
               "tm_irq_count|tm_napi_count|tm_rx_count|tm_tx_count|q\\['"], wait=2.5)
    for ln in out.splitlines():
        if any(k in ln for k in ("sw_tx", "tm_irq", "tm_napi", "tm_rx_count", "tm_tx_count", "q[")):
            info(ln.strip())
    return 0


# ---------------------------------------------------------------------------
# teardown — netns restore (mandatory before any reboot) + device nft flush.
# ---------------------------------------------------------------------------
def cmd_teardown(args):
    with step("teardown: restore host NIC to root ns (mandatory before reboot)"):
        rig.netns_down()
    if not args.skip_device:
        try:
            dev(["nft flush ruleset", "echo TEARDOWN_DONE"], wait=3.0)
        except Exception as e:
            warn("device-side cleanup failed (device may be down): %s" % e)
    ok("teardown complete.")
    return 0


# ---------------------------------------------------------------------------
# wifi-ab — WiFi HW-offload A/B: N runs each with ftwifi 0 vs 1, report the
# device→client throughput delta. Uses rig's configured wifi client backend.
# ---------------------------------------------------------------------------
def cmd_wifi_ab(args):
    client = rig.wifi_client()
    hdr("wifi-ab: %d runs/side, ftwifi OFF vs ON" % args.n)
    rig.wifi_serve_file()
    results = {}
    for ft in (0, 1):
        dev(["echo %d > /sys/kernel/debug/zx_eth/ftwifi" % ft], wait=1.5)
        speeds = [client.download_mbps() for _ in range(args.n)]
        speeds = [s for s in speeds if s]
        results[ft] = sum(speeds) / len(speeds) if speeds else 0.0
        info("ftwifi=%d  avg=%.1f Mbps  (%s)" % (ft, results[ft],
             " ".join("%.0f" % s for s in speeds)))
    tbl = rig.Table(title="WiFi HW-offload A/B")
    tbl.add_column("ftwifi"); tbl.add_column("avg Mbps", justify="right")
    tbl.add_row("0 (slow path)", "%.1f" % results[0])
    tbl.add_row("1 (HW offload)", "%.1f" % results[1])
    rig.CON.print(tbl)
    if results[0]:
        ok("offload gain: %.2fx" % (results[1] / results[0]))
    return 0


# ---------------------------------------------------------------------------
# build — produce tftp/zImage_dtb.uimg from source (the reproducible recipe,
# consolidated from build_slotA.py + stage_wifi_initramfs.sh, minus the NAND
# bits). Config = zx279128s_defconfig + netfilter.fragment (NAT/iptables/
# masquerade). Initramfs = tftp/initramfs.cpio.gz base + freshly-built modules
# + mt7915 firmware, embedded via CONFIG_INITRAMFS_SOURCE=/tmp/initramfs_extract.
# ---------------------------------------------------------------------------
KSRC = os.path.join(rig.REPO, "linux-v6.6")
BUILD = os.path.join(rig.REPO, "build")
MAKE = "make -C %s ARCH=arm CROSS_COMPILE=arm-linux-gnueabi- O=%s" % (KSRC, BUILD)
FRAG = os.path.join(rig.REPO, "tasks/00.01.eth-driver/configs/netfilter.fragment")
STAGE_USERLAND = os.path.join(rig.REPO, "tasks/00.01.eth-driver/scripts/stage_userland.sh")
STAGE_WIFI = os.path.join(rig.REPO, "tasks/00.07.wifi/scripts/stage_wifi_initramfs.sh")
INITRAMFS_DIR = "/tmp/initramfs_extract"
# The reproducible initramfs base is the TRACKED tree (real static-C /init REPL,
# bin/, lib/), NOT tftp/initramfs.cpio.gz — that cpio has a stale shell-script
# /init and boots to a kernel panic (SIGILL). (2026-08-02)
INITRAMFS_SRC = os.path.join(rig.REPO, "tasks/00.01.eth-driver/initramfs")
UIMG = os.path.join(rig.REPO, "tftp/zImage_dtb.uimg")
DTB = os.path.join(BUILD, "arch/arm/boot/dts/zte/zx279128s-h3600.dtb")


def _sh_checked(cmd, timeout, label):
    rc, out = sh(cmd, timeout=timeout)
    if rc != 0:
        fail("%s failed (rc=%d)" % (label, rc))
        print(out[-1500:])
        raise SystemExit(1)
    return out


def cmd_build(args):
    ncpu = os.cpu_count() or 4
    # config — regenerate only if missing (incremental otherwise). An in-tree
    # linux-v6.6/.config breaks O= builds ("source tree not clean") — clean it.
    if os.path.exists(os.path.join(KSRC, ".config")):
        warn("in-tree .config present — running mrproper (O= build needs a clean tree)")
        _sh_checked("make -C %s ARCH=arm mrproper" % KSRC, 300, "mrproper")
    if not os.path.exists(os.path.join(BUILD, ".config")) or args.reconfig:
        with step("build: config (zx279128s_defconfig + netfilter/NAT fragment)"):
            _sh_checked("%s zx279128s_defconfig" % MAKE, 120, "defconfig")
            _sh_checked("%s/scripts/kconfig/merge_config.sh -m -O %s %s/.config %s"
                        % (KSRC, BUILD, BUILD, FRAG), 120, "merge fragment")
            _sh_checked("%s olddefconfig" % MAKE, 120, "olddefconfig")
            for opt, act in [("CFG80211_CERTIFICATION_ONUS", "--enable"),
                             ("CFG80211_REQUIRE_SIGNED_REGDB", "--disable")]:
                sh("%s/scripts/config --file %s/.config %s %s" % (KSRC, BUILD, act, opt))
    rc, out = sh("grep -c '^CONFIG_NF_NAT=y' %s/.config" % BUILD)
    if "1" not in out:
        fail("NAT not in .config — aborting (would defeat the purpose).")
        return 1
    ok("config ready (NAT enabled)")

    with step("build: make all (kernel + modules + dtbs) — can take ~15-25 min"):
        _sh_checked("%s -j%d all" % (MAKE, ncpu), 3600, "make all")

    with step("build: stage initramfs (tracked base + fresh modules + mt7915 firmware)"):
        _sh_checked("rm -rf %s && mkdir -p %s && cp -a %s/. %s/"
                    % (INITRAMFS_DIR, INITRAMFS_DIR, INITRAMFS_SRC, INITRAMFS_DIR),
                    120, "copy tracked initramfs base")
        # mount-point dirs — the tracked base ships only /dev, so without these
        # the C-init's mount("proc"/"sys"/"tmp") fails silently: no /proc/sys ->
        # no ip_forward -> no routing/NAT. (2026-08-02, the "before" cpio had them.)
        sh("mkdir -p %s/proc %s/sys/kernel/debug %s/tmp"
           % (INITRAMFS_DIR, INITRAMFS_DIR, INITRAMFS_DIR))
        # fresh in-tree modules → initramfs (vermagic must match this kernel).
        # NOTE: BUILD may be a SYMLINK (repo/build -> linux-v6.6/build); plain
        # `find <symlink>` (default -P) does NOT descend into it, which silently
        # copied ZERO fresh modules and shipped the tracked base's STALE .kos
        # (root-caused 2026-08-02: two boots ran a 12:08 eth driver while the
        # kernel was 16:45). realpath() makes find always descend.
        real_build = os.path.realpath(BUILD)
        sh("mkdir -p %s/lib/modules" % INITRAMFS_DIR)
        rc, out = sh("find %s -name '*.ko' \\( -path '*net/wireless*' -o -path '*mac80211*' "
                     "-o -path '*mt76*' -o -path '*ethernet/zte*' -o -path '*dwc3*' "
                     "-o -path '*xhci*' -o -path '*usb/storage*' \\) "
                     "-exec cp {} %s/lib/modules/ \\; -print | wc -l"
                     % (real_build, INITRAMFS_DIR), timeout=60)
        n_ko = int(out.strip() or 0)
        if n_ko < 5:
            fail("module staging copied only %d .ko files — build tree find is broken "
                 "(stale drivers would ship). Aborting." % n_ko)
            return 1
        info("staged %d fresh modules" % n_ko)
        # stage_userland recompiles /init from init.c and installs /etc/rc.router
        # (LAN/WAN bring-up, ip_forward, iptables MASQUERADE), iptables, udhcpd,
        # busybox. WITHOUT it the image boots but never sets up routing/NAT.
        _sh_checked("bash %s" % STAGE_USERLAND, 120, "stage userland (rc.router+iptables+init)")
        _sh_checked("bash %s %s" % (STAGE_WIFI, INITRAMFS_DIR), 120, "stage wifi firmware")

    with step("build: re-embed initramfs (make zImage)"):
        _sh_checked("%s -j%d zImage" % (MAKE, ncpu), 900, "make zImage")

    with step("build: wrap uImage"):
        _sh_checked("cat %s/arch/arm/boot/zImage %s > %s.bin"
                    % (BUILD, DTB, os.path.splitext(UIMG)[0]), 30, "concat")
        _sh_checked("mkimage -A arm -O linux -T kernel -C none -a 0x42000000 "
                    "-e 0x42000040 -n zx279128s-h3600 -d %s.bin %s"
                    % (os.path.splitext(UIMG)[0], UIMG), 30, "mkimage")
    sz = os.path.getsize(UIMG)
    ok("image built: %s (%.1f MB) — boot with `rig.py boot [--wifi]`" % (UIMG, sz / 1e6))
    return 0


# ---------------------------------------------------------------------------
# eth-download — repeatable ethernet forwarding throughput test. A client
# BEHIND the device (host NIC on a device LAN port) downloads a big file from
# the internet ROUTED+NAT'd by the device out its WAN (lan4). This measures the
# eth datapath's forward path, NOT the CPU slow-path of a device-terminated
# download. Run right after a fresh `rig.py boot` (a clean register state — lots
# of manual bridge/IP churn leaves the DSA switch in a bad state).
# ---------------------------------------------------------------------------
ETH_LAN_IP = "172.31.9.1"           # device LAN (bridge) gateway
ETH_HOST_IP = "172.31.9.50"         # host NIC address on the LAN
ETH_WAN_IP = "10.44.66.223"         # device WAN on the DIGI /24 (host eth0 is 10.44.66.x)
# default target: Ubuntu ISO (big, real). IP pinned so the device needs no DNS.
ETH_URL = "http://cdimage.ubuntu.com/ubuntu/releases/26.04/release/ubuntu-26.04-desktop-arm64.iso"
ETH_HOST_HDR = "cdimage.ubuntu.com"
ETH_TARGET_IP = "185.125.190.40"


def cmd_eth_download(args):
    hdr("eth-download: device forward+NAT rig (WAN lan4=%s, LAN br0=%s)" % (ETH_WAN_IP, ETH_LAN_IP))
    with step("device: WAN + default route + quiet console"):
        dev(["busybox ip addr flush dev lan4 2>/dev/null",
             "busybox ip addr add %s/24 dev lan4; busybox ip link set lan4 up" % ETH_WAN_IP,
             "busybox ip route add default via %s dev lan4 2>/dev/null" % rig.WAN_GW,
             "echo 0 > /proc/sys/kernel/printk"], wait=4)
    # LAN on the boot-linked port ONLY, NOT a bridge. A port's MAC is inited
    # (zx_smac_init_port) only if it had PHY link AT BOOT; bridging in ports
    # whose MAC never inited kills forwarding. The port with the cable is the
    # one dmesg logs as "PHY[N] link UP -> MAC[N]" — its lanN forwards.
    # Also: rc.router leaves FORWARD policy DROP, so forwarded packets die
    # until we set it ACCEPT. Both proven 2026-08-02.
    port = args.lan_port
    out = dev(["busybox dmesg 2>/dev/null | busybox grep -oE 'PHY\\[[0-9]\\] link UP' | busybox tail -1"], wait=2)
    m = re.search(r"PHY\[([0-9])\]", out)
    if m:
        port = "lan%s" % m.group(1)
        info("boot-linked port detected: %s" % port)
    with step("device: LAN on %s (boot-linked, MAC-inited) + FORWARD ACCEPT" % port):
        # Flush ALL LAN ports first: a stale LANIP on another lanN (fixed-link
        # = carrier always up) leaves a duplicate 172.31.9.0/24 route that wins
        # by FIB insertion order and black-holes every reply (the "intermittent
        # rc=28" bug, root-caused 2026-08-02).
        dev(["for d in lan0 lan1 lan2 lan3; do busybox ip addr flush dev $d 2>/dev/null; done",
             "busybox ip addr add %s/24 dev %s; busybox ip link set %s up" % (ETH_LAN_IP, port, port),
             "iptables -P FORWARD ACCEPT"], wait=3)
    out = dev(["cat /proc/sys/net/ipv4/ip_forward",
               "iptables -t nat -L POSTROUTING -n 2>&1 | busybox grep -c MASQUERADE",
               "ping -c2 -W3 %s | busybox tail -1" % ETH_TARGET_IP], wait=8)
    (ok if "0% packet loss" in out else warn)(
        "device WAN reachability: %s" % ("internet OK" if "0% packet loss" in out else "NO internet via WAN"))

    hdr("eth-download: host client on the LAN")
    with step("host: %s += %s + route target via device" % (rig.HOST_NIC, ETH_HOST_IP)):
        sh(rig.SUDO + "ip addr add %s/24 dev %s 2>/dev/null" % (ETH_HOST_IP, rig.HOST_NIC))
        sh(rig.SUDO + "ip link set %s up" % rig.HOST_NIC)
        sh(rig.SUDO + "ip route replace %s/32 via %s dev %s" % (ETH_TARGET_IP, ETH_LAN_IP, rig.HOST_NIC))
    # L2 sanity: serve a probe file on the device and fetch it from the host.
    dev(["busybox mkdir -p /tmp; busybox dd if=/dev/zero of=/tmp/probe bs=1k count=8 2>/dev/null",
         "busybox httpd -p 8090 -h /tmp 2>/dev/null"], wait=2)
    rc, out = sh("curl -s -o /dev/null -m5 -w '%%{http_code}' --interface %s http://%s:8090/probe"
                 % (ETH_HOST_IP, ETH_LAN_IP))
    if out.strip() != "200":
        fail("host can't reach the device LAN gateway (%s) — is the cable on the "
             "boot-linked port (%s)? Only the port with PHY link AT BOOT forwards "
             "(zx_smac_init_port). Re-boot with the cable on the jack and retry." % (ETH_LAN_IP, port))
        return 1
    ok("host<->device L2 up (via %s)" % port)

    hdr("eth-download: %d runs, %ds each, host->device->WAN->internet (sink /dev/null)" % (args.n, args.dur))
    speeds = []
    for i in range(args.n):
        with step("run %d/%d" % (i + 1, args.n)) as s:
            rc, out = sh("curl --interface %s --resolve %s:80:%s -s -o /dev/null "
                         "--max-time %d -w '%%{speed_download}' %s"
                         % (ETH_HOST_IP, ETH_HOST_HDR, ETH_TARGET_IP, args.dur, ETH_URL),
                         timeout=args.dur + 15)
            m = re.search(r"([0-9.]+)", out.strip())
            mbps = float(m.group(1)) * 8 / 1e6 if m else 0.0
            if mbps:
                s.note("%.1f Mbps" % mbps); speeds.append(mbps)
            else:
                s.fail("no data")
    if not speeds:
        fail("no successful runs (device forwarding/NAT or DSA L2 issue).")
        return 1
    avg = sum(speeds) / len(speeds)
    tbl = rig.Table(title="eth forwarding download (host->device->WAN)")
    tbl.add_column("metric"); tbl.add_column("Mbps", justify="right"); tbl.add_column("MB/s", justify="right")
    tbl.add_row("average", "%.1f" % avg, "%.1f" % (avg / 8))
    tbl.add_row("peak", "%.1f" % max(speeds), "%.1f" % (max(speeds) / 8))
    rig.CON.print(tbl)
    ok("eth forwarding download: avg %.1f Mbps over %d runs." % (avg, len(speeds)))
    return 0


# ---------------------------------------------------------------------------
# eth-hammer — L2 stability regression guard. From a FRESH boot: bind the LAN
# IP to the boot-linked port, start a device httpd, then fetch a 1 MiB file
# from the host N times in a row. Guards the 2026-08-02 duplicate-route bug
# (rc.router lan1 IP shadowing the boot-linked port -> intermittent rc=28).
# PASS = 100% of fetches return http 200 AND device->host ping is 0% loss.
# ---------------------------------------------------------------------------
def _detect_boot_lan(default="lan2"):
    """The lanN whose PHY the driver logged 'PHY[N] link UP' (N 0..3)."""
    out = dev(["busybox dmesg 2>/dev/null | busybox grep -oE 'PHY\\[[0-3]\\] link UP' | busybox tail -1"], wait=2)
    m = re.search(r"PHY\[([0-3])\]", out)
    if m:
        return "lan%s" % m.group(1)
    warn("no 'PHY[N] link UP' in dmesg — falling back to %s" % default)
    return default


def _eth_lan_setup(port):
    """Device: LAN IP on the boot-linked port ONLY (flush the rest — a stale
    LANIP on another fixed-link lanN shadows the route, see l2_stability_re
    finding), FORWARD ACCEPT, httpd :8090 with a 1 MiB test file. Host: test
    IP on HOST_NIC."""
    dev(["for d in lan0 lan1 lan2 lan3; do busybox ip addr flush dev $d 2>/dev/null; done",
         "busybox ip addr add %s/24 dev %s; busybox ip link set %s up" % (ETH_LAN_IP, port, port),
         "iptables -P FORWARD ACCEPT",
         "busybox dd if=/dev/zero of=/tmp/tf bs=1k count=1024 2>/dev/null",
         "busybox httpd -p 8090 -h /tmp 2>/dev/null"], wait=4)
    sh(rig.SUDO + "ip addr add %s/24 dev %s 2>/dev/null" % (ETH_HOST_IP, rig.HOST_NIC))
    sh(rig.SUDO + "ip link set %s up" % rig.HOST_NIC)


def cmd_eth_hammer(args):
    hdr("eth-hammer: L2 stability, %d consecutive host->device fetches" % args.n)
    port = _detect_boot_lan(args.lan_port)
    with step("device+host setup on %s (boot-linked)" % port):
        _eth_lan_setup(port)
    npass = 0
    fails = []
    for i in range(args.n):
        rc, out = sh("curl -s -o /dev/null -m5 --interface %s -w '%%{http_code}' "
                     "http://%s:8090/tf" % (ETH_HOST_IP, ETH_LAN_IP), timeout=10)
        if out.strip() == "200":
            npass += 1
        else:
            fails.append((i + 1, out.strip() or "rc=%s" % rc))
    for i, code in fails[:5]:
        warn("fetch %d failed (%s)" % (i, code))
    out = dev(["ping -c 5 -W 2 %s | busybox grep 'packet loss'" % ETH_HOST_IP], wait=8)
    ping_ok = " 0% packet loss" in out
    (ok if ping_ok else warn)("device->host ping: %s" % ("0% loss" if ping_ok else out.strip()[-60:]))
    (ok if npass == args.n else fail)("hammer: %d/%d http=200" % (npass, args.n))
    return 0 if (npass == args.n and ping_ok) else 1


# ---------------------------------------------------------------------------
# eth-offload — one-shot HW flow-offload forwarding throughput, from a FRESH
# boot, with a LAN-LOCAL fast source (the internet uplink is ~90 Mbps and
# can't show the eth ceiling). client==server==this host, so the flow must be
# forced onto the wire with a phantom SERVER IP — and the phantom translation
# must live on the HOST so the DEVICE flow stays plain MASQUERADE (UP=src
# rewrite, DN=dst rewrite — the ONLY per-direction rewrites the PM engine
# supports/validated; a DN src-rewrite comes out as src=0.0.0.0, and dual-NAT
# directions are declined to SW — see l2_stability_re_2026-08-02.md):
#   client: curl --interface 172.31.9.50 -> http://10.99.99.99:8000/big.bin
#           (10.99.99.99/32 routed via the device LAN gw on HOST_NIC)
#   device: routes 10.99.99.99/32 dev lan4 (static ARP -> host eth0 MAC) and
#           MASQUERADEs out lan4 — exactly the validated internet-NAT flow.
#   host:   PREROUTING on eth0 DNATs 10.99.99.99 -> eth0's real IP, so the
#           server socket answers; conntrack un-DNATs replies back to the
#           phantom -> the whole flow rides the wire twice through the device.
# Reports slow-path baseline vs offloaded MB/s + QMG DN hw_fwd delta, and
# checks the dual-NAT fallback (device-side DNAT on 10.99.99.98 + masquerade)
# still transfers via SW instead of black-holing.
# ---------------------------------------------------------------------------
ETH_PH_SRV = "10.99.99.99"       # phantom server IP (host eth0 PREROUTING DNAT)
ETH_PH_SRV_DUAL = "10.99.99.98"  # device-side DNAT variant -> dual-NAT (SW fallback)
ETH_SRV_PORT = 8000


def _host_eth0_ip():
    rc, out = sh("ip -o -4 addr show eth0 | head -1")
    m = re.search(r"inet ([0-9.]+)/", out)
    return m.group(1) if m else "10.44.66.30"


def _qmg_dn_hw():
    out = dev(["cat /sys/kernel/debug/zx_eth/pipeline_stats 2>/dev/null | busybox grep 'QMG DN'"], wait=3)
    m = re.search(r"hw_fwd=(\d+)", out)
    return int(m.group(1)) if m else -1


def cmd_eth_offload(args):
    srv_ip = _host_eth0_ip()
    www = "/tmp/zx_ethtest"
    hdr("eth-offload: LAN-local offloaded forwarding (host %s:%d through the device)"
        % (srv_ip, ETH_SRV_PORT))

    port = _detect_boot_lan(args.lan_port)
    with step("device+host base setup on %s (boot-linked)" % port):
        _eth_lan_setup(port)
    rc, out = sh("ip -o link show eth0")
    m = re.search(r"link/ether ([0-9a-f:]{17})", out)
    if not m:
        fail("cannot read host eth0 MAC")
        return 1
    eth0_mac = m.group(1)

    with step("host: big.bin server on eth0 + phantom DNAT/routes"):
        sh("mkdir -p %s" % www)
        sh("[ -f %s/big.bin ] || dd if=/dev/urandom of=%s/big.bin bs=1M count=%d status=none"
           % (www, www, args.mb), timeout=120)
        rc, out = sh("ss -ltn 2>/dev/null | grep -c ':%d '" % ETH_SRV_PORT)
        if out.strip() == "0":
            sh("cd %s && nohup python3 -m http.server %d --bind %s >/dev/null 2>&1 &"
               % (www, ETH_SRV_PORT, srv_ip))
            time.sleep(1)
        # phantom-server DNAT on the host's WAN-side NIC (see header comment)
        sh(rig.SUDO + "iptables -t nat -C PREROUTING -i eth0 -d %s -j DNAT --to-destination %s 2>/dev/null || "
           % (ETH_PH_SRV, srv_ip) +
           rig.SUDO + "iptables -t nat -A PREROUTING -i eth0 -d %s -j DNAT --to-destination %s"
           % (ETH_PH_SRV, srv_ip))
        sh(rig.SUDO + "ip route replace %s/32 via %s dev %s" % (ETH_PH_SRV, ETH_LAN_IP, rig.HOST_NIC))
        sh(rig.SUDO + "ip route replace %s/32 via %s dev %s" % (ETH_PH_SRV_DUAL, ETH_LAN_IP, rig.HOST_NIC))

    with step("device: WAN addr + masquerade + phantom route out lan4 (static ARP)"):
        # OWN the NAT state: stale PREROUTING rules (e.g. a leftover DNAT on
        # ETH_PH_SRV from ad-hoc experiments) silently turn the flow dual-NAT
        # -> declined to SW and the "offloaded" number measures nothing.
        dev(["iptables -t nat -F PREROUTING", "iptables -t nat -F POSTROUTING",
             "busybox ip addr flush dev lan4 2>/dev/null",
             "busybox ip addr add %s/24 dev lan4; busybox ip link set lan4 up" % ETH_WAN_IP,
             "iptables -t nat -A POSTROUTING -o lan4 -j MASQUERADE",
             "busybox ip route add %s/32 dev lan4 2>/dev/null" % ETH_PH_SRV,
             "busybox arp -s %s %s" % (ETH_PH_SRV, eth0_mac),
             # dual-NAT variant: device-side DNAT (+ masquerade) on .98
             "iptables -t nat -A PREROUTING -i %s -d %s -j DNAT --to-destination %s" % (port, ETH_PH_SRV_DUAL, srv_ip),
             "echo 0 > /proc/sys/kernel/printk"], wait=8)

    def fetch(ip, secs):
        rc, out = sh("curl -s -o /dev/null -m %d --interface %s "
                     "-w '%%{http_code} %%{size_download} %%{speed_download}' "
                     "http://%s:%d/big.bin" % (secs, ETH_HOST_IP, ip, ETH_SRV_PORT),
                     timeout=secs + 10)
        m = re.search(r"(\d{3}) (\d+) ([0-9.]+)", out.strip())
        if not m:
            return "000", 0, 0.0
        return m.group(1), int(m.group(2)), float(m.group(3))

    with step("slow-path baseline (no flowtable)") as s:
        dev(["nft flush ruleset"], wait=3)
        code, size, bps = fetch(ETH_PH_SRV, args.base_dur)
        base_mbs = bps / 1e6
        if size == 0:
            s.fail("baseline moved 0 bytes (http=%s) — phantom rig broken" % code)
            return 1
        s.note("%.2f MB/s (http=%s)" % (base_mbs, code))

    with step("install nft flowtable offload {%s, lan4}" % port):
        dev([c.replace("lan2", port) for c in rig.OFFLOAD_CMDS], wait=6)
    hw0 = _qmg_dn_hw()
    with step("OFFLOADED download (%d MiB)" % args.mb) as s:
        code, size, bps = fetch(ETH_PH_SRV, args.dur)
        off_mbs = bps / 1e6
        s.note("%.1f MB/s http=%s %d bytes" % (off_mbs, code, size))
    hw1 = _qmg_dn_hw()
    hw_delta = hw1 - hw0 if (hw0 >= 0 and hw1 >= 0) else -1

    with step("dual-NAT fallback (%s must transfer via SW, not black-hole)" % ETH_PH_SRV_DUAL) as s:
        dcode, dsize, dbps = fetch(ETH_PH_SRV_DUAL, 10)
        s.note("%.2f MB/s (http=%s)" % (dbps / 1e6, dcode))
    out = dev(["busybox dmesg | busybox grep -c 'dual-NAT'"], wait=3)
    declined = re.search(r"\n(\d+)", out) and int(re.search(r"\n(\d+)", out).group(1)) > 0

    tbl = rig.Table(title="eth-offload (host->%s->device->lan4->host eth0)" % port)
    tbl.add_column("leg"); tbl.add_column("MB/s", justify="right"); tbl.add_column("check")
    tbl.add_row("slow-path baseline", "%.2f" % base_mbs, "")
    tbl.add_row("HW-offloaded", "%.1f" % off_mbs, "qmg_dn_hw +%d" % hw_delta)
    tbl.add_row("dual-NAT SW fallback", "%.2f" % (dbps / 1e6), "declined logged: %s" % bool(declined))
    rig.CON.print(tbl)

    passed = (size > 0 and off_mbs > args.min_mbs and hw_delta > 1000
              and dsize > 0)
    (ok if passed else fail)(
        "eth-offload: offloaded %.1f MB/s (min %.0f), hw_fwd +%d, dual-NAT fallback %s"
        % (off_mbs, args.min_mbs, hw_delta, "OK" if dsize else "BROKEN"))
    return 0 if passed else 1


# ---------------------------------------------------------------------------
# wifi-offload — forwarded WiFi throughput from a FRESH boot: the adb phone
# (192.168.50.10 on the device AP) downloads big.bin from the host's fast NIC
# (eth0, on the WAN /24) THROUGH the device (wlan1 -> route+NAT -> lan4),
# slow-path vs HW-offloaded (ftwifi=1 + nft flowtable {lanN, lan4}; wlan1 must
# NOT be in the offload flowtable — it can't HW-bind; the UP leg is injected
# into the fabric by the driver's rx_handler and both directions' FLOW_CLS
# reach the driver via the lan4 block).
# ---------------------------------------------------------------------------
def _qmg_all():
    out = dev(["cat /sys/kernel/debug/zx_eth/pipeline_stats 2>/dev/null | busybox grep 'QMG DN'"], wait=3)
    m = re.search(r"QMG DN sw_fwd=(\d+) hw_fwd=(\d+) hw_trap=(\d+) \| UP sw_fwd=(\d+) hw_fwd=(\d+) hw_trap=(\d+)", out)
    return [int(x) for x in m.groups()] if m else None


def cmd_wifi_offload(args):
    srv_ip = _host_eth0_ip()
    www = "/tmp/zx_ethtest"
    hdr("wifi-offload: phone -> wlan1 -> device -> lan4 -> host %s:%d" % (srv_ip, ETH_SRV_PORT))
    port = _detect_boot_lan(args.lan_port)

    with step("host: big.bin server on eth0"):
        sh("mkdir -p %s" % www)
        sh("[ -f %s/big.bin ] || dd if=/dev/urandom of=%s/big.bin bs=1M count=%d status=none"
           % (www, www, args.mb), timeout=120)
        rc, out = sh("ss -ltn 2>/dev/null | grep -c ':%d '" % ETH_SRV_PORT)
        if out.strip() == "0":
            sh("cd %s && nohup python3 -m http.server %d --bind %s >/dev/null 2>&1 &"
               % (www, ETH_SRV_PORT, srv_ip))
            time.sleep(1)

    if rig.wifi_up_ap() != 0:
        fail("AP bring-up failed")
        return 1
    client = rig.wifi_client()
    if hasattr(client, "assoc") and not client.assoc():
        return 1

    with step("device: FORWARD ACCEPT + masquerade out lan4"):
        dev(["iptables -P FORWARD ACCEPT",
             "iptables -t nat -C POSTROUTING -o lan4 -j MASQUERADE 2>/dev/null || iptables -t nat -A POSTROUTING -o lan4 -j MASQUERADE",
             "echo 0 > /proc/sys/kernel/printk"], wait=5)

    def phone_fetch(secs):
        rc, out = sh("adb shell \"curl -s -o /dev/null -m %d --interface %s "
                     "-w '%%{http_code} %%{size_download} %%{speed_download}' "
                     "http://%s:%d/big.bin\"" % (secs, rig.wifi_client().src_ip
                                                 if hasattr(client, 'src_ip') else "192.168.50.10",
                                                 srv_ip, ETH_SRV_PORT),
                     timeout=secs + 15)
        m = re.search(r"(\d{3}) (\d+) ([0-9.]+)", out.strip())
        return (m.group(1), int(m.group(2)), float(m.group(3))) if m else ("000", 0, 0.0)

    with step("slow-path baseline (no flowtable, ftwifi irrelevant)") as s:
        dev(["nft flush ruleset"], wait=3)
        code, size, bps = fetchv = phone_fetch(args.base_dur)
        base_mbs = bps / 1e6
        if size == 0:
            s.fail("baseline moved 0 bytes (http=%s)" % code)
            return 1
        s.note("%.2f MB/s (http=%s)" % (base_mbs, code))

    with step("install flowtable {%s, lan4} + ftwifi=1" % port):
        dev([c.replace("lan2", port) for c in rig.OFFLOAD_CMDS] +
            ["echo 1 > /sys/kernel/debug/zx_eth/ftwifi"], wait=6)
    v1 = _qmg_all()
    with step("OFFLOADED phone download (%d MiB)" % args.mb) as s:
        code, size, bps = phone_fetch(args.dur)
        off_mbs = bps / 1e6
        s.note("%.2f MB/s http=%s %d bytes" % (off_mbs, code, size))
    v2 = _qmg_all()
    delta = {}
    if v1 and v2:
        delta = dict(zip(["dn_sw", "dn_hw", "dn_trap", "up_sw", "up_hw", "up_trap"],
                         [b - a for a, b in zip(v1, v2)]))
        info("QMG deltas: %s" % delta)

    tbl = rig.Table(title="wifi-offload (phone->wlan1->device->lan4->host eth0)")
    tbl.add_column("leg"); tbl.add_column("MB/s", justify="right"); tbl.add_column("check")
    tbl.add_row("slow-path baseline", "%.2f" % base_mbs, "")
    tbl.add_row("HW-offloaded", "%.2f" % off_mbs, "dn_hw +%d" % delta.get("dn_hw", -1))
    rig.CON.print(tbl)
    passed = size > 0 and off_mbs >= base_mbs * 0.9
    (ok if passed else fail)("wifi-offload: %.2f MB/s offloaded vs %.2f slow-path"
                             % (off_mbs, base_mbs))
    return 0 if passed else 1


def main():
    p = argparse.ArgumentParser(
        description=__doc__, formatter_class=argparse.RawDescriptionHelpFormatter)
    sub = p.add_subparsers(dest="cmd", required=True)

    sp = sub.add_parser("wifi-offload", help="forwarded WiFi throughput (phone->device->lan4->host), slow vs offloaded")
    sp.add_argument("--mb", type=int, default=1024)
    sp.add_argument("--dur", type=int, default=60)
    sp.add_argument("--base-dur", type=int, default=20)
    sp.add_argument("--lan-port", default="lan2")
    sp.set_defaults(func=cmd_wifi_offload)

    sp = sub.add_parser("eth-hammer", help="L2 stability: N consecutive host->device fetches (regression guard)")
    sp.add_argument("--n", type=int, default=30)
    sp.add_argument("--lan-port", default="lan2", help="fallback if dmesg PHY-link detect fails")
    sp.set_defaults(func=cmd_eth_hammer)

    sp = sub.add_parser("eth-offload", help="HW flow-offload line-rate test (LAN-local phantom rig)")
    sp.add_argument("--mb", type=int, default=1024, help="test file size MiB")
    sp.add_argument("--dur", type=int, default=90, help="offloaded fetch max seconds")
    sp.add_argument("--base-dur", type=int, default=10, help="slow-path baseline seconds")
    sp.add_argument("--min-mbs", type=float, default=20.0, help="PASS threshold MB/s")
    sp.add_argument("--lan-port", default="lan2", help="fallback if dmesg PHY-link detect fails")
    sp.set_defaults(func=cmd_eth_offload)

    sp = sub.add_parser("eth-download", help="ethernet forwarding throughput (client->device->WAN)")
    sp.add_argument("--n", type=int, default=4, help="number of runs")
    sp.add_argument("--dur", type=float, default=15.0, help="max-time seconds per run")
    sp.add_argument("--lan-port", default="lan2",
                    help="device LAN port the host is cabled to (auto-detected from dmesg PHY link)")
    sp.set_defaults(func=cmd_eth_download)

    sp = sub.add_parser("build", help="build tftp/zImage_dtb.uimg from source (defconfig+NAT+wifi fw)")
    sp.add_argument("--reconfig", action="store_true", help="regenerate .config from defconfig")
    sp.set_defaults(func=cmd_build)

    sp = sub.add_parser("reset", help="DTR power-cycle the device (relay mod)")
    sp.add_argument("--long", dest="long_dtr", action="store_true",
                    help="10s DTR-off (also revives the WAN modem)")
    sp.set_defaults(func=cmd_reset)

    sub.add_parser("wan", help="device: lan4 WAN + NAT + verify modem ping").set_defaults(func=cmd_wan)
    sub.add_parser("client", help="host: netns client on lan2").set_defaults(func=cmd_client)
    sub.add_parser("offload", help="device: nft flowtable {lan2,lan4} offload").set_defaults(func=cmd_offload)

    sp = sub.add_parser("up", help="boot + wan + client + offload")
    sp.add_argument("--wifi", action="store_true", help="boot the WiFi image")
    sp.add_argument("--long", dest="long_dtr", action="store_true")
    sp.set_defaults(func=cmd_up)

    sp = sub.add_parser("download", help="internet download through the device (+counters)")
    sp.add_argument("--url", default=rig.DL_URL_DEFAULT)
    sp.add_argument("--size", type=int, default=0, help="cap bytes via Range (0 = whole file)")
    sp.add_argument("--dur", type=float, default=20.0)
    sp.add_argument("--lport", type=int, default=40000)
    sp.add_argument("--counters", action="store_true")
    sp.set_defaults(func=cmd_download)

    sub.add_parser("counters", help="one-shot decoded pipeline-counter dump").set_defaults(func=cmd_counters)

    sp = sub.add_parser("teardown", help="netns restore (mandatory) + device nft flush")
    sp.add_argument("--skip-device", action="store_true")
    sp.set_defaults(func=cmd_teardown)

    sp = sub.add_parser("wifi-ab", help="WiFi HW-offload A/B (ftwifi off vs on)")
    sp.add_argument("--n", type=int, default=4, help="runs per side")
    sp.set_defaults(func=cmd_wifi_ab)

    args = p.parse_args()
    sys.exit(args.func(args))


if __name__ == "__main__":
    main()
