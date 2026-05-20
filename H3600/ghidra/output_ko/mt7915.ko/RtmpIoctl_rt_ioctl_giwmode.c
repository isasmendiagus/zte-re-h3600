// module: mt7915.ko
// function: RtmpIoctl_rt_ioctl_giwmode @ 0x6227c
// size: 116 bytes
//

undefined4 RtmpIoctl_rt_ioctl_giwmode(int *param_1,undefined4 *param_2)

{
  undefined4 uVar1;
  
  if ((param_1[0x1e5449] & 2U) == 0) {
    if ((param_1[*(int *)(*param_1 + 0x3c) * 0x84dec + 0x15ffef] & 1U) == 0) {
      uVar1 = 0;
      if ((char)param_1[0xa6e43] == '\x01') {
        uVar1 = 3;
      }
      *param_2 = uVar1;
    }
    else {
      *param_2 = 2;
    }
  }
  else {
    *param_2 = 1;
  }
  return 0;
}

