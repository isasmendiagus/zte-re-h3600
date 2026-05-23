// module: mt7915.ko
// function: dumpSesMacTb @ 0x7bc50
// size: 404 bytes
//

undefined4 dumpSesMacTb(int param_1,int param_2)

{
  undefined4 uVar1;
  int iVar2;
  undefined2 *puVar3;
  int iVar4;
  char *pcVar5;
  
  pcVar5 = *(char **)(param_1 + 0x10);
  if ((pcVar5 == (char *)0x0) || (*pcVar5 == '\0')) {
    if (DebugLevel < 1) {
      uVar1 = 0;
    }
    else {
      printk("SesMacTable not init yet, so cannot do dump!\n");
      uVar1 = 0;
    }
  }
  else {
    iVar4 = param_2;
    if (param_2 < 0) {
      param_2 = 0x3f;
      iVar4 = 0;
    }
    if (0 < DebugLevel) {
      printk("%s():\n","dumpSesMacTb");
    }
    pcVar5 = pcVar5 + iVar4 * 4;
    iVar2 = DebugLevel;
    do {
      pcVar5 = pcVar5 + 4;
      for (puVar3 = *(undefined2 **)pcVar5; puVar3 != (undefined2 *)0x0;
          puVar3 = *(undefined2 **)(puVar3 + 10)) {
        if ((0 < iVar2) && (printk("SesMac[%d]:\n",iVar4), iVar2 = DebugLevel, 0 < DebugLevel)) {
          printk("\tsesID=%d,inMac=%02x:%02x:%02x:%02x:%02x:%02x,outMac=%02x:%02x:%02x:%02x:%02x:%02x,lastTime=0x%lx, pNext=%p\n"
                 ,*puVar3,*(undefined1 *)(puVar3 + 4),*(undefined1 *)((int)puVar3 + 9),
                 *(undefined1 *)(puVar3 + 5),*(undefined1 *)((int)puVar3 + 0xb),
                 *(undefined1 *)(puVar3 + 6),*(undefined1 *)((int)puVar3 + 0xd),
                 *(undefined1 *)(puVar3 + 1),*(undefined1 *)((int)puVar3 + 3),
                 *(undefined1 *)(puVar3 + 2),*(undefined1 *)((int)puVar3 + 5),
                 *(undefined1 *)(puVar3 + 3),*(undefined1 *)((int)puVar3 + 7),
                 *(undefined4 *)(puVar3 + 8),*(undefined4 *)(puVar3 + 10));
          iVar2 = DebugLevel;
        }
      }
      iVar4 = iVar4 + 1;
    } while (iVar4 <= param_2);
    if (iVar2 < 1) {
      uVar1 = 1;
    }
    else {
      printk("\t----EndOfDump!\n");
      uVar1 = 1;
    }
  }
  return uVar1;
}

