#!/bin/sh

if [[ "$1" == "--help" ]];
then
   echo "Please type in:$0 'wlanx' 'mac'."
   echo "'wlanx' is the wlan interface, 'wlanx' default is wlan5g0."
   echo "'mac' is sta mac, %02x%02x%02x%02x%02x%02x."
   exit 1
fi

if [[ "$1" != "wlan"* ]];
then
    WLAN_STR=wlan5g0
else
    WLAN_STR=$1
fi

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

iwpriv $WLAN_STR set Debug=0