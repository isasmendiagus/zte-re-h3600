// module: mt7915.ko
// function: GenerateWpsPinCode @ 0xb7d60
// size: 264 bytes
//

int GenerateWpsPinCode(int param_1,int param_2,int param_3)

{
  int iVar1;
  uint uVar2;
  uint local_16;
  undefined2 local_12;
  
  __memzero(&local_16,6);
  if (*(char *)(param_1 + 0x286285) == '\x01') {
    if (param_2 == 0) {
      param_1 = param_3 * 0x5834 + param_1;
      local_16 = *(uint *)(
                          "======== Badnode detector =============\nvow_bn_en = <0/1> 0:dieable, 1:enable\nvow_bn_mon_period = <period> ms\nvow_bn_fallback_th = <count>\nvow_bn_per_th = <TX PER>\n======== Airtime counter test =============\nvow_counter_test = <0/1> 0:dieable, 1:enable\nvow_counter_test_period = <period> ms\nvow_counter_test_band = <band>\nvow_counter_test_avgcnt = <average num> sec\nvow_counter_test_target = <wlanidx>\n======== DVT =============\nvow_dvt_en = <0/1> 0:dieable, 1:enable\nvow_monitor_sta = <STA num>\nvow_show_sta = <STA num>\nvow_monitor_bss = <BSS num>\nvow_monitor_mbss = <MBSS num>\nvow_show_mbss = <MBSS num>\nvow_avg_num = <average num> sec\n======== RED ===========\nvow_set_red_en = <0/1> 0:disable, 1:enable\nvow_set_red_show_sta = <STA num>\nvow_set_red_tar_delay = <tarDelay> us\n======== WATF ===========\nvow_watf_en = <0/1> 0:disable, 1:enable\nvow_watf_q = <level>-<quantum> unit 256us\nvow_watf_add_entry = <level>-<Addr>\nvow_watf_del_entry = <Addr>\n"
                          + param_1 + 0xfb);
      local_12 = *(undefined2 *)
                  (
                  "======== Badnode detector =============\nvow_bn_en = <0/1> 0:dieable, 1:enable\nvow_bn_mon_period = <period> ms\nvow_bn_fallback_th = <count>\nvow_bn_per_th = <TX PER>\n======== Airtime counter test =============\nvow_counter_test = <0/1> 0:dieable, 1:enable\nvow_counter_test_period = <period> ms\nvow_counter_test_band = <band>\nvow_counter_test_avgcnt = <average num> sec\nvow_counter_test_target = <wlanidx>\n======== DVT =============\nvow_dvt_en = <0/1> 0:dieable, 1:enable\nvow_monitor_sta = <STA num>\nvow_show_sta = <STA num>\nvow_monitor_bss = <BSS num>\nvow_monitor_mbss = <MBSS num>\nvow_show_mbss = <MBSS num>\nvow_avg_num = <average num> sec\n======== RED ===========\nvow_set_red_en = <0/1> 0:disable, 1:enable\nvow_set_red_show_sta = <STA num>\nvow_set_red_tar_delay = <tarDelay> us\n======== WATF ===========\nvow_watf_en = <0/1> 0:disable, 1:enable\nvow_watf_q = <level>-<quantum> unit 256us\nvow_watf_add_entry = <level>-<Addr>\nvow_watf_del_entry = <Addr>\n"
                  + param_1 + 0xff);
    }
    else {
      param_1 = param_1 + param_3 * 0x2137b0;
      local_16 = *(uint *)(&DAT_0036db73 + param_1);
      local_12 = *(undefined2 *)(&DAT_0036db77 + param_1);
    }
  }
  else if (*(char *)(param_1 + 0x286285) == '\0') {
    local_16 = *(uint *)(&DAT_0036db73 + param_1);
    local_12 = *(undefined2 *)(&DAT_0036db77 + param_1);
  }
  uVar2 = ((uint)local_12._1_1_ + ((uint)(byte)local_12 + (local_16 & 0xff) * 0x100) * 0x100) %
          10000000;
  iVar1 = ComputeChecksum(uVar2);
  return iVar1 + uVar2 * 10;
}

