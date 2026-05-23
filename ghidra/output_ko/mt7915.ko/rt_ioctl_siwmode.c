// module: mt7915.ko
// function: rt_ioctl_siwmode @ 0x6d574
// size: 276 bytes
//

undefined4 rt_ioctl_siwmode(undefined4 param_1,undefined4 param_2,int *param_3)

{
  undefined4 uVar1;
  int iVar2;
  int iVar3;
  undefined4 uVar4;
  
  uVar1 = RtmpOsGetNetDevPriv();
  iVar2 = RTMP_COM_IoctlHandle(uVar1,0,0x5011,0,0,0);
  if (iVar2 == 0) {
    iVar2 = *param_3;
    if ((iVar2 != 1) && (iVar2 != 2)) {
      if (iVar2 != 6) {
        if (2 < DebugLevel) {
          printk("===>rt_ioctl_siwmode::SIOCSIWMODE (unknown %d)\n");
          return 0xffffffea;
        }
        return 0xffffffea;
      }
      iVar2 = 3;
    }
    iVar3 = DetermineCallerInterface(param_1,uVar1);
    if (iVar3 == 0) {
      uVar4 = RtmpDevPrivFlagsGet(param_1);
      RTMP_STA_IoctlHandle(uVar1,0,0xa009,0,0,iVar2,uVar4);
      return 0;
    }
    uVar1 = 0xfffffff2;
  }
  else if (DebugLevel < 3) {
    uVar1 = 0xffffff9c;
  }
  else {
    uVar1 = 0xffffff9c;
    printk("INFO::Network is down!\n");
  }
  return uVar1;
}

