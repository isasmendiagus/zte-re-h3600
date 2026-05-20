// module: mt7915.ko
// function: show_dfs_ch_info_proc @ 0x230bbc
// size: 396 bytes
//

undefined4 show_dfs_ch_info_proc(int param_1)

{
  int iVar1;
  undefined2 *puVar2;
  undefined1 *puVar3;
  int iVar4;
  bool bVar5;
  
  if (2 < DebugLevel) {
    printk("[%s]: DFS channel info\n","show_dfs_ch_info_proc");
  }
  if (0 < DebugLevel) {
    printk("=========================================\n ");
  }
  puVar3 = (undefined1 *)(param_1 + 0x795130);
  puVar2 = (undefined2 *)(param_1 + 0xa37726);
  iVar4 = 0;
  iVar1 = DebugLevel;
  do {
    if (((0 < iVar1) && (printk("band_idx: %d\n",iVar4), iVar1 = DebugLevel, 0 < DebugLevel)) &&
       (printk("CH: %d,\tBW: %d,\tCAC cnt: %d,\tCAC: %d\n",*puVar3,puVar3[4],*puVar2,puVar2[3]),
       iVar1 = DebugLevel, 0 < DebugLevel)) {
      printk("-----------------------------------------\n ");
      iVar1 = DebugLevel;
    }
    bVar5 = iVar4 != 1;
    puVar2 = puVar2 + 0x10;
    iVar4 = 1;
    puVar3 = puVar3 + 1;
  } while (bVar5);
  if (((*(char *)(param_1 + 0x7953fa) == '\x01') && (*(char *)(param_1 + 0x795404) == '\x01')) &&
     (0 < iVar1)) {
    printk("dedicated RX:\n");
    if (DebugLevel < 1) {
      return 1;
    }
    printk("CH: %d,\tBW: %d,\tCAC cnt: %d,\tCAC: %d\n",*(undefined1 *)(param_1 + 0x7953fb),
           *(undefined1 *)(param_1 + 0x7953fc),*(undefined2 *)(param_1 + 0x795400),
           *(undefined2 *)(param_1 + 0x795406));
    iVar1 = DebugLevel;
  }
  if (0 < iVar1) {
    printk("=========================================\n ");
  }
  return 1;
}

