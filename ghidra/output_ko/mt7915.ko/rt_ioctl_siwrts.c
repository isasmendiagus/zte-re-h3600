// module: mt7915.ko
// function: rt_ioctl_siwrts @ 0x6eb30
// size: 252 bytes
//

undefined4 rt_ioctl_siwrts(undefined4 param_1,undefined4 param_2,uint *param_3)

{
  undefined4 uVar1;
  int iVar2;
  undefined4 uVar3;
  uint uVar4;
  
  uVar1 = RtmpOsGetNetDevPriv();
  iVar2 = RTMP_COM_IoctlHandle(uVar1,0,0x5011,0,0,0);
  if (iVar2 == 0) {
    if (*(char *)((int)param_3 + 5) == '\0') {
      uVar4 = *param_3;
      if (0xfffff < uVar4) {
        return 0xffffffea;
      }
      if (uVar4 == 0) {
        uVar4 = 0xfffff;
      }
    }
    else {
      uVar4 = 0xfffff;
    }
    iVar2 = DetermineCallerInterface(param_1,uVar1);
    if (iVar2 == 0) {
      uVar3 = RtmpDevPrivFlagsGet(param_1);
      RTMP_STA_IoctlHandle(uVar1,0,0xa013,0,0,uVar4,uVar3);
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

