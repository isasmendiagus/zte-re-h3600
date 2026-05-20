// module: mt7915.ko
// function: ap_inf_open @ 0x16e28
// size: 336 bytes
//

undefined4 ap_inf_open(int param_1,undefined4 param_2,undefined4 param_3,undefined4 param_4)

{
  int iVar1;
  int iVar2;
  
  iVar2 = *(int *)(param_1 + 8);
  *(uint *)("Set::OID_802_11_SET_PASSPHRASE, Failed (len less than 8 or greater than 64)!!\n" +
           (uint)*(byte *)(param_1 + 0xe) * 0x5834 + iVar2 + 0x2c) = (uint)*(byte *)(param_1 + 0xe);
  iVar1 = wifi_sys_open();
  if (iVar1 != 1) {
    if (2 < DebugLevel) {
      printk("%s() open fail!!!\n","ap_inf_open");
    }
    return 0;
  }
  if (0 < DebugLevel) {
    printk("AP inf up for ra_%x(func_idx) OmacIdx=%d\n",*(undefined1 *)(param_1 + 0xe),
           *(undefined1 *)(param_1 + 0x29),DebugLevel,param_4);
  }
  MlmeRadioOn(iVar2,param_1);
  *(undefined1 *)(param_1 + 0xb1c) = 1;
  auto_ch_select_reset_sm(iVar2,param_1);
  BackgroundScanInit(iVar2,param_1);
  iVar1 = ApAutoChannelAtBootUp(iVar2,param_1);
  if ((iVar1 != 1) && (1 < DebugLevel)) {
    printk(&_LC103,"ap_run_at_boot");
  }
  APStartUpForMbss(iVar2,"======== Badnode detector =============\nvow_bn_en = <0/1> 0:dieable, 1:enable\nvow_bn_mon_period = <period> ms\nvow_bn_fallback_th = <count>\nvow_bn_per_th = <TX PER>\n======== Airtime counter test =============\nvow_counter_test = <0/1> 0:dieable, 1:enable\nvow_counter_test_period = <period> ms\nvow_counter_test_band = <band>\nvow_counter_test_avgcnt = <average num> sec\nvow_counter_test_target = <wlanidx>\n======== DVT =============\nvow_dvt_en = <0/1> 0:dieable, 1:enable\nvow_monitor_sta = <STA num>\nvow_show_sta = <STA num>\nvow_monitor_bss = <BSS num>\nvow_monitor_mbss = <MBSS num>\nvow_show_mbss = <MBSS num>\nvow_avg_num = <average num> sec\n======== RED ===========\nvow_set_red_en = <0/1> 0:disable, 1:enable\nvow_set_red_show_sta = <STA num>\nvow_set_red_tar_delay = <tarDelay> us\n======== WATF ===========\nvow_watf_en = <0/1> 0:disable, 1:enable\nvow_watf_q = <level>-<quantum> unit 256us\nvow_watf_add_entry = <level>-<Addr>\nvow_watf_del_entry = <Addr>\n"
                         + (uint)*(byte *)(param_1 + 0xe) * 0x5834 + iVar2 + 0xe0);
  if (0 < DebugLevel) {
    printk("apidx %d for WscUUIDInit\n",*(undefined1 *)(param_1 + 0xe));
  }
  WscUUIDInit(iVar2,*(undefined1 *)(param_1 + 0xe),0);
  return 1;
}

