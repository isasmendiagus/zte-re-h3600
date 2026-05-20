// module: mt7915.ko
// function: rtmp_cfg_init @ 0x13cf88
// size: 208 bytes
//

undefined4 rtmp_cfg_init(int param_1)

{
  undefined2 uVar1;
  int iVar2;
  
  UserCfgInit();
  CfgInitHook(param_1);
  if ("rtmp_read_dot11v_mbssid_cfg_from_file"[param_1 + 0x1e] == '\0') {
    "rtmp_read_dot11v_mbssid_cfg_from_file"[param_1 + 0x1e] = -1;
    if (0 < DebugLevel) {
      printk("%s(): Invalid RfIcType, reset it first\n","rtmp_cfg_init");
    }
  }
  iVar2 = RTMPReadParametersHook(param_1);
  if (iVar2 != 0) {
    if (DebugLevel < 0) {
      return 0;
    }
    printk("RTMPReadParametersHook failed, Status[=0x%08x]\n");
    return 0;
  }
  uVar1 = bssid_num_to_max_indicator
                    ("======== Badnode detector =============\nvow_bn_en = <0/1> 0:dieable, 1:enable\nvow_bn_mon_period = <period> ms\nvow_bn_fallback_th = <count>\nvow_bn_per_th = <TX PER>\n======== Airtime counter test =============\nvow_counter_test = <0/1> 0:dieable, 1:enable\nvow_counter_test_period = <period> ms\nvow_counter_test_band = <band>\nvow_counter_test_avgcnt = <average num> sec\nvow_counter_test_target = <wlanidx>\n======== DVT =============\nvow_dvt_en = <0/1> 0:dieable, 1:enable\nvow_monitor_sta = <STA num>\nvow_show_sta = <STA num>\nvow_monitor_bss = <BSS num>\nvow_monitor_mbss = <MBSS num>\nvow_show_mbss = <MBSS num>\nvow_avg_num = <average num> sec\n======== RED ===========\nvow_set_red_en = <0/1> 0:disable, 1:enable\nvow_set_red_show_sta = <STA num>\nvow_set_red_tar_delay = <tarDelay> us\n======== WATF ===========\nvow_watf_en = <0/1> 0:disable, 1:enable\nvow_watf_q = <level>-<quantum> unit 256us\nvow_watf_add_entry = <level>-<Addr>\nvow_watf_del_entry = <Addr>\n"
                     [param_1 + 0xda]);
  entrytb_aid_bitmap_reserve(param_1 + 0x28594c,uVar1);
  HcSetMaxStaNum(param_1);
  return 1;
}

