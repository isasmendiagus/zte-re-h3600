// module: mt7915.ko
// function: WscApShowPeerList @ 0x1ee5cc
// size: 304 bytes
//

undefined4 WscApShowPeerList(int param_1)

{
  int *piVar1;
  uint uVar2;
  int iVar3;
  
  if ("======== Badnode detector =============\nvow_bn_en = <0/1> 0:dieable, 1:enable\nvow_bn_mon_period = <period> ms\nvow_bn_fallback_th = <count>\nvow_bn_per_th = <TX PER>\n======== Airtime counter test =============\nvow_counter_test = <0/1> 0:dieable, 1:enable\nvow_counter_test_period = <period> ms\nvow_counter_test_band = <band>\nvow_counter_test_avgcnt = <average num> sec\nvow_counter_test_target = <wlanidx>\n======== DVT =============\nvow_dvt_en = <0/1> 0:dieable, 1:enable\nvow_monitor_sta = <STA num>\nvow_show_sta = <STA num>\nvow_monitor_bss = <BSS num>\nvow_monitor_mbss = <MBSS num>\nvow_show_mbss = <MBSS num>\nvow_avg_num = <average num> sec\n======== RED ===========\nvow_set_red_en = <0/1> 0:disable, 1:enable\nvow_set_red_show_sta = <STA num>\nvow_set_red_tar_delay = <tarDelay> us\n======== WATF ===========\nvow_watf_en = <0/1> 0:disable, 1:enable\nvow_watf_q = <level>-<quantum> unit 256us\nvow_watf_add_entry = <level>-<Addr>\nvow_watf_del_entry = <Addr>\n"
      [param_1 + 0xda] != '\0') {
    uVar2 = 0;
    do {
      iVar3 = param_1 + uVar2 * 0x5834;
      if ("!!! Link UP, ignore this set::OID_802_11_BSSID_LIST_SCAN\n"[iVar3 + 0x1c] != '\0') {
        WscMaintainPeerList(param_1,"4/home/ws/zx279128s/packages/function/wlan/mtk/drivers/MT7915_V7.0.1.0/mt_wifi_ap/../mt_wifi/embedded/fsm/ap_mgmt_cntl.c:%d assert pAdfailed\n"
                                    + iVar3 + 0x2b);
        _raw_spin_lock_bh("!!! Link UP, ignore this set::OID_802_11_BSSID_LIST_SCAN\n" +
                          iVar3 + 0x10);
        for (piVar1 = *(int **)("!!! Link UP, ignore this set::OID_802_11_BSSID_LIST_SCAN\n" +
                               iVar3 + 0x14); piVar1 != (int *)0x0; piVar1 = (int *)*piVar1) {
          if (0 < DebugLevel) {
            printk("MAC:%02x:%02x:%02x:%02x:%02x:%02x\tReveive Time:%lu\n",
                   *(undefined1 *)(piVar1 + 2),*(undefined1 *)((int)piVar1 + 9),
                   *(undefined1 *)((int)piVar1 + 10),*(undefined1 *)((int)piVar1 + 0xb),
                   *(undefined1 *)(piVar1 + 3),*(undefined1 *)((int)piVar1 + 0xd),piVar1[1]);
          }
        }
        _raw_spin_unlock_bh("!!! Link UP, ignore this set::OID_802_11_BSSID_LIST_SCAN\n" +
                            iVar3 + 0x10);
      }
      if (0 < DebugLevel) {
        printk(&_LC13);
      }
      uVar2 = uVar2 + 1 & 0xff;
    } while (uVar2 < (byte)"======== Badnode detector =============\nvow_bn_en = <0/1> 0:dieable, 1:enable\nvow_bn_mon_period = <period> ms\nvow_bn_fallback_th = <count>\nvow_bn_per_th = <TX PER>\n======== Airtime counter test =============\nvow_counter_test = <0/1> 0:dieable, 1:enable\nvow_counter_test_period = <period> ms\nvow_counter_test_band = <band>\nvow_counter_test_avgcnt = <average num> sec\nvow_counter_test_target = <wlanidx>\n======== DVT =============\nvow_dvt_en = <0/1> 0:dieable, 1:enable\nvow_monitor_sta = <STA num>\nvow_show_sta = <STA num>\nvow_monitor_bss = <BSS num>\nvow_monitor_mbss = <MBSS num>\nvow_show_mbss = <MBSS num>\nvow_avg_num = <average num> sec\n======== RED ===========\nvow_set_red_en = <0/1> 0:disable, 1:enable\nvow_set_red_show_sta = <STA num>\nvow_set_red_tar_delay = <tarDelay> us\n======== WATF ===========\nvow_watf_en = <0/1> 0:disable, 1:enable\nvow_watf_q = <level>-<quantum> unit 256us\nvow_watf_add_entry = <level>-<Addr>\nvow_watf_del_entry = <Addr>\n"
                           [param_1 + 0xda]);
  }
  return 1;
}

