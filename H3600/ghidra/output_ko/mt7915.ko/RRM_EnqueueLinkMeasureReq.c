// module: mt7915.ko
// function: RRM_EnqueueLinkMeasureReq @ 0x21e30c
// size: 604 bytes
//

void RRM_EnqueueLinkMeasureReq(int param_1,uint param_2,uint param_3)

{
  undefined4 uVar1;
  uint uVar2;
  int iVar3;
  undefined4 uVar4;
  int iVar5;
  int iVar6;
  undefined1 local_3d;
  void *local_3c;
  int local_38;
  int local_34;
  undefined1 auStack_30 [24];
  
  uVar1 = RandomByte();
  local_3c = (void *)0x0;
  if ((param_3 < (byte)"======== Badnode detector =============\nvow_bn_en = <0/1> 0:dieable, 1:enable\nvow_bn_mon_period = <period> ms\nvow_bn_fallback_th = <count>\nvow_bn_per_th = <TX PER>\n======== Airtime counter test =============\nvow_counter_test = <0/1> 0:dieable, 1:enable\nvow_counter_test_period = <period> ms\nvow_counter_test_band = <band>\nvow_counter_test_avgcnt = <average num> sec\nvow_counter_test_target = <wlanidx>\n======== DVT =============\nvow_dvt_en = <0/1> 0:dieable, 1:enable\nvow_monitor_sta = <STA num>\nvow_show_sta = <STA num>\nvow_monitor_bss = <BSS num>\nvow_monitor_mbss = <MBSS num>\nvow_show_mbss = <MBSS num>\nvow_avg_num = <average num> sec\n======== RED ===========\nvow_set_red_en = <0/1> 0:disable, 1:enable\nvow_set_red_show_sta = <STA num>\nvow_set_red_tar_delay = <tarDelay> us\n======== WATF ===========\nvow_watf_en = <0/1> 0:disable, 1:enable\nvow_watf_q = <level>-<quantum> unit 256us\nvow_watf_add_entry = <level>-<Addr>\nvow_watf_del_entry = <Addr>\n"
                       [param_1 + 0xda]) && (uVar2 = HcGetMaxStaNum(param_1), param_2 < uVar2)) {
    iVar3 = os_alloc_mem(param_1,&local_3c,0x900);
    if (iVar3 == 0) {
      if (local_3c != (void *)0x0) {
        iVar3 = param_1 + param_2 * 0x14c0;
        iVar5 = *(int *)(iVar3 + 0xa1d28);
        iVar6 = param_1 + (uint)*(byte *)(iVar3 + 0xa1e04) * 0x5834;
        MgtMacHeaderInit(param_1,auStack_30,0xd,0,iVar3 + 0xa1e0c,
                         "======== Badnode detector =============\nvow_bn_en = <0/1> 0:dieable, 1:enable\nvow_bn_mon_period = <period> ms\nvow_bn_fallback_th = <count>\nvow_bn_per_th = <TX PER>\n======== Airtime counter test =============\nvow_counter_test = <0/1> 0:dieable, 1:enable\nvow_counter_test_period = <period> ms\nvow_counter_test_band = <band>\nvow_counter_test_avgcnt = <average num> sec\nvow_counter_test_target = <wlanidx>\n======== DVT =============\nvow_dvt_en = <0/1> 0:dieable, 1:enable\nvow_monitor_sta = <STA num>\nvow_show_sta = <STA num>\nvow_monitor_bss = <BSS num>\nvow_monitor_mbss = <MBSS num>\nvow_show_mbss = <MBSS num>\nvow_avg_num = <average num> sec\n======== RED ===========\nvow_set_red_en = <0/1> 0:disable, 1:enable\nvow_set_red_show_sta = <STA num>\nvow_set_red_tar_delay = <tarDelay> us\n======== WATF ===========\nvow_watf_en = <0/1> 0:disable, 1:enable\nvow_watf_q = <level>-<quantum> unit 256us\nvow_watf_add_entry = <level>-<Addr>\nvow_watf_del_entry = <Addr>\n"
                         + iVar6 + 0xfb,
                         "======== Badnode detector =============\nvow_bn_en = <0/1> 0:dieable, 1:enable\nvow_bn_mon_period = <period> ms\nvow_bn_fallback_th = <count>\nvow_bn_per_th = <TX PER>\n======== Airtime counter test =============\nvow_counter_test = <0/1> 0:dieable, 1:enable\nvow_counter_test_period = <period> ms\nvow_counter_test_band = <band>\nvow_counter_test_avgcnt = <average num> sec\nvow_counter_test_target = <wlanidx>\n======== DVT =============\nvow_dvt_en = <0/1> 0:dieable, 1:enable\nvow_monitor_sta = <STA num>\nvow_show_sta = <STA num>\nvow_monitor_bss = <BSS num>\nvow_monitor_mbss = <MBSS num>\nvow_show_mbss = <MBSS num>\nvow_avg_num = <average num> sec\n======== RED ===========\nvow_set_red_en = <0/1> 0:disable, 1:enable\nvow_set_red_show_sta = <STA num>\nvow_set_red_tar_delay = <tarDelay> us\n======== WATF ===========\nvow_watf_en = <0/1> 0:disable, 1:enable\nvow_watf_q = <level>-<quantum> unit 256us\nvow_watf_add_entry = <level>-<Addr>\nvow_watf_del_entry = <Addr>\n"
                         + iVar6 + 0x101);
        memmove(local_3c,auStack_30,0x18);
        local_38 = 0x18;
        InsertActField(param_1,(int)local_3c + 0x18,&local_38,5,2);
        InsertDialogToken(param_1,(int)local_3c + local_38,&local_38,uVar1);
        local_3d = RTMP_GetTxPwr(param_1,*(undefined2 *)(iVar5 + 0xb0a),
                                 *(undefined1 *)(iVar5 + 0x1a),iVar5);
        MakeOutgoingFrame((int)local_3c + local_38,&local_34,1,&local_3d,0xffffffff);
        local_38 = local_38 + local_34;
        uVar4 = wlan_operate_get_ht_bw(iVar5);
        local_3d = GetCuntryMaxTxPwr(param_1,*(undefined2 *)(iVar5 + 0x18),iVar5,uVar4);
        MakeOutgoingFrame((int)local_3c + local_38,&local_34,1,&local_3d,0xffffffff);
        local_38 = local_38 + local_34;
        MeasureReqInsert(param_1,uVar1);
        MiniportMMRequest(param_1,0x81,local_3c,local_38);
        if (local_3c != (void *)0x0) {
          os_free_mem();
        }
      }
    }
    else if (2 < DebugLevel) {
      printk("%s() allocate memory failed\n","RRM_EnqueueLinkMeasureReq");
    }
  }
  else if (-1 < DebugLevel) {
    printk("%s: Invalid STA. apidx=%d Aid=%d\n","RRM_EnqueueLinkMeasureReq",param_3,param_2);
  }
  return;
}

