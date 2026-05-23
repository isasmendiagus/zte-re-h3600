// module: mt7915.ko
// function: mt_wifi_close @ 0x24621c
// size: 128 bytes
//

undefined4 mt_wifi_close(undefined4 param_1)

{
  int iVar1;
  
  if (2 < DebugLevel) {
    printk("===> mt_wifi_close\n");
  }
  iVar1 = RtmpOsGetNetDevPriv(param_1);
  if (iVar1 != 0) {
    RTMPDrvClose(iVar1,param_1);
    mt_service_close(iVar1);
    mt_wlan_hook_call(7,iVar1,0);
    if (2 < DebugLevel) {
      printk("<=== mt_wifi_close\n");
    }
  }
  return 0;
}

