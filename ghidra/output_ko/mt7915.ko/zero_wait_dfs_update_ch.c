// module: mt7915.ko
// function: zero_wait_dfs_update_ch @ 0x234aec
// size: 516 bytes
//

undefined4 zero_wait_dfs_update_ch(int param_1,int param_2,undefined1 *param_3)

{
  undefined4 uVar1;
  int iVar2;
  
  uVar1 = HcGetBandByWdev(param_2);
  if (DebugLevel < 3) {
    if (*(char *)(param_1 + 0x795404) == '\0') {
      return 0;
    }
  }
  else {
    printk("%s(): outband ch %d, ch_stat %d\n","zero_wait_dfs_update_ch",
           *(undefined1 *)(param_1 + 0x7953fb),*(undefined4 *)(param_1 + 0x79540c));
    if (*(char *)(param_1 + 0x795404) == '\0') {
      if (DebugLevel < 3) {
        return 0;
      }
      printk("%s(): bDedicatedZeroWaitDefault != 0\n","zero_wait_dfs_update_ch");
      return 0;
    }
  }
  if ((*(ushort *)(param_2 + 0x18) & 0xb1) != 0) {
    iVar2 = *(int *)(param_1 + 0x79540c);
    if (iVar2 == 0) {
      iVar2 = RadarChannelCheck(param_1,*param_3);
      if (iVar2 == 0) {
        if (2 < DebugLevel) {
          printk("%s(): non-DFS ch %d, ch_stat %d\n","zero_wait_dfs_update_ch",*param_3,
                 *(undefined4 *)(param_1 + 0x79540c));
        }
        *(undefined4 *)(param_1 + 0x79540c) = 0;
        *(undefined1 *)(param_1 + 0x7953fb) = 0;
        return 0;
      }
      *(undefined1 *)(param_1 + 0x7953fb) = *param_3;
      dfs_get_outband_bw(param_1,param_2,param_1 + 0x7953fc);
      mtRddControl(param_1,0,uVar1,0,0);
      uVar1 = FirstChannel(param_1,param_2);
      *param_3 = (char)uVar1;
      if (DebugLevel < 3) {
        return 1;
      }
      printk("%s(): DFS ch %d is selected, use non-DFS ch %d, ch_stat %d\n",
             "zero_wait_dfs_update_ch",*(undefined1 *)(param_1 + 0x7953fb),uVar1,
             *(undefined4 *)(param_1 + 0x79540c));
      return 1;
    }
    if (iVar2 == 5) {
      if ((0 < DebugLevel) &&
         (printk("%s(): Do not switch to DFS ch immediately\n","zero_wait_dfs_update_ch"),
         2 < DebugLevel)) {
        printk("%s(): ch_stat %d\n","zero_wait_dfs_update_ch",*(undefined4 *)(param_1 + 0x79540c));
        return 0;
      }
    }
    else if (-1 < DebugLevel) {
      printk("%s(): ch_stat %d\n","zero_wait_dfs_update_ch",iVar2);
    }
  }
  return 0;
}

