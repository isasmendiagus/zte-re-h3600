// module: mt7915.ko
// function: RtmpIoctl_rt_ioctl_giwessid @ 0x629e0
// size: 236 bytes
//

undefined4 RtmpIoctl_rt_ioctl_giwessid(int *param_1,int param_2)

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
  if ((char)param_1[0xa6e43] == '\x01') {
    *(undefined4 *)(param_2 + 4) = 0;
  }
  else if ((piVar2[0x84919] & 0x80U) == 0) {
    *(undefined4 *)(param_2 + 4) = 0;
    if (2 < DebugLevel) {
      printk("MediaState is not connected, ess\n");
    }
  }
  else {
    if (2 < DebugLevel) {
      printk("MediaState is connected\n");
    }
    *(uint *)(param_2 + 4) = (uint)*(byte *)((int)piVar2 + 0x212426);
    memcpy(*(void **)(param_2 + 8),(void *)((int)piVar2 + 0x212406),
           (uint)*(byte *)((int)piVar2 + 0x212426));
  }
  return 0;
}

