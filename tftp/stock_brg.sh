#!/bin/sh
LOG=/tmp/brg.out
> $LOG
cat /proc/kmsg > /tmp/k.live 2>&1 &
KPID=$!
sleep 0.3

# ppBrg ops - probable FDB queries
echo "=== ppBrg ls ===" >> $LOG
ls /sys/devices/platform/tm/ppBrg/ >> $LOG 2>&1

# Try common FDB query files
for OP in showfdb show_fdb fdb_show getfdb showFdb showVlan getVlan helpBrg; do
    (echo 0 > /sys/devices/platform/tm/ppBrg/$OP) 2>/dev/null && echo "OK_$OP" >> $LOG
    sleep 0.1
done

# Also try writing to discover (some may be write-only show all)
for F in /sys/devices/platform/tm/ppBrg/*; do
    NAME=$(basename $F)
    (echo 0 > $F) 2>/dev/null
    sleep 0.1
done

sleep 1
kill $KPID 2>/dev/null
sleep 0.5
echo "=== KMSG ===" >> $LOG
cat /tmp/k.live >> $LOG
cat $LOG
