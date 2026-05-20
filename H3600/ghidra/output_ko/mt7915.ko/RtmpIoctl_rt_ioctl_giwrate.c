// module: mt7915.ko
// function: RtmpIoctl_rt_ioctl_giwrate @ 0x64a50
// size: 288 bytes
//

undefined4 RtmpIoctl_rt_ioctl_giwrate(int param_1,int *param_2,undefined4 param_3,int param_4)

{
  ushort uVar1;
  int iVar2;
  uint uVar3;
  uint uVar4;
  
  iVar2 = GetStaCfgByWdev(param_1,param_4);
  if (((*(char *)(param_4 + 0x8b0) == '\0') && ((*(uint *)(iVar2 + 0x212464) & 1) != 0)) &&
     (((*(ushort *)(param_4 + 0x18) & 0x18) == 0 || (*(byte *)(param_1 + 0xa329d) < 0x40)))) {
    uVar1 = *(ushort *)(param_4 + 0x8b2);
  }
  else {
    uVar1 = *(ushort *)(param_1 + 0xa329c);
  }
  uVar4 = (uint)uVar1;
  if ((uVar4 << 0x10) >> 0x1d < 2) {
    uVar3 = (uVar4 << 0x10) >> 0x18 & 0xe0;
    if (uVar3 == 0x20) {
      uVar4 = (uVar4 & 0x3f) + 4;
    }
    else if (uVar3 == 0) {
      uVar4 = uVar4 & 0x3f;
    }
    else {
      uVar4 = 0;
    }
  }
  else {
    uVar4 = ((uVar4 << 0x17) >> 0x1e) * 0x18 + 0xc + ((int)(uVar4 << 0x16) >> 0x1f) * -0x30 +
            (uVar4 & 0x3f);
  }
  if (((int)(RT_RateSize >> 2) <= (int)uVar4) &&
     (uVar4 = (RT_RateSize >> 2) - 1, uVar4 == 0xffffffff)) {
    uVar4 = 0;
  }
  *param_2 = *(int *)(ralinkrate + uVar4 * 4) * 500000;
  return 0;
}

