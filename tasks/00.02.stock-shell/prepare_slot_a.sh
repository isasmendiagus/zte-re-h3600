#!/usr/bin/env bash
# prepare_slot_a.sh — Build encrypted rootfs A + patched BootPara header, stage to TFTP.
#
# Produces TWO files in ../tftp/ ready for U-Boot to flash:
#   1. rootfs_a_patched_enc.jffs2   — 22 MiB AES-128-ECB encrypted JFFS2 with patched cspd
#   2. header_a_patched.bin          — 128 KiB BootPara header with CRC matching #1
#
# Usage:
#     ./prepare_slot_a.sh           # build only, print U-Boot commands at end
#     ./prepare_slot_a.sh --write   # build + auto-flash via UART (calls flash_slot_a.py)
#     ./prepare_slot_a.sh --dry     # build, then print flash sequence WITHOUT executing
#
# To re-build with a different patched cspd, drop the patched binary at
# `out/cspd-uart-alive` (same size as original `../rootfs/bin/cspd`) before running.
set -euo pipefail

# ---------- Arg parsing ----------
MODE="manual"   # "manual" | "write" | "dry"
for arg in "$@"; do
    case "$arg" in
        --write) MODE="write" ;;
        --dry)   MODE="dry"   ;;
        --help|-h)
            sed -n '2,15p' "$0" | sed 's/^# \?//'
            exit 0 ;;
        *)
            echo "Unknown flag: $arg (use --write, --dry, or --help)" >&2
            exit 2 ;;
    esac
done

# ---------- Config ----------
ROOT="$(cd "$(dirname "$0")" && pwd)"
ZXIC="$(cd "$ROOT/../.." && pwd)"   # tasks/00.02.stock-shell/ -> zxic/
STAGING="$ROOT/staging"
OUT="$ROOT/out"
TFTP="$ZXIC/tftp"
ROOTFS_SRC="$ZXIC/ext/rootfs"
NAND_DUMP="$ZXIC/ext/h3600_nand_full.bin"

# AES-128-ECB key for this device (per aes_key_discovered.md memory)
AES_KEY_ASCII="H36000e71071c440"

# Slot A NAND layout (per NAND_LAYOUT_AND_BOOT.md)
SLOT_A_KERNEL_OFFSET=0x700000
SLOT_A_ROOTFS_OFFSET=0xa60000
SLOT_A_ROOTFS_SIZE=0x1620000      # 22 MiB
SLOT_A_HEADER_OFFSET=0x2080000
SLOT_A_HEADER_SIZE=0x20000        # 128 KiB

# Patched cspd location (must be 2,809,662 bytes, same as ../rootfs/bin/cspd)
PATCHED_CSPD="$OUT/cspd-uart-alive"

# ---------- Phase 0: sanity checks ----------
echo "==== Phase 0: sanity checks ===="
command -v mkfs.jffs2 >/dev/null || { echo "ERROR: install mtd-utils (apt install mtd-utils)"; exit 1; }
command -v openssl    >/dev/null || { echo "ERROR: openssl not found"; exit 1; }
command -v python3    >/dev/null || { echo "ERROR: python3 not found"; exit 1; }

[ -d "$ROOTFS_SRC" ]      || { echo "ERROR: missing $ROOTFS_SRC (extracted stock rootfs)"; exit 1; }
[ -f "$NAND_DUMP" ]       || { echo "ERROR: missing $NAND_DUMP (full NAND backup)"; exit 1; }
[ -f "$PATCHED_CSPD" ]    || { echo "ERROR: missing $PATCHED_CSPD"; exit 1; }
[ -d "$TFTP" ]            || { echo "ERROR: missing $TFTP dir"; exit 1; }

orig_cspd_size=$(stat -c%s "$ROOTFS_SRC/bin/cspd")
patched_size=$(stat -c%s "$PATCHED_CSPD")
[ "$orig_cspd_size" -eq "$patched_size" ] || {
    echo "ERROR: patched cspd size ($patched_size) != original ($orig_cspd_size)"
    exit 1
}
echo "  ✓ tools, files, sizes all OK"
mkdir -p "$OUT"

# ---------- Phase 1: refresh staging dir from stock rootfs + drop patched cspd ----------
echo "==== Phase 1: refresh staging/ ===="
rm -rf "$STAGING"
cp -a "$ROOTFS_SRC" "$STAGING"
cp "$PATCHED_CSPD" "$STAGING/bin/cspd"
chmod 755 "$STAGING/bin/cspd"
echo "  ✓ staging rebuilt; patched cspd in place"

