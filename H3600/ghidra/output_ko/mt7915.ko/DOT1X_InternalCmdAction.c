// module: mt7915.ko
// function: DOT1X_InternalCmdAction @ 0x164d8
// size: 648 bytes
//

undefined4 DOT1X_InternalCmdAction(int param_1,int param_2,undefined4 param_3)

{
  short sVar1;
  undefined2 uVar2;
  undefined4 uVar3;
  int *__src;
  int iVar4;
  uint uVar5;
  ushort uVar6;
  undefined4 uVar7;
  void *local_34;
  undefined4 local_2f;
  undefined2 local_2b;
  undefined4 local_29;
  undefined4 local_25;
  undefined1 local_21;
  
  local_34 = (void *)0x0;
  local_29 = 0xc0007dd;
  local_25 = 0x43;
  local_21 = 0;
  os_alloc_mem(0,&local_34,0x1b);
  if (local_34 == (void *)0x0) {
    uVar7 = 0;
    if (-1 < DebugLevel) {
      printk("%s : FrameBuf Allocate memory fail!!!\n","DOT1X_InternalCmdAction");
    }
  }
  else {
    __memzero(local_34,0x1b);
    if (param_2 == 0) {
      __src = (int *)(
                     "======== Badnode detector =============\nvow_bn_en = <0/1> 0:dieable, 1:enable\nvow_bn_mon_period = <period> ms\nvow_bn_fallback_th = <count>\nvow_bn_per_th = <TX PER>\n======== Airtime counter test =============\nvow_counter_test = <0/1> 0:dieable, 1:enable\nvow_counter_test_period = <period> ms\nvow_counter_test_band = <band>\nvow_counter_test_avgcnt = <average num> sec\nvow_counter_test_target = <wlanidx>\n======== DVT =============\nvow_dvt_en = <0/1> 0:dieable, 1:enable\nvow_monitor_sta = <STA num>\nvow_show_sta = <STA num>\nvow_monitor_bss = <BSS num>\nvow_monitor_mbss = <MBSS num>\nvow_show_mbss = <MBSS num>\nvow_avg_num = <average num> sec\n======== RED ===========\nvow_set_red_en = <0/1> 0:disable, 1:enable\nvow_set_red_show_sta = <STA num>\nvow_set_red_tar_delay = <tarDelay> us\n======== WATF ===========\nvow_watf_en = <0/1> 0:disable, 1:enable\nvow_watf_q = <level>-<quantum> unit 256us\nvow_watf_add_entry = <level>-<Addr>\nvow_watf_del_entry = <Addr>\n"
                     + param_1 + 0x101);
      local_2b = *(undefined2 *)
                  (
                  "======== Badnode detector =============\nvow_bn_en = <0/1> 0:dieable, 1:enable\nvow_bn_mon_period = <period> ms\nvow_bn_fallback_th = <count>\nvow_bn_per_th = <TX PER>\n======== Airtime counter test =============\nvow_counter_test = <0/1> 0:dieable, 1:enable\nvow_counter_test_period = <period> ms\nvow_counter_test_band = <band>\nvow_counter_test_avgcnt = <average num> sec\nvow_counter_test_target = <wlanidx>\n======== DVT =============\nvow_dvt_en = <0/1> 0:dieable, 1:enable\nvow_monitor_sta = <STA num>\nvow_show_sta = <STA num>\nvow_monitor_bss = <BSS num>\nvow_monitor_mbss = <MBSS num>\nvow_show_mbss = <MBSS num>\nvow_avg_num = <average num> sec\n======== RED ===========\nvow_set_red_en = <0/1> 0:disable, 1:enable\nvow_set_red_show_sta = <STA num>\nvow_set_red_tar_delay = <tarDelay> us\n======== WATF ===========\nvow_watf_en = <0/1> 0:disable, 1:enable\nvow_watf_q = <level>-<quantum> unit 256us\nvow_watf_add_entry = <level>-<Addr>\nvow_watf_del_entry = <Addr>\n"
                  + param_1 + 0x105);
      local_2f = CONCAT31((int3)((uint)*__src >> 8),
                          ~((byte)~(byte)((uint)(*__src << 0x19) >> 0x18) >> 1));
      uVar5 = 0;
    }
    else {
      uVar5 = (uint)*(byte *)(param_2 + 0xe4);
      local_2f = *(undefined4 *)(param_2 + 0xec);
      local_2b = *(undefined2 *)(param_2 + 0xf0);
      __src = (int *)(
                     "======== Badnode detector =============\nvow_bn_en = <0/1> 0:dieable, 1:enable\nvow_bn_mon_period = <period> ms\nvow_bn_fallback_th = <count>\nvow_bn_per_th = <TX PER>\n======== Airtime counter test =============\nvow_counter_test = <0/1> 0:dieable, 1:enable\nvow_counter_test_period = <period> ms\nvow_counter_test_band = <band>\nvow_counter_test_avgcnt = <average num> sec\nvow_counter_test_target = <wlanidx>\n======== DVT =============\nvow_dvt_en = <0/1> 0:dieable, 1:enable\nvow_monitor_sta = <STA num>\nvow_show_sta = <STA num>\nvow_monitor_bss = <BSS num>\nvow_monitor_mbss = <MBSS num>\nvow_show_mbss = <MBSS num>\nvow_avg_num = <average num> sec\n======== RED ===========\nvow_set_red_en = <0/1> 0:disable, 1:enable\nvow_set_red_show_sta = <STA num>\nvow_set_red_tar_delay = <tarDelay> us\n======== WATF ===========\nvow_watf_en = <0/1> 0:disable, 1:enable\nvow_watf_q = <level>-<quantum> unit 256us\nvow_watf_add_entry = <level>-<Addr>\nvow_watf_del_entry = <Addr>\n"
                     + uVar5 * 0x5834 + param_1 + 0x101);
    }
    local_25._0_2_ = CONCAT11((char)param_3,(undefined1)local_25);
    iVar4 = uVar5 * 0x5834 + param_1;
    uVar6 = *(ushort *)("%s: target = %d\n" + iVar4 + 0x12);
    if (uVar6 == 0) {
      uVar7 = 0x17;
      memmove(local_34,__src,6);
      iVar4 = 0xe;
      *(undefined4 *)((int)local_34 + 6) = local_2f;
      *(undefined2 *)((int)local_34 + 10) = local_2b;
      *(undefined2 *)((int)local_34 + 0xc) = 0x8e88;
    }
    else {
      sVar1 = *(short *)("======== WATF Information ========\n" + iVar4);
      memmove(local_34,__src,6);
      uVar6 = uVar6 & 0xfff;
      uVar7 = 0x1b;
      *(undefined2 *)((int)local_34 + 10) = local_2b;
      *(undefined4 *)((int)local_34 + 6) = local_2f;
      *(undefined2 *)((int)local_34 + 0xc) = 0x8e88;
      uVar2 = TPID;
      iVar4 = 0x12;
      *(ushort *)((int)local_34 + 0xe) = (ushort)(uVar6 | sVar1 << 0xd) >> 8 | uVar6 << 8;
      *(undefined2 *)((int)local_34 + 0x10) = 0x8e88;
      *(undefined2 *)((int)local_34 + 0xc) = uVar2;
    }
    *(undefined4 *)((int)local_34 + iVar4) = local_29;
    *(undefined1 *)((int)local_34 + iVar4 + 8) = local_21;
    *(undefined4 *)((int)local_34 + iVar4 + 4) = local_25;
    uVar3 = get_netdev_from_bssid(param_1,uVar5);
    iVar4 = RTMPL2FrameTxAction(param_1,uVar3,announce_802_3_packet,uVar5,local_34,uVar7,
                                *(undefined1 *)(param_1 + 0x286285));
    if (iVar4 == 0) {
      os_free_mem(local_34);
      return 0;
    }
    if (2 < DebugLevel) {
      printk("%s done. (cmd=%d)\n","DOT1X_InternalCmdAction",param_3);
    }
    uVar7 = 1;
    os_free_mem(local_34);
  }
  return uVar7;
}

