#!/bin/sh
# Stock comprehensive HW state dump.
# Writes commands to sysfs, captures kmsg output to /tmp/stock_state.log

LOG=/tmp/stock_state.log
> "$LOG"

# Start kmsg capture
cat /proc/kmsg > /tmp/k.live 2>&1 &
KPID=$!
sleep 0.3

# Helper: write to file, log section
do_write() {
    local desc="$1"; local file="$2"; local val="$3"
    echo "###[$desc] echo $val > $file" >> "$LOG"
    (echo "$val" > "$file") 2>/dev/null
    sleep 0.2
}

# Per-port stats (try ports 0-7)
for P in 0 1 2 3 4 5 6 7; do
    do_write "GPORT_STATS1 port=$P" /sys/devices/platform/tm/tmTest/gportstatistics1 "$P"
done
for P in 0 1 2 3 4 5 6 7; do
    do_write "SPORT_STATS1 port=$P" /sys/devices/platform/tm/tmTest/sportingratelimit "$P"
done

# CLA HW state
do_write "CLA_FASTENTRYNUM" /sys/devices/platform/tm/ppCla/gfastentrynum "0"
do_write "CLA_GHASHTABLE bucket=0" /sys/devices/platform/tm/ppCla/ghashtable "0"
do_write "CLA_STATICS" /sys/devices/platform/tm/ppCla/statics "0"
do_write "CLA_HELP" /sys/devices/platform/tm/ppCla/helpCla "0"

# NPP port status
do_write "GPORT_STATUS_0" /sys/devices/platform/tm/nppGreg/gportstatus "0"
do_write "GPORT_STATUS_1" /sys/devices/platform/tm/nppGreg/gportstatus "1"
do_write "SPORT_STATUS_0" /sys/devices/platform/tm/nppGreg/sportstatus "0"
do_write "SPORT_STATUS_1" /sys/devices/platform/tm/nppGreg/sportstatus "1"

sleep 1
kill $KPID 2>/dev/null
sleep 0.5

echo "" >> "$LOG"
echo "==== KMSG CAPTURE ====" >> "$LOG"
cat /tmp/k.live >> "$LOG" 2>&1

# Print full log
cat "$LOG"
