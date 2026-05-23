// module: mt7915.ko
// function: MWDSDisable @ 0x9eb0c
// size: 276 bytes
//

undefined4 MWDSDisable(int param_1,uint param_2,int param_3,int param_4)

{
  uint uVar1;
  int iVar2;
  int iVar3;
  
  if (param_3 == 0) {
    if (((param_2 < 2) && (&DAT_0036db58 + param_1 + param_2 * 0x2137b0 != (undefined *)0x0)) &&
       (param_1 = param_1 + param_2 * 0x2137b0,
       s__m__d_t_id__x__d__d__m_id__d__ts_00371ab0[param_1 + 1] != '\0')) {
      s__m__d_t_id__x__d__d__m_id__d__ts_00371ab0[param_1 + 1] = '\0';
      a4_interface_deinit();
    }
  }
  else {
    iVar3 = param_4;
    uVar1 = hc_get_chip_bcn_max_num(*(undefined4 *)(param_1 + 0xa797a0));
    if (param_2 < 0x20 && param_2 < uVar1) {
      if (("======== Badnode detector =============\nvow_bn_en = <0/1> 0:dieable, 1:enable\nvow_bn_mon_period = <period> ms\nvow_bn_fallback_th = <count>\nvow_bn_per_th = <TX PER>\n======== Airtime counter test =============\nvow_counter_test = <0/1> 0:dieable, 1:enable\nvow_counter_test_period = <period> ms\nvow_counter_test_band = <band>\nvow_counter_test_avgcnt = <average num> sec\nvow_counter_test_target = <wlanidx>\n======== DVT =============\nvow_dvt_en = <0/1> 0:dieable, 1:enable\nvow_monitor_sta = <STA num>\nvow_show_sta = <STA num>\nvow_monitor_bss = <BSS num>\nvow_monitor_mbss = <MBSS num>\nvow_show_mbss = <MBSS num>\nvow_avg_num = <average num> sec\n======== RED ===========\nvow_set_red_en = <0/1> 0:disable, 1:enable\nvow_set_red_show_sta = <STA num>\nvow_set_red_tar_delay = <tarDelay> us\n======== WATF ===========\nvow_watf_en = <0/1> 0:disable, 1:enable\nvow_watf_q = <level>-<quantum> unit 256us\nvow_watf_add_entry = <level>-<Addr>\nvow_watf_del_entry = <Addr>\n"
           + param_1 + param_2 * 0x5834 + 0xe0 != (char *)0x0) &&
         (iVar2 = param_1 + param_2 * 0x5834,
         "!!! Link UP, Port Not Secured! ignore this set::OID_802_11_BSSID_LIST_SCAN\n"
         [iVar2 + 0x49] != '\0')) {
        "!!! Link UP, Port Not Secured! ignore this set::OID_802_11_BSSID_LIST_SCAN\n"[iVar2 + 0x49]
             = '\0';
        a4_interface_deinit(param_1,param_2,1,1,iVar3);
        if (param_4 == 0) {
          UpdateBeaconHandler(param_1,"======== Badnode detector =============\nvow_bn_en = <0/1> 0:dieable, 1:enable\nvow_bn_mon_period = <period> ms\nvow_bn_fallback_th = <count>\nvow_bn_per_th = <TX PER>\n======== Airtime counter test =============\nvow_counter_test = <0/1> 0:dieable, 1:enable\nvow_counter_test_period = <period> ms\nvow_counter_test_band = <band>\nvow_counter_test_avgcnt = <average num> sec\nvow_counter_test_target = <wlanidx>\n======== DVT =============\nvow_dvt_en = <0/1> 0:dieable, 1:enable\nvow_monitor_sta = <STA num>\nvow_show_sta = <STA num>\nvow_monitor_bss = <BSS num>\nvow_monitor_mbss = <MBSS num>\nvow_show_mbss = <MBSS num>\nvow_avg_num = <average num> sec\n======== RED ===========\nvow_set_red_en = <0/1> 0:disable, 1:enable\nvow_set_red_show_sta = <STA num>\nvow_set_red_tar_delay = <tarDelay> us\n======== WATF ===========\nvow_watf_en = <0/1> 0:disable, 1:enable\nvow_watf_q = <level>-<quantum> unit 256us\nvow_watf_add_entry = <level>-<Addr>\nvow_watf_del_entry = <Addr>\n"
                                      + param_1 + param_2 * 0x5834 + 0xe0,2);
        }
      }
    }
  }
  return 1;
}

