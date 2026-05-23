// module: mt7915.ko
// function: show_background_scan_info @ 0xea908
// size: 612 bytes
//

undefined4
show_background_scan_info(int param_1,undefined4 param_2,undefined4 param_3,undefined4 param_4)

{
  undefined4 extraout_r2;
  undefined4 extraout_r2_00;
  undefined4 extraout_r2_01;
  undefined4 extraout_r2_02;
  undefined4 uVar1;
  undefined4 extraout_r2_03;
  undefined4 extraout_r2_04;
  
  if (0 < DebugLevel) {
    printk(" Background scan support = %d\n",*(undefined1 *)(param_1 + 0xa78ad2),param_3,DebugLevel,
           param_4);
  }
  if (*(char *)(param_1 + 0xa78ad2) != '\x01') {
    return 1;
  }
  if (DebugLevel < 1) {
    return 1;
  }
  printk("===== Configuration =====\n");
  uVar1 = extraout_r2;
  if (DebugLevel < 1) {
LAB_000ea9d8:
    if (0 < DebugLevel) {
      printk(" Partial Scan Interval = %d second\n",*(undefined4 *)(param_1 + 0xa79610),uVar1,
             DebugLevel,param_4);
      if (DebugLevel < 1) {
        return 1;
      }
      printk(" DriverTrigger support= %d\n",*(undefined1 *)(param_1 + 0xa79753),extraout_r2_03,
             DebugLevel,param_4);
      goto LAB_000eaa1c;
    }
LAB_000eaa5c:
    if (0 < DebugLevel) {
      printk(" One sec primary channel busy time = %d\n",*(undefined4 *)(param_1 + 0xa7c308),uVar1,
             DebugLevel,param_4);
      if (DebugLevel < 1) {
        return 1;
      }
      printk(" One sec My Tx Airtime = %d\n",*(undefined4 *)(param_1 + 0xa7c320));
      goto LAB_000eaaa0;
    }
  }
  else {
    printk(" Channel busy time Threshold = %d\n",*(undefined4 *)(param_1 + 0xa79624),extraout_r2,
           DebugLevel,param_4);
    if (DebugLevel < 1) {
      return 1;
    }
    printk(" Noisy Threshold = %d\n",*(undefined1 *)(param_1 + 0xa79620),extraout_r2_00,DebugLevel,
           param_4);
    if (0 < DebugLevel) {
      printk(" IPI Idle Threshold (*8us) = %d\n",*(undefined4 *)(param_1 + 0xa79798),extraout_r2_01,
             DebugLevel,param_4);
      if (DebugLevel < 1) {
        return 1;
      }
      printk(" Scan Duration = %d ms\n",*(undefined2 *)(param_1 + 0xa79230));
      uVar1 = extraout_r2_02;
      goto LAB_000ea9d8;
    }
LAB_000eaa1c:
    if (0 < DebugLevel) {
      printk("===== Status / Statistic =====\n");
      if (DebugLevel < 1) {
        return 1;
      }
      printk(" One sec channel busy time = %d\n",*(undefined4 *)(param_1 + 0xa7c310));
      uVar1 = extraout_r2_04;
      goto LAB_000eaa5c;
    }
LAB_000eaaa0:
    if (DebugLevel < 1) goto LAB_000eab2c;
    printk(" One sec My Rx Airtime = %d\n",*(undefined4 *)(param_1 + 0xa7c328));
    if (DebugLevel < 1) {
      return 1;
    }
    printk(" IPI Idle time = %d\n",*(undefined4 *)(param_1 + 0xa79794));
  }
  if (DebugLevel < 1) {
    return 1;
  }
  printk(" Noisy = %d\n",*(undefined4 *)(param_1 + 0xa7961c));
  if (DebugLevel < 1) {
    return 1;
  }
  printk(" Current state = %ld\n",*(undefined4 *)(param_1 + 0xa79184));
LAB_000eab2c:
  if (0 < DebugLevel) {
    printk(" Scan type = %d\n",*(undefined1 *)(param_1 + 0xa79754));
  }
  return 1;
}

