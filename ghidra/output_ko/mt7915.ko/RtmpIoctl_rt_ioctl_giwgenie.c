// module: mt7915.ko
// function: RtmpIoctl_rt_ioctl_giwgenie @ 0x644cc
// size: 192 bytes
//

undefined4 RtmpIoctl_rt_ioctl_giwgenie(int *param_1,uint *param_2)

{
  uint uVar1;
  undefined1 uVar2;
  int iVar3;
  
  iVar3 = *(int *)(*param_1 + 0x3c);
  if ((*(byte *)(param_1 + iVar3 * 0x84dec + 0x1602e4) != 0) &&
     ((param_1[iVar3 * 0x84dec + 0xdb6e1] & 7U) == 0)) {
    uVar1 = *(byte *)(param_1 + iVar3 * 0x84dec + 0x1602e4) + 2;
    if (*param_2 < uVar1) {
      return 1;
    }
    *param_2 = uVar1;
    if ((param_1[iVar3 * 0x84dec + 0xdb6e1] & 0xc0U) == 0) {
      uVar2 = 0xdd;
    }
    else {
      uVar2 = 0x30;
    }
    *(undefined1 *)param_2[1] = uVar2;
    *(char *)(param_2[1] + 1) = (char)param_1[iVar3 * 0x84dec + 0x1602e4];
    memcpy((void *)(param_2[1] + 2),(void *)((int)param_1 + iVar3 * 0x2137b0 + 0x580b91),
           (uint)*(byte *)(param_1 + iVar3 * 0x84dec + 0x1602e4));
    return 0;
  }
  *param_2 = 0;
  return 0;
}

