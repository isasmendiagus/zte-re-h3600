// module: mt7915.ko
// function: rt_ioctl_giwrts @ 0x6ec2c
// size: 220 bytes
//

undefined4 rt_ioctl_giwrts(undefined4 param_1,undefined4 param_2,uint *param_3)

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
      RTMP_STA_IoctlHandle(iVar1,0,0xa014,0,local_1a,0,uVar3);
      *(undefined1 *)((int)param_3 + 5) = 0;
      *(undefined1 *)(param_3 + 1) = 1;
      *param_3 = (uint)local_1a[0];
      return 0;
    }
    if (2 < DebugLevel) {
      printk("INFO::Network is down!\n");
      return 0xffffff9c;
    }
  }
  return 0xffffff9c;
}

