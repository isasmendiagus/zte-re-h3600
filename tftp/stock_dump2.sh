#!/bin/sh
# SAFE stock state dump v2 — only query-type writes

> /tmp/k.live
cat /proc/kmsg > /tmp/k.live 2>&1 &
KPID=$!
sleep 0.3

# Port 0 stats (the active LAN port)
for VAR in gportstatistics1 gportstatistics2 gportstatistics3 gportstatistics4; do
    (echo "0" > /sys/devices/platform/tm/tmTest/$VAR) 2>/dev/null
    sleep 0.2
done

# Sample CLA hashtable: 32 buckets across range  
for B in 0 1 2 3 4 5 8 16 32 64 128 256 512 700 769 800 906 1000 1023; do
    (echo "$B" > /sys/devices/platform/tm/ppCla/ghashtable) 2>/dev/null
    sleep 0.1
done

# Fast rule info (probably dumps all)
(echo "0" > /sys/devices/platform/tm/ppCla/showfastinfoall) 2>/dev/null
sleep 0.5
(echo "0" > /sys/devices/platform/tm/ppCla/showfastrule) 2>/dev/null
sleep 0.5
(echo "0" > /sys/devices/platform/tm/ppCla/showaclinfoall) 2>/dev/null
sleep 0.5
(echo "0" > /sys/devices/platform/tm/ppCla/gfastentrynum) 2>/dev/null
sleep 0.3
(echo "0" > /sys/devices/platform/tm/ppCla/gclacfg) 2>/dev/null
sleep 0.3

# Extra rule + index tables
for I in 0 1 2 3 4 5 8 16; do
    (echo "$I" > /sys/devices/platform/tm/ppCla/gextraruletable) 2>/dev/null
    sleep 0.1
done
for I in 0 1 2 3 4 5 8 16; do
    (echo "$I" > /sys/devices/platform/tm/ppCla/gextraindextable) 2>/dev/null
    sleep 0.1
done

sleep 1
kill $KPID 2>/dev/null
sleep 0.5
cat /tmp/k.live
