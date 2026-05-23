#!/bin/sh
# Usage: dumpregs.sh START_HEX COUNT > out.txt
# START_HEX is 8 hex digits without 0x (e.g. "92340000"). COUNT = words.
# Generates address list in Python-like form via shell hex math.
START_HEX=$1
COUNT=$2
# Use printf-based hex arithmetic: split start into high/low halves
# start_hi = upper 16 bits, start_lo = lower 16 bits, both fit in busybox int.
hi=$(echo $START_HEX | cut -c1-4)
lo=$(echo $START_HEX | cut -c5-8)
hi_dec=$(printf "%d" 0x$hi)
lo_dec=$(printf "%d" 0x$lo)
i=0
while [ $i -lt $COUNT ]; do
    cur_lo=$((lo_dec + i*4))
    # carry into hi if cur_lo >= 65536
    extra_hi=$((cur_lo / 65536))
    cur_lo=$((cur_lo % 65536))
    cur_hi=$((hi_dec + extra_hi))
    addr=$(printf "%04x%04x" $cur_hi $cur_lo)
    v=$(devmem2 0x$addr w 2>/dev/null | sed -n 's/.*: \(0x[0-9A-Fa-f]*\).*/\1/p')
    printf '%s %s\n' "$addr" "$v"
    i=$((i + 1))
done
