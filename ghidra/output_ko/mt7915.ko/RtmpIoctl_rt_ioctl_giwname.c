// module: mt7915.ko
// function: RtmpIoctl_rt_ioctl_giwname @ 0xb8de4
// size: 44 bytes
//

undefined4 RtmpIoctl_rt_ioctl_giwname(undefined4 param_1,char *param_2)

{
  builtin_strncpy(param_2,"RTWIFI SoftAP",0xe);
  return 0;
}

