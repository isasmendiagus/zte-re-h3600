// module: mt7915.ko
// function: EventTpcUpLinkTbl @ 0x1a893c
// size: 252 bytes
//

void EventTpcUpLinkTbl(undefined4 param_1,int param_2)

{
  int iVar1;
  
  if ((((0 < DebugLevel) && (printk("TPC UPLINK INFO TABLE\n\n"), 0 < DebugLevel)) &&
      (printk("AP INFO: AP TX Power = %d\n",*(undefined1 *)(param_2 + 1)), 0 < DebugLevel)) &&
     (((printk("STA INFO\n"), 0 < DebugLevel &&
       (printk("===============================================================================\n"),
       0 < DebugLevel)) &&
      (printk("\t\tWLAN\t\tTargetRssi\t\tPwrHeadRoom\t\tMinPwrFlag\n"), 0 < DebugLevel)))) {
    printk("===============================================================================\n");
  }
  iVar1 = param_2 + 0xc0;
  do {
    if (0 < DebugLevel) {
      printk("\t\t%3d\t\t\t%3d\t\t\t%3d\t\t\t%3d\n",*(undefined2 *)(param_2 + 4),
             *(undefined1 *)(param_2 + 6),*(undefined1 *)(param_2 + 7),*(undefined1 *)(param_2 + 8))
      ;
    }
    param_2 = param_2 + 6;
  } while (param_2 != iVar1);
  return;
}

