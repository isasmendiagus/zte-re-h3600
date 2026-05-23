// module: mt7915.ko
// function: dumpIPv6MacTb @ 0x7ca64
// size: 488 bytes
//

undefined4 dumpIPv6MacTb(int param_1,int param_2)

{
  undefined4 uVar1;
  int iVar2;
  ushort *puVar3;
  int iVar4;
  char *pcVar5;
  
  pcVar5 = *(char **)(param_1 + 0xc);
  if ((pcVar5 == (char *)0x0) || (*pcVar5 == '\0')) {
    if (DebugLevel < 1) {
      uVar1 = 0;
    }
    else {
      printk("%s():IPv6MacTable not init yet, so cannot do dump!\n","dumpIPv6MacTb");
      uVar1 = 0;
    }
  }
  else {
    iVar4 = param_2;
    if (param_2 < 0) {
      param_2 = 0x40;
      iVar4 = 0;
    }
    if (0 < DebugLevel) {
      printk("%s():\n","dumpIPv6MacTb");
    }
    pcVar5 = pcVar5 + iVar4 * 4;
    iVar2 = DebugLevel;
    do {
      pcVar5 = pcVar5 + 4;
      for (puVar3 = *(ushort **)pcVar5; puVar3 != (ushort *)0x0; puVar3 = *(ushort **)(puVar3 + 0xe)
          ) {
        if ((0 < iVar2) && (printk("IPv6Mac[%d]:\n",iVar4), iVar2 = DebugLevel, 0 < DebugLevel)) {
          printk("\t:IPv6=%04x:%04x:%04x:%04x:%04x:%04x:%04x:%04x,Mac=%02x:%02x:%02x:%02x:%02x:%02x, lastTime=0x%lx, next=%p\n"
                 ,*puVar3 << 8 | *puVar3 >> 8,puVar3[1] << 8 | puVar3[1] >> 8,
                 puVar3[2] << 8 | puVar3[2] >> 8,puVar3[3] << 8 | puVar3[3] >> 8,
                 puVar3[4] << 8 | puVar3[4] >> 8,puVar3[5] << 8 | puVar3[5] >> 8,
                 puVar3[6] << 8 | puVar3[6] >> 8,puVar3[7] << 8 | puVar3[7] >> 8,(char)puVar3[8],
                 *(undefined1 *)((int)puVar3 + 0x11),(char)puVar3[9],
                 *(undefined1 *)((int)puVar3 + 0x13),(char)puVar3[10],
                 *(undefined1 *)((int)puVar3 + 0x15),*(undefined4 *)(puVar3 + 0xc),
                 *(undefined4 *)(puVar3 + 0xe));
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

