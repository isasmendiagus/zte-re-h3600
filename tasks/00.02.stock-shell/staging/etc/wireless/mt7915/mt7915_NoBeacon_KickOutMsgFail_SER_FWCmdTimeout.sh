#!/bin/sh

WLAN_STR=wlan5g0

iwpriv $WLAN_STR set Debug=2

iwpriv $WLAN_STR show driverinfo
iwpriv $WLAN_STR show serinfo
iwpriv $WLAN_STR show serinfo2
iwpriv $WLAN_STR show fw_dbg_info

for i in 1 2 3 4 5
do
    iwpriv $WLAN_STR show bcninfo
done

for i in 1 2 3 4 5
do
    iwpriv $WLAN_STR show mibinfo
done

iwpriv $WLAN_STR set Debug=0
