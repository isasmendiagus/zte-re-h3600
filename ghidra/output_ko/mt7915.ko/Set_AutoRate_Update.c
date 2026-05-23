// module: mt7915.ko
// function: Set_AutoRate_Update @ 0x1dcef8
// size: 360 bytes
//

undefined4 Set_AutoRate_Update(int param_1,char *param_2)

{
  int iVar1;
  int iVar2;
  uint uVar3;
  uint local_38;
  undefined1 auStack_34 [4];
  undefined4 local_30;
  
  local_38 = 0;
  hc_get_chip_cap(*(undefined4 *)(param_1 + 0xa797a0));
  iVar1 = hc_get_chip_cap(*(undefined4 *)(param_1 + 0xa797a0));
  if (param_2 == (char *)0x0) {
    return 1;
  }
  iVar2 = sscanf(param_2,"%u",&local_38);
  if (2 < DebugLevel) {
    printk("%s():WCID = %d\n","Set_AutoRate_Update",local_38);
  }
  if (iVar2 == 1) {
    uVar3 = HcGetMaxStaNum(param_1);
    if (local_38 < uVar3) {
      down_interruptible(param_1 + 0x285d58);
      iVar2 = local_38 * 0x14c0;
      if ((*(int *)(param_1 + iVar2 + 0xa1d20) != 0) && (*(char *)(iVar1 + 0x150) == '\x01')) {
        __memzero(auStack_34,0x1c);
        local_30 = 0x14;
        RAParamUpdate(param_1,param_1 + iVar2 + 0xa1d20,auStack_34);
      }
      up(param_1 + 0x285d58);
      return 1;
    }
    if (-1 < DebugLevel) {
      printk("WCID exceed pAd->MaxUcastEntryNum!\n");
      return 0;
    }
  }
  else if (-1 < DebugLevel) {
    printk("Format Error!\n");
  }
  return 0;
}

