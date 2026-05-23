// module: mt7915.ko
// function: mtf_txpower_show_info @ 0x1a3414
// size: 756 bytes
//

void mtf_txpower_show_info(undefined4 param_1,int param_2)

{
  undefined *puVar1;
  undefined *puVar2;
  char *pcVar3;
  
  if (DebugLevel < 1) {
    return;
  }
  printk("=============================================================================\n");
  if (DebugLevel < 1) {
LAB_001a3500:
    if (0 < DebugLevel) {
      printk("-----------------------------------------------------------------------------\n");
      if (DebugLevel < 1) {
        return;
      }
      pcVar3 = "Enable";
      if (*(char *)(param_2 + 0x15) == '\0') {
        pcVar3 = "Disable";
      }
      printk("  Sku: %s\n",pcVar3);
      goto LAB_001a3558;
    }
LAB_001a35b0:
    if (0 < DebugLevel) {
      pcVar3 = "Disable";
      if (*(char *)(param_2 + 0x16) != '\0') {
        pcVar3 = "Enable";
      }
      printk("  Backoff: %s\n",pcVar3);
      if (DebugLevel < 1) {
        return;
      }
      printk("  FrontEnd Loss (Tx): %d, %d, %d, %d\n",(int)*(char *)(param_2 + 8),
             (int)*(char *)(param_2 + 9),(int)*(char *)(param_2 + 10),(int)*(char *)(param_2 + 0xb))
      ;
      goto LAB_001a3614;
    }
  }
  else {
    printk(" \t\t\t\t\t\t\t BASIC INFO\n");
    if (DebugLevel < 1) {
      return;
    }
    printk("=============================================================================\n");
    if (0 < DebugLevel) {
      puVar1 = &_LC333;
      if (*(char *)(param_2 + 3) == '\0') {
        puVar1 = &_LC334;
      }
      printk("  Band Index: %d,  Channel Band: %s\n",*(undefined1 *)(param_2 + 2),puVar1);
      if (DebugLevel < 1) {
        return;
      }
      puVar1 = &_LC335;
      if (*(char *)(param_2 + 4) == '\0') {
        puVar1 = &_LC336;
      }
      puVar2 = &_LC337;
      if (*(char *)(param_2 + 5) == '\0') {
        puVar2 = &_LC338;
      }
      printk("  PA Type: %s,  LNA Type: %s\n",puVar1,puVar2);
      goto LAB_001a3500;
    }
LAB_001a3558:
    if (0 < DebugLevel) {
      pcVar3 = "Disable";
      if (*(char *)(param_2 + 6) != '\0') {
        pcVar3 = "Enable";
      }
      printk("  Percentage: %s\n",pcVar3);
      if (DebugLevel < 1) {
        return;
      }
      printk("  Power Drop: %d [dbm]\n",(int)*(char *)(param_2 + 7) >> 1);
      goto LAB_001a35b0;
    }
LAB_001a3614:
    if (DebugLevel < 1) goto LAB_001a36c4;
    printk("  FrontEnd Loss (Rx): %d, %d, %d, %d\n",(int)*(char *)(param_2 + 0xc),
           (int)*(char *)(param_2 + 0xd),(int)*(char *)(param_2 + 0xe),(int)*(char *)(param_2 + 0xf)
          );
    if (DebugLevel < 1) {
      return;
    }
    printk("  Mu Tx Power Manual Mode: %d\n",*(undefined1 *)(param_2 + 0x17));
  }
  if (DebugLevel < 1) {
    return;
  }
  printk("  Mu Tx Power (Auto): %d, Mu Tx Power (Manual): %d\n",(int)*(char *)(param_2 + 0x18),
         (int)*(char *)(param_2 + 0x19));
  if (DebugLevel < 1) {
    return;
  }
  pcVar3 = "Enable";
  if (*(char *)(param_2 + 0x10) == '\0') {
    pcVar3 = "Disable";
  }
  printk("  Thermal compensation: %s\n",pcVar3);
LAB_001a36c4:
  if ((0 < DebugLevel) &&
     (printk("  Theraml compensation value: %d\n",(int)*(char *)(param_2 + 0x11)), 0 < DebugLevel))
  {
    printk("=============================================================================\n");
    return;
  }
  return;
}

