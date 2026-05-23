// module: mt7915.ko
// function: rt_ioctl_giwnickn @ 0x6ea4c
// size: 228 bytes
//

undefined4 rt_ioctl_giwnickn(undefined4 param_1,undefined4 param_2,int param_3,undefined4 param_4)

{
  int iVar1;
  int iVar2;
  undefined4 uVar3;
  uint local_20;
  undefined4 local_1c;
  
  iVar1 = RtmpOsGetNetDevPriv();
  if (iVar1 == 0) {
    uVar3 = 0xffffff9c;
  }
  else {
    iVar2 = RTMP_COM_IoctlHandle(iVar1,0,0x5011,0,0,0);
    if (iVar2 == 0) {
      local_20 = (uint)*(ushort *)(param_3 + 4);
      local_1c = param_4;
      iVar2 = DetermineCallerInterface(param_1,iVar1);
      if (iVar2 == 0) {
        uVar3 = RtmpDevPrivFlagsGet(param_1);
        RTMP_STA_IoctlHandle(iVar1,0,0xa012,0,&local_20,0,uVar3);
        *(short *)(param_3 + 4) = (short)local_20;
        uVar3 = 0;
      }
      else {
        uVar3 = 0xfffffff2;
      }
    }
    else {
      if (2 < DebugLevel) {
        printk("INFO::Network is down!\n");
      }
      uVar3 = 0xffffff9c;
      *(undefined2 *)(param_3 + 4) = 0;
    }
  }
  return uVar3;
}

