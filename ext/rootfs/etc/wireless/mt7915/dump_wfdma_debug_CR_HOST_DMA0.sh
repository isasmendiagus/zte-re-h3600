#!/bin/sh

debug_cr_base=7c024124
debug_cr_val=7c024128
dump_cr_index=256

while [ "${dump_cr_index}" != "326" ]
do
        x=`printf '%x' ${dump_cr_index}`
        iwpriv wlan0 mac ${debug_cr_base}=${x}
        iwpriv wlan0 mac ${debug_cr_val}
        dump_cr_index=$((${dump_cr_index}+1))
done
