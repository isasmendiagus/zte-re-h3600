// module: mt7915.ko
// function: rt_ioctl_showparam @ 0x6f194
// size: 264 bytes
//

undefined4
rt_ioctl_showparam(undefined4 param_1,undefined4 param_2,undefined4 param_3,char *param_4)

{
  int iVar1;
  undefined1 *puVar2;
  int iVar3;
  undefined4 uVar4;
  undefined1 *puVar5;
  char *local_20;
  undefined1 *local_1c;
  
  iVar1 = RtmpOsGetNetDevPriv();
  if (iVar1 != 0) {
    if (*param_4 == '\0') {
      return 0xffffffea;
    }
    puVar2 = (undefined1 *)rtstrchr(param_4,0x3d);
    if (puVar2 == (undefined1 *)0x0) {
      puVar5 = (undefined1 *)0x0;
    }
    else {
      puVar5 = puVar2 + 1;
      *puVar2 = 0;
    }
    iVar3 = RTMP_COM_IoctlHandle(iVar1,0,0x5011,0,param_4,0);
    if (iVar3 == 0) {
      local_20 = param_4;
      local_1c = puVar5;
      iVar3 = DetermineCallerInterface(param_1,iVar1);
      if (iVar3 != 0) {
        return 0xfffffff2;
      }
      uVar4 = RtmpDevPrivFlagsGet(param_1);
      RTMP_STA_IoctlHandle(iVar1,0,0xa001,0,&local_20,0,uVar4);
      return 0;
    }
    if (2 < DebugLevel) {
      printk("INFO::Network is down!\n");
      return 0xffffff9c;
    }
  }
  return 0xffffff9c;
}

