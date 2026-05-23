// module: mt7915.ko
// function: BcnRepTimeout @ 0x223184
// size: 264 bytes
//

void BcnRepTimeout(int param_1,int param_2)

{
  undefined1 uVar1;
  int iVar2;
  undefined1 uStack_19;
  
  uVar1 = *(undefined1 *)(param_2 + 1);
  if (2 < DebugLevel) {
    printk("%s StaMac(%02x:%02x:%02x:%02x:%02x:%02x), MeasureReqToken=%d\n","BcnRepTimeout",
           *(undefined1 *)(param_2 + 2),*(undefined1 *)(param_2 + 3),*(undefined1 *)(param_2 + 4),
           *(undefined1 *)(param_2 + 5),*(undefined1 *)(param_2 + 6),*(undefined1 *)(param_2 + 7),
           uVar1);
  }
  iVar2 = MeasureReqLookUp(param_1,uVar1);
  if (iVar2 == 0) {
    if (-1 < DebugLevel) {
      printk("%s Bcnreq entry not founded\n","BcnRepTimeout");
    }
  }
  else {
    RTMPReleaseTimer(iVar2 + 0x50,&uStack_19);
    MeasureReqDelete(param_1,uVar1);
    if (*(int *)(
                "======== Badnode detector =============\nvow_bn_en = <0/1> 0:dieable, 1:enable\nvow_bn_mon_period = <period> ms\nvow_bn_fallback_th = <count>\nvow_bn_per_th = <TX PER>\n======== Airtime counter test =============\nvow_counter_test = <0/1> 0:dieable, 1:enable\nvow_counter_test_period = <period> ms\nvow_counter_test_band = <band>\nvow_counter_test_avgcnt = <average num> sec\nvow_counter_test_target = <wlanidx>\n======== DVT =============\nvow_dvt_en = <0/1> 0:dieable, 1:enable\nvow_monitor_sta = <STA num>\nvow_show_sta = <STA num>\nvow_monitor_bss = <BSS num>\nvow_monitor_mbss = <MBSS num>\nvow_show_mbss = <MBSS num>\nvow_avg_num = <average num> sec\n======== RED ===========\nvow_set_red_en = <0/1> 0:disable, 1:enable\nvow_set_red_show_sta = <STA num>\nvow_set_red_tar_delay = <tarDelay> us\n======== WATF ===========\nvow_watf_en = <0/1> 0:disable, 1:enable\nvow_watf_q = <level>-<quantum> unit 256us\nvow_watf_add_entry = <level>-<Addr>\nvow_watf_del_entry = <Addr>\n"
                + (uint)*(byte *)(iVar2 + 0x4e) * 0x5834 + param_1 + 0xe0) == 0) {
      if (-1 < DebugLevel) {
        printk("no valid NetDev! IfIndex=%d\n");
      }
    }
    else {
      wext_send_bcn_rsp_event
                (*(int *)(
                         "======== Badnode detector =============\nvow_bn_en = <0/1> 0:dieable, 1:enable\nvow_bn_mon_period = <period> ms\nvow_bn_fallback_th = <count>\nvow_bn_per_th = <TX PER>\n======== Airtime counter test =============\nvow_counter_test = <0/1> 0:dieable, 1:enable\nvow_counter_test_period = <period> ms\nvow_counter_test_band = <band>\nvow_counter_test_avgcnt = <average num> sec\nvow_counter_test_target = <wlanidx>\n======== DVT =============\nvow_dvt_en = <0/1> 0:dieable, 1:enable\nvow_monitor_sta = <STA num>\nvow_show_sta = <STA num>\nvow_monitor_bss = <BSS num>\nvow_monitor_mbss = <MBSS num>\nvow_show_mbss = <MBSS num>\nvow_avg_num = <average num> sec\n======== RED ===========\nvow_set_red_en = <0/1> 0:disable, 1:enable\nvow_set_red_show_sta = <STA num>\nvow_set_red_tar_delay = <tarDelay> us\n======== WATF ===========\nvow_watf_en = <0/1> 0:disable, 1:enable\nvow_watf_q = <level>-<quantum> unit 256us\nvow_watf_add_entry = <level>-<Addr>\nvow_watf_del_entry = <Addr>\n"
                         + (uint)*(byte *)(iVar2 + 0x4e) * 0x5834 + param_1 + 0xe0),param_2 + 2,
                 param_2 + 10,0,uVar1);
    }
  }
  return;
}

