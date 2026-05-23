// module: mt7915.ko
// function: RtmpIoctl_rt_ioctl_giwencodeext @ 0x642cc
// size: 504 bytes
//

undefined4 RtmpIoctl_rt_ioctl_giwencodeext(int *param_1,int *param_2)

{
  uint uVar1;
  uint uVar2;
  int iVar3;
  int iVar4;
  
  iVar3 = *(int *)(*param_1 + 0x3c);
  if (param_2[2] == 0) {
    uVar1 = (uint)*(byte *)(param_1 + iVar3 * 0x84dec + 0xdb734);
  }
  else {
    uVar1 = param_2[2] - 1;
    if (3 < uVar1) goto LAB_00064414;
    if (((param_1[iVar3 * 0x84dec + 0xdb733] & 0x30U) != 0) &&
       (*(byte *)(param_1 + iVar3 * 0x84dec + 0xdb734) != uVar1)) {
      param_2[6] = 0;
      *(undefined2 *)(param_2 + 1) = 0;
      return 1;
    }
  }
  param_2[2] = uVar1 + 1;
  *(undefined2 *)(param_2 + 1) = 0;
  iVar4 = iVar3 * 0x2137b0;
  uVar2 = param_1[iVar3 * 0x84dec + 0xdb733];
  if ((uVar2 & 1) != 0) {
    param_2[4] = 1;
    *(ushort *)((int)param_2 + 0x16) = *(ushort *)((int)param_2 + 0x16) | 1;
    return 0;
  }
  if ((uVar2 & 0xe) == 0) {
    if ((uVar2 & 0x10) == 0) {
      if ((uVar2 & 0x20) == 0) {
LAB_00064414:
        param_2[6] = 30000;
        return 1;
      }
      param_2[4] = 4;
      if (0x1f < param_2[3]) {
        *(undefined2 *)(param_2 + 1) = 0x20;
        *param_2 = (int)param_1 + iVar4 + 0x36dd12;
        return 0;
      }
    }
    else {
      param_2[4] = 3;
      if (0x1f < param_2[3]) {
        *(undefined2 *)(param_2 + 1) = 0x20;
        *param_2 = (int)param_1 + iVar4 + 0x36dd12;
        return 0;
      }
    }
  }
  else {
    param_2[4] = 2;
    iVar4 = uVar1 * 0x51 + iVar4;
    if ((int)(uint)(byte)(&DAT_0036dbd8)[(int)param_1 + iVar4] <= param_2[3]) {
      *(ushort *)(param_2 + 1) = (ushort)(byte)(&DAT_0036dbd8)[(int)param_1 + iVar4];
      *param_2 = (int)(&DAT_0036db88 + (int)param_1 + iVar4);
      return 0;
    }
  }
  param_2[6] = 0x7534;
  return 1;
}

