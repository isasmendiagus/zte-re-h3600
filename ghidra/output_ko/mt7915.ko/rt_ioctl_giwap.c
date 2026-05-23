// module: mt7915.ko
// function: rt_ioctl_giwap @ 0x6dc84
// size: 240 bytes
//

undefined4 rt_ioctl_giwap(undefined4 param_1,undefined4 param_2,undefined2 *param_3)

{
  int iVar1;
  int iVar2;
  undefined4 uVar3;
  
  iVar1 = RtmpOsGetNetDevPriv();
  if (iVar1 != 0) {
    iVar2 = RTMP_COM_IoctlHandle(iVar1,0,0x5011,0,0,0);
    if (iVar2 == 0) {
      iVar2 = DetermineCallerInterface(param_1,iVar1);
      if (iVar2 != 0) {
        return 0xfffffff2;
      }
      uVar3 = RtmpDevPrivFlagsGet(param_1);
      iVar1 = RTMP_STA_IoctlHandle(iVar1,0,0xa00c,0,param_3 + 1,0,uVar3);
      if (iVar1 != 0) {
        if (2 < DebugLevel) {
          printk("IOCTL::SIOCGIWAP(=EMPTY)\n");
          return 0xffffff95;
        }
        return 0xffffff95;
      }
      *param_3 = 1;
      return 0;
    }
    if (2 < DebugLevel) {
      printk("INFO::Network is down!\n");
    }
  }
  return 0xffffff9c;
}

