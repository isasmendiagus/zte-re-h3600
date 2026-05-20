// module: mt7915.ko
// function: APMlmeKickOutSta @ 0x51778
// size: 476 bytes
//

void APMlmeKickOutSta(int param_1,undefined1 *param_2,uint param_3,undefined2 param_4)

{
  int iVar1;
  uint uVar2;
  int iVar3;
  uint uVar4;
  undefined2 local_42;
  undefined4 local_40;
  undefined4 local_3c;
  undefined1 auStack_38 [28];
  
  local_40 = 0;
  local_3c = 0;
  local_42 = param_4;
  iVar1 = MacTableLookup();
  if (iVar1 != 0) {
    uVar4 = (uint)*(byte *)(iVar1 + 0xe4);
    if (uVar4 < (byte)"======== Badnode detector =============\nvow_bn_en = <0/1> 0:dieable, 1:enable\nvow_bn_mon_period = <period> ms\nvow_bn_fallback_th = <count>\nvow_bn_per_th = <TX PER>\n======== Airtime counter test =============\nvow_counter_test = <0/1> 0:dieable, 1:enable\nvow_counter_test_period = <period> ms\nvow_counter_test_band = <band>\nvow_counter_test_avgcnt = <average num> sec\nvow_counter_test_target = <wlanidx>\n======== DVT =============\nvow_dvt_en = <0/1> 0:dieable, 1:enable\nvow_monitor_sta = <STA num>\nvow_show_sta = <STA num>\nvow_monitor_bss = <BSS num>\nvow_monitor_mbss = <MBSS num>\nvow_show_mbss = <MBSS num>\nvow_avg_num = <average num> sec\n======== RED ===========\nvow_set_red_en = <0/1> 0:disable, 1:enable\nvow_set_red_show_sta = <STA num>\nvow_set_red_tar_delay = <tarDelay> us\n======== WATF ===========\nvow_watf_en = <0/1> 0:disable, 1:enable\nvow_watf_q = <level>-<quantum> unit 256us\nvow_watf_add_entry = <level>-<Addr>\nvow_watf_del_entry = <Addr>\n"
                      [param_1 + 0xda]) {
      uVar2 = HcGetMaxStaNum(param_1);
      if ((param_3 < uVar2) && (iVar3 = os_alloc_mem(param_1,&local_40,0x900), iVar3 == 0)) {
        if (2 < DebugLevel) {
          printk("ASSOC - MLME disassociates %02x:%02x:%02x:%02x:%02x:%02x; Send DISASSOC request\n"
                 ,*param_2,param_2[1],param_2[2],param_2[3],param_2[4],param_2[5]);
        }
        iVar3 = param_1 + uVar4 * 0x5834;
        MgtMacHeaderInit(param_1,auStack_38,10,0,param_2,
                         "======== Badnode detector =============\nvow_bn_en = <0/1> 0:dieable, 1:enable\nvow_bn_mon_period = <period> ms\nvow_bn_fallback_th = <count>\nvow_bn_per_th = <TX PER>\n======== Airtime counter test =============\nvow_counter_test = <0/1> 0:dieable, 1:enable\nvow_counter_test_period = <period> ms\nvow_counter_test_band = <band>\nvow_counter_test_avgcnt = <average num> sec\nvow_counter_test_target = <wlanidx>\n======== DVT =============\nvow_dvt_en = <0/1> 0:dieable, 1:enable\nvow_monitor_sta = <STA num>\nvow_show_sta = <STA num>\nvow_monitor_bss = <BSS num>\nvow_monitor_mbss = <MBSS num>\nvow_show_mbss = <MBSS num>\nvow_avg_num = <average num> sec\n======== RED ===========\nvow_set_red_en = <0/1> 0:disable, 1:enable\nvow_set_red_show_sta = <STA num>\nvow_set_red_tar_delay = <tarDelay> us\n======== WATF ===========\nvow_watf_en = <0/1> 0:disable, 1:enable\nvow_watf_q = <level>-<quantum> unit 256us\nvow_watf_add_entry = <level>-<Addr>\nvow_watf_del_entry = <Addr>\n"
                         + iVar3 + 0xfb,
                         "======== Badnode detector =============\nvow_bn_en = <0/1> 0:dieable, 1:enable\nvow_bn_mon_period = <period> ms\nvow_bn_fallback_th = <count>\nvow_bn_per_th = <TX PER>\n======== Airtime counter test =============\nvow_counter_test = <0/1> 0:dieable, 1:enable\nvow_counter_test_period = <period> ms\nvow_counter_test_band = <band>\nvow_counter_test_avgcnt = <average num> sec\nvow_counter_test_target = <wlanidx>\n======== DVT =============\nvow_dvt_en = <0/1> 0:dieable, 1:enable\nvow_monitor_sta = <STA num>\nvow_show_sta = <STA num>\nvow_monitor_bss = <BSS num>\nvow_monitor_mbss = <MBSS num>\nvow_show_mbss = <MBSS num>\nvow_avg_num = <average num> sec\n======== RED ===========\nvow_set_red_en = <0/1> 0:disable, 1:enable\nvow_set_red_show_sta = <STA num>\nvow_set_red_tar_delay = <tarDelay> us\n======== WATF ===========\nvow_watf_en = <0/1> 0:disable, 1:enable\nvow_watf_q = <level>-<quantum> unit 256us\nvow_watf_add_entry = <level>-<Addr>\nvow_watf_del_entry = <Addr>\n"
                         + iVar3 + 0x101);
        MakeOutgoingFrame(local_40,&local_3c,0x18,auStack_38,2,&local_42,0xffffffff);
        MiniportMMRequest(param_1,0,local_40,local_3c);
        os_free_mem(local_40);
        ZTE_Notify_Node_AD(0,iVar1);
        wlan_dbg_save_staoffline_record(iVar1,local_42,0xd5b,"APMlmeKickOutSta");
        __ZTE_STA_Assoc_Process(param_1,0x11,0,0,local_42,0,iVar1,"APMlmeKickOutSta",0xd5e);
        MacTableDeleteEntry(param_1,param_3,param_2);
      }
    }
    else if (-1 < DebugLevel) {
      printk("%s: Invalid Apidx=%d\n","APMlmeKickOutSta",uVar4);
    }
  }
  return;
}

