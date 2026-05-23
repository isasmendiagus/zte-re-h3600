#!/bin/sh
> /tmp/fdb.out
cat /proc/kmsg > /tmp/k.live 2>&1 &
KPID=$!
sleep 0.3

# Query MAC table - try various args (0=dump all, by bucket, by mac, etc)
for ARG in "0" "0 0" "1" "1 0" "0 1 0 0 0 0 0 0"; do
    echo "=== macTable arg=[$ARG] ===" >> /tmp/fdb.out
    (echo "$ARG" > /sys/devices/platform/tm/ppBrg/macTable) 2>/dev/null
    sleep 0.2
done

# show vlan table
for ARG in "0" "0 0" "1"; do
    echo "=== vlanTable arg=[$ARG] ===" >> /tmp/fdb.out
    (echo "$ARG" > /sys/devices/platform/tm/ppBrg/vlanTable) 2>/dev/null
    sleep 0.1
done

# Port info / status
for OP in PortInfo portStatus portStat; do
    for P in 0 1 2 3 4 5 6 7; do
        echo "=== $OP port=$P ===" >> /tmp/fdb.out
        (echo $P > /sys/devices/platform/tm/ppBrg/$OP) 2>/dev/null
        sleep 0.1
    done
done

sleep 1
kill $KPID 2>/dev/null
sleep 0.5
echo "=== KMSG ===" >> /tmp/fdb.out
cat /tmp/k.live >> /tmp/fdb.out
cat /tmp/fdb.out
