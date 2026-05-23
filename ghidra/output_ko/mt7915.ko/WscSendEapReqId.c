// module: mt7915.ko
// function: WscSendEapReqId @ 0x1e1930
// size: 652 bytes
//

void WscSendEapReqId(int param_1,int param_2,int param_3)

{
  byte bVar1;
  uint uVar2;
  int iVar3;
  int iVar4;
  int local_48;
  undefined4 local_44;
  undefined1 local_3e;
  undefined1 local_3d;
  undefined2 local_3c;
  undefined1 local_39;
  char local_38;
  undefined1 local_37;
  undefined1 local_36;
  undefined1 local_35;
  char local_34 [4];
  undefined2 local_30;
  undefined4 local_2e;
  undefined2 local_2a;
  undefined4 local_28;
  undefined2 local_24;
  undefined2 local_22;
  
  builtin_strncpy(local_34,"hell",4);
  local_30 = 0x6f;
  local_48 = 0;
  local_44 = 0;
  __memzero(&local_2e,0xe);
  if (2 < DebugLevel) {
    printk("-----> WscSendEapReqId\n");
  }
  if (param_3 == 0) {
    bVar1 = *(byte *)(param_2 + 0xe4);
    uVar2 = hc_get_chip_bcn_max_num(*(undefined4 *)(param_1 + 0xa797a0));
    if ((uVar2 <= bVar1) || (0x1f < *(byte *)(param_2 + 0xe4))) goto LAB_001e1994;
    iVar3 = (uint)*(byte *)(param_2 + 0xe4) * 0x5834 + param_1;
    local_2e = *(undefined4 *)(param_2 + 0xec);
    iVar4 = *(int *)(param_2 + 8);
    local_28 = *(undefined4 *)
                (
                "======== Badnode detector =============\nvow_bn_en = <0/1> 0:dieable, 1:enable\nvow_bn_mon_period = <period> ms\nvow_bn_fallback_th = <count>\nvow_bn_per_th = <TX PER>\n======== Airtime counter test =============\nvow_counter_test = <0/1> 0:dieable, 1:enable\nvow_counter_test_period = <period> ms\nvow_counter_test_band = <band>\nvow_counter_test_avgcnt = <average num> sec\nvow_counter_test_target = <wlanidx>\n======== DVT =============\nvow_dvt_en = <0/1> 0:dieable, 1:enable\nvow_monitor_sta = <STA num>\nvow_show_sta = <STA num>\nvow_monitor_bss = <BSS num>\nvow_monitor_mbss = <MBSS num>\nvow_show_mbss = <MBSS num>\nvow_avg_num = <average num> sec\n======== RED ===========\nvow_set_red_en = <0/1> 0:disable, 1:enable\nvow_set_red_show_sta = <STA num>\nvow_set_red_tar_delay = <tarDelay> us\n======== WATF ===========\nvow_watf_en = <0/1> 0:disable, 1:enable\nvow_watf_q = <level>-<quantum> unit 256us\nvow_watf_add_entry = <level>-<Addr>\nvow_watf_del_entry = <Addr>\n"
                + iVar3 + 0x101);
    local_2a = *(undefined2 *)(param_2 + 0xf0);
    local_24 = *(undefined2 *)
                (
                "======== Badnode detector =============\nvow_bn_en = <0/1> 0:dieable, 1:enable\nvow_bn_mon_period = <period> ms\nvow_bn_fallback_th = <count>\nvow_bn_per_th = <TX PER>\n======== Airtime counter test =============\nvow_counter_test = <0/1> 0:dieable, 1:enable\nvow_counter_test_period = <period> ms\nvow_counter_test_band = <band>\nvow_counter_test_avgcnt = <average num> sec\nvow_counter_test_target = <wlanidx>\n======== DVT =============\nvow_dvt_en = <0/1> 0:dieable, 1:enable\nvow_monitor_sta = <STA num>\nvow_show_sta = <STA num>\nvow_monitor_bss = <BSS num>\nvow_monitor_mbss = <MBSS num>\nvow_show_mbss = <MBSS num>\nvow_avg_num = <average num> sec\n======== RED ===========\nvow_set_red_en = <0/1> 0:disable, 1:enable\nvow_set_red_show_sta = <STA num>\nvow_set_red_tar_delay = <tarDelay> us\n======== WATF ===========\nvow_watf_en = <0/1> 0:disable, 1:enable\nvow_watf_q = <level>-<quantum> unit 256us\nvow_watf_add_entry = <level>-<Addr>\nvow_watf_del_entry = <Addr>\n"
                + iVar3 + 0x105);
  }
  else {
    if (param_3 != 2) goto LAB_001e1994;
    local_2e = *(undefined4 *)(param_2 + 0xec);
    iVar4 = *(int *)(param_2 + 8);
    local_28 = *(undefined4 *)(&DAT_0036db73 + param_1);
    local_24 = *(undefined2 *)(&DAT_0036db77 + param_1);
    local_2a = *(undefined2 *)(param_2 + 0xf0);
  }
  local_22 = EAPOL;
  if (iVar4 != -0x12e4) {
    __memzero(&local_3e,4);
    local_3e = 1;
    local_3d = 0;
    local_3c = 0xa00;
    __memzero(&local_39,5);
    uVar2 = RandomByte(param_1);
    local_38 = (char)uVar2;
    if (*(byte *)(iVar4 + 0x2f34) == uVar2) {
      local_38 = local_38 + '\x01';
    }
    *(char *)(iVar4 + 0x2f34) = local_38;
    local_37 = 0;
    local_39 = 1;
    local_35 = 1;
    local_36 = 10;
    os_alloc_mem(0,&local_48,0x800);
    if (local_48 == 0) {
      return;
    }
    local_44 = 0;
    MakeOutgoingFrame(local_48,&local_44,4,&local_3e,5,&local_39,5,local_34,0xffffffff);
    RTMPToWirelessSta(param_1,param_2,&local_2e,0xe,local_48,local_44,1);
    *(undefined1 *)(iVar4 + 0x2f37) = 0;
    if (local_48 != 0) {
      os_free_mem();
    }
    if (DebugLevel < 3) {
      return;
    }
    printk("<----- WscSendEapReqId\n");
    return;
  }
LAB_001e1994:
  if (-1 < DebugLevel) {
    printk("pWpsCtrl == NULL!\n");
  }
  return;
}

