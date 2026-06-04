#!/bin/bash
# Stage the router userland into the initramfs source (/tmp/initramfs_extract).
# Idempotent. Run this after a /tmp wipe so build_slotA.py embeds a complete
# rootfs. The eth .ko is staged by build_slotA.py itself.
#   Phase 1.1: iptables/ip6tables (+ uClibc runtime) — WORKS.
#   Phase 1.2: pppd, dnsmasq staged but UNUSABLE (link ZTE liboss_pub.so whose
#              constructor blocks with no ZTE platform daemon → process hangs;
#              iptables works only because it does NOT link liboss_pub). For DHCP
#              use busybox udhcpd (no ZTE-lib deps). pppd/dnsmasq kept staged for
#              a future clean rebuild / liboss_pub stub.
#   Phase 2:   busybox udhcpd LAN DHCP — config /etc/udhcpd.conf.
set -e
REPO="$(cd "$(dirname "$0")/../../.." && pwd)"
SRC="$REPO/ext/rootfs"
CFG="$REPO/tasks/00.01.eth-driver/configs"
DST=/tmp/initramfs_extract
mkdir -p "$DST/lib" "$DST/sbin" "$DST/etc" "$DST/usr/share/udhcpc"

# uClibc runtime + ZTE libs needed by the stock binaries we reuse
for f in ld-uClibc-0.9.33.2.so ld-uClibc.so.0 libuClibc-0.9.33.2.so libc.so.0 \
         libm-0.9.33.2.so libm.so.0 libdl-0.9.33.2.so libdl.so.0 \
         libpthread-0.9.33.2.so libpthread.so.0 libcommfun.so liboss_pub.so \
         libssl.so.1.0.0 libcrypto.so.1.0.0 libhardcode.so libsha256.so \
         libresolv.so.0 libresolv-0.9.33.2.so libssl.so libcrypto.so; do
  [ -e "$DST/lib/$f" ] && continue
  s="$(find "$SRC/lib" -maxdepth 1 -name "$f" 2>/dev/null | head -1)"
  [ -n "$s" ] && cp -a "$s" "$DST/lib/$f" && echo "  lib/$f"
done

# stock binaries (iptables WORKS; pppd/dnsmasq staged-but-hang, see header)
for b in iptables ip6tables pppd dnsmasq; do
  cp -a "$SRC/bin/$b" "$DST/sbin/$b" && echo "  sbin/$b"
done

# tc: a MODERN static iproute2 tc we cross-built (the stock tc is iproute2-2012,
# no `flower`; busybox tc has no flower either). Needed for Phase 6 HW-offload
# (tc-flower) + Phase 5 QoS. Build recipe: tasks/00.01.eth-driver/configs/bin/README-tc.md.
[ -f "$CFG/bin/tc" ] && cp -a "$CFG/bin/tc" "$DST/sbin/tc" && echo "  sbin/tc (static iproute2-6.1.0, flower built-in)"

# config + scripts (the durable artifacts)
cp -a "$CFG/passwd" "$DST/etc/passwd"
cp -a "$CFG/group"  "$DST/etc/group"
cp -a "$CFG/udhcpd.conf" "$DST/etc/udhcpd.conf"
cp -a "$CFG/rc.router" "$DST/etc/rc.router"; chmod +x "$DST/etc/rc.router"
cp -a "$CFG/udhcpc.default.script" "$DST/usr/share/udhcpc/default.script"
chmod +x "$DST/usr/share/udhcpc/default.script"

# rebuild /init (C-init PID 1) — it runs /etc/rc.router at boot
if command -v arm-linux-gnueabi-gcc >/dev/null; then
  arm-linux-gnueabi-gcc -static -O2 -o "$DST/init" \
    "$REPO/tasks/00.01.eth-driver/initramfs/init.c" 2>/dev/null \
    && echo "  init (recompiled)"
fi
echo "✓ userland staged into $DST"
