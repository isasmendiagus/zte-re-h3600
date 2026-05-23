#!/bin/sh

if [[ "$1" == "--help" ]];
then
   echo "Please type in:$0 'wlanx' 'mac'."
   echo "'wlanx' is the wlan interface, 'wlanx' default is wlan5g0."
   echo "'mac' is sta mac, %02x:%02x:%02x:%02x:%02x:%02x."
   exit 1
fi

WLAN_STR=wlan5g0

case "$1" in
"wlan"*)
    WLAN_STR=$1;;
esac

debug_cr_base_HOST=7c024124
debug_cr_val_HOST=7c024128
dump_cr_index_HOST=256

while [ "${dump_cr_index_HOST}" != "326" ]
do
        x=`printf '%x' ${dump_cr_index_HOST}`
        iwpriv $WLAN_STR mac ${debug_cr_base_HOST}=${x}
        iwpriv $WLAN_STR mac ${debug_cr_val_HOST}
        dump_cr_index_HOST=$((${dump_cr_index_HOST}+1))
done
sleep 3

debug_cr_base_MCU=54000124
debug_cr_val_MCU=54000128
dump_cr_index_MCU=256

while [ "${dump_cr_index_MCU}" != "326" ]
do
        x=`printf '%x' ${dump_cr_index_MCU}`
        iwpriv $WLAN_STR mac ${debug_cr_base_MCU}=${x}
        iwpriv $WLAN_STR mac ${debug_cr_val_MCU}
        dump_cr_index_MCU=$((${dump_cr_index_MCU}+1))
done
sleep 3

debug_cr_base_MEM=58000124
debug_cr_val_MEM=58000128
dump_cr_index_MEM=256

while [ "${dump_cr_index_MEM}" != "326" ]
do
        x=`printf '%x' ${dump_cr_index_MEM}`
        iwpriv $WLAN_STR mac ${debug_cr_base_MEM}=${x}
        iwpriv $WLAN_STR mac ${debug_cr_val_MEM}
        dump_cr_index_MEM=$((${dump_cr_index_MEM}+1))
done



