// module: mt7915.ko
// function: rt_ioctl_siwscan @ 0x6dfec
// size: 304 bytes
//

int rt_ioctl_siwscan(undefined4 param_1)

{
  undefined4 uVar1;
  int iVar2;
  undefined4 uVar3;
  undefined1 auStack_24 [16];
  int local_14;
  
  uVar1 = RtmpOsGetNetDevPriv();
  iVar2 = RTMP_COM_IoctlHandle(uVar1,0,0x5011,0,0,0);
  if (iVar2 != 0) {
    if (2 < DebugLevel) {
      printk("INFO::Network is down!\n");
      return -100;
    }
    return -100;
  }
  __memzero(auStack_24);
  iVar2 = DetermineCallerInterface(param_1,uVar1);
  if (iVar2 == 0) {
    uVar3 = RtmpDevPrivFlagsGet(param_1);
    RTMP_STA_IoctlHandle(uVar1,0,0xa00d,0,auStack_24,0,uVar3);
    if (local_14 == 30000) {
      return -0x16;
    }
    if (local_14 == 0x7531) {
      return -0x5f;
    }
    if (local_14 != 0x7532) {
      if (local_14 == 0x7534) {
        return -7;
      }
      if (local_14 == 0x7535) {
        return -0xc;
      }
      if (local_14 == 0x7536) {
        return -0xb;
      }
      if (local_14 != 0x7537) {
        return local_14;
      }
      return -0x6b;
    }
  }
  return -0xe;
}

