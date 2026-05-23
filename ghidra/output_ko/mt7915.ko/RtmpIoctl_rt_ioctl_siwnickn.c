// module: mt7915.ko
// function: RtmpIoctl_rt_ioctl_siwnickn @ 0x62acc
// size: 60 bytes
//

undefined4 RtmpIoctl_rt_ioctl_siwnickn(int param_1,void *param_2,size_t param_3)

{
  __memzero((void *)(param_1 + 0x794abb),0x21);
  memcpy((void *)(param_1 + 0x794abb),param_2,param_3);
  return 0;
}

