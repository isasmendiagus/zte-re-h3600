#!/bin/sh
> /tmp/help.out
cat /proc/kmsg > /tmp/khelp 2>&1 &
KP=$!
sleep 0.3
echo "0" > /sys/devices/platform/tm/ppBrg/helpBrg 2>&1
sleep 1
echo "0" > /sys/devices/platform/tm/ppCla/helpCla 2>&1
sleep 1
kill $KP 2>/dev/null
sleep 0.5
cat /tmp/khelp > /tmp/help.out
cat /tmp/help.out
