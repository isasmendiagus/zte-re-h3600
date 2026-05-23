// module: mt7915.ko
// function: rt_ioctl_giwgenie @ 0x6c960
// size: 196 bytes
//

undefined4 rt_ioctl_giwgenie(undefined4 param_1,undefined4 param_2,int param_3,undefined4 param_4)

{
  undefined4 uVar1;
  int iVar2;
  undefined4 uVar3;
  uint local_20;
  undefined4 local_1c;
  
  uVar1 = RtmpOsGetNetDevPriv();
  iVar2 = RTMP_COM_IoctlHandle(uVar1,0,0x5011,0,0,0);
  if (iVar2 != 0) {
    if (2 < DebugLevel) {
      printk("INFO::Network is down!\n");
    }
    return 0xffffff9c;
  }
  local_20 = (uint)*(ushort *)(param_3 + 4);
  local_1c = param_4;
  uVar3 = RtmpDevPrivFlagsGet(param_1);
  iVar2 = RTMP_STA_IoctlHandle(uVar1,0,0xa01f,0,&local_20,0,uVar3);
  if (iVar2 == 0) {
    *(short *)(param_3 + 4) = (short)local_20;
    uVar1 = 0;
  }
  else {
    uVar1 = 0xfffffff9;
  }
  return uVar1;
}

