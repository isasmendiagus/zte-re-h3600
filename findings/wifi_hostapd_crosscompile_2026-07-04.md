# Soft-float hostapd 2.11 cross-compile for the H3600 (2026-07-04)

Device-free. Unblocks the Stage-2 AP bring-up (the missing userspace piece per
`wifi_stage2_prep_2026-07-04.md`). No device contact was made.

## Toolchain (mirrored from the proven busybox.softfloat recipe)

Bootlin **armv5-eabi--glibc--stable-2018.11-1**
(`/home/ubuntu/toolchains/...`, gcc 7.3.0, prefix `arm-linux-` =
`arm-buildroot-linux-gnueabi-`). Soft-float, emits zero VFP instructions;
armv5 code runs fine on the no-VFP Cortex-A9. Static link throughout (no .so
gaps on the minimal initramfs), exactly like busybox.

**Gotcha found:** `$TC/bin` must be APPENDED to PATH, not prepended — the
toolchain ships its own `bison`/`m4`/`pkg-config` with a hardcoded
`/opt/armv5-eabi...` prefix that errors out if the toolchain lives elsewhere
(ours is in `~/toolchains/`). Host bison/flex must win; the `arm-linux-*`
names are unique so appending is safe.

## What was built

Script: `tasks/00.07.wifi/scripts/build_hostapd_softfloat.sh` (one-shot,
sha256-pinned downloads, rebuilds from clean tree, ABI-gates the output).

1. **libnl 3.5.0** — static (`--enable-static --disable-shared --disable-cli
   --disable-pthreads --disable-debug`, CFLAGS=-Os), installed to a staging
   prefix. Provides `libnl-3.a` + `libnl-genl-3.a` (hostapd's nl80211 deps).
   - **libnl 3.9.0 does NOT build** with this 2018 toolchain (glibc-header
     `struct tm`/`gmtime_r` breakage in `lib/xfrm/` — code hostapd doesn't
     use). 3.5.0 is era-matched and builds clean.
2. **hostapd 2.11** (`hostapd` + `hostapd_cli`), sha256
   `2b3facb632fd4f65e32f4bf82a76b4b72c501f995a4f62e330219fe7aed1747a`.

### hostapd .config (full copy at `tasks/00.07.wifi/userland/hostapd-2.11.config`)
```
CONFIG_DRIVER_NL80211=y     CONFIG_LIBNL32=y
CONFIG_IEEE80211N=y  CONFIG_IEEE80211AC=y  CONFIG_IEEE80211AX=y
CONFIG_TLS=internal  CONFIG_INTERNAL_LIBTOMMATH=y
CONFIG_NO_RADIUS=y  CONFIG_NO_ACCOUNTING=y  CONFIG_NO_VLAN=y
```
WPA2-PSK/CCMP is hostapd core (always in); ctrl_interface is default-on
(`CONFIG_NO_CTRL_IFACE` unset) so `hostapd_cli` works. `CONFIG_TLS=internal`
avoids an OpenSSL cross-build — sufficient for WPA2-PSK.

**Build gotcha:** `CC/CFLAGS/LDFLAGS/LIBS` must be exported via the
ENVIRONMENT, not given on the make command line — command-line CFLAGS
override the Makefile's `CFLAGS += -I../src` appends and the build dies on
`utils/includes.h: No such file`. `LDFLAGS=-static`, `-L<staging>/lib`,
`-I<staging>/include/libnl3`.

## ABI verification (static only — NOT run on host, wrong arch)

`arm-linux-readelf -A` on both binaries — attribute set is IDENTICAL to the
HW-verified `busybox.softfloat`:
```
Tag_CPU_name: "ARM926EJ-S"
Tag_CPU_arch: v5TEJ
(no Tag_FP_arch, no Tag_ABI_VFP_args)   ← soft-float, no VFP
```
`file`: `ELF 32-bit LSB executable, ARM, EABI5 ... statically linked, for
GNU/Linux 4.1.0, stripped`. The build script hard-fails if any FP/VFP tag
appears. Feature strings confirmed in the binary: `nl80211`, `ieee80211ac`,
`ieee80211ax`, `he_su_beamformer`, `vht_capab`, `ctrl_interface`,
`wpa_passphrase`. hostapd compiled with zero warnings (the ~100 in the log
are all libnl-internal yacc/style noise).

## Sizes and staging

| Binary | Size | Where |
|---|---|---|
| `hostapd` | 1,218,348 B | `tasks/00.07.wifi/userland/hostapd.softfloat` (canonical) |
| `hostapd_cli` | 537,984 B | `tasks/00.07.wifi/userland/hostapd_cli.softfloat` |

Staged for the boot flow (same two spots busybox occupies):
- `tasks/00.01.eth-driver/initramfs/bin/{hostapd,hostapd_cli}` (git-tracked,
  same convention as the tracked busybox)
- `/tmp/initramfs_extract/bin/{hostapd,hostapd_cli}` (the live
  `CONFIG_INITRAMFS_SOURCE` — next `build_slotA.py` re-embed picks them up;
  ~1.7 MB uncompressed added to the initramfs)

No secret staged: the tracked `configs/hostapd-ap.conf.template` is
placeholder-only (`@WIFI_PSK@`); render on-device via
`scripts/gen_wifi_configs.sh` from git-ignored `scratchpad/.wifi_psk`.

## How to regenerate
```
tasks/00.07.wifi/scripts/build_hostapd_softfloat.sh
```
(re-uses downloaded tarballs in `tasks/00.07.wifi/build/` — git-ignored —
verifies sha256, rebuilds clean, re-verifies ABI, refreshes `userland/`.
Re-staging into the two initramfs locations is a manual `cp`, see README.)

## On-device notes for the next (device) agent
- `ctrl_interface=/var/run/hostapd` — ensure `/var/run` exists before start.
- regdb pair + non-world `country_code` mandatory or 5 GHz is NO-IR → AP
  refuses to start (see `wifi_stage2_prep_2026-07-04.md` §5).
- 5 GHz radio is **wlan1**; rename the template SSID before radiating (it
  currently equals the owner's home SSID).
