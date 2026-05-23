// module: mt7915.ko
// function: sae_pwd_id_deinit @ 0x115e78
// size: 140 bytes
//

void sae_pwd_id_deinit(int param_1)

{
  byte *pbVar1;
  int iVar2;
  
  if ((byte)"======== Badnode detector =============\nvow_bn_en = <0/1> 0:dieable, 1:enable\nvow_bn_mon_period = <period> ms\nvow_bn_fallback_th = <count>\nvow_bn_per_th = <TX PER>\n======== Airtime counter test =============\nvow_counter_test = <0/1> 0:dieable, 1:enable\nvow_counter_test_period = <period> ms\nvow_counter_test_band = <band>\nvow_counter_test_avgcnt = <average num> sec\nvow_counter_test_target = <wlanidx>\n======== DVT =============\nvow_dvt_en = <0/1> 0:dieable, 1:enable\nvow_monitor_sta = <STA num>\nvow_show_sta = <STA num>\nvow_monitor_bss = <BSS num>\nvow_monitor_mbss = <MBSS num>\nvow_show_mbss = <MBSS num>\nvow_avg_num = <average num> sec\n======== RED ===========\nvow_set_red_en = <0/1> 0:disable, 1:enable\nvow_set_red_show_sta = <STA num>\nvow_set_red_tar_delay = <tarDelay> us\n======== WATF ===========\nvow_watf_en = <0/1> 0:disable, 1:enable\nvow_watf_q = <level>-<quantum> unit 256us\nvow_watf_add_entry = <level>-<Addr>\nvow_watf_del_entry = <Addr>\n"
            [param_1 + 0xda] == 0) {
    return;
  }
  pbVar1 = (byte *)(param_1 + 0x3678c7);
  do {
    pbVar1 = pbVar1 + 1;
    iVar2 = param_1 + (uint)*pbVar1 * 0x5834;
    if ("vow_rx_time (Non-wifi/OBSS)\nvow_sta_conf = <wlanidx>\nvow_sta_conf\nvow_bss_conf = <group>\nvow_all_bss_conf\nvow_dump_sta (raw)\nvow_dump_bss_bitmap (raw)\nvow_dump_bss (raw)\nvow_dump_vow (raw)\nvow_show_sta_dtoken = <wlanidx> DWRR\nvow_show_bss_dtoken = <group> DWRR\nvow_show_bss_atoken = <group> airtime\nvow_show_bss_ltoken = <group> length\n"
        [iVar2 + 0x10d] != '\0') {
      do {
      } while ("vow_rx_time (Non-wifi/OBSS)\nvow_sta_conf = <wlanidx>\nvow_sta_conf\nvow_bss_conf = <group>\nvow_all_bss_conf\nvow_dump_sta (raw)\nvow_dump_bss_bitmap (raw)\nvow_dump_bss (raw)\nvow_dump_vow (raw)\nvow_show_sta_dtoken = <wlanidx> DWRR\nvow_show_bss_dtoken = <group> DWRR\nvow_show_bss_atoken = <group> airtime\nvow_show_bss_ltoken = <group> length\n"
               + iVar2 + 0x110 ==
               *(char **)(
                         "vow_rx_time (Non-wifi/OBSS)\nvow_sta_conf = <wlanidx>\nvow_sta_conf\nvow_bss_conf = <group>\nvow_all_bss_conf\nvow_dump_sta (raw)\nvow_dump_bss_bitmap (raw)\nvow_dump_bss (raw)\nvow_dump_vow (raw)\nvow_show_sta_dtoken = <wlanidx> DWRR\nvow_show_bss_dtoken = <group> DWRR\nvow_show_bss_atoken = <group> airtime\nvow_show_bss_ltoken = <group> length\n"
                         + iVar2 + 0x110));
    }
  } while (pbVar1 != (byte *)(param_1 +
                             (byte)"======== Badnode detector =============\nvow_bn_en = <0/1> 0:dieable, 1:enable\nvow_bn_mon_period = <period> ms\nvow_bn_fallback_th = <count>\nvow_bn_per_th = <TX PER>\n======== Airtime counter test =============\nvow_counter_test = <0/1> 0:dieable, 1:enable\nvow_counter_test_period = <period> ms\nvow_counter_test_band = <band>\nvow_counter_test_avgcnt = <average num> sec\nvow_counter_test_target = <wlanidx>\n======== DVT =============\nvow_dvt_en = <0/1> 0:dieable, 1:enable\nvow_monitor_sta = <STA num>\nvow_show_sta = <STA num>\nvow_monitor_bss = <BSS num>\nvow_monitor_mbss = <MBSS num>\nvow_show_mbss = <MBSS num>\nvow_avg_num = <average num> sec\n======== RED ===========\nvow_set_red_en = <0/1> 0:disable, 1:enable\nvow_set_red_show_sta = <STA num>\nvow_set_red_tar_delay = <tarDelay> us\n======== WATF ===========\nvow_watf_en = <0/1> 0:disable, 1:enable\nvow_watf_q = <level>-<quantum> unit 256us\nvow_watf_add_entry = <level>-<Addr>\nvow_watf_del_entry = <Addr>\n"
                                   [param_1 + 0xda] + 0x3678c7));
  return;
}

