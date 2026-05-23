#!/bin/sh
cat /proc/kmsg > /tmp/sm.k 2>&1 &
KP=$!
sleep 0.3
# smacfiltermode is write-only - try a few args
for ARG in "0" "0 0" "5" "5 0" "5 1"; do
    echo "=== smacfiltermode $ARG ===" >> /tmp/sm.k 2>&1
    (echo "$ARG" > /sys/devices/platform/tm/ppBrg/smacfiltermode) 2>/dev/null
    sleep 0.2
done
# v4Table - IP table?
cat /sys/devices/platform/tm/ppBrg/v4Table 2>&1 >> /tmp/sm.k
echo "=== v4end ===" >> /tmp/sm.k
sleep 1
kill $KP 2>/dev/null
sleep 0.5
cat /tmp/sm.k
