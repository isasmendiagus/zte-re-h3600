// module: mt7915.ko
// function: MeasureReqInsert @ 0x13e718
// size: 604 bytes
//

char * MeasureReqInsert(int param_1,uint param_2)

{
  char *pcVar1;
  char *pcVar2;
  char *pcVar3;
  undefined4 *puVar4;
  int iVar5;
  undefined4 *puVar6;
  char *pcVar7;
  char *pcVar8;
  undefined1 auStack_29 [5];
  
  pcVar8 = *(char **)(param_1 + 0x795978);
  if (pcVar8 == (char *)0x0) {
    if (DebugLevel < 0) {
      return (char *)0x0;
    }
    printk("%s: pMeasureReqTab doesn\'t exist.\n","MeasureReqInsert");
    return (char *)0x0;
  }
  pcVar2 = (char *)MeasureReqLookUp();
  if (pcVar2 != (char *)0x0) {
    return pcVar2;
  }
  _raw_spin_lock_bh(param_1 + 0x795974);
  iVar5 = 0;
  pcVar2 = pcVar8;
  do {
    pcVar7 = pcVar2 + 0x84;
    if (pcVar2[0x8c] == '\x01') {
      if (((500 - jiffies) + *(int *)(pcVar2 + 0x88) < 0) && (pcVar2[0x91] == '\0')) {
        pcVar3 = *(char **)(pcVar8 + ((byte)pcVar8[iVar5 * 0x84 + 0x8d] & 0x1f) * 4 + 4);
        if (pcVar3 == pcVar7) goto LAB_0013e960;
        pcVar1 = *(char **)pcVar3;
        goto joined_r0x0013e81c;
      }
    }
    else if (pcVar2[0x8c] == '\0') goto LAB_0013e8bc;
    iVar5 = iVar5 + 1;
    pcVar2 = pcVar7;
  } while (iVar5 != 0x20);
  pcVar7 = (char *)0x0;
  if (-1 < DebugLevel) {
    printk("%s: pMeasureReqTab tab full.\n","MeasureReqInsert");
  }
LAB_0013e920:
  _raw_spin_unlock_bh(param_1 + 0x795974);
  return pcVar7;
joined_r0x0013e81c:
  if (pcVar1 == (char *)0x0) goto LAB_0013e858;
  if (pcVar7 == pcVar1) {
    if (pcVar3 == (char *)0x0) {
LAB_0013e960:
      *(undefined4 *)(pcVar8 + ((byte)pcVar8[iVar5 * 0x84 + 0x8d] & 0x1f) * 4 + 4) =
           *(undefined4 *)(pcVar8 + iVar5 * 0x84 + 0x84);
    }
    else {
      *(undefined4 *)pcVar3 = *(undefined4 *)(pcVar8 + iVar5 * 0x84 + 0x84);
    }
    goto LAB_0013e858;
  }
  pcVar3 = pcVar1;
  pcVar1 = *(char **)pcVar1;
  goto joined_r0x0013e81c;
LAB_0013e858:
  RTMPCancelTimer(pcVar8 + iVar5 * 0x84 + 0xd4,auStack_29);
  RTMPReleaseTimer(pcVar8 + iVar5 * 0x84 + 0xd4,auStack_29);
  RTMPCancelTimer(pcVar8 + iVar5 * 0x84 + 0x98,auStack_29);
  RTMPReleaseTimer(pcVar8 + iVar5 * 0x84 + 0x98,auStack_29);
  __memzero(pcVar7,0x84);
  *pcVar8 = *pcVar8 + -1;
LAB_0013e8bc:
  iVar5 = jiffies;
  pcVar2[0x8d] = (char)param_2;
  pcVar2[0x8c] = '\x01';
  *(int *)(pcVar2 + 0x88) = iVar5;
  pcVar2[0x91] = '\0';
  *pcVar8 = *pcVar8 + '\x01';
  if (pcVar7 != (char *)0x0) {
    puVar6 = *(undefined4 **)(pcVar8 + (param_2 & 0x1f) * 4 + 4);
    if (*(undefined4 **)(pcVar8 + (param_2 & 0x1f) * 4 + 4) == (undefined4 *)0x0) {
      *(char **)(pcVar8 + (param_2 & 0x1f) * 4 + 4) = pcVar7;
    }
    else {
      do {
        puVar4 = puVar6;
        puVar6 = (undefined4 *)*puVar4;
      } while (puVar6 != (undefined4 *)0x0);
      *puVar4 = pcVar7;
    }
  }
  goto LAB_0013e920;
}

