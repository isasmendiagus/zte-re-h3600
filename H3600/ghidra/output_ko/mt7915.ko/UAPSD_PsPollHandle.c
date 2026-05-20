// module: mt7915.ko
// function: UAPSD_PsPollHandle @ 0x1de490
// size: 740 bytes
//

/* WARNING: Removing unreachable block (ram,0x001de508) */
/* WARNING: Removing unreachable block (ram,0x001de51c) */
/* WARNING: Removing unreachable block (ram,0x001de54c) */
/* WARNING: Removing unreachable block (ram,0x001de73c) */

undefined4 UAPSD_PsPollHandle(int param_1,int param_2)

{
  ushort uVar1;
  ushort uVar2;
  undefined1 uVar3;
  bool bVar4;
  int *piVar5;
  uint uVar6;
  int iVar7;
  int iVar8;
  int *piVar9;
  int iVar10;
  int *piVar11;
  int iVar12;
  int iVar13;
  undefined4 local_3c;
  int local_38 [4];
  int iStack_28;
  
  local_38[0] = 1;
  local_38[1] = 0;
  local_38[2] = 2;
  local_38[3] = 3;
  iVar10 = *(int *)("Get_RBIST_Raw_Data_Proc" + param_1 + 0x14);
  local_3c = 0x3020001;
  if (param_2 == 0) {
    return 0;
  }
  _raw_spin_lock_bh();
  if ((*(char *)(param_2 + 0xb16) == '\0') || (*(char *)(param_2 + 0xb63) != '\0')) {
    _raw_spin_unlock_bh("BssTableSortByRssi" + param_1 + 0x10);
    return 0;
  }
  piVar5 = &iStack_28;
  iVar12 = param_1 + (uint)*(ushort *)(param_2 + 0xe0) * 0x620 + 0x2f6a0;
  uVar6 = 0;
  piVar11 = (int *)0x0;
  do {
    piVar5 = piVar5 + -1;
    iVar7 = *piVar5;
    iVar13 = param_2 + iVar7 * 0x10;
    piVar9 = *(int **)(iVar13 + 0xb18);
    if (piVar9 != (int *)0x0) {
      if (piVar11 == (int *)0x0) {
        iVar8 = *piVar9;
        *piVar9 = 0;
        *(int *)(iVar13 + 0xb18) = iVar8;
        uVar6 = (uint)*(byte *)((int)local_38 + iVar7 + -4);
        if (iVar8 == 0) {
          *(undefined4 *)(iVar13 + 0xb1c) = 0;
        }
        *(int *)(iVar13 + 0xb20) = *(int *)(iVar13 + 0xb20) + -1;
        *(byte *)((int)piVar9 + 0x32) = ~((byte)~(byte)((uVar6 << 0x19) >> 0x18) >> 1);
        *(undefined1 *)((int)piVar9 + 0x2f) = 1;
        *(undefined1 *)((int)piVar9 + 0x36) = 2;
        piVar11 = piVar9;
        if (*(int *)(iVar13 + 0xb18) == 0) goto LAB_001de690;
      }
      iVar12 = ge_enq_req(param_1,piVar11,uVar6,iVar12,0);
      if (iVar12 != 0) goto LAB_001de5d4;
      bVar4 = false;
      goto LAB_001de74c;
    }
LAB_001de690:
  } while (piVar5 != local_38);
  if (piVar11 == (int *)0x0) {
    bVar4 = true;
  }
  else {
    *(undefined1 *)((int)piVar11 + 0x2f) = 0;
    iVar12 = ge_enq_req(param_1,piVar11,uVar6,iVar12,0);
    bVar4 = true;
    if (iVar12 == 0) {
LAB_001de74c:
      RTMPFreeNdisPacket(param_1,piVar11);
    }
  }
  uVar1 = *(ushort *)(param_2 + 0xf8);
  if (*(char *)(param_2 + 0xb16) != '\x01') {
    bVar4 = false;
  }
  uVar2 = *(ushort *)(param_2 + 0xe0);
  if ((bVar4) && (uVar6 = HcGetMaxStaNum(param_1), uVar2 < uVar6)) {
    iVar12 = (uint)*(byte *)(param_2 + 0xe4) * 0x5834 + param_1 + (((uint)uVar1 << 0x15) >> 0x18);
    "vow_watf_q_lv1: %d\n"[iVar12 + 0x13] =
         "vow_watf_q_lv1: %d\n"[iVar12 + 0x13] & ~*(byte *)((int)&NUM_BIT8 + (uVar1 & 7));
  }
LAB_001de5d4:
  *(undefined2 *)(param_2 + 0xb58) = 0;
  _raw_spin_unlock_bh();
  uVar3 = hif_get_resource_idx(*(undefined4 *)(param_1 + 0xa797a0),*(undefined4 *)(param_2 + 8),0,0)
  ;
  (**(code **)(iVar10 + 0x3c))(param_1,uVar3);
  return 1;
}

