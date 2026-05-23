// module: mt7915.ko
// function: RRM_EnqueueBcnReq @ 0x21d3a4
// size: 1060 bytes
//

void RRM_EnqueueBcnReq(int param_1,int param_2,int param_3,undefined2 *param_4)

{
  byte bVar1;
  undefined4 uVar2;
  int iVar3;
  uint uVar4;
  char cVar5;
  uint uVar6;
  uint uVar7;
  uint uVar8;
  char *pcVar9;
  void *local_5c;
  uint local_58;
  int local_54;
  undefined1 local_4d;
  undefined1 local_4c;
  undefined2 local_4b;
  undefined2 local_49;
  char local_47;
  undefined4 local_46;
  undefined2 local_42;
  undefined1 auStack_40 [28];
  
  uVar2 = RandomByte();
  local_5c = (void *)0x0;
  iVar3 = os_alloc_mem(param_1,&local_5c,0x900);
  if (iVar3 == 0) {
    if (param_2 == 0) {
      iVar3 = param_1 + param_3 * 0x5834;
      MgtMacHeaderInit(param_1,auStack_40,0xd,0,param_4 + 4,
                       "======== Badnode detector =============\nvow_bn_en = <0/1> 0:dieable, 1:enable\nvow_bn_mon_period = <period> ms\nvow_bn_fallback_th = <count>\nvow_bn_per_th = <TX PER>\n======== Airtime counter test =============\nvow_counter_test = <0/1> 0:dieable, 1:enable\nvow_counter_test_period = <period> ms\nvow_counter_test_band = <band>\nvow_counter_test_avgcnt = <average num> sec\nvow_counter_test_target = <wlanidx>\n======== DVT =============\nvow_dvt_en = <0/1> 0:dieable, 1:enable\nvow_monitor_sta = <STA num>\nvow_show_sta = <STA num>\nvow_monitor_bss = <BSS num>\nvow_monitor_mbss = <MBSS num>\nvow_show_mbss = <MBSS num>\nvow_avg_num = <average num> sec\n======== RED ===========\nvow_set_red_en = <0/1> 0:disable, 1:enable\nvow_set_red_show_sta = <STA num>\nvow_set_red_tar_delay = <tarDelay> us\n======== WATF ===========\nvow_watf_en = <0/1> 0:disable, 1:enable\nvow_watf_q = <level>-<quantum> unit 256us\nvow_watf_add_entry = <level>-<Addr>\nvow_watf_del_entry = <Addr>\n"
                       + iVar3 + 0xfb,
                       "======== Badnode detector =============\nvow_bn_en = <0/1> 0:dieable, 1:enable\nvow_bn_mon_period = <period> ms\nvow_bn_fallback_th = <count>\nvow_bn_per_th = <TX PER>\n======== Airtime counter test =============\nvow_counter_test = <0/1> 0:dieable, 1:enable\nvow_counter_test_period = <period> ms\nvow_counter_test_band = <band>\nvow_counter_test_avgcnt = <average num> sec\nvow_counter_test_target = <wlanidx>\n======== DVT =============\nvow_dvt_en = <0/1> 0:dieable, 1:enable\nvow_monitor_sta = <STA num>\nvow_show_sta = <STA num>\nvow_monitor_bss = <BSS num>\nvow_monitor_mbss = <MBSS num>\nvow_show_mbss = <MBSS num>\nvow_avg_num = <average num> sec\n======== RED ===========\nvow_set_red_en = <0/1> 0:disable, 1:enable\nvow_set_red_show_sta = <STA num>\nvow_set_red_tar_delay = <tarDelay> us\n======== WATF ===========\nvow_watf_en = <0/1> 0:disable, 1:enable\nvow_watf_q = <level>-<quantum> unit 256us\nvow_watf_add_entry = <level>-<Addr>\nvow_watf_del_entry = <Addr>\n"
                       + iVar3 + 0x101);
    }
    else {
      iVar3 = param_1 + param_3 * 0x5834;
      MgtMacHeaderInit(param_1,auStack_40,0xd,0,param_2 * 0x14c0 + param_1 + 0xa1e0c,
                       "======== Badnode detector =============\nvow_bn_en = <0/1> 0:dieable, 1:enable\nvow_bn_mon_period = <period> ms\nvow_bn_fallback_th = <count>\nvow_bn_per_th = <TX PER>\n======== Airtime counter test =============\nvow_counter_test = <0/1> 0:dieable, 1:enable\nvow_counter_test_period = <period> ms\nvow_counter_test_band = <band>\nvow_counter_test_avgcnt = <average num> sec\nvow_counter_test_target = <wlanidx>\n======== DVT =============\nvow_dvt_en = <0/1> 0:dieable, 1:enable\nvow_monitor_sta = <STA num>\nvow_show_sta = <STA num>\nvow_monitor_bss = <BSS num>\nvow_monitor_mbss = <MBSS num>\nvow_show_mbss = <MBSS num>\nvow_avg_num = <average num> sec\n======== RED ===========\nvow_set_red_en = <0/1> 0:disable, 1:enable\nvow_set_red_show_sta = <STA num>\nvow_set_red_tar_delay = <tarDelay> us\n======== WATF ===========\nvow_watf_en = <0/1> 0:disable, 1:enable\nvow_watf_q = <level>-<quantum> unit 256us\nvow_watf_add_entry = <level>-<Addr>\nvow_watf_del_entry = <Addr>\n"
                       + iVar3 + 0xfb,
                       "======== Badnode detector =============\nvow_bn_en = <0/1> 0:dieable, 1:enable\nvow_bn_mon_period = <period> ms\nvow_bn_fallback_th = <count>\nvow_bn_per_th = <TX PER>\n======== Airtime counter test =============\nvow_counter_test = <0/1> 0:dieable, 1:enable\nvow_counter_test_period = <period> ms\nvow_counter_test_band = <band>\nvow_counter_test_avgcnt = <average num> sec\nvow_counter_test_target = <wlanidx>\n======== DVT =============\nvow_dvt_en = <0/1> 0:dieable, 1:enable\nvow_monitor_sta = <STA num>\nvow_show_sta = <STA num>\nvow_monitor_bss = <BSS num>\nvow_monitor_mbss = <MBSS num>\nvow_show_mbss = <MBSS num>\nvow_avg_num = <average num> sec\n======== RED ===========\nvow_set_red_en = <0/1> 0:disable, 1:enable\nvow_set_red_show_sta = <STA num>\nvow_set_red_tar_delay = <tarDelay> us\n======== WATF ===========\nvow_watf_en = <0/1> 0:disable, 1:enable\nvow_watf_q = <level>-<quantum> unit 256us\nvow_watf_add_entry = <level>-<Addr>\nvow_watf_del_entry = <Addr>\n"
                       + iVar3 + 0x101);
    }
    if (local_5c != (void *)0x0) {
      memmove(local_5c,auStack_40,0x18);
    }
    local_4d = *(undefined1 *)((int)param_4 + 0x15);
    local_46 = *(undefined4 *)(param_4 + 1);
    local_4c = *(undefined1 *)(param_4 + 0xb);
    local_4b = param_4[0x32];
    local_42 = param_4[3];
    local_49 = *param_4;
    local_47 = *(char *)((int)param_4 + 0x17);
    local_58 = 0x22;
    MakeOutgoingFrame((int)local_5c + 0x22,&local_54,0xd,&local_4d,0xffffffff);
    local_58 = local_54 + local_58;
    RRM_InsertBcnReqSsidSubIE
              (param_1,(int)local_5c + local_58,&local_58,*(undefined4 *)(param_4 + 8),
               *(undefined1 *)(param_4 + 10));
    bVar1 = *(byte *)(param_4 + 0xc);
    if ((bVar1 & 1) == 0) {
      uVar7 = *(byte *)(param_4 + 10) + 0x12;
    }
    else {
      uVar7 = *(byte *)(param_4 + 10) + 0x16;
      RRM_InsertBcnReqRepCndSubIE(param_1,(int)local_5c + local_58,&local_58,0,0);
      bVar1 = *(byte *)(param_4 + 0xc);
    }
    uVar7 = uVar7 & 0xff;
    if (((bVar1 & 2) == 0) || (cVar5 = *(char *)((int)param_4 + 0x19), cVar5 == '\0')) {
      uVar4 = local_58 & 0xff;
    }
    else {
      pcVar9 = (char *)((int)param_4 + 0x19);
      do {
        uVar6 = local_58;
        InsertChannelRepIE(param_1,(int)local_5c + local_58,&local_58,param_1 + 0x794c31,cVar5,
                           (int)param_4 + 0x29,
                           *(undefined2 *)
                            (
                            "======== Badnode detector =============\nvow_bn_en = <0/1> 0:dieable, 1:enable\nvow_bn_mon_period = <period> ms\nvow_bn_fallback_th = <count>\nvow_bn_per_th = <TX PER>\n======== Airtime counter test =============\nvow_counter_test = <0/1> 0:dieable, 1:enable\nvow_counter_test_period = <period> ms\nvow_counter_test_band = <band>\nvow_counter_test_avgcnt = <average num> sec\nvow_counter_test_target = <wlanidx>\n======== DVT =============\nvow_dvt_en = <0/1> 0:dieable, 1:enable\nvow_monitor_sta = <STA num>\nvow_show_sta = <STA num>\nvow_monitor_bss = <BSS num>\nvow_monitor_mbss = <MBSS num>\nvow_show_mbss = <MBSS num>\nvow_avg_num = <average num> sec\n======== RED ===========\nvow_set_red_en = <0/1> 0:disable, 1:enable\nvow_set_red_show_sta = <STA num>\nvow_set_red_tar_delay = <tarDelay> us\n======== WATF ===========\nvow_watf_en = <0/1> 0:disable, 1:enable\nvow_watf_q = <level>-<quantum> unit 256us\nvow_watf_add_entry = <level>-<Addr>\nvow_watf_del_entry = <Addr>\n"
                            + param_3 * 0x5834 + param_1 + 0xf8),param_3);
        pcVar9 = pcVar9 + 1;
        cVar5 = *pcVar9;
        uVar4 = local_58 & 0xff;
        uVar7 = uVar7 + (uVar4 - uVar6) & 0xff;
      } while (cVar5 != '\0');
    }
    cVar5 = *(char *)(param_4 + 0x33);
    if (local_47 == '\x02') {
      RRM_InsertBcnReqRepDetailSubIE(param_1,(int)local_5c + local_58,&local_58,0);
      uVar6 = local_58 & 0xff;
      uVar7 = (uVar7 + uVar6) - uVar4 & 0xff;
    }
    else {
      RRM_InsertBcnReqRepDetailSubIE(param_1,(int)local_5c + local_58,&local_58,cVar5);
      uVar8 = local_58 & 0xff;
      uVar7 = (uVar7 + uVar8) - uVar4 & 0xff;
      uVar6 = uVar8;
      if (cVar5 == '\x01') {
        RRM_InsertRequestIE(param_1,(int)local_5c + local_58,&local_58,
                            *(undefined1 *)((int)param_4 + 0x67),param_4 + 0x34);
        uVar6 = local_58 & 0xff;
        uVar7 = uVar7 + (uVar6 - uVar8) & 0xff;
      }
    }
    InsertBcnReportIndicationReqIE(param_1,(int)local_5c + local_58,&local_58,1);
    local_54 = 0x18;
    MakeMeasurementReqFrame
              (param_1,local_5c,&local_54,(uVar7 + local_58) - uVar6 & 0xff,5,0,uVar2,0,5,0);
    MeasureReqInsert(param_1,uVar2);
    MiniportMMRequest(param_1,0x81,local_5c,local_58);
    if (local_5c != (void *)0x0) {
      os_free_mem();
      return;
    }
  }
  else if (2 < DebugLevel) {
    printk("%s() allocate memory failed\n","RRM_EnqueueBcnReq");
  }
  return;
}

