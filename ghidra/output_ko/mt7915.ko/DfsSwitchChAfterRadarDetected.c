// module: mt7915.ko
// function: DfsSwitchChAfterRadarDetected @ 0x231e40
// size: 136 bytes
//

undefined4 DfsSwitchChAfterRadarDetected(int param_1,int param_2)

{
  uint uVar1;
  uint uVar2;
  
  uVar1 = **(uint **)(param_2 + 4);
  uVar2 = uVar1 >> 8 & 0xff;
  if (0 < DebugLevel) {
    printk("[%s] bandIdx: %d, BssIdx: %d, NextCh: %d\n","DfsSwitchChAfterRadarDetected",
           (uVar1 << 8) >> 0x18,uVar2,uVar1 & 0xff);
  }
  rtmp_set_channel(param_1,"======== Badnode detector =============\nvow_bn_en = <0/1> 0:dieable, 1:enable\nvow_bn_mon_period = <period> ms\nvow_bn_fallback_th = <count>\nvow_bn_per_th = <TX PER>\n======== Airtime counter test =============\nvow_counter_test = <0/1> 0:dieable, 1:enable\nvow_counter_test_period = <period> ms\nvow_counter_test_band = <band>\nvow_counter_test_avgcnt = <average num> sec\nvow_counter_test_target = <wlanidx>\n======== DVT =============\nvow_dvt_en = <0/1> 0:dieable, 1:enable\nvow_monitor_sta = <STA num>\nvow_show_sta = <STA num>\nvow_monitor_bss = <BSS num>\nvow_monitor_mbss = <MBSS num>\nvow_show_mbss = <MBSS num>\nvow_avg_num = <average num> sec\n======== RED ===========\nvow_set_red_en = <0/1> 0:disable, 1:enable\nvow_set_red_show_sta = <STA num>\nvow_set_red_tar_delay = <tarDelay> us\n======== WATF ===========\nvow_watf_en = <0/1> 0:disable, 1:enable\nvow_watf_q = <level>-<quantum> unit 256us\nvow_watf_add_entry = <level>-<Addr>\nvow_watf_del_entry = <Addr>\n"
                           + uVar2 * 0x5834 + param_1 + 0xe0,uVar1 & 0xff);
  return 0;
}

