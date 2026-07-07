#!/bin/bash
# stage_wifi_initramfs.sh — stage the MT7915 WiFi payload into the live
# initramfs source dir (CONFIG_INITRAMFS_SOURCE=/tmp/initramfs_extract).
#
# Idempotent; run before rebuilding the zImage for a WiFi-enabled boot.
# Sources (all canonical, tracked or host-system):
#   - wpa_supplicant + iw : tasks/00.07.wifi/bin/  (soft-float static v5T,
#     built 2026-05-03; recovered 2026-07-04 from the embedded initramfs of
#     tftp/zImage_dtb.uimg.bak_v6 after the originals were lost — see
#     findings/wifi_sta_reverify_2026-07-04.md)
#   - mt7915 firmware      : ext/firmware/mediatek/  (linux-firmware blobs)
#   - MT7915 EEPROM        : ext/rootfs/etc/wireless/mt7915/MT7915_EEPROM.bin
#     (per-unit calibration; staged as BOTH mt7915_eeprom.bin and
#     mt7915_eeprom_dbdc.bin — the driver asks for the dbdc name on this SKU)
#   - regulatory.db + .p7s : /lib/firmware (Ubuntu wireless-regdb, the pair
#     must stay consistent; md5-verified identical to the May-2026 proven pair)
#   - module chain         : build/ .kos (pcie-zx279128s, cfg80211, mac80211,
#     mt76, mt76-connac-lib, mt7915e)
#
# ⚠ NEVER stage the rendered wpa_supplicant conf (contains the PSK) here:
#   the initramfs gets baked into tftp/zImage_dtb.{bin,uimg} which are
#   GIT-TRACKED. The PSK config is fetched over the LAN at runtime instead
#   (busybox wget from a host http.server serving tasks/00.07.wifi/out/).
set -euo pipefail
REPO="$(cd "$(dirname "$0")/../../.." && pwd)"
DEST="${1:-/tmp/initramfs_extract}"

[ -d "$DEST" ] || { echo "ERROR: $DEST missing (initramfs source dir)"; exit 1; }

echo "== staging WiFi payload into $DEST"

# userland
install -d "$DEST/usr/sbin" "$DEST/usr/bin"
install -m755 "$REPO/tasks/00.07.wifi/bin/wpa_supplicant" "$DEST/usr/sbin/wpa_supplicant"
install -m755 "$REPO/tasks/00.07.wifi/bin/iw"             "$DEST/usr/bin/iw"

# firmware
install -d "$DEST/lib/firmware/mediatek"
for f in mt7915_rom_patch.bin mt7915_wm.bin mt7915_wa.bin; do
    install -m644 "$REPO/ext/firmware/mediatek/$f" "$DEST/lib/firmware/mediatek/$f"
done
install -m644 "$REPO/ext/rootfs/etc/wireless/mt7915/MT7915_EEPROM.bin" \
              "$DEST/lib/firmware/mediatek/mt7915_eeprom.bin"
install -m644 "$REPO/ext/rootfs/etc/wireless/mt7915/MT7915_EEPROM.bin" \
              "$DEST/lib/firmware/mediatek/mt7915_eeprom_dbdc.bin"
install -m644 /lib/firmware/regulatory.db     "$DEST/lib/firmware/regulatory.db"
install -m644 /lib/firmware/regulatory.db.p7s "$DEST/lib/firmware/regulatory.db.p7s"

# module chain (fresh build artifacts)
install -d "$DEST/lib/modules"
for ko in drivers/pci/controller/dwc/pcie-zx279128s.ko \
          net/wireless/cfg80211.ko \
          net/mac80211/mac80211.ko \
          drivers/net/wireless/mediatek/mt76/mt76.ko \
          drivers/net/wireless/mediatek/mt76/mt76-connac-lib.ko \
          drivers/net/wireless/mediatek/mt76/mt7915/mt7915e.ko; do
    install -m644 "$REPO/build/$ko" "$DEST/lib/modules/$(basename "$ko")"
done

# sanity: no rendered secret config in the staged tree (the wpa_supplicant
# BINARY legitimately contains the "psk=" parser string, so scan text
# configs only)
if grep -rl --include="*.conf" "psk=" "$DEST" >/dev/null 2>&1; then
    echo "FATAL: a psk= literal is present in a .conf under $DEST — refusing (would bake the secret into tracked tftp images)"
    exit 1
fi

echo "== staged:"
ls -la "$DEST/usr/sbin/wpa_supplicant" "$DEST/usr/bin/iw"
ls -la "$DEST/lib/firmware/mediatek/" "$DEST/lib/firmware/regulatory.db" "$DEST/lib/firmware/regulatory.db.p7s"
ls -la "$DEST/lib/modules/"
echo "OK"
