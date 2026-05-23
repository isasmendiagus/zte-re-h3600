// module: mt7915.ko
// function: RtmpIoctl_rt_ioctl_siwfreq @ 0x62048
// size: 304 bytes
//

undefined4 RtmpIoctl_rt_ioctl_siwfreq(int *param_1,uint *param_2)

{
  uint uVar1;
  int iVar2;
  undefined4 uVar3;
  uint uVar4;
  int iVar5;
  bool bVar6;
  uint local_1c [2];
  
  uVar4 = *param_2;
  iVar5 = *(int *)(*param_1 + 0x3c);
  local_1c[0] = 0xffffffff;
  if ((int)uVar4 < 0x5f5e101) {
    uVar1 = uVar4;
    if (100000 < (int)uVar4) {
      uVar1 = (int)uVar4 / 100;
    }
  }
  else {
    uVar1 = (int)uVar4 / 100000;
  }
  bVar6 = uVar1 == 1000;
  if (uVar1 < 0x3e9) {
    bVar6 = (short)param_2[1] == 0;
  }
  if (!bVar6) {
    RTMP_MapKHZ2ChannelID(uVar1,local_1c);
    uVar4 = local_1c[0];
  }
  local_1c[0] = uVar4;
  iVar2 = ChannelSanity(param_1,local_1c[0] & 0xff);
  if (iVar2 == 1) {
    bVar6 = DebugLevel < 0;
    *(undefined1 *)((int)param_1 + iVar5 * 0x2137b0 + 0x36db72) = (undefined1)local_1c[0];
    *(undefined1 *)((int)param_1 + iVar5 * 0x2137b0 + 0x371cbd) = (undefined1)local_1c[0];
    *(undefined1 *)((int)param_1 + iVar5 * 0x2137b0 + 0x580d67) = (undefined1)local_1c[0];
    if (bVar6) {
      uVar3 = 0;
    }
    else {
      printk("==>rt_ioctl_siwfreq::SIOCSIWFREQ(Channel=%d)\n",
             *(undefined1 *)((int)param_1 + iVar5 * 0x2137b0 + 0x36db72));
      uVar3 = 0;
    }
  }
  else {
    uVar3 = 1;
  }
  return uVar3;
}

