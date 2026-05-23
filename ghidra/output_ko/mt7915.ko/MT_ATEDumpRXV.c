// module: mt7915.ko
// function: MT_ATEDumpRXV @ 0x27b9f0
// size: 432 bytes
//

undefined4
MT_ATEDumpRXV(undefined4 param_1,undefined4 param_2,undefined4 param_3,undefined4 param_4,
             undefined4 param_5,undefined4 param_6,undefined4 param_7,undefined4 param_8,
             undefined4 param_9,undefined4 param_10,undefined4 param_11,undefined4 param_12)

{
  if (DebugLevel < 1) {
    return 0;
  }
  printk("%%[RXV DUMP START][%d]\n",param_12);
  if (DebugLevel < 1) {
LAB_0027bae0:
    if (DebugLevel < 1) goto LAB_0027bb60;
    printk("[RXVD5]%08x\n",param_7);
    if (DebugLevel < 1) {
      return 0;
    }
    printk("[RXVD6]%08x\n",param_8);
  }
  else {
    printk("[RXVD1]%08x\n",param_3);
    if (DebugLevel < 1) {
      return 0;
    }
    printk("[RXVD2]%08x\n",param_4);
    if (0 < DebugLevel) {
      printk("[RXVD3]%08x\n",param_5);
      if (DebugLevel < 1) {
        return 0;
      }
      printk("[RXVD4]%08x\n",param_6);
      goto LAB_0027bae0;
    }
  }
  if (DebugLevel < 1) {
    return 0;
  }
  printk("[RXVD7]%08x\n",param_9);
  if (DebugLevel < 1) {
    return 0;
  }
  printk("[RXVD8]%08x\n",param_10);
LAB_0027bb60:
  if ((0 < DebugLevel) && (printk("[RXVD9]%08x\n",param_11), 0 < DebugLevel)) {
    printk("[RXV DUMP END]\n");
  }
  return 0;
}

