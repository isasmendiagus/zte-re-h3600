// module: mt7915.ko
// function: Get_BndStrgTable @ 0x9b79c
// size: 268 bytes
//

undefined * Get_BndStrgTable(int param_1,int param_2,undefined4 param_3,undefined4 param_4)

{
  int iVar1;
  char cVar2;
  
  iVar1 = hc_get_chip_bcn_max_num(*(undefined4 *)(param_1 + 0xa797a0));
  if ((param_2 < 0x20 && param_2 < iVar1) &&
     ("======== Badnode detector =============\nvow_bn_en = <0/1> 0:dieable, 1:enable\nvow_bn_mon_period = <period> ms\nvow_bn_fallback_th = <count>\nvow_bn_per_th = <TX PER>\n======== Airtime counter test =============\nvow_counter_test = <0/1> 0:dieable, 1:enable\nvow_counter_test_period = <period> ms\nvow_counter_test_band = <band>\nvow_counter_test_avgcnt = <average num> sec\nvow_counter_test_target = <wlanidx>\n======== DVT =============\nvow_dvt_en = <0/1> 0:dieable, 1:enable\nvow_monitor_sta = <STA num>\nvow_show_sta = <STA num>\nvow_monitor_bss = <BSS num>\nvow_monitor_mbss = <MBSS num>\nvow_show_mbss = <MBSS num>\nvow_avg_num = <average num> sec\n======== RED ===========\nvow_set_red_en = <0/1> 0:disable, 1:enable\nvow_set_red_show_sta = <STA num>\nvow_set_red_tar_delay = <tarDelay> us\n======== WATF ===========\nvow_watf_en = <0/1> 0:disable, 1:enable\nvow_watf_q = <level>-<quantum> unit 256us\nvow_watf_add_entry = <level>-<Addr>\nvow_watf_del_entry = <Addr>\n"
      + param_1 + param_2 * 0x5834 + 0xe0 != (char *)0x0)) {
    if ((*(ushort *)
          (
          "======== Badnode detector =============\nvow_bn_en = <0/1> 0:dieable, 1:enable\nvow_bn_mon_period = <period> ms\nvow_bn_fallback_th = <count>\nvow_bn_per_th = <TX PER>\n======== Airtime counter test =============\nvow_counter_test = <0/1> 0:dieable, 1:enable\nvow_counter_test_period = <period> ms\nvow_counter_test_band = <band>\nvow_counter_test_avgcnt = <average num> sec\nvow_counter_test_target = <wlanidx>\n======== DVT =============\nvow_dvt_en = <0/1> 0:dieable, 1:enable\nvow_monitor_sta = <STA num>\nvow_show_sta = <STA num>\nvow_monitor_bss = <BSS num>\nvow_monitor_mbss = <MBSS num>\nvow_show_mbss = <MBSS num>\nvow_avg_num = <average num> sec\n======== RED ===========\nvow_set_red_en = <0/1> 0:disable, 1:enable\nvow_set_red_show_sta = <STA num>\nvow_set_red_tar_delay = <tarDelay> us\n======== WATF ===========\nvow_watf_en = <0/1> 0:disable, 1:enable\nvow_watf_q = <level>-<quantum> unit 256us\nvow_watf_add_entry = <level>-<Addr>\nvow_watf_del_entry = <Addr>\n"
          + param_1 + param_2 * 0x5834 + 0xf8) & 0xb1) == 0) {
      cVar2 = '\x02';
    }
    else {
      cVar2 = '\x01';
    }
    if (((&DAT_0036b928)[param_1] != '\0') && ((&DAT_0036c992)[param_1] == cVar2)) {
      return &DAT_0036b924 + param_1;
    }
    if ((&DAT_0036c9bc)[param_1] == '\0') {
      return (undefined *)0x0;
    }
    if ((&DAT_0036da26)[param_1] == cVar2) {
      return &DAT_0036c9b8 + param_1;
    }
  }
  else if (-1 < DebugLevel) {
    printk(&_LC27,"Get_BndStrgTable",0x36,param_2,param_4);
    return (undefined *)0x0;
  }
  return (undefined *)0x0;
}

