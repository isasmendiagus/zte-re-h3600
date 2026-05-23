// module: mt7915.ko
// function: RtmpIoctl_rt_ioctl_setparam @ 0x64be4
// size: 28 bytes
//

undefined4 RtmpIoctl_rt_ioctl_setparam(int *param_1)

{
  int iVar1;
  
  iVar1 = *param_1;
  *(undefined4 *)(iVar1 + 0x38) = 0x100;
  *(undefined4 *)(iVar1 + 0x3c) = 0;
  return 0;
}

