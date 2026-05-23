// module: mt7915.ko
// function: ZTE_Bss_Report_Info @ 0x160a38
// size: 252 bytes
//

undefined4 ZTE_Bss_Report_Info(int *param_1,undefined4 param_2)

{
  char cVar1;
  undefined4 uVar2;
  int iVar3;
  uint uVar4;
  uint local_54;
  undefined4 local_50;
  undefined2 local_4c;
  undefined1 local_4a;
  ushort local_20;
  undefined1 local_1e;
  undefined1 local_18;
  
  uVar4 = *(uint *)(*param_1 + 0x3c);
  cVar1 = simple_strtol(param_2,0,10);
  if (cVar1 != '\x01') {
    return 1;
  }
  __memzero(&local_54,0x44);
  local_54 = uVar4 & 0xff;
  iVar3 = local_54 * 0x5834;
  local_50 = *(undefined4 *)
              ((int)param_1 +
              (int)(
                   "======== Badnode detector =============\nvow_bn_en = <0/1> 0:dieable, 1:enable\nvow_bn_mon_period = <period> ms\nvow_bn_fallback_th = <count>\nvow_bn_per_th = <TX PER>\n======== Airtime counter test =============\nvow_counter_test = <0/1> 0:dieable, 1:enable\nvow_counter_test_period = <period> ms\nvow_counter_test_band = <band>\nvow_counter_test_avgcnt = <average num> sec\nvow_counter_test_target = <wlanidx>\n======== DVT =============\nvow_dvt_en = <0/1> 0:dieable, 1:enable\nvow_monitor_sta = <STA num>\nvow_show_sta = <STA num>\nvow_monitor_bss = <BSS num>\nvow_monitor_mbss = <MBSS num>\nvow_show_mbss = <MBSS num>\nvow_avg_num = <average num> sec\n======== RED ===========\nvow_set_red_en = <0/1> 0:disable, 1:enable\nvow_set_red_show_sta = <STA num>\nvow_set_red_tar_delay = <tarDelay> us\n======== WATF ===========\nvow_watf_en = <0/1> 0:disable, 1:enable\nvow_watf_q = <level>-<quantum> unit 256us\nvow_watf_add_entry = <level>-<Addr>\nvow_watf_del_entry = <Addr>\n"
                   + iVar3 + 0x101));
  local_4a = *(undefined1 *)((int)param_1 + iVar3 + 0x2b7262);
  local_4c = *(undefined2 *)
              ((int)param_1 +
              (int)(
                   "======== Badnode detector =============\nvow_bn_en = <0/1> 0:dieable, 1:enable\nvow_bn_mon_period = <period> ms\nvow_bn_fallback_th = <count>\nvow_bn_per_th = <TX PER>\n======== Airtime counter test =============\nvow_counter_test = <0/1> 0:dieable, 1:enable\nvow_counter_test_period = <period> ms\nvow_counter_test_band = <band>\nvow_counter_test_avgcnt = <average num> sec\nvow_counter_test_target = <wlanidx>\n======== DVT =============\nvow_dvt_en = <0/1> 0:dieable, 1:enable\nvow_monitor_sta = <STA num>\nvow_show_sta = <STA num>\nvow_monitor_bss = <BSS num>\nvow_monitor_mbss = <MBSS num>\nvow_show_mbss = <MBSS num>\nvow_avg_num = <average num> sec\n======== RED ===========\nvow_set_red_en = <0/1> 0:disable, 1:enable\nvow_set_red_show_sta = <STA num>\nvow_set_red_tar_delay = <tarDelay> us\n======== WATF ===========\nvow_watf_en = <0/1> 0:disable, 1:enable\nvow_watf_q = <level>-<quantum> unit 256us\nvow_watf_add_entry = <level>-<Addr>\nvow_watf_del_entry = <Addr>\n"
                   + iVar3 + 0x105));
  local_20 = (ushort)*(byte *)((int)param_1 + iVar3 + 0x2bb2d7);
  uVar2 = HcGetBandByChannel(param_1,local_4a);
  local_1e = ZTE_Get_ChannelUtilization(param_1,uVar2);
  local_18 = ZTE_Get_ChannelInterfer(param_1);
  Kernel_ASEND("multiapd.map.slave",0xa2b9,&local_54,0x44,0,0);
  return 1;
}

