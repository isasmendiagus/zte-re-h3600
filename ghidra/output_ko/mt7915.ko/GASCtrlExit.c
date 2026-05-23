// module: mt7915.ko
// function: GASCtrlExit @ 0x22c8d4
// size: 496 bytes
//

void GASCtrlExit(int param_1)

{
  char cVar1;
  char *pcVar2;
  char *pcVar3;
  char *pcVar4;
  char *pcVar5;
  char *pcVar6;
  uint uVar7;
  int iVar8;
  char *pcVar9;
  char *pcVar10;
  uint uVar11;
  int iVar12;
  uint local_40;
  undefined1 auStack_29 [5];
  
  local_40 = 0;
  while( true ) {
    uVar11 = local_40 & 0xff;
    uVar7 = hc_get_chip_bcn_max_num(*(undefined4 *)(param_1 + 0xa797a0));
    if (uVar7 <= uVar11) break;
    iVar8 = uVar11 * 0x5834;
    pcVar10 = "RT_OID_WSC_SET_PROFILE:: ProfileCnt = %d\n" + param_1 + iVar8 + 0x1c;
    _raw_spin_lock_bh("RT_OID_WSC_SET_PROFILE:: ProfileCnt = %d\n" + param_1 + iVar8 + 0x24);
    pcVar5 = *(char **)*(char **)("RT_OID_WSC_SET_PROFILE:: ProfileCnt = %d\n" +
                                 param_1 + iVar8 + 0x1c);
    pcVar4 = *(char **)("RT_OID_WSC_SET_PROFILE:: ProfileCnt = %d\n" + param_1 + iVar8 + 0x1c);
    while (pcVar2 = pcVar5, pcVar10 != pcVar4) {
      if (pcVar2 != (char *)0x0) {
        *(undefined4 *)(pcVar2 + 4) = *(undefined4 *)(pcVar4 + 4);
      }
      if (*(undefined4 **)(pcVar4 + 4) != (undefined4 *)0x0) {
        **(undefined4 **)(pcVar4 + 4) = *(undefined4 *)pcVar4;
      }
      pcVar4[0] = '\0';
      pcVar4[1] = '\0';
      pcVar4[2] = '\0';
      pcVar4[3] = '\0';
      pcVar4[4] = '\0';
      pcVar4[5] = '\0';
      pcVar4[6] = '\0';
      pcVar4[7] = '\0';
      pcVar9 = pcVar4 + 0x108;
      pcVar6 = *(char **)*(char **)pcVar9;
      pcVar5 = *(char **)pcVar9;
      while (pcVar3 = pcVar6, pcVar5 != pcVar9) {
        if (pcVar3 != (char *)0x0) {
          *(undefined4 *)(pcVar3 + 4) = *(undefined4 *)(pcVar5 + 4);
        }
        if (*(undefined4 **)(pcVar5 + 4) != (undefined4 *)0x0) {
          **(undefined4 **)(pcVar5 + 4) = *(undefined4 *)pcVar5;
        }
        pcVar5[0] = '\0';
        pcVar5[1] = '\0';
        pcVar5[2] = '\0';
        pcVar5[3] = '\0';
        pcVar5[4] = '\0';
        pcVar5[5] = '\0';
        pcVar5[6] = '\0';
        pcVar5[7] = '\0';
        os_free_mem(*(undefined4 *)(pcVar5 + 0xc));
        os_free_mem(pcVar5);
        pcVar6 = *(char **)pcVar3;
        pcVar5 = pcVar3;
      }
      *(char **)(pcVar4 + 0x108) = pcVar9;
      *(char **)(pcVar4 + 0x10c) = pcVar9;
      if (pcVar4[0x50] == '\0') {
        cVar1 = pcVar4[0x88];
      }
      else {
        RTMPCancelTimer(pcVar4 + 0x1c,auStack_29);
        cVar1 = pcVar4[0x88];
        pcVar4[0x50] = '\0';
      }
      if (cVar1 != '\0') {
        RTMPCancelTimer(pcVar4 + 0x54,auStack_29);
        pcVar4[0x88] = '\0';
      }
      RTMPReleaseTimer(pcVar4 + 0x1c,auStack_29);
      RTMPReleaseTimer(pcVar4 + 0x54,auStack_29);
      os_free_mem(pcVar4);
      pcVar5 = *(char **)pcVar2;
      pcVar4 = pcVar2;
    }
    iVar12 = uVar11 * 0x5834 + param_1;
    local_40 = local_40 + 1;
    *(char **)("RT_OID_WSC_SET_PROFILE:: ProfileCnt = %d\n" + iVar12 + 0x1c) = pcVar10;
    *(char **)("RT_OID_WSC_SET_PROFILE:: ProfileCnt = %d\n" + iVar12 + 0x20) = pcVar10;
    _raw_spin_unlock_bh("RT_OID_WSC_SET_PROFILE:: ProfileCnt = %d\n" + param_1 + iVar8 + 0x24);
  }
  return;
}

