// module: mt7915.ko
// function: ChannelRescanHdlr @ 0xc46b0
// size: 228 bytes
//

undefined4 ChannelRescanHdlr(int param_1,int param_2)

{
  byte bVar1;
  int iVar2;
  int *piVar3;
  undefined4 uVar4;
  int iVar5;
  
  HcGetRadioChannel();
  iVar2 = get_default_wdev(param_1);
  piVar3 = (int *)HcGetAutoChCtrl(param_1);
  bVar1 = **(byte **)(param_2 + 4);
  uVar4 = APAutoSelectChannel(param_1,iVar2,1,*(undefined1 *)(*piVar3 + 0x510));
  if (DebugLevel < 3) {
    if (iVar2 == 0) goto LAB_000c4734;
LAB_000c4728:
    iVar5 = DebugLevel;
    *(char *)(iVar2 + 0x1a) = (char)uVar4;
  }
  else {
    printk("cmd> Re-scan channel!\n");
    iVar5 = DebugLevel;
    if (iVar2 != 0) goto LAB_000c4728;
  }
  if (2 < iVar5) {
    printk("cmd> Switch to %d!\n",uVar4);
  }
LAB_000c4734:
  APStop(param_1,"======== Badnode detector =============\nvow_bn_en = <0/1> 0:dieable, 1:enable\nvow_bn_mon_period = <period> ms\nvow_bn_fallback_th = <count>\nvow_bn_per_th = <TX PER>\n======== Airtime counter test =============\nvow_counter_test = <0/1> 0:dieable, 1:enable\nvow_counter_test_period = <period> ms\nvow_counter_test_band = <band>\nvow_counter_test_avgcnt = <average num> sec\nvow_counter_test_target = <wlanidx>\n======== DVT =============\nvow_dvt_en = <0/1> 0:dieable, 1:enable\nvow_monitor_sta = <STA num>\nvow_show_sta = <STA num>\nvow_monitor_bss = <BSS num>\nvow_monitor_mbss = <MBSS num>\nvow_show_mbss = <MBSS num>\nvow_avg_num = <average num> sec\n======== RED ===========\nvow_set_red_en = <0/1> 0:disable, 1:enable\nvow_set_red_show_sta = <STA num>\nvow_set_red_tar_delay = <tarDelay> us\n======== WATF ===========\nvow_watf_en = <0/1> 0:disable, 1:enable\nvow_watf_q = <level>-<quantum> unit 256us\nvow_watf_add_entry = <level>-<Addr>\nvow_watf_del_entry = <Addr>\n"
                 + (uint)bVar1 * 0x5834 + param_1 + 0xe0,1);
  APStartUp(param_1,"======== Badnode detector =============\nvow_bn_en = <0/1> 0:dieable, 1:enable\nvow_bn_mon_period = <period> ms\nvow_bn_fallback_th = <count>\nvow_bn_per_th = <TX PER>\n======== Airtime counter test =============\nvow_counter_test = <0/1> 0:dieable, 1:enable\nvow_counter_test_period = <period> ms\nvow_counter_test_band = <band>\nvow_counter_test_avgcnt = <average num> sec\nvow_counter_test_target = <wlanidx>\n======== DVT =============\nvow_dvt_en = <0/1> 0:dieable, 1:enable\nvow_monitor_sta = <STA num>\nvow_show_sta = <STA num>\nvow_monitor_bss = <BSS num>\nvow_monitor_mbss = <MBSS num>\nvow_show_mbss = <MBSS num>\nvow_avg_num = <average num> sec\n======== RED ===========\nvow_set_red_en = <0/1> 0:disable, 1:enable\nvow_set_red_show_sta = <STA num>\nvow_set_red_tar_delay = <tarDelay> us\n======== WATF ===========\nvow_watf_en = <0/1> 0:disable, 1:enable\nvow_watf_q = <level>-<quantum> unit 256us\nvow_watf_add_entry = <level>-<Addr>\nvow_watf_del_entry = <Addr>\n"
                    + (uint)bVar1 * 0x5834 + param_1 + 0xe0,1);
  QBSS_LoadAlarmResume(param_1);
  return 0;
}

