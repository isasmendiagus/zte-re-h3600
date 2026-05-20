// module: mt7915.ko
// function: Set_MonitorShowAll_Proc @ 0x27c48
// size: 528 bytes
//

undefined4 Set_MonitorShowAll_Proc(int param_1)

{
  int iVar1;
  char *pcVar2;
  int iVar3;
  
  if (0 < DebugLevel) {
    printk("--> %s()\n","Set_MonitorShowAll_Proc");
    if (0 < DebugLevel) {
      printk("  Monitor Enable: %d\n",*(undefined1 *)(param_1 + 0xa37233));
      if (0 < DebugLevel) {
        printk("  Index last set: %d\n",*(undefined1 *)(param_1 + 0xa37694));
        if (0 < DebugLevel) {
          printk("  BAND0 Count: %d\n",*(undefined4 *)(param_1 + 0xa3769c));
          if (0 < DebugLevel) {
            printk("  BAND1 Count: %d\n",*(undefined4 *)(param_1 + 0xa376a0));
          }
        }
      }
    }
  }
  pcVar2 = (char *)(param_1 + 0xa37234);
  iVar3 = 0;
  iVar1 = DebugLevel;
  do {
    if ((*pcVar2 != '\0') && (0 < iVar1)) {
      printk("Band%d: Monitor STA[%d]\t",pcVar2[1],iVar3);
      iVar1 = DebugLevel;
      if (0 < DebugLevel) {
        printk("%02x:%02x:%02x:%02x:%02x:%02x\t",pcVar2[0x14],pcVar2[0x15],pcVar2[0x16],pcVar2[0x17]
               ,pcVar2[0x18],pcVar2[0x19]);
        iVar1 = DebugLevel;
        if (0 < DebugLevel) {
          printk("[DATA]=%08lu\t",*(undefined4 *)(pcVar2 + 8));
          iVar1 = DebugLevel;
          if (0 < DebugLevel) {
            printk("[MGMT]=%08lu\t",*(undefined4 *)(pcVar2 + 0xc));
            iVar1 = DebugLevel;
            if (0 < DebugLevel) {
              printk("[CNTL]=%08lu\t",*(undefined4 *)(pcVar2 + 0x10));
              iVar1 = DebugLevel;
              if (0 < DebugLevel) {
                printk("[TOTAL]=%08lu\t",*(undefined4 *)(pcVar2 + 4));
                iVar1 = DebugLevel;
                if (0 < DebugLevel) {
                  printk("RSSI:%d,%d,%d,%d\n",(int)pcVar2[0x1e],(int)pcVar2[0x1f],(int)pcVar2[0x20],
                         (int)pcVar2[0x21]);
                  iVar1 = DebugLevel;
                }
              }
            }
          }
        }
      }
    }
    iVar3 = iVar3 + 1;
    pcVar2 = pcVar2 + 0x44;
  } while (iVar3 != 0x10);
  if (0 < iVar1) {
    printk("<-- %s()\n","Set_MonitorShowAll_Proc");
  }
  return 1;
}

