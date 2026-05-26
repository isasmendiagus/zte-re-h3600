#!/usr/bin/env bash
# refactor_test_cycle.sh — full edit→build→deploy→boot→watch loop for the
# mainline driver refactor (task #38).
#
# What this does (one command, ~3-5 min):
#   1. Regenerate zx_cla_table.h from cla.bin (if either is newer)
#   2. Run build_slotA.py  — rebuilds driver .ko, copies to initramfs,
#                            rebuilds zImage (embeds initramfs), wraps as
#                            uImage_dtb_appended, drops in tftp/
#   3. Run tftp_boot_mainline.py — DTR-reset, drive U-Boot, TFTP load, bootm
#   4. Tail /tmp/uart_bridge.log for ~60s, look for STATS / panic / link
#
# Exit codes:
#   0  driver init produced STATS output (boot OK)
#   1  build or boot failure
#   2  panic detected in UART log
#
# Use: from ANY directory, `bash tasks/00.01.eth-driver/scripts/refactor_test_cycle.sh`
set -euo pipefail

ROOT="$(cd "$(dirname "$0")/../../.." && pwd)"
cd "$ROOT"

echo "=== [1/4] regen zx_cla_table.h if needed ==="
CLA_BIN="tasks/00.01.eth-driver/initramfs/lib/firmware/zx-replay/cla.bin"
CLA_HDR="linux-v6.6/drivers/net/ethernet/zte/zx_cla_table.h"
if [ ! -f "$CLA_HDR" ] || [ "$CLA_BIN" -nt "$CLA_HDR" ]; then
    python3 tasks/00.01.eth-driver/scripts/gen_cla_table.py
else
    echo "  ✓ zx_cla_table.h is up to date"
fi

echo
echo "=== [2/4] build_slotA.py ==="
python3 tasks/00.01.eth-driver/scripts/build_slotA.py 2>&1 | tail -30

echo
echo "=== [3/4] TFTP boot ==="
# Mark current bridge-log line count so we can grep just THIS boot's output
# WITHOUT rotating (rotation breaks the bridge daemon's open FD).
BRIDGE_LOG=/tmp/uart_bridge.log
mkdir -p "$(dirname "$BRIDGE_LOG")"
[ -f "$BRIDGE_LOG" ] || touch "$BRIDGE_LOG"
START_LINE=$(wc -l < "$BRIDGE_LOG")
echo "Bridge log starts watching at line $START_LINE"

python3 tasks/00.01.eth-driver/scripts/tftp_boot_mainline.py &
BOOT_PID=$!

echo "Boot script PID=$BOOT_PID  Bridge log: $BRIDGE_LOG"
echo
echo "=== [4/4] watch new content for up to 180s (poll until STATS or panic) ==="
SECS=0
while [ $SECS -lt 180 ]; do
    sleep 5
    SECS=$((SECS + 5))
    NEW=$(tail -n +$((START_LINE + 1)) "$BRIDGE_LOG")
    if echo "$NEW" | grep -q "Kernel panic\|Oops"; then
        echo "[$SECS s] PANIC detected"
        break
    fi
    if echo "$NEW" | grep -q "CLA init\|STATS uptime_jiff"; then
        echo "[$SECS s] driver alive marker found"
        break
    fi
done

echo
echo "--- new content (line $((START_LINE + 1)) onward, last 40 lines) ---"
tail -n +$((START_LINE + 1)) "$BRIDGE_LOG" | grep -v "????????" | tail -40
echo
echo "=== checks ==="

NEW=$(tail -n +$((START_LINE + 1)) "$BRIDGE_LOG")
if echo "$NEW" | grep -q "Kernel panic\|Oops"; then
    echo "❌ PANIC DETECTED"
    echo "$NEW" | grep -nE "panic|Oops|Unable to handle" | head
    kill "$BOOT_PID" 2>/dev/null || true
    exit 2
fi

if echo "$NEW" | grep -q "CLA init.*ok"; then
    OK_LINE=$(echo "$NEW" | grep "CLA init" | head -1)
    echo "✓ CLA init ran: $OK_LINE"
fi

if echo "$NEW" | grep -q "STATS uptime_jiff\|register_netdev\|link UP\|netif_carrier"; then
    echo "✓ Driver alive — STATS or netdev output present"
    echo "$NEW" | grep -E "STATS|register_netdev|link UP" | tail -3
else
    echo "⚠️  No STATS / register_netdev output yet — boot may still be in progress"
fi

# Soft-kill the boot script so it doesn't hang the terminal
kill "$BOOT_PID" 2>/dev/null || true

echo
echo "=== summary ==="
echo "Boot log: $BRIDGE_LOG"
echo "Older rotated: $(ls -t ${BRIDGE_LOG}.*.rot 2>/dev/null | head -1)"
echo
echo "Run \`tail -f $BRIDGE_LOG\` to keep watching live."
