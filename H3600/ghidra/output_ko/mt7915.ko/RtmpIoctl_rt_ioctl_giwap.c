// module: mt7915.ko
// function: RtmpIoctl_rt_ioctl_giwap @ 0x623c0
// size: 148 bytes
//

undefined4 RtmpIoctl_rt_ioctl_giwap(int *param_1,int *param_2)

{
  uint uVar1;
  int *piVar2;
  
  if (param_1 == (int *)0x0) {
    piVar2 = (int *)0x0;
  }
  else {
    piVar2 = (int *)0x0;
    if (*param_1 != 0) {
      uVar1 = *(uint *)(*param_1 + 0x3c);
      if (uVar1 < 2) {
        piVar2 = param_1 + uVar1 * 0x84dec + 0xdb6d6;
      }
      else {
        piVar2 = (int *)0x0;
      }
    }
  }
  if (((piVar2[0x84919] & 1U) == 0) && ((param_1[0x1e5449] & 2U) == 0)) {
    return 1;
  }
  *param_2 = piVar2[0x8490a];
  *(short *)(param_2 + 1) = (short)piVar2[0x8490b];
  return 0;
}

