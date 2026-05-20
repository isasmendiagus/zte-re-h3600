// module: mt7915.ko
// function: WNMCtrlExit @ 0x228784
// size: 972 bytes
//

void WNMCtrlExit(int param_1)

{
  int *piVar1;
  char *pcVar2;
  char *pcVar3;
  char *pcVar4;
  uint uVar5;
  int iVar6;
  int iVar7;
  uint uVar8;
  int *piVar9;
  int *piVar10;
  int *piVar11;
  undefined *puVar12;
  undefined *puVar13;
  char *pcVar14;
  int iVar15;
  int iVar16;
  bool bVar17;
  uint local_40;
  undefined1 auStack_29 [5];
  
  local_40 = 0;
  while( true ) {
    uVar8 = local_40 & 0xff;
    uVar5 = hc_get_chip_bcn_max_num(*(undefined4 *)(param_1 + 0xa797a0));
    if (uVar5 <= uVar8) break;
    iVar6 = param_1 + uVar8 * 0x5834;
    down_interruptible("RT_OID_WSC_SET_CONF_MODE:: WscConfMode = %d\n" + iVar6 + 0x20);
    iVar7 = param_1 + uVar8 * 0x5834;
    piVar10 = (int *)("RT_OID_WSC_SET_MODE::unknown WscMode = %d\n" + iVar7 + 0x28);
    piVar11 = (int *)**(int **)("RT_OID_WSC_SET_MODE::unknown WscMode = %d\n" + iVar7 + 0x28);
    piVar9 = *(int **)("RT_OID_WSC_SET_MODE::unknown WscMode = %d\n" + iVar7 + 0x28);
    while (piVar1 = piVar11, piVar9 != piVar10) {
      RTMPCancelTimer(piVar9 + 0x13,auStack_29);
      RTMPReleaseTimer(piVar9 + 0x13,auStack_29);
      RTMPCancelTimer(piVar9 + 6,auStack_29);
      RTMPReleaseTimer(piVar9 + 6,auStack_29);
      if (*piVar9 != 0) {
        *(int *)(*piVar9 + 4) = piVar9[1];
      }
      if ((int *)piVar9[1] != (int *)0x0) {
        *(int *)piVar9[1] = *piVar9;
      }
      *piVar9 = 0;
      piVar9[1] = 0;
      os_free_mem(piVar9);
      piVar11 = (int *)*piVar1;
      piVar9 = piVar1;
    }
    iVar7 = uVar8 * 0x5834;
    iVar15 = param_1 + iVar7;
    *(int **)("RT_OID_WSC_SET_MODE::unknown WscMode = %d\n" + iVar15 + 0x28) = piVar10;
    *(int **)("RT_OID_WSC_SET_MODE::WscMode = %d\n" + iVar15) = piVar10;
    up("RT_OID_WSC_SET_CONF_MODE:: WscConfMode = %d\n" + iVar6 + 0x20);
    _raw_spin_lock_bh("RT_OID_WSC_SET_MODE::unknown WscMode = %d\n" + param_1 + iVar7 + 0x10);
    pcVar14 = "RT_OID_WSC_SET_MODE::unknown WscMode = %d\n" + param_1 + iVar7 + 0x18;
    pcVar4 = *(char **)*(char **)("RT_OID_WSC_SET_MODE::unknown WscMode = %d\n" + iVar15 + 0x18);
    pcVar3 = *(char **)("RT_OID_WSC_SET_MODE::unknown WscMode = %d\n" + iVar15 + 0x18);
    while (pcVar2 = pcVar4, pcVar3 != pcVar14) {
      if (pcVar2 != (char *)0x0) {
        *(undefined4 *)(pcVar2 + 4) = *(undefined4 *)(pcVar3 + 4);
      }
      if (*(undefined4 **)(pcVar3 + 4) != (undefined4 *)0x0) {
        **(undefined4 **)(pcVar3 + 4) = *(undefined4 *)pcVar3;
      }
      pcVar3[0] = '\0';
      pcVar3[1] = '\0';
      pcVar3[2] = '\0';
      pcVar3[3] = '\0';
      pcVar3[4] = '\0';
      pcVar3[5] = '\0';
      pcVar3[6] = '\0';
      pcVar3[7] = '\0';
      os_free_mem(pcVar3);
      pcVar4 = *(char **)pcVar2;
      pcVar3 = pcVar2;
    }
    iVar15 = uVar8 * 0x5834;
    iVar16 = param_1 + iVar15;
    *(char **)("RT_OID_WSC_SET_MODE::unknown WscMode = %d\n" + iVar16 + 0x18) = pcVar14;
    *(char **)("RT_OID_WSC_SET_MODE::unknown WscMode = %d\n" + iVar16 + 0x1c) = pcVar14;
    _raw_spin_unlock_bh("RT_OID_WSC_SET_MODE::unknown WscMode = %d\n" + param_1 + iVar7 + 0x10);
    _raw_spin_lock_bh("RT_OID_WSC_SET_MODE::unknown WscMode = %d\n" + param_1 + iVar15 + 0x14);
    pcVar14 = "RT_OID_WSC_SET_MODE::unknown WscMode = %d\n" + param_1 + iVar15 + 0x20;
    pcVar4 = *(char **)*(char **)("RT_OID_WSC_SET_MODE::unknown WscMode = %d\n" + iVar16 + 0x20);
    pcVar3 = *(char **)("RT_OID_WSC_SET_MODE::unknown WscMode = %d\n" + iVar16 + 0x20);
    while (pcVar2 = pcVar4, pcVar3 != pcVar14) {
      if (pcVar2 != (char *)0x0) {
        *(undefined4 *)(pcVar2 + 4) = *(undefined4 *)(pcVar3 + 4);
      }
      if (*(undefined4 **)(pcVar3 + 4) != (undefined4 *)0x0) {
        **(undefined4 **)(pcVar3 + 4) = *(undefined4 *)pcVar3;
      }
      pcVar3[0] = '\0';
      pcVar3[1] = '\0';
      pcVar3[2] = '\0';
      pcVar3[3] = '\0';
      pcVar3[4] = '\0';
      pcVar3[5] = '\0';
      pcVar3[6] = '\0';
      pcVar3[7] = '\0';
      os_free_mem(pcVar3);
      pcVar4 = *(char **)pcVar2;
      pcVar3 = pcVar2;
    }
    iVar7 = uVar8 * 0x5834 + param_1;
    local_40 = local_40 + 1;
    *(char **)("RT_OID_WSC_SET_MODE::unknown WscMode = %d\n" + iVar7 + 0x20) = pcVar14;
    *(char **)("RT_OID_WSC_SET_MODE::unknown WscMode = %d\n" + iVar7 + 0x24) = pcVar14;
    _raw_spin_unlock_bh("RT_OID_WSC_SET_MODE::unknown WscMode = %d\n" + param_1 + iVar15 + 0x14);
    FUN_002246f4("RT_OID_WSC_SET_CONF_MODE:: WscConfMode = %d\n" + iVar6 + 0x10);
  }
  puVar12 = &DAT_00580dec + param_1;
  do {
    down_interruptible(puVar12);
    piVar10 = (int *)(puVar12 + 0x3c);
    piVar9 = (int *)*piVar10;
    puVar13 = puVar12 + -0x10;
    piVar11 = (int *)*piVar9;
    if (piVar9 != piVar10) {
      do {
        RTMPCancelTimer(piVar9 + 0x20,auStack_29);
        RTMPReleaseTimer(piVar9 + 0x20,auStack_29);
        if (*piVar9 != 0) {
          *(int *)(*piVar9 + 4) = piVar9[1];
        }
        if ((int *)piVar9[1] != (int *)0x0) {
          *(int *)piVar9[1] = *piVar9;
        }
        *piVar9 = 0;
        piVar9[1] = 0;
        os_free_mem(piVar9);
        bVar17 = piVar11 != piVar10;
        piVar9 = piVar11;
        piVar11 = (int *)*piVar11;
      } while (bVar17);
      piVar9 = *(int **)(puVar12 + 0x3c);
    }
    if (piVar9 != (int *)0x0) {
      piVar9[1] = *(int *)(puVar12 + 0x40);
    }
    if (*(undefined4 **)(puVar12 + 0x40) != (undefined4 *)0x0) {
      **(undefined4 **)(puVar12 + 0x40) = *(undefined4 *)(puVar12 + 0x3c);
    }
    *(undefined4 *)(puVar12 + 0x3c) = 0;
    *(undefined4 *)(puVar12 + 0x40) = 0;
    up(puVar12);
    puVar12 = puVar12 + 0x2137b0;
    FUN_002246f4(puVar13);
  } while (puVar12 != (undefined *)(param_1 + 0x9a7d4c));
  return;
}

