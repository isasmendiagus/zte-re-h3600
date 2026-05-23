// module: mt7915.ko
// function: mt_ate_set_tmac_info @ 0x283f80
// size: 2112 bytes
//

undefined4 mt_ate_set_tmac_info(int param_1,undefined2 *param_2,uint param_3)

{
  char cVar1;
  char cVar2;
  char cVar3;
  char cVar4;
  char cVar5;
  char cVar6;
  byte bVar7;
  undefined1 uVar8;
  undefined1 uVar9;
  undefined2 uVar10;
  bool bVar11;
  undefined1 uVar12;
  int iVar13;
  int iVar14;
  int iVar15;
  int iVar16;
  char cVar17;
  undefined4 uVar18;
  int iVar19;
  bool bVar20;
  int iVar21;
  uint uVar22;
  bool bVar23;
  
  iVar13 = net_ad_wrap_service();
  cVar1 = *(char *)(param_1 + 0xa3ae36);
  iVar13 = iVar13 + param_3 * 0xd18;
  iVar19 = *(int *)(iVar13 + 0x10f0);
  cVar17 = *(char *)(iVar13 + 0x1104);
  cVar2 = *(char *)(iVar13 + 0x1105);
  cVar3 = *(char *)(iVar13 + 0x1106);
  iVar14 = net_ad_wrap_service(param_1);
  iVar14 = *(int *)(iVar14 + param_3 * 0xd18 + 0x504);
  if (3 < DebugLevel) {
    printk("%s: wdev_idx=%d\n","mt_ate_set_tmac_info",*(undefined1 *)(iVar14 + 0xc));
  }
  if (iVar14 == 0) {
    if (DebugLevel < 0) {
      return 1;
    }
    printk("%s:: Cannot get Wdev by band:%d\n","mt_ate_set_tmac_info",param_3);
    return 1;
  }
  iVar15 = net_ad_wrap_service(param_1);
  *(undefined2 *)(iVar15 + param_3 * 0xd18 + 0x6d6) = 0x18;
  iVar15 = net_ad_wrap_service(param_1);
  iVar15 = iVar15 + param_3 * 0xd18 + 0x530;
  if (3 < DebugLevel) {
    printk("%s:: addr1: %02x:%02x:%02x:%02x:%02x:%02x\n","mt_ate_set_tmac_info",
           *(undefined1 *)(iVar15 + 1),*(undefined1 *)(iVar15 + 2),*(undefined1 *)(iVar15 + 3),
           *(undefined1 *)(iVar15 + 4),*(undefined1 *)(iVar15 + 5),*(undefined1 *)(iVar15 + 6));
  }
  iVar16 = net_ad_wrap_service(param_1);
  iVar21 = param_3 * 0xd18;
  uVar22 = *(uint *)(iVar16 + iVar21 + 0x1128);
  iVar16 = net_ad_wrap_service(param_1);
  cVar4 = *(char *)(iVar16 + iVar21 + 0x1135);
  iVar16 = net_ad_wrap_service(param_1);
  cVar5 = *(char *)(iVar16 + iVar21 + 0x1138);
  iVar16 = net_ad_wrap_service(param_1);
  cVar6 = *(char *)(iVar16 + iVar21 + 0x1139);
  __memzero(param_2,0x3c);
  *(undefined1 *)((int)param_2 + 0x25) = 1;
  if (iVar19 == 0) {
    iVar13 = net_ad_wrap_service(param_1);
    uVar10 = *(undefined2 *)(iVar13 + iVar21 + 0x6d6);
    *(undefined1 *)(param_2 + 10) = 0;
    *(char *)(param_2 + 1) = (char)uVar10;
    iVar13 = net_ad_wrap_service(param_1);
    *param_2 = (short)*(undefined4 *)(iVar13 + iVar21 + 0x6dc);
    *(byte *)((int)param_2 + 0x2b) = *(byte *)(iVar15 + 1) & 1;
LAB_00284484:
    bVar20 = false;
    *(undefined1 *)(param_2 + 5) = 0;
  }
  else {
    *(char *)(param_2 + 1) = (char)*(undefined4 *)(iVar13 + 0x10fc);
    uVar18 = *(undefined4 *)(iVar13 + 0x10f8);
    bVar20 = cVar2 == '\0';
    bVar11 = cVar17 == '\0';
    bVar23 = cVar3 == '\0' && (bVar20 && bVar11);
    if (bVar23) {
      *(undefined1 *)(param_2 + 10) = 0;
    }
    *(undefined1 *)(param_2 + 0x13) = 0;
    uVar12 = 0;
    if (cVar3 != '\0' || (!bVar20 || !bVar11)) {
      uVar12 = 2;
    }
    *param_2 = (short)uVar18;
    if (bVar23) {
      bVar7 = *(byte *)(iVar15 + 1);
      *(undefined1 *)((int)param_2 + 0xb) = uVar12;
      *(byte *)((int)param_2 + 0x2b) = bVar7 & 1;
    }
    else {
      *(undefined1 *)(param_2 + 10) = uVar12;
      *(undefined1 *)((int)param_2 + 0x2b) = 0;
      *(undefined1 *)((int)param_2 + 0xb) = 0;
    }
    if (cVar3 == '\0') goto LAB_00284484;
    bVar20 = true;
    *(undefined1 *)(param_2 + 5) = 1;
  }
  iVar13 = DebugLevel;
  param_2[0x1a] = 2;
  param_2[0x1b] = 8;
  *(undefined1 *)(param_2 + 6) = *(undefined1 *)(iVar14 + 0x29);
  if (3 < iVar13) {
    printk("%s: tmac_info->OwnMacIdx=%d\n","mt_ate_set_tmac_info");
  }
  *(undefined1 *)((int)param_2 + 0x15) = 0;
  *(undefined4 *)(param_2 + 8) = 0;
  cVar17 = cVar6;
  if (cVar6 == '\0') {
    cVar17 = '\x01';
  }
  *(undefined1 *)(param_2 + 0xc) = 0;
  *(char *)(param_2 + 0x1d) = cVar17;
  *(undefined1 *)((int)param_2 + 0x19) = 0;
  if ((*(int *)("Set_RBIST_Capture_Start" + param_1 + 0x10) != 0) &&
     (*(char *)(*(int *)("Set_RBIST_Capture_Start" + param_1 + 0x10) + 1) == '\x01')) {
    *(undefined1 *)((int)param_2 + 0x1b) = 1;
  }
  *(char *)((int)param_2 + 0x3b) = (char)param_3;
  if (uVar22 == 0) {
    *(undefined1 *)((int)param_2 + 0x19) = 1;
LAB_002841cc:
    iVar13 = net_ad_wrap_service(param_1);
    *(undefined1 *)((int)param_2 + 5) = *(undefined1 *)(param_3 * 0xd18 + iVar13 + 0x50d);
    iVar13 = hc_get_hif_type(*(undefined4 *)(param_1 + 0xa797a0));
    if (iVar13 != 2) goto LAB_002841fc;
LAB_00284598:
    if (ant_to_spe_idx_map._0_4_ == uVar22) {
      iVar13 = 0;
LAB_002846b4:
      *(char *)(param_2 + 0xc) = (char)*(undefined4 *)(ant_to_spe_idx_map + iVar13 + 4);
    }
    else {
      iVar14 = 1;
      do {
        iVar19 = iVar14 * 8;
        iVar13 = iVar14 << 3;
        iVar14 = iVar14 + 1;
        if (*(uint *)(ant_to_spe_idx_map + iVar19) == uVar22) goto LAB_002846b4;
      } while (iVar14 != 0x10);
      *(undefined1 *)(param_2 + 0xc) = 0;
    }
    if (cVar1 == '\0') {
      if ((*(char *)(param_1 + 0xa3ae07) != '\0') || (*(char *)(param_1 + 0xa3ae08) != '\0')) {
LAB_002845f4:
        *(undefined1 *)(param_2 + 0xc) = 0;
      }
    }
    else if ((param_1 != -0xa3a098) && (*(short *)(param_1 + 0xa3a9c2) != 0)) goto LAB_002845f4;
  }
  else {
    if (uVar22 == 2) {
      *(undefined1 *)(param_2 + 0xc) = 2;
      goto LAB_002841cc;
    }
    iVar13 = net_ad_wrap_service(param_1);
    *(undefined1 *)((int)param_2 + 5) = *(undefined1 *)(param_3 * 0xd18 + iVar13 + 0x50d);
    iVar13 = hc_get_hif_type(*(undefined4 *)(param_1 + 0xa797a0));
    if (iVar13 != 2) goto LAB_002841fc;
    if (-1 < (int)uVar22) goto LAB_00284598;
    uVar22 = uVar22 & 0x7fffffff;
    *(char *)(param_2 + 0xc) = (char)uVar22;
  }
  iVar13 = DebugLevel;
  if (g_EBF_certification != '\0') {
    if (BF_ON_certification == '\0') {
      *(undefined1 *)(param_2 + 0xc) = 0x18;
      if (iVar13 < 4) goto LAB_002841fc;
      printk("tmac_info->AntPri = 24\n");
    }
    else {
      *(undefined1 *)(param_2 + 0xc) = 0;
      if (iVar13 < 4) goto LAB_002841fc;
      printk("tmac_info->AntPri = 0\n");
    }
  }
  if (3 < DebugLevel) {
    printk("%s:: ant_sel:%x, ant_pri:%u, vht_nss:%x, TxD.VhtNss:%x\n","mt_ate_set_tmac_info",uVar22,
           *(undefined1 *)(param_2 + 0xc),cVar6,*(undefined1 *)(param_2 + 0x1d));
  }
LAB_002841fc:
  iVar14 = param_3 * 0xd18;
  *(char *)((int)param_2 + 0x23) = cVar5;
  iVar13 = net_ad_wrap_service(param_1);
  *(undefined1 *)((int)param_2 + 0x21) = *(undefined1 *)(iVar13 + iVar14 + 0x1137);
  iVar13 = net_ad_wrap_service(param_1);
  *(undefined1 *)(param_2 + 0xf) = *(undefined1 *)(iVar13 + iVar14 + 0x113c);
  iVar13 = net_ad_wrap_service(param_1);
  uVar12 = *(undefined1 *)(iVar13 + iVar14 + 0x113a);
  *(char *)(param_2 + 0x12) = cVar4;
  *(undefined1 *)(param_2 + 0x10) = uVar12;
  iVar13 = net_ad_wrap_service(param_1);
  uVar12 = *(undefined1 *)((int)param_2 + 5);
  *(undefined1 *)((int)param_2 + 0x1f) = *(undefined1 *)(iVar13 + iVar14 + 0x113b);
  iVar13 = net_ad_wrap_service(param_1);
  uVar12 = asic_get_hwq_from_ac(param_1,uVar12,*(undefined1 *)(iVar13 + iVar14 + 0x50e));
  *(undefined1 *)((int)param_2 + 3) = uVar12;
  if (bVar20) {
    uVar10 = *(undefined2 *)(param_1 + 0xa3b008);
    *(undefined1 *)(param_2 + 0x16) = 0;
    *(undefined1 *)((int)param_2 + 0x2d) = 0;
    param_2[4] = uVar10;
    *(undefined1 *)(param_2 + 0x19) = 1;
  }
  else {
    param_2[4] = 0;
    *(undefined1 *)(param_2 + 0x16) = 1;
    *(undefined1 *)((int)param_2 + 0x2d) = 1;
    *(undefined1 *)(param_2 + 0x19) = 0xf;
  }
  if (*(char *)(param_1 + 0xa3b8b5) != '\0') {
    *(undefined1 *)(param_2 + 0x17) = 1;
    *(undefined1 *)(param_2 + 0x18) = 1;
    *(undefined1 *)((int)param_2 + 0x2f) = 0;
  }
  if (cVar4 == '\0') {
    *(undefined1 *)(param_2 + 0x11) = 1;
    if (cVar5 == '\t') {
      *(undefined1 *)((int)param_2 + 0x23) = 0;
      *(undefined1 *)(param_2 + 0x11) = 0;
    }
    else if (cVar5 == '\n') {
      *(undefined1 *)((int)param_2 + 0x23) = 1;
      *(undefined1 *)(param_2 + 0x11) = 0;
    }
    else if (cVar5 == '\v') {
      *(undefined1 *)(param_2 + 0x11) = 0;
      *(undefined1 *)((int)param_2 + 0x23) = 2;
    }
  }
  else {
    iVar13 = net_ad_wrap_service(param_1);
    cVar1 = *(char *)(iVar13 + param_3 * 0xd18 + 0x11cc);
    iVar13 = net_ad_wrap_service(param_1);
    cVar17 = *(char *)(iVar13 + param_3 * 0xd18 + 0x11cd);
    if (cVar17 != '\0' || cVar1 != '\0') {
      *(char *)(param_2 + 0xe) = cVar1;
      *(char *)((int)param_2 + 0x1d) = cVar17;
    }
  }
  iVar13 = DebugLevel;
  param_2[4] = *(undefined2 *)(param_1 + 0xa3b008);
  if (3 < iVar13) {
    printk("%s: tmac_info->TxRadioSet.EtxBFEnable=%d, tmac_info->Wcid=%d\n","mt_ate_set_tmac_info",
           *(undefined1 *)((int)param_2 + 0x1d));
  }
  bVar7 = *(byte *)(param_2 + 0xc);
  iVar13 = net_ad_wrap_service(param_1);
  iVar14 = param_3 * 0xd18;
  uVar12 = *(undefined1 *)(iVar13 + iVar14 + 0x1137);
  iVar13 = net_ad_wrap_service(param_1);
  uVar8 = *(undefined1 *)(iVar13 + iVar14 + 0x1135);
  iVar13 = net_ad_wrap_service(param_1);
  uVar9 = *(undefined1 *)(iVar13 + iVar14 + 0x1138);
  iVar13 = net_ad_wrap_service(param_1);
  uVar22 = SKUTxPwrOffsetGet(param_1,param_3 & 0xff,uVar12,uVar8,uVar9,
                             *(undefined1 *)(iVar13 + iVar14 + 0x1139),0x17 < bVar7);
  iVar13 = DebugLevel;
  *(char *)(param_2 + 0xd) = (char)uVar22;
  if (2 < iVar13) {
    printk("%s: tmac_info->PowerOffset = 0x%x (%d)\n","mt_ate_set_tmac_info",uVar22,uVar22);
    uVar22 = (uint)*(byte *)(param_2 + 0xd);
  }
  if ((char)uVar22 < -0x10) {
    *(undefined1 *)(param_2 + 0xd) = 0xf0;
  }
  else if ('\x0f' < (char)uVar22) {
    *(undefined1 *)(param_2 + 0xd) = 0xf;
  }
  if ((bVar20) && (3 < DebugLevel)) {
    printk("%s: tmac_info->Wcid/Wmmset/QueIdx=%d/%d/%d\n","mt_ate_set_tmac_info",param_2[4],
           *(undefined1 *)((int)param_2 + 5),*(undefined1 *)((int)param_2 + 3));
  }
  return 0;
}

