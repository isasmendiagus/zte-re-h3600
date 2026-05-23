// module: mt7915.ko
// function: WscSendEapFail @ 0x1e3dcc
// size: 684 bytes
//

void WscSendEapFail(int param_1,int param_2,int param_3)

{
  byte bVar1;
  char cVar2;
  int iVar3;
  int local_4c;
  int local_48;
  undefined4 local_44;
  undefined1 local_40;
  undefined1 local_3f;
  undefined2 local_3e;
  undefined1 local_3b;
  undefined1 local_3a;
  undefined1 local_39;
  undefined1 local_38;
  undefined4 local_36;
  undefined2 local_32;
  undefined4 local_30;
  undefined2 local_2c;
  undefined2 local_2a;
  
  local_48 = 0;
  local_44 = 0;
  bVar1 = *(byte *)(param_2 + 0x1c54);
  __memzero(&local_36,0xe);
  if (2 < DebugLevel) {
    printk("-----> WscSendEapFail\n");
  }
  if (*(char *)(param_1 + 0x286285) == '\x01') {
    iVar3 = (bVar1 & 0xf) * 0x5834 + param_1;
    local_4c = 0;
    local_36 = *(undefined4 *)(param_2 + 0x1c55);
    local_30 = *(undefined4 *)
                (
                "======== Badnode detector =============\nvow_bn_en = <0/1> 0:dieable, 1:enable\nvow_bn_mon_period = <period> ms\nvow_bn_fallback_th = <count>\nvow_bn_per_th = <TX PER>\n======== Airtime counter test =============\nvow_counter_test = <0/1> 0:dieable, 1:enable\nvow_counter_test_period = <period> ms\nvow_counter_test_band = <band>\nvow_counter_test_avgcnt = <average num> sec\nvow_counter_test_target = <wlanidx>\n======== DVT =============\nvow_dvt_en = <0/1> 0:dieable, 1:enable\nvow_monitor_sta = <STA num>\nvow_show_sta = <STA num>\nvow_monitor_bss = <BSS num>\nvow_monitor_mbss = <MBSS num>\nvow_show_mbss = <MBSS num>\nvow_avg_num = <average num> sec\n======== RED ===========\nvow_set_red_en = <0/1> 0:disable, 1:enable\nvow_set_red_show_sta = <STA num>\nvow_set_red_tar_delay = <tarDelay> us\n======== WATF ===========\nvow_watf_en = <0/1> 0:disable, 1:enable\nvow_watf_q = <level>-<quantum> unit 256us\nvow_watf_add_entry = <level>-<Addr>\nvow_watf_del_entry = <Addr>\n"
                + iVar3 + 0x101);
    local_32 = *(undefined2 *)(param_2 + 0x1c59);
    local_2a = EAPOL;
    local_2c = *(undefined2 *)
                (
                "======== Badnode detector =============\nvow_bn_en = <0/1> 0:dieable, 1:enable\nvow_bn_mon_period = <period> ms\nvow_bn_fallback_th = <count>\nvow_bn_per_th = <TX PER>\n======== Airtime counter test =============\nvow_counter_test = <0/1> 0:dieable, 1:enable\nvow_counter_test_period = <period> ms\nvow_counter_test_band = <band>\nvow_counter_test_avgcnt = <average num> sec\nvow_counter_test_target = <wlanidx>\n======== DVT =============\nvow_dvt_en = <0/1> 0:dieable, 1:enable\nvow_monitor_sta = <STA num>\nvow_show_sta = <STA num>\nvow_monitor_bss = <BSS num>\nvow_monitor_mbss = <MBSS num>\nvow_show_mbss = <MBSS num>\nvow_avg_num = <average num> sec\n======== RED ===========\nvow_set_red_en = <0/1> 0:disable, 1:enable\nvow_set_red_show_sta = <STA num>\nvow_set_red_tar_delay = <tarDelay> us\n======== WATF ===========\nvow_watf_en = <0/1> 0:disable, 1:enable\nvow_watf_q = <level>-<quantum> unit 256us\nvow_watf_add_entry = <level>-<Addr>\nvow_watf_del_entry = <Addr>\n"
                + iVar3 + 0x105);
  }
  else if (*(char *)(param_1 + 0x286285) == '\0') {
    local_36 = *(undefined4 *)(param_2 + 0x1c55);
    local_30 = *(undefined4 *)(&DAT_0036db73 + param_1);
    local_32 = *(undefined2 *)(param_2 + 0x1c59);
    local_4c = 2;
    local_2c = *(undefined2 *)(&DAT_0036db77 + param_1);
    local_2a = EAPOL;
  }
  else {
    local_4c = 0xff;
  }
  __memzero(&local_40);
  iVar3 = 0;
  local_40 = 1;
  local_3f = 0;
  local_3e = 0x400;
  __memzero(&local_3b,5);
  local_3a = *(undefined1 *)(param_2 + 0x1c50);
  local_39 = 0;
  local_3b = 4;
  local_38 = 4;
  os_alloc_mem(0,&local_48,0x800);
  if (local_48 != 0) {
    local_44 = 0;
    MakeOutgoingFrame(local_48,&local_44,4,&local_40,4,&local_3b,0xffffffff);
    cVar2 = *(char *)(param_1 + 0x286285);
    if (cVar2 == '\x01') {
      iVar3 = MacTableLookup(param_1,param_2 + 0x1c55);
      cVar2 = *(char *)(param_1 + 0x286285);
    }
    if (cVar2 == '\0') {
      iVar3 = MacTableLookup2(param_1,param_2 + 0x1c55);
    }
    RTMPToWirelessSta(param_1,iVar3,&local_36,0xe,local_48,local_44,1);
    if (local_48 != 0) {
      os_free_mem();
    }
    if (iVar3 == 0 || param_3 == 0) {
      if (iVar3 == 0) {
        __memzero(param_2 + 0x1c55,6);
      }
    }
    else if (local_4c == 0) {
      __MlmeDeAuthAction(param_1,iVar3,3,1,"WscSendEapFail",0x1a68);
    }
    if (2 < DebugLevel) {
      printk("<----- WscSendEapFail\n");
    }
  }
  return;
}

