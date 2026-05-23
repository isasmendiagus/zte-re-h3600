#!/bin/sh
echo "=== DMESG ==="
cat /proc/kmsg > /tmp/k.live 2>&1 &
KP=$!
sleep 1
kill $KP 2>/dev/null
sleep 0.5
# Actually need full dmesg - use dmesg if available, else /var/log/messages
echo "===dmesg attempt==="
dmesg 2>&1 || echo "no dmesg"
echo "===klog==="
cat /tmp/k.live | head -200

echo "=== KPROBE CHECK ==="
ls /sys/kernel/debug/kprobes 2>&1
ls /sys/kernel/debug/tracing 2>&1 | head
cat /proc/kallsyms | grep -E "kprobe_register$" | head -3
cat /proc/sys/kernel/kprobes_optimization 2>&1

echo "=== FTRACE CHECK ==="
ls /sys/kernel/debug/tracing/available_tracers 2>&1
cat /sys/kernel/debug/tracing/available_tracers 2>&1 | head -5

echo "=== STOCK TM IRQ INIT STATE ==="
cat /proc/interrupts | grep -iE "tm|pon|idm|npp"
