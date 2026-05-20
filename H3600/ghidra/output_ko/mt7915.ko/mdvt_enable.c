// module: mt7915.ko
// function: mdvt_enable @ 0x1d7574
// size: 376 bytes
//

void mdvt_enable(int param_1)

{
  byte bVar1;
  int iVar2;
  int iVar3;
  int *piVar4;
  undefined1 uStack_19;
  
  if (param_1 == 0) {
    return;
  }
  if ((*(char *)(param_1 + 0xa7c23e) == '\x01') && (*(char *)(param_1 + 0xa7c23f) == '\0')) {
    *(undefined1 *)(param_1 + 0xa7c23f) = 1;
    iVar3 = *(int *)(*(int *)(param_1 + 4) + 0x240);
    bVar1 = "======== Badnode detector =============\nvow_bn_en = <0/1> 0:dieable, 1:enable\nvow_bn_mon_period = <period> ms\nvow_bn_fallback_th = <count>\nvow_bn_per_th = <TX PER>\n======== Airtime counter test =============\nvow_counter_test = <0/1> 0:dieable, 1:enable\nvow_counter_test_period = <period> ms\nvow_counter_test_band = <band>\nvow_counter_test_avgcnt = <average num> sec\nvow_counter_test_target = <wlanidx>\n======== DVT =============\nvow_dvt_en = <0/1> 0:dieable, 1:enable\nvow_monitor_sta = <STA num>\nvow_show_sta = <STA num>\nvow_monitor_bss = <BSS num>\nvow_monitor_mbss = <MBSS num>\nvow_show_mbss = <MBSS num>\nvow_avg_num = <average num> sec\n======== RED ===========\nvow_set_red_en = <0/1> 0:disable, 1:enable\nvow_set_red_show_sta = <STA num>\nvow_set_red_tar_delay = <tarDelay> us\n======== WATF ===========\nvow_watf_en = <0/1> 0:disable, 1:enable\nvow_watf_q = <level>-<quantum> unit 256us\nvow_watf_add_entry = <level>-<Addr>\nvow_watf_del_entry = <Addr>\n"
            [param_1 + 0xda];
    if (iVar3 == 0) {
      warn_slowpath_null("include/linux/netdevice.h",0xa06);
      printk(&_LC1);
    }
    else {
      _set_bit(0,iVar3 + 0x50);
    }
    if (*(char *)(param_1 + 0x286285) == '\x01') {
      iVar3 = hc_get_chip_bcn_max_num(*(undefined4 *)(param_1 + 0xa797a0));
      if (iVar3 < (int)(uint)bVar1) {
        hc_get_chip_bcn_max_num(*(undefined4 *)(param_1 + 0xa797a0));
      }
      piVar4 = (int *)("%s: Allocate memory fail!!!\n" + param_1 + 0xc);
      for (iVar3 = 1; iVar2 = hc_get_chip_bcn_max_num(*(undefined4 *)(param_1 + 0xa797a0)),
          iVar3 < iVar2; iVar3 = iVar3 + 1) {
        if (*piVar4 != 0) {
          iVar2 = *(int *)(*piVar4 + 0x240);
          if (iVar2 == 0) {
            warn_slowpath_null("include/linux/netdevice.h",0xa06);
            printk(&_LC1);
          }
          else {
            _set_bit(0,iVar2 + 0x50);
          }
        }
        piVar4 = piVar4 + 0x160d;
      }
    }
    APStop(param_1,"======== Badnode detector =============\nvow_bn_en = <0/1> 0:dieable, 1:enable\nvow_bn_mon_period = <period> ms\nvow_bn_fallback_th = <count>\nvow_bn_per_th = <TX PER>\n======== Airtime counter test =============\nvow_counter_test = <0/1> 0:dieable, 1:enable\nvow_counter_test_period = <period> ms\nvow_counter_test_band = <band>\nvow_counter_test_avgcnt = <average num> sec\nvow_counter_test_target = <wlanidx>\n======== DVT =============\nvow_dvt_en = <0/1> 0:dieable, 1:enable\nvow_monitor_sta = <STA num>\nvow_show_sta = <STA num>\nvow_monitor_bss = <BSS num>\nvow_monitor_mbss = <MBSS num>\nvow_show_mbss = <MBSS num>\nvow_avg_num = <average num> sec\n======== RED ===========\nvow_set_red_en = <0/1> 0:disable, 1:enable\nvow_set_red_show_sta = <STA num>\nvow_set_red_tar_delay = <tarDelay> us\n======== WATF ===========\nvow_watf_en = <0/1> 0:disable, 1:enable\nvow_watf_q = <level>-<quantum> unit 256us\nvow_watf_add_entry = <level>-<Addr>\nvow_watf_del_entry = <Addr>\n"
                   + param_1 + 0xe0,0);
    *(uint *)(param_1 + 0xa39f84) = *(uint *)(param_1 + 0xa39f84) | 0x800000;
    RTMPCancelTimer(param_1 + 0x82910c,&uStack_19);
    return;
  }
  return;
}

