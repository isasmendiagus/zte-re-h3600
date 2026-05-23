// module: mt7915.ko
// function: MT_ATEStartTx @ 0x288058
// size: 3956 bytes
//

int MT_ATEStartTx(int param_1)

{
  undefined1 uVar1;
  undefined1 uVar2;
  ushort uVar3;
  undefined2 uVar4;
  undefined2 uVar5;
  byte bVar6;
  int iVar7;
  int iVar8;
  int iVar9;
  int iVar10;
  undefined4 uVar11;
  int iVar12;
  uint uVar13;
  uint uVar14;
  int iVar15;
  uint uVar16;
  int iVar17;
  code *pcVar18;
  int iVar19;
  uint uVar20;
  int iVar21;
  uint uVar22;
  uint uVar23;
  uint uVar24;
  byte bVar25;
  ushort uVar26;
  int *piVar27;
  uint uVar28;
  int iVar29;
  bool bVar30;
  uint uVar31;
  int local_a8;
  int local_a4;
  undefined1 local_9c;
  uint local_98;
  uint local_90;
  undefined1 local_74;
  undefined1 local_73;
  undefined1 local_71;
  undefined1 local_70;
  undefined1 local_6e;
  undefined2 local_6c;
  undefined2 local_6a;
  undefined1 local_67;
  undefined1 local_65;
  undefined1 local_64;
  undefined1 local_63;
  undefined1 local_62;
  undefined1 local_61;
  undefined1 local_60;
  undefined1 local_5f;
  undefined1 local_5e;
  undefined1 local_5d;
  undefined1 local_5c;
  undefined1 local_5b;
  undefined1 local_5a;
  undefined1 local_59;
  undefined1 local_58;
  undefined1 local_57;
  undefined1 local_56;
  undefined1 local_4f;
  undefined1 local_4e;
  undefined1 local_4d;
  undefined1 local_4b;
  undefined1 local_4a;
  undefined2 local_48;
  undefined1 local_45;
  undefined2 local_44;
  undefined1 local_3a;
  undefined1 local_37;
  undefined1 local_36;
  undefined1 local_32;
  undefined1 local_31;
  int local_2c;
  
  iVar15 = *(int *)(param_1 + 0xa39fd8);
  iVar7 = net_ad_wrap_service();
  uVar22 = (uint)*(byte *)(iVar7 + 0x4cc);
  iVar7 = net_ad_wrap_service(param_1);
  iVar21 = uVar22 * 0xd18;
  uVar16 = *(uint *)(iVar7 + iVar21 + 0x4e0);
  iVar7 = net_ad_wrap_service(param_1);
  local_a4 = *(int *)(iVar7 + iVar21 + 0x1118);
  iVar7 = net_ad_wrap_service(param_1);
  iVar17 = *(int *)(iVar7 + iVar21 + 0x504);
  iVar7 = net_ad_wrap_service(param_1);
  uVar28 = (uint)(byte)"======== Badnode detector =============\nvow_bn_en = <0/1> 0:dieable, 1:enable\nvow_bn_mon_period = <period> ms\nvow_bn_fallback_th = <count>\nvow_bn_per_th = <TX PER>\n======== Airtime counter test =============\nvow_counter_test = <0/1> 0:dieable, 1:enable\nvow_counter_test_period = <period> ms\nvow_counter_test_band = <band>\nvow_counter_test_avgcnt = <average num> sec\nvow_counter_test_target = <wlanidx>\n======== DVT =============\nvow_dvt_en = <0/1> 0:dieable, 1:enable\nvow_monitor_sta = <STA num>\nvow_show_sta = <STA num>\nvow_monitor_bss = <BSS num>\nvow_monitor_mbss = <MBSS num>\nvow_show_mbss = <MBSS num>\nvow_avg_num = <average num> sec\n======== RED ===========\nvow_set_red_en = <0/1> 0:disable, 1:enable\nvow_set_red_show_sta = <STA num>\nvow_set_red_tar_delay = <tarDelay> us\n======== WATF ===========\nvow_watf_en = <0/1> 0:disable, 1:enable\nvow_watf_q = <level>-<quantum> unit 256us\nvow_watf_add_entry = <level>-<Addr>\nvow_watf_del_entry = <Addr>\n"
                       [param_1 + 0xda];
  uVar13 = (uint)*(byte *)(iVar7 + iVar21 + 0x1135);
  iVar7 = net_ad_wrap_service(param_1);
  iVar8 = hc_get_chip_dbg(*(undefined4 *)(param_1 + 0xa797a0));
  if (iVar17 == 0) {
    if (DebugLevel < 0) {
      return 0;
    }
    printk("%s: wdev for band_idx[%d] is not initialized!\n","MT_ATEStartTx",uVar22);
    return 0;
  }
  if ((uVar16 & 2) != 0) {
    if (DebugLevel < 2) {
      return 0;
    }
    printk("%s: already in TXFRAME mode now, tx is on-going!\n","MT_ATEStartTx");
    return 0;
  }
  iVar9 = net_ad_wrap_service(param_1);
  if (*(char *)(iVar9 + iVar21 + 0x6f0 + 5) == '\0') {
    if (DebugLevel < 0) {
      return 0;
    }
    printk("%s: TX information is not commit, dismissed!\n","MT_ATEStartTx");
    return 0;
  }
  iVar7 = iVar7 + iVar21 + 0x6f0;
  MtATESetMacTxRx(param_1,1,0,uVar22);
  if (uVar13 == 10) {
    iVar29 = *(int *)(iVar7 + 0x6c);
    iVar9 = net_ad_wrap_service(param_1);
    iVar9 = iVar9 + iVar21;
    iVar19 = iVar9 + 0xa1c;
    if (iVar19 == 0) {
      if (DebugLevel < 0) {
        return 0;
      }
      printk("%s: Invalid RU info\n","MT_ATEStartTx");
      return 0;
    }
    iVar12 = *(int *)(iVar9 + 0xa3c);
    iVar10 = net_ad_wrap_service(param_1);
    uVar1 = *(undefined1 *)(iVar10 + iVar21 + 0x113a);
    iVar10 = net_ad_wrap_service(param_1);
    uVar2 = *(undefined1 *)(iVar10 + iVar21 + 0x113c);
    iVar10 = net_ad_wrap_service(param_1);
    FUN_0027ef70(iVar19,iVar12 + 0xd,uVar1,uVar2,(*(byte *)(iVar10 + iVar21 + 0x1150) & 0x7f) << 1);
    iVar10 = net_ad_wrap_service(param_1);
    local_9c = 0;
    *(undefined1 *)(iVar10 + iVar21 + 0x10dc) = 0;
    if ((*(uint *)("Get_RBIST_IQ_Data_Proc" + param_1 + 0xc) & 0xffff) == 0x6867) {
      iVar15 = *(int *)(iVar9 + 0xa3c);
      iVar7 = net_ad_wrap_service(param_1);
      iVar8 = net_ad_wrap_service(param_1);
      uVar1 = *(undefined1 *)((uint)*(byte *)(iVar8 + 0x4cc) * 0xd18 + iVar7 + 0x113a);
      os_zero_mem(&local_74,0x4c);
      local_70 = *(undefined1 *)(param_1 + 0xa3ae36);
      local_63 = *(undefined1 *)(iVar29 + 0xc4);
      local_62 = *(undefined1 *)(iVar29 + 0xc6);
      local_5f = *(undefined1 *)(iVar29 + 0xd7);
      local_60 = 0;
      local_74 = 1;
      local_65 = 1;
      local_73 = 0x1f;
      local_61 = uVar1;
      if (DebugLevel < 1) {
        local_5c = *(undefined1 *)(iVar29 + 0xca);
        local_5b = *(undefined1 *)(iVar29 + 0xc9);
        local_5e = local_9c;
        local_5d = local_9c;
        local_5a = local_9c;
        local_58 = local_9c;
        local_57 = local_9c;
        local_56 = local_9c;
      }
      else {
        printk("%s: [band:%d][TXV Common1 DDW1] total_pwr_dbm:0x%x pwr_dbm:%d user_cnt:%d, tx_mode:0x%x, bw:%d, stbc:%d, ru_mu:%d, spatial_ext:%d\n"
               ,"MtCmdSetPhyManualTx",local_70,local_67,local_64,1,local_63,local_62,uVar1,0,
               local_5f);
        local_5e = 0;
        local_5d = 0;
        local_5c = *(undefined1 *)(iVar29 + 0xca);
        local_5b = *(undefined1 *)(iVar29 + 0xc9);
        local_5a = 0;
        local_58 = 0;
        local_57 = 0;
        local_56 = 0;
        if (0 < DebugLevel) {
          local_5e = local_9c;
          local_5d = local_9c;
          local_5a = local_9c;
          local_58 = local_9c;
          local_57 = local_9c;
          local_56 = local_9c;
          printk("%s: [band:%d][TXV Common1 DDW2] trigger_frame_ind:%d format:%d ltf:%d, gi:%d, sig_a_rsvd:0x%x, total_pwr_ind:%d, tf_rsp_ind:%d, cfo_ind:%d, precomp_cfo_idx:%d\n"
                 ,"MtCmdSetPhyManualTx",*(undefined1 *)(param_1 + 0xa3ae36),0,0,local_5c,local_5b,0,
                 local_59,0,0,0);
        }
      }
      local_4f = 0;
      uVar13 = *(int *)(iVar9 + 0xa7c) - 100;
      local_4b = *(undefined1 *)(iVar9 + 0xa80);
      local_4e = 0;
      local_4d = (undefined1)*(uint *)(iVar9 + 0xa4c);
      uVar28 = uVar13 / 0x14;
      local_4a = (&DAT_002a75ec)[*(int *)(iVar9 + 0xa34)];
      local_45 = *(undefined1 *)(iVar9 + 0xa78);
      iVar7 = uVar28 * 3;
      local_48 = (undefined2)*(uint *)(iVar9 + 0xa50);
      if (uVar13 == uVar28 * 0x14) {
        uVar28 = iVar7 - 5;
      }
      else {
        uVar28 = iVar7 - 2;
      }
      local_44 = (undefined2)uVar28;
      if (0 < DebugLevel) {
        printk("%s: [band:%d][TXV Common2 DDW1] mimo_ltf:%d afactor:%d txop:%d, pe_disamb:%d, ltf_symbol:%d ppdu_sym_cnt:0x%x, ldpc_extra_symbol:%d, lg_txlen:0x%x\n"
               ,"MtCmdSetPhyManualTx",*(undefined1 *)(param_1 + 0xa3ae36),0,
               *(uint *)(iVar9 + 0xa4c) & 0xff,0,local_4b,local_4a,*(uint *)(iVar9 + 0xa50) & 0xffff
               ,local_45,uVar28 & 0xffff);
      }
      local_3a = (undefined1)*(uint *)(iVar9 + 0xa38);
      local_37 = (undefined1)*(uint *)(iVar9 + 0xa28);
      local_36 = (undefined1)*(uint *)(iVar9 + 0xa30);
      uVar28 = *(int *)(iVar9 + 0xa34) - 1;
      uVar13 = uVar28 & 0xff;
      local_32 = (undefined1)uVar28;
      uVar28 = *(uint *)(iVar9 + 0xa2c);
      if ((uVar28 & 0x20) == 0) {
        uVar28 = uVar28 & 0xff;
      }
      else {
        uVar28 = uVar28 & 0xcf | 0x10;
      }
      local_31 = (undefined1)uVar28;
      if (DebugLevel < 1) {
        if (*(int *)(iVar9 + 0xa30) == 0) {
          local_2c = iVar15 + 3;
        }
        else {
          local_2c = iVar15 + 2;
        }
      }
      else {
        uVar22 = *(uint *)(iVar9 + 0xa30) & 0xff;
        uVar16 = *(uint *)(iVar9 + 0xa28) & 0xff;
        printk("%s: [band:%d][TXV Common2 DDW1] start_spatial_stream:%d ru_size:%d fec_coding:%d, nsts:%d, rate:%d\n"
               ,"MtCmdSetPhyManualTx",*(undefined1 *)(param_1 + 0xa3ae36),
               *(uint *)(iVar9 + 0xa38) & 0xff,uVar16,uVar22,uVar13,uVar28);
        if (*(int *)(iVar9 + 0xa30) == 0) {
          local_2c = 3;
        }
        else {
          local_2c = 2;
        }
        local_2c = local_2c + iVar15;
        if (0 < DebugLevel) {
          printk("%s: [band:%d][TXV User2 DDW1] apep_length:0x%x\n","MtCmdSetPhyManualTx",
                 *(undefined1 *)(param_1 + 0xa3ae36),local_2c,uVar16,uVar22,uVar13,uVar28);
        }
      }
      local_6c = 0;
      local_6e = 1;
      local_6a = 0;
      local_71 = 0xf;
      MtCmdATETest(param_1,&local_74);
      goto LAB_00288448;
    }
    pcVar18 = *(code **)(iVar8 + 0x98);
    if (pcVar18 == (code *)0x0) {
      if (-1 < DebugLevel) {
        printk("%s: ctrl_manual_hetb_tx is not registered\n","MT_ATEStartTx");
      }
      goto LAB_00288448;
    }
    iVar8 = net_ad_wrap_service(param_1);
    uVar1 = *(undefined1 *)(iVar8 + iVar21 + 0x1137);
    iVar8 = net_ad_wrap_service(param_1);
    uVar2 = *(undefined1 *)(iVar8 + iVar21 + 0x113c);
    iVar8 = net_ad_wrap_service(param_1);
    (*pcVar18)(param_1,uVar22,0,uVar1,uVar2,*(undefined1 *)(iVar8 + iVar21 + 0x113a),iVar19);
  }
  MtATESetMacTxRx(param_1,6,0,uVar22);
  msleep(0x1e);
  iVar8 = *(int *)(*(int *)(param_1 + 4) + 0x240);
  if (iVar8 == 0) {
    warn_slowpath_null("include/linux/netdevice.h",0xa06);
    printk(&_LC113);
  }
  else {
    _set_bit(0,iVar8 + 0x50);
  }
  if (*(char *)(param_1 + 0x286285) == '\x01') {
    iVar8 = hc_get_chip_bcn_max_num(*(undefined4 *)(param_1 + 0xa797a0));
    if (iVar8 < (int)uVar28) {
      uVar28 = hc_get_chip_bcn_max_num(*(undefined4 *)(param_1 + 0xa797a0));
    }
    piVar27 = (int *)("%s: Allocate memory fail!!!\n" + param_1 + 0xc);
    for (iVar8 = 1; iVar21 = hc_get_chip_bcn_max_num(*(undefined4 *)(param_1 + 0xa797a0)),
        iVar8 < iVar21; iVar8 = iVar8 + 1) {
      if (*piVar27 != 0) {
        iVar21 = *(int *)(*piVar27 + 0x240);
        if (iVar21 == 0) {
          warn_slowpath_null("include/linux/netdevice.h",0xa06);
          printk(&_LC113);
        }
        else {
          _set_bit(0,iVar21 + 0x50);
        }
      }
      piVar27 = piVar27 + 0x160d;
    }
  }
  *(uint *)(param_1 + 0xa39f84) = *(uint *)(param_1 + 0xa39f84) | 0x800000;
  chip_set_hif_dma(param_1,0,0);
  pcVar18 = *(code **)(iVar15 + 4);
  if (pcVar18 != (code *)0x0) {
    (*pcVar18)(param_1);
  }
  if ((uVar16 & 4) == 0) {
    _clear_bit(0,*(int *)(*(int *)(param_1 + 4) + 0x240) + 0x50);
    if (*(char *)(param_1 + 0x286285) == '\x01') {
LAB_002888b0:
      iVar8 = hc_get_chip_bcn_max_num(*(undefined4 *)(param_1 + 0xa797a0));
      if (iVar8 < (int)uVar28) {
        hc_get_chip_bcn_max_num(*(undefined4 *)(param_1 + 0xa797a0));
      }
      piVar27 = (int *)("%s: Allocate memory fail!!!\n" + param_1 + 0xc);
      iVar8 = 1;
      while( true ) {
        iVar21 = hc_get_chip_bcn_max_num(*(undefined4 *)(param_1 + 0xa797a0));
        iVar9 = iVar8 + 1;
        if (iVar21 <= iVar8) break;
        iVar21 = *piVar27;
        piVar27 = piVar27 + 0x160d;
        iVar8 = iVar9;
        if (iVar21 != 0) {
          _clear_bit(0,*(int *)(iVar21 + 0x240) + 0x50);
        }
      }
      chip_set_hif_dma(param_1,2,1);
      *(uint *)(param_1 + 0xa39f84) = *(uint *)(param_1 + 0xa39f84) & 0xff7fffff;
      if ((uVar16 & 4) != 0) goto LAB_0028850c;
    }
    else {
      chip_set_hif_dma(param_1,2,1);
      *(uint *)(param_1 + 0xa39f84) = *(uint *)(param_1 + 0xa39f84) & 0xff7fffff;
    }
  }
  else {
    MtATESetMacTxRx(param_1,6,1,uVar22);
    _clear_bit(0,*(int *)(*(int *)(param_1 + 4) + 0x240) + 0x50);
    if (*(char *)(param_1 + 0x286285) == '\x01') goto LAB_002888b0;
    chip_set_hif_dma(param_1,2,1);
    *(uint *)(param_1 + 0xa39f84) = *(uint *)(param_1 + 0xa39f84) & 0xff7fffff;
LAB_0028850c:
    MtATESetMacTxRx(param_1,6,1,uVar22);
  }
  iVar29 = *(int *)(iVar7 + 0xac);
  uVar28 = HcGetBandByWdev(iVar29);
  iVar8 = hc_get_chip_ops(*(undefined4 *)(param_1 + 0xa797a0));
  iVar21 = net_ad_wrap_service(param_1);
  iVar21 = uVar28 * 0xd18 + iVar21;
  iVar9 = *(int *)(iVar21 + 0x10f4);
  if (iVar9 == 0) {
    local_90 = 1;
    uVar23 = 10;
    uVar26 = 9;
    local_98 = 10;
    uVar3 = 9;
    uVar4 = 0;
  }
  else {
    uVar3 = *(ushort *)(iVar21 + 0x10fa);
    local_98 = (uint)*(ushort *)(iVar21 + 0x10fc);
    local_90 = (uint)*(byte *)(iVar21 + 0x10ff);
    uVar26 = uVar3 & 0xff;
    uVar4 = *(undefined2 *)(iVar21 + 0x1100);
    uVar23 = local_98 & 0xff;
  }
  *(ushort *)(iVar21 + 0x10fa) = uVar3;
  *(undefined2 *)(iVar21 + 0x10fc) = (undefined2)local_98;
  *(undefined1 *)(iVar21 + 0x10ff) = (undefined1)local_90;
  *(undefined2 *)(iVar21 + 0x1100) = uVar4;
  if (*(code **)(iVar8 + 0x2dc) != (code *)0x0) {
    (**(code **)(iVar8 + 0x2dc))(param_1,uVar28);
  }
  uVar31 = 0x3c;
  MtCmdATESetSlotTime(param_1,uVar26,uVar23,2,0x3c,uVar28);
  iVar8 = HcGetBandByWdev(iVar29);
  iVar21 = net_ad_wrap_service(param_1);
  bVar6 = HcGetWmmIdx(param_1,iVar29);
  bVar25 = bVar6;
  if (bVar6 < 4) {
LAB_00288544:
    if (2 < DebugLevel) {
      printk("%s: wdev_idx=%d, WmmIdx=%d\n","mt_ate_set_wmm_param_by_qid",
             *(undefined1 *)(iVar29 + 0xc),bVar25);
    }
  }
  else {
    if (-1 < DebugLevel) {
      bVar25 = 0xff;
      printk("%s: wdev_idx=%d, invalid WmmIdx=%d, reset to 0!\n","mt_ate_set_wmm_param_by_qid",
             *(undefined1 *)(iVar29 + 0xc),bVar6);
      goto LAB_00288544;
    }
    bVar25 = 0xff;
  }
  iVar29 = net_ad_wrap_service(param_1);
  uVar23 = (uint)*(ushort *)(iVar29 + iVar8 * 0xd18 + 0x50e);
  if ((uVar23 & 0xfffffffb) == 0x10 || uVar23 == 1) {
    iVar21 = iVar21 + iVar8 * 0xd18;
    uVar23 = uVar23 & 0xff;
    uVar5 = *(undefined2 *)(iVar21 + 0x10fa);
    uVar1 = *(undefined1 *)(iVar21 + 0x10ff);
    uVar24 = (uint)*(ushort *)(iVar21 + 0x10fc);
    uVar14 = (uint)*(ushort *)(iVar21 + 0x1100);
    AsicSetWmmParam(param_1,bVar25,uVar23,1,uVar1);
    AsicSetWmmParam(param_1,bVar25,uVar23,2,uVar14);
    uVar31 = uVar14;
    AsicSetWmmParam(param_1,bVar25,uVar23,3,uVar14);
    if (2 < DebugLevel) {
      printk("%s: qid=%d, slot_time=%d, sifs_time=%d, ac_num=%d, aifsn=%d, cw=%d\n",
             "mt_ate_set_wmm_param_by_qid",uVar23,uVar5,uVar24,uVar23,uVar1,uVar14);
      uVar31 = uVar24;
      uVar28 = uVar23;
    }
LAB_00288658:
    if (0 < DebugLevel) {
      printk("%s: ipg=%d, slot_time=%d, sifs_time=%d, aifsn=%d, cw=%d\n","mt_ate_apply_ipg_param",
             iVar9,uVar3,local_98,local_90,uVar4);
      uVar31 = local_98;
      uVar28 = local_90;
    }
  }
  else if (-1 < DebugLevel) {
    printk("%s: Impossible!\n","mt_ate_set_wmm_param_by_qid");
    goto LAB_00288658;
  }
  if (local_a4 != -1) {
    if ((uVar13 == 0xb) &&
       (iVar8 = net_ad_wrap_service(param_1), *(char *)(uVar22 * 0xd18 + iVar8 + 0x1104) != '\0')) {
      local_a4 = 1;
    }
    iVar8 = net_ad_wrap_service(param_1);
    *(int *)(uVar22 * 0xd18 + iVar8 + 0x1118) = local_a4;
  }
  iVar8 = net_ad_wrap_service(param_1);
  iVar21 = uVar22 * 0xd18;
  *(uint *)(iVar8 + iVar21 + 0x4e0) = uVar16 | 2;
  pcVar18 = *(code **)(iVar15 + 0xc);
  if (pcVar18 == (code *)0x0) {
    iVar8 = net_ad_wrap_service(param_1);
    iVar15 = net_ad_wrap_service(param_1);
    iVar8 = *(int *)(iVar8 + iVar21 + 0x10f4);
    iVar15 = iVar15 + iVar21;
    uVar23 = *(uint *)(iVar15 + 0x10f0);
    if (uVar23 != 0 || iVar8 != 0) {
      uVar11 = hc_get_ct_cb(*(undefined4 *)(param_1 + 0xa797a0));
      iVar9 = token_tx_get_queue_by_band(uVar11,uVar22);
      iVar29 = net_ad_wrap_service(param_1);
      iVar19 = *(int *)(iVar29 + iVar21 + 0x1118);
      iVar29 = net_ad_wrap_service(param_1);
      uVar20 = (uint)*(byte *)(iVar7 + 5);
      uVar14 = uVar20 * iVar19 * *(int *)(iVar15 + 0x1100);
      uVar24 = *(uint *)(iVar9 + 0x10) >> 1;
      if (uVar24 <= uVar14) {
        uVar14 = uVar24;
      }
      local_a8 = *(int *)(iVar29 + iVar21 + 0x1120);
      if (0 < DebugLevel) {
        printk("%s: repeat=0x%x, ampdu_cnt=%d, token_limit=%d, pkt_tx_time=%d, ipg=%d\n",
               "MT_ATEStartTx",iVar19,*(int *)(iVar15 + 0x1100),uVar24,uVar23,iVar8);
        uVar20 = (uint)*(byte *)(iVar7 + 5);
        uVar31 = uVar24;
        uVar28 = uVar23;
      }
      if (uVar20 <= uVar14) {
        iVar8 = 0;
        do {
          do {
            local_a8 = local_a8 + 1;
          } while (uVar20 == 0);
          uVar23 = 0;
          do {
            iVar21 = *(int *)(iVar15 + 0x1100);
            if (iVar21 != 0) {
              do {
                mt_ate_enq_pkt(param_1,uVar22,uVar23);
                iVar21 = iVar21 + -1;
              } while (iVar21 != 0);
              uVar20 = (uint)*(byte *)(iVar7 + 5);
            }
            uVar23 = uVar23 + 1 & 0xff;
          } while (uVar23 < uVar20);
          iVar8 = iVar8 + uVar20;
        } while (uVar20 <= uVar14 - iVar8);
      }
      *(undefined1 *)(iVar7 + 6) = 0;
      if (uVar13 - 0xb < 2) {
        mt_ate_enq_pkt(param_1,uVar22);
      }
      if (2 < DebugLevel) {
        printk("%s: txed=%d\n","MT_ATEStartTx",local_a8,DebugLevel,uVar31,uVar28);
      }
      iVar7 = net_ad_wrap_service(param_1);
      *(int *)(uVar22 * 0xd18 + iVar7 + 0x1120) = local_a8;
      if ((uVar13 == 10) &&
         ((*(uint *)("Get_RBIST_IQ_Data_Proc" + param_1 + 0xc) & 0xffff) == 0x7915)) {
        iVar7 = hc_get_chip_dbg(*(undefined4 *)(param_1 + 0xa797a0));
        if (*(code **)(iVar7 + 0x98) != (code *)0x0) {
          (**(code **)(iVar7 + 0x98))(param_1,uVar22,1,0,0,0,0);
        }
      }
    }
    iVar7 = MT_ATETxControl(param_1,uVar22,0);
  }
  else {
    iVar7 = (*pcVar18)();
  }
  if (iVar7 != 0) {
    iVar8 = net_ad_wrap_service(param_1);
    bVar30 = -1 < DebugLevel;
    *(uint *)(uVar22 * 0xd18 + iVar8 + 0x4e0) = uVar16 & 0xfffffffd;
    if (bVar30) {
      printk("%s: Err %d, wdev_idx:%x\n","MT_ATEStartTx",iVar7,*(undefined1 *)(iVar17 + 0xc));
      return iVar7;
    }
    return iVar7;
  }
  MtATESetMacTxRx(param_1,1,1,uVar22);
LAB_00288448:
  *(undefined1 *)(param_1 + 0xa3b8bb) = 1;
  return 0;
}

