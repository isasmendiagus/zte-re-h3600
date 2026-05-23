#!/bin/sh
echo "=== PRE INTERRUPTS ==="
cat /proc/interrupts | grep -iE "tm|pon|idm|npp|sbrg|smac|switch"
echo "=== START PING (host→modem) ==="
# wait for caller to ping
sleep 6
echo "=== POST INTERRUPTS ==="
cat /proc/interrupts | grep -iE "tm|pon|idm|npp|sbrg|smac|switch"
echo "=== MACTABLE ==="
cat /sys/devices/platform/tm/ppBrg/macTable
