# Soft-float hostapd for the no-VFP ZX279128S (AP bring-up, Stage 2)

Cross-compiled 2026-07-04, device-free. Same rule as busybox
(`tasks/00.01.eth-driver/userland/README.md`): the Cortex-A9 here has **no
VFP**, so any hard-float binary SIGILLs (exit=4). Everything userland must be
soft-float + static.

## What's here
- `hostapd.softfloat` (1,218,348 B) — hostapd 2.11, static, stripped
- `hostapd_cli.softfloat` (537,984 B) — control-interface CLI, static, stripped
- `hostapd-2.11.config` — the exact build `.config` used

## Recipe (fully scripted)
`../scripts/build_hostapd_softfloat.sh` — downloads (sha256-pinned), builds,
ABI-verifies, and drops the binaries here. Summary:
- Toolchain: Bootlin **armv5-eabi--glibc--stable-2018.11-1** (gcc 7.3.0,
  prefix `arm-linux-`) — the SAME toolchain that produced busybox.softfloat.
  ⚠ APPEND its bin/ to PATH, don't prepend: it ships a broken bison/m4
  (hardcoded /opt paths) that must not shadow the host tools.
- libnl **3.5.0** static (`--enable-static --disable-shared --disable-cli
  --disable-pthreads`). NOT 3.9.x — too new for the 2018 glibc headers
  (struct tm breakage in lib/xfrm/).
- hostapd **2.11**: `CONFIG_DRIVER_NL80211` + `CONFIG_LIBNL32`,
  `IEEE80211N/AC/AX`, `CONFIG_TLS=internal` (no OpenSSL dep), RADIUS/
  accounting/VLAN stripped. ctrl_interface default-on. WPA2-PSK/CCMP core.
- Flags passed via ENVIRONMENT (`CC/CFLAGS/LDFLAGS=-static/LIBS`), not the
  make command line (command-line CFLAGS kills the Makefile's -I appends).

## ABI (verified, matches busybox.softfloat exactly)
`arm-linux-readelf -A`: `Tag_CPU_name: ARM926EJ-S`, `Tag_CPU_arch: v5TEJ`,
**no `Tag_FP_arch`, no `Tag_ABI_VFP_args`** → soft-float, zero VFP
instructions. `file`: ELF 32-bit ARM EABI5, statically linked, stripped.
NOT run on the host (wrong arch) — static verification only.

## Install / on-device use
Staged (same flow as busybox) in BOTH:
- `tasks/00.01.eth-driver/initramfs/bin/{hostapd,hostapd_cli}` (tracked mirror)
- `/tmp/initramfs_extract/bin/` (live `CONFIG_INITRAMFS_SOURCE`; build_slotA.py
  re-embeds on next kernel build — adds ~1.7 MB uncompressed to the initramfs)

Runtime config: render `../configs/hostapd-ap.conf.template` on-device with
`../scripts/gen_wifi_configs.sh` (PSK comes from git-ignored
`scratchpad/.wifi_psk` — never bake it into the image). `ctrl_interface=
/var/run/hostapd` — make sure `/var/run` exists (tmpfs) before starting.
Regdb + non-world `country_code` required or 5 GHz is NO-IR and AP start fails.
