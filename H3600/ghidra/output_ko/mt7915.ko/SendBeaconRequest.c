// module: mt7915.ko
// function: SendBeaconRequest @ 0xa42d4
// size: 444 bytes
//

void SendBeaconRequest(int param_1,int param_2)

{
  int iVar1;
  int iVar2;
  undefined4 local_64;
  undefined4 local_60;
  undefined1 local_5b;
  undefined1 local_5a;
  undefined1 local_59;
  undefined1 local_58;
  undefined1 local_57;
  undefined1 local_56;
  undefined1 local_55;
  undefined2 local_54;
  undefined2 local_52;
  undefined1 local_50;
  undefined4 local_4f;
  undefined2 local_4b;
  undefined1 local_49;
  undefined1 local_48;
  undefined1 local_47;
  undefined1 local_46;
  undefined1 auStack_45 [24];
  undefined1 local_2d;
  undefined1 local_2c;
  undefined1 local_2b;
  undefined1 local_2a;
  undefined1 local_29;
  
  local_64 = 0;
  iVar2 = param_1 + param_2 * 0x14c0;
  iVar1 = *(int *)(iVar2 + 0xa1d20);
  if (iVar1 != 2 && iVar1 != 0x40001) {
    iVar1 = os_alloc_mem(param_1,&local_64,0x900);
    if (iVar1 == 0) {
      iVar1 = param_1 + (uint)*(byte *)(iVar2 + 0xa1e05) * 0x5834;
      ActHeaderInit(param_1,auStack_45,param_1 + param_2 * 0x14c0 + 0xa1e0c,
                    "======== Badnode detector =============\nvow_bn_en = <0/1> 0:dieable, 1:enable\nvow_bn_mon_period = <period> ms\nvow_bn_fallback_th = <count>\nvow_bn_per_th = <TX PER>\n======== Airtime counter test =============\nvow_counter_test = <0/1> 0:dieable, 1:enable\nvow_counter_test_period = <period> ms\nvow_counter_test_band = <band>\nvow_counter_test_avgcnt = <average num> sec\nvow_counter_test_target = <wlanidx>\n======== DVT =============\nvow_dvt_en = <0/1> 0:dieable, 1:enable\nvow_monitor_sta = <STA num>\nvow_show_sta = <STA num>\nvow_monitor_bss = <BSS num>\nvow_monitor_mbss = <MBSS num>\nvow_show_mbss = <MBSS num>\nvow_avg_num = <average num> sec\n======== RED ===========\nvow_set_red_en = <0/1> 0:disable, 1:enable\nvow_set_red_show_sta = <STA num>\nvow_set_red_tar_delay = <tarDelay> us\n======== WATF ===========\nvow_watf_en = <0/1> 0:disable, 1:enable\nvow_watf_q = <level>-<quantum> unit 256us\nvow_watf_add_entry = <level>-<Addr>\nvow_watf_del_entry = <Addr>\n"
                    + iVar1 + 0xfb,
                    "======== Badnode detector =============\nvow_bn_en = <0/1> 0:dieable, 1:enable\nvow_bn_mon_period = <period> ms\nvow_bn_fallback_th = <count>\nvow_bn_per_th = <TX PER>\n======== Airtime counter test =============\nvow_counter_test = <0/1> 0:dieable, 1:enable\nvow_counter_test_period = <period> ms\nvow_counter_test_band = <band>\nvow_counter_test_avgcnt = <average num> sec\nvow_counter_test_target = <wlanidx>\n======== DVT =============\nvow_dvt_en = <0/1> 0:dieable, 1:enable\nvow_monitor_sta = <STA num>\nvow_show_sta = <STA num>\nvow_monitor_bss = <BSS num>\nvow_monitor_mbss = <MBSS num>\nvow_show_mbss = <MBSS num>\nvow_avg_num = <average num> sec\n======== RED ===========\nvow_set_red_en = <0/1> 0:disable, 1:enable\nvow_set_red_show_sta = <STA num>\nvow_set_red_tar_delay = <tarDelay> us\n======== WATF ===========\nvow_watf_en = <0/1> 0:disable, 1:enable\nvow_watf_q = <level>-<quantum> unit 256us\nvow_watf_add_entry = <level>-<Addr>\nvow_watf_del_entry = <Addr>\n"
                    + iVar1 + 0x101);
      local_55 = 0xff;
      local_2d = 5;
      local_57 = 5;
      local_2c = 0;
      local_2a = 0;
      local_29 = 0;
      local_54 = 0;
      local_48 = 0;
      local_47 = 0;
      local_46 = 0;
      local_59 = 0;
      local_58 = 0;
      local_4f = (undefined4)BROADCAST_ADDR;
      local_4b = BROADCAST_ADDR._4_2_;
      local_56 = 0x20;
      local_52 = 10;
      local_2b = 1;
      local_50 = 1;
      local_49 = 0xfe;
      local_5b = 0x26;
      local_5a = 0x14;
      MakeOutgoingFrame(local_64,&local_60,0x1d,auStack_45,5,&local_5b,0x11,&local_56,0xffffffff);
      MiniportMMRequest(param_1,1,local_64,local_60);
      os_free_mem(local_64);
      if (2 < DebugLevel) {
        printk("Radio - SendBeaconRequest\n");
      }
    }
    else if (-1 < DebugLevel) {
      printk("Radio - SendBeaconRequest() allocate memory failed\n");
    }
  }
  return;
}

