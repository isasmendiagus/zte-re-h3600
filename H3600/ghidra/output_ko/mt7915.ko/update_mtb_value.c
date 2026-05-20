// module: mt7915.ko
// function: update_mtb_value @ 0x164ba0
// size: 624 bytes
//

undefined4 update_mtb_value(undefined4 param_1,int param_2,undefined4 param_3,char *param_4)

{
  int iVar1;
  char *pcVar2;
  int iVar3;
  size_t sVar4;
  uint uVar5;
  char *pcVar6;
  
  pcVar6 = param_4;
  iVar1 = get_dev_config_idx();
  if (param_2 == 1) {
    sVar4 = strlen(param_4);
    pcVar2 = s__etc_Wireless_RT2860_RT2860_5G_d_0034d5b2 + iVar1 * 0x14c;
    uVar5 = sVar4 & 0xff;
    iVar3 = strcmp(param_4,pcVar2);
    if (iVar3 == 0 || 0x31 < uVar5) {
      if (2 < DebugLevel) {
        printk("mtb[%d].profile_5g remain %s!\n",iVar1,pcVar2,DebugLevel,pcVar6);
      }
    }
    else {
      strncpy(pcVar2,param_4,uVar5);
      iVar3 = DebugLevel;
      (_LANCHOR1 + uVar5 + iVar1 * 0x14c)[0x32] = '\0';
      if (2 < iVar3) {
        printk("mtb[%d].profile_5g updated as %s!\n",iVar1,pcVar2,_LANCHOR1 + uVar5 + iVar1 * 0x14c,
               pcVar6);
      }
    }
  }
  else if (param_2 == 0) {
    sVar4 = strlen(param_4);
    pcVar2 = _LANCHOR1 + iVar1 * 0x14c;
    iVar3 = strcmp(param_4,pcVar2);
    uVar5 = sVar4 & 0xff;
    if (iVar3 == 0 || 0x31 < uVar5) {
      if (2 < DebugLevel) {
        printk("mtb[%d].profile_2g remain %s!\n",iVar1,pcVar2,DebugLevel,pcVar6);
      }
    }
    else {
      strncpy(pcVar2,param_4,uVar5);
      iVar3 = DebugLevel;
      _LANCHOR1[iVar1 * 0x14c + uVar5] = '\0';
      if (2 < iVar3) {
        printk("mtb[%d].profile_2g updated as %s!\n",iVar1,pcVar2,iVar3,pcVar6);
      }
    }
  }
  else if (param_2 == 3) {
    pcVar2 = (char *)FUN_001621e4(param_1,param_3);
    if ((pcVar2 == (char *)0x0) || (iVar3 = strcmp(pcVar2,param_4), iVar3 == 0)) {
      if (2 < DebugLevel) {
        printk("mtb[%d].prefix remain %s!\n",iVar1,pcVar2,DebugLevel,pcVar6);
      }
    }
    else {
      strcpy(pcVar2,param_4);
      if (2 < DebugLevel) {
        printk("mtb[%d].prefix updated as %s!\n",iVar1,pcVar2,DebugLevel,pcVar6);
      }
    }
  }
  else if (-1 < DebugLevel) {
    printk("Uknown profile_id(%d)\n",param_2);
  }
  return 0;
}

