// module: mt7915.ko
// function: RtmpIoctl_rt_ioctl_giwnickn @ 0x62b08
// size: 96 bytes
//

undefined4 RtmpIoctl_rt_ioctl_giwnickn(int param_1,uint *param_2)

{
  size_t sVar1;
  uint uVar2;
  uint uVar3;
  
  uVar3 = *param_2;
  sVar1 = strlen((char *)(param_1 + 0x794abb));
  uVar2 = sVar1 + 1;
  if (uVar2 < uVar3) {
    *param_2 = uVar2;
    uVar3 = uVar2;
  }
  if (uVar3 != 0) {
    memcpy((void *)param_2[1],(char *)(param_1 + 0x794abb),uVar3 - 1);
    *(undefined1 *)(param_2[1] + *param_2 + -1) = 0;
  }
  return 0;
}

