// module: mt7915.ko
// function: muru_tune_ap_muedca_handler @ 0x23b3f8
// size: 244 bytes
//

void muru_tune_ap_muedca_handler(int param_1,int param_2,undefined4 param_3,undefined4 param_4)

{
  ushort uVar1;
  undefined1 uVar2;
  uint uVar3;
  int iVar4;
  char *pcVar5;
  uint uVar6;
  
  uVar1 = *(ushort *)(param_2 + 4);
  if (*(char *)(param_1 + 0x795a80) == '\x01') {
    if (DebugLevel < 1) goto LAB_0023b434;
  }
  else if (DebugLevel < 3) goto LAB_0023b434;
  printk("EVENT_MURU_TUNE_AP_MUEDCA setting %d tune Band %d BCN MU_EDCA timer to %d\n",uVar1,
         *(undefined1 *)(param_2 + 6),uVar1 & 0xff,param_4);
LAB_0023b434:
  if ("======== Badnode detector =============\nvow_bn_en = <0/1> 0:dieable, 1:enable\nvow_bn_mon_period = <period> ms\nvow_bn_fallback_th = <count>\nvow_bn_per_th = <TX PER>\n======== Airtime counter test =============\nvow_counter_test = <0/1> 0:dieable, 1:enable\nvow_counter_test_period = <period> ms\nvow_counter_test_band = <band>\nvow_counter_test_avgcnt = <average num> sec\nvow_counter_test_target = <wlanidx>\n======== DVT =============\nvow_dvt_en = <0/1> 0:dieable, 1:enable\nvow_monitor_sta = <STA num>\nvow_show_sta = <STA num>\nvow_monitor_bss = <BSS num>\nvow_monitor_mbss = <MBSS num>\nvow_show_mbss = <MBSS num>\nvow_avg_num = <average num> sec\n======== RED ===========\nvow_set_red_en = <0/1> 0:disable, 1:enable\nvow_set_red_show_sta = <STA num>\nvow_set_red_tar_delay = <tarDelay> us\n======== WATF ===========\nvow_watf_en = <0/1> 0:disable, 1:enable\nvow_watf_q = <level>-<quantum> unit 256us\nvow_watf_add_entry = <level>-<Addr>\nvow_watf_del_entry = <Addr>\n"
      [param_1 + 0xda] == '\0') {
    return;
  }
  uVar6 = 0;
  pcVar5 = "======== Badnode detector =============\nvow_bn_en = <0/1> 0:dieable, 1:enable\nvow_bn_mon_period = <period> ms\nvow_bn_fallback_th = <count>\nvow_bn_per_th = <TX PER>\n======== Airtime counter test =============\nvow_counter_test = <0/1> 0:dieable, 1:enable\nvow_counter_test_period = <period> ms\nvow_counter_test_band = <band>\nvow_counter_test_avgcnt = <average num> sec\nvow_counter_test_target = <wlanidx>\n======== DVT =============\nvow_dvt_en = <0/1> 0:dieable, 1:enable\nvow_monitor_sta = <STA num>\nvow_show_sta = <STA num>\nvow_monitor_bss = <BSS num>\nvow_monitor_mbss = <MBSS num>\nvow_show_mbss = <MBSS num>\nvow_avg_num = <average num> sec\n======== RED ===========\nvow_set_red_en = <0/1> 0:disable, 1:enable\nvow_set_red_show_sta = <STA num>\nvow_set_red_tar_delay = <tarDelay> us\n======== WATF ===========\nvow_watf_en = <0/1> 0:disable, 1:enable\nvow_watf_q = <level>-<quantum> unit 256us\nvow_watf_add_entry = <level>-<Addr>\nvow_watf_del_entry = <Addr>\n"
           + param_1 + 0xe0;
  do {
    uVar6 = uVar6 + 1;
    if ((pcVar5[0xb1c] != '\0') &&
       (uVar3 = HcGetBandByWdev(pcVar5), *(byte *)(param_2 + 6) == uVar3)) {
      iVar4 = wlan_config_get_he_mu_edca(pcVar5);
      uVar2 = (undefined1)uVar1;
      if (iVar4 != 0) {
        *(undefined1 *)(iVar4 + 4) = uVar2;
        *(undefined1 *)(iVar4 + 9) = uVar2;
        *(undefined1 *)(iVar4 + 0xe) = uVar2;
        *(undefined1 *)(iVar4 + 0x13) = uVar2;
      }
      UpdateBeaconHandler(param_1,pcVar5,2);
    }
    pcVar5 = pcVar5 + 0x5834;
  } while (uVar6 < (byte)"======== Badnode detector =============\nvow_bn_en = <0/1> 0:dieable, 1:enable\nvow_bn_mon_period = <period> ms\nvow_bn_fallback_th = <count>\nvow_bn_per_th = <TX PER>\n======== Airtime counter test =============\nvow_counter_test = <0/1> 0:dieable, 1:enable\nvow_counter_test_period = <period> ms\nvow_counter_test_band = <band>\nvow_counter_test_avgcnt = <average num> sec\nvow_counter_test_target = <wlanidx>\n======== DVT =============\nvow_dvt_en = <0/1> 0:dieable, 1:enable\nvow_monitor_sta = <STA num>\nvow_show_sta = <STA num>\nvow_monitor_bss = <BSS num>\nvow_monitor_mbss = <MBSS num>\nvow_show_mbss = <MBSS num>\nvow_avg_num = <average num> sec\n======== RED ===========\nvow_set_red_en = <0/1> 0:disable, 1:enable\nvow_set_red_show_sta = <STA num>\nvow_set_red_tar_delay = <tarDelay> us\n======== WATF ===========\nvow_watf_en = <0/1> 0:disable, 1:enable\nvow_watf_q = <level>-<quantum> unit 256us\nvow_watf_add_entry = <level>-<Addr>\nvow_watf_del_entry = <Addr>\n"
                         [param_1 + 0xda]);
  return;
}

