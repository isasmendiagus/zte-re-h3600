// module: mt7915.ko
// function: mt_wifi_open @ 0x2462d8
// size: 380 bytes
//

undefined4 mt_wifi_open(int param_1)

{
  int iVar1;
  undefined4 uVar2;
  int iVar3;
  int local_14;
  
  iVar1 = RtmpOsGetNetDevPriv();
  if (iVar1 != 0) {
    RTMP_COM_IoctlHandle(iVar1,0,0x5006,0,0,0);
    RTMP_COM_IoctlHandle(iVar1,0,0x5002,0,&local_14,0);
    uVar2 = RtmpDevPrivFlagsGet(param_1);
    iVar3 = RTMP_COM_IoctlHandle(iVar1,0,0x5040,0,0,uVar2);
    if (iVar3 == 0) {
      if (local_14 == 1) {
        *(undefined1 **)(param_1 + 0x124) = rt28xx_ap_iw_handler_def;
      }
      else if (local_14 == 0) {
        *(undefined1 **)(param_1 + 0x124) = rt28xx_iw_handler_def;
      }
    }
    iVar3 = load_dev_l1profile(iVar1);
    if (iVar3 == 0) {
      if (0 < DebugLevel) {
        printk("load l1profile succeed!\n");
      }
    }
    else if (0 < DebugLevel) {
      printk("load l1profile failed!\n");
    }
    mt_wlan_hook_call(6,iVar1,0);
    mt_service_open(iVar1);
    iVar3 = mt_wifi_init(iVar1,mac,hostname);
    if (iVar3 != 0) {
      if (*(char *)(iVar1 + 0x286285) == '\x01') {
        RT28xx_MBSS_Init(iVar1,param_1);
      }
      RT28xx_MSTA_Init(iVar1,param_1);
      mt_service_init(iVar1);
      RTMPDrvOpen(iVar1);
      return 0;
    }
  }
  return 0xffffffff;
}

