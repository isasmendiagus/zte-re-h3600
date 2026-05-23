// module: mt7915.ko
// function: WscCheckPinAttackCount @ 0x2013f8
// size: 300 bytes
//

void WscCheckPinAttackCount(int param_1,int param_2)

{
  byte bVar1;
  byte bVar2;
  undefined1 auStack_21 [5];
  
  bVar1 = *(byte *)(param_2 + 0x1c54);
  if ((bVar1 & 0x30) == 0) {
    bVar2 = *(char *)(param_2 + 0x2bda) + 1;
    *(byte *)(param_2 + 0x2bda) = bVar2;
    if (*(byte *)(param_2 + 0x2bdb) <= bVar2) {
      *(undefined1 *)(param_2 + 0x2bd9) = 1;
      if (*(char *)(param_2 + 0x2ba0) != '\0') {
        RTMPCancelTimer(param_2 + 0x2b6c,auStack_21);
        bVar2 = *(byte *)(param_2 + 0x2bda);
        *(byte *)(param_2 + 0x2ba0) = bVar1 & 0x30;
      }
      if (bVar2 < 10) {
        *(undefined1 *)(param_2 + 0x2ba0) = 1;
        RTMPSetTimer(param_2 + 0x2b6c,*(int *)(param_2 + 0x2bdc) * 60000);
      }
      WscBuildBeaconIE(param_1,*(undefined1 *)(param_2 + 8),0,0,0,*(byte *)(param_2 + 0x1c54) & 0xf,
                       0,0,0);
      WscBuildProbeRespIE(param_1,3,*(undefined1 *)(param_2 + 8),0,0,0,
                          *(undefined1 *)(param_2 + 0x1c54),0,0,0);
      UpdateBeaconHandler(param_1,"======== Badnode detector =============\nvow_bn_en = <0/1> 0:dieable, 1:enable\nvow_bn_mon_period = <period> ms\nvow_bn_fallback_th = <count>\nvow_bn_per_th = <TX PER>\n======== Airtime counter test =============\nvow_counter_test = <0/1> 0:dieable, 1:enable\nvow_counter_test_period = <period> ms\nvow_counter_test_band = <band>\nvow_counter_test_avgcnt = <average num> sec\nvow_counter_test_target = <wlanidx>\n======== DVT =============\nvow_dvt_en = <0/1> 0:dieable, 1:enable\nvow_monitor_sta = <STA num>\nvow_show_sta = <STA num>\nvow_monitor_bss = <BSS num>\nvow_monitor_mbss = <MBSS num>\nvow_show_mbss = <MBSS num>\nvow_avg_num = <average num> sec\n======== RED ===========\nvow_set_red_en = <0/1> 0:disable, 1:enable\nvow_set_red_show_sta = <STA num>\nvow_set_red_tar_delay = <tarDelay> us\n======== WATF ===========\nvow_watf_en = <0/1> 0:disable, 1:enable\nvow_watf_q = <level>-<quantum> unit 256us\nvow_watf_add_entry = <level>-<Addr>\nvow_watf_del_entry = <Addr>\n"
                                  + (bVar1 & 0xf) * 0x5834 + param_1 + 0xe0,2);
    }
  }
  return;
}

