// module: mt7915.ko
// function: rt_ioctl_siwsens @ 0x6f368
// size: 100 bytes
//

undefined4 rt_ioctl_siwsens(void)

{
  undefined4 uVar1;
  int iVar2;
  
  uVar1 = RtmpOsGetNetDevPriv();
  iVar2 = RTMP_COM_IoctlHandle(uVar1,0,0x5011,0,0,0);
  uVar1 = 0;
  if (iVar2 != 0) {
    if (DebugLevel < 3) {
      uVar1 = 0xffffff9c;
    }
    else {
      printk("INFO::Network is down!\n");
      uVar1 = 0xffffff9c;
    }
  }
  return uVar1;
}