# Inject kmsg2uart daemon: drains /proc/kmsg → writes to PL011 DR (ZTE-shifted).
# Without this, kernel printk never reaches UART on stock kernel — see
# docs/SLOT_A_CSPD_PATCH_PLAYBOOK.md §5.
KMSG2UART_BIN="$OUT/kmsg2uart"
if [ -f "$KMSG2UART_BIN" ]; then
    cp "$KMSG2UART_BIN" "$STAGING/sbin/kmsg2uart"
    chmod 755 "$STAGING/sbin/kmsg2uart"
    # Add startup hook to /etc/rc, AFTER /proc is mounted but BEFORE init.norm
    # (the daemon needs /proc/kmsg, /dev/mem; both exist by then).
    RC="$STAGING/etc/rc"
    if ! grep -q "kmsg2uart" "$RC"; then
        # Insert right after the `mount -t proc proc /proc` line
        # so /proc/kmsg is available.
        sed -i '/^mount -t proc proc \/proc$/a\
\
# Kernel printk → UART (DR=0x94404004 ZTE-shifted PL011)\
/sbin/kmsg2uart > /dev/null 2>&1 &' "$RC"
        echo "  ✓ kmsg2uart binary + /etc/rc hook added"
    else
        echo "  ✓ kmsg2uart binary added (rc hook already present)"
    fi
else
    echo "  ⚠ $KMSG2UART_BIN not built — kernel printk will NOT reach UART"
    echo "    Build it: arm-linux-gnueabi-gcc -static -O2 -o $KMSG2UART_BIN $ROOT/kmsg2uart.c"
fi

# ---------- Phase 2: trim non-essential files to fit 22 MiB after JFFS2 compression ----------
# DO NOT REMOVE (broke boot when we did):
#   /home/httpd          — cspd hangs waiting for web admin if missing
#   /home/httpd/public   — Lua handlers needed by cspd
#   /lib/firmware/*      — kernel modules need their fw blobs
#   /kmodule/*           — all kernel modules essential
#
# SAFE to remove:
#   /etc/dsl/              — DSL configs; H3600 is GPON, doesn't have DSL hardware
#   /bin/smbd, smbpasswd   — SMB file sharing daemon
#   /bin/voip              — VoIP daemon (phone port)
#   /bin/mqtt              — MQTT phone-home (we'd want disabled anyway)
#   /etc/usb_modeswitch.d/ — USB modem switching tables
#   /lib/modules/<ver>/modules.*.bin — regenerable cache files
#   /etc/autokernelconf    — kernel config doc, we have on host
echo "==== Phase 2: SAFE trim (iter 4 — keep /etc/dsl, add voip+mqtt to trim) ===="
# CRITICAL: /etc/dsl is the SWITCH CHIP FIRMWARE (boot.bin + fw.bin), not DSL configs.
#   /etc/rc loads it: `nfbi bootdownload 0 /etc/dsl/boot.bin &`
#   Without it: switch.ko hangs at init → whole boot hangs.
#
# init.norm shows voip is NOT auto-started (line is commented: `#voip&`)
# mqtt phone-home daemon is non-critical
rm -rf "$STAGING/home/httpd/public/img"            2>/dev/null || true   # ~1.5 MiB — web UI images
rm -rf "$STAGING/etc/usb_modeswitch.d"             2>/dev/null || true   # ~1.7 MiB — USB modem switch tables
rm -f  "$STAGING/bin/voip"                         2>/dev/null || true   # ~1.3 MiB — init.norm: '#voip&' commented
rm -f  "$STAGING/bin/mqtt"                         2>/dev/null || true   # ~272 KiB — phone-home
rm -f  "$STAGING/lib/modules/4.1.25/modules."*.bin 2>/dev/null || true   # ~200 KiB — regenerable
rm -f  "$STAGING/etc/autokernelconf"               2>/dev/null || true   # ~88 KiB — we have on host
# Iter 8 additions to make room for kmsg2uart (~543 KB):
rm -f  "$STAGING/bin/smbd"                         2>/dev/null || true   # ~2.3 MiB — Samba server (no file sharing needed)
rm -f  "$STAGING/bin/smbpasswd"                    2>/dev/null || true   # ~1.4 MiB — Samba pwd tool
rm -f  "$STAGING/bin/nmbd"                         2>/dev/null || true   # ~190 KiB — Samba NetBIOS
staging_kb=$(du -sk "$STAGING" 2>/dev/null | cut -f1)
echo "  ✓ staging size: ${staging_kb} KiB raw"

