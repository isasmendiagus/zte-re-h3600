// module: mt7915.ko
// function: rt_ioctl_giwfrag @ 0x6ede0
// size: 236 bytes
//

undefined4 rt_ioctl_giwfrag(undefined4 param_1,undefined4 param_2,uint *param_3)

{
  int iVar1;
  int iVar2;
  undefined4 uVar3;
  ushort local_1a [3];
  
  iVar1 = RtmpOsGetNetDevPriv();
  if (iVar1 != 0) {
    iVar2 = RTMP_COM_IoctlHandle(iVar1,0,0x5011,0,0,0);
    if (iVar2 == 0) {
      iVar2 = DetermineCallerInterface(param_1,iVar1);
      if (iVar2 != 0) {
        return 0xfffffff2;
      }
      uVar3 = RtmpDevPrivFlagsGet(param_1);
      RTMP_STA_IoctlHandle(iVar1,0,0xa016,0,local_1a,0,uVar3);
      *(undefined1 *)(param_3 + 1) = 1;
      *param_3 = (uint)local_1a[0];
      *(bool *)((int)param_3 + 5) = local_1a[0] == 0x92a;
      return 0;
    }
    if (2 < DebugLevel) {
      printk("INFO::Network is down!\n");
      return 0xffffff9c;
    }
  }
  return 0xffffff9c;
}

