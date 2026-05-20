// module: mt7915.ko
// function: BndStrg_DeleteEntry_UnLock @ 0x9c658
// size: 528 bytes
//

undefined4 BndStrg_DeleteEntry_UnLock(int param_1,byte *param_2,uint param_3)

{
  byte bVar1;
  byte bVar2;
  byte bVar3;
  byte bVar4;
  byte bVar5;
  byte bVar6;
  char *pcVar7;
  char *pcVar8;
  int iVar9;
  char *pcVar10;
  uint uVar11;
  char *pcVar12;
  char *__s2;
  
  bVar1 = *param_2;
  bVar2 = param_2[1];
  bVar3 = param_2[2];
  bVar4 = param_2[3];
  bVar5 = param_2[4];
  bVar6 = param_2[5];
  uVar11 = (uint)(byte)(bVar2 ^ bVar1 ^ bVar3 ^ bVar4 ^ bVar5 ^ bVar6);
  if (param_3 < 0x80) {
    iVar9 = param_1 + param_3 * 0x18 + 0x10;
    pcVar10 = (char *)(iVar9 + 4);
    if (pcVar10 == (char *)0x0) {
      return 0;
    }
    if (*(char *)(param_1 + param_3 * 0x18 + 0x14) == '\0') {
      return 0;
    }
    pcVar12 = *(char **)(param_1 + (uVar11 + 0x304) * 4 + 4);
    if (pcVar12 != (char *)0x0) {
      __s2 = (char *)(iVar9 + 0xc);
      goto LAB_0009c750;
    }
    __s2 = (char *)(iVar9 + 0xc);
    printk(&_LC36,0x2c8);
    dump_stack();
  }
  else {
    pcVar12 = *(char **)(param_1 + (uVar11 + 0x304) * 4 + 4);
    pcVar10 = pcVar12;
    while( true ) {
      if (pcVar10 == (char *)0x0) {
        if (1 < DebugLevel) {
          printk("%s(): Index=%u, %02x:%02x:%02x:%02x:%02x:%02x, Entry not found.\n",
                 "BndStrg_DeleteEntry_UnLock",param_3,bVar1,bVar2,bVar3,bVar4,bVar5,bVar6);
          return 1;
        }
        return 1;
      }
      __s2 = pcVar10 + 8;
      iVar9 = memcmp(param_2,__s2,6);
      if (iVar9 == 0) break;
      pcVar10 = *(char **)(pcVar10 + 0x14);
    }
    if (*pcVar10 == '\0') {
      return 0;
    }
LAB_0009c750:
    if (pcVar12 == pcVar10) {
LAB_0009c814:
      *(undefined4 *)(param_1 + (uVar11 + 0x304) * 4 + 4) = *(undefined4 *)(pcVar10 + 0x14);
      goto LAB_0009c794;
    }
    pcVar8 = *(char **)(pcVar12 + 0x14);
    while (pcVar7 = pcVar8, pcVar7 != (char *)0x0) {
      if (pcVar7 == pcVar10) {
        if (pcVar12 == (char *)0x0) goto LAB_0009c814;
        *(undefined4 *)(pcVar12 + 0x14) = *(undefined4 *)(pcVar10 + 0x14);
        goto LAB_0009c794;
      }
      pcVar12 = pcVar7;
      pcVar8 = *(char **)(pcVar7 + 0x14);
    }
  }
  printk(&_LC37,0x2dd);
  dump_stack();
LAB_0009c794:
  __memzero(__s2,6);
  pcVar10[0x14] = '\0';
  pcVar10[0x15] = '\0';
  pcVar10[0x16] = '\0';
  pcVar10[0x17] = '\0';
  *pcVar10 = '\0';
  *(int *)(param_1 + 8) = *(int *)(param_1 + 8) + -1;
  return 0;
}

