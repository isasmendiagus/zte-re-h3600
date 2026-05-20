// module: mt7915.ko
// function: rt_ioctl_siwpmksa @ 0x6ca24
// size: 296 bytes
//

undefined4 rt_ioctl_siwpmksa(undefined4 param_1,undefined4 param_2,undefined4 *param_3)

{
  undefined4 uVar1;
  int iVar2;
  undefined4 uVar3;
  int *piVar4;
  int local_24;
  int local_20;
  int *local_1c;
  
  piVar4 = (int *)*param_3;
  uVar1 = RtmpOsGetNetDevPriv();
  iVar2 = RTMP_COM_IoctlHandle(uVar1,0,0x5011,0,0,0);
  if (iVar2 == 0) {
    if (piVar4 != (int *)0x0) {
      if (2 < DebugLevel) {
        printk("===> rt_ioctl_siwpmksa\n");
      }
      local_24 = *piVar4;
      if (local_24 == 3) {
        local_24 = 1;
      }
      else if (local_24 != 2) {
        if (local_24 == 1) {
          local_24 = 3;
        }
        else {
          local_24 = 0;
        }
      }
      local_20 = (int)piVar4 + 6;
      local_1c = piVar4 + 5;
      uVar3 = RtmpDevPrivFlagsGet(param_1);
      RTMP_STA_IoctlHandle(uVar1,0,0xa020,0,&local_24,0,uVar3);
      return 0;
    }
    uVar1 = 0xffffffea;
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