# ---------- Phase 3: build JFFS2 image (22 MiB padded) ----------
echo "==== Phase 3: mkfs.jffs2 → 22 MiB image ===="
# --squash forces all files to root:root with stripped group/other writes.
# --devtable adds the /dev/* device nodes that our extracted rootfs/ is missing
# (the JFFS2 extractor that produced rootfs/ couldn't create char/block special
#  files without CAP_MKNOD, so /dev/console etc. don't exist in staging).
# Without devtable: init can't open /dev/console → silent boot hang.
DEVTABLE="$ROOT/devtable.txt"
[ -f "$DEVTABLE" ] || { echo "ERROR: missing $DEVTABLE (run generate-devtable-from-running-device first)"; exit 1; }
mkfs.jffs2 \
    -r "$STAGING" \
    -o "$OUT/rootfs_a_patched.jffs2" \
    --pagesize=2048 \
    --eraseblock=131072 \
    --no-cleanmarkers \
    --pad="$SLOT_A_ROOTFS_SIZE" \
    --little-endian \
    -m size \
    --squash \
    --devtable="$DEVTABLE"
chmod 644 "$OUT/rootfs_a_patched.jffs2"

jffs2_size=$(stat -c%s "$OUT/rootfs_a_patched.jffs2")
expected_size=$((SLOT_A_ROOTFS_SIZE))
[ "$jffs2_size" -eq "$expected_size" ] || {
    echo "ERROR: jffs2 size $jffs2_size != expected $expected_size"
    echo "       Likely staging content > 22 MiB compressed — trim more files in Phase 2."
    exit 1
}
echo "  ✓ jffs2 image: $jffs2_size bytes (= 0x$(printf '%x' $jffs2_size))"

# Verify JFFS2 magic at start (plain, pre-encrypt)
magic=$(xxd -l 2 "$OUT/rootfs_a_patched.jffs2" | head -1 | awk '{print $2}')
[ "$magic" = "8519" ] || { echo "ERROR: jffs2 magic invalid ($magic) — should be 8519"; exit 1; }
echo "  ✓ JFFS2 magic 0x1985 (bytes 85 19) confirmed at offset 0"

# ---------- Phase 4: AES-128-ECB encrypt ----------
echo "==== Phase 4: AES-128-ECB encrypt with key '$AES_KEY_ASCII' ===="
KEY_HEX=$(echo -n "$AES_KEY_ASCII" | xxd -p)
echo "  key (hex): $KEY_HEX"

openssl enc -e -aes-128-ecb -K "$KEY_HEX" -nopad \
    -in  "$OUT/rootfs_a_patched.jffs2" \
    -out "$OUT/rootfs_a_patched_enc.jffs2"

enc_size=$(stat -c%s "$OUT/rootfs_a_patched_enc.jffs2")
[ "$enc_size" -eq "$expected_size" ] || { echo "ERROR: encrypted size mismatch"; exit 1; }

# Round-trip integrity check
openssl enc -d -aes-128-ecb -K "$KEY_HEX" -nopad \
    -in  "$OUT/rootfs_a_patched_enc.jffs2" \
    -out "/tmp/roundtrip_check_$$.bin"
if ! cmp -s "$OUT/rootfs_a_patched.jffs2" "/tmp/roundtrip_check_$$.bin"; then
    echo "ERROR: encrypt+decrypt round-trip MISMATCH"
    exit 1
fi
rm -f "/tmp/roundtrip_check_$$.bin"
echo "  ✓ encrypted ($enc_size bytes); round-trip decrypt matches original"

# Encrypted bytes preview
echo "  encrypted first 16 bytes:"
xxd -l 16 "$OUT/rootfs_a_patched_enc.jffs2" | head -1 | sed 's/^/    /'

# ---------- Phase 5: compute rootfs CRC32 + build patched BootPara header ----------
echo "==== Phase 5: compute CRC, build patched header ===="
python3 << PYEOF
import zlib, struct, sys

ENC = open("$OUT/rootfs_a_patched_enc.jffs2", "rb").read()
new_rootfs_crc = zlib.crc32(ENC) & 0xffffffff
print(f"  computed rootfs CRC32: 0x{new_rootfs_crc:08x}")

