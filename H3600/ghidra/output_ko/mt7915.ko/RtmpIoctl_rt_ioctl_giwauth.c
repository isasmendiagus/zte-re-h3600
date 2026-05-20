// module: mt7915.ko
// function: RtmpIoctl_rt_ioctl_giwauth @ 0x63a08
// size: 232 bytes
//

undefined4 RtmpIoctl_rt_ioctl_giwauth(int *param_1,int *param_2)

{
  uint uVar1;
  int iVar2;
  int iVar3;
  
  iVar2 = *param_2;
  iVar3 = *(int *)(*param_1 + 0x3c);
  if (iVar2 == 0x80) {
    uVar1 = param_1[iVar3 * 0x84dec + 0xdb6e1] & 2;
  }
  else {
    if (iVar2 == 0x90) {
      if ((param_1[iVar3 * 0x84dec + 0xdb6e1] & 0x12cf8U) == 0) {
        param_2[1] = 0;
      }
      else {
        param_2[1] = 1;
      }
      return 0;
    }
    if (iVar2 != 0x70) {
      return 0;
    }
    uVar1 = param_1[iVar3 * 0x84dec + 0xdb6e1] & 1;
  }
  if (uVar1 != 0) {
    param_2[1] = 0;
    return 0;
  }
  param_2[1] = 1;
  return 0;
}

