// module: mt7915.ko
// function: dumpIPMacTb @ 0x7ac50
// size: 352 bytes
//

void dumpIPMacTb(int param_1,int param_2)

{
  int iVar1;
  undefined4 *puVar2;
  int iVar3;
  char *pcVar4;
  int *piVar5;
  
  pcVar4 = *(char **)(param_1 + 8);
  if (pcVar4 != (char *)0x0) {
    if (*pcVar4 == '\0') {
      if (0 < DebugLevel) {
        printk("%s():IPMacTable not init yet, so cannot do dump!\n","dumpIPMacTb");
        return;
      }
    }
    else {
      iVar3 = param_2;
      if (param_2 < 0) {
        param_2 = 0x40;
        iVar3 = 0;
      }
      if (0 < DebugLevel) {
        printk("%s():\n","dumpIPMacTb");
      }
      piVar5 = (int *)(pcVar4 + iVar3 * 4);
      iVar1 = DebugLevel;
      do {
        piVar5 = piVar5 + 1;
        for (puVar2 = (undefined4 *)*piVar5; puVar2 != (undefined4 *)0x0;
            puVar2 = (undefined4 *)puVar2[4]) {
          if ((0 < iVar1) && (printk("IPMac[%d]:\n",iVar3), iVar1 = DebugLevel, 0 < DebugLevel)) {
            printk("\t:IP=0x%x,Mac=%02x:%02x:%02x:%02x:%02x:%02x, lastTime=0x%lx, next=%p\n",*puVar2
                   ,*(undefined1 *)(puVar2 + 1),*(undefined1 *)((int)puVar2 + 5),
                   *(undefined1 *)((int)puVar2 + 6),*(undefined1 *)((int)puVar2 + 7),
                   *(undefined1 *)(puVar2 + 2),*(undefined1 *)((int)puVar2 + 9),puVar2[3],puVar2[4])
            ;
            iVar1 = DebugLevel;
          }
        }
        iVar3 = iVar3 + 1;
      } while (iVar3 <= param_2);
      if (0 < iVar1) {
        printk("\t----EndOfDump!\n");
        return;
      }
    }
  }
  return;
}

