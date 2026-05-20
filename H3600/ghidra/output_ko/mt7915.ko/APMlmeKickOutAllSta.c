// module: mt7915.ko
// function: APMlmeKickOutAllSta @ 0x519ec
// size: 492 bytes
//

void APMlmeKickOutAllSta(int param_1,uint param_2,undefined2 param_3)

{
  int iVar1;
  undefined2 local_6a [2];
  undefined1 local_66;
  undefined1 local_65;
  int local_64;
  int local_60;
  int local_5c;
  undefined4 local_56;
  undefined2 local_52;
  undefined1 auStack_50 [16];
  byte local_40;
  byte local_3f;
  undefined4 local_3c;
  undefined2 local_38;
  undefined4 local_36;
  undefined2 local_32;
  undefined4 local_30;
  undefined2 local_2c;
  
  local_56 = 0xffffffff;
  local_52 = 0xffff;
  local_64 = 0;
  local_60 = 0;
  if ((param_2 * 0x5834 + param_1 != -0x2b7654 &&
       param_2 < (byte)"======== Badnode detector =============\nvow_bn_en = <0/1> 0:dieable, 1:enable\nvow_bn_mon_period = <period> ms\nvow_bn_fallback_th = <count>\nvow_bn_per_th = <TX PER>\n======== Airtime counter test =============\nvow_counter_test = <0/1> 0:dieable, 1:enable\nvow_counter_test_period = <period> ms\nvow_counter_test_band = <band>\nvow_counter_test_avgcnt = <average num> sec\nvow_counter_test_target = <wlanidx>\n======== DVT =============\nvow_dvt_en = <0/1> 0:dieable, 1:enable\nvow_monitor_sta = <STA num>\nvow_show_sta = <STA num>\nvow_monitor_bss = <BSS num>\nvow_monitor_mbss = <MBSS num>\nvow_show_mbss = <MBSS num>\nvow_avg_num = <average num> sec\n======== RED ===========\nvow_set_red_en = <0/1> 0:disable, 1:enable\nvow_set_red_show_sta = <STA num>\nvow_set_red_tar_delay = <tarDelay> us\n======== WATF ===========\nvow_watf_en = <0/1> 0:disable, 1:enable\nvow_watf_q = <level>-<quantum> unit 256us\nvow_watf_add_entry = <level>-<Addr>\nvow_watf_del_entry = <Addr>\n"
                       [param_1 + 0xda]) &&
     (local_6a[0] = param_3, iVar1 = os_alloc_mem(param_1,&local_64,0x900), iVar1 == 0)) {
    if (-1 < DebugLevel) {
      printk("Send DISASSOC Broadcast frame(%d) with ra%d\n",local_6a[0],param_2);
    }
    __memzero(&local_40,0x18);
    iVar1 = param_2 * 0x5834 + param_1;
    local_36 = *(undefined4 *)
                (
                "======== Badnode detector =============\nvow_bn_en = <0/1> 0:dieable, 1:enable\nvow_bn_mon_period = <period> ms\nvow_bn_fallback_th = <count>\nvow_bn_per_th = <TX PER>\n======== Airtime counter test =============\nvow_counter_test = <0/1> 0:dieable, 1:enable\nvow_counter_test_period = <period> ms\nvow_counter_test_band = <band>\nvow_counter_test_avgcnt = <average num> sec\nvow_counter_test_target = <wlanidx>\n======== DVT =============\nvow_dvt_en = <0/1> 0:dieable, 1:enable\nvow_monitor_sta = <STA num>\nvow_show_sta = <STA num>\nvow_monitor_bss = <BSS num>\nvow_monitor_mbss = <MBSS num>\nvow_show_mbss = <MBSS num>\nvow_avg_num = <average num> sec\n======== RED ===========\nvow_set_red_en = <0/1> 0:disable, 1:enable\nvow_set_red_show_sta = <STA num>\nvow_set_red_tar_delay = <tarDelay> us\n======== WATF ===========\nvow_watf_en = <0/1> 0:disable, 1:enable\nvow_watf_q = <level>-<quantum> unit 256us\nvow_watf_add_entry = <level>-<Addr>\nvow_watf_del_entry = <Addr>\n"
                + iVar1 + 0x101);
    local_32 = *(undefined2 *)
                (
                "======== Badnode detector =============\nvow_bn_en = <0/1> 0:dieable, 1:enable\nvow_bn_mon_period = <period> ms\nvow_bn_fallback_th = <count>\nvow_bn_per_th = <TX PER>\n======== Airtime counter test =============\nvow_counter_test = <0/1> 0:dieable, 1:enable\nvow_counter_test_period = <period> ms\nvow_counter_test_band = <band>\nvow_counter_test_avgcnt = <average num> sec\nvow_counter_test_target = <wlanidx>\n======== DVT =============\nvow_dvt_en = <0/1> 0:dieable, 1:enable\nvow_monitor_sta = <STA num>\nvow_show_sta = <STA num>\nvow_monitor_bss = <BSS num>\nvow_monitor_mbss = <MBSS num>\nvow_show_mbss = <MBSS num>\nvow_avg_num = <average num> sec\n======== RED ===========\nvow_set_red_en = <0/1> 0:disable, 1:enable\nvow_set_red_show_sta = <STA num>\nvow_set_red_tar_delay = <tarDelay> us\n======== WATF ===========\nvow_watf_en = <0/1> 0:disable, 1:enable\nvow_watf_q = <level>-<quantum> unit 256us\nvow_watf_add_entry = <level>-<Addr>\nvow_watf_del_entry = <Addr>\n"
                + iVar1 + 0x105);
    local_3c = local_56;
    local_3f = local_3f & 0xbe;
    local_40 = local_40 & 3 | 0xa0;
    local_38 = local_52;
    local_30 = local_36;
    local_2c = local_32;
    MakeOutgoingFrame(local_64,&local_60,0x18,&local_40,2,local_6a,0xffffffff);
    if ("Group%d airtime token: max %d(0x%08X), min %d(0x%08X)\n"[iVar1 + 4] == '\x01') {
      local_65 = 0x10;
      local_66 = 0x4c;
      MakeOutgoingFrame(local_64 + local_60,&local_5c,1,&local_66,1,&local_65,0x10,auStack_50,
                        0xffffffff);
      local_60 = local_5c + local_60;
      if (1 < DebugLevel) {
        printk("[PMF]: This is a Broadcast Robust management frame, Add 0x4C(76) EID\n");
      }
    }
    MiniportMMRequest(param_1,0,local_64,local_60);
    os_free_mem(local_64);
  }
  return;
}

