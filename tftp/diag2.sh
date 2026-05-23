#!/bin/sh
# Mount debugfs first
mount -t debugfs none /sys/kernel/debug 2>&1
echo "=== check debugfs ==="
ls /sys/kernel/debug 2>&1
echo "=== klog (full) ==="
# Read /proc/kmsg as snapshot (already-printed messages stay in ringbuffer)
# But /proc/kmsg is a blocking stream that returns ONLY new msgs.
# Try /dev/kmsg instead (Linux 3.5+ ringbuffer)
ls /dev/kmsg 2>&1
cat /dev/kmsg > /tmp/dmesg.txt 2>&1 &
CP=$!
sleep 0.5
kill $CP 2>/dev/null
sleep 0.3
wc -l /tmp/dmesg.txt
