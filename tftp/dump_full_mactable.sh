#!/bin/sh
# Try to capture FULL macTable output - sbrg_print_mactable iterates 1024 entries
echo 8 > /proc/sys/kernel/printk  # max console verbosity
# Pre-buffer kmsg
cat /proc/kmsg > /tmp/mt.k 2>&1 &
KP=$!
sleep 0.5
cat /sys/devices/platform/tm/ppBrg/macTable > /dev/null
sleep 3
kill $KP 2>/dev/null
sleep 0.5
echo "=== SIZE ===" 
wc -l /tmp/mt.k
cat /tmp/mt.k
