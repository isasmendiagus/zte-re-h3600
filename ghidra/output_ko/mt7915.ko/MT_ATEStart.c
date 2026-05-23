// module: mt7915.ko
// function: MT_ATEStart @ 0x2830b0
// size: 3764 bytes
//

int MT_ATEStart(int param_1)

{
  uint uVar1;
  int iVar2;
  int iVar3;
  undefined4 uVar4;
  int iVar5;
  byte bVar6;
  undefined2 uVar7;
  uint uVar8;
  undefined4 *puVar9;
  byte bVar10;
  undefined2 uVar11;
  undefined4 *puVar12;
  code *pcVar13;
  undefined4 *puVar14;
  undefined1 uVar15;
  int *piVar16;
  bool bVar17;
  uint local_74;
  undefined1 uStack_6f;
  undefined4 local_6e;
  undefined2 local_6a;
  char local_68 [4];
  undefined2 local_64;
  ushort local_62;
  undefined3 uStack_60;
  undefined1 uStack_5d;
  undefined4 local_5c;
  undefined4 local_58;
  undefined4 local_54;
  undefined4 local_50;
  undefined4 local_4c;
  undefined4 local_48;
  undefined4 local_44;
  undefined4 local_40;
  undefined4 local_3c;
  undefined4 local_38;
  undefined4 local_34;
  undefined4 local_30;
  undefined4 local_2c;
  
  puVar12 = *(undefined4 **)(param_1 + 0xa39fd8);
  iVar2 = hc_get_chip_ops(*(undefined4 *)(param_1 + 0xa797a0));
  local_74 = (uint)(byte)"======== Badnode detector =============\nvow_bn_en = <0/1> 0:dieable, 1:enable\nvow_bn_mon_period = <period> ms\nvow_bn_fallback_th = <count>\nvow_bn_per_th = <TX PER>\n======== Airtime counter test =============\nvow_counter_test = <0/1> 0:dieable, 1:enable\nvow_counter_test_period = <period> ms\nvow_counter_test_band = <band>\nvow_counter_test_avgcnt = <average num> sec\nvow_counter_test_target = <wlanidx>\n======== DVT =============\nvow_dvt_en = <0/1> 0:dieable, 1:enable\nvow_monitor_sta = <STA num>\nvow_show_sta = <STA num>\nvow_monitor_bss = <BSS num>\nvow_monitor_mbss = <MBSS num>\nvow_show_mbss = <MBSS num>\nvow_avg_num = <average num> sec\n======== RED ===========\nvow_set_red_en = <0/1> 0:disable, 1:enable\nvow_set_red_show_sta = <STA num>\nvow_set_red_tar_delay = <tarDelay> us\n======== WATF ===========\nvow_watf_en = <0/1> 0:disable, 1:enable\nvow_watf_q = <level>-<quantum> unit 256us\nvow_watf_add_entry = <level>-<Addr>\nvow_watf_del_entry = <Addr>\n"
                         [param_1 + 0xda];
  MtCmdATEModeCtrl(param_1,1);
  mt_Trigger_Sounding_Packet(param_1,0,0,0,0,0);
  if ((*(uint *)(param_1 + 0xa3ac14) & 1) != 0) {
    if (((0 < DebugLevel) &&
        (printk("%s: ATE has already started, wdev_idx:%u\n","MT_ATEStart",
                *(undefined1 *)(param_1 + 0xa3ad58)), *(char *)(param_1 + 0x79504d) != '\0')) &&
       (0 < DebugLevel)) {
      printk("%s: ATE has already started, wdev_idx:%u\n","MT_ATEStart",
             *(undefined1 *)(param_1 + 0xa3a244));
      return 0;
    }
    return 0;
  }
  if ((*(int *)(param_1 + 0xa3abcc) == 0) &&
     (iVar3 = os_alloc_mem(param_1,param_1 + 0xa3abcc,0x33ff), iVar3 != 0)) goto LAB_00283830;
  *(undefined1 *)(param_1 + 0xa3ad65) = 0;
  *(undefined1 *)(param_1 + 0xa3ad5c) = 1;
  *(undefined1 *)(param_1 + 0xa3ad5e) = 1;
  *(undefined1 *)(param_1 + 0xa3b8bd) = 0;
  *(undefined4 *)(param_1 + 0xa3ad78) = 0x400;
  *(undefined4 *)(param_1 + 0xa3ad80) = 0;
  *(undefined1 *)(param_1 + 0xa3af77) = 0xaa;
  *(undefined4 *)(param_1 + 0xa3ad84) = 0;
  *(undefined4 *)(param_1 + 0xa3aff8) = 1;
  *(undefined2 *)(param_1 + 0xa3ad5a) = 1;
  *(undefined2 *)(param_1 + 0xa3affc) = 0x18;
  *(undefined4 *)(param_1 + 0xa3ba98) = 2;
  *(undefined1 *)(param_1 + 0xa3ba96) = 1;
  *(undefined4 *)(param_1 + 0xa3ba28) = 0;
  __init_waitqueue_head(param_1 + 0xa3ba2c,"&x->wait",&g_EBF_certification);
  mt_asic_pcie_aspm_dym_ctrl(param_1,0,0,0);
  if (*(char *)(param_1 + 0x79504d) != '\0') {
    mt_asic_pcie_aspm_dym_ctrl(param_1,1,0,0);
  }
  set_pcie_aspm_dym_ctrl_cap(param_1,0);
  __memzero(param_1 + 0xa3b70c,0x148);
  *(undefined1 *)(param_1 + 0xa3b774) = 0xff;
  *(undefined1 *)(param_1 + 0xa3b775) = 0xff;
  *(undefined1 *)(param_1 + 0xa3b776) = 0xff;
  *(undefined1 *)(param_1 + 0xa3b777) = 0xff;
  *(ushort *)(param_1 + 0xa3abc8) = (ushort)((byte)"SetPartProfileParameters"[param_1 + 0x18] >> 4);
  *(ushort *)(param_1 + 0xa3abca) = (byte)"SetPartProfileParameters"[param_1 + 0x18] & 0xf;
  if ("SetPartProfileParameters"[param_1 + 0x1b] == 0) {
    uVar7 = 0;
  }
  else {
    bVar10 = 0;
    uVar8 = 0;
    do {
      uVar1 = (uint)bVar10;
      bVar10 = bVar10 + 1;
      uVar8 = uVar8 | 1 << uVar1 & 0xffU;
      uVar7 = (undefined2)uVar8;
    } while (bVar10 < (byte)"SetPartProfileParameters"[param_1 + 0x1b]);
  }
  bVar10 = "rtmp_read_vow_parms_from_file"[param_1 + 1];
  "SetPartProfileParameters"[param_1 + 0x1b] = (char)uVar7;
  if (bVar10 == 0) {
    uVar11 = 0;
  }
  else {
    bVar6 = 0;
    uVar8 = 0;
    do {
      uVar1 = (uint)bVar6;
      bVar6 = bVar6 + 1;
      uVar8 = uVar8 | 1 << uVar1 & 0xffU;
      uVar11 = (undefined2)uVar8;
    } while (bVar6 < bVar10);
  }
  "rtmp_read_vow_parms_from_file"[param_1 + 1] = (char)uVar11;
  iVar3 = net_ad_wrap_service(param_1);
  *(undefined2 *)(iVar3 + 0x112e) = uVar7;
  iVar3 = net_ad_wrap_service(param_1);
  *(undefined2 *)(iVar3 + 0x1e46) = uVar11;
  *(undefined4 *)(param_1 + 0xa3bae8) = 0x60ff;
  *(undefined4 *)(param_1 + 0xa3baec) = 0x240004;
  if (*(code **)(iVar2 + 0x2d0) != (code *)0x0) {
    (**(code **)(iVar2 + 0x2d0))(param_1);
  }
  *(undefined4 *)(param_1 + 0xa39ffc) = 0;
  *(undefined4 *)(param_1 + 0xa39fdc) = 0;
  uVar4 = RTMPMsecsToJiffies(3000);
  *(undefined4 *)(param_1 + 0xa3ba38) = 0;
  *(undefined4 *)(param_1 + 0xa3ba48) = uVar4;
  __init_waitqueue_head(param_1 + 0xa3ba3c,"&x->wait",&g_EBF_certification);
  iVar2 = *(int *)("Set_IRR_TTGOnOff" + param_1 + 4);
  *(undefined1 *)(param_1 + 0xa3ac1c) = *(undefined1 *)(iVar2 + 0x58);
  *(undefined1 *)(param_1 + 0xa3ac1d) = *(undefined1 *)(iVar2 + 0x5e);
  __memzero(param_1 + 0xa3b854,0x60);
  iVar2 = 0;
  do {
    iVar3 = net_ad_wrap_service(param_1);
    iVar3 = iVar2 * 0xd18 + iVar3;
    if (*(int *)(iVar3 + 0x11cc) != 0) {
      os_free_mem();
    }
    __memzero(iVar3 + 0x11b4,0x1c);
    bVar17 = iVar2 != 1;
    *(undefined1 *)(iVar3 + 0x11c4) = 0;
    *(undefined4 *)(iVar3 + 0x11b8) = 0;
    *(int *)(iVar3 + 0x11bc) = iVar2;
    *(undefined4 *)(iVar3 + 0x11c0) = 0;
    *(undefined4 *)(iVar3 + 0x11cc) = 0;
    *(undefined4 *)(iVar3 + 0x11c8) = 1;
    *(undefined4 *)(iVar3 + 0x11b4) = 0;
    iVar2 = 1;
  } while (bVar17);
  __memzero(param_1 + 0xa3b00a,0x28);
  AsicGetRxStat(param_1,9);
  AsicGetRxStat(param_1,10);
  local_68[0] = 'A';
  local_68[1] = 'T';
  local_68[2] = 'E';
  local_68[3] = '_';
  local_64._0_1_ = 'T';
  local_64._1_1_ = 'h';
  local_62._0_1_ = 'r';
  local_62._1_1_ = 'e';
  uStack_60 = 0x6461;
  memset(&uStack_5d,0,0x35);
  *(undefined4 *)(param_1 + 0xa3a058) = 1;
  if (*(char *)(param_1 + 0xa3a010) == '\0') {
    __memzero(param_1 + 0xa3a010,0x44);
    iVar2 = param_1 + 0xa3a014;
    RtmpOSTaskInit(iVar2,local_68,param_1,param_1 + 0xa78454,param_1 + 0xa78478);
    *(undefined4 *)(param_1 + 0xa3a054) = 0;
    *(undefined4 *)(param_1 + 0xa3a044) = 0;
    iVar3 = RtmpOSTaskAttach(iVar2,TestMode_TxThread,iVar2);
    iVar2 = wait_for_completion_timeout(param_1 + 0xa3ba38,*(undefined4 *)(param_1 + 0xa3ba48));
    if (iVar2 != 0 && iVar3 == 0) {
      *(undefined1 *)(param_1 + 0xa3a010) = 1;
      goto LAB_002834a4;
    }
    if (-1 < DebugLevel) {
      printk("%s: tx thread create fail\n","TESTMODE_TXTHREAD_INIT");
    }
    if (iVar3 == 0) goto LAB_002834c4;
LAB_002837c4:
    if (-1 < DebugLevel) {
      printk("%s: initial value fail, ret:%d\n","MT_ATEStart",iVar3);
    }
    *(undefined4 *)(param_1 + 0xa3ac14) = 0x100;
    FUN_0027d3f4(param_1);
  }
  else {
    *(undefined4 *)(param_1 + 0xa3a04c) = 0;
    *(undefined4 *)(param_1 + 0xa3a048) = 0;
LAB_002834a4:
    iVar2 = DebugLevel;
    *(undefined1 *)(param_1 + 0xa3a050) = 0;
    if (0 < iVar2) {
      printk("%s: Initialize thread_idx=%d\n","TESTMODE_TXTHREAD_INIT");
    }
LAB_002834c4:
    if ((*(uint *)("Get_RBIST_IQ_Data_Proc" + param_1 + 0xc) & 0xffff) == 0x7626) {
      local_68[0] = 'A';
      local_68[1] = 'T';
      local_68[2] = 'E';
      local_68[3] = '_';
      local_64._0_1_ = 'P';
      local_64._1_1_ = 'T';
      local_62._0_1_ = 'h';
      local_62._1_1_ = 'r';
      uStack_60._0_1_ = 'e';
      uStack_60._1_1_ = 'a';
      uStack_60._2_1_ = 'd';
      uStack_5d = '\0';
      local_5c = 0;
      local_58 = 0;
      local_54 = 0;
      local_50 = 0;
      local_4c = 0;
      local_48 = 0;
      local_44 = 0;
      local_40 = 0;
      local_3c = 0;
      local_38 = 0;
      local_34 = 0;
      local_30 = 0;
      local_2c = 0;
      if (*(char *)(param_1 + 0xa3baac) == '\0') {
        iVar2 = param_1 + 0xa3bab0;
        __memzero(param_1 + 0xa3baac,0x3c);
        RtmpOSTaskInit(iVar2,local_68,param_1,param_1 + 0xa78454,param_1 + 0xa78478);
        *(undefined4 *)(param_1 + 0xa3bae0) = 0;
        iVar3 = RtmpOSTaskAttach(iVar2,TestMode_PeriodicThread,iVar2);
        iVar2 = wait_for_completion_timeout(param_1 + 0xa3ba38,*(undefined4 *)(param_1 + 0xa3ba48));
        if (iVar2 != 0 && iVar3 == 0) {
          *(undefined1 *)(param_1 + 0xa3baac) = 1;
          *(undefined1 *)(param_1 + 0xa3bae4) = 1;
          goto LAB_00283a18;
        }
        if (-1 < DebugLevel) {
          printk("%s: tx thread Periodic create fail\n","TESTMODE_PeriodicThread_INIT");
        }
        if (iVar3 != 0) goto LAB_002837c4;
      }
      else if (0 < DebugLevel) {
        printk("%s: Initialize Periodic thread Fail\n","TESTMODE_PeriodicThread_INIT");
LAB_00283a18:
        if (0 < DebugLevel) {
          printk("%s: Initialize Periodic thread OK\n","TESTMODE_PeriodicThread_INIT");
        }
      }
    }
    MtATESetMacTxRx(param_1,6,0,0);
    if (*(char *)(param_1 + 0x79504d) != '\0') {
      MtATESetMacTxRx(param_1,6,0,1);
    }
    os_zero_mem(local_68,8);
    local_62 = SUB42(_local_64,2) & 0xff00;
    local_68[0] = -0x7a;
    local_68[1] = ';';
    local_68[2] = '\a';
    local_68[3] = '\0';
    local_64 = 0x100;
    iVar3 = MtATESetRxFilter(param_1,0x73b86,_local_64);
    if (*(char *)(param_1 + 0x79504d) != '\0') {
      local_62._0_1_ = 1;
      iVar3 = MtATESetRxFilter(param_1,local_68,_local_64);
    }
    iVar2 = *(int *)(*(int *)(param_1 + 4) + 0x240);
    if (iVar2 == 0) {
      warn_slowpath_null("include/linux/netdevice.h",0xa06);
      printk(&_LC113);
    }
    else {
      _set_bit(0,iVar2 + 0x50);
    }
    if (*(char *)(param_1 + 0x286285) == '\x01') {
      iVar2 = hc_get_chip_bcn_max_num(*(undefined4 *)(param_1 + 0xa797a0));
      if (iVar2 < (int)local_74) {
        local_74 = hc_get_chip_bcn_max_num(*(undefined4 *)(param_1 + 0xa797a0));
      }
      piVar16 = (int *)("%s: Allocate memory fail!!!\n" + param_1 + 0xc);
      for (iVar2 = 1; iVar5 = hc_get_chip_bcn_max_num(*(undefined4 *)(param_1 + 0xa797a0)),
          iVar2 < iVar5; iVar2 = iVar2 + 1) {
        if (*piVar16 != 0) {
          iVar5 = *(int *)(*piVar16 + 0x240);
          if (iVar5 == 0) {
            warn_slowpath_null("include/linux/netdevice.h",0xa06);
            printk(&_LC113);
          }
          else {
            _set_bit(0,iVar5 + 0x50);
          }
        }
        piVar16 = piVar16 + 0x160d;
      }
    }
    *(uint *)(param_1 + 0xa39f84) = *(uint *)(param_1 + 0xa39f84) | 0x800000;
    chip_set_hif_dma(param_1,2,0);
    pcVar13 = (code *)*puVar12;
    if (pcVar13 != (code *)0x0) {
      iVar3 = (*pcVar13)(param_1);
    }
    pcVar13 = (code *)puVar12[1];
    if (pcVar13 != (code *)0x0) {
      iVar3 = (*pcVar13)(param_1);
    }
    if (*(char *)(param_1 + 0x286285) == '\x01') {
      iVar2 = hc_get_chip_bcn_max_num(*(undefined4 *)(param_1 + 0xa797a0));
      if (iVar2 < (int)local_74) {
        hc_get_chip_bcn_max_num(*(undefined4 *)(param_1 + 0xa797a0));
      }
      piVar16 = (int *)("%s: Allocate memory fail!!!\n" + param_1 + 0xc);
      iVar2 = 1;
      while( true ) {
        iVar5 = hc_get_chip_bcn_max_num(*(undefined4 *)(param_1 + 0xa797a0));
        if (iVar5 <= iVar2) break;
        if (*piVar16 != 0) {
          piVar16[0x237] = 0;
        }
        piVar16 = piVar16 + 0x160d;
        iVar2 = iVar2 + 1;
      }
    }
    chip_set_hif_dma(param_1,2,1);
    APStop(param_1,"======== Badnode detector =============\nvow_bn_en = <0/1> 0:dieable, 1:enable\nvow_bn_mon_period = <period> ms\nvow_bn_fallback_th = <count>\nvow_bn_per_th = <TX PER>\n======== Airtime counter test =============\nvow_counter_test = <0/1> 0:dieable, 1:enable\nvow_counter_test_period = <period> ms\nvow_counter_test_band = <band>\nvow_counter_test_avgcnt = <average num> sec\nvow_counter_test_target = <wlanidx>\n======== DVT =============\nvow_dvt_en = <0/1> 0:dieable, 1:enable\nvow_monitor_sta = <STA num>\nvow_show_sta = <STA num>\nvow_monitor_bss = <BSS num>\nvow_monitor_mbss = <MBSS num>\nvow_show_mbss = <MBSS num>\nvow_avg_num = <average num> sec\n======== RED ===========\nvow_set_red_en = <0/1> 0:disable, 1:enable\nvow_set_red_show_sta = <STA num>\nvow_set_red_tar_delay = <tarDelay> us\n======== WATF ===========\nvow_watf_en = <0/1> 0:disable, 1:enable\nvow_watf_q = <level>-<quantum> unit 256us\nvow_watf_add_entry = <level>-<Addr>\nvow_watf_del_entry = <Addr>\n"
                   + param_1 + 0xe0,0);
    *(undefined1 *)(param_1 + 0xa3baf0) = *(undefined1 *)(param_1 + 0x795071);
    *(undefined1 *)(param_1 + 0x795071) = 0;
    *(undefined2 *)(param_1 + 0xa3baf2) = *(undefined2 *)(&DAT_00794c50 + param_1);
    *(undefined2 *)(&DAT_00794c50 + param_1) = 0;
    *(uint *)(param_1 + 0xa39f84) = *(uint *)(param_1 + 0xa39f84) & 0xffffffbf;
    if (-1 < iVar3) {
      RTMPCancelTimer(param_1 + 0x82910c,&uStack_6f);
      *(uint *)(param_1 + 0xa39f84) = *(uint *)(param_1 + 0xa39f84) | 4;
      hc_set_txcmd_mode(*(undefined4 *)(param_1 + 0xa797a0));
      *(undefined4 *)(param_1 + 0xa3ac14) = 1;
      if (*(char *)(param_1 + 0x79504d) != '\0') {
        iVar2 = net_ad_wrap_service(param_1);
        *(undefined4 *)(iVar2 + 0x11f8) = 1;
      }
      iVar2 = net_ad_wrap_service(param_1);
      *(undefined1 *)(iVar2 + 0x1150) = 2;
      iVar2 = net_ad_wrap_service(param_1);
      *(undefined1 *)(iVar2 + 0x1104) = 1;
      iVar2 = mt_ate_init_wdev(param_1,0);
      if (*(char *)(param_1 + 0x79504d) != '\0') {
        iVar2 = net_ad_wrap_service(param_1);
        local_6e = 0xba221100;
        local_6a = 0x112d;
        if (*(int *)(param_1 + 0xa3a0a8) != 0) {
          os_free_mem();
        }
        iVar3 = os_alloc_mem(param_1,param_1 + 0xa3a0a8,0x33ff);
        if (*(int *)(param_1 + 0x795050) == 2) {
          uVar15 = 100;
        }
        else {
          uVar15 = 0x24;
        }
        iVar5 = net_ad_wrap_service(param_1);
        *(undefined1 *)(iVar5 + 0x1e48) = uVar15;
        iVar5 = net_ad_wrap_service(param_1);
        *(undefined1 *)(iVar5 + 0x1e4a) = uVar15;
        *(undefined4 *)(param_1 + 0xa3abc0) = 0x60ff;
        *(undefined4 *)(param_1 + 0xa3abc4) = 0x240004;
        iVar5 = net_ad_wrap_service(param_1);
        *(undefined1 *)(iVar5 + 0x1e4e) = 0;
        iVar5 = net_ad_wrap_service(param_1);
        *(undefined4 *)(iVar5 + 0x1e34) = 0;
        iVar5 = net_ad_wrap_service(param_1);
        *(undefined4 *)(iVar5 + 0x1e38) = 0;
        iVar5 = net_ad_wrap_service(param_1);
        *(undefined4 *)(iVar5 + 0x13f4) = 0x400;
        iVar5 = net_ad_wrap_service(param_1);
        *(undefined4 *)(iVar5 + 0x13f0) = 1;
        iVar5 = net_ad_wrap_service(param_1);
        *(undefined2 *)(iVar5 + 0x1226) = 1;
        iVar5 = net_ad_wrap_service(param_1);
        *(undefined1 *)(iVar5 + 0x1369) = 0xaa;
        iVar5 = net_ad_wrap_service(param_1);
        *(undefined2 *)(iVar5 + 0x13ee) = 0x18;
        iVar5 = net_ad_wrap_service(param_1);
        *(undefined4 *)(iVar5 + 0x13f8) = 1;
        iVar5 = net_ad_wrap_service(param_1);
        *(undefined4 *)(iVar5 + 0x1e30) = 0xffffffff;
        iVar5 = net_ad_wrap_service(param_1);
        puVar9 = (undefined4 *)(param_1 + 0xa3a0a8);
        *(undefined1 *)(iVar5 + 0x1e1c) = 1;
        puVar12 = (undefined4 *)(param_1 + 0xa3a9f0);
        do {
          puVar14 = (undefined4 *)((int)puVar12 + 6);
          puVar9 = puVar9 + 1;
          *puVar9 = 0;
          *puVar12 = local_6e;
          puVar12[0x18] = local_6e;
          puVar12[0x30] = local_6e;
          *(undefined2 *)(puVar12 + 1) = local_6a;
          *(undefined2 *)(puVar12 + 0x19) = local_6a;
          *(undefined2 *)(puVar12 + 0x31) = local_6a;
          puVar12 = puVar14;
        } while (puVar14 != (undefined4 *)(param_1 + 0xa3aa50));
        *(undefined4 *)(param_1 + 0xa3a9d0) = *(undefined4 *)(param_1 + 0xa3ae37);
        *(undefined4 *)(param_1 + 0xa3a9d4) = *(undefined4 *)(param_1 + 0xa3ae3b);
        *(undefined4 *)(param_1 + 0xa3a9d8) = *(undefined4 *)(param_1 + 0xa3ae3f);
        *(undefined4 *)(param_1 + 0xa3a9dc) = *(undefined4 *)(param_1 + 0xa3ae43);
        *(undefined4 *)(param_1 + 0xa3a9e0) = *(undefined4 *)(param_1 + 0xa3ae47);
        *(undefined4 *)(param_1 + 0xa3a9e8) = *(undefined4 *)(param_1 + 0xa3ae4f);
        *(undefined4 *)(param_1 + 0xa3a9ec) = *(undefined4 *)(param_1 + 0xa3ae53);
        *(undefined4 *)(param_1 + 0xa3a9e4) = *(undefined4 *)(param_1 + 0xa3ae4b);
        *(undefined1 *)(param_1 + 0xa3a9c0) = 2;
        os_zero_mem(param_1 + 0xa3a11c,0x128);
        os_zero_mem(param_1 + 0xa3a098,0xd);
        *(undefined1 *)(param_1 + 0xa3a0a3) = 1;
        *(undefined1 *)(param_1 + 0xa3a0a4) = 1;
        *(undefined4 *)(iVar2 + 0x1208) = 0;
        __init_waitqueue_head(iVar2 + 0x120c,"&x->wait",&g_EBF_certification);
        if (0 < DebugLevel) {
          printk("%s: idx:%u, pkt:%p\n","MT_ATEInitBandInfo",0,*(undefined4 *)(param_1 + 0xa3a0a8));
        }
        iVar2 = mt_ate_init_wdev(param_1,1);
        iVar2 = iVar2 + iVar3;
      }
      TxPowerSKUCtrl(param_1,0,0);
      TxPowerPercentCtrl(param_1,0,0);
      TxPowerBfBackoffCtrl(param_1,0,0);
      if (*(char *)(param_1 + 0x79504d) != '\0') {
        TxPowerSKUCtrl(param_1,0,1);
        TxPowerPercentCtrl(param_1,0,1);
        TxPowerBfBackoffCtrl(param_1,0,1);
      }
      os_zero_mem(param_1 + 0xa3ac30,0x128);
      if (DebugLevel < 1) {
        return iVar2;
      }
      printk("%s: wdev_idx:%u\n","MT_ATEStart",*(undefined1 *)(param_1 + 0xa3ad58));
      if (*(char *)(param_1 + 0x79504d) == '\0') {
        return iVar2;
      }
      if (DebugLevel < 1) {
        return iVar2;
      }
      printk("%s: wdev_idx:%u\n","MT_ATEStart",*(undefined1 *)(param_1 + 0xa3a244));
      return iVar2;
    }
  }
  if (DebugLevel < 0) {
    return iVar3;
  }
  printk("%s(): if init fail, ret:%d\n","MT_ATEStart",iVar3);
LAB_00283830:
  if (DebugLevel < 0) {
    return iVar3;
  }
  printk("%s: Allocate test packet fail at pakcet\n","MT_ATEStart");
  return iVar3;
}

