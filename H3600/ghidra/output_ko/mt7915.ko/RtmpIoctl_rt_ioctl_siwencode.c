// module: mt7915.ko
// function: RtmpIoctl_rt_ioctl_siwencode @ 0x62c28
// size: 880 bytes
//

undefined4
RtmpIoctl_rt_ioctl_siwencode(int *param_1,undefined4 *param_2,undefined4 param_3,undefined4 param_4)

{
  short sVar1;
  uint uVar2;
  ushort uVar3;
  int iVar4;
  int iVar5;
  int iVar6;
  
  uVar3 = *(ushort *)(param_2 + 1);
  iVar4 = *(int *)(*param_1 + 0x3c);
  if ((uVar3 == 0) && ((*(ushort *)((int)param_2 + 0x16) & 1) != 0)) {
    param_1[iVar4 * 0x84dec + 0x160009] = param_1[iVar4 * 0x84dec + 0x160009] | 1;
    param_1[iVar4 * 0x84dec + 0x16000a] = param_1[iVar4 * 0x84dec + 0x16000a] | 1;
    param_1[iVar4 * 0x84dec + 0xdb6e1] = param_1[iVar4 * 0x84dec + 0xdb6e1] | 1;
    param_1[iVar4 * 0x84dec + 0xdb733] = param_1[iVar4 * 0x84dec + 0xdb733] | 1;
  }
  else {
    if ((*(ushort *)((int)param_2 + 0x16) & 0xc) != 0) {
      *(undefined1 *)(param_1 + iVar4 * 0x84dec + 0xdb8f8) = 1;
      param_1[iVar4 * 0x84dec + 0x160009] = param_1[iVar4 * 0x84dec + 0x160009] | 0xe;
      param_1[iVar4 * 0x84dec + 0x16000a] = param_1[iVar4 * 0x84dec + 0x16000a] | 0xe;
      param_1[iVar4 * 0x84dec + 0xdb733] = param_1[iVar4 * 0x84dec + 0xdb733] | 0xe;
      if ((*(ushort *)((int)param_2 + 0x16) & 4) == 0) {
        uVar2 = param_1[iVar4 * 0x84dec + 0xdb6e1] | 1;
      }
      else {
        uVar2 = param_1[iVar4 * 0x84dec + 0xdb6e1] | 2;
      }
      param_1[iVar4 * 0x84dec + 0xdb6e1] = uVar2;
      uVar3 = *(ushort *)(param_2 + 1);
    }
    if (uVar3 == 0) {
      if ((uint)param_2[2] < 4) {
        *(char *)(param_1 + iVar4 * 0x84dec + 0xdb734) = (char)param_2[2];
      }
      else if ((*(ushort *)((int)param_2 + 0x16) & 0x20) == 0) goto LAB_00062e38;
    }
    else {
      uVar2 = param_2[2];
      if (0xd < uVar3) {
LAB_00062e38:
        param_2[6] = 30000;
        return 0;
      }
      if (uVar2 < 4) {
        *(char *)(param_1 + iVar4 * 0x84dec + 0xdb734) = (char)uVar2;
      }
      else {
        if (2 < DebugLevel) {
          printk("==>rt_ioctl_siwencode::Wrong keyIdx=%d! Using default key instead (%d)\n",uVar2,
                 (char)param_1[iVar4 * 0x84dec + 0xdb734],param_1 + iVar4 * 0x84dec + 0xdb732,
                 param_4);
        }
        uVar2 = (uint)*(byte *)(param_1 + iVar4 * 0x84dec + 0xdb734);
      }
      iVar6 = uVar2 * 0x51 + iVar4 * 0x2137b0;
      iVar5 = (int)param_1 + iVar6;
      __memzero(&DAT_0036db88 + (int)param_1 + iVar6,0x10);
      sVar1 = *(short *)(param_2 + 1);
      if ((sVar1 == 0xd) || (sVar1 == 5)) {
        (&DAT_0036dbd8)[iVar5] = (char)sVar1;
      }
      else {
        (&DAT_0036dbd8)[iVar5] = 0;
      }
      if ((*(ushort *)((int)param_2 + 0x16) & 0x10) == 0) {
        memmove(&DAT_0036db88 + (int)param_1 + iVar6,(void *)*param_2,(uint)*(ushort *)(param_2 + 1)
               );
      }
    }
  }
  if ((2 < DebugLevel) &&
     (printk("==>rt_ioctl_siwencode::erq->flags=%x\n",*(undefined2 *)((int)param_2 + 0x16)),
     2 < DebugLevel)) {
    printk("==>rt_ioctl_siwencode::AuthMode=0x%x\n",param_1[iVar4 * 0x84dec + 0xdb6e1]);
    if ((2 < DebugLevel) &&
       (iVar6 = (int)param_1 +
                (uint)*(byte *)(param_1 + iVar4 * 0x84dec + 0xdb734) * 0x51 + iVar4 * 0x2137b0,
       printk("==>rt_ioctl_siwencode::DefaultKeyId=%x, KeyLen = %d\n",
              (uint)*(byte *)(param_1 + iVar4 * 0x84dec + 0xdb734),(&DAT_0036dbd8)[iVar6],
              iVar6 + 0x36dbd0,param_4), 2 < DebugLevel)) {
      printk("==>rt_ioctl_siwencode::WepStatus=0x%x\n",param_1[iVar4 * 0x84dec + 0xdb733]);
    }
  }
  return 0;
}

