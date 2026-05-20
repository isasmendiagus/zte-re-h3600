// module: mt7915.ko
// function: show_twt_support_cap_proc @ 0xe1054
// size: 272 bytes
//

undefined4 show_twt_support_cap_proc(int param_1)

{
  undefined4 uVar1;
  char cVar2;
  undefined *puVar3;
  uint uVar4;
  bool bVar5;
  
  cVar2 = *(char *)(param_1 + 0x286285);
  if (cVar2 == '\0') {
    puVar3 = &DAT_0036db58 + param_1;
    cVar2 = '\0';
    do {
      if ((puVar3 != (undefined *)0x0) && (0 < DebugLevel)) {
        uVar1 = wlan_config_get_he_twt_support(puVar3);
        printk("\t STA_%d, twt_support on wf_cfg=%d\n",cVar2,uVar1);
      }
      bVar5 = cVar2 != '\x01';
      cVar2 = '\x01';
      puVar3 = puVar3 + 0x2137b0;
    } while (bVar5);
    cVar2 = *(char *)(param_1 + 0x286285);
  }
  if ((cVar2 == '\x01') &&
     ("======== Badnode detector =============\nvow_bn_en = <0/1> 0:dieable, 1:enable\nvow_bn_mon_period = <period> ms\nvow_bn_fallback_th = <count>\nvow_bn_per_th = <TX PER>\n======== Airtime counter test =============\nvow_counter_test = <0/1> 0:dieable, 1:enable\nvow_counter_test_period = <period> ms\nvow_counter_test_band = <band>\nvow_counter_test_avgcnt = <average num> sec\nvow_counter_test_target = <wlanidx>\n======== DVT =============\nvow_dvt_en = <0/1> 0:dieable, 1:enable\nvow_monitor_sta = <STA num>\nvow_show_sta = <STA num>\nvow_monitor_bss = <BSS num>\nvow_monitor_mbss = <MBSS num>\nvow_show_mbss = <MBSS num>\nvow_avg_num = <average num> sec\n======== RED ===========\nvow_set_red_en = <0/1> 0:disable, 1:enable\nvow_set_red_show_sta = <STA num>\nvow_set_red_tar_delay = <tarDelay> us\n======== WATF ===========\nvow_watf_en = <0/1> 0:disable, 1:enable\nvow_watf_q = <level>-<quantum> unit 256us\nvow_watf_add_entry = <level>-<Addr>\nvow_watf_del_entry = <Addr>\n"
      [param_1 + 0xda] != '\0')) {
    uVar4 = 0;
    do {
      if ((uVar4 * 0x5834 + param_1 != -0x2b7248) && (0 < DebugLevel)) {
        uVar1 = wlan_config_get_he_twt_support();
        printk("\t AP_%d, twt_support on wf_cfg=%d\n",uVar4,uVar1);
      }
      uVar4 = uVar4 + 1 & 0xff;
    } while (uVar4 < (byte)"======== Badnode detector =============\nvow_bn_en = <0/1> 0:dieable, 1:enable\nvow_bn_mon_period = <period> ms\nvow_bn_fallback_th = <count>\nvow_bn_per_th = <TX PER>\n======== Airtime counter test =============\nvow_counter_test = <0/1> 0:dieable, 1:enable\nvow_counter_test_period = <period> ms\nvow_counter_test_band = <band>\nvow_counter_test_avgcnt = <average num> sec\nvow_counter_test_target = <wlanidx>\n======== DVT =============\nvow_dvt_en = <0/1> 0:dieable, 1:enable\nvow_monitor_sta = <STA num>\nvow_show_sta = <STA num>\nvow_monitor_bss = <BSS num>\nvow_monitor_mbss = <MBSS num>\nvow_show_mbss = <MBSS num>\nvow_avg_num = <average num> sec\n======== RED ===========\nvow_set_red_en = <0/1> 0:disable, 1:enable\nvow_set_red_show_sta = <STA num>\nvow_set_red_tar_delay = <tarDelay> us\n======== WATF ===========\nvow_watf_en = <0/1> 0:disable, 1:enable\nvow_watf_q = <level>-<quantum> unit 256us\nvow_watf_add_entry = <level>-<Addr>\nvow_watf_del_entry = <Addr>\n"
                           [param_1 + 0xda]);
  }
  return 1;
}

