// module: mt7915.ko
// function: rt_ioctl_siwmlme @ 0x6c1d8
// size: 300 bytes
//

undefined4 rt_ioctl_siwmlme(undefined4 param_1,undefined4 param_2,undefined4 *param_3)

{
  short sVar1;
  undefined4 uVar2;
  int iVar3;
  undefined4 uVar4;
  short *psVar5;
  undefined4 uVar6;
  
  psVar5 = (short *)*param_3;
  uVar2 = RtmpOsGetNetDevPriv();
  if (2 < DebugLevel) {
    printk("====> %s\n","rt_ioctl_siwmlme");
  }
  iVar3 = RTMP_COM_IoctlHandle(uVar2,0,0x5011,0,0,0);
  if (iVar3 == 0) {
    if (psVar5 != (short *)0x0) {
      if (*psVar5 == 0) {
        uVar6 = 1;
      }
      else if (*psVar5 == 1) {
        uVar6 = 2;
      }
      else {
        uVar6 = 0;
        if (2 < DebugLevel) {
          printk("====> %s - Unknow Command\n","rt_ioctl_siwmlme");
        }
      }
      sVar1 = psVar5[1];
      uVar4 = RtmpDevPrivFlagsGet(param_1);
      RTMP_STA_IoctlHandle(uVar2,0,0xa019,uVar6,0,sVar1,uVar4);
      return 0;
    }
    uVar2 = 0xffffffea;
  }
  else if (DebugLevel < 3) {
    uVar2 = 0xffffff9c;
  }
  else {
    uVar2 = 0xffffff9c;
    printk("INFO::Network is down!\n");
  }
  return uVar2;
}

