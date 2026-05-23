#!/bin/sh
> /tmp/d4.out
cat /proc/kmsg > /tmp/k.live 2>&1 &
KP=$!
sleep 0.3

# Query nppSpa stuff
for OP in statics g802xtrap; do
    echo "--- $OP all ports ---" >> /tmp/d4.out
    for P in 0 1 2 3 4 5 6 7; do
        echo "==$OP p=$P==" >> /tmp/d4.out
        (echo $P > /sys/devices/platform/tm/nppSpa/$OP) 2>/dev/null
        sleep 0.1
    done
done

# Also helpSpa to see usage
echo "--- helpSpa ---" >> /tmp/d4.out
cat /sys/devices/platform/tm/nppSpa/helpSpa >> /tmp/d4.out 2>&1
echo "--- helpAdm ---" >> /tmp/d4.out
cat /sys/devices/platform/tm/ppAdm/helpAdm >> /tmp/d4.out 2>&1
echo "--- helpOpc (ppPm) ---" >> /tmp/d4.out
cat /sys/devices/platform/tm/ppPm/helpOpc >> /tmp/d4.out 2>&1

# pp Cla showfastinfoall
echo "=== showfastinfoall ===" >> /tmp/d4.out
(echo 0 > /sys/devices/platform/tm/ppCla/showfastinfoall) 2>/dev/null
sleep 1

sleep 1
kill $KP 2>/dev/null
sleep 0.5
echo "===KMSG===" >> /tmp/d4.out
cat /tmp/k.live >> /tmp/d4.out
cat /tmp/d4.out
