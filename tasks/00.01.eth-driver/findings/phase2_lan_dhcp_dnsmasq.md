# Phase 2 — LAN DHCP service (+ the stock-daemon liboss_pub blocker)

**Status: LAN DHCP DONE + verified end-to-end on HW (2026-06-04, Iter loop-6).** branch hw-ack-forward.

## Result
The device serves DHCP to a real LAN client over the DSA `lan1` port. Device-side: busybox udhcpd
on `lan1` (172.31.9.1/24). Host (`enxc8a362e95900`, cabled to lan1) sent a DHCPDISCOVER; the device
replied with a full DHCPOFFER:
```
IP Offered: 172.31.9.50   Server Identifier: 172.31.9.1   Lease: 12h
Subnet Mask: 255.255.255.0   Router: 172.31.9.1   DNS: 8.8.8.8
```
(verified non-disruptively with `sudo nmap --script broadcast-dhcp-discover -e enxc8a362e95900` — no
host-IP changes, TFTP path untouched). This proves the LAN datapath host↔lan1↔CPU↔udhcpd works
bidirectionally and the DHCP server is functional.

## KEY BLOCKER discovered: stock dnsmasq/pppd are UNUSABLE on mainline
Staged stock `ext/rootfs/bin/{dnsmasq,pppd}` (uClibc) into the initramfs — both **hang immediately at
exec** (no output, never daemonize, wedge the job-control-less C-init REPL → only a reboot recovers).
Root cause by elimination: dnsmasq/pppd link ZTE's **`liboss_pub.so`** (NEEDED); `iptables` (which
works fine) does NOT. liboss_pub's library constructor evidently blocks waiting on a ZTE platform
service (OSS/IPC daemon) that doesn't exist on mainline. So any stock binary linking liboss_pub
hangs. ⟹ For DHCP use **busybox udhcpd** (static, zero ZTE-lib deps). For local DNS and PPPoE later:
build clean dnsmasq/pppd from source (or stub liboss_pub), OR use busybox alternatives (dnsd) — do
NOT rely on the stock binaries. pppd/dnsmasq remain staged for a future clean rebuild.

## Environment gotchas (cost several reboots — now documented)
- **busybox applets need `busybox <applet>`** — no symlinks are installed (`udhcpd` alone = "not
  found"; `busybox udhcpd` works). Same for udhcpc/udhcpd/brctl etc.
- **No `/etc/passwd`/`/etc/group`** on the device — daemons doing getpwnam (dnsmasq `--user`) fail.
  Created minimal ones (root + nobody); now staged in the initramfs (`configs/passwd`,`configs/group`).
- **The C-init REPL has NO job control** — a foreground daemon (or a hanging binary) wedges the
  console; Ctrl-C is echoed but not delivered. Recover only by reboot. Launch daemons backgrounded
  (`busybox udhcpd -f -v /etc/udhcpd.conf >/tmp/ud.log 2>&1 &`) and read their logfile.
- **busybox has no `timeout` applet** — can't guard a possibly-hanging command that way.
- **Console floods**: quiet with `echo 1 4 1 7 > /proc/sys/kernel/printk` right after boot (the eth
  driver's BPDUMP is dev_info, capped at the first 20 RX pkts, so not a continuous flood once quieted).

## Reproducibility
- `tasks/00.01.eth-driver/configs/{passwd,group,udhcpd.conf,udhcpc.default.script}` — the durable artifacts.
- `tasks/00.01.eth-driver/scripts/stage_userland.sh` — idempotently re-stages the whole router
  userland (uClibc libs + stock binaries + configs) into /tmp/initramfs_extract after a /tmp wipe.
- Bring-up on device (after boot): `echo 1 4 1 7 >/proc/sys/kernel/printk; ip addr add 172.31.9.1/24
  dev lan1; ip link set lan1 up; busybox udhcpd -f -v /etc/udhcpd.conf >/tmp/ud.log 2>&1 &`.

## Next
- DNS for LAN (dnsmasq clean-build or busybox dnsd) — optional; clients can use upstream DNS via
  the DHCP dns option, so not required for a working NAT router.
- 1.2 WAN udhcpc (client on lan4 — cable-blocked for live test) / PPPoE (pppd needs clean build).
- 1.3 NAT: `ip_forward=1` + `iptables -t nat -A POSTROUTING -o lan4 -j MASQUERADE` + FORWARD rules
  (config + rule-verify now; live internet test when the WAN jack is cabled).
