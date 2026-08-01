#!/usr/bin/env python3
"""One-command WiFi-AP bring-up on a freshly RAM-booted mainline H3600.

WHY: every WiFi session used to re-derive the same fragile sequence (module
chain -> hostapd -> udhcpd -> client assoc -> wifi_bind -> optional offload
rig) from findings docs. This codifies it, gotchas included, same principle
as rig.py/regress.py (see RIG_README.md).

Usage:
    python3 wifi_up.py all                # sanity+wan+wifi+conf+daemons+bind+verify
    python3 wifi_up.py all --adb          # ... + associate the adb Android first
    python3 wifi_up.py all --adb --offload  # ... + nft flowtable rig + ftwifi=1
    python3 wifi_up.py <phase> [...]      # individual phases, in any order
Phases: sanity wan wifi conf daemons assoc bind offload verify

Baked-in gotchas (each cost a session to find):
  * udhcpd MUST run foregrounded (-f) with its output logged — a daemonized
    udhcpd died silently inside the STA's DHCP retry window (Phase-B).
  * ASSOCIATE the client BEFORE wifi_bind: with a vif bound, IDM-dispatched
    frames bypass the local stack, and an early bind was suspected of eating
    EAPOL during the 4-way handshake. assoc -> bind is the safe order.
  * The initramfs does not up `lo` — bring it up in sanity (localhost users).
  * Console printk noise (TM-RX NOPARSE ARP dumps) floods UART captures:
    sanity sets printk loglevel 1.
  * `ftwifi` stays 0 unless --offload: HW WiFi-offload is opt-in per test.
  * hostapd is the static soft-float 2.11 staged in the initramfs /bin
    (findings/wifi_hostapd_crosscompile_2026-07-04.md); driver chain must
    load in the exact order below (fw load in mt7915e takes ~20 s).
  * DHCP fallback: if the client gets no lease, give it a static
    192.168.50.100/24 gw 192.168.50.1 (Android: long-press network ->
    modify -> static) — worked whenever udhcpd raced the retry window.

Device transport: the UART bridge REPL on :9999 via scratchpad/ctr.py.
"""
import argparse
import subprocess
import sys
import time
from pathlib import Path

sys.path.insert(0, str(Path(__file__).resolve().parent))
import ctr  # noqa: E402

AP_SSID = "H3600-AP-Test"
AP_PASS = "h3600aptest"
AP_IP = "192.168.50.1"
CLIENT_STATIC_FALLBACK = "192.168.50.100"
LAN4_IP = "10.44.66.223"

HOSTAPD_CONF = [
    "interface=wlan1", "driver=nl80211", f"ssid={AP_SSID}",
    "country_code=ES", "hw_mode=a", "channel=36",
    "ieee80211n=1", "ieee80211ac=1",
    "wmm_enabled=1", "auth_algs=1", "wpa=2", "wpa_key_mgmt=WPA-PSK",
    "rsn_pairwise=CCMP", f"wpa_passphrase={AP_PASS}",
]
UDHCPD_CONF = [
    "interface wlan1", "start 192.168.50.10", "end 192.168.50.100",
    "opt subnet 255.255.255.0", f"opt router {AP_IP}",
    "opt lease 86400", "lease_file /tmp/udhcpd.leases", "max_leases 32",
]
MODULE_CHAIN = [  # exact order matters; mt7915e loads firmware (~20 s)
    ("pcie-zx279128s.ko", 6), ("cfg80211.ko", 4), ("mac80211.ko", 4),
    ("mt76.ko", 4), ("mt76-connac-lib.ko", 4), ("mt7915e.ko", 25),
]


def run(cmds, wait=3.0, label=""):
    out = ctr.zc(cmds, wait=wait)
    print(f"--- {label} ---")
    print(out[-600:])
    return out


def sanity():
    run(["mkdir -p /proc /sys/kernel/debug /tmp 2>/dev/null",
         "mount -t proc none /proc 2>/dev/null",
         "mount -t sysfs none /sys 2>/dev/null",
         "mount -t debugfs none /sys/kernel/debug 2>/dev/null",
         "mount -t tmpfs none /tmp 2>/dev/null"], 3, "sanity: mount")
    run(["uname -a", "busybox ip link set lo up",
         "echo 1 > /proc/sys/kernel/printk"], 3, "sanity: uname + lo + printk")
    run(["ls /sys/kernel/debug/zx_eth/ | busybox grep -cE 'wifi_bind|ftwifi'"],
         3, "sanity: debugfs nodes (expect 2)")


def wan():
    run([f"busybox ip addr add {LAN4_IP}/24 dev lan4 2>/dev/null; "
         "busybox ip link set lan4 up",
         "busybox ip addr show lan4 | busybox grep inet"], 4, "wan: lan4")


def wifi():
    out = ctr.zc(["iw dev 2>/dev/null | busybox grep -c Interface"], wait=3)
    if out.strip().splitlines() and "2" in out[-8:]:
        print("--- wifi: modules already loaded (wlan present), skipping ---")
        return
    for ko, wait_s in MODULE_CHAIN:
        run([f"busybox insmod /lib/modules/{ko} 2>&1 | busybox head -1"],
            wait_s, f"wifi: insmod {ko}")
    time.sleep(5)
    run(["iw dev | busybox grep -E 'Interface|phy#'",
         "iw reg set ES", "iw reg get | busybox grep -m1 country"],
        4, "wifi: interfaces + regdom")


