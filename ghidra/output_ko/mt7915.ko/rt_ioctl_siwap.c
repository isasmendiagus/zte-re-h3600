// module: mt7915.ko
// function: rt_ioctl_siwap @ 0x6db84
// size: 256 bytes
//

undefined4 rt_ioctl_siwap(undefined4 param_1,undefined4 param_2,int param_3)

{
  undefined4 uVar1;
  int iVar2;
  undefined4 uVar3;
  
  uVar1 = RtmpOsGetNetDevPriv();
  iVar2 = RTMP_COM_IoctlHandle(uVar1,0,0x5011,0,0,0);
  if (iVar2 == 0) {
    iVar2 = DetermineCallerInterface(param_1,uVar1);
    if (iVar2 == 0) {
      uVar3 = RtmpDevPrivFlagsGet(param_1);
      RTMP_STA_IoctlHandle(uVar1,0,0xa00b,0,param_3 + 2,0,uVar3);
      uVar1 = 0;
      if (2 < DebugLevel) {
        printk("IOCTL::SIOCSIWAP %02x:%02x:%02x:%02x:%02x:%02x\n",*(undefined1 *)(param_3 + 2),
               *(undefined1 *)(param_3 + 3),*(undefined1 *)(param_3 + 4),
               *(undefined1 *)(param_3 + 5),*(undefined1 *)(param_3 + 6),
               *(undefined1 *)(param_3 + 7));
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
    uVar1 = 0xffffff9c;
    printk("INFO::Network is down!\n");
  }
  return uVar1;
}

