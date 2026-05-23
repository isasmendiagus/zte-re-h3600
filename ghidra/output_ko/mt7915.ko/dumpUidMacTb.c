// module: mt7915.ko
// function: dumpUidMacTb @ 0x7bde8
// size: 476 bytes
//

undefined4 dumpUidMacTb(int param_1,int param_2)

{
  undefined4 uVar1;
  int iVar2;
  undefined1 *puVar3;
  undefined1 *puVar4;
  int iVar5;
  char *pcVar6;
  
  pcVar6 = *(char **)(param_1 + 0x14);
  if ((pcVar6 == (char *)0x0) || (*pcVar6 == '\0')) {
    if (0 < DebugLevel) {
      printk("UidMacTable not init yet, so cannot do dump!\n");
      return 0;
    }
    uVar1 = 0;
  }
  else {
    iVar5 = param_2;
    if (param_2 < 0) {
      param_2 = 0x3f;
      iVar5 = 0;
    }
    if (0 < DebugLevel) {
      printk("%s():\n","dumpUidMacTb");
    }
    pcVar6 = pcVar6 + iVar5 * 4;
    iVar2 = DebugLevel;
    do {
      pcVar6 = pcVar6 + 4;
      for (puVar4 = *(undefined1 **)pcVar6; puVar4 != (undefined1 *)0x0;
          puVar4 = *(undefined1 **)(puVar4 + 0x14)) {
        if (((0 < iVar2) && (printk("UidMac[%d]:\n",iVar5), iVar2 = DebugLevel, 0 < DebugLevel)) &&
           (printk("\tisSrv=%d, uIDAddbyUs=%d, Mac=%02x:%02x:%02x:%02x:%02x:%02x, lastTime=0x%lx, pNext=%p\n"
                   ,*puVar4,puVar4[1],puVar4[8],puVar4[9],puVar4[10],puVar4[0xb],puVar4[0xc],
                   puVar4[0xd],*(undefined4 *)(puVar4 + 0x10),*(undefined4 *)(puVar4 + 0x14)),
           iVar2 = DebugLevel, 0 < DebugLevel)) {
          printk("\tuIDStr=");
          iVar2 = DebugLevel;
        }
        puVar3 = puVar4 + 2;
        do {
          if (0 < iVar2) {
            printk(&_LC12,*puVar3);
            iVar2 = DebugLevel;
          }
          puVar3 = puVar3 + 1;
        } while (puVar3 != puVar4 + 8);
        if (0 < iVar2) {
          printk(&_LC13);
          iVar2 = DebugLevel;
        }
      }
      iVar5 = iVar5 + 1;
    } while (iVar5 <= param_2);
    if (0 < iVar2) {
      printk("\t----EndOfDump!\n");
      return 1;
    }
    uVar1 = 1;
  }
  return uVar1;
}

