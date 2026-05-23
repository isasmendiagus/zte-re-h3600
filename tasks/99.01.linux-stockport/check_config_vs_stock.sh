#!/usr/bin/env bash
#
# check_config_vs_stock.sh — diff our stockport .config against /etc/autokernelconf
#
# Stock H3600's rootfs ships its own kernel build config at
# /etc/autokernelconf (with `@` as comment marker instead of `#`).
# Diffing against it from the start would have saved us multiple
# hours this session chasing silent boots / NULL crashes.
#
# Usage:
#   ./check_config_vs_stock.sh                       # full diff
#   ./check_config_vs_stock.sh --critical            # only knobs we know matter
#   ./check_config_vs_stock.sh --fix                 # auto-pin critical knobs
#
set -euo pipefail

ROOT="$(cd "$(dirname "$0")" && pwd)"
OUR_CFG="$ROOT/linux-4.1.25/.config"
STOCK_CFG="$ROOT/../rootfs/etc/autokernelconf"

[ -f "$OUR_CFG" ]   || { echo "ERROR: $OUR_CFG missing — run ./build.sh kernel first" >&2; exit 1; }
[ -f "$STOCK_CFG" ] || { echo "ERROR: $STOCK_CFG missing (rootfs not extracted?)" >&2; exit 1; }

# Convert stock's `@` comment marker → `#` so diff works.
STOCK_NORM="$(mktemp)"
trap "rm -f $STOCK_NORM" EXIT
sed 's|^@|#|' "$STOCK_CFG" > "$STOCK_NORM"

# === Knobs known to cause real-world boot/init failures if mismatched ===
# Format: KNOB:reason
CRITICAL=(
	"CONFIG_VMSPLIT_3G:plat pon_tm_bmu_init formula relies on PAGE_OFFSET=0xC0000000"
	"CONFIG_PAGE_OFFSET:must be 0xC0000000 for stock memory layout"
	"CONFIG_PHYS_OFFSET:RAM base (0x40000000 for H3600)"
	"CONFIG_ARM_PATCH_PHYS_VIRT:must NOT be set if PHYS_OFFSET is hard-coded"
	"CONFIG_ARCH_ZX279128S:enables mach-zx code (stock symbol name)"
	"CONFIG_MACH_ZX279128S:machine descriptor scaffolding"
	"CONFIG_ARM_APPENDED_DTB:DTB appended to zImage"
	"CONFIG_ARM_ATAG_DTB_COMPAT:merges bootloader cmdline into DT"
	"CONFIG_ARM_ATAG_DTB_COMPAT_CMDLINE_FROM_BOOTLOADER:bootloader cmdline wins"
	"CONFIG_DEBUG_LL:early UART output (without this, silent boot)"
	"CONFIG_DEBUG_LL_UART_PL01X:use pl01x.S DEBUG_LL macros"
	"CONFIG_DEBUG_UART_PHYS:0x94404000 — console UART phys"
	"CONFIG_DEBUG_UART_VIRT:0xf0704000 — NOT 0xf0404000 (we had this wrong)"
	"CONFIG_DEBUG_LL_INCLUDE:debug/pl01x.S"
	"CONFIG_EARLY_PRINTK:hooks DEBUG_LL into early console"
	"CONFIG_CMDLINE_FROM_BOOTLOADER:use ATAG cmdline"
	"CONFIG_ARCH_MULTI_V7:generic ARMv7 multiplatform"
	"CONFIG_CPU_V7:Cortex-A9"
	"CONFIG_SMP:dual-core"
	"CONFIG_HZ_100:100 Hz timer"
	"CONFIG_HZ:100 (must match HZ_100=y)"
	"CONFIG_SERIAL_AMBA_PL011:console driver"
	"CONFIG_SERIAL_AMBA_PL011_CONSOLE:enable as kernel console"
	"CONFIG_UNINLINE_SPIN_UNLOCK:export _raw_spin_unlock (stock .ko need it)"
	"CONFIG_INITRAMFS_SOURCE:must be /tmp/initramfs_stockport"
)

normalize() {
	# Strip whitespace and trailing comments, keep CONFIG_*=...  and "# CONFIG_* is not set"
	grep -E '^(CONFIG_|# CONFIG_)' "$1" | sed 's|[[:space:]]*$||'
}

get_val() {
	# get_val FILE KNOB → prints the value (or NOT_SET, or MISSING)
	local f=$1 k=$2
	local line
	line=$(grep -E "^${k}=" "$f" 2>/dev/null || true)
	if [ -n "$line" ]; then
		echo "${line#${k}=}"
		return
	fi
	if grep -qE "^# ${k} is not set\$" "$f" 2>/dev/null; then
		echo "NOT_SET"
		return
	fi
	echo "MISSING"
}

mode="${1:-default}"
case "$mode" in
	--critical|critical)
		echo "=== Critical-knobs diff: stock /etc/autokernelconf vs our .config ==="
		printf "%-50s %-25s %-25s %s\n" "KNOB" "STOCK" "OURS" "RESULT"
		printf "%-50s %-25s %-25s %s\n" "----" "-----" "----" "------"
		for entry in "${CRITICAL[@]}"; do
			knob="${entry%%:*}"
			s=$(get_val "$STOCK_NORM" "$knob")
			o=$(get_val "$OUR_CFG"    "$knob")
			if [ "$s" = "$o" ]; then
				printf "%-50s %-25s %-25s %s\n" "$knob" "$s" "$o" "OK"
			else
				printf "%-50s %-25s %-25s \e[31mMISMATCH\e[0m\n" "$knob" "$s" "$o"
			fi
		done
		;;
	--full|full|default)
		echo "=== Full diff (stock left, ours right) ==="
		diff -u <(normalize "$STOCK_NORM" | sort) <(normalize "$OUR_CFG" | sort) | head -200
		;;
	--fix|fix)
		echo "Fix mode: writing all critical knobs to .config (run ./build.sh kernel after)"
		for entry in "${CRITICAL[@]}"; do
			knob="${entry%%:*}"
			s=$(get_val "$STOCK_NORM" "$knob")
			[ "$s" = "MISSING" ] && continue
			if [ "$s" = "NOT_SET" ]; then
				sed -i "/^${knob}=/d" "$OUR_CFG"
				grep -qE "^# ${knob} is not set\$" "$OUR_CFG" || echo "# ${knob} is not set" >> "$OUR_CFG"
			else
				sed -i "/^${knob}=/d;/^# ${knob} is not set\$/d" "$OUR_CFG"
				echo "${knob}=${s}" >> "$OUR_CFG"
			fi
			echo "  pinned: ${knob}=${s}"
		done
		echo "Done. Run: cd linux-4.1.25 && make olddefconfig && cd .. && ./build.sh kernel"
		;;
	*)
		echo "Usage: $0 [--critical | --full | --fix]" >&2; exit 2 ;;
esac
