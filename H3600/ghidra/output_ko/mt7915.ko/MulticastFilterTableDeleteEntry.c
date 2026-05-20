// module: mt7915.ko
// function: MulticastFilterTableDeleteEntry @ 0x2404bc
// size: 604 bytes
//

undefined4
MulticastFilterTableDeleteEntry
          (int param_1,byte *param_2,undefined4 param_3,int param_4,int param_5)

{
  int iVar1;
  char *pcVar2;
  char *pcVar3;
  char *pcVar4;
  char *pcVar5;
  uint uVar6;
  char *pcVar7;
  
  pcVar5 = *(char **)(param_1 + 0xa77bc4);
  if (pcVar5 == (char *)0x0) {
    if (-1 < DebugLevel) {
      printk("%s Multicase filter table is not ready.\n","MulticastFilterTableDeleteEntry");
    }
    return 0;
  }
  _raw_spin_lock_bh(pcVar5 + 0xc04);
  uVar6 = (byte)(param_2[1] ^ *param_2 ^ param_2[2] ^ param_2[3] ^ param_2[4] ^ param_2[5]) & 0x7f;
  pcVar7 = *(char **)(pcVar5 + uVar6 * 4 + 4);
  if (pcVar7 == (char *)0x0) {
LAB_0024065c:
    if (-1 < DebugLevel) {
      printk("%s: the Group doesn\'t exist.\n","MulticastFilterTableDeleteEntry");
    }
    goto LAB_00240628;
  }
  pcVar4 = pcVar7;
  pcVar3 = pcVar7;
  if (*pcVar7 == '\0') {
    if (param_4 != 0) goto LAB_002405a8;
  }
  else {
    do {
      pcVar2 = pcVar4;
      if ((*(int *)(pcVar2 + 0xc) == param_5) &&
         (iVar1 = memcmp(pcVar2 + 0x10,param_2,6), pcVar4 = pcVar2, iVar1 == 0)) break;
      pcVar4 = *(char **)(pcVar2 + 0x24);
      if (pcVar4 == (char *)0x0) goto LAB_0024065c;
      pcVar3 = pcVar2;
    } while (*pcVar4 != '\0');
    if (param_4 != 0) {
LAB_002405a8:
      FUN_002400ac(pcVar5,pcVar4 + 0x18,param_4);
      if (pcVar4[0x20] != '\0') goto LAB_00240628;
      pcVar7 = *(char **)(pcVar5 + uVar6 * 4 + 4);
    }
    if (pcVar7 != pcVar4) {
      *(undefined4 *)(pcVar3 + 0x24) = *(undefined4 *)(pcVar4 + 0x24);
      FUN_0023ff78(pcVar5,pcVar4 + 0x18);
      __memzero(pcVar4,0x28);
      *pcVar5 = *pcVar5 + -1;
      if (2 < DebugLevel) {
        printk("MCastFilterTableDeleteEntry 2 - Total= %d\n");
      }
      goto LAB_00240628;
    }
  }
  *(undefined4 *)(pcVar5 + uVar6 * 4 + 4) = *(undefined4 *)(pcVar7 + 0x24);
  FUN_0023ff78(pcVar5,pcVar7 + 0x18);
  __memzero(pcVar7,0x28);
  *pcVar5 = *pcVar5 + -1;
  if (2 < DebugLevel) {
    printk("MCastFilterTableDeleteEntry 1 - Total= %d\n");
  }
LAB_00240628:
  _raw_spin_unlock_bh(pcVar5 + 0xc04);
  return 1;
}

