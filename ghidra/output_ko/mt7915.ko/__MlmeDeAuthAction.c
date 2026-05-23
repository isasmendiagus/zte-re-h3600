// module: mt7915.ko
// function: __MlmeDeAuthAction @ 0x1197e8
// size: 704 bytes
//

void __MlmeDeAuthAction(int param_1,char *param_2,undefined2 param_3,int param_4,undefined4 param_5,
                       undefined4 param_6)

{
  int iVar1;
  int iVar2;
  undefined4 uVar3;
  char cVar4;
  char *local_60;
  uint local_5c;
  undefined4 local_58;
  undefined2 local_4a [3];
  int local_44;
  int local_40;
  int local_3c;
  undefined1 uStack_38;
  byte local_37;
  
  local_44 = 0;
  local_40 = 0;
  if (param_2 != (char *)0x0) {
    local_4a[0] = param_3;
    iVar1 = GetStaCfgByWdev(param_1,*(undefined4 *)(param_2 + 8));
    iVar2 = os_alloc_mem(param_1,&local_44,0x900);
    if (iVar2 == 0) {
      if (2 < DebugLevel) {
        local_60 = (char *)(uint)(byte)param_2[0xf0];
        local_5c = (uint)(byte)param_2[0xf1];
        printk("Send DEAUTH frame with ReasonCode(%d) to %02x:%02x:%02x:%02x:%02x:%02x\n",
               local_4a[0],param_2[0xec],param_2[0xed],param_2[0xee],param_2[0xef]);
      }
      cVar4 = *(char *)(param_1 + 0x286285);
      if (cVar4 == '\0') {
        local_60 = (char *)(iVar1 + 0x212428);
        MgtMacHeaderInit(param_1,&uStack_38,0xc,0,param_2 + 0xec,*(int *)(param_2 + 8) + 0x1b);
        cVar4 = *(char *)(param_1 + 0x286285);
      }
      if (cVar4 == '\x01') {
        iVar1 = param_1 + (uint)(byte)param_2[0xe4] * 0x5834;
        local_60 = "======== Badnode detector =============\nvow_bn_en = <0/1> 0:dieable, 1:enable\nvow_bn_mon_period = <period> ms\nvow_bn_fallback_th = <count>\nvow_bn_per_th = <TX PER>\n======== Airtime counter test =============\nvow_counter_test = <0/1> 0:dieable, 1:enable\nvow_counter_test_period = <period> ms\nvow_counter_test_band = <band>\nvow_counter_test_avgcnt = <average num> sec\nvow_counter_test_target = <wlanidx>\n======== DVT =============\nvow_dvt_en = <0/1> 0:dieable, 1:enable\nvow_monitor_sta = <STA num>\nvow_show_sta = <STA num>\nvow_monitor_bss = <BSS num>\nvow_monitor_mbss = <MBSS num>\nvow_show_mbss = <MBSS num>\nvow_avg_num = <average num> sec\n======== RED ===========\nvow_set_red_en = <0/1> 0:disable, 1:enable\nvow_set_red_show_sta = <STA num>\nvow_set_red_tar_delay = <tarDelay> us\n======== WATF ===========\nvow_watf_en = <0/1> 0:disable, 1:enable\nvow_watf_q = <level>-<quantum> unit 256us\nvow_watf_add_entry = <level>-<Addr>\nvow_watf_del_entry = <Addr>\n"
                   + iVar1 + 0x101;
        MgtMacHeaderInit(param_1,&uStack_38,0xc,0,param_2 + 0xec,
                         "======== Badnode detector =============\nvow_bn_en = <0/1> 0:dieable, 1:enable\nvow_bn_mon_period = <period> ms\nvow_bn_fallback_th = <count>\nvow_bn_per_th = <TX PER>\n======== Airtime counter test =============\nvow_counter_test = <0/1> 0:dieable, 1:enable\nvow_counter_test_period = <period> ms\nvow_counter_test_band = <band>\nvow_counter_test_avgcnt = <average num> sec\nvow_counter_test_target = <wlanidx>\n======== DVT =============\nvow_dvt_en = <0/1> 0:dieable, 1:enable\nvow_monitor_sta = <STA num>\nvow_show_sta = <STA num>\nvow_monitor_bss = <BSS num>\nvow_monitor_mbss = <MBSS num>\nvow_show_mbss = <MBSS num>\nvow_avg_num = <average num> sec\n======== RED ===========\nvow_set_red_en = <0/1> 0:disable, 1:enable\nvow_set_red_show_sta = <STA num>\nvow_set_red_tar_delay = <tarDelay> us\n======== WATF ===========\nvow_watf_en = <0/1> 0:disable, 1:enable\nvow_watf_q = <level>-<quantum> unit 256us\nvow_watf_add_entry = <level>-<Addr>\nvow_watf_del_entry = <Addr>\n"
                         + iVar1 + 0xfb);
      }
      local_60 = (char *)0xffffffff;
      MakeOutgoingFrame(local_44,&local_40,0x18,&uStack_38,2,local_4a);
      if ((param_2[0x562] == '\x01') &&
         (*(char *)(param_1 + (uint)*(ushort *)(param_2 + 0xe0) * 0x620 + 0x2f762) == '\x01')) {
        MakeOutgoingFrame(local_44 + local_40,&local_3c,0x10,&local_60,0xffffffff);
        local_37 = local_37 | 0x40;
        local_40 = local_40 + local_3c;
      }
      if (param_4 == 0) {
        uVar3 = 0;
      }
      else {
        uVar3 = 0x80;
      }
      MiniportMMRequest(param_1,uVar3,local_44,local_40);
      if ((*(ushort *)(param_2 + 0xe0) < 0x120) && (*(int *)(param_2 + 0xfc) == 2)) {
        ZTE_Notify_Node_AD(0,param_2);
      }
      local_5c = param_5;
      local_58 = param_6;
      local_60 = param_2;
      __ZTE_STA_Assoc_Process(param_1,0x11,0,0,local_4a[0],0);
      wlan_dbg_save_staoffline_record(param_2,local_4a[0],0x56c,"__MlmeDeAuthAction");
      os_free_mem(local_44);
      if (param_2[0x13b1] == '\0') {
        mac_entry_delete(param_1,param_2);
        return;
      }
    }
  }
  return;
}

