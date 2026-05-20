// module: mt7915.ko
// function: RtmpIoctl_rt_ioctl_giwencode @ 0x62f98
// size: 540 bytes
//

undefined4 RtmpIoctl_rt_ioctl_giwencode(int *param_1,undefined4 *param_2)

{
  byte bVar1;
  uint __n;
  ushort uVar2;
  int iVar3;
  int iVar4;
  uint uVar5;
  
  iVar4 = param_2[2];
  iVar3 = *(int *)(*param_1 + 0x3c);
  if (2 < DebugLevel) {
    printk("===>rt_ioctl_giwencode %d\n",iVar4);
  }
  if ((param_1[iVar3 * 0x84dec + 0xdb733] & 1U) != 0) {
    *(undefined2 *)(param_2 + 1) = 0;
    *(undefined2 *)((int)param_2 + 0x16) = 1;
    return 0;
  }
  uVar5 = iVar4 - 1;
  if (uVar5 < 4) {
    param_2[2] = iVar4;
    bVar1 = (&DAT_0036dbd8)[(int)param_1 + uVar5 * 0x51 + iVar3 * 0x2137b0];
    __n = (uint)*(ushort *)(param_2 + 1);
    if ((uint)bVar1 < (uint)*(ushort *)(param_2 + 1)) {
      *(ushort *)(param_2 + 1) = (ushort)bVar1;
      __n = (uint)bVar1;
    }
    memcpy((void *)*param_2,&DAT_0036db88 + (int)param_1 + uVar5 * 0x51 + iVar3 * 0x2137b0,__n);
    if ((param_1[iVar3 * 0x84dec + 0xdb6e1] & 2U) == 0) {
      uVar2 = *(ushort *)((int)param_2 + 0x16) | 8;
    }
    else {
      uVar2 = *(ushort *)((int)param_2 + 0x16) | 4;
    }
    *(ushort *)((int)param_2 + 0x16) = uVar2;
  }
  else if (iVar4 == 0) {
    if ((param_1[iVar3 * 0x84dec + 0xdb6e1] & 2U) == 0) {
      uVar2 = *(ushort *)((int)param_2 + 0x16) | 8;
    }
    else {
      uVar2 = *(ushort *)((int)param_2 + 0x16) | 4;
    }
    *(ushort *)((int)param_2 + 0x16) = uVar2;
    bVar1 = (&DAT_0036dbd8)
            [(int)param_1 +
             (uint)*(byte *)(param_1 + iVar3 * 0x84dec + 0xdb734) * 0x51 + iVar3 * 0x2137b0];
    *(ushort *)(param_2 + 1) = (ushort)bVar1;
    memcpy((void *)*param_2,
           &DAT_0036db88 +
           (int)param_1 +
           (uint)*(byte *)(param_1 + iVar3 * 0x84dec + 0xdb734) * 0x51 + iVar3 * 0x2137b0,
           (uint)bVar1);
    if ((param_1[iVar3 * 0x84dec + 0xdb6e1] & 2U) == 0) {
      uVar2 = *(ushort *)((int)param_2 + 0x16) | 8;
    }
    else {
      uVar2 = *(ushort *)((int)param_2 + 0x16) | 4;
    }
    *(ushort *)((int)param_2 + 0x16) = uVar2;
    bVar1 = *(byte *)(param_1 + iVar3 * 0x84dec + 0xdb734);
    *(ushort *)((int)param_2 + 0x16) = uVar2 | 2;
    param_2[2] = bVar1 + 1;
    return 0;
  }
  return 0;
}

