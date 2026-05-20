// module: mt7915.ko
// function: ZTE_Bss_Report_Info_Active @ 0x1605b0
// size: 988 bytes
//

undefined4 ZTE_Bss_Report_Info_Active(int param_1,int param_2,int param_3)

{
  byte bVar1;
  undefined2 uVar2;
  byte bVar3;
  byte bVar4;
  int *piVar5;
  int *piVar6;
  undefined1 uVar7;
  char cVar8;
  byte bVar9;
  byte bVar10;
  int iVar11;
  undefined4 uVar12;
  int iVar13;
  uint uVar14;
  char *pcVar15;
  uint uVar16;
  int *local_1c;
  
  iVar11 = hc_get_chip_cap(*(undefined4 *)(param_1 + 0xa797a0));
  bVar10 = *(byte *)(iVar11 + 0x6e);
  os_alloc_mem(0,&local_1c,0x45c);
  if (local_1c == (int *)0x0) {
    uVar12 = 0;
    if (-1 < DebugLevel) {
      printk("ZTE_Bss_Report_Info_Active alloc memory failed sizeof=%d",0x45c);
    }
  }
  else {
    __memzero(local_1c,0x45c);
    piVar5 = local_1c;
    iVar13 = param_2 * 0x5834;
    iVar11 = param_1 + iVar13 + 0x100;
    pcVar15 = "======== Badnode detector =============\nvow_bn_en = <0/1> 0:dieable, 1:enable\nvow_bn_mon_period = <period> ms\nvow_bn_fallback_th = <count>\nvow_bn_per_th = <TX PER>\n======== Airtime counter test =============\nvow_counter_test = <0/1> 0:dieable, 1:enable\nvow_counter_test_period = <period> ms\nvow_counter_test_band = <band>\nvow_counter_test_avgcnt = <average num> sec\nvow_counter_test_target = <wlanidx>\n======== DVT =============\nvow_dvt_en = <0/1> 0:dieable, 1:enable\nvow_monitor_sta = <STA num>\nvow_show_sta = <STA num>\nvow_monitor_bss = <BSS num>\nvow_monitor_mbss = <MBSS num>\nvow_show_mbss = <MBSS num>\nvow_avg_num = <average num> sec\n======== RED ===========\nvow_set_red_en = <0/1> 0:disable, 1:enable\nvow_set_red_show_sta = <STA num>\nvow_set_red_tar_delay = <tarDelay> us\n======== WATF ===========\nvow_watf_en = <0/1> 0:disable, 1:enable\nvow_watf_q = <level>-<quantum> unit 256us\nvow_watf_add_entry = <level>-<Addr>\nvow_watf_del_entry = <Addr>\n"
              + param_1 + iVar13 + 0xe0;
    *local_1c = param_2;
    local_1c[1] = *(int *)(
                          "======== Badnode detector =============\nvow_bn_en = <0/1> 0:dieable, 1:enable\nvow_bn_mon_period = <period> ms\nvow_bn_fallback_th = <count>\nvow_bn_per_th = <TX PER>\n======== Airtime counter test =============\nvow_counter_test = <0/1> 0:dieable, 1:enable\nvow_counter_test_period = <period> ms\nvow_counter_test_band = <band>\nvow_counter_test_avgcnt = <average num> sec\nvow_counter_test_target = <wlanidx>\n======== DVT =============\nvow_dvt_en = <0/1> 0:dieable, 1:enable\nvow_monitor_sta = <STA num>\nvow_show_sta = <STA num>\nvow_monitor_bss = <BSS num>\nvow_monitor_mbss = <MBSS num>\nvow_show_mbss = <MBSS num>\nvow_avg_num = <average num> sec\n======== RED ===========\nvow_set_red_en = <0/1> 0:disable, 1:enable\nvow_set_red_show_sta = <STA num>\nvow_set_red_tar_delay = <tarDelay> us\n======== WATF ===========\nvow_watf_en = <0/1> 0:disable, 1:enable\nvow_watf_q = <level>-<quantum> unit 256us\nvow_watf_add_entry = <level>-<Addr>\nvow_watf_del_entry = <Addr>\n"
                          + iVar11 + 1);
    uVar2 = *(undefined2 *)
             (
             "======== Badnode detector =============\nvow_bn_en = <0/1> 0:dieable, 1:enable\nvow_bn_mon_period = <period> ms\nvow_bn_fallback_th = <count>\nvow_bn_per_th = <TX PER>\n======== Airtime counter test =============\nvow_counter_test = <0/1> 0:dieable, 1:enable\nvow_counter_test_period = <period> ms\nvow_counter_test_band = <band>\nvow_counter_test_avgcnt = <average num> sec\nvow_counter_test_target = <wlanidx>\n======== DVT =============\nvow_dvt_en = <0/1> 0:dieable, 1:enable\nvow_monitor_sta = <STA num>\nvow_show_sta = <STA num>\nvow_monitor_bss = <BSS num>\nvow_monitor_mbss = <MBSS num>\nvow_show_mbss = <MBSS num>\nvow_avg_num = <average num> sec\n======== RED ===========\nvow_set_red_en = <0/1> 0:disable, 1:enable\nvow_set_red_show_sta = <STA num>\nvow_set_red_tar_delay = <tarDelay> us\n======== WATF ===========\nvow_watf_en = <0/1> 0:disable, 1:enable\nvow_watf_q = <level>-<quantum> unit 256us\nvow_watf_add_entry = <level>-<Addr>\nvow_watf_del_entry = <Addr>\n"
             + iVar11 + 5);
    local_1c[3] = param_3;
    *(undefined2 *)(local_1c + 2) = uVar2;
    cVar8 = "======== Badnode detector =============\nvow_bn_en = <0/1> 0:dieable, 1:enable\nvow_bn_mon_period = <period> ms\nvow_bn_fallback_th = <count>\nvow_bn_per_th = <TX PER>\n======== Airtime counter test =============\nvow_counter_test = <0/1> 0:dieable, 1:enable\nvow_counter_test_period = <period> ms\nvow_counter_test_band = <band>\nvow_counter_test_avgcnt = <average num> sec\nvow_counter_test_target = <wlanidx>\n======== DVT =============\nvow_dvt_en = <0/1> 0:dieable, 1:enable\nvow_monitor_sta = <STA num>\nvow_show_sta = <STA num>\nvow_monitor_bss = <BSS num>\nvow_monitor_mbss = <MBSS num>\nvow_show_mbss = <MBSS num>\nvow_avg_num = <average num> sec\n======== RED ===========\nvow_set_red_en = <0/1> 0:disable, 1:enable\nvow_set_red_show_sta = <STA num>\nvow_set_red_tar_delay = <tarDelay> us\n======== WATF ===========\nvow_watf_en = <0/1> 0:disable, 1:enable\nvow_watf_q = <level>-<quantum> unit 256us\nvow_watf_add_entry = <level>-<Addr>\nvow_watf_del_entry = <Addr>\n"
            [param_1 + iVar13 + 0xfa];
    *(undefined1 *)((int)local_1c + 0x11) = 0;
    *(char *)(local_1c + 4) = cVar8;
    uVar2 = *(undefined2 *)
             (
             "======== Badnode detector =============\nvow_bn_en = <0/1> 0:dieable, 1:enable\nvow_bn_mon_period = <period> ms\nvow_bn_fallback_th = <count>\nvow_bn_per_th = <TX PER>\n======== Airtime counter test =============\nvow_counter_test = <0/1> 0:dieable, 1:enable\nvow_counter_test_period = <period> ms\nvow_counter_test_band = <band>\nvow_counter_test_avgcnt = <average num> sec\nvow_counter_test_target = <wlanidx>\n======== DVT =============\nvow_dvt_en = <0/1> 0:dieable, 1:enable\nvow_monitor_sta = <STA num>\nvow_show_sta = <STA num>\nvow_monitor_bss = <BSS num>\nvow_monitor_mbss = <MBSS num>\nvow_show_mbss = <MBSS num>\nvow_avg_num = <average num> sec\n======== RED ===========\nvow_set_red_en = <0/1> 0:disable, 1:enable\nvow_set_red_show_sta = <STA num>\nvow_set_red_tar_delay = <tarDelay> us\n======== WATF ===========\nvow_watf_en = <0/1> 0:disable, 1:enable\nvow_watf_q = <level>-<quantum> unit 256us\nvow_watf_add_entry = <level>-<Addr>\nvow_watf_del_entry = <Addr>\n"
             + param_1 + iVar13 + 0xf8);
    uVar12 = wlan_config_get_ht_bw(pcVar15);
    uVar7 = GetCuntryMaxTxPwr(param_1,uVar2,pcVar15,uVar12);
    *(undefined1 *)(piVar5 + 0x10e) = uVar7;
    iVar11 = HcGetBandByWdev(pcVar15);
    piVar5 = local_1c;
    if (iVar11 == 0) {
      local_1c[0x10f] = 0;
    }
    else {
      local_1c[0x10f] = 1;
    }
    cVar8 = wlan_operate_get_tx_stream(pcVar15);
    piVar6 = local_1c;
    *(byte *)(piVar5 + 0x110) = *(byte *)(piVar5 + 0x110) & 0x3f | (cVar8 + -1) * '@';
    cVar8 = wlan_operate_get_rx_stream(pcVar15);
    *(byte *)(piVar6 + 0x110) = *(byte *)(piVar6 + 0x110) & 0xcf | (cVar8 - 1U & 3) << 4;
    iVar11 = wlan_config_get_ht_gi(pcVar15);
    if (iVar11 == 1) {
      *(byte *)(local_1c + 0x110) = *(byte *)(local_1c + 0x110) | 8;
      iVar11 = wlan_operate_get_ht_bw(pcVar15);
      if (iVar11 == 1) {
        *(byte *)(local_1c + 0x110) = *(byte *)(local_1c + 0x110) | 4;
      }
      iVar11 = wlan_operate_get_vht_bw(pcVar15);
      if (iVar11 == 1) {
        *(byte *)((int)local_1c + 0x446) = *(byte *)((int)local_1c + 0x446) | 2;
      }
    }
    piVar5 = local_1c;
    iVar11 = wlan_operate_get_ht_bw(pcVar15);
    piVar6 = local_1c;
    *(byte *)(piVar5 + 0x110) = *(byte *)(piVar5 + 0x110) & 0xfd | (iVar11 == 1) << 1;
    cVar8 = wlan_operate_get_tx_stream(pcVar15);
    piVar5 = local_1c;
    *(byte *)((int)piVar6 + 0x446) = *(byte *)((int)piVar6 + 0x446) & 0x1f | cVar8 << 5;
    bVar9 = wlan_operate_get_rx_stream(pcVar15);
    piVar6 = local_1c;
    *(byte *)((int)piVar5 + 0x446) = *(byte *)((int)piVar5 + 0x446) & 0xe3 | (bVar9 & 7) << 2;
    *(undefined1 *)((int)local_1c + 0x443) = 0xff;
    *(undefined1 *)(local_1c + 0x111) = 0xff;
    *(undefined1 *)((int)local_1c + 0x441) = 0xff;
    *(undefined1 *)((int)local_1c + 0x442) = 0xff;
    if (bVar10 < 3) {
      bVar9 = *(byte *)((int)local_1c + 0x446) >> 5;
      if (((bVar9 + 7 & 7) < 4) &&
         (uVar14 = ((uint)*(byte *)((int)local_1c + 0x446) << 0x1b) >> 0x1d, (uVar14 + 7 & 7) < 4))
      {
        uVar16 = bVar10 & 3;
        bVar10 = (byte)uVar16;
        *(byte *)((int)local_1c + 0x443) = bVar10 | 0xfc;
        if (uVar14 != 1) {
          bVar1 = (byte)(uVar16 << 2);
          *(byte *)((int)local_1c + 0x443) = bVar10 | 0xf0 | bVar1;
          if (2 < uVar14) {
            bVar3 = (byte)(uVar16 << 4);
            *(byte *)((int)local_1c + 0x443) = bVar10 | 0xc0 | bVar1 | bVar3;
            if (uVar14 == 4) {
              *(byte *)((int)local_1c + 0x443) = bVar10 | bVar1 | bVar3 | (byte)(uVar16 << 6);
            }
          }
        }
        bVar1 = *(byte *)((int)local_1c + 0x441);
        *(byte *)((int)local_1c + 0x441) = bVar1 & 0xfc | bVar10;
        if (bVar9 != 1) {
          bVar3 = (byte)(uVar16 << 2);
          *(byte *)((int)local_1c + 0x441) = bVar1 & 0xf0 | bVar10 | bVar3;
          if (2 < bVar9) {
            bVar4 = (byte)(uVar16 << 4);
            *(byte *)((int)local_1c + 0x441) = bVar1 & 0xc0 | bVar10 | bVar3 | bVar4;
            if (bVar9 == 4) {
              *(byte *)((int)local_1c + 0x441) = bVar10 | bVar3 | bVar4 | (byte)(uVar16 << 6);
            }
          }
        }
      }
    }
    cVar8 = wlan_operate_get_tx_stream(pcVar15);
    piVar5 = local_1c;
    *(byte *)((int)piVar6 + 0x446) = *(byte *)((int)piVar6 + 0x446) & 0x1f | (cVar8 + -1) * ' ';
    cVar8 = wlan_operate_get_rx_stream(pcVar15);
    piVar6 = local_1c;
    *(byte *)((int)piVar5 + 0x446) = *(byte *)((int)piVar5 + 0x446) & 0xe3 | (cVar8 - 1U & 7) << 2;
    cVar8 = wlan_operate_get_tx_stream(pcVar15);
    piVar5 = local_1c;
    *(byte *)((int)piVar6 + 0x459) = *(byte *)((int)piVar6 + 0x459) & 0x1f | (cVar8 + -1) * ' ';
    cVar8 = wlan_operate_get_rx_stream(pcVar15);
    piVar6 = local_1c;
    *(byte *)((int)piVar5 + 0x459) = *(byte *)((int)piVar5 + 0x459) & 0xe3 | (cVar8 - 1U & 7) << 2;
    bVar10 = wlan_config_get_mu_dl_ofdma(pcVar15);
    piVar5 = local_1c;
    *(byte *)(piVar6 + 0x116) = *(byte *)(piVar6 + 0x116) & 0xfd | (bVar10 & 1) << 1;
    bVar10 = wlan_config_get_mu_ul_ofdma(pcVar15);
    piVar6 = local_1c;
    *(byte *)(piVar5 + 0x116) = *(byte *)(piVar5 + 0x116) & 0xfb | (bVar10 & 1) << 2;
    bVar10 = wlan_config_get_mu_ul_mimo(pcVar15);
    *(byte *)(piVar6 + 0x116) = *(byte *)(piVar6 + 0x116) & 0xdf | (bVar10 & 1) << 5;
    Kernel_ASEND("multiapd.map.slave",0xa2bf,local_1c,0x45c,0,0);
    os_free_mem(local_1c);
    uVar12 = 1;
  }
  return uVar12;
}

