// module: mt7915.ko
// function: show_vow_info @ 0x48b54
// size: 576 bytes
//

undefined4 show_vow_info(int param_1)

{
  if (DebugLevel < 0) {
    return 1;
  }
  printk("======== VOW Control Information ========\n");
  if (DebugLevel < 0) {
LAB_00048bfc:
    if (-1 < DebugLevel) {
      printk("en_txop_no_change_bss: %d\n",*(undefined1 *)(param_1 + 0xa7a2eb));
      if (DebugLevel < 0) {
        return 1;
      }
      printk("dbdc0_search_rule: %d\n",*(undefined1 *)(param_1 + 0xa7a2ec));
      goto LAB_00048c44;
    }
LAB_00048c84:
    if (-1 < DebugLevel) {
      printk("SPL sta num: %d\n",*(undefined1 *)(param_1 + 0xa7a319));
      if (DebugLevel < 0) {
        return 1;
      }
      printk("======== VOW Max Deficit Information ========\n");
      goto LAB_00048cc8;
    }
  }
  else {
    printk("ATC Enbale: %d\n",*(undefined1 *)(param_1 + 0xa7a2e8));
    if (DebugLevel < 0) {
      return 1;
    }
    printk("ATF Enbale: %d\n",*(undefined1 *)(param_1 + 0xa7a2ea));
    if (-1 < DebugLevel) {
      printk("WATF Enable: %d\n",*(undefined1 *)(param_1 + 0xa7a32c));
      if (DebugLevel < 0) {
        return 1;
      }
      printk("en_bw_refill: %d\n",*(undefined1 *)(param_1 + 0xa7a2e9));
      goto LAB_00048bfc;
    }
LAB_00048c44:
    if (-1 < DebugLevel) {
      printk("dbdc1_search_rule: %d\n",*(undefined1 *)(param_1 + 0xa7a2ed));
      if (DebugLevel < 0) {
        return 1;
      }
      printk("refill_period: %d\n",*(undefined1 *)(param_1 + 0xa7a2ee));
      goto LAB_00048c84;
    }
LAB_00048cc8:
    if (DebugLevel < 0) goto LAB_00048d4c;
    printk("VOW Max Deficit(unit 256us): %d\n",*(undefined1 *)(param_1 + 0xa7a2f2));
    if (DebugLevel < 0) {
      return 1;
    }
    printk("======== VOW Quantum Information ========\n");
  }
  if (DebugLevel < 0) {
    return 1;
  }
  printk("Quantum ID 0 value(unit 256us): %d\n",*(undefined1 *)(param_1 + 0xa7a2f4));
  if (DebugLevel < 0) {
    return 1;
  }
  printk("Quantum ID 1 value(unit 256us): %d\n",*(undefined1 *)(param_1 + 0xa7a2f5));
LAB_00048d4c:
  if ((-1 < DebugLevel) &&
     (printk("Quantum ID 2 value(unit 256us): %d\n",*(undefined1 *)(param_1 + 0xa7a2f6)),
     -1 < DebugLevel)) {
    printk("Quantum ID 3 value(unit 256us): %d\n",*(undefined1 *)(param_1 + 0xa7a2f7));
  }
  return 1;
}

