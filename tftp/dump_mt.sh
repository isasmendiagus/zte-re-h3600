#!/bin/sh
cat /proc/kmsg > /tmp/mt.k 2>&1 &
KP=$!
sleep 0.5
echo "READING MACTABLE..."
cat /sys/devices/platform/tm/ppBrg/macTable >> /tmp/mt.k
sleep 2
kill $KP 2>/dev/null
sleep 0.5
echo "=== KMSG SIZE ==="
wc -c /tmp/mt.k 2>&1
cat /tmp/mt.k
