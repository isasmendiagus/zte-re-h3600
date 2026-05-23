#!/bin/sh
# Try syslog read or kernel ringbuffer
# /proc/kmsg is BLOCKING stream of NEW msgs only. The history is in kernel buf.
# busybox might have dmesg as applet
busybox dmesg 2>&1 > /tmp/d3 && echo "BUSYBOX DMESG OK" || echo "no busybox dmesg"
ls -la /tmp/d3 2>&1

echo "=== /proc/sys/kernel/printk_ratelimit ==="
ls /proc/sys/kernel/ | grep -i print 2>&1

echo "=== Look for syslog ==="
ls /var/log 2>&1
ls /proc/sys/kernel/ 2>&1 | head -30

echo "=== TM/IRQ symbols ==="
grep -iE " pon_tm_net|pon_tm_int|sbrg_add|cla_set_hash|pon_tm_irq|set_pon_tm" /proc/kallsyms 2>/dev/null

echo "=== ppPm sysfs ==="
ls /sys/devices/platform/tm/ppPm 2>&1

echo "=== nppPm sysfs ==="
ls /sys/devices/platform/tm/nppPm 2>&1

echo "=== sysfs hooks summary ==="
for D in /sys/devices/platform/tm/*/; do
    NAME=$(basename $D)
    echo "--- $NAME ---"
    ls $D 2>&1
done
