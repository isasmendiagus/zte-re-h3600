// module: mt7915.ko
// function: DOT1X_EapTriggerAction @ 0x16768
// size: 472 bytes
//

undefined4 DOT1X_EapTriggerAction(int param_1,int param_2)

{
  int iVar1;
  int iVar2;
  undefined4 uVar3;
  ushort uVar4;
  uint uVar5;
  undefined4 uVar6;
  undefined4 local_52;
  undefined2 local_4e;
  undefined4 local_4c;
  undefined2 local_48;
  undefined2 local_46;
  ushort local_44;
  undefined2 local_42;
  
  if (((*(uint *)(param_2 + 0x17c) & 0x10048) != 0) ||
     ("Airtime control --> %s(%d)\n"[param_1 + 0x18] == '\x01')) {
    __memzero(&local_52,0x12);
    uVar5 = (uint)*(byte *)(param_2 + 0xe4);
    iVar2 = uVar5 * 0x5834;
    if (*(ushort *)("%s: target = %d\n" + param_1 + iVar2 + 0x12) == 0) {
      iVar1 = param_1 + iVar2 + 0x100;
      local_4c = *(undefined4 *)(param_2 + 0xec);
      uVar6 = 0x12;
      local_52 = *(undefined4 *)
                  (
                  "======== Badnode detector =============\nvow_bn_en = <0/1> 0:dieable, 1:enable\nvow_bn_mon_period = <period> ms\nvow_bn_fallback_th = <count>\nvow_bn_per_th = <TX PER>\n======== Airtime counter test =============\nvow_counter_test = <0/1> 0:dieable, 1:enable\nvow_counter_test_period = <period> ms\nvow_counter_test_band = <band>\nvow_counter_test_avgcnt = <average num> sec\nvow_counter_test_target = <wlanidx>\n======== DVT =============\nvow_dvt_en = <0/1> 0:dieable, 1:enable\nvow_monitor_sta = <STA num>\nvow_show_sta = <STA num>\nvow_monitor_bss = <BSS num>\nvow_monitor_mbss = <MBSS num>\nvow_show_mbss = <MBSS num>\nvow_avg_num = <average num> sec\n======== RED ===========\nvow_set_red_en = <0/1> 0:disable, 1:enable\nvow_set_red_show_sta = <STA num>\nvow_set_red_tar_delay = <tarDelay> us\n======== WATF ===========\nvow_watf_en = <0/1> 0:disable, 1:enable\nvow_watf_q = <level>-<quantum> unit 256us\nvow_watf_add_entry = <level>-<Addr>\nvow_watf_del_entry = <Addr>\n"
                  + iVar1 + 1);
      local_48 = *(undefined2 *)(param_2 + 0xf0);
      iVar2 = 0xe;
      local_4e = *(undefined2 *)
                  (
                  "======== Badnode detector =============\nvow_bn_en = <0/1> 0:dieable, 1:enable\nvow_bn_mon_period = <period> ms\nvow_bn_fallback_th = <count>\nvow_bn_per_th = <TX PER>\n======== Airtime counter test =============\nvow_counter_test = <0/1> 0:dieable, 1:enable\nvow_counter_test_period = <period> ms\nvow_counter_test_band = <band>\nvow_counter_test_avgcnt = <average num> sec\nvow_counter_test_target = <wlanidx>\n======== DVT =============\nvow_dvt_en = <0/1> 0:dieable, 1:enable\nvow_monitor_sta = <STA num>\nvow_show_sta = <STA num>\nvow_monitor_bss = <BSS num>\nvow_monitor_mbss = <MBSS num>\nvow_show_mbss = <MBSS num>\nvow_avg_num = <average num> sec\n======== RED ===========\nvow_set_red_en = <0/1> 0:disable, 1:enable\nvow_set_red_show_sta = <STA num>\nvow_set_red_tar_delay = <tarDelay> us\n======== WATF ===========\nvow_watf_en = <0/1> 0:disable, 1:enable\nvow_watf_q = <level>-<quantum> unit 256us\nvow_watf_add_entry = <level>-<Addr>\nvow_watf_del_entry = <Addr>\n"
                  + iVar1 + 5);
      local_46 = EAPOL;
    }
    else {
      iVar1 = param_1 + iVar2 + 0x100;
      local_4c = *(undefined4 *)(param_2 + 0xec);
      uVar4 = *(ushort *)("%s: target = %d\n" + param_1 + iVar2 + 0x12) & 0xfff;
      local_52 = *(undefined4 *)
                  (
                  "======== Badnode detector =============\nvow_bn_en = <0/1> 0:dieable, 1:enable\nvow_bn_mon_period = <period> ms\nvow_bn_fallback_th = <count>\nvow_bn_per_th = <TX PER>\n======== Airtime counter test =============\nvow_counter_test = <0/1> 0:dieable, 1:enable\nvow_counter_test_period = <period> ms\nvow_counter_test_band = <band>\nvow_counter_test_avgcnt = <average num> sec\nvow_counter_test_target = <wlanidx>\n======== DVT =============\nvow_dvt_en = <0/1> 0:dieable, 1:enable\nvow_monitor_sta = <STA num>\nvow_show_sta = <STA num>\nvow_monitor_bss = <BSS num>\nvow_monitor_mbss = <MBSS num>\nvow_show_mbss = <MBSS num>\nvow_avg_num = <average num> sec\n======== RED ===========\nvow_set_red_en = <0/1> 0:disable, 1:enable\nvow_set_red_show_sta = <STA num>\nvow_set_red_tar_delay = <tarDelay> us\n======== WATF ===========\nvow_watf_en = <0/1> 0:disable, 1:enable\nvow_watf_q = <level>-<quantum> unit 256us\nvow_watf_add_entry = <level>-<Addr>\nvow_watf_del_entry = <Addr>\n"
                  + iVar1 + 1);
      local_46 = TPID;
      local_4e = *(undefined2 *)
                  (
                  "======== Badnode detector =============\nvow_bn_en = <0/1> 0:dieable, 1:enable\nvow_bn_mon_period = <period> ms\nvow_bn_fallback_th = <count>\nvow_bn_per_th = <TX PER>\n======== Airtime counter test =============\nvow_counter_test = <0/1> 0:dieable, 1:enable\nvow_counter_test_period = <period> ms\nvow_counter_test_band = <band>\nvow_counter_test_avgcnt = <average num> sec\nvow_counter_test_target = <wlanidx>\n======== DVT =============\nvow_dvt_en = <0/1> 0:dieable, 1:enable\nvow_monitor_sta = <STA num>\nvow_show_sta = <STA num>\nvow_monitor_bss = <BSS num>\nvow_monitor_mbss = <MBSS num>\nvow_show_mbss = <MBSS num>\nvow_avg_num = <average num> sec\n======== RED ===========\nvow_set_red_en = <0/1> 0:disable, 1:enable\nvow_set_red_show_sta = <STA num>\nvow_set_red_tar_delay = <tarDelay> us\n======== WATF ===========\nvow_watf_en = <0/1> 0:disable, 1:enable\nvow_watf_q = <level>-<quantum> unit 256us\nvow_watf_add_entry = <level>-<Addr>\nvow_watf_del_entry = <Addr>\n"
                  + iVar1 + 5);
      local_42 = EAPOL;
      local_48 = *(undefined2 *)(param_2 + 0xf0);
      local_44 = (ushort)(uVar4 | *(short *)("======== WATF Information ========\n" +
                                            param_1 + iVar2) << 0xd) >> 8 | uVar4 << 8;
      uVar6 = 0x16;
      iVar2 = 0x12;
    }
    *(undefined4 *)((int)&local_52 + iVar2) = 0x101;
    uVar3 = get_netdev_from_bssid(param_1,uVar5);
    iVar2 = RTMPL2FrameTxAction(param_1,uVar3,announce_802_3_packet,uVar5,&local_52,uVar6,
                                *(undefined1 *)(param_1 + 0x286285));
    if (iVar2 == 0) {
      return 0;
    }
    if (2 < DebugLevel) {
      printk("Notify 8021.x daemon to trigger EAP-SM for this sta(%02x:%02x:%02x:%02x:%02x:%02x)\n",
             *(undefined1 *)(param_2 + 0xec),*(undefined1 *)(param_2 + 0xed),
             *(undefined1 *)(param_2 + 0xee),*(undefined1 *)(param_2 + 0xef),
             *(undefined1 *)(param_2 + 0xf0),*(undefined1 *)(param_2 + 0xf1));
    }
  }
  return 1;
}

