#!/bin/bash
# build_hostapd_softfloat.sh — cross-compile a STATIC SOFT-FLOAT hostapd (+cli)
# for the ZTE H3600 (ZX279128S Cortex-A9, **no VFP** — hard-float binaries SIGILL).
#
# Mirrors EXACTLY the proven busybox.softfloat recipe
# (tasks/00.01.eth-driver/userland/README.md):
#   - Toolchain: Bootlin armv5-eabi--glibc--stable-2018.11-1 (gcc 7.3.0,
#     prefix arm-linux-, soft-float, zero VFP instructions; armv5 code runs
#     fine on the A9). Resulting ABI: Tag_CPU_arch v5TEJ, NO Tag_FP_arch.
#   - Static link (no .so gaps on the minimal initramfs).
#
# Deps built here: libnl-3.9.0 (libnl-3 + libnl-genl-3, static) -> hostapd 2.11.
# hostapd config: nl80211 driver, WPA2-PSK/CCMP (default), 11n+VHT(ac)+HE(ax),
# ctrl_interface (default-on), TLS=internal (no OpenSSL cross-dep).
#
# Usage: ./build_hostapd_softfloat.sh
# Output: tasks/00.07.wifi/userland/hostapd.softfloat + hostapd_cli.softfloat
# Build tree: tasks/00.07.wifi/build/ (git-ignored). Re-run is idempotent-ish:
# nukes and rebuilds the source trees, reuses downloaded tarballs.

set -euo pipefail

TC=/home/ubuntu/toolchains/armv5-eabi--glibc--stable-2018.11-1
# APPEND (not prepend): $TC/bin also ships bison/m4/pkg-config with a hardcoded
# /opt/... prefix that breaks if the toolchain lives elsewhere; host tools must
# win for those, and the arm-linux-* names are unique so appending is safe.
export PATH="$PATH:$TC/bin"
CROSS=arm-linux-               # same prefix the busybox build used
HOST_TRIPLET=arm-buildroot-linux-gnueabi

TASK_DIR="$(cd "$(dirname "$0")/.." && pwd)"
BUILD="$TASK_DIR/build"
STAGING="$BUILD/staging"        # libnl headers + static libs land here
OUT="$TASK_DIR/userland"
mkdir -p "$BUILD" "$STAGING" "$OUT"

# libnl 3.5.0 (2019, era-matched with the gcc-7.3/glibc-2.28 toolchain).
# 3.9.0 does NOT build against these old glibc headers (struct tm/gmtime_r
# breakage in lib/xfrm/, which hostapd doesn't need anyway).
LIBNL_V=3.5.0
HOSTAPD_V=2.11
LIBNL_URL="https://github.com/thom311/libnl/releases/download/libnl3_5_0/libnl-$LIBNL_V.tar.gz"
HOSTAPD_URL="https://w1.fi/releases/hostapd-$HOSTAPD_V.tar.gz"
HOSTAPD_SHA256=2b3facb632fd4f65e32f4bf82a76b4b72c501f995a4f62e330219fe7aed1747a
LIBNL_SHA256=352133ec9545da76f77e70ccb48c9d7e5324d67f6474744647a7ed382b5e05fa

cd "$BUILD"
[ -f "libnl-$LIBNL_V.tar.gz" ]   || curl -sL -o "libnl-$LIBNL_V.tar.gz" "$LIBNL_URL"
[ -f "hostapd-$HOSTAPD_V.tar.gz" ] || curl -sL -o "hostapd-$HOSTAPD_V.tar.gz" "$HOSTAPD_URL"
echo "$LIBNL_SHA256  libnl-$LIBNL_V.tar.gz"     | sha256sum -c -
echo "$HOSTAPD_SHA256  hostapd-$HOSTAPD_V.tar.gz" | sha256sum -c -

# ---------------- libnl (static) ----------------
rm -rf "libnl-$LIBNL_V"
tar xzf "libnl-$LIBNL_V.tar.gz"
cd "libnl-$LIBNL_V"
./configure --host="$HOST_TRIPLET" \
            CC="${CROSS}gcc" \
            CFLAGS="-Os" \
            --prefix="$STAGING" \
            --enable-static --disable-shared \
            --disable-cli --disable-pthreads \
            --disable-debug
make -j"$(nproc)"
make install
cd "$BUILD"

# ---------------- hostapd ----------------
rm -rf "hostapd-$HOSTAPD_V"
tar xzf "hostapd-$HOSTAPD_V.tar.gz"
cd "hostapd-$HOSTAPD_V/hostapd"

cat > .config <<'EOF'
# Minimal AP build for the H3600 (mac80211/nl80211, WPA2-PSK/CCMP, 5GHz ac/ax)
CONFIG_DRIVER_NL80211=y
CONFIG_LIBNL32=y
# WPA2-PSK + CCMP are core (always built). ctrl_interface is default-on
# (CONFIG_NO_CTRL_IFACE not set) -> hostapd_cli works.
CONFIG_IEEE80211N=y
CONFIG_IEEE80211AC=y
CONFIG_IEEE80211AX=y
# No OpenSSL on the rootfs: internal crypto/TLS (sufficient for WPA2-PSK).
CONFIG_TLS=internal
CONFIG_INTERNAL_LIBTOMMATH=y
# Trim what the minimal rootfs can't use anyway
CONFIG_NO_RADIUS=y
CONFIG_NO_ACCOUNTING=y
CONFIG_NO_VLAN=y
EOF

# NOTE: these MUST go through the environment, not the make command line —
# command-line CFLAGS would override the Makefile's own `CFLAGS += -I../src`
# appends and break the build (utils/includes.h not found).
export CC="${CROSS}gcc"
export CFLAGS="-MMD -Os -Wall -I$STAGING/include/libnl3"
export LDFLAGS="-static -L$STAGING/lib"
export LIBS="-lm"
make -j"$(nproc)" hostapd hostapd_cli

"${CROSS}strip" hostapd hostapd_cli
cp hostapd     "$OUT/hostapd.softfloat"
cp hostapd_cli "$OUT/hostapd_cli.softfloat"
cp .config     "$OUT/hostapd-2.11.config"

# ---------------- ABI verification (MUST match busybox.softfloat) ----------------
echo "=== ABI check (want: v5TEJ / ARM926EJ-S, NO Tag_FP_arch, NO Tag_ABI_VFP_args, static) ==="
for b in "$OUT/hostapd.softfloat" "$OUT/hostapd_cli.softfloat"; do
    echo "--- $b"
    file "$b"
    "${CROSS}readelf" -A "$b"
    if "${CROSS}readelf" -A "$b" | grep -qE "Tag_FP_arch|Tag_ABI_VFP_args"; then
        echo "FATAL: $b has hard-float/VFP tags — DO NOT deploy (will SIGILL)"; exit 1
    fi
done
echo "OK: both binaries are soft-float (no FP/VFP ABI tags)."
ls -la "$OUT"/hostapd*.softfloat
