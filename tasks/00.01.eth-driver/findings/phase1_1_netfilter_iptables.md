# Phase 1.1 — netfilter kernel + iptables userland (the NAT-router toolkit)

**Status: DONE + verified on HW (2026-06-04, Iter loop-5).** branch hw-ack-forward.

Goal: give mainline 6.6 the netfilter/conntrack/NAT stack + a working iptables so the CPU can
run the control plane (NAT, firewall) — stock's HYBRID model, SW side. Independent of the physical
WAN cable, so testable now.

## (a) Kernel config — netfilter built in
Base defconfig had `CONFIG_NETFILTER is not set` + `CONFIG_IP_ADVANCED_ROUTER is not set`. Added a
config fragment `tasks/00.01.eth-driver/configs/netfilter.fragment` (NETFILTER, NETFILTER_ADVANCED,
NF_CONNTRACK(+PROCFS), NF_NAT(+MASQUERADE), the XT match/target set — STATE, CONNTRACK, MULTIPORT,
MARK, LIMIT, MAC, IPRANGE, PHYSDEV, MASQUERADE, REDIRECT, NETMAP, LOG/NFLOG — IP_NF_IPTABLES,
IP_NF_FILTER, IP_NF_TARGET_REJECT, IP_NF_NAT, IP_NF_TARGET_MASQUERADE/REDIRECT/NETMAP, IP_NF_MANGLE,
IP_ADVANCED_ROUTER, IP_MULTIPLE_TABLES). 41 netfilter symbols now `=y`.

**Reproducibility:** `build_slotA.py` step 0a auto-merges the fragment (`merge_config.sh -m` +
`make olddefconfig`) before every build — the build dir is untracked, so without this a fresh
build silently drops netfilter. The fragment file is the durable, committed artifact.

## (b) iptables userland — reuse stock's own ARM binary
The stock firmware ships a working ARM iptables (`ext/rootfs/bin/iptables`, uClibc/EABI5). It has
ALL match/target extensions compiled IN (binary symbols `libipt_MASQUERADE_init`, `libipt_SNAT_init`,
`libipt_DNAT_init`, `libxt_state_init`, `libxt_conntrack`-family, `libxt_standard_init`, …) — no
external `libxt_*.so` modules needed (none exist in the rootfs). libxtables is statically linked in
(readelf NEEDED = only libcommfun.so, libm.so.0, libc.so.0). Staged into the initramfs
(`/tmp/initramfs_extract`):
- `lib/`: ld-uClibc(-0.9.33.2).so.0, libuClibc-0.9.33.2.so→libc.so.0, libm-0.9.33.2.so→libm.so.0,
  libdl/libpthread (for later pppd/dnsmasq), libcommfun.so (ZTE lib, needs only libc).
- `sbin/`: iptables, ip6tables.
(Re-stage with `cp -a ext/rootfs/lib/{ld-uClibc*,libuClibc*,libc.so.0,libm*,libdl*,libpthread*,libcommfun.so} /tmp/initramfs_extract/lib/`
and `cp -a ext/rootfs/bin/{iptables,ip6tables} /tmp/initramfs_extract/sbin/` if /tmp is wiped.)

## (c) Live verification on device
- `iptables -L -n` → RC=0, INPUT/FORWARD/OUTPUT chains (uClibc binary runs on the 6.6 kernel ✓).
- `iptables -t nat -L -n` → PREROUTING/INPUT/OUTPUT/POSTROUTING ✓.
- `iptables -t nat -A POSTROUTING -o lan4 -j MASQUERADE` → RC=0; `-S` shows the rule installed ✓.
- `iptables -A FORWARD -m state --state ESTABLISHED,RELATED -j ACCEPT` → RC=0 (state ext works) ✓.
- `echo 1 > /proc/sys/net/ipv4/ip_forward` → reads back 1 ✓.
- `/proc/net/nf_conntrack` exists ✓.

⟹ The full NAT-router + firewall toolkit is live. Ready for 1.2 (udhcpc/pppd on lan4) and 1.3
(`ip_forward` + MASQUERADE LAN→WAN = NAT router; a live end-to-end test needs a host NIC on the WAN
jack).

## Known issue (deferred): NAND flash size
With netfilter built in + iptables in the initramfs, the slotA body is 0xc3c9df > the NAND write
size 0xc00000 — `build_slotA.py` errors at the flash-image packing step. **TFTP/RAM boot is
unaffected** (loads zImage_dtb.uimg, which builds fine), so dev/test continues. To FLASH later:
trim the kernel (make rarely-used netfilter pieces `=m` and insmod from initramfs, or drop unused
drivers) or bump the partition layout. Not blocking for the mainline bring-up.