def conf():
    cmds = ["rm -f /tmp/hostapd.conf /tmp/udhcpd.conf"]
    cmds += [f"echo '{l}' >> /tmp/hostapd.conf" for l in HOSTAPD_CONF]
    cmds += [f"echo '{l}' >> /tmp/udhcpd.conf" for l in UDHCPD_CONF]
    cmds += ["touch /tmp/udhcpd.leases"]
    run(cmds, 3, "conf: hostapd.conf + udhcpd.conf")


def daemons():
    run([f"ip addr add {AP_IP}/24 dev wlan1 2>/dev/null",
         "ip link set wlan1 up"], 4, "daemons: wlan1 addr")
    run(["/bin/hostapd -B -t -f /tmp/hostapd.log /tmp/hostapd.conf"],
        12, "daemons: hostapd (wait AP-ENABLED)")
    # udhcpd: FOREGROUND + logged (see gotcha header)
    run(["busybox udhcpd -f /tmp/udhcpd.conf > /tmp/udhcpd.log 2>&1 &"],
        4, "daemons: udhcpd -f (logged)")


def assoc():
    """Associate the adb-attached Android. STOP if adb is dead — a human can
    connect the phone by hand instead (SSID/pass in the header)."""
    p = subprocess.run(["adb", "devices"], capture_output=True, text=True,
                       timeout=15)
    if "\tdevice" not in p.stdout:
        sys.exit("assoc: NO adb device — connect the phone by hand "
                 f"(SSID {AP_SSID} / {AP_PASS}), then run the bind phase.")
    subprocess.run(["adb", "shell", "svc power stayon true; "
                    "input keyevent KEYCODE_WAKEUP"], timeout=15)
    subprocess.run(["adb", "shell",
                    f'cmd wifi connect-network "{AP_SSID}" wpa2 "{AP_PASS}"'],
                   timeout=25)
    for _ in range(6):
        time.sleep(5)
        out = ctr.zc(["iw dev wlan1 station dump | busybox head -1"], wait=3)
        if "Station" in out:
            print("--- assoc: station associated ---")
            print(out[-200:])
            return
    print(f"assoc: WARNING no station after 30 s — check the phone; "
          f"static fallback {CLIENT_STATIC_FALLBACK}/24 gw {AP_IP}")


def bind():
    # AFTER assoc (EAPOL gotcha, header). idm1/ssid4 = the Phase-A/B/C vif slot.
    run(["echo 'wlan1 1 4' > /sys/kernel/debug/zx_eth/wifi_bind",
         "cat /sys/kernel/debug/zx_eth/wifi_bind"], 4, "bind: wlan1 -> idm1/ssid4")


def offload():
    run(["ip link set idm0 up 2>/dev/null",
         "ip link set idm1 up 2>/dev/null"], 2, "offload: idm0/idm1 up")
    run(["echo 1 > /proc/sys/net/ipv4/ip_forward",
         "nft flush ruleset",
         "nft add table inet ft",
         "nft 'add flowtable inet ft f { hook ingress priority 0; "
         "devices = { lan4 }; flags offload; }'",
         "nft 'add chain inet ft ftfwd { type filter hook forward "
         "priority filter; }'",
         "nft 'add rule inet ft ftfwd ct state established ip protocol tcp "
         "flow add @f'"], 5, "offload: nft flowtable {lan4}")
    run(["echo 1 > /sys/kernel/debug/zx_eth/ftwifi",
         "cat /sys/kernel/debug/zx_eth/ftwifi"], 3, "offload: ftwifi=1")


def verify():
    run(["busybox ps | busybox grep -aE 'hostapd|udhcpd' | busybox grep -av grep",
         "iw dev wlan1 info | busybox grep -aE 'ssid|channel'",
         "iw dev wlan1 station dump | busybox head -3",
         "cat /sys/kernel/debug/zx_eth/wifi_bind | busybox tail -2",
         "cat /sys/kernel/debug/zx_eth/ftwifi"], 5, "verify")


PHASES = ["sanity", "wan", "wifi", "conf", "daemons", "assoc", "bind",
          "offload", "verify"]


def main():
    ap = argparse.ArgumentParser(description=__doc__.splitlines()[0])
    ap.add_argument("phases", nargs="+",
                    help="phase names, or 'all' (= %s)" % " ".join(
                        p for p in PHASES if p not in ("assoc", "offload")))
    ap.add_argument("--adb", action="store_true",
                    help="also associate the adb Android (assoc phase)")
    ap.add_argument("--offload", action="store_true",
                    help="also install the nft flowtable rig + ftwifi=1")
    args = ap.parse_args()
    todo = args.phases
    if todo == ["all"]:
        todo = ["sanity", "wan", "wifi", "conf", "daemons"]
        if args.adb:
            todo.append("assoc")
        todo.append("bind")  # bind AFTER assoc — EAPOL gotcha
        if args.offload:
            todo.append("offload")
        todo.append("verify")
    for ph in todo:
        if ph not in PHASES:
            sys.exit(f"unknown phase {ph!r} (valid: {' '.join(PHASES)})")
        globals()[ph]()


if __name__ == "__main__":
    main()
