// module: mt7915.ko
// function: build_ht_ies @ 0x1394fc
// size: 1340 bytes
//

int build_ht_ies(int param_1,int *param_2)

{
  ushort uVar1;
  undefined2 uVar2;
  undefined2 uVar3;
  undefined2 uVar4;
  undefined2 uVar5;
  undefined2 uVar6;
  undefined2 uVar7;
  undefined2 uVar8;
  undefined1 uVar9;
  byte bVar10;
  void *pvVar11;
  int iVar12;
  undefined4 uVar13;
  int iVar14;
  int iVar15;
  undefined1 *puVar16;
  int iVar17;
  bool bVar18;
  uint local_42;
  undefined4 local_3e;
  undefined4 local_3a;
  undefined4 local_36;
  undefined4 local_32;
  undefined4 local_2e;
  undefined2 local_2a;
  
  if (*(char *)((int)param_2 + 10) == '\x01') {
    iVar15 = param_2[4];
    puVar16 = (undefined1 *)*param_2;
    pvVar11 = (void *)wlan_operate_get_ht_cap(iVar15);
    bVar10 = wlan_config_get_ht_bw(iVar15);
    memmove(&local_42,pvVar11,0x1a);
    local_42 = CONCAT31(local_42._1_3_,(byte)local_42 & 0xfd | (bVar10 & 1) << 1);
    iVar12 = HcIsBfCapSupport(iVar15);
    if (iVar12 == 0) {
      uVar13 = wlan_config_get_etxbf(iVar15);
      wlan_config_set_etxbf(iVar15,0);
      mt_WrapSetETxBFCap(param_1,iVar15,(int)&local_2e + 1);
      wlan_config_set_etxbf(iVar15,uVar13);
    }
    uVar9 = WpaIe;
    *(undefined4 *)(puVar16 + 2) = 0x334c9000;
    puVar16[1] = 0x1e;
    *puVar16 = uVar9;
    iVar12 = 0x20;
    memmove(puVar16 + 6,&local_42,0x1a);
    goto LAB_00139604;
  }
  iVar15 = param_2[4];
  uVar1 = *(ushort *)(param_2 + 3);
  puVar16 = (undefined1 *)*param_2;
  pvVar11 = (void *)wlan_operate_get_ht_cap(iVar15);
  bVar10 = wlan_operate_get_ht_bw(iVar15);
  iVar12 = GetStaCfgByWdev(param_1,iVar15);
  memmove(&local_42,pvVar11,0x1a);
  bVar10 = (byte)local_42 & 0xfd | (bVar10 & 1) << 1;
  local_42 = CONCAT31(local_42._1_3_,bVar10);
  if ((iVar15 == 0) || (*(int *)(iVar15 + 0x14) != 2)) {
    if (iVar12 == 0) goto LAB_001399b0;
  }
  else if (iVar12 == 0) {
LAB_001399b0:
    if (3 < DebugLevel) {
      printk("%s : pStaCfg is NULL\n","build_ht_cap_ie");
    }
  }
  else if (((*(byte *)(iVar12 + 0x4190) & 0x10) != 0) &&
          (local_42 = CONCAT31(local_42._1_3_,bVar10) | 0x10, 2 < DebugLevel)) {
    printk("%s : Setting Green Field for Ap-Cli\n","build_ht_cap_ie");
  }
  iVar12 = HcIsBfCapSupport(iVar15);
  if (iVar12 == 0) {
    uVar13 = wlan_config_get_etxbf(iVar15);
    wlan_config_set_etxbf(iVar15,0);
    mt_WrapSetETxBFCap(param_1,iVar15,(int)&local_2e + 1);
    wlan_config_set_etxbf(iVar15,uVar13);
  }
  else if (((&DAT_0036790d)[param_1] != '\0') &&
          (iVar12 = hc_get_chip_cap(*(undefined4 *)(param_1 + 0xa797a0)),
          (*(byte *)(iVar12 + 0x96) & 2) != 0)) {
    uVar13 = wlan_config_get_etxbf(iVar15);
    wlan_config_set_etxbf(iVar15,2);
    if ((uVar1 != 0) && (*(char *)(param_1 + 0xa786f8) == '\0')) {
      iVar12 = (uint)uVar1 * 0x14c0;
      if (param_1 + iVar12 + 0xa1d20 == 0) {
        if (0 < DebugLevel) {
          printk("%s : HT This entry isn\'t belong to cloned STA!!!===============\n",
                 "build_ht_cap_ie");
        }
      }
      else {
        iVar12 = param_1 + iVar12;
        iVar17 = HcIsBfCapSupport(*(undefined4 *)(iVar12 + 0xa1d28));
        if ((iVar17 == 1) &&
           (wlan_config_set_etxbf(iVar15,1), (*(ushort *)(iVar15 + 0x18) & 0xffc7) == 0)) {
          *(undefined1 *)(param_1 + 0xa786f8) = 1;
          *(undefined1 *)(param_1 + 0xa786f9) = *(undefined1 *)(*(int *)(iVar12 + 0xa281c) + 2);
        }
      }
    }
    mt_WrapSetETxBFCap(param_1,iVar15,(int)&local_2e + 1);
    wlan_config_set_etxbf(iVar15,uVar13);
  }
  puVar16[1] = 0x1a;
  iVar12 = 0x1c;
  *puVar16 = HtCapIe;
  *(uint *)(puVar16 + 2) = local_42;
  *(undefined4 *)(puVar16 + 6) = local_3e;
  *(undefined4 *)(puVar16 + 10) = local_3a;
  *(undefined4 *)(puVar16 + 0xe) = local_36;
  *(undefined4 *)(puVar16 + 0x16) = local_2e;
  *(undefined4 *)(puVar16 + 0x12) = local_32;
  *(undefined2 *)(puVar16 + 0x1a) = local_2a;
LAB_00139604:
  bVar10 = *(byte *)(param_2 + 1);
  if ((bVar10 & 0xfd) == 1 || (bVar10 == 8 || bVar10 == 5)) {
    if (*(char *)((int)param_2 + 10) == '\x01') {
      iVar17 = *param_2;
      local_42 = 0x344c9000;
      iVar15 = iVar17 + iVar12;
      pvVar11 = (void *)wlan_operate_get_addht(param_2[4]);
      *(undefined1 *)(iVar17 + iVar12) = WpaIe;
      iVar12 = iVar12 + 0x1c;
      *(undefined1 *)(iVar15 + 1) = 0x1a;
      *(uint *)(iVar15 + 2) = local_42;
      memmove((void *)(iVar15 + 6),pvVar11,0x16);
    }
    else {
      iVar15 = *param_2;
      pvVar11 = (void *)wlan_operate_get_addht(param_2[4]);
      iVar17 = iVar15 + iVar12;
      *(undefined1 *)(iVar15 + iVar12) = AddHtInfoIe;
      iVar12 = iVar12 + 0x18;
      *(undefined1 *)(iVar17 + 1) = 0x16;
      memmove((void *)(iVar17 + 2),pvVar11,0x16);
    }
    bVar10 = *(byte *)(param_2 + 1);
    if ((bVar10 & 0xfd) == 1 || (bVar10 == 8 || bVar10 == 5)) {
      bVar10 = *(byte *)((int)param_2 + 6);
      iVar17 = *param_2;
      iVar15 = wlan_config_get_ht_bw(param_2[4]);
      bVar18 = bVar10 == 0xe;
      if (bVar10 < 0xf) {
        bVar18 = iVar15 == 1;
      }
      if (bVar18) {
        uVar2 = *(undefined2 *)(param_1 + 0x79569e);
        uVar3 = *(undefined2 *)(param_1 + 0x7956a2);
        iVar14 = iVar17 + iVar12;
        uVar4 = *(undefined2 *)(param_1 + 0x7956a6);
        iVar15 = 0x10;
        uVar5 = *(undefined2 *)(param_1 + 0x7956a0);
        uVar6 = *(undefined2 *)(param_1 + 0x7956a4);
        uVar7 = *(undefined2 *)(param_1 + 0x7956a8);
        uVar8 = *(undefined2 *)(param_1 + 0x7956aa);
        *(undefined1 *)(iVar17 + iVar12) = 0x4a;
        *(undefined2 *)(iVar14 + 4) = uVar5;
        *(undefined2 *)(iVar14 + 2) = uVar2;
        *(undefined2 *)(iVar14 + 6) = uVar3;
        *(undefined2 *)(iVar14 + 8) = uVar6;
        *(undefined2 *)(iVar14 + 10) = uVar4;
        *(undefined2 *)(iVar14 + 0xc) = uVar7;
        *(undefined2 *)(iVar14 + 0xe) = uVar8;
        *(undefined1 *)(iVar14 + 1) = 0xe;
      }
      else {
        iVar15 = 0;
      }
      return iVar12 + iVar15;
    }
  }
  return iVar12;
}

