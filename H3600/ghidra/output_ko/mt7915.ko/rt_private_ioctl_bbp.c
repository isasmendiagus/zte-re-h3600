// module: mt7915.ko
// function: rt_private_ioctl_bbp @ 0x6cf1c
// size: 156 bytes
//

undefined4
rt_private_ioctl_bbp(undefined4 param_1,undefined4 param_2,undefined4 *param_3,undefined4 param_4)

{
  int iVar1;
  undefined4 uVar2;
  undefined4 uVar3;
  undefined1 auStack_30 [16];
  undefined4 local_20;
  undefined2 local_1c;
  
  uVar2 = RtmpOsGetNetDevPriv();
  __memzero(param_4,0x7ff);
  local_20 = *param_3;
  local_1c = *(undefined2 *)(param_3 + 1);
  uVar3 = RtmpDevPrivFlagsGet(param_1);
  RTMP_STA_IoctlHandle(uVar2,auStack_30,10,0,param_4,0x7ff,uVar3);
  iVar1 = DebugLevel;
  *(undefined2 *)(param_3 + 1) = local_1c;
  if (2 < iVar1) {
    printk("<==rt_private_ioctl_bbp\n\n");
  }
  return 0;
}

