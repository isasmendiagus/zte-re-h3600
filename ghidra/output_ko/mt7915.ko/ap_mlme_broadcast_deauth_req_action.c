// module: mt7915.ko
// function: ap_mlme_broadcast_deauth_req_action @ 0x4dc78
// size: 452 bytes
//

void ap_mlme_broadcast_deauth_req_action(int param_1,void *param_2)

{
  byte bVar1;
  int iVar2;
  int iVar3;
  int *piVar4;
  uint uVar5;
  undefined4 local_48;
  undefined4 local_44;
  undefined1 auStack_40 [28];
  
  local_48 = 0;
  local_44 = 0;
  iVar2 = memcmp(param_2,&BROADCAST_ADDR,6);
  if (iVar2 == 0) {
    iVar2 = *(int *)((int)param_2 + 8);
    piVar4 = (int *)(param_1 + 0xa31e0);
    bVar1 = *(byte *)(iVar2 + 0xe);
    for (uVar5 = 1; iVar3 = HcGetMaxStaNum(param_1), (int)uVar5 < iVar3; uVar5 = uVar5 + 1) {
      if (((piVar4 != (int *)0x0) && (*piVar4 != 0)) && (piVar4[2] == iVar2)) {
        if ((*(ushort *)(piVar4 + 0x38) < 0x120) && (piVar4[0x3f] == 2)) {
          ZTE_Notify_Node_AD(0,piVar4);
          __ZTE_STA_Assoc_Process
                    (param_1,0x11,0,0,*(undefined2 *)((int)param_2 + 6),0,piVar4,
                     "ap_mlme_broadcast_deauth_req_action",0xcc);
        }
        wlan_dbg_save_staoffline_record
                  (piVar4,*(undefined2 *)((int)param_2 + 6),0xcf,
                   "ap_mlme_broadcast_deauth_req_action");
        MacTableDeleteEntry(param_1,uVar5 & 0xffff,piVar4 + 0x3b);
      }
      piVar4 = piVar4 + 0x530;
    }
    iVar2 = os_alloc_mem(param_1,&local_48,0x900);
    if (iVar2 == 0) {
      iVar2 = param_1 + (uint)bVar1 * 0x5834;
      MgtMacHeaderInit(param_1,auStack_40,0xc,0,param_2,
                       "======== Badnode detector =============\nvow_bn_en = <0/1> 0:dieable, 1:enable\nvow_bn_mon_period = <period> ms\nvow_bn_fallback_th = <count>\nvow_bn_per_th = <TX PER>\n======== Airtime counter test =============\nvow_counter_test = <0/1> 0:dieable, 1:enable\nvow_counter_test_period = <period> ms\nvow_counter_test_band = <band>\nvow_counter_test_avgcnt = <average num> sec\nvow_counter_test_target = <wlanidx>\n======== DVT =============\nvow_dvt_en = <0/1> 0:dieable, 1:enable\nvow_monitor_sta = <STA num>\nvow_show_sta = <STA num>\nvow_monitor_bss = <BSS num>\nvow_monitor_mbss = <MBSS num>\nvow_show_mbss = <MBSS num>\nvow_avg_num = <average num> sec\n======== RED ===========\nvow_set_red_en = <0/1> 0:disable, 1:enable\nvow_set_red_show_sta = <STA num>\nvow_set_red_tar_delay = <tarDelay> us\n======== WATF ===========\nvow_watf_en = <0/1> 0:disable, 1:enable\nvow_watf_q = <level>-<quantum> unit 256us\nvow_watf_add_entry = <level>-<Addr>\nvow_watf_del_entry = <Addr>\n"
                       + iVar2 + 0xfb,
                       "======== Badnode detector =============\nvow_bn_en = <0/1> 0:dieable, 1:enable\nvow_bn_mon_period = <period> ms\nvow_bn_fallback_th = <count>\nvow_bn_per_th = <TX PER>\n======== Airtime counter test =============\nvow_counter_test = <0/1> 0:dieable, 1:enable\nvow_counter_test_period = <period> ms\nvow_counter_test_band = <band>\nvow_counter_test_avgcnt = <average num> sec\nvow_counter_test_target = <wlanidx>\n======== DVT =============\nvow_dvt_en = <0/1> 0:dieable, 1:enable\nvow_monitor_sta = <STA num>\nvow_show_sta = <STA num>\nvow_monitor_bss = <BSS num>\nvow_monitor_mbss = <MBSS num>\nvow_show_mbss = <MBSS num>\nvow_avg_num = <average num> sec\n======== RED ===========\nvow_set_red_en = <0/1> 0:disable, 1:enable\nvow_set_red_show_sta = <STA num>\nvow_set_red_tar_delay = <tarDelay> us\n======== WATF ===========\nvow_watf_en = <0/1> 0:disable, 1:enable\nvow_watf_q = <level>-<quantum> unit 256us\nvow_watf_add_entry = <level>-<Addr>\nvow_watf_del_entry = <Addr>\n"
                       + iVar2 + 0x101);
      MakeOutgoingFrame(local_48,&local_44,0x18,auStack_40,2,(int)param_2 + 6,0xffffffff);
      MiniportMMRequest(param_1,0,local_48,local_44);
      os_free_mem(local_48);
      return;
    }
  }
  return;
}

