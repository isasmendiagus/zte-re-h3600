#!/bin/sh
echo "fill in your usb disk path, like /mnt/usb1_1/ "
echo "type in usb path :"
read fwlogpath

echo "NOTICE:type in  0 for 2.4gfwlog, 1 for 5g fwlog, c for stop "
echo " only 1 band can run at one time, please check the size of your usb disk in $fwlogpath"
echo "type in : "
read COMMAND_STR

if [[ "$COMMAND_STR" == "0" ]];then
echo iwpriv wlan0 set fwlogdir=$fwlogpath
iwpriv wlan0 set fwlogdir=$fwlogpath
iwpriv wlan0 set fw_dbg=1:62
iwpriv wlan0 set fw_dbg=1:63
iwpriv wlan0 set fw_dbg=1:64
iwpriv wlan0 set fw_dbg=1:65
iwpriv wlan0 set fw_dbg=1:66
iwpriv wlan0 set fw_dbg=1:68
iwpriv wlan5g0 mac 820E70F0=0FF0000
iwpriv wlan0 mac 820E70F0=1FF0000
iwpriv wlan0 mac 820E70F4=5780070
iwpriv wlan0 mac 820E4200=1
iwpriv wlan0 mac 820E5618=1
iwpriv wlan0 set fwlog=0:8
echo "-----------begin catch fwlog-------------"
fi
if [[ "$COMMAND_STR" == "1" ]];then
echo iwpriv wlan5g0 set fwlogdir=$fwlogpath
iwpriv wlan5g0 set fwlogdir=$fwlogpath
iwpriv wlan5g0 set fw_dbg=1:62
iwpriv wlan5g0 set fw_dbg=1:63
iwpriv wlan5g0 set fw_dbg=1:64
iwpriv wlan5g0 set fw_dbg=1:65
iwpriv wlan5g0 set fw_dbg=1:66
iwpriv wlan5g0 set fw_dbg=1:68
iwpriv wlan0 mac 820E70F0=0FF0000
iwpriv wlan5g0 mac 820E70F0=1FF0000
iwpriv wlan5g0 mac 820E70F4=5780070
iwpriv wlan5g0 mac 820E4200=1
iwpriv wlan5g0 mac 820E5618=1
iwpriv wlan5g0 set fwlog=0:8
echo "-----------begin catch fwlog-------------"
fi
if [[ "$COMMAND_STR" == "c" ]];then
iwpriv wlan0 set fw_dbg=0:62
iwpriv wlan0 set fw_dbg=0:63
iwpriv wlan0 set fw_dbg=0:64
iwpriv wlan0 set fw_dbg=0:65
iwpriv wlan0 set fw_dbg=0:66
iwpriv wlan0 set fw_dbg=0:68
iwpriv wlan0 mac 820E70F0=0FF0000
iwpriv wlan0 set fwlog=0:0

iwpriv wlan5g0 set fw_dbg=0:62
iwpriv wlan5g0 set fw_dbg=0:63
iwpriv wlan5g0 set fw_dbg=0:64
iwpriv wlan5g0 set fw_dbg=0:65
iwpriv wlan5g0 set fw_dbg=0:66
iwpriv wlan5g0 set fw_dbg=0:68
iwpriv wlan5g0 mac 820E70F0=0FF0000
iwpriv wlan5g0 set fwlog=0:0
echo "===========stop fwlog===================="
fi