# Read original BootPara header from NAND dump (slot A header at 0x2080000, 128 KiB)
nand = open("$NAND_DUMP", "rb").read()
SLOT_A_HEADER_OFFSET = $SLOT_A_HEADER_OFFSET
SLOT_A_HEADER_SIZE   = $SLOT_A_HEADER_SIZE
header = bytearray(nand[SLOT_A_HEADER_OFFSET : SLOT_A_HEADER_OFFSET + SLOT_A_HEADER_SIZE])

orig_rootfs_crc_in_header = int.from_bytes(header[0x48:0x4c], "little")
orig_header_crc           = int.from_bytes(header[0xa4:0xa8], "little")
print(f"  original header[0x48] (rootfs CRC): 0x{orig_rootfs_crc_in_header:08x}")
print(f"  original header[0xa4] (header CRC): 0x{orig_header_crc:08x}")

# Update rootfs CRC at offset 0x48 (4 bytes LE)
header[0x48:0x4c] = new_rootfs_crc.to_bytes(4, "little")

# Recompute header CRC over bytes [0..0xa4)
new_header_crc = zlib.crc32(bytes(header[0:0xa4])) & 0xffffffff
header[0xa4:0xa8] = new_header_crc.to_bytes(4, "little")
print(f"  new header[0x48] (rootfs CRC):     0x{new_rootfs_crc:08x}")
print(f"  new header[0xa4] (header CRC):      0x{new_header_crc:08x}")

open("$OUT/header_a_patched.bin", "wb").write(bytes(header))
print(f"  ✓ wrote header_a_patched.bin ({len(header)} bytes)")
PYEOF

# ---------- Phase 6: stage to TFTP ----------
echo "==== Phase 6: stage to $TFTP ===="
cp -f "$OUT/rootfs_a_patched_enc.jffs2" "$TFTP/"
cp -f "$OUT/header_a_patched.bin"       "$TFTP/"
echo "  ✓ TFTP files ready:"
ls -la "$TFTP/rootfs_a_patched_enc.jffs2" "$TFTP/header_a_patched.bin"

# ---------- Done. Behavior based on MODE ----------
case "$MODE" in
    write)
        echo ""
        echo "=== BUILD complete. --write mode → invoking flash_slot_a.py ==="
        exec python3 "$ROOT/flash_slot_a.py"
        ;;

    dry)
        echo ""
        echo "=== BUILD complete. --dry mode → showing flash sequence (no execution) ==="
        exec python3 "$ROOT/flash_slot_a.py" --dry-run
        ;;

    manual|*)
        cat <<EOM

=========================================================================
BUILD COMPLETE. Now flash via U-Boot.

Quick path (automated): re-run with --write
    ./prepare_slot_a.sh --write

Manual path:

1. In one terminal, monitor UART:
       python3 ../../lib/uart.py log

2. In another terminal, hard reset:
       python3 ../../lib/uart.py reset

3. When UART shows "Press 1 means entering boot mode", press 1.
4. When prompted for password, type:    Boot4128s!
   (You should land at "=>" prompt.)

5. Paste these commands at the => prompt:

       setenv serverip 192.168.1.50
       setenv ipaddr 192.168.1.1
       setenv tftpblocksize 1468

       tftp 0x42000000 rootfs_a_patched_enc.jffs2
       md.l 0x42000000 1
       nand erase 0xa60000 0x1620000
       nand write 0x42000000 0xa60000 0x1620000

       tftp 0x42000000 header_a_patched.bin
       md.l 0x42000048 1
       md.l 0x420000a4 1
       nand erase 0x2080000 0x20000
       nand write 0x42000000 0x2080000 0x20000

       reset

6. After reset, slot A should boot.

   Look for:
     - "verify fs success!!" (slot A's CRC now matches)
     - kernel boot + module load via init.norm
     - cspd start → calls "logctrl -g 3" → UART STAYS ALIVE

7. IMPORTANT — DO NOT do "mount -o remount,rw /" after boot:
   any rw mount triggers JFFS2 metadata writes → encrypted NAND drifts
   → next boot's CRC fails → fallback to slot B again.

If anything fails: slot B is intact, cspstart auto-falls back to it.
Full NAND backup at ../../h3600_nand_full.bin for total recovery.
=========================================================================
EOM
        ;;
esac
