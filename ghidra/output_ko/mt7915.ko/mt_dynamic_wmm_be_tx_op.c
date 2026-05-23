// module: mt7915.ko
// function: mt_dynamic_wmm_be_tx_op @ 0xc7f10
// size: 1188 bytes
//

void mt_dynamic_wmm_be_tx_op(int param_1,uint param_2)

{
  int iVar1;
  uint uVar2;
  char *pcVar3;
  undefined *puVar4;
  undefined *puVar5;
  int *piVar6;
  char *pcVar7;
  char *pcVar8;
  
  iVar1 = hc_get_chip_cap(*(undefined4 *)(param_1 + 0xa797a0));
  if ((param_2 < *(uint *)(param_1 + 0xa77c2c)) || (param_2 < *(uint *)(param_1 + 0xa77c30))) {
    if ((*(uint *)(param_1 + 0xa39f84) & 0x200000) != 0) {
      uVar2 = hc_get_asic_cap(*(undefined4 *)(param_1 + 0xa797a0));
      if (((uVar2 & 0x400) != 0) && (*(char *)(iVar1 + 0x21) != '\0')) {
        MtCmdCr4Set(param_1,0x21,1,0);
      }
      puVar4 = &DAT_0036db58 + param_1;
      puVar5 = puVar4;
      do {
        if ((puVar5 != (undefined *)0x0) && (puVar5[0x213336] == '\x01')) {
          enable_tx_burst(param_1,puVar5,2,9,txop0);
        }
        puVar5 = puVar5 + 0x2137b0;
      } while (puVar5 != (undefined *)(param_1 + 0x794ab8));
      if ("======== Badnode detector =============\nvow_bn_en = <0/1> 0:dieable, 1:enable\nvow_bn_mon_period = <period> ms\nvow_bn_fallback_th = <count>\nvow_bn_per_th = <TX PER>\n======== Airtime counter test =============\nvow_counter_test = <0/1> 0:dieable, 1:enable\nvow_counter_test_period = <period> ms\nvow_counter_test_band = <band>\nvow_counter_test_avgcnt = <average num> sec\nvow_counter_test_target = <wlanidx>\n======== DVT =============\nvow_dvt_en = <0/1> 0:dieable, 1:enable\nvow_monitor_sta = <STA num>\nvow_show_sta = <STA num>\nvow_monitor_bss = <BSS num>\nvow_monitor_mbss = <MBSS num>\nvow_show_mbss = <MBSS num>\nvow_avg_num = <average num> sec\n======== RED ===========\nvow_set_red_en = <0/1> 0:disable, 1:enable\nvow_set_red_show_sta = <STA num>\nvow_set_red_tar_delay = <tarDelay> us\n======== WATF ===========\nvow_watf_en = <0/1> 0:disable, 1:enable\nvow_watf_q = <level>-<quantum> unit 256us\nvow_watf_add_entry = <level>-<Addr>\nvow_watf_del_entry = <Addr>\n"
          + param_1 + 0xe0 != (char *)0x0) {
        enable_tx_burst(param_1,"======== Badnode detector =============\nvow_bn_en = <0/1> 0:dieable, 1:enable\nvow_bn_mon_period = <period> ms\nvow_bn_fallback_th = <count>\nvow_bn_per_th = <TX PER>\n======== Airtime counter test =============\nvow_counter_test = <0/1> 0:dieable, 1:enable\nvow_counter_test_period = <period> ms\nvow_counter_test_band = <band>\nvow_counter_test_avgcnt = <average num> sec\nvow_counter_test_target = <wlanidx>\n======== DVT =============\nvow_dvt_en = <0/1> 0:dieable, 1:enable\nvow_monitor_sta = <STA num>\nvow_show_sta = <STA num>\nvow_monitor_bss = <BSS num>\nvow_monitor_mbss = <MBSS num>\nvow_show_mbss = <MBSS num>\nvow_avg_num = <average num> sec\n======== RED ===========\nvow_set_red_en = <0/1> 0:disable, 1:enable\nvow_set_red_show_sta = <STA num>\nvow_set_red_tar_delay = <tarDelay> us\n======== WATF ===========\nvow_watf_en = <0/1> 0:disable, 1:enable\nvow_watf_q = <level>-<quantum> unit 256us\nvow_watf_add_entry = <level>-<Addr>\nvow_watf_del_entry = <Addr>\n"
                                + param_1 + 0xe0,2,9,txop0);
      }
      uVar2 = hc_get_asic_cap(*(undefined4 *)(param_1 + 0xa797a0));
      if ((uVar2 & 0x400) != 0) {
        HW_SET_PBC_CTRL(param_1,0,0,1);
      }
      if (*(char *)(param_1 + 0x794ab8) != '\0') {
        iVar1 = 0;
        do {
          iVar1 = iVar1 + 1;
          if ((puVar4 != (undefined *)0x0) && (puVar4[0xaa8] != '\0')) {
            enable_tx_burst(param_1,puVar4,2,9,txop0);
          }
          puVar4 = puVar4 + 0x2137b0;
        } while (iVar1 < (int)(uint)*(byte *)(param_1 + 0x794ab8));
      }
      *(uint *)(param_1 + 0xa39f84) = *(uint *)(param_1 + 0xa39f84) & 0xffdfffff;
    }
  }
  else if ((*(uint *)(param_1 + 0xa39f84) & 0x200000) == 0) {
    uVar2 = hc_get_asic_cap(*(undefined4 *)(param_1 + 0xa797a0));
    if (((uVar2 & 0x400) != 0) && (*(char *)(iVar1 + 0x21) != '\0')) {
      MtCmdCr4Set(param_1,0x21,0,0);
    }
    puVar4 = &DAT_0036db58 + param_1;
    puVar5 = puVar4;
    do {
      if ((puVar5 != (undefined *)0x0) && (puVar5[0x213336] == '\x01')) {
        disable_tx_burst(param_1,puVar5,2,9,txop0);
      }
      puVar5 = puVar5 + 0x2137b0;
    } while (puVar5 != (undefined *)(param_1 + 0x794ab8));
    if ("======== Badnode detector =============\nvow_bn_en = <0/1> 0:dieable, 1:enable\nvow_bn_mon_period = <period> ms\nvow_bn_fallback_th = <count>\nvow_bn_per_th = <TX PER>\n======== Airtime counter test =============\nvow_counter_test = <0/1> 0:dieable, 1:enable\nvow_counter_test_period = <period> ms\nvow_counter_test_band = <band>\nvow_counter_test_avgcnt = <average num> sec\nvow_counter_test_target = <wlanidx>\n======== DVT =============\nvow_dvt_en = <0/1> 0:dieable, 1:enable\nvow_monitor_sta = <STA num>\nvow_show_sta = <STA num>\nvow_monitor_bss = <BSS num>\nvow_monitor_mbss = <MBSS num>\nvow_show_mbss = <MBSS num>\nvow_avg_num = <average num> sec\n======== RED ===========\nvow_set_red_en = <0/1> 0:disable, 1:enable\nvow_set_red_show_sta = <STA num>\nvow_set_red_tar_delay = <tarDelay> us\n======== WATF ===========\nvow_watf_en = <0/1> 0:disable, 1:enable\nvow_watf_q = <level>-<quantum> unit 256us\nvow_watf_add_entry = <level>-<Addr>\nvow_watf_del_entry = <Addr>\n"
        + param_1 + 0xe0 != (char *)0x0) {
      disable_tx_burst(param_1,"======== Badnode detector =============\nvow_bn_en = <0/1> 0:dieable, 1:enable\nvow_bn_mon_period = <period> ms\nvow_bn_fallback_th = <count>\nvow_bn_per_th = <TX PER>\n======== Airtime counter test =============\nvow_counter_test = <0/1> 0:dieable, 1:enable\nvow_counter_test_period = <period> ms\nvow_counter_test_band = <band>\nvow_counter_test_avgcnt = <average num> sec\nvow_counter_test_target = <wlanidx>\n======== DVT =============\nvow_dvt_en = <0/1> 0:dieable, 1:enable\nvow_monitor_sta = <STA num>\nvow_show_sta = <STA num>\nvow_monitor_bss = <BSS num>\nvow_monitor_mbss = <MBSS num>\nvow_show_mbss = <MBSS num>\nvow_avg_num = <average num> sec\n======== RED ===========\nvow_set_red_en = <0/1> 0:disable, 1:enable\nvow_set_red_show_sta = <STA num>\nvow_set_red_tar_delay = <tarDelay> us\n======== WATF ===========\nvow_watf_en = <0/1> 0:disable, 1:enable\nvow_watf_q = <level>-<quantum> unit 256us\nvow_watf_add_entry = <level>-<Addr>\nvow_watf_del_entry = <Addr>\n"
                               + param_1 + 0xe0,2,9,txop0);
    }
    uVar2 = hc_get_asic_cap(*(undefined4 *)(param_1 + 0xa797a0));
    if ((uVar2 & 0x400) != 0) {
      HW_SET_PBC_CTRL(param_1,0,0,0);
    }
    if (*(char *)(param_1 + 0x794ab8) != '\0') {
      iVar1 = 0;
      do {
        iVar1 = iVar1 + 1;
        if ((puVar4 != (undefined *)0x0) && (puVar4[0xaa8] != '\0')) {
          disable_tx_burst(param_1,puVar4,2,9,txop0);
        }
        puVar4 = puVar4 + 0x2137b0;
      } while (iVar1 < (int)(uint)*(byte *)(param_1 + 0x794ab8));
    }
    *(uint *)(param_1 + 0xa39f84) = *(uint *)(param_1 + 0xa39f84) | 0x200000;
  }
  pcVar3 = "======== Badnode detector =============\nvow_bn_en = <0/1> 0:dieable, 1:enable\nvow_bn_mon_period = <period> ms\nvow_bn_fallback_th = <count>\nvow_bn_per_th = <TX PER>\n======== Airtime counter test =============\nvow_counter_test = <0/1> 0:dieable, 1:enable\nvow_counter_test_period = <period> ms\nvow_counter_test_band = <band>\nvow_counter_test_avgcnt = <average num> sec\nvow_counter_test_target = <wlanidx>\n======== DVT =============\nvow_dvt_en = <0/1> 0:dieable, 1:enable\nvow_monitor_sta = <STA num>\nvow_show_sta = <STA num>\nvow_monitor_bss = <BSS num>\nvow_monitor_mbss = <MBSS num>\nvow_show_mbss = <MBSS num>\nvow_avg_num = <average num> sec\n======== RED ===========\nvow_set_red_en = <0/1> 0:disable, 1:enable\nvow_set_red_show_sta = <STA num>\nvow_set_red_tar_delay = <tarDelay> us\n======== WATF ===========\nvow_watf_en = <0/1> 0:disable, 1:enable\nvow_watf_q = <level>-<quantum> unit 256us\nvow_watf_add_entry = <level>-<Addr>\nvow_watf_del_entry = <Addr>\n"
           + param_1 + 0xe0;
  pcVar8 = (char *)(param_1 + 0xa7d164);
  piVar6 = (int *)("[RTMPSetInformation][BandIdx=%d] Ndis802_11OFDM24\n" + param_1 + 0x10);
  pcVar7 = &_LANCHOR2;
  *(undefined4 *)(param_1 + 0xa77c2c) = 0;
  *(undefined4 *)(param_1 + 0xa77c30) = 0;
  do {
    pcVar8 = pcVar8 + 1;
    if ((((*pcVar8 == '\0') || (*(short *)(param_1 + 0x285920) != 1)) ||
        ((uint)piVar6[-1] < 0x19001)) || ((uint)piVar6[-1] <= (uint)(*piVar6 * 0x10))) {
      if (*pcVar7 != '\0') {
        if (pcVar3 != (char *)0x0) {
          disable_tx_burst(param_1,pcVar3,2,9,0xffe);
        }
        *pcVar7 = '\0';
      }
    }
    else if ((*pcVar7 == '\0') && (*pcVar7 = '\x01', pcVar3 != (char *)0x0)) {
      enable_tx_burst(param_1,pcVar3,2,9,0xffe);
    }
    pcVar3 = pcVar3 + 0x1b904;
    piVar6 = piVar6 + 0x6e41;
    pcVar7 = pcVar7 + 1;
  } while (pcVar3 != "ZTE_Notify_Node_AD emEvent = %d idx=%d MAC[%02x:%02x:%02x:%02x:%02x:%02x]\n" +
                     param_1);
  return;
}

