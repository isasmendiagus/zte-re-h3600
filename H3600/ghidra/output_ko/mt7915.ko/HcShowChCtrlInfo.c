// module: mt7915.ko
// function: HcShowChCtrlInfo @ 0xa94f8
// size: 500 bytes
//

void HcShowChCtrlInfo(int param_1)

{
  char cVar1;
  int iVar2;
  uint uVar3;
  int iVar4;
  int iVar5;
  int iVar6;
  
  if ((0 < DebugLevel) &&
     (printk("=====================START====================\n "), 0 < DebugLevel)) {
    printk("---------------------------------------------\n ");
  }
  iVar5 = 0;
  iVar6 = DebugLevel;
  while( true ) {
    iVar4 = *(int *)(param_1 + 0xa797a0);
    iVar2 = iVar4 + iVar5 * 0x4e0;
    if (*(char *)(iVar2 + 0x4d4) == '\0') break;
    if (iVar6 < 1) {
LAB_000a954c:
      uVar3 = 0;
      do {
        if (0 < iVar6) {
          iVar6 = iVar4 + iVar5 * 0x4e0 + uVar3 * 0x14;
          printk("\t#%d \t\t%d/%d \t\t%x\n ",*(undefined1 *)(iVar6 + 0x38),
                 (int)*(char *)(iVar6 + 0x3a),(int)*(char *)(iVar6 + 0x3b),
                 *(undefined4 *)(iVar6 + 0x48));
          iVar6 = DebugLevel;
        }
        uVar3 = uVar3 + 1 & 0xff;
      } while (uVar3 < *(byte *)(iVar4 + iVar5 * 0x4e0 + 0x4d4));
LAB_000a9578:
      if (0 < iVar6) {
        printk("---------------------------------------------\n ");
        iVar6 = DebugLevel;
      }
    }
    else {
      printk(&_LC21,iVar5);
      if (0 < DebugLevel) {
        printk("\tChGrpABandEn = %d\n ",*(undefined1 *)(iVar2 + 0x4d5));
        if (DebugLevel < 1) {
          cVar1 = *(char *)(iVar2 + 0x4d4);
          iVar6 = DebugLevel;
          goto joined_r0x000a96a4;
        }
        printk("\tChannel list information:\n ");
        if (DebugLevel < 1) goto LAB_000a9690;
        printk("\tChannel \tPwr0/1 \t\tFlags\n ");
        iVar6 = DebugLevel;
        if (*(char *)(iVar2 + 0x4d4) != '\0') goto LAB_000a954c;
        goto LAB_000a9578;
      }
LAB_000a9690:
      cVar1 = *(char *)(iVar4 + iVar5 * 0x4e0 + 0x4d4);
      iVar6 = DebugLevel;
joined_r0x000a96a4:
      DebugLevel = iVar6;
      if (cVar1 != '\0') goto LAB_000a954c;
    }
    if (iVar5 == 1) goto LAB_000a95ac;
    iVar5 = 1;
  }
  if (2 < iVar6) {
    printk(&_LC20,iVar5);
    iVar6 = DebugLevel;
  }
LAB_000a95ac:
  if (iVar6 < 1) {
    return;
  }
  printk("=====================END=====================\n ");
  return;
}

