// module: mt7915.ko
// function: RtmpIoctl_rt_ioctl_gifhwaddr @ 0x64b70
// size: 68 bytes
//

undefined4 RtmpIoctl_rt_ioctl_gifhwaddr(int *param_1,undefined4 *param_2)

{
  int iVar1;
  
  iVar1 = *(int *)(*param_1 + 0x3c);
  *param_2 = *(undefined4 *)((int)param_1 + iVar1 * 0x2137b0 + 0x36db73);
  *(undefined2 *)(param_2 + 1) = *(undefined2 *)((int)param_1 + iVar1 * 0x2137b0 + 0x36db77);
  return 0;
}

