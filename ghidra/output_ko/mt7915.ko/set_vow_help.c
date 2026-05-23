// module: mt7915.ko
// function: set_vow_help @ 0x4630c
// size: 120 bytes
//

undefined4 set_vow_help(void)

{
  if (-1 < DebugLevel) {
    printk(
          "======== Group table =========\nvow_min_rate_token = <group>-<token>\nvow_max_rate_token = <group>-<token>\nvow_min_airtime_token = <group>-<token>\nvow_max_airtime_token = <group>-<token>\nvow_min_rate_bucket = <group>-<byte> 1K\nvow_max_rate_bucket = <group>-<byte> 1K\nvow_min_airtime_bucket = <group>-<time> 1.024\nvow_max_airtime_bucket = <group>-<time> 1.024\nvow_max_wait_time = <group>-<time> 1.024\nvow_max_backlog_size = <group>-<byte> 1K\n======== Control =============\nvow_bw_enable = <0/1> 0:disable, 1:enable\nvow_refill_en = <0/1> 0:disable, 1:enable\nvow_airtime_fairness_en = <0/1> 0:disable, 1:enable\nvow_txop_switch_bss_en = <0/1> 0:disable, 1:enable\nvow_dbdc_search_rule = <band>-<0/1> 0:WMM AC, 1:WMM set\nvow_refill_period = <n> 2^n\nvow_bss_enable = <group>-<0/1> 0:disable, 1:enable\nvow_spl_sta_num = <sta num> in txop\nvow_airtime_control_en = <group>-<0/1> 0:disable, 1:enable\nvow_bw_control_en = <group>-<0/1> 0:disable, 1:enable\n"
          );
    if (-1 < DebugLevel) {
      printk(
            "======== Group others =============\nvow_bss_dwrr_quantum = <group>-<time> 256us\nvow_group_dwrr_max_wait_time = <time> 256us\nvow_group2band_map = <group>-<band>\n======== Station table =============\nvow_sta_dwrr_quantum = <Qid>-<val> 256us\nvow_sta_dwrr_quantum_id = <wlanidx>-<WMMA AC>-<Qid>\nvow_sta_ac_priority = <wlanidx>-<0/1/2> 0:disable, 1:BE, 2:BK\nvow_sta_pause = <wlanidx>-<0/1> 0: normal, 1: pause\nvow_sta_psm = <wlanidx>-<0/1> 0: normal, 1: power save\nvow_sta_group = <wlanidx>-<group>\nvow_dwrr_max_wait_time = <time> 256us\n======== User Config =============\nvow_min_rate = <group>-<Mbps>\nvow_max_rate = <group>-<Mbps>\nvow_min_ratio = <group>-<%%>\nvow_max_ratio = <group>-<%%>\n"
            );
      if (-1 < DebugLevel) {
        printk(
              "======== Rx Config =============\nvow_rx_counter_clr = <n>\nvow_rx_airtime_en = <0/1> 0:dieable, 1:enable\nvow_rx_ed_offset = <val> 1.024(5b)\nvow_rx_obss_backoff = <val> 1.024(16b)\nvow_rx_wmm_backoff = <WMM set>-<WMM AC>-<val>\nvow_om_wmm_backoff = <WMM AC>-<val>\nvow_repeater_wmm_backoff = <WMM AC>-<val>\nvow_rx_non_qos_backoff = <val>\nvow_rx_bss_wmmset = <MBSS idx>-<0/1/2/3>\nvow_rx_om_wmm_sel = <OM idx>-<val> 0:RX WMM(1to1), 1:OM wmm\n======== Airtime estimator =============\nvow_at_est_en = <0/1> 0:dieable, 1:enable\nvow_at_mon_period = <period> ms\n"
              );
        if (-1 < DebugLevel) {
          printk(
                "======== Badnode detector =============\nvow_bn_en = <0/1> 0:dieable, 1:enable\nvow_bn_mon_period = <period> ms\nvow_bn_fallback_th = <count>\nvow_bn_per_th = <TX PER>\n======== Airtime counter test =============\nvow_counter_test = <0/1> 0:dieable, 1:enable\nvow_counter_test_period = <period> ms\nvow_counter_test_band = <band>\nvow_counter_test_avgcnt = <average num> sec\nvow_counter_test_target = <wlanidx>\n======== DVT =============\nvow_dvt_en = <0/1> 0:dieable, 1:enable\nvow_monitor_sta = <STA num>\nvow_show_sta = <STA num>\nvow_monitor_bss = <BSS num>\nvow_monitor_mbss = <MBSS num>\nvow_show_mbss = <MBSS num>\nvow_avg_num = <average num> sec\n======== RED ===========\nvow_set_red_en = <0/1> 0:disable, 1:enable\nvow_set_red_show_sta = <STA num>\nvow_set_red_tar_delay = <tarDelay> us\n======== WATF ===========\nvow_watf_en = <0/1> 0:disable, 1:enable\nvow_watf_q = <level>-<quantum> unit 256us\nvow_watf_add_entry = <level>-<Addr>\nvow_watf_del_entry = <Addr>\n"
                );
        }
      }
    }
  }
  return 1;
}

