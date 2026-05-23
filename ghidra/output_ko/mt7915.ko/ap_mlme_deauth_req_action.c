// module: mt7915.ko
// function: ap_mlme_deauth_req_action @ 0x4de44
// size: 564 bytes
//

void ap_mlme_deauth_req_action(int param_1,undefined1 *param_2)

{
  byte bVar1;
  ushort uVar2;
  uint uVar3;
  int iVar4;
  ushort *puVar5;
  int iVar6;
  undefined4 local_48;
  undefined4 local_44;
  undefined1 auStack_40 [28];
  
  local_48 = 0;
  puVar5 = (ushort *)(param_2 + 0x920);
  local_44 = 0;
  if (2 < DebugLevel) {
    printk(" ---> %s, wcid = %d\n","ap_mlme_deauth_req_action",*puVar5);
  }
  uVar2 = *puVar5;
  uVar3 = HcGetMaxStaNum(param_1);
  if (uVar2 < uVar3) {
    if (2 < DebugLevel) {
      printk("Valid unicast entry\n");
    }
    iVar6 = param_1 + (uint)*puVar5 * 0x14c0 + 0xa1d20;
    if (iVar6 != 0) {
      iVar4 = param_1 + (uint)*puVar5 * 0x14c0;
      bVar1 = *(byte *)(iVar4 + 0xa1e04);
      if (*(ushort *)(iVar4 + 0xa1e00) < 0x120) {
        if (*(int *)(iVar4 + 0xa1e1c) == 2) {
          ZTE_Notify_Node_AD(0,iVar6);
          __ZTE_STA_Assoc_Process
                    (param_1,0x11,0,0,*(undefined2 *)(param_2 + 6),0,iVar6,
                     "ap_mlme_deauth_req_action",0x10c);
        }
      }
      wlan_dbg_save_staoffline_record
                (iVar6,*(undefined2 *)(param_2 + 6),0x10f,"ap_mlme_deauth_req_action");
      MacTableDeleteEntry(param_1,*puVar5,param_2);
      iVar6 = os_alloc_mem(param_1,&local_48,0x900);
      if (iVar6 == 0) {
        if (2 < DebugLevel) {
          printk("AUTH - Send DE-AUTH req to %02x:%02x:%02x:%02x:%02x:%02x\n",*param_2,param_2[1],
                 param_2[2],param_2[3],param_2[4],param_2[5]);
        }
        iVar6 = param_1 + (uint)bVar1 * 0x5834;
        MgtMacHeaderInit(param_1,auStack_40,0xc,0,param_2,
                         "======== Badnode detector =============\nvow_bn_en = <0/1> 0:dieable, 1:enable\nvow_bn_mon_period = <period> ms\nvow_bn_fallback_th = <count>\nvow_bn_per_th = <TX PER>\n======== Airtime counter test =============\nvow_counter_test = <0/1> 0:dieable, 1:enable\nvow_counter_test_period = <period> ms\nvow_counter_test_band = <band>\nvow_counter_test_avgcnt = <average num> sec\nvow_counter_test_target = <wlanidx>\n======== DVT =============\nvow_dvt_en = <0/1> 0:dieable, 1:enable\nvow_monitor_sta = <STA num>\nvow_show_sta = <STA num>\nvow_monitor_bss = <BSS num>\nvow_monitor_mbss = <MBSS num>\nvow_show_mbss = <MBSS num>\nvow_avg_num = <average num> sec\n======== RED ===========\nvow_set_red_en = <0/1> 0:disable, 1:enable\nvow_set_red_show_sta = <STA num>\nvow_set_red_tar_delay = <tarDelay> us\n======== WATF ===========\nvow_watf_en = <0/1> 0:disable, 1:enable\nvow_watf_q = <level>-<quantum> unit 256us\nvow_watf_add_entry = <level>-<Addr>\nvow_watf_del_entry = <Addr>\n"
                         + iVar6 + 0xfb,
                         "======== Badnode detector =============\nvow_bn_en = <0/1> 0:dieable, 1:enable\nvow_bn_mon_period = <period> ms\nvow_bn_fallback_th = <count>\nvow_bn_per_th = <TX PER>\n======== Airtime counter test =============\nvow_counter_test = <0/1> 0:dieable, 1:enable\nvow_counter_test_period = <period> ms\nvow_counter_test_band = <band>\nvow_counter_test_avgcnt = <average num> sec\nvow_counter_test_target = <wlanidx>\n======== DVT =============\nvow_dvt_en = <0/1> 0:dieable, 1:enable\nvow_monitor_sta = <STA num>\nvow_show_sta = <STA num>\nvow_monitor_bss = <BSS num>\nvow_monitor_mbss = <MBSS num>\nvow_show_mbss = <MBSS num>\nvow_avg_num = <average num> sec\n======== RED ===========\nvow_set_red_en = <0/1> 0:disable, 1:enable\nvow_set_red_show_sta = <STA num>\nvow_set_red_tar_delay = <tarDelay> us\n======== WATF ===========\nvow_watf_en = <0/1> 0:disable, 1:enable\nvow_watf_q = <level>-<quantum> unit 256us\nvow_watf_add_entry = <level>-<Addr>\nvow_watf_del_entry = <Addr>\n"
                         + iVar6 + 0x101);
        MakeOutgoingFrame(local_48,&local_44,0x18,auStack_40,2,param_2 + 6,0xffffffff);
        MiniportMMRequest(param_1,0,local_48,local_44);
        os_free_mem(local_48);
      }
    }
    return;
  }
  ap_mlme_broadcast_deauth_req_action(param_1,param_2);
  return;
}

