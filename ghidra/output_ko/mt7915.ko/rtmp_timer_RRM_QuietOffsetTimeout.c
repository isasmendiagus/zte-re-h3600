// module: mt7915.ko
// function: rtmp_timer_RRM_QuietOffsetTimeout @ 0x21f124
// size: 204 bytes
//

void rtmp_timer_RRM_QuietOffsetTimeout(char *param_1)

{
  uint uVar1;
  char *pcVar2;
  int iVar3;
  bool bVar4;
  
  iVar3 = *(int *)(param_1 + 0x24);
  if ((byte)"======== Badnode detector =============\nvow_bn_en = <0/1> 0:dieable, 1:enable\nvow_bn_mon_period = <period> ms\nvow_bn_fallback_th = <count>\nvow_bn_per_th = <TX PER>\n======== Airtime counter test =============\nvow_counter_test = <0/1> 0:dieable, 1:enable\nvow_counter_test_period = <period> ms\nvow_counter_test_band = <band>\nvow_counter_test_avgcnt = <average num> sec\nvow_counter_test_target = <wlanidx>\n======== DVT =============\nvow_dvt_en = <0/1> 0:dieable, 1:enable\nvow_monitor_sta = <STA num>\nvow_show_sta = <STA num>\nvow_monitor_bss = <BSS num>\nvow_monitor_mbss = <MBSS num>\nvow_show_mbss = <MBSS num>\nvow_avg_num = <average num> sec\n======== RED ===========\nvow_set_red_en = <0/1> 0:disable, 1:enable\nvow_set_red_show_sta = <STA num>\nvow_set_red_tar_delay = <tarDelay> us\n======== WATF ===========\nvow_watf_en = <0/1> 0:disable, 1:enable\nvow_watf_q = <level>-<quantum> unit 256us\nvow_watf_add_entry = <level>-<Addr>\nvow_watf_del_entry = <Addr>\n"
            [iVar3 + 0xda] != 0) {
    if (param_1 == "%u-%02x:%02x:%02x:%02x:%02x:%02x" + iVar3 + 0x1c) {
      uVar1 = 0;
    }
    else {
      uVar1 = 0;
      pcVar2 = "Tx success                      = %lu\n" + iVar3 + 0x20;
      do {
        uVar1 = uVar1 + 1;
        if (uVar1 == (byte)"======== Badnode detector =============\nvow_bn_en = <0/1> 0:dieable, 1:enable\nvow_bn_mon_period = <period> ms\nvow_bn_fallback_th = <count>\nvow_bn_per_th = <TX PER>\n======== Airtime counter test =============\nvow_counter_test = <0/1> 0:dieable, 1:enable\nvow_counter_test_period = <period> ms\nvow_counter_test_band = <band>\nvow_counter_test_avgcnt = <average num> sec\nvow_counter_test_target = <wlanidx>\n======== DVT =============\nvow_dvt_en = <0/1> 0:dieable, 1:enable\nvow_monitor_sta = <STA num>\nvow_show_sta = <STA num>\nvow_monitor_bss = <BSS num>\nvow_monitor_mbss = <MBSS num>\nvow_show_mbss = <MBSS num>\nvow_avg_num = <average num> sec\n======== RED ===========\nvow_set_red_en = <0/1> 0:disable, 1:enable\nvow_set_red_show_sta = <STA num>\nvow_set_red_tar_delay = <tarDelay> us\n======== WATF ===========\nvow_watf_en = <0/1> 0:disable, 1:enable\nvow_watf_q = <level>-<quantum> unit 256us\nvow_watf_add_entry = <level>-<Addr>\nvow_watf_del_entry = <Addr>\n"
                           [iVar3 + 0xda]) goto LAB_0021f18c;
        bVar4 = param_1 != pcVar2;
        pcVar2 = pcVar2 + 0x5834;
      } while (bVar4);
    }
    iVar3 = iVar3 + uVar1 * 0x5834;
    "%u-%02x:%02x:%02x:%02x:%02x:%02x"[iVar3 + 0x14] = '\x01';
    RTMPSetTimer("This MAC Address %02x:%02x:%02x:%02x:%02x:%02x is duplicate.\n" + iVar3 + 0x2c,
                 "The entry Level %d - %02x:%02x:%02x:%02x:%02x:%02x is set complete!\n"
                 [iVar3 + 0x22]);
  }
LAB_0021f18c:
  if (param_1[0x1f] == '\0') {
    return;
  }
  RTMP_OS_Add_Timer(param_1,*(undefined4 *)(param_1 + 0x20));
  return;
}

