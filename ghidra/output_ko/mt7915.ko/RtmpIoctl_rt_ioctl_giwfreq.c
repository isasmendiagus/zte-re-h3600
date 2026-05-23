// module: mt7915.ko
// function: RtmpIoctl_rt_ioctl_giwfreq @ 0x62178
// size: 136 bytes
//

undefined4 RtmpIoctl_rt_ioctl_giwfreq(int *param_1,undefined4 *param_2)

{
  undefined1 uVar1;
  undefined4 local_14 [2];
  
  local_14[0] = 0x24cde0;
  uVar1 = *(undefined1 *)((int)param_1 + *(int *)(*param_1 + 0x3c) * 0x2137b0 + 0x36db72);
  if (2 < DebugLevel) {
    printk("==>rt_ioctl_giwfreq  %d\n",uVar1);
  }
  RTMP_MapChannelID2KHZ(uVar1,local_14);
  *param_2 = local_14[0];
  return 0;
}

