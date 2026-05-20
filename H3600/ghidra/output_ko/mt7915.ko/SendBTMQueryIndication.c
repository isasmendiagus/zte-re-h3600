// module: mt7915.ko
// function: SendBTMQueryIndication @ 0x227490
// size: 108 bytes
//

void SendBTMQueryIndication(int param_1,byte *param_2,undefined4 param_3,undefined4 param_4)

{
  undefined4 uVar1;
  
  uVar1 = *(undefined4 *)
           (
           "======== Badnode detector =============\nvow_bn_en = <0/1> 0:dieable, 1:enable\nvow_bn_mon_period = <period> ms\nvow_bn_fallback_th = <count>\nvow_bn_per_th = <TX PER>\n======== Airtime counter test =============\nvow_counter_test = <0/1> 0:dieable, 1:enable\nvow_counter_test_period = <period> ms\nvow_counter_test_band = <band>\nvow_counter_test_avgcnt = <average num> sec\nvow_counter_test_target = <wlanidx>\n======== DVT =============\nvow_dvt_en = <0/1> 0:dieable, 1:enable\nvow_monitor_sta = <STA num>\nvow_show_sta = <STA num>\nvow_monitor_bss = <BSS num>\nvow_monitor_mbss = <MBSS num>\nvow_show_mbss = <MBSS num>\nvow_avg_num = <average num> sec\n======== RED ===========\nvow_set_red_en = <0/1> 0:disable, 1:enable\nvow_set_red_show_sta = <STA num>\nvow_set_red_tar_delay = <tarDelay> us\n======== WATF ===========\nvow_watf_en = <0/1> 0:disable, 1:enable\nvow_watf_q = <level>-<quantum> unit 256us\nvow_watf_add_entry = <level>-<Addr>\nvow_watf_del_entry = <Addr>\n"
           + (uint)*param_2 * 0x5834 + param_1 + 0xe0);
  printk(&_LC4,"SendBTMQueryIndication");
  wext_send_btm_query_event_newapi(uVar1,param_2 + 1,param_2 + 0xc,*(undefined2 *)(param_2 + 10));
  BTMStartWaitBTMReqTimer(param_1,param_2);
  BTMSetPeerCurrentState(param_1,param_2,2,param_4);
  return;
}

