// module: mt7915.ko
// function: mt7915_apply_dpd_flatness_data @ 0x17edfc
// size: 844 bytes
//

void mt7915_apply_dpd_flatness_data(int param_1,uint param_2)

{
  int iVar1;
  int iVar2;
  undefined4 uVar3;
  undefined4 uVar4;
  uint uVar5;
  uint uVar6;
  int iVar7;
  int iVar8;
  uint uVar9;
  ushort local_32;
  char cStack_9;
  
  local_32 = 0;
  uVar6 = param_2 >> 0x10 & 0xff;
  cStack_9 = (char)(param_2 >> 0x18);
  iVar1 = hc_get_chip_ops(*(undefined4 *)(param_1 + 0xa797a0));
  if (("cp_support_is_enabled"[param_1 + 4] - 2U & 0xfd) != 0) {
    if (DebugLevel < 0) {
      return;
    }
    printk("%s: Currently not in FLASH or BIN MODE,return.\n","mt7915_apply_dpd_flatness_data");
    return;
  }
  (**(code **)(iVar1 + 8))(param_1,0x62,&local_32);
  if ((local_32 & 6) != 6) {
    if (DebugLevel < 2) {
      return;
    }
    printk("%s: eeprom 0x%2x bit 0 is 0, do runtime cal\n","mt7915_apply_dpd_flatness_data",0x62);
    return;
  }
  if (-1 < DebugLevel) {
    printk("%s: DPD Pre-Cal finished, load DPD Pre-Cal data\n","mt7915_apply_dpd_flatness_data");
  }
  if (uVar6 == 0xe) {
    if (DebugLevel < 3) {
      return;
    }
    printk("%s: CH 14 don\'t need DPD , return!!!\n","mt7915_apply_dpd_flatness_data");
    return;
  }
  if (uVar6 < 0xe) {
    if (uVar6 - 1 < 4) {
      uVar6 = 0x976;
    }
    else if (uVar6 - 5 < 5) {
      uVar6 = 0x98a;
    }
    else if (uVar6 - 10 < 4) {
      uVar6 = 0x99e;
    }
    else if (DebugLevel < 0) {
      uVar6 = 0;
    }
    else {
      printk("%s: can\'t find cent freq for CH %d , should not happen!!!\n",
             "mt7915_apply_dpd_flatness_data",uVar6);
      uVar6 = 0;
    }
  }
  else if (cStack_9 == '\0') {
    uVar6 = uVar6 * 5 + 5000;
  }
  else {
    if (cStack_9 == '\x03' || cStack_9 == '\x06') {
      if (DebugLevel < 0) {
        return;
      }
      printk("%s: MT7915 not support BW8080 or BW160. return\n","mt7915_apply_dpd_flatness_data");
      return;
    }
    iVar8 = uVar6 * 5 + 5000;
    iVar7 = uVar6 * 5 + 0x137e;
    iVar1 = ChannelFreqToGroup(iVar8);
    iVar2 = ChannelFreqToGroup(iVar7);
    if (iVar1 == iVar2) {
      uVar6 = (uVar6 - 2) * 5 + 5000 & 0xffff;
    }
    else {
      if (2 < DebugLevel) {
        uVar3 = ChannelFreqToGroup(iVar8);
        uVar4 = ChannelFreqToGroup(iVar7);
        printk("==== Different Group Central %d @ group %d Central-10 @ group %d !!\n",iVar8,uVar3,
               uVar4);
      }
      uVar6 = uVar6 * 5 + 0x1392;
    }
  }
  uVar9 = (uint)MT7915_DPD_FLATNESS_BW20_FREQ_SIZE;
  if (uVar9 == 0) {
LAB_0017f048:
    if (2 < DebugLevel) {
      printk("%s: Unexpected freq (%d)\n","mt7915_apply_dpd_flatness_data",uVar6);
    }
  }
  else {
    if ((ushort)MT7915_DPD_FLATNESS_BW20_FREQ._0_2_ == uVar6) {
      if (2 < DebugLevel) {
        uVar5 = 0;
        goto LAB_0017efe0;
      }
      uVar5 = 0;
    }
    else {
      uVar5 = 0;
      do {
        uVar5 = uVar5 + 1 & 0xff;
        if (uVar9 <= uVar5) goto LAB_0017ef48;
      } while (*(ushort *)(MT7915_DPD_FLATNESS_BW20_FREQ + uVar5 * 2) != uVar6);
      if (2 < DebugLevel) {
LAB_0017efe0:
        printk("%s: %d is in DPD-Flatness cal table, index = %d\n","mt7915_apply_dpd_flatness_data",
               uVar6,uVar5);
        uVar9 = (uint)MT7915_DPD_FLATNESS_BW20_FREQ_SIZE;
LAB_0017ef48:
        if (uVar9 == uVar5) goto LAB_0017f048;
      }
    }
    MtCmdSetDpdFlatnessCal_7915(param_1,uVar5 * 2,0x400);
    MtCmdSetDpdFlatnessCal_7915(param_1,uVar5 * 2 + 1,0x400);
  }
  return;
}

