// module: mt7915.ko
// function: rt_ioctl_giwfreq @ 0x6d474
// size: 256 bytes
//

undefined4 rt_ioctl_giwfreq(undefined4 param_1,undefined4 param_2,int *param_3)

{
  int iVar1;
  int iVar2;
  undefined4 uVar3;
  undefined4 uVar4;
  int local_1c;
  
  local_1c = 0x24cde0;
  iVar1 = RtmpOsGetNetDevPriv();
  if (iVar1 != 0) {
    iVar2 = RTMP_COM_IoctlHandle(iVar1,0,0x5011,0,0,0);
    if (iVar2 == 0) {
      iVar2 = DetermineCallerInterface(param_1,iVar1);
      if (iVar2 != 0) {
        return 0xfffffff2;
      }
      uVar3 = RtmpDevPrivFlagsGet(param_1);
      uVar4 = RtmpDevPrivFlagsGet(param_1);
      RTMP_STA_IoctlHandle(iVar1,0,0xa008,0,&local_1c,uVar3,uVar4);
      *(undefined1 *)((int)param_3 + 6) = 0;
      *(undefined2 *)(param_3 + 1) = 1;
      *param_3 = local_1c * 100;
      return 0;
    }
    if (2 < DebugLevel) {
      printk("INFO::Network is down!\n");
      return 0xffffff9c;
    }
  }
  return 0xffffff9c;
}

