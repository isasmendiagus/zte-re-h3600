// module: mt7915.ko
// function: mdvt_disable @ 0x1d76ec
// size: 288 bytes
//

void mdvt_disable(int param_1)

{
  byte bVar1;
  int iVar2;
  int iVar3;
  int *piVar4;
  int iVar5;
  
  if (param_1 == 0) {
    return;
  }
  if (*(char *)(param_1 + 0xa7c23e) != '\x01') {
    return;
  }
  if (*(char *)(param_1 + 0xa7c23f) != '\x01') {
    return;
  }
  bVar1 = "======== Badnode detector =============\nvow_bn_en = <0/1> 0:dieable, 1:enable\nvow_bn_mon_period = <period> ms\nvow_bn_fallback_th = <count>\nvow_bn_per_th = <TX PER>\n======== Airtime counter test =============\nvow_counter_test = <0/1> 0:dieable, 1:enable\nvow_counter_test_period = <period> ms\nvow_counter_test_band = <band>\nvow_counter_test_avgcnt = <average num> sec\nvow_counter_test_target = <wlanidx>\n======== DVT =============\nvow_dvt_en = <0/1> 0:dieable, 1:enable\nvow_monitor_sta = <STA num>\nvow_show_sta = <STA num>\nvow_monitor_bss = <BSS num>\nvow_monitor_mbss = <MBSS num>\nvow_show_mbss = <MBSS num>\nvow_avg_num = <average num> sec\n======== RED ===========\nvow_set_red_en = <0/1> 0:disable, 1:enable\nvow_set_red_show_sta = <STA num>\nvow_set_red_tar_delay = <tarDelay> us\n======== WATF ===========\nvow_watf_en = <0/1> 0:disable, 1:enable\nvow_watf_q = <level>-<quantum> unit 256us\nvow_watf_add_entry = <level>-<Addr>\nvow_watf_del_entry = <Addr>\n"
          [param_1 + 0xda];
  *(uint *)(param_1 + 0xa39f84) = *(uint *)(param_1 + 0xa39f84) & 0xff7fffff;
  _clear_bit(0,*(int *)(*(int *)(param_1 + 4) + 0x240) + 0x50);
  RTMPSetTimer(param_1 + 0x82910c,100);
  APStartUp(param_1,"======== Badnode detector =============\nvow_bn_en = <0/1> 0:dieable, 1:enable\nvow_bn_mon_period = <period> ms\nvow_bn_fallback_th = <count>\nvow_bn_per_th = <TX PER>\n======== Airtime counter test =============\nvow_counter_test = <0/1> 0:dieable, 1:enable\nvow_counter_test_period = <period> ms\nvow_counter_test_band = <band>\nvow_counter_test_avgcnt = <average num> sec\nvow_counter_test_target = <wlanidx>\n======== DVT =============\nvow_dvt_en = <0/1> 0:dieable, 1:enable\nvow_monitor_sta = <STA num>\nvow_show_sta = <STA num>\nvow_monitor_bss = <BSS num>\nvow_monitor_mbss = <MBSS num>\nvow_show_mbss = <MBSS num>\nvow_avg_num = <average num> sec\n======== RED ===========\nvow_set_red_en = <0/1> 0:disable, 1:enable\nvow_set_red_show_sta = <STA num>\nvow_set_red_tar_delay = <tarDelay> us\n======== WATF ===========\nvow_watf_en = <0/1> 0:disable, 1:enable\nvow_watf_q = <level>-<quantum> unit 256us\nvow_watf_add_entry = <level>-<Addr>\nvow_watf_del_entry = <Addr>\n"
                    + param_1 + 0xe0,0);
  if (*(char *)(param_1 + 0x286285) == '\x01') {
    iVar2 = hc_get_chip_bcn_max_num(*(undefined4 *)(param_1 + 0xa797a0));
    if (iVar2 < (int)(uint)bVar1) {
      hc_get_chip_bcn_max_num(*(undefined4 *)(param_1 + 0xa797a0));
    }
    piVar4 = (int *)("%s: Allocate memory fail!!!\n" + param_1 + 0xc);
    iVar2 = 1;
    while( true ) {
      iVar3 = hc_get_chip_bcn_max_num(*(undefined4 *)(param_1 + 0xa797a0));
      iVar5 = iVar2 + 1;
      if (iVar3 <= iVar2) break;
      iVar3 = *piVar4;
      piVar4 = piVar4 + 0x160d;
      iVar2 = iVar5;
      if (iVar3 != 0) {
        _clear_bit(0,*(int *)(iVar3 + 0x240) + 0x50);
      }
    }
  }
  *(undefined1 *)(param_1 + 0xa7c23f) = 0;
  return;
}

