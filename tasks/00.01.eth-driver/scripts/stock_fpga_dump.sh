#!/bin/sh
# Capture stock kernel printk output while running fpga -r commands.
# Useful for dumping TM/PP/NPP/etc. registers via zx_ponreg's /dev/fpga ioctl.

set -u
OUT=/tmp/kmsg.out
> "$OUT"

# Start kmsg capture in background
cat /proc/kmsg > "$OUT" 2>&1 &
KPID=$!
sleep 0.3

# Run the queries the user wants — passed as args
for spec in "$@"; do
    addr=$(echo "$spec" | cut -d, -f1)
    count=$(echo "$spec" | cut -d, -f2)
    echo "### fpga -r $addr $count"
    fpga -r "$addr" "$count"
done

sleep 0.3
kill $KPID 2>/dev/null
sleep 0.2

echo "=== KMSG CAPTURE ==="
cat "$OUT"
