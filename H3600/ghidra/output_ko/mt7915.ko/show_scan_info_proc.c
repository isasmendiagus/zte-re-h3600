// module: mt7915.ko
// function: show_scan_info_proc @ 0x2916c
// size: 608 bytes
//

undefined4 show_scan_info_proc(int *param_1)

{
  undefined1 uVar1;
  undefined1 uVar2;
  int iVar3;
  uint uVar4;
  int iVar5;
  uint uVar6;
  undefined4 uVar7;
  bool bVar8;
  
  iVar5 = *param_1;
  iVar3 = *(int *)(iVar5 + 0x38);
  uVar4 = iVar3 - 0x100U & 0xfffffeff;
  if (iVar3 != 0x400 && uVar4 != 0) {
    return 0;
  }
  uVar6 = (uint)*(byte *)(iVar5 + 0x3c);
  if (uVar4 == 0) {
    uVar4 = hc_get_chip_bcn_max_num(param_1[0x29e5e8]);
    bVar8 = 0x1e < uVar6;
    if (uVar6 < 0x20) {
      bVar8 = uVar4 <= uVar6;
    }
    if (bVar8) {
      bVar8 = uVar6 == 1;
      if (uVar6 < 2) {
        bVar8 = *(int *)(iVar5 + 0x38) == 0x400;
      }
      goto joined_r0x00029298;
    }
  }
  else {
    bVar8 = uVar6 == 1;
    if (uVar6 < 2) {
      bVar8 = iVar3 == 0x400;
    }
joined_r0x00029298:
    if (!bVar8) {
      return 0;
    }
  }
  iVar3 = get_scan_ctrl_by_wdev(param_1,param_1 + uVar6 * 0x160d + 0xadc92);
  uVar7 = *(undefined4 *)(iVar3 + 0x184);
  uVar1 = *(undefined1 *)(iVar3 + 0x17d);
  uVar2 = *(undefined1 *)(iVar3 + 0x80);
  if (0 < DebugLevel) {
    printk("===== Scan Information =====\n");
    if (0 < DebugLevel) {
      printk("= Partial Scan =\n");
      if (((DebugLevel < 1) ||
          (printk("Partial Scan Timer Interval = %d (ms)\n",uVar7), DebugLevel < 1)) ||
         (printk("Number of channels to scan = %d\n",uVar1), DebugLevel < 1)) goto LAB_00029200;
      printk("= DFS Channel utilization =\n");
    }
    if (0 < DebugLevel) {
      printk("Using DFS channel is allowed = %d\n",uVar2);
    }
  }
LAB_00029200:
  if (*(int *)(iVar3 + 0x7c) != 0) {
    if ((0 < DebugLevel) && (printk("= Scan Skip List =\n"), 0 < DebugLevel)) {
      printk("Length of the channel skip list : %d\n",*(undefined1 *)(iVar3 + 0x79));
    }
    uVar4 = (uint)*(byte *)(iVar3 + 0x79);
    if (uVar4 != 0) {
      iVar5 = 0;
      do {
        if (0 < DebugLevel) {
          printk("Channel : %d\n",*(undefined1 *)(*(int *)(iVar3 + 0x7c) + iVar5));
          uVar4 = (uint)*(byte *)(iVar3 + 0x79);
        }
        iVar5 = iVar5 + 1;
      } while (iVar5 < (int)uVar4);
    }
  }
  if (((*(char *)(iVar3 + 0x1c0) != '\0') && (0 < DebugLevel)) &&
     ((printk("= User-defined Dwell Time =\n"), 0 < DebugLevel &&
      (printk("5G Dwell Time : %d (msec)\n",*(undefined2 *)(iVar3 + 0x1c2)), 0 < DebugLevel)))) {
    printk("2G Dwell Time : %d (msec)\n",*(undefined2 *)(iVar3 + 0x1c4));
  }
  return 1;
}

