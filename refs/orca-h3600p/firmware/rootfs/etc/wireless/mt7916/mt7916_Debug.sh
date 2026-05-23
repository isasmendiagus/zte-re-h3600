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

iwpriv $WLAN_STR set Debug=3

iwpriv $WLAN_STR show driverinfo
for i in 1 2 3 4 5
do
    iwpriv $WLAN_STR stat
    iwpriv $WLAN_STR set ResetCounter=1
    sleep 1
done
for i in 1 2 3 4 5
do
    iwpriv $WLAN_STR show stat
    sleep 1
done
for i in 1 2 3 4 5
do
    iwpriv $WLAN_STR show stainfo
    sleep 1
done
for i in 1 2 3 4 5
do
    iwpriv $WLAN_STR show trinfo
done

iwpriv $WLAN_STR show sysinfo
iwpriv $WLAN_STR show devinfo
for i in 1 2 3 4 5
do
    iwpriv $WLAN_STR show stacountinfo
    sleep 1
done
for i in 1 2 3 4 5
do
    iwpriv $WLAN_STR show bainfo
    sleep 1
done

iwpriv $WLAN_STR e2p

iwpriv $WLAN_STR show sta_tr
for i in 1 2 3 4 5
do
    iwpriv $WLAN_STR show peerinfo=$2
    sleep 1
done
for i in 1 2 3 4 5
do
    iwpriv $WLAN_STR show mibinfo
done

for i in 1 2 3 4 5
do
    iwpriv $WLAN_STR show radiostat
    sleep 1
done
for i in 1 2 3 4 5
do
    iwpriv $WLAN_STR show bcninfo
done
iwpriv $WLAN_STR show wifi_sys
iwpriv $WLAN_STR show radio_info
for i in 1 2 3 4 5
do
    iwpriv $WLAN_STR show staoffline
done
for i in 1 2 3 4 5
do
    iwpriv $WLAN_STR show chanutil
done

for i in 1 2 3 4 5
do
    iwpriv $WLAN_STR show tpinfo=0-1-0
done
for i in 1 2 3 4 5
do
    iwpriv $WLAN_STR show tpinfo=0-2-0
done
for i in 1 2 3 4 5
do
    iwpriv $WLAN_STR show tpinfo=0-3-0
done
iwpriv $WLAN_STR show pseinfo
iwpriv $WLAN_STR show pleinfo
for i in 1 2 3 4 5
do
    iwpriv $WLAN_STR show chanstat
done

for i in 1 2 3 4 5
do
    iwpriv $WLAN_STR show swqinfo
done

for i in 1 2 3 4 5
do
    iwpriv $WLAN_STR show apcfginfo
done
for i in 1 2 3 4 5
do
    iwpriv $WLAN_STR show mbss=1
done
for i in 1 2 3 4 5
do
    iwpriv $WLAN_STR show MibBucket
done
for i in 1 2 3 4 5
do
    iwpriv $WLAN_STR show wtbl=0
done
for i in 1 2 3 4 5
do
    iwpriv $WLAN_STR show ser
done
for i in 1 2 3 4 5
do
    iwpriv $WLAN_STR show serinfo
done
for i in 1 2 3 4 5
do
    iwpriv $WLAN_STR show fw_dbg_info
done

for i in 1 2 3 4 5
do
    iwpriv $WLAN_STR mac 401980
done
for i in 1 2 3 4 5
do
    iwpriv $WLAN_STR mac 890d0100-890d0300
    sleep 1
done
for i in 1 2 3 4 5
do
    iwpriv $WLAN_STR mac 820E3150
done
for i in 1 2 3 4 5
do
    iwpriv $WLAN_STR mac 820F3150
done
for i in 1 2 3 4 5
do
    iwpriv $WLAN_STR mac 820E3000
done
for i in 1 2 3 4 5
do
    iwpriv $WLAN_STR mac 820F3000
done
for i in 1 2 3 4 5
do
    iwpriv $WLAN_STR mac 820E3160
done
for i in 1 2 3 4 5
do
    iwpriv $WLAN_STR mac 820F3160
done
for i in 1 2 3 4 5
do
    iwpriv $WLAN_STR mac 820E3164
done
for i in 1 2 3 4 5
do
    iwpriv $WLAN_STR mac 820F3164
done
for i in 1 2 3 4 5
do
    iwpriv $WLAN_STR mac 820e3260-820e3278
    sleep 1
done
for i in 1 2 3 4 5
do
    iwpriv $WLAN_STR mac 820f3260-820f3278
    sleep 1
done
for i in 1 2 3 4 5
do
    iwpriv $WLAN_STR mac 820e3170-820e317C
    sleep 1
done
for i in 1 2 3 4 5
do
    iwpriv $WLAN_STR mac 820f3170-820f317C
    sleep 1
done
for i in 1 2 3 4 5
do
    iwpriv $WLAN_STR mac 820c0100-820c0140
    sleep 1
done

for i in 1 2 3
do
    iwpriv $WLAN_STR mac 820EB0A8
done
for i in 1 2 3
do
    iwpriv $WLAN_STR mac 820FB0A8
done
for i in 1 2 3
do
    iwpriv $WLAN_STR mac 820EB0B8
done
for i in 1 2 3
do
    iwpriv $WLAN_STR mac 820FB0B8
done
for i in 1 2 3
do
    iwpriv $WLAN_STR mac 820EB330
done
for i in 1 2 3
do
    iwpriv $WLAN_STR mac 820FB330
done
for i in 1 2 3
do
    iwpriv $WLAN_STR mac 820EB368
done
for i in 1 2 3
do
    iwpriv $WLAN_STR mac 820FB368
done

iwpriv $WLAN_STR set Debug=0