// module: mt7915.ko
// function: rt_ioctl_siwrate @ 0x6cb4c
// size: 220 bytes
//

undefined4 rt_ioctl_siwrate(undefined4 param_1,undefined4 param_2,undefined4 *param_3)

{
  byte bVar1;
  undefined4 uVar2;
  int iVar3;
  undefined4 uVar4;
  undefined4 local_20;
  uint local_1c;
  
  uVar4 = *param_3;
  bVar1 = *(byte *)(param_3 + 1);
  uVar2 = RtmpOsGetNetDevPriv();
  iVar3 = RTMP_COM_IoctlHandle(uVar2,0,0x5011,0,0,0);
  if (iVar3 != 0) {
    if (2 < DebugLevel) {
      printk("rt_ioctl_siwrate::Network is down!\n");
    }
    return 0xffffff9c;
  }
  if (2 < DebugLevel) {
    printk("rt_ioctl_siwrate::(rate = %d, fixed = %d)\n",uVar4,(uint)bVar1);
  }
  local_20 = uVar4;
  local_1c = (uint)bVar1;
  uVar4 = RtmpDevPrivFlagsGet(param_1);
  iVar3 = RTMP_STA_IoctlHandle(uVar2,0,0xa021,0,&local_20,0,uVar4);
  uVar2 = 0;
  if (iVar3 != 0) {
    uVar2 = 0xffffffa1;
  }
  return uVar2;
}

