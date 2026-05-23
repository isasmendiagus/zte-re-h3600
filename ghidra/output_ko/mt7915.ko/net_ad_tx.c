// module: mt7915.ko
// function: net_ad_tx @ 0x25a4b8
// size: 1128 bytes
//

undefined4 net_ad_tx(int param_1,undefined4 param_2,int param_3)

{
  char cVar1;
  char cVar2;
  char cVar3;
  char cVar4;
  char cVar5;
  char cVar6;
  byte bVar7;
  undefined1 uVar8;
  int iVar9;
  int iVar10;
  undefined4 uVar11;
  undefined1 uVar12;
  int iVar13;
  int *piVar14;
  uint uVar15;
  int iVar16;
  int iVar17;
  int iVar18;
  int iVar19;
  int iVar20;
  bool bVar21;
  bool bVar22;
  bool bVar23;
  undefined2 local_64;
  undefined1 local_62;
  undefined1 local_61;
  undefined1 local_5f;
  ushort local_5c;
  undefined1 local_5a;
  undefined1 local_59;
  undefined1 local_58;
  undefined4 local_54;
  undefined1 local_50;
  undefined1 local_4f;
  undefined1 local_4c;
  undefined1 local_4b;
  undefined1 local_49;
  undefined1 local_46;
  undefined1 local_45;
  undefined1 local_44;
  undefined1 local_43;
  undefined1 local_42;
  char local_41;
  char local_40;
  undefined1 local_3f;
  undefined1 local_3e;
  byte local_39;
  undefined1 local_38;
  undefined1 local_37;
  undefined1 local_36;
  undefined1 local_35;
  undefined1 local_34;
  undefined1 local_32;
  undefined2 local_30;
  undefined2 local_2e;
  char local_2a;
  undefined1 local_29;
  
  iVar9 = hc_get_arch_ops(*(undefined4 *)(param_1 + 0xa797a0));
  iVar10 = HcGetBandByWdev(param_2);
  piVar14 = *(int **)(param_3 + 0x40);
  if (piVar14 != (int *)0x0) {
    iVar13 = *piVar14;
    *piVar14 = 0;
    *(int *)(param_3 + 0x40) = iVar13;
    if (iVar13 == 0) {
      *(undefined4 *)(param_3 + 0x44) = 0;
    }
    *(int *)(param_3 + 0x48) = *(int *)(param_3 + 0x48) + -1;
  }
  *(int **)(param_3 + 0xc) = piVar14;
  *(undefined2 *)((int)piVar14 + 0x42) = 0;
  iVar13 = *(int *)(param_3 + 0xc);
  *(undefined2 *)(param_3 + 0x1e) = *(undefined2 *)(iVar13 + 0x42);
  RTMP_QueryPacketInfo(iVar13,&local_64,param_3 + 0x24,param_3 + 0x28);
  uVar15 = *(uint *)(param_3 + 0x18);
  *(uint *)(param_3 + 0x18) = uVar15 | 0x100000;
  if (*(char *)(iVar13 + 0x2e) != '\0') {
    *(uint *)(param_3 + 0x18) = uVar15 | 0x100100;
  }
  uVar15 = hc_get_asic_cap(*(undefined4 *)(param_1 + 0xa797a0));
  if ((uVar15 & 0x40) != 0) {
    uVar15 = (uint)*(byte *)(param_3 + 5);
    bVar23 = 3 < uVar15;
    bVar21 = uVar15 != 4;
    if (bVar21) {
      bVar23 = uVar15 != 1;
    }
    bVar22 = uVar15 == 2;
    if (!bVar23 || (!bVar21 || bVar22)) {
      uVar15 = *(uint *)(param_3 + 0x18);
    }
    if (!bVar23 || (!bVar21 || bVar22)) {
      uVar15 = uVar15 | 0x800000;
    }
    if (!bVar23 || (!bVar21 || bVar22)) {
      *(uint *)(param_3 + 0x18) = uVar15;
    }
  }
  *(undefined4 *)(param_3 + 0x30) = *(undefined4 *)(param_3 + 0x24);
  iVar19 = *(int *)(param_1 + 0xa77bb8);
  iVar17 = iVar19 + iVar10 * 0xd18;
  cVar1 = *(char *)(iVar17 + 0x838);
  iVar20 = *(int *)(iVar17 + 0x504);
  iVar13 = *(int *)(iVar17 + 0x10f0);
  cVar2 = *(char *)(iVar17 + 0x839);
  cVar3 = *(char *)(iVar17 + 0x83a);
  if (iVar20 == 0) {
    printk("%s: cannot get wdev\n","net_ad_fill_tmac_info");
    return 0x60a;
  }
  iVar16 = iVar19 + iVar10 * 0xd18 + 0x530;
  *(undefined2 *)(iVar17 + 0x6d6) = 0x18;
  cVar4 = *(char *)(iVar17 + 0x1139);
  iVar18 = *(int *)(iVar17 + 0x1128);
  cVar5 = *(char *)(iVar17 + 0x1135);
  cVar6 = *(char *)(iVar17 + 0x1138);
  sys_ad_zero_mem(&local_64,0x3c);
  local_3f = 1;
  if (iVar13 == 0) {
    local_50 = 0;
    local_62 = (undefined1)*(undefined2 *)(iVar17 + 0x6d6);
    local_64 = (undefined2)*(undefined4 *)(iVar17 + 0x6dc);
    local_39 = *(byte *)(iVar16 + 1) & 1;
LAB_0025a868:
    bVar23 = false;
    local_5a = 0;
  }
  else {
    local_62 = (undefined1)*(undefined4 *)(iVar17 + 0x830);
    bVar23 = cVar2 == '\0';
    bVar21 = cVar1 == '\0';
    local_64 = (undefined2)*(int *)(iVar17 + 0x82c);
    if (cVar3 == '\0' && (bVar23 && bVar21)) {
      local_50 = 0;
      uVar12 = 0;
    }
    else {
      uVar12 = 2;
      iVar16 = *(int *)(iVar17 + 0x82c);
    }
    local_3e = 0;
    if (cVar3 == '\0' && (bVar23 && bVar21)) {
      local_39 = *(byte *)(iVar16 + 1) & 1;
      local_59 = uVar12;
    }
    else {
      local_39 = 0;
      local_59 = 0;
      local_50 = uVar12;
    }
    if (cVar3 == '\0') goto LAB_0025a868;
    bVar23 = true;
    local_5a = 1;
  }
  local_30 = 2;
  local_2a = cVar4;
  if (cVar4 == '\0') {
    local_2a = '\x01';
  }
  local_2e = 8;
  local_58 = *(undefined1 *)(iVar20 + 0x29);
  local_4f = 0;
  local_54 = 0;
  local_4b = 0;
  if ((*(int *)("Set_RBIST_Capture_Start" + param_1 + 0x10) != 0) &&
     (*(char *)(*(int *)("Set_RBIST_Capture_Start" + param_1 + 0x10) + 1) == '\x01')) {
    local_49 = 1;
  }
  local_29 = (undefined1)iVar10;
  if (iVar18 == 0) {
    local_4b = 1;
LAB_0025a878:
    local_5f = *(undefined1 *)(iVar10 * 0xd18 + iVar19 + 0x50d);
  }
  else {
    local_4c = (undefined1)iVar18;
    if (iVar18 == 2) goto LAB_0025a878;
    local_5f = *(undefined1 *)(iVar10 * 0xd18 + iVar19 + 0x50d);
    if (iVar18 < 0) goto LAB_0025a740;
  }
  if (iVar18 == test_ant_to_spe_idx_map._0_4_) {
    iVar13 = 0;
LAB_0025a8f8:
    local_4c = (undefined1)*(undefined4 *)(test_ant_to_spe_idx_map + iVar13 + 4);
  }
  else {
    iVar17 = 1;
    do {
      iVar20 = iVar17 * 8;
      iVar13 = iVar17 << 3;
      iVar17 = iVar17 + 1;
      if (iVar18 == *(int *)(test_ant_to_spe_idx_map + iVar20)) goto LAB_0025a8f8;
    } while (iVar17 != 0x10);
    local_4c = 0;
  }
LAB_0025a740:
  iVar13 = iVar10 * 0xd18 + iVar19;
  local_43 = *(undefined1 *)(iVar13 + 0x1137);
  local_46 = *(undefined1 *)(iVar13 + 0x113c);
  local_44 = *(undefined1 *)(iVar13 + 0x113a);
  local_45 = *(undefined1 *)(iVar13 + 0x113b);
  local_41 = cVar6;
  local_40 = cVar5;
  local_61 = asic_get_hwq_from_ac(param_1,local_5f,*(undefined1 *)(iVar13 + 0x50e));
  local_38 = !bVar23;
  if ((bool)local_38) {
    local_32 = 0xf;
    bVar7 = *(byte *)(iVar13 + 0x510);
  }
  else {
    bVar7 = *(byte *)(iVar13 + 0x510);
    local_32 = 1;
  }
  if (*(char *)(iVar10 * 0xd18 + iVar19 + 0x1114) != '\0') {
    local_36 = 1;
    local_34 = 1;
    local_35 = 0;
  }
  uVar12 = local_42;
  if (cVar5 == '\0') {
    if (cVar6 == '\t') {
      local_41 = '\0';
    }
    local_42 = 1;
    uVar8 = 0;
    uVar12 = uVar8;
    if (cVar6 != '\t') {
      if (cVar6 == '\n') {
        local_41 = '\x01';
      }
      else {
        uVar12 = local_42;
        if (cVar6 == '\v') {
          local_41 = '\x02';
          uVar12 = uVar8;
        }
      }
    }
  }
  local_42 = uVar12;
  local_5c = (ushort)bVar7;
  local_37 = local_38;
  uVar11 = (**(code **)(iVar9 + 0x188))(param_1,&local_64,param_3);
  return uVar11;
}

