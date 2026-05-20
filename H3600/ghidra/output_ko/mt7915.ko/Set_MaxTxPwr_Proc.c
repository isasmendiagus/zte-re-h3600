// module: mt7915.ko
// function: Set_MaxTxPwr_Proc @ 0xd9f1c
// size: 360 bytes
//

undefined4 Set_MaxTxPwr_Proc(int *param_1,undefined4 param_2)

{
  char cVar1;
  undefined4 uVar2;
  int iVar3;
  uint uVar4;
  int *piVar5;
  
  iVar3 = *(int *)(*param_1 + 0x38);
  uVar4 = *(uint *)(*param_1 + 0x3c);
  if ((iVar3 - 0x100U & 0xfffffeff) == 0) {
    piVar5 = param_1 + (uVar4 & 0xff) * 0x160d + 0xadc92;
  }
  else {
    piVar5 = (int *)0x0;
  }
  if ((iVar3 == 0x400) || (iVar3 == 0x800)) {
    piVar5 = param_1 + (uVar4 & 0xff) * 0x84dec + 0xdb6d6;
  }
  if (piVar5 == (int *)0x0) {
    if (-1 < DebugLevel) {
      printk("[Set_MaxTxPwr_Proc]: pObj->ioctl_if_type = %d!!\n",iVar3);
      return 0;
    }
  }
  else {
    cVar1 = simple_strtol(param_2,0,10);
    if ((byte)(cVar1 - 1U) < 0xfe) {
      *(char *)(param_1 + 0xa5dfb) = cVar1;
      uVar2 = HcGetBandByWdev(piVar5);
      uVar2 = hc_get_channel_ctrl(param_1[0x29e5e8],uVar2);
      hc_set_ChCtrlChListStat(uVar2,0);
      BuildChannelList(param_1,piVar5);
      if (0 < DebugLevel) {
        printk("Set MaxTxPwr = %d\n",cVar1);
        return 1;
      }
      return 1;
    }
    if (0 < DebugLevel) {
      printk("ERROR: wrong power announced(MaxTxPwr=%d)\n",cVar1);
    }
  }
  return 0;
}

