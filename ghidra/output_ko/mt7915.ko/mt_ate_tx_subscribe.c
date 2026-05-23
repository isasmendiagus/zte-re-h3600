// module: mt7915.ko
// function: mt_ate_tx_subscribe @ 0x289414
// size: 3096 bytes
//

undefined4 mt_ate_tx_subscribe(int param_1)

{
  byte bVar1;
  undefined1 uVar2;
  undefined1 uVar3;
  char cVar4;
  undefined1 uVar5;
  byte bVar6;
  int iVar7;
  int iVar8;
  int iVar9;
  int iVar10;
  undefined4 uVar11;
  int extraout_r1;
  int extraout_r1_00;
  int extraout_r1_01;
  int extraout_r1_02;
  int extraout_r1_03;
  int *piVar12;
  uint *puVar13;
  undefined4 *puVar14;
  int iVar15;
  uint uVar16;
  code *pcVar17;
  int iVar18;
  int iVar19;
  uint uVar20;
  int iVar21;
  int iVar22;
  uint uVar23;
  uint uVar24;
  undefined4 uVar25;
  int iVar26;
  bool bVar27;
  undefined8 uVar28;
  int local_258;
  byte local_248;
  undefined1 local_247;
  undefined1 local_246;
  undefined1 local_245;
  undefined1 local_244;
  undefined1 local_243;
  byte local_242;
  undefined1 local_241;
  undefined1 local_240;
  undefined1 local_23f;
  uint local_23c;
  uint local_238;
  uint local_234;
  undefined1 local_22c;
  byte local_22a;
  undefined1 local_229;
  undefined1 local_226;
  byte local_225;
  undefined1 local_224;
  undefined1 local_223;
  undefined1 local_222;
  byte local_221;
  byte local_220;
  undefined1 auStack_21e [8];
  undefined1 auStack_216 [2];
  undefined2 local_214;
  byte local_212 [12];
  undefined2 local_206 [103];
  uint auStack_138 [69];
  
  iVar7 = hc_get_chip_ops(*(undefined4 *)(param_1 + 0xa797a0));
  iVar8 = net_ad_wrap_service(param_1);
  bVar6 = *(byte *)(iVar8 + 0x4cc);
  uVar24 = (uint)bVar6;
  iVar8 = net_ad_wrap_service(param_1);
  iVar22 = uVar24 * 0xd18;
  bVar1 = *(byte *)(iVar8 + iVar22 + 0x1135);
  uVar16 = (uint)bVar1;
  iVar8 = net_ad_wrap_service(param_1);
  iVar9 = net_ad_wrap_service(param_1);
  iVar9 = iVar9 + iVar22;
  iVar10 = net_ad_wrap_service(param_1);
  iVar18 = *(int *)(iVar10 + iVar22 + 0x10e8);
  iVar10 = net_ad_wrap_service(param_1);
  if ((*(char *)(iVar10 + iVar22 + 0x6f5) != '\0') &&
     (mt_ate_tx_unsubscribe(param_1), 1 < DebugLevel)) {
    printk("%s: Preiously stored TX information for band[%d] will be flushed!\n",
           "mt_ate_tx_subscribe",uVar24);
  }
  __memzero(&local_248,0x10);
  iVar10 = net_ad_wrap_service(param_1);
  iVar22 = uVar24 * 0xd18;
  if (iVar18 == 0) goto LAB_00289510;
  iVar15 = *(int *)(param_1 + 0xa39fd4);
  iVar19 = net_ad_wrap_service(param_1);
  iVar19 = iVar19 + iVar22 + 0x10f0;
  iVar21 = net_ad_wrap_service(param_1);
  local_258 = *(int *)(iVar19 + 4);
  iVar26 = *(int *)(iVar21 + iVar22 + 0x10f0);
  iVar18 = net_ad_wrap_service(param_1);
  iVar18 = *(int *)(iVar18 + iVar22 + 0x10e8);
  bVar27 = iVar18 != 0;
  if ((iVar26 == 0 && bVar27) && local_258 == 0) {
    if (DebugLevel < 1) {
      iVar26 = 0;
      iVar18 = iVar26;
      goto LAB_00289d54;
    }
    iVar18 = 0;
    iVar26 = 0;
    printk("%s: There are no pkt_tx_time/ipg!!\n%s: Use default transmission setting and set duty_cycle=%d\n"
           ,"mt_ate_calculate_duty_cycle","mt_ate_calculate_duty_cycle");
    local_258 = 0;
LAB_00289f10:
    if (0 < DebugLevel) {
      printk("%s: duty_cycle=%d%%, ipg=%dus, pkt_tx_time=%dus\n","mt_ate_calculate_duty_cycle",
             iVar18,local_258,iVar26);
    }
  }
  else {
    if (iVar26 != 0 && (bVar27 && local_258 == 0)) {
      local_258 = __aeabi_uidiv(iVar26 * 100,iVar18);
      local_258 = local_258 - iVar26;
      *(int *)(iVar19 + 4) = local_258;
      (**(code **)(iVar15 + 0x68))(param_1,local_258);
      goto LAB_00289f10;
    }
    if (local_258 != 0 && (iVar26 == 0 && bVar27)) {
      iVar26 = __aeabi_uidiv(local_258 * iVar18,100 - iVar18);
      goto LAB_00289f10;
    }
    if (DebugLevel < 1) {
      iVar18 = __aeabi_uidiv(iVar26 * 100,iVar26 + local_258);
    }
    else {
      printk("%s: Already existed pkt_tx_time/ipg, can\'t set duty_cycle!!\n%s: Expected duty_cycle=%d%%\n"
             ,"mt_ate_calculate_duty_cycle","mt_ate_calculate_duty_cycle",iVar18);
      iVar18 = __aeabi_uidiv(iVar26 * 100,iVar26 + local_258);
      if (0 < DebugLevel) {
        printk("%s: Real duty_cycle=%d%%\n","mt_ate_calculate_duty_cycle",iVar18);
        goto LAB_00289f10;
      }
    }
  }
LAB_00289d54:
  *(int *)(iVar21 + iVar22 + 0x10f0) = iVar26;
  iVar19 = net_ad_wrap_service(param_1);
  *(int *)(uVar24 * 0xd18 + iVar19 + 0x10e8) = iVar18;
LAB_00289510:
  local_248 = bVar1;
  iVar18 = net_ad_wrap_service(param_1);
  iVar19 = uVar24 * 0xd18;
  local_247 = *(undefined1 *)(iVar18 + iVar19 + 0x1137);
  iVar18 = net_ad_wrap_service(param_1);
  local_246 = *(undefined1 *)(iVar18 + iVar19 + 0x113a);
  iVar18 = net_ad_wrap_service(param_1);
  local_245 = *(undefined1 *)(iVar18 + iVar19 + 0x113b);
  iVar18 = net_ad_wrap_service(param_1);
  local_23c = *(uint *)(iVar18 + iVar19 + 0x6dc);
  iVar18 = net_ad_wrap_service(param_1);
  local_243 = FUN_0027f5ec(uVar16,*(undefined1 *)(iVar18 + iVar19 + 0x113c));
  iVar18 = net_ad_wrap_service(param_1);
  local_244 = FUN_0027f65c(uVar16,*(undefined1 *)(iVar18 + iVar19 + 0x113c));
  iVar18 = net_ad_wrap_service(param_1);
  local_240 = *(undefined1 *)(iVar18 + iVar19 + 0x11cc);
  iVar18 = net_ad_wrap_service(param_1);
  local_23f = *(undefined1 *)(iVar18 + iVar19 + 0x11cd);
  if (*(char *)(iVar10 + iVar22 + 0x6e5 + uVar16) == '\0') {
    iVar10 = net_ad_wrap_service(param_1);
    uVar25 = *(undefined4 *)(iVar10 + iVar19 + 0x504);
  }
  else {
    iVar10 = net_ad_wrap_service(param_1);
    uVar25 = *(undefined4 *)(iVar10 + iVar19 + 0x508);
  }
  if (uVar16 < 10) {
    if ((*(uint *)("Get_RBIST_IQ_Data_Proc" + param_1 + 0xc) & 0xffff) == 0x7915) {
      wifi_test_muru_set_arb_op_mode(param_1,5);
    }
    iVar10 = net_ad_wrap_service(param_1);
    iVar18 = uVar24 * 0xd18;
    iVar22 = iVar8 + iVar18 + 0x531;
    local_242 = *(byte *)(iVar10 + iVar18 + 0x1138);
    iVar8 = net_ad_wrap_service(param_1);
    local_241 = *(undefined1 *)(iVar8 + iVar18 + 0x1139);
    uVar11 = MacTableInsertEntry(param_1,iVar22,uVar25,0x20,4,1);
    mt_ate_store_tx_info(param_1,uVar24,uVar25,iVar22,uVar11,&local_248);
    iVar8 = extraout_r1;
  }
  else {
    uVar28 = net_ad_wrap_service(param_1);
    iVar8 = (int)((ulonglong)uVar28 >> 0x20);
    iVar18 = 0;
    iVar10 = uVar24 * 0xd18 + (int)uVar28;
    if (uVar16 == 0xc) {
      local_248 = 4;
    }
    piVar12 = (int *)(iVar10 + 0xa24);
    do {
      iVar22 = net_ad_wrap_service(param_1,iVar8);
      iVar8 = iVar18 * 6;
      iVar18 = iVar18 + 1;
      iVar8 = iVar22 + uVar24 * 0xd18 + iVar8 + 0x531;
      if ((char)piVar12[-2] != '\0') {
        local_242 = (byte)piVar12[2];
        local_241 = (undefined1)piVar12[4];
        local_245 = (undefined1)piVar12[3];
        if (0x1a < (uint)piVar12[6]) {
          local_23c = piVar12[6];
        }
        iVar22 = MacTableInsertEntry(param_1,iVar8,uVar25,0x20,4,1);
        if (iVar22 != 0 && *piVar12 != 0) {
          *(short *)(iVar22 + 0xf8) = (short)*piVar12;
        }
        mt_ate_store_tx_info(param_1,uVar24,uVar25,iVar8,iVar22,&local_248);
        iVar8 = extraout_r1_02;
      }
      piVar12 = piVar12 + 0x1b;
    } while (iVar18 != 0x10);
    if ((*(uint *)("Get_RBIST_IQ_Data_Proc" + param_1 + 0xc) & 0xffff) == 0x7915) {
      iVar8 = net_ad_wrap_service(param_1,iVar8);
      iVar21 = uVar24 * 0xd18;
      iVar18 = net_ad_wrap_service(param_1);
      iVar19 = *(int *)(iVar8 + iVar21 + 0x75c);
      os_zero_mem(&local_238,0x210);
      iVar22 = net_ad_wrap_service(param_1);
      local_242 = *(byte *)(iVar22 + iVar21 + 0x1138);
      local_22c = 8;
      local_238 = 5;
      local_22a = bVar6;
      local_229 = HcGetWmmIdx(param_1,uVar25);
      local_225 = local_248;
      local_238 = local_238 | 8;
      local_224 = local_247;
      local_221 = local_242 & 0xf;
      local_220 = (byte)(((uint)local_242 << 0x1a) >> 0x1f);
      local_234 = local_234 | 0xd5;
      local_226 = *(undefined1 *)(iVar8 + iVar21 + 0x6f5);
      os_move_mem(auStack_21e,(void *)(iVar18 + iVar21 + 0x10dd),8);
      puVar14 = (undefined4 *)(iVar10 + 0xa40);
      local_223 = local_243;
      local_222 = local_244;
      puVar13 = &local_238;
      do {
        if (*(char *)(puVar14 + -9) != '\0') {
          *(undefined2 *)(puVar13 + 9) = *(undefined2 *)(iVar19 + 0xe0);
          *(byte *)((int)puVar13 + 0x26) = (byte)puVar14[-6] & 1;
          *(char *)((int)puVar13 + 0x27) = (char)((uint)puVar14[-6] >> 1);
          bVar6 = (byte)*(undefined4 *)(iVar19 + 0xd0) & 0xf;
          *(byte *)((int)puVar13 + 0x2a) = bVar6;
          *(short *)((int)puVar13 + 0x32) = (short)*puVar14;
          if ((*(uint *)(iVar19 + 0xd0) & 0x20) != 0) {
            *(byte *)((int)puVar13 + 0x2a) = bVar6 | 0x10;
          }
          *(char *)((int)puVar13 + 0x29) = *(char *)(iVar19 + 0xcd) + -1;
          *(undefined1 *)(puVar13 + 10) = *(undefined1 *)(iVar19 + 199);
          if ((uint)puVar14[-6] >> 1 == 0x12) {
            auStack_216[puVar14[-6] & 1] = 1;
          }
        }
        puVar13 = puVar13 + 4;
        iVar19 = iVar19 + 0x14c0;
        puVar14 = puVar14 + 0x1b;
      } while (puVar13 != auStack_138);
      local_234 = local_234 | 0x21f002a;
      wifi_test_muru_set_arb_op_mode(param_1,2);
      wifi_test_muru_set_manual_config(param_1,&local_238);
      iVar8 = extraout_r1_03;
    }
  }
  if (*(int *)(iVar9 + 0x10f0) == 0) {
    *(undefined4 *)(iVar9 + 0x1100) = 1;
  }
  pcVar17 = *(code **)(iVar7 + 0x2e0);
  if (pcVar17 != (code *)0x0) {
    uVar5 = HcGetWmmIdx(param_1,uVar25);
    (*pcVar17)(param_1,uVar5,*(undefined1 *)(iVar9 + 0x1100));
    iVar8 = extraout_r1_00;
  }
  if (*(code **)(iVar7 + 0x2e4) != (code *)0x0) {
    (**(code **)(iVar7 + 0x2e4))(param_1,0xf);
    iVar8 = extraout_r1_01;
  }
  iVar7 = net_ad_wrap_service(param_1,iVar8);
  uVar16 = *(uint *)(iVar7 + uVar24 * 0xd18 + 0x1128);
  iVar7 = net_ad_wrap_service(param_1);
  iVar7 = iVar7 + uVar24 * 0xd18;
  iVar8 = hc_get_chip_dbg(*(undefined4 *)(param_1 + 0xa797a0));
  iVar9 = hc_get_hif_type(*(undefined4 *)(param_1 + 0xa797a0));
  if (iVar9 == 2) {
    if ((int)uVar16 < 0) {
      uVar23 = uVar16 & 0xff;
    }
    else {
      if ((*(uint *)("Get_RBIST_IQ_Data_Proc" + param_1 + 0xc) & 0xffff) == 0x7915) {
        uVar16 = uVar16 >> ((uVar24 & 0x7f) << 1);
      }
      if (ant_to_spe_idx_map._0_4_ == uVar16) {
        iVar9 = 0;
LAB_00289ea0:
        uVar23 = (uint)(byte)ant_to_spe_idx_map[iVar9 + 4];
      }
      else {
        iVar10 = 1;
        do {
          iVar18 = iVar10 * 8;
          iVar9 = iVar10 << 3;
          iVar10 = iVar10 + 1;
          if (*(uint *)(ant_to_spe_idx_map + iVar18) == uVar16) goto LAB_00289ea0;
        } while (iVar10 != 0x10);
        uVar23 = 0;
      }
    }
    uVar16 = 0;
    if (g_EBF_certification != '\0') {
      if (BF_ON_certification == '\0') {
        if (DebugLevel < 4) {
          uVar16 = 0x18;
        }
        else {
          uVar16 = 0x18;
          printk("Info.AntPri = 24\n");
        }
      }
      else if (DebugLevel < 4) {
        uVar16 = 0;
      }
      else {
        uVar16 = 0;
        printk("Info.AntPri = 0\n");
      }
    }
  }
  else if (uVar16 == 0) {
    uVar23 = 1;
  }
  else if (uVar16 == 2) {
    uVar23 = 0;
  }
  else {
    uVar16 = 0;
    uVar23 = uVar16;
  }
  iVar9 = *(int *)(iVar7 + 0x75c);
  if ((iVar9 != 0) && (*(char *)(iVar7 + 0x6f5) != '\0')) {
    uVar20 = 0;
    do {
      *(char *)(iVar9 + 0xd7) = (char)uVar16;
      *(char *)(iVar9 + 0xd8) = (char)uVar23;
      __memzero(&local_238,0x1c);
      uVar20 = uVar20 + 1 & 0xff;
      local_234 = 0x16;
      local_223 = (char)uVar23;
      RAParamUpdate(param_1,iVar9,&local_238);
      iVar9 = *(int *)(iVar7 + 0x6f4 + (uVar20 + 0x1a) * 4);
      if (iVar9 == 0) break;
    } while (uVar20 < *(byte *)(iVar7 + 0x6f5));
  }
  pcVar17 = *(code **)(iVar8 + 0xa0);
  if (pcVar17 != (code *)0x0) {
    iVar7 = net_ad_wrap_service(param_1);
    (*pcVar17)(param_1,uVar24,*(undefined1 *)(uVar24 * 0xd18 + iVar7 + 0x1135),uVar23);
  }
  iVar7 = net_ad_wrap_service(param_1);
  iVar7 = uVar24 * 0xd18 + iVar7;
  cVar4 = *(char *)(*(int *)(iVar7 + 0x75c) + 0xd7);
  iVar8 = net_ad_wrap_service(param_1);
  iVar9 = net_ad_wrap_service(param_1);
  uVar5 = *(undefined1 *)((uint)*(byte *)(iVar9 + 0x4cc) * 0xd18 + iVar8 + 0x1137);
  iVar8 = net_ad_wrap_service(param_1);
  iVar9 = net_ad_wrap_service(param_1);
  uVar2 = *(undefined1 *)((uint)*(byte *)(iVar9 + 0x4cc) * 0xd18 + iVar8 + 0x1135);
  iVar8 = net_ad_wrap_service(param_1);
  iVar9 = net_ad_wrap_service(param_1);
  uVar3 = *(undefined1 *)((uint)*(byte *)(iVar9 + 0x4cc) * 0xd18 + iVar8 + 0x1138);
  iVar8 = net_ad_wrap_service(param_1);
  iVar9 = net_ad_wrap_service(param_1);
  bVar6 = SKUTxPwrOffsetGet(param_1,uVar24,uVar5,uVar2,uVar3,
                            *(undefined1 *)((uint)*(byte *)(iVar9 + 0x4cc) * 0xd18 + iVar8 + 0x1139)
                            ,'\x17' < cVar4);
  if (2 < DebugLevel) {
    printk("%s: Info.PowerOffset = 0x%x (%d)\n","mt_ate_apply_pwr_offset",bVar6,bVar6);
  }
  iVar8 = *(int *)(iVar7 + 0x75c);
  if (0xe < bVar6) {
    bVar6 = 0xf;
  }
  if ((iVar8 != 0) && (*(char *)(iVar7 + 0x6f5) != '\0')) {
    piVar12 = (int *)(iVar7 + 0x75c);
    iVar9 = 0;
    do {
      *(byte *)(iVar8 + 0xd6) = bVar6;
      iVar9 = iVar9 + 1;
      piVar12 = piVar12 + 1;
      iVar8 = *piVar12;
      if (iVar8 == 0) {
        return 0;
      }
    } while (iVar9 < (int)(uint)*(byte *)(iVar7 + 0x6f5));
  }
  return 0;
}

