// module: mt7915.ko
// function: get_wdev_by_idx @ 0x139ad8
// size: 284 bytes
//

char * get_wdev_by_idx(int param_1,int param_2)

{
  int iVar1;
  int iVar2;
  char *pcVar3;
  bool bVar4;
  
  if (param_2 < 0x30) {
    if (*(char *)(param_1 + 0x286285) == '\x01') goto LAB_00139b84;
    bVar4 = param_2 == 1;
    if (param_2 < 2) {
      bVar4 = *(char *)(param_1 + 0x286285) == '\0';
    }
    if (!bVar4) goto LAB_00139b0c;
    pcVar3 = &DAT_0036db58 + param_1 + param_2 * 0x2137b0;
  }
  else {
    param_2 = param_2 + -0x30;
    if (param_2 < 2) {
      pcVar3 = &DAT_0036db58 + param_1 + param_2 * 0x2137b0;
    }
    else {
      if (*(char *)(param_1 + 0x286285) != '\x01') goto LAB_00139b0c;
LAB_00139b84:
      if ((int)(uint)(byte)"======== Badnode detector =============\nvow_bn_en = <0/1> 0:dieable, 1:enable\nvow_bn_mon_period = <period> ms\nvow_bn_fallback_th = <count>\nvow_bn_per_th = <TX PER>\n======== Airtime counter test =============\nvow_counter_test = <0/1> 0:dieable, 1:enable\nvow_counter_test_period = <period> ms\nvow_counter_test_band = <band>\nvow_counter_test_avgcnt = <average num> sec\nvow_counter_test_target = <wlanidx>\n======== DVT =============\nvow_dvt_en = <0/1> 0:dieable, 1:enable\nvow_monitor_sta = <STA num>\nvow_show_sta = <STA num>\nvow_monitor_bss = <BSS num>\nvow_monitor_mbss = <MBSS num>\nvow_show_mbss = <MBSS num>\nvow_avg_num = <average num> sec\n======== RED ===========\nvow_set_red_en = <0/1> 0:disable, 1:enable\nvow_set_red_show_sta = <STA num>\nvow_set_red_tar_delay = <tarDelay> us\n======== WATF ===========\nvow_watf_en = <0/1> 0:disable, 1:enable\nvow_watf_q = <level>-<quantum> unit 256us\nvow_watf_add_entry = <level>-<Addr>\nvow_watf_del_entry = <Addr>\n"
                           [param_1 + 0xda] <= param_2) goto LAB_00139b0c;
      iVar2 = hc_get_chip_bcn_max_num(*(undefined4 *)(param_1 + 0xa797a0));
      bVar4 = SBORROW4(param_2,0x1f);
      iVar1 = param_2 + -0x1f;
      if (param_2 < 0x20) {
        bVar4 = SBORROW4(param_2,iVar2);
        iVar1 = param_2 - iVar2;
      }
      if (iVar1 < 0 == bVar4) goto LAB_00139b0c;
      pcVar3 = "======== Badnode detector =============\nvow_bn_en = <0/1> 0:dieable, 1:enable\nvow_bn_mon_period = <period> ms\nvow_bn_fallback_th = <count>\nvow_bn_per_th = <TX PER>\n======== Airtime counter test =============\nvow_counter_test = <0/1> 0:dieable, 1:enable\nvow_counter_test_period = <period> ms\nvow_counter_test_band = <band>\nvow_counter_test_avgcnt = <average num> sec\nvow_counter_test_target = <wlanidx>\n======== DVT =============\nvow_dvt_en = <0/1> 0:dieable, 1:enable\nvow_monitor_sta = <STA num>\nvow_show_sta = <STA num>\nvow_monitor_bss = <BSS num>\nvow_monitor_mbss = <MBSS num>\nvow_show_mbss = <MBSS num>\nvow_avg_num = <average num> sec\n======== RED ===========\nvow_set_red_en = <0/1> 0:disable, 1:enable\nvow_set_red_show_sta = <STA num>\nvow_set_red_tar_delay = <tarDelay> us\n======== WATF ===========\nvow_watf_en = <0/1> 0:disable, 1:enable\nvow_watf_q = <level>-<quantum> unit 256us\nvow_watf_add_entry = <level>-<Addr>\nvow_watf_del_entry = <Addr>\n"
               + param_2 * 0x5834 + param_1 + 0xe0;
    }
  }
  if (pcVar3 != (char *)0x0) {
    return pcVar3;
  }
LAB_00139b0c:
  if (0 < DebugLevel) {
    printk("get_wdev_by_idx: invalid idx(%d)\n");
  }
  return (char *)0x0;
}

