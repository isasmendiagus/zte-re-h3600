// module: mt7915.ko
// function: rt_ioctl_siwfreq @ 0x6d38c
// size: 232 bytes
//

undefined4 rt_ioctl_siwfreq(undefined4 param_1,undefined4 param_2,undefined4 *param_3)

{
  undefined4 uVar1;
  int iVar2;
  undefined4 uVar3;
  undefined4 local_18;
  short local_14;
  
  uVar1 = RtmpOsGetNetDevPriv();
  iVar2 = RTMP_COM_IoctlHandle(uVar1,0,0x5011,0,0,0);
  if (iVar2 == 0) {
    local_14 = *(short *)(param_3 + 1);
    if (1 < local_14) {
      return 0xffffffea;
    }
    local_18 = *param_3;
    iVar2 = DetermineCallerInterface(param_1,uVar1);
    if (iVar2 == 0) {
      uVar3 = RtmpDevPrivFlagsGet(param_1);
      iVar2 = RTMP_STA_IoctlHandle(uVar1,0,0xa007,0,&local_18,0,uVar3);
      uVar1 = 0;
      if (iVar2 != 0) {
        return 0xffffffea;
      }
    }
    else {
      uVar1 = 0xfffffff2;
    }
  }
  else if (DebugLevel < 3) {
    uVar1 = 0xffffff9c;
  }
  else {
    printk("INFO::Network is down!\n");
    uVar1 = 0xffffff9c;
  }
  return uVar1;
}

