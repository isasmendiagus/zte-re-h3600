#!/bin/sh
echo "=== current cmdline ==="
cat /proc/cmdline
echo "=== loglevel ==="
cat /proc/sys/kernel/printk
echo "=== uart console ==="
cat /proc/consoles 2>&1
