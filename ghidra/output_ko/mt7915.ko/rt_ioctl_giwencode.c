// module: mt7915.ko
// function: rt_ioctl_giwencode @ 0x6f070
// size: 292 bytes
//

undefined4 rt_ioctl_giwencode(undefined4 param_1,undefined4 param_2,int param_3,undefined4 param_4)

{
  int iVar1;
  int iVar2;
  undefined4 uVar3;
  undefined4 local_34;
  undefined2 local_30;
  uint local_2c;
  ushort local_1e;
  
  iVar1 = RtmpOsGetNetDevPriv();
  if (iVar1 != 0) {
    iVar2 = RTMP_COM_IoctlHandle(iVar1,0,0x5011,0,0,0);
    if (iVar2 == 0) {
      local_2c = (uint)*(byte *)(param_3 + 6);
      local_30 = *(undefined2 *)(param_3 + 4);
      local_34 = param_4;
      iVar2 = DetermineCallerInterface(param_1,iVar1);
      if (iVar2 != 0) {
        return 0xfffffff2;
      }
      uVar3 = RtmpDevPrivFlagsGet(param_1);
      RTMP_STA_IoctlHandle(iVar1,0,0xa018,0,&local_34,0,uVar3);
      *(short *)(param_3 + 6) = (short)local_2c;
      if ((local_1e & 1) != 0) {
        *(undefined2 *)(param_3 + 6) = 1;
      }
      *(undefined2 *)(param_3 + 4) = local_30;
      if ((local_1e & 4) != 0) {
        *(ushort *)(param_3 + 6) = *(ushort *)(param_3 + 6) | 0x4000;
      }
      if ((local_1e & 8) == 0) {
        return 0;
      }
      *(ushort *)(param_3 + 6) = *(ushort *)(param_3 + 6) | 0x2000;
      return 0;
    }
    if (2 < DebugLevel) {
      printk("INFO::Network is down!\n");
      return 0xffffff9c;
    }
  }
  return 0xffffff9c;
}

