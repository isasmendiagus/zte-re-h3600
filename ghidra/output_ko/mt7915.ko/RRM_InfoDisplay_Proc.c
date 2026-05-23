// module: mt7915.ko
// function: RRM_InfoDisplay_Proc @ 0x220198
// size: 348 bytes
//

undefined4
RRM_InfoDisplay_Proc(int param_1,undefined4 param_2,undefined4 param_3,undefined4 param_4)

{
  undefined4 uVar1;
  int iVar2;
  uint uVar3;
  char *pcVar4;
  int iVar5;
  
  uVar3 = (uint)(byte)"======== Badnode detector =============\nvow_bn_en = <0/1> 0:dieable, 1:enable\nvow_bn_mon_period = <period> ms\nvow_bn_fallback_th = <count>\nvow_bn_per_th = <TX PER>\n======== Airtime counter test =============\nvow_counter_test = <0/1> 0:dieable, 1:enable\nvow_counter_test_period = <period> ms\nvow_counter_test_band = <band>\nvow_counter_test_avgcnt = <average num> sec\nvow_counter_test_target = <wlanidx>\n======== DVT =============\nvow_dvt_en = <0/1> 0:dieable, 1:enable\nvow_monitor_sta = <STA num>\nvow_show_sta = <STA num>\nvow_monitor_bss = <BSS num>\nvow_monitor_mbss = <MBSS num>\nvow_show_mbss = <MBSS num>\nvow_avg_num = <average num> sec\n======== RED ===========\nvow_set_red_en = <0/1> 0:disable, 1:enable\nvow_set_red_show_sta = <STA num>\nvow_set_red_tar_delay = <tarDelay> us\n======== WATF ===========\nvow_watf_en = <0/1> 0:disable, 1:enable\nvow_watf_q = <level>-<quantum> unit 256us\nvow_watf_add_entry = <level>-<Addr>\nvow_watf_del_entry = <Addr>\n"
                      [param_1 + 0xda];
  iVar2 = DebugLevel;
  if (uVar3 == 0) {
    uVar3 = 0;
  }
  else {
    pcVar4 = "======== Badnode detector =============\nvow_bn_en = <0/1> 0:dieable, 1:enable\nvow_bn_mon_period = <period> ms\nvow_bn_fallback_th = <count>\nvow_bn_per_th = <TX PER>\n======== Airtime counter test =============\nvow_counter_test = <0/1> 0:dieable, 1:enable\nvow_counter_test_period = <period> ms\nvow_counter_test_band = <band>\nvow_counter_test_avgcnt = <average num> sec\nvow_counter_test_target = <wlanidx>\n======== DVT =============\nvow_dvt_en = <0/1> 0:dieable, 1:enable\nvow_monitor_sta = <STA num>\nvow_show_sta = <STA num>\nvow_monitor_bss = <BSS num>\nvow_monitor_mbss = <MBSS num>\nvow_show_mbss = <MBSS num>\nvow_avg_num = <average num> sec\n======== RED ===========\nvow_set_red_en = <0/1> 0:disable, 1:enable\nvow_set_red_show_sta = <STA num>\nvow_set_red_tar_delay = <tarDelay> us\n======== WATF ===========\nvow_watf_en = <0/1> 0:disable, 1:enable\nvow_watf_q = <level>-<quantum> unit 256us\nvow_watf_add_entry = <level>-<Addr>\nvow_watf_del_entry = <Addr>\n"
             + param_1 + 0xe0;
    iVar5 = 0;
    do {
      if (0 < iVar2) {
        printk("%d: bDot11kRRMEnable=%d\n",iVar5,pcVar4[0xb21],uVar3,param_4);
        iVar2 = DebugLevel;
        if (0 < DebugLevel) {
          printk("Regulator Class=");
          iVar2 = DebugLevel;
          if (0 < DebugLevel) {
            uVar1 = get_regulatory_class(param_1,pcVar4[0x1a],*(undefined2 *)(pcVar4 + 0x18),pcVar4)
            ;
            printk(&_LC45,uVar1);
            iVar2 = DebugLevel;
            if (0 < DebugLevel) {
              printk(&_LC46);
              iVar2 = DebugLevel;
            }
          }
        }
      }
      uVar3 = (uint)(byte)"======== Badnode detector =============\nvow_bn_en = <0/1> 0:dieable, 1:enable\nvow_bn_mon_period = <period> ms\nvow_bn_fallback_th = <count>\nvow_bn_per_th = <TX PER>\n======== Airtime counter test =============\nvow_counter_test = <0/1> 0:dieable, 1:enable\nvow_counter_test_period = <period> ms\nvow_counter_test_band = <band>\nvow_counter_test_avgcnt = <average num> sec\nvow_counter_test_target = <wlanidx>\n======== DVT =============\nvow_dvt_en = <0/1> 0:dieable, 1:enable\nvow_monitor_sta = <STA num>\nvow_show_sta = <STA num>\nvow_monitor_bss = <BSS num>\nvow_monitor_mbss = <MBSS num>\nvow_show_mbss = <MBSS num>\nvow_avg_num = <average num> sec\n======== RED ===========\nvow_set_red_en = <0/1> 0:disable, 1:enable\nvow_set_red_show_sta = <STA num>\nvow_set_red_tar_delay = <tarDelay> us\n======== WATF ===========\nvow_watf_en = <0/1> 0:disable, 1:enable\nvow_watf_q = <level>-<quantum> unit 256us\nvow_watf_add_entry = <level>-<Addr>\nvow_watf_del_entry = <Addr>\n"
                          [param_1 + 0xda];
      iVar5 = iVar5 + 1;
      pcVar4 = pcVar4 + 0x5834;
    } while (iVar5 < (int)uVar3);
  }
  if (((0 < iVar2) &&
      (printk("Country Code=%s\n",param_1 + 0x794c31,iVar2,uVar3,param_4), 0 < DebugLevel)) &&
     (printk("Power Constraint=%d\n",*(undefined1 *)(param_1 + 0x795043)), 0 < DebugLevel)) {
    printk("Regulator TxPowerPercentage=(%d, %d)\n",*(undefined1 *)(param_1 + 0x794cd8),
           *(undefined1 *)(param_1 + 0x794cd9),DebugLevel,param_4);
  }
  return 1;
}

