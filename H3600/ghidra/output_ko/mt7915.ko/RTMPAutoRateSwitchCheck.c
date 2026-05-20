// module: mt7915.ko
// function: RTMPAutoRateSwitchCheck @ 0x130b14
// size: 196 bytes
//

undefined4 RTMPAutoRateSwitchCheck(int param_1)

{
  char cVar1;
  undefined4 uVar2;
  uint uVar3;
  char *pcVar4;
  
  if (*(char *)(param_1 + 0x286285) != '\x01') {
    if (*(char *)(param_1 + 0x286285) == '\0') {
      uVar2 = 0;
      if ((&DAT_0036e408)[param_1] != '\0') {
        uVar2 = 1;
      }
    }
    else {
      uVar2 = 0;
    }
    return uVar2;
  }
  uVar2 = 1;
  if ((byte)"======== Badnode detector =============\nvow_bn_en = <0/1> 0:dieable, 1:enable\nvow_bn_mon_period = <period> ms\nvow_bn_fallback_th = <count>\nvow_bn_per_th = <TX PER>\n======== Airtime counter test =============\nvow_counter_test = <0/1> 0:dieable, 1:enable\nvow_counter_test_period = <period> ms\nvow_counter_test_band = <band>\nvow_counter_test_avgcnt = <average num> sec\nvow_counter_test_target = <wlanidx>\n======== DVT =============\nvow_dvt_en = <0/1> 0:dieable, 1:enable\nvow_monitor_sta = <STA num>\nvow_show_sta = <STA num>\nvow_monitor_bss = <BSS num>\nvow_monitor_mbss = <MBSS num>\nvow_show_mbss = <MBSS num>\nvow_avg_num = <average num> sec\n======== RED ===========\nvow_set_red_en = <0/1> 0:disable, 1:enable\nvow_set_red_show_sta = <STA num>\nvow_set_red_tar_delay = <tarDelay> us\n======== WATF ===========\nvow_watf_en = <0/1> 0:disable, 1:enable\nvow_watf_q = <level>-<quantum> unit 256us\nvow_watf_add_entry = <level>-<Addr>\nvow_watf_del_entry = <Addr>\n"
            [param_1 + 0xda] == 0) {
LAB_00130ba8:
    if (((&DAT_0036e408)[param_1] == '\0') && (uVar2 = 0, (&DAT_00581bb8)[param_1] != '\0')) {
      uVar2 = 1;
    }
  }
  else if ("%s: period = %d\n"[param_1] == '\0') {
    uVar3 = 0;
    pcVar4 = "%s - WSC_SET_CONF_MODE, value = %d\n" + param_1 + 0x14;
    do {
      uVar3 = uVar3 + 1;
      if (uVar3 == (byte)"======== Badnode detector =============\nvow_bn_en = <0/1> 0:dieable, 1:enable\nvow_bn_mon_period = <period> ms\nvow_bn_fallback_th = <count>\nvow_bn_per_th = <TX PER>\n======== Airtime counter test =============\nvow_counter_test = <0/1> 0:dieable, 1:enable\nvow_counter_test_period = <period> ms\nvow_counter_test_band = <band>\nvow_counter_test_avgcnt = <average num> sec\nvow_counter_test_target = <wlanidx>\n======== DVT =============\nvow_dvt_en = <0/1> 0:dieable, 1:enable\nvow_monitor_sta = <STA num>\nvow_show_sta = <STA num>\nvow_monitor_bss = <BSS num>\nvow_monitor_mbss = <MBSS num>\nvow_show_mbss = <MBSS num>\nvow_avg_num = <average num> sec\n======== RED ===========\nvow_set_red_en = <0/1> 0:disable, 1:enable\nvow_set_red_show_sta = <STA num>\nvow_set_red_tar_delay = <tarDelay> us\n======== WATF ===========\nvow_watf_en = <0/1> 0:disable, 1:enable\nvow_watf_q = <level>-<quantum> unit 256us\nvow_watf_add_entry = <level>-<Addr>\nvow_watf_del_entry = <Addr>\n"
                         [param_1 + 0xda]) goto LAB_00130ba8;
      cVar1 = *pcVar4;
      pcVar4 = pcVar4 + 0x5834;
    } while (cVar1 == '\0');
  }
  return uVar2;
}

