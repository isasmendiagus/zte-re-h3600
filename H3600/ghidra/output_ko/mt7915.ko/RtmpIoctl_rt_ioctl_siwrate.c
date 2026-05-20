// module: mt7915.ko
// function: RtmpIoctl_rt_ioctl_siwrate @ 0x64944
// size: 268 bytes
//

undefined4 RtmpIoctl_rt_ioctl_siwrate(int param_1,int *param_2,undefined4 param_3,int param_4)

{
  int iVar1;
  byte bVar2;
  ushort uVar3;
  
  iVar1 = *param_2;
  if (iVar1 == -1) {
    *(undefined1 *)(param_4 + 0x8b0) = 1;
    bVar2 = *(byte *)(param_4 + 0x8ae) & 0x80 | 0x21;
    *(byte *)(param_4 + 0x8ae) = bVar2;
    if (((*(ushort *)(param_4 + 0x18) & 0x18) == 0) ||
       (bVar2 = *(byte *)(param_1 + 0xa329d), bVar2 < 0x40)) {
      RTMPSetDesiredRates(param_1,param_4,0xffffffff,bVar2,param_4);
    }
    SetCommonHtVht(param_1,param_4);
    return 0;
  }
  if (param_2[1] != 0) {
    uVar3 = *(ushort *)(param_4 + 0x18);
    *(undefined1 *)(param_4 + 0x8b0) = 0;
    if (((uVar3 & 0x18) == 0) || (uVar3 = (ushort)*(byte *)(param_1 + 0xa329d), uVar3 < 0x40)) {
      RTMPSetDesiredRates(param_1,param_4,iVar1,uVar3,param_4);
    }
    else {
      *(byte *)(param_4 + 0x8ae) = *(byte *)(param_4 + 0x8ae) & 0x80 | 0x21;
      SetCommonHtVht(param_1,param_4);
    }
    if (DebugLevel < 3) {
      return 0;
    }
    printk("rt_ioctl_siwrate::(HtMcs=%d)\n",*(byte *)(param_4 + 0x8ae) & 0x7f);
    return 0;
  }
  return 1;
}

