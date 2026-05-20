// module: mt7915.ko
// function: RtmpIoctl_rt_ioctl_rssi @ 0x64bb4
// size: 48 bytes
//

undefined4 RtmpIoctl_rt_ioctl_rssi(int *param_1,undefined1 *param_2)

{
  *param_2 = (char)param_1[*(int *)(*param_1 + 0x3c) * 0x84dec + 0x160349];
  return 0;
}

