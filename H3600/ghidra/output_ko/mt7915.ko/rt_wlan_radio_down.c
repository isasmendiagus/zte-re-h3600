// module: mt7915.ko
// function: rt_wlan_radio_down @ 0x15617c
// size: 184 bytes
//

undefined4 rt_wlan_radio_down(void)

{
  int iVar1;
  uint uVar2;
  char *pcVar3;
  uint uVar4;
  bool bVar5;
  char local_1a [2];
  
  iVar1 = g_pAd;
  uVar4 = 0;
  local_1a[0] = '\0';
  local_1a[1] = '\0';
  if (g_pAd != 0) {
    pcVar3 = "======== Badnode detector =============\nvow_bn_en = <0/1> 0:dieable, 1:enable\nvow_bn_mon_period = <period> ms\nvow_bn_fallback_th = <count>\nvow_bn_per_th = <TX PER>\n======== Airtime counter test =============\nvow_counter_test = <0/1> 0:dieable, 1:enable\nvow_counter_test_period = <period> ms\nvow_counter_test_band = <band>\nvow_counter_test_avgcnt = <average num> sec\nvow_counter_test_target = <wlanidx>\n======== DVT =============\nvow_dvt_en = <0/1> 0:dieable, 1:enable\nvow_monitor_sta = <STA num>\nvow_show_sta = <STA num>\nvow_monitor_bss = <BSS num>\nvow_monitor_mbss = <MBSS num>\nvow_show_mbss = <MBSS num>\nvow_avg_num = <average num> sec\n======== RED ===========\nvow_set_red_en = <0/1> 0:disable, 1:enable\nvow_set_red_show_sta = <STA num>\nvow_set_red_tar_delay = <tarDelay> us\n======== WATF ===========\nvow_watf_en = <0/1> 0:disable, 1:enable\nvow_watf_q = <level>-<quantum> unit 256us\nvow_watf_add_entry = <level>-<Addr>\nvow_watf_del_entry = <Addr>\n"
             + g_pAd + 0xe0;
    while( true ) {
      uVar2 = hc_get_chip_bcn_max_num(*(undefined4 *)(iVar1 + 0xa797a0));
      bVar5 = uVar2 <= uVar4;
      uVar4 = uVar4 + 1;
      if (bVar5) break;
      if ((pcVar3[0x28] != '\0') && (uVar2 = HcGetBandByWdev(pcVar3), uVar2 < 2)) {
        if (local_1a[uVar2] == '\0') {
          local_1a[uVar2] = '\x01';
          MlmeRadioOff(iVar1,pcVar3);
        }
      }
      pcVar3 = pcVar3 + 0x5834;
    }
  }
  printk("<== rt_wlan_radio_down\n");
  return 0;
}

