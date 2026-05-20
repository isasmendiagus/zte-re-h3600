// module: mt7915.ko
// function: dfs_off_cac_end_update @ 0x236888
// size: 456 bytes
//

void dfs_off_cac_end_update(int param_1)

{
  uint uVar1;
  undefined4 uVar2;
  int iVar3;
  
  if (*(char *)(param_1 + 0x795404) == '\0') {
    if (2 < DebugLevel) {
      uVar1 = 0x880c;
LAB_002369f4:
      printk(uVar1 | 0x310000,"dfs_off_cac_end_update");
      return;
    }
  }
  else if (*(char *)(param_1 + 0x795402) == '\0') {
    if (-1 < DebugLevel) {
      uVar1 = 0x8834;
      goto LAB_002369f4;
    }
  }
  else {
    if (2 < DebugLevel) {
      printk("%s() zero-wait CAC end, ch_stat %d\n","dfs_off_cac_end_update",
             *(undefined4 *)(param_1 + 0x79540c));
    }
    iVar3 = *(int *)(param_1 + 0x79540c);
    if (iVar3 == 1) {
      uVar2 = dfs_get_band_by_ch(param_1,*(undefined1 *)(param_1 + 0x7953fb));
      if (0 < DebugLevel) {
        printk("%s() New inband channel %d bandidx %d\n","dfs_off_cac_end_update",
               *(undefined1 *)(param_1 + 0x7953fb),uVar2);
      }
      *(undefined4 *)(param_1 + 0x79540c) = 2;
      DfsDedicatedInBandSetChannel
                (param_1,*(undefined1 *)(param_1 + 0x7953fb),*(undefined1 *)(param_1 + 0x7953fc),0,
                 uVar2);
      iVar3 = DebugLevel;
    }
    else if ((iVar3 == 0) || (1 < iVar3 - 3U)) {
      if (DebugLevel < 0) {
        return;
      }
      printk("%s() invalid input %d\n","dfs_off_cac_end_update");
      iVar3 = DebugLevel;
    }
    else {
      uVar2 = dfs_get_band_by_ch(param_1,*(undefined1 *)(param_1 + 0x7953fb));
      if (2 < DebugLevel) {
        printk("%s() zero-wait CAC ch %d is available, bandidx %d\n","dfs_off_cac_end_update",
               *(undefined1 *)(param_1 + 0x7953fb),uVar2);
      }
      iVar3 = DebugLevel;
      *(undefined4 *)(param_1 + 0x79540c) = 4;
    }
    if (2 < iVar3) {
      printk("%s() ch_stat %d\n","dfs_off_cac_end_update",*(undefined4 *)(param_1 + 0x79540c));
      return;
    }
  }
  return;
}

