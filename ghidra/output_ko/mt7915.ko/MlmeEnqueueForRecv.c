// module: mt7915.ko
// function: MlmeEnqueueForRecv @ 0x12e084
// size: 2792 bytes
//

undefined4
MlmeEnqueueForRecv(int param_1,int param_2,void *param_3,uint param_4,byte *param_5,
                  undefined1 param_6,char *param_7,undefined1 param_8)

{
  byte bVar1;
  bool bVar2;
  bool bVar3;
  int iVar4;
  char cVar5;
  uint uVar6;
  int iVar7;
  char *pcVar8;
  uint uVar9;
  int iVar10;
  uint uVar11;
  undefined *puVar12;
  int iVar13;
  char *pcVar14;
  int iVar15;
  int *local_5c;
  uint local_50;
  int local_38;
  undefined4 local_34;
  undefined4 local_30;
  int local_2c [2];
  
  local_2c[0] = 0;
  local_38 = 0xff;
  if ((*(uint *)(param_1 + 0xa3ac14) & 1) != 0) {
    return 0;
  }
  if (*(int *)(param_1 + 0xa77bb4) == 1) {
    if ((*(uint *)(*(int *)(param_1 + 0xa77bb8) + 0x4e0) & 1) != 0) {
      return 0;
    }
    uVar6 = *(uint *)(param_1 + 0xa39f84);
  }
  else {
    uVar6 = *(uint *)(param_1 + 0xa39f84);
  }
  if ((uVar6 & 0x140) != 0) {
    if (DebugLevel < 0) {
      return 0;
    }
    printk("%s(): fRTMP_ADAPTER_HALT_IN_PROGRESS\n","MlmeEnqueueForRecv");
    return 0;
  }
  if (param_7 == (char *)0x0) {
    if (*(char *)(param_1 + 0x286285) != '\0') {
      return 0;
    }
    if (DebugLevel < 0) {
      return 0;
    }
    printk("%s():wdev can\'t find!\n","MlmeEnqueueForRecv");
    return 0;
  }
  if ((param_7[0x28] == '\0') &&
     (iVar4 = hc_get_chip_wtbl_no_matched_idx(*(undefined4 *)(param_1 + 0xa797a0)), iVar4 != param_2
     )) {
    if (DebugLevel < 3) {
      return 0;
    }
    printk("%s(): wdev (%d) not ready\n","MlmeEnqueueForRecv",param_7[0xc]);
    return 0;
  }
  if (0x900 < param_4) {
    if (DebugLevel < 0) {
      return 0;
    }
    printk("%s(): frame too large, size = %ld\n","MlmeEnqueueForRecv",param_4);
    return 0;
  }
  if (param_5 == (byte *)0x0) {
    if (DebugLevel < 0) {
      return 0;
    }
    printk("%s(): frame is Null\n","MlmeEnqueueForRecv");
    return 0;
  }
  iVar7 = param_1 + 0x7960f8;
  iVar4 = MlmeQueueFull(iVar7,0);
  if (iVar4 != 0) {
    RtmpOsMlmeUp(param_1 + 0x286298);
    return 0;
  }
  cVar5 = *(char *)(param_1 + 0x286285);
  local_50 = 0;
  if (cVar5 == '\x01') {
    uVar6 = (uint)(byte)(&DAT_003678f9)[param_1];
    if (uVar6 == 0) {
      bVar2 = false;
    }
    else {
      puVar12 = &DAT_00371c92 + param_1;
      do {
        iVar4 = memcmp(puVar12,param_5 + 10,6);
        if ((iVar4 == 0) && (puVar12[-0x4112] != '\0')) {
          bVar2 = true;
          goto LAB_0012e488;
        }
        local_50 = local_50 + 1 & 0xff;
        puVar12 = puVar12 + 0x2137b0;
      } while (local_50 != uVar6);
      local_50 = 0;
      bVar2 = false;
LAB_0012e488:
      puVar12 = &DAT_0036db73 + param_1;
      uVar9 = 0;
      uVar11 = 0;
      do {
        iVar4 = memcmp(puVar12,param_5 + 4,6);
        puVar12 = puVar12 + 0x2137b0;
        if (iVar4 == 0) {
          bVar2 = true;
          param_7 = &DAT_0036db58 + param_1 + uVar9 * 0x2137b0;
          local_50 = uVar11;
          break;
        }
        uVar9 = uVar9 + 1;
        uVar11 = uVar9 & 0xff;
      } while (uVar11 < uVar6);
    }
    bVar1 = "======== Badnode detector =============\nvow_bn_en = <0/1> 0:dieable, 1:enable\nvow_bn_mon_period = <period> ms\nvow_bn_fallback_th = <count>\nvow_bn_per_th = <TX PER>\n======== Airtime counter test =============\nvow_counter_test = <0/1> 0:dieable, 1:enable\nvow_counter_test_period = <period> ms\nvow_counter_test_band = <band>\nvow_counter_test_avgcnt = <average num> sec\nvow_counter_test_target = <wlanidx>\n======== DVT =============\nvow_dvt_en = <0/1> 0:dieable, 1:enable\nvow_monitor_sta = <STA num>\nvow_show_sta = <STA num>\nvow_monitor_bss = <BSS num>\nvow_monitor_mbss = <MBSS num>\nvow_show_mbss = <MBSS num>\nvow_avg_num = <average num> sec\n======== RED ===========\nvow_set_red_en = <0/1> 0:disable, 1:enable\nvow_set_red_show_sta = <STA num>\nvow_set_red_tar_delay = <tarDelay> us\n======== WATF ===========\nvow_watf_en = <0/1> 0:disable, 1:enable\nvow_watf_q = <level>-<quantum> unit 256us\nvow_watf_add_entry = <level>-<Addr>\nvow_watf_del_entry = <Addr>\n"
            [param_1 + 0xda];
    if (bVar1 != 0) {
      pcVar14 = "======== Badnode detector =============\nvow_bn_en = <0/1> 0:dieable, 1:enable\nvow_bn_mon_period = <period> ms\nvow_bn_fallback_th = <count>\nvow_bn_per_th = <TX PER>\n======== Airtime counter test =============\nvow_counter_test = <0/1> 0:dieable, 1:enable\nvow_counter_test_period = <period> ms\nvow_counter_test_band = <band>\nvow_counter_test_avgcnt = <average num> sec\nvow_counter_test_target = <wlanidx>\n======== DVT =============\nvow_dvt_en = <0/1> 0:dieable, 1:enable\nvow_monitor_sta = <STA num>\nvow_show_sta = <STA num>\nvow_monitor_bss = <BSS num>\nvow_monitor_mbss = <MBSS num>\nvow_show_mbss = <MBSS num>\nvow_avg_num = <average num> sec\n======== RED ===========\nvow_set_red_en = <0/1> 0:disable, 1:enable\nvow_set_red_show_sta = <STA num>\nvow_set_red_tar_delay = <tarDelay> us\n======== WATF ===========\nvow_watf_en = <0/1> 0:disable, 1:enable\nvow_watf_q = <level>-<quantum> unit 256us\nvow_watf_add_entry = <level>-<Addr>\nvow_watf_del_entry = <Addr>\n"
                + param_1 + 0xfb;
      uVar6 = 0;
      do {
        iVar4 = memcmp(pcVar14,param_5 + 4,6);
        pcVar14 = pcVar14 + 0x5834;
        if (iVar4 == 0) {
          param_7 = "======== Badnode detector =============\nvow_bn_en = <0/1> 0:dieable, 1:enable\nvow_bn_mon_period = <period> ms\nvow_bn_fallback_th = <count>\nvow_bn_per_th = <TX PER>\n======== Airtime counter test =============\nvow_counter_test = <0/1> 0:dieable, 1:enable\nvow_counter_test_period = <period> ms\nvow_counter_test_band = <band>\nvow_counter_test_avgcnt = <average num> sec\nvow_counter_test_target = <wlanidx>\n======== DVT =============\nvow_dvt_en = <0/1> 0:dieable, 1:enable\nvow_monitor_sta = <STA num>\nvow_show_sta = <STA num>\nvow_monitor_bss = <BSS num>\nvow_monitor_mbss = <MBSS num>\nvow_show_mbss = <MBSS num>\nvow_avg_num = <average num> sec\n======== RED ===========\nvow_set_red_en = <0/1> 0:disable, 1:enable\nvow_set_red_show_sta = <STA num>\nvow_set_red_tar_delay = <tarDelay> us\n======== WATF ===========\nvow_watf_en = <0/1> 0:disable, 1:enable\nvow_watf_q = <level>-<quantum> unit 256us\nvow_watf_add_entry = <level>-<Addr>\nvow_watf_del_entry = <Addr>\n"
                    + uVar6 * 0x5834 + param_1 + 0xe0;
          if ((((&DAT_0036790d)[param_1] == '\0') || (!bVar2)) || ((*param_5 & 0xf0) != 0xb0))
          goto LAB_0012e60c;
          iVar4 = RTMPLookupRepeaterCliEntry(param_1,0,param_5 + 4,1);
          bVar3 = true;
          if (iVar4 == 0) goto LAB_0012e60c;
          goto LAB_0012ea3c;
        }
        uVar6 = uVar6 + 1;
      } while ((uVar6 & 0xff) < (uint)bVar1);
    }
    if ((&DAT_0036790d)[param_1] == '\0') goto LAB_0012ea54;
    if (!bVar2) {
      iVar4 = preCheckMsgTypeSubset(param_1,param_5,&local_38);
      if (iVar4 == 0) {
LAB_0012ea78:
        local_5c = local_2c;
        if ((!bVar2) ||
           (iVar4 = ApCliMsgTypeSubst(param_1,param_5,&local_38,local_5c), pcVar14 = param_7,
           iVar4 == 0)) goto LAB_0012e60c;
      }
      else {
LAB_0012e828:
        cVar5 = *(char *)((int)param_3 + 5);
        if (cVar5 == '\0') {
          cVar5 = "rtmp_read_dot11v_mbssid_cfg_from_file"[param_1 + 0x20];
        }
        iVar4 = HcGetBandInfoByChannel(param_1,cVar5);
        iVar13 = iVar4 * 0xaf5d8 + param_1;
        if ((((*(char *)(iVar13 + 0x829272) == '\0') ||
             (pcVar14 = *(char **)(iVar13 + 0x8d8840), pcVar14 == (char *)0x0)) ||
            (*(int *)(pcVar14 + 0x14) != 2)) &&
           (pcVar14 = param_7,
           "======== Badnode detector =============\nvow_bn_en = <0/1> 0:dieable, 1:enable\nvow_bn_mon_period = <period> ms\nvow_bn_fallback_th = <count>\nvow_bn_per_th = <TX PER>\n======== Airtime counter test =============\nvow_counter_test = <0/1> 0:dieable, 1:enable\nvow_counter_test_period = <period> ms\nvow_counter_test_band = <band>\nvow_counter_test_avgcnt = <average num> sec\nvow_counter_test_target = <wlanidx>\n======== DVT =============\nvow_dvt_en = <0/1> 0:dieable, 1:enable\nvow_monitor_sta = <STA num>\nvow_show_sta = <STA num>\nvow_monitor_bss = <BSS num>\nvow_monitor_mbss = <MBSS num>\nvow_show_mbss = <MBSS num>\nvow_avg_num = <average num> sec\n======== RED ===========\nvow_set_red_en = <0/1> 0:disable, 1:enable\nvow_set_red_show_sta = <STA num>\nvow_set_red_tar_delay = <tarDelay> us\n======== WATF ===========\nvow_watf_en = <0/1> 0:disable, 1:enable\nvow_watf_q = <level>-<quantum> unit 256us\nvow_watf_add_entry = <level>-<Addr>\nvow_watf_del_entry = <Addr>\n"
           [param_1 + 0xda] != '\0')) {
          uVar6 = 0;
          do {
            iVar15 = uVar6 * 0x5834;
            pcVar14 = "======== Badnode detector =============\nvow_bn_en = <0/1> 0:dieable, 1:enable\nvow_bn_mon_period = <period> ms\nvow_bn_fallback_th = <count>\nvow_bn_per_th = <TX PER>\n======== Airtime counter test =============\nvow_counter_test = <0/1> 0:dieable, 1:enable\nvow_counter_test_period = <period> ms\nvow_counter_test_band = <band>\nvow_counter_test_avgcnt = <average num> sec\nvow_counter_test_target = <wlanidx>\n======== DVT =============\nvow_dvt_en = <0/1> 0:dieable, 1:enable\nvow_monitor_sta = <STA num>\nvow_show_sta = <STA num>\nvow_monitor_bss = <BSS num>\nvow_monitor_mbss = <MBSS num>\nvow_show_mbss = <MBSS num>\nvow_avg_num = <average num> sec\n======== RED ===========\nvow_set_red_en = <0/1> 0:disable, 1:enable\nvow_set_red_show_sta = <STA num>\nvow_set_red_tar_delay = <tarDelay> us\n======== WATF ===========\nvow_watf_en = <0/1> 0:disable, 1:enable\nvow_watf_q = <level>-<quantum> unit 256us\nvow_watf_add_entry = <level>-<Addr>\nvow_watf_del_entry = <Addr>\n"
                      + param_1 + iVar15 + 0xe0;
            iVar13 = HcGetBandByWdev(pcVar14);
            uVar6 = uVar6 + 1 & 0xff;
            if ((iVar4 == iVar13) &&
               (param_7 = pcVar14,
               "Wrong format, vow_watf_q=[Level]-[Quantum]\n[Level] should be among 0 to 3 !\n[Quantum] unit is 256us.\n"
               [param_1 + iVar15] != '\0')) {
              cVar5 = *(char *)(param_1 + 0x286285);
              goto LAB_0012e228;
            }
            pcVar14 = param_7;
          } while (uVar6 < (byte)"======== Badnode detector =============\nvow_bn_en = <0/1> 0:dieable, 1:enable\nvow_bn_mon_period = <period> ms\nvow_bn_fallback_th = <count>\nvow_bn_per_th = <TX PER>\n======== Airtime counter test =============\nvow_counter_test = <0/1> 0:dieable, 1:enable\nvow_counter_test_period = <period> ms\nvow_counter_test_band = <band>\nvow_counter_test_avgcnt = <average num> sec\nvow_counter_test_target = <wlanidx>\n======== DVT =============\nvow_dvt_en = <0/1> 0:dieable, 1:enable\nvow_monitor_sta = <STA num>\nvow_show_sta = <STA num>\nvow_monitor_bss = <BSS num>\nvow_monitor_mbss = <MBSS num>\nvow_show_mbss = <MBSS num>\nvow_avg_num = <average num> sec\n======== RED ===========\nvow_set_red_en = <0/1> 0:disable, 1:enable\nvow_set_red_show_sta = <STA num>\nvow_set_red_tar_delay = <tarDelay> us\n======== WATF ===========\nvow_watf_en = <0/1> 0:disable, 1:enable\nvow_watf_q = <level>-<quantum> unit 256us\nvow_watf_add_entry = <level>-<Addr>\nvow_watf_del_entry = <Addr>\n"
                                 [param_1 + 0xda]);
        }
      }
LAB_0012e698:
      param_7 = pcVar14;
      cVar5 = *(char *)(param_1 + 0x286285);
      goto LAB_0012e228;
    }
    if ((*param_5 & 0xf0) == 0xb0) {
      bVar3 = false;
      iVar4 = RTMPLookupRepeaterCliEntry(param_1,0,param_5 + 4,1);
      if (iVar4 == 0) goto LAB_0012ea54;
LAB_0012ea3c:
      if (*(char *)(iVar4 + 0x108) != '\0') {
        param_7 = (char *)(iVar4 + 0xe0);
      }
      if (!bVar3) goto LAB_0012ea54;
LAB_0012e60c:
      local_5c = local_2c;
      iVar4 = APMsgTypeSubst(param_1,param_5,&local_38,local_5c);
      if (iVar4 == 0) {
        if (DebugLevel < 0) {
          return 0;
        }
        printk("%s(): un-recongnized mgmt->subtype=%d, STA-%02x:%02x:%02x:%02x:%02x:%02x\n",
               "MlmeEnqueueForRecv",*param_5 >> 4,param_5[10],param_5[0xb],param_5[0xc],param_5[0xd]
               ,param_5[0xe],param_5[0xf]);
        return 0;
      }
      pcVar14 = param_7;
      if ((param_7[0xaa8] == '\0') &&
         ("======== Badnode detector =============\nvow_bn_en = <0/1> 0:dieable, 1:enable\nvow_bn_mon_period = <period> ms\nvow_bn_fallback_th = <count>\nvow_bn_per_th = <TX PER>\n======== Airtime counter test =============\nvow_counter_test = <0/1> 0:dieable, 1:enable\nvow_counter_test_period = <period> ms\nvow_counter_test_band = <band>\nvow_counter_test_avgcnt = <average num> sec\nvow_counter_test_target = <wlanidx>\n======== DVT =============\nvow_dvt_en = <0/1> 0:dieable, 1:enable\nvow_monitor_sta = <STA num>\nvow_show_sta = <STA num>\nvow_monitor_bss = <BSS num>\nvow_monitor_mbss = <MBSS num>\nvow_show_mbss = <MBSS num>\nvow_avg_num = <average num> sec\n======== RED ===========\nvow_set_red_en = <0/1> 0:disable, 1:enable\nvow_set_red_show_sta = <STA num>\nvow_set_red_tar_delay = <tarDelay> us\n======== WATF ===========\nvow_watf_en = <0/1> 0:disable, 1:enable\nvow_watf_q = <level>-<quantum> unit 256us\nvow_watf_add_entry = <level>-<Addr>\nvow_watf_del_entry = <Addr>\n"
          [param_1 + 0xda] != '\0')) {
        pcVar8 = "======== Badnode detector =============\nvow_bn_en = <0/1> 0:dieable, 1:enable\nvow_bn_mon_period = <period> ms\nvow_bn_fallback_th = <count>\nvow_bn_per_th = <TX PER>\n======== Airtime counter test =============\nvow_counter_test = <0/1> 0:dieable, 1:enable\nvow_counter_test_period = <period> ms\nvow_counter_test_band = <band>\nvow_counter_test_avgcnt = <average num> sec\nvow_counter_test_target = <wlanidx>\n======== DVT =============\nvow_dvt_en = <0/1> 0:dieable, 1:enable\nvow_monitor_sta = <STA num>\nvow_show_sta = <STA num>\nvow_monitor_bss = <BSS num>\nvow_monitor_mbss = <MBSS num>\nvow_show_mbss = <MBSS num>\nvow_avg_num = <average num> sec\n======== RED ===========\nvow_set_red_en = <0/1> 0:disable, 1:enable\nvow_set_red_show_sta = <STA num>\nvow_set_red_tar_delay = <tarDelay> us\n======== WATF ===========\nvow_watf_en = <0/1> 0:disable, 1:enable\nvow_watf_q = <level>-<quantum> unit 256us\nvow_watf_add_entry = <level>-<Addr>\nvow_watf_del_entry = <Addr>\n"
                 + param_1 + 0xe0;
        do {
          if ((pcVar8 != param_7) && (pcVar14 = pcVar8, pcVar8[0xaa8] != '\0')) break;
          pcVar8 = pcVar8 + 0x5834;
          pcVar14 = param_7;
        } while (pcVar8 != "%s: Allocate memory fail!!!\n" +
                           (uint)(byte)("======== Badnode detector =============\nvow_bn_en = <0/1> 0:dieable, 1:enable\nvow_bn_mon_period = <period> ms\nvow_bn_fallback_th = <count>\nvow_bn_per_th = <TX PER>\n======== Airtime counter test =============\nvow_counter_test = <0/1> 0:dieable, 1:enable\nvow_counter_test_period = <period> ms\nvow_counter_test_band = <band>\nvow_counter_test_avgcnt = <average num> sec\nvow_counter_test_target = <wlanidx>\n======== DVT =============\nvow_dvt_en = <0/1> 0:dieable, 1:enable\nvow_monitor_sta = <STA num>\nvow_show_sta = <STA num>\nvow_monitor_bss = <BSS num>\nvow_monitor_mbss = <MBSS num>\nvow_show_mbss = <MBSS num>\nvow_avg_num = <average num> sec\n======== RED ===========\nvow_set_red_en = <0/1> 0:disable, 1:enable\nvow_set_red_show_sta = <STA num>\nvow_set_red_tar_delay = <tarDelay> us\n======== WATF ===========\nvow_watf_en = <0/1> 0:disable, 1:enable\nvow_watf_q = <level>-<quantum> unit 256us\nvow_watf_add_entry = <level>-<Addr>\nvow_watf_del_entry = <Addr>\n"
                                        [param_1 + 0xda] - 1) * 0x5834 + param_1 + 0xc);
      }
      goto LAB_0012e698;
    }
LAB_0012ea54:
    iVar4 = preCheckMsgTypeSubset(param_1,param_5,&local_38);
    if (iVar4 == 0) goto LAB_0012ea78;
    if (!bVar2) goto LAB_0012e828;
    if (local_38 == 4) {
      if (local_2c[0] == 6) {
        iVar4 = local_50 * 0x2137b0 + param_1;
        *(undefined4 *)(&DAT_00580e90 + iVar4) = jiffies;
        *(undefined4 *)(&DAT_00580e94 + iVar4) = *(undefined4 *)(param_1 + 0x7960e8);
        cVar5 = *(char *)(param_1 + 0x286285);
        goto LAB_0012e228;
      }
      if (*(char *)(param_1 + 0x286285) == '\0') goto LAB_0012e734;
      goto LAB_0012e7bc;
    }
    if (*(char *)(param_1 + 0x286285) == '\0') goto LAB_0012e734;
  }
  else {
LAB_0012e228:
    if (cVar5 == '\0') {
LAB_0012e734:
      local_5c = local_2c;
      iVar4 = MsgTypeSubst(param_1,param_5,&local_38,local_5c);
      if (iVar4 == 0) {
        if (DebugLevel < 0) {
          return 0;
        }
        printk("%s(): un-recongnized mgmt->subtype=%d\n","MlmeEnqueueForRecv",*param_5 >> 4);
        return 0;
      }
    }
    if (local_38 == 4) {
LAB_0012e7bc:
      local_5c = local_2c;
      sync_fsm_msg_pre_checker(param_1,param_5,&local_38,local_5c);
      goto LAB_0012e258;
    }
  }
  local_5c = local_2c;
  iVar4 = sync_fsm_msg_pre_checker(param_1,param_5,&local_38,local_5c);
  if ((iVar4 == 1) && (0 < DebugLevel)) {
    printk("%s(): NEED CHECK IN %d\n","MlmeEnqueueForRecv",0x15d6);
  }
LAB_0012e258:
  local_30 = 0;
  local_34 = 0;
  if ((*(int *)(param_1 + 0x286280) != 2) &&
     (iVar4 = hc_get_hif_type(*(undefined4 *)(param_1 + 0xa797a0)), iVar4 != 2)) {
    AsicGetTsfTime(param_1,&local_34,&local_30,0);
  }
  iVar4 = param_1 + 0x796104;
  _raw_spin_lock_bh(iVar4);
  iVar13 = *(int *)(param_1 + 0x796100);
  iVar15 = iVar13 * 0x930 + param_1;
  if (*(char *)(iVar15 + 0x796a2a) != '\0') {
    _raw_spin_unlock_bh(iVar4);
    return 0;
  }
  *(int *)(param_1 + 0x796100) = iVar13 + 1;
  if (iVar13 + 1 == 0x100) {
    *(undefined4 *)(param_1 + 0x796100) = 0;
  }
  iVar10 = param_1 + 0x796000 + iVar13 * 0x930;
  *(int *)(param_1 + 0x7960f8) = *(int *)(param_1 + 0x7960f8) + 1;
  *(char **)(iVar10 + 0xa34) = param_7;
  *(undefined1 *)(iVar15 + 0x796a2a) = 1;
  *(undefined4 *)(iVar10 + 0xa18) = local_30;
  *(uint *)(iVar10 + 0xa10) = param_4;
  *(int *)(iVar10 + 0xa08) = local_38;
  *(int *)(iVar10 + 0xa0c) = local_2c[0];
  *(undefined4 *)(iVar10 + 0xa1c) = local_34;
  memmove((void *)(iVar7 + iVar13 * 0x930 + 0x928),param_3,6);
  *(undefined1 *)(iVar10 + 0xa26) = *(undefined1 *)((int)param_3 + 4);
  iVar10 = param_1 + 0x796000 + iVar13 * 0x930;
  *(undefined1 *)(iVar15 + 0x796a2b) = param_6;
  *(short *)(iVar15 + 0x796a28) = (short)param_2;
  cVar5 = *(char *)((int)param_3 + 5);
  if (cVar5 == '\0') {
    cVar5 = "rtmp_read_dot11v_mbssid_cfg_from_file"[param_1 + 0x20];
  }
  *(char *)(iVar10 + 0xa27) = cVar5;
  *(undefined1 *)(iVar10 + 0xa30) = param_8;
  *(uint *)(iVar15 + 0x796a2c) = local_50;
  memmove((void *)(iVar7 + iVar13 * 0x930 + 0x10),param_5,param_4);
  _raw_spin_unlock_bh(iVar4);
  RtmpOsMlmeUp(param_1 + 0x286298);
  return 1;
}

