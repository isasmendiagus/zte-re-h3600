// module: mt7915.ko
// function: rtmp_timer_RRM_QuietTimeout @ 0x21ead0
// size: 160 bytes
//

void rtmp_timer_RRM_QuietTimeout(char *param_1)

{
  char *pcVar1;
  uint uVar2;
  int iVar3;
  bool bVar4;
  
  iVar3 = *(int *)(param_1 + 0x24);
  if ((byte)"======== Badnode detector =============\nvow_bn_en = <0/1> 0:dieable, 1:enable\nvow_bn_mon_period = <period> ms\nvow_bn_fallback_th = <count>\nvow_bn_per_th = <TX PER>\n======== Airtime counter test =============\nvow_counter_test = <0/1> 0:dieable, 1:enable\nvow_counter_test_period = <period> ms\nvow_counter_test_band = <band>\nvow_counter_test_avgcnt = <average num> sec\nvow_counter_test_target = <wlanidx>\n======== DVT =============\nvow_dvt_en = <0/1> 0:dieable, 1:enable\nvow_monitor_sta = <STA num>\nvow_show_sta = <STA num>\nvow_monitor_bss = <BSS num>\nvow_monitor_mbss = <MBSS num>\nvow_show_mbss = <MBSS num>\nvow_avg_num = <average num> sec\n======== RED ===========\nvow_set_red_en = <0/1> 0:disable, 1:enable\nvow_set_red_show_sta = <STA num>\nvow_set_red_tar_delay = <tarDelay> us\n======== WATF ===========\nvow_watf_en = <0/1> 0:disable, 1:enable\nvow_watf_q = <level>-<quantum> unit 256us\nvow_watf_add_entry = <level>-<Addr>\nvow_watf_del_entry = <Addr>\n"
            [iVar3 + 0xda] != 0) {
    if (param_1 == "This MAC Address %02x:%02x:%02x:%02x:%02x:%02x is duplicate.\n" + iVar3 + 0x2c)
    {
      uVar2 = 0;
    }
    else {
      uVar2 = 0;
      pcVar1 = "Tx fail count                   = %ld, PER=%ld.%1ld%%\n" + iVar3 + 0x2c;
      do {
        uVar2 = uVar2 + 1;
        if (uVar2 == (byte)"======== Badnode detector =============\nvow_bn_en = <0/1> 0:dieable, 1:enable\nvow_bn_mon_period = <period> ms\nvow_bn_fallback_th = <count>\nvow_bn_per_th = <TX PER>\n======== Airtime counter test =============\nvow_counter_test = <0/1> 0:dieable, 1:enable\nvow_counter_test_period = <period> ms\nvow_counter_test_band = <band>\nvow_counter_test_avgcnt = <average num> sec\nvow_counter_test_target = <wlanidx>\n======== DVT =============\nvow_dvt_en = <0/1> 0:dieable, 1:enable\nvow_monitor_sta = <STA num>\nvow_show_sta = <STA num>\nvow_monitor_bss = <BSS num>\nvow_monitor_mbss = <MBSS num>\nvow_show_mbss = <MBSS num>\nvow_avg_num = <average num> sec\n======== RED ===========\nvow_set_red_en = <0/1> 0:disable, 1:enable\nvow_set_red_show_sta = <STA num>\nvow_set_red_tar_delay = <tarDelay> us\n======== WATF ===========\nvow_watf_en = <0/1> 0:disable, 1:enable\nvow_watf_q = <level>-<quantum> unit 256us\nvow_watf_add_entry = <level>-<Addr>\nvow_watf_del_entry = <Addr>\n"
                           [iVar3 + 0xda]) goto LAB_0021eb34;
        bVar4 = param_1 != pcVar1;
        pcVar1 = pcVar1 + 0x5834;
      } while (bVar4);
    }
    "%u-%02x:%02x:%02x:%02x:%02x:%02x"[uVar2 * 0x5834 + iVar3 + 0x14] = '\0';
  }
LAB_0021eb34:
  if (param_1[0x1f] == '\0') {
    return;
  }
  RTMP_OS_Add_Timer(param_1,*(undefined4 *)(param_1 + 0x20));
  return;
}

