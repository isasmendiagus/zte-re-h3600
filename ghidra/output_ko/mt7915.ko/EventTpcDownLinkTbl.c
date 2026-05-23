// module: mt7915.ko
// function: EventTpcDownLinkTbl @ 0x1a87d0
// size: 364 bytes
//

void EventTpcDownLinkTbl(undefined4 param_1,int param_2)

{
  int iVar1;
  
  if ((((((0 < DebugLevel) && (printk("TPC DOWNLINK INFO TABLE\n\n"), 0 < DebugLevel)) &&
        (printk("AP INFO\n"), 0 < DebugLevel)) &&
       ((printk("===============================================================================\n")
        , 0 < DebugLevel &&
        (printk("\t\tDL Tx Type\t\t\tCmd Pwr Ctrl\t\tDL Tc Pwr\n"), 0 < DebugLevel)))) &&
      ((printk("===============================================================================\n"),
       0 < DebugLevel &&
       ((printk("\t\tMU MIMO\t\t\t\t%3d\t\t\t\t\t%3d\n",*(undefined1 *)(param_2 + 1),
                (int)*(char *)(param_2 + 3)), 0 < DebugLevel &&
        (printk("\t\tOFDMA\t\t\t\t%3d\t\t\t\t\t%3d\n\n",*(undefined1 *)(param_2 + 2),
                (int)*(char *)(param_2 + 4)), 0 < DebugLevel)))))) &&
     ((printk("STA INFO\n"), 0 < DebugLevel &&
      ((printk("===============================================================================\n"),
       0 < DebugLevel &&
       (printk("\t\tWLAN\t\tTxPwrAlpha MU_MIMO\t\tTxPwrAlpha OFDMA\n"), 0 < DebugLevel)))))) {
    printk("===============================================================================\n");
  }
  iVar1 = param_2 + 0x100;
  do {
    if (0 < DebugLevel) {
      printk("\t\t%3d\t\t\t\t%3d\t\t\t\t\t%3d\n",*(undefined2 *)(param_2 + 8),
             (int)*(short *)(param_2 + 0xc),(int)*(short *)(param_2 + 0xe));
    }
    param_2 = param_2 + 8;
  } while (param_2 != iVar1);
  return;
}

