// module: mt7915.ko
// function: Set_RA_Debug_Proc @ 0x1db6e8
// size: 316 bytes
//

undefined1 Set_RA_Debug_Proc(int param_1,char *param_2)

{
  int iVar1;
  char *pcVar2;
  uint uVar3;
  uint uVar4;
  uint uVar5;
  char *local_3c [2];
  undefined1 auStack_34 [4];
  uint local_30;
  
  local_3c[0] = param_2;
  iVar1 = hc_get_chip_cap(*(undefined4 *)(param_1 + 0xa797a0));
  if (0 < DebugLevel) {
    printk("%s: arg = %s\n","Set_RA_Debug_Proc",local_3c[0]);
  }
  pcVar2 = strsep(local_3c,":");
  if ((pcVar2 == (char *)0x0) || (local_3c[0] == (char *)0x0)) {
    if (0 < DebugLevel) {
      printk("%s: Invalid parameters\n","Set_RA_Debug_Proc");
    }
  }
  else {
    uVar3 = os_str_toul(pcVar2,0,10);
    uVar4 = os_str_toul(local_3c[0],0,10);
    uVar5 = HcGetMaxStaNum(param_1);
    if (uVar3 < uVar5) {
      if ((*(char *)(iVar1 + 0x150) == '\x01') && (0x16 < uVar4)) {
        __memzero(auStack_34,0x1c);
        local_30 = uVar4;
        RAParamUpdate(param_1,uVar3 * 0x14c0 + param_1 + 0xa1d20,auStack_34);
        return 1;
      }
    }
    else if (-1 < DebugLevel) {
      printk("u4WlanIndex exceed pAd->MaxUcastEntryNum!\n");
      return 0;
    }
  }
  return 0;
}

