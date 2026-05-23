// module: mt7915.ko
// function: scan_ch_restore @ 0x142ea0
// size: 1700 bytes
//

/* WARNING: Type propagation algorithm not settling */

undefined4 scan_ch_restore(int param_1,int param_2,char *param_3)

{
  undefined2 uVar1;
  undefined1 *puVar2;
  undefined4 *puVar3;
  undefined4 uVar4;
  uint uVar5;
  int iVar6;
  undefined *puVar7;
  char *pcVar8;
  uint uVar9;
  int iVar10;
  undefined1 uVar11;
  bool bVar12;
  int local_38;
  
  if (param_3 == (char *)0x0) {
    if (*(char *)(param_1 + 0x286285) != '\x01') {
      return 0;
    }
    pcVar8 = "======== Badnode detector =============\nvow_bn_en = <0/1> 0:dieable, 1:enable\nvow_bn_mon_period = <period> ms\nvow_bn_fallback_th = <count>\nvow_bn_per_th = <TX PER>\n======== Airtime counter test =============\nvow_counter_test = <0/1> 0:dieable, 1:enable\nvow_counter_test_period = <period> ms\nvow_counter_test_band = <band>\nvow_counter_test_avgcnt = <average num> sec\nvow_counter_test_target = <wlanidx>\n======== DVT =============\nvow_dvt_en = <0/1> 0:dieable, 1:enable\nvow_monitor_sta = <STA num>\nvow_show_sta = <STA num>\nvow_monitor_bss = <BSS num>\nvow_monitor_mbss = <MBSS num>\nvow_show_mbss = <MBSS num>\nvow_avg_num = <average num> sec\n======== RED ===========\nvow_set_red_en = <0/1> 0:disable, 1:enable\nvow_set_red_show_sta = <STA num>\nvow_set_red_tar_delay = <tarDelay> us\n======== WATF ===========\nvow_watf_en = <0/1> 0:disable, 1:enable\nvow_watf_q = <level>-<quantum> unit 256us\nvow_watf_add_entry = <level>-<Addr>\nvow_watf_del_entry = <Addr>\n"
             + param_1 + 0xe0;
    if (pcVar8 == (char *)0x0) {
      return 0;
    }
    puVar2 = (undefined1 *)0x0;
    puVar3 = (undefined4 *)0x0;
    uVar11 = 0;
  }
  else {
    puVar2 = (undefined1 *)get_scan_ctrl_by_wdev(param_1,param_3);
    puVar3 = (undefined4 *)get_scan_tab_by_wdev(param_1,param_3);
    uVar11 = *puVar2;
    pcVar8 = param_3;
  }
  uVar4 = wlan_operate_get_cen_ch_1(pcVar8);
  wlan_operate_get_bw(pcVar8);
  if (param_2 == 0) {
    HcCrossChannelCheck(param_1,pcVar8,uVar4);
  }
  if ((puVar2 == (undefined1 *)0x0) || (*(int *)(puVar2 + 0x5c) == 0)) {
    if (0 < DebugLevel) {
      printk("%s : restore channel done in non-offchannel scan path\n","scan_ch_restore");
    }
    uVar5 = wlan_operate_get_prim_ch(pcVar8);
    if (uVar5 == 0) goto LAB_001431c4;
LAB_00142f30:
    wlan_operate_set_prim_ch(pcVar8,uVar5 & 0xff);
    local_38 = wlan_operate_get_cen_ch_1(pcVar8);
    uVar4 = wlan_operate_get_bw(pcVar8);
    if (puVar2 == (undefined1 *)0x0) goto LAB_00142f68;
  }
  else {
    if (0 < DebugLevel) {
      printk("%s : restore channel selected from stored channel\n","scan_ch_restore");
    }
    if (pcVar8[0x902] == '\0') {
LAB_001431c4:
      printk(&_LC8,0x8a);
      dump_stack();
      uVar5 = 0;
      goto LAB_00142f30;
    }
    wlan_operate_set_prim_ch(pcVar8);
    local_38 = wlan_operate_get_cen_ch_1(pcVar8);
    uVar4 = wlan_operate_get_bw(pcVar8);
  }
  if (0 < DebugLevel) {
    printk("%s - End of SCAN(TYPE: %d, BandIdx: %d), restore to BW(%d) channel %d, Total BSS[%02d]\n"
           ,"scan_ch_restore",uVar11,puVar2[0x1c6],uVar4,local_38,*puVar3);
  }
LAB_00142f68:
  if (param_2 == 0) {
    iVar10 = GetStaCfgByWdev(param_1,pcVar8);
    if (iVar10 == 0) {
      printk(&_LC0,0xb6);
      dump_stack();
      return 0;
    }
    if ((*(uint *)(param_1 + 0x795124) & 2) != 0) {
      __memzero((void *)(iVar10 + 0x4119),0x20);
      *(byte *)(iVar10 + 0x4139) = *(byte *)(iVar10 + 0x212426);
      memmove((void *)(iVar10 + 0x4119),(void *)(iVar10 + 0x212406),
              (uint)*(byte *)(iVar10 + 0x212426));
    }
    if ((*(uint *)(iVar10 + 0x212464) & 0x81) == 0x81) {
      iVar6 = GetAssociatedAPByWdev(param_1,iVar10);
      if (iVar6 != 0) {
        if (*(char *)(param_1 + 0x794cc6) == '\0') {
          uVar1 = *(undefined2 *)(iVar10 + 0x2124b8);
        }
        else {
          uVar1 = 1;
        }
        RTMPSendNullFrame(param_1,iVar6,*(undefined1 *)(param_1 + 0x794cd0),
                          (uint)(*(int *)(param_1 + 0x795124) << 0x17) >> 0x1f,uVar1);
      }
      if (2 < DebugLevel) {
        printk("%s -- Send null frame\n","scan_ch_restore");
      }
    }
    bVar12 = puVar2 != (undefined1 *)0x0;
    if ((((*(char *)(iVar10 + 0x213390) == '\x01' && bVar12) && (puVar2[0x17c] == '\0')) &&
        (iVar10 = ApCliAutoConnectExec(param_1,param_3), iVar10 == 0)) && (-1 < DebugLevel)) {
      printk("Error in  %s\n","scan_ch_restore");
    }
    uVar5 = (uint)(byte)pcVar8[0xe];
    if (((uVar5 < 2) &&
        (((((*(byte *)(param_1 + 0x286294) & 3) == 3 && (*(int *)(pcVar8 + 0x14) == 2)) ||
          (*(int *)(s_OTH__d__d_N_A__0037170c + param_1 + uVar5 * 0x2137b0 + 0x14) != 0)) &&
         ((iVar10 = param_1 + uVar5 * 0x2137b0, *(int *)(&DAT_0036ee3c + iVar10) != 0 &&
          ((&DAT_00371820)[iVar10] == '\x01')))))) &&
       ((*(int *)(&DAT_0036ee40 + iVar10) == 2 &&
        (s_format__t_id_task_id_task_prempt_00371a7c[iVar10 + 0xd] == '\x01')))) {
      if (!bVar12) {
        return 1;
      }
      if ((*(uint *)(puVar2 + 0x17c) & 0xff00ff) == 0) {
        if (2 < DebugLevel) {
          puVar7 = &_LC4;
          if (local_38 < 0xf) {
            puVar7 = &_LC5;
          }
          printk("[%s] %s AP-Client WPS Partial Scan done!!!\n","scan_ch_restore",puVar7);
        }
        iVar10 = param_1 + uVar5 * 0x2137b0;
        if (s_Monitor_Duration___d_unit____d_m_00371634[iVar10 + 0xc] == '\0') {
          RTMPSetTimer(s_Monitor_Duration___d_unit____d_m_00371634 +
                       param_1 + uVar5 * 0x2137b0 + 0x10,1000);
          s_Monitor_Duration___d_unit____d_m_00371634[iVar10 + 0xc] = '\x01';
        }
      }
    }
    else if (!bVar12) {
      return 1;
    }
    if (((puVar2[2] != '\0') && (pcVar8[0xbb4] != '\0')) && (1 < DebugLevel)) {
      printk("bFastRoamingScan ~~~ Get back to send data ~~~\n");
    }
  }
  else if (param_2 == 1) {
    iVar10 = *(int *)(pcVar8 + 0x3fe4);
    uVar5 = (uint)(byte)"======== Badnode detector =============\nvow_bn_en = <0/1> 0:dieable, 1:enable\nvow_bn_mon_period = <period> ms\nvow_bn_fallback_th = <count>\nvow_bn_per_th = <TX PER>\n======== Airtime counter test =============\nvow_counter_test = <0/1> 0:dieable, 1:enable\nvow_counter_test_period = <period> ms\nvow_counter_test_band = <band>\nvow_counter_test_avgcnt = <average num> sec\nvow_counter_test_target = <wlanidx>\n======== DVT =============\nvow_dvt_en = <0/1> 0:dieable, 1:enable\nvow_monitor_sta = <STA num>\nvow_show_sta = <STA num>\nvow_monitor_bss = <BSS num>\nvow_monitor_mbss = <MBSS num>\nvow_show_mbss = <MBSS num>\nvow_avg_num = <average num> sec\n======== RED ===========\nvow_set_red_en = <0/1> 0:disable, 1:enable\nvow_set_red_show_sta = <STA num>\nvow_set_red_tar_delay = <tarDelay> us\n======== WATF ===========\nvow_watf_en = <0/1> 0:disable, 1:enable\nvow_watf_q = <level>-<quantum> unit 256us\nvow_watf_add_entry = <level>-<Addr>\nvow_watf_del_entry = <Addr>\n"
                        [param_1 + 0xda];
    if (iVar10 == 0) {
      return 0;
    }
    if (((((byte)pcVar8[0x1a] < 0xf) || (*(char *)(param_1 + 0x795074) != '\x01')) ||
        (iVar6 = RadarChannelCheck(param_1), iVar6 == 0)) || (*(char *)(iVar10 + 4) == '\x01')) {
      AsicSetSyncModeAndEnable(param_1,*(undefined2 *)(&DAT_00794c50 + param_1),0,1);
      if (uVar5 != 0) {
        uVar9 = 0;
        pcVar8 = "======== Badnode detector =============\nvow_bn_en = <0/1> 0:dieable, 1:enable\nvow_bn_mon_period = <period> ms\nvow_bn_fallback_th = <count>\nvow_bn_per_th = <TX PER>\n======== Airtime counter test =============\nvow_counter_test = <0/1> 0:dieable, 1:enable\nvow_counter_test_period = <period> ms\nvow_counter_test_band = <band>\nvow_counter_test_avgcnt = <average num> sec\nvow_counter_test_target = <wlanidx>\n======== DVT =============\nvow_dvt_en = <0/1> 0:dieable, 1:enable\nvow_monitor_sta = <STA num>\nvow_show_sta = <STA num>\nvow_monitor_bss = <BSS num>\nvow_monitor_mbss = <MBSS num>\nvow_show_mbss = <MBSS num>\nvow_avg_num = <average num> sec\n======== RED ===========\nvow_set_red_en = <0/1> 0:disable, 1:enable\nvow_set_red_show_sta = <STA num>\nvow_set_red_tar_delay = <tarDelay> us\n======== WATF ===========\nvow_watf_en = <0/1> 0:disable, 1:enable\nvow_watf_q = <level>-<quantum> unit 256us\nvow_watf_add_entry = <level>-<Addr>\nvow_watf_del_entry = <Addr>\n"
                 + param_1 + 0xe0;
        do {
          while ((uVar9 = uVar9 + 1, pcVar8[0x1a] == param_3[0x1a] && (pcVar8[0xb1c] != '\0'))) {
            UpdateBeaconHandler(param_1,pcVar8,5);
            pcVar8 = pcVar8 + 0x5834;
            if (uVar5 == uVar9) {
              return 1;
            }
          }
          pcVar8 = pcVar8 + 0x5834;
        } while (uVar5 != uVar9);
      }
    }
    else {
      if (*(int *)(iVar10 + 0x10) == 0) {
        *(undefined1 *)(iVar10 + 4) = 2;
        return 1;
      }
      *(undefined1 *)(iVar10 + 4) = 0;
      AsicSetSyncModeAndEnable(param_1,*(undefined2 *)(&DAT_00794c50 + param_1),0,1);
      if (uVar5 != 0) {
        uVar9 = 0;
        pcVar8 = "======== Badnode detector =============\nvow_bn_en = <0/1> 0:dieable, 1:enable\nvow_bn_mon_period = <period> ms\nvow_bn_fallback_th = <count>\nvow_bn_per_th = <TX PER>\n======== Airtime counter test =============\nvow_counter_test = <0/1> 0:dieable, 1:enable\nvow_counter_test_period = <period> ms\nvow_counter_test_band = <band>\nvow_counter_test_avgcnt = <average num> sec\nvow_counter_test_target = <wlanidx>\n======== DVT =============\nvow_dvt_en = <0/1> 0:dieable, 1:enable\nvow_monitor_sta = <STA num>\nvow_show_sta = <STA num>\nvow_monitor_bss = <BSS num>\nvow_monitor_mbss = <MBSS num>\nvow_show_mbss = <MBSS num>\nvow_avg_num = <average num> sec\n======== RED ===========\nvow_set_red_en = <0/1> 0:disable, 1:enable\nvow_set_red_show_sta = <STA num>\nvow_set_red_tar_delay = <tarDelay> us\n======== WATF ===========\nvow_watf_en = <0/1> 0:disable, 1:enable\nvow_watf_q = <level>-<quantum> unit 256us\nvow_watf_add_entry = <level>-<Addr>\nvow_watf_del_entry = <Addr>\n"
                 + param_1 + 0xe0;
        do {
          uVar9 = uVar9 + 1;
          if (((param_3 == (char *)0x0) || (pcVar8[0x1a] == param_3[0x1a])) &&
             (pcVar8[0xb1c] != '\0')) {
            UpdateBeaconHandler(param_1,pcVar8,5);
          }
          pcVar8 = pcVar8 + 0x5834;
        } while (uVar5 != uVar9);
      }
    }
  }
  return 1;
}

