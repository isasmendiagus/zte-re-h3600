// module: mt7915.ko
// function: RRM_EnqueueTxStreamMeasureReq @ 0x21e56c
// size: 632 bytes
//

/* WARNING: Type propagation algorithm not settling */

void RRM_EnqueueTxStreamMeasureReq(int param_1,int param_2,int param_3,undefined2 *param_4)

{
  byte bVar1;
  byte bVar2;
  bool bVar3;
  undefined4 uVar4;
  int iVar5;
  byte bVar6;
  undefined4 uVar7;
  uint uVar8;
  void *local_58;
  int local_54 [2];
  undefined4 local_4c;
  undefined1 local_48;
  undefined1 local_47;
  undefined2 local_44;
  undefined2 local_42;
  undefined4 local_40;
  undefined2 local_3c;
  char local_3a;
  undefined1 local_39;
  undefined1 auStack_38 [24];
  
  uVar4 = RandomByte();
  local_58 = (void *)0x0;
  iVar5 = os_alloc_mem(param_1,&local_58,0x900);
  if (iVar5 == 0) {
    if (local_58 != (void *)0x0) {
      iVar5 = param_1 + param_3 * 0x5834;
      MgtMacHeaderInit(param_1,auStack_38,0xd,0,param_1 + param_2 * 0x14c0 + 0xa1e0c,
                       "======== Badnode detector =============\nvow_bn_en = <0/1> 0:dieable, 1:enable\nvow_bn_mon_period = <period> ms\nvow_bn_fallback_th = <count>\nvow_bn_per_th = <TX PER>\n======== Airtime counter test =============\nvow_counter_test = <0/1> 0:dieable, 1:enable\nvow_counter_test_period = <period> ms\nvow_counter_test_band = <band>\nvow_counter_test_avgcnt = <average num> sec\nvow_counter_test_target = <wlanidx>\n======== DVT =============\nvow_dvt_en = <0/1> 0:dieable, 1:enable\nvow_monitor_sta = <STA num>\nvow_show_sta = <STA num>\nvow_monitor_bss = <BSS num>\nvow_monitor_mbss = <MBSS num>\nvow_show_mbss = <MBSS num>\nvow_avg_num = <average num> sec\n======== RED ===========\nvow_set_red_en = <0/1> 0:disable, 1:enable\nvow_set_red_show_sta = <STA num>\nvow_set_red_tar_delay = <tarDelay> us\n======== WATF ===========\nvow_watf_en = <0/1> 0:disable, 1:enable\nvow_watf_q = <level>-<quantum> unit 256us\nvow_watf_add_entry = <level>-<Addr>\nvow_watf_del_entry = <Addr>\n"
                       + iVar5 + 0xfb,
                       "======== Badnode detector =============\nvow_bn_en = <0/1> 0:dieable, 1:enable\nvow_bn_mon_period = <period> ms\nvow_bn_fallback_th = <count>\nvow_bn_per_th = <TX PER>\n======== Airtime counter test =============\nvow_counter_test = <0/1> 0:dieable, 1:enable\nvow_counter_test_period = <period> ms\nvow_counter_test_band = <band>\nvow_counter_test_avgcnt = <average num> sec\nvow_counter_test_target = <wlanidx>\n======== DVT =============\nvow_dvt_en = <0/1> 0:dieable, 1:enable\nvow_monitor_sta = <STA num>\nvow_show_sta = <STA num>\nvow_monitor_bss = <BSS num>\nvow_monitor_mbss = <MBSS num>\nvow_show_mbss = <MBSS num>\nvow_avg_num = <average num> sec\n======== RED ===========\nvow_set_red_en = <0/1> 0:disable, 1:enable\nvow_set_red_show_sta = <STA num>\nvow_set_red_tar_delay = <tarDelay> us\n======== WATF ===========\nvow_watf_en = <0/1> 0:disable, 1:enable\nvow_watf_q = <level>-<quantum> unit 256us\nvow_watf_add_entry = <level>-<Addr>\nvow_watf_del_entry = <Addr>\n"
                       + iVar5 + 0x101);
      iVar5 = param_1 + param_2 * 0x14c0;
      memmove(local_58,auStack_38,0x18);
      local_42 = *param_4;
      local_40 = *(undefined4 *)(iVar5 + 0xa1e0c);
      local_39 = *(undefined1 *)((int)param_4 + 3);
      local_3c = (undefined2)*(undefined4 *)(iVar5 + 0xa1e10);
      local_3a = *(char *)(param_4 + 1) << 4;
      local_44 = 0;
      local_54[0] = 0x22;
      MakeOutgoingFrame((int)local_58 + 0x22,&local_4c,0xc,&local_44,0xffffffff);
      iVar5 = local_4c;
      local_54[0] = local_4c + local_54[0];
      if (*(char *)(param_4 + 2) == '\x01') {
        bVar6 = *(byte *)((int)param_4 + 7);
        local_47 = *(undefined1 *)(param_4 + 6);
        bVar1 = bVar6 & 1;
        bVar2 = (byte)local_4c & 0xf8 | *(byte *)((int)param_4 + 5) & 1 |
                (*(byte *)(param_4 + 3) & 1) << 1 | bVar1 << 2;
        local_4c = CONCAT31(local_4c._1_3_,bVar2);
        local_48 = *(undefined1 *)((int)param_4 + 0xb);
        bVar3 = (*(byte *)((int)param_4 + 5) & 1) != 0;
        if (bVar3) {
          bVar6 = *(byte *)(param_4 + 4);
        }
        uVar8 = 8;
        if (bVar3) {
          local_4c._2_2_ = SUB42(iVar5,2);
          local_4c._0_2_ = CONCAT11(bVar6,bVar2);
        }
        if ((*(byte *)(param_4 + 3) & 1) != 0) {
          local_4c._0_3_ = CONCAT12(*(undefined1 *)((int)param_4 + 9),(undefined2)local_4c);
        }
        if (bVar1 != 0) {
          local_4c = CONCAT13(*(undefined1 *)(param_4 + 5),(undefined3)local_4c);
        }
        RRM_InsertTxStreamReqTriggerReportSubIE
                  (param_1,(int)local_58 + local_54[0],local_54,&local_4c);
        uVar7 = 0x17;
      }
      else {
        uVar7 = 0xf;
        uVar8 = 0;
      }
      local_54[1] = 0x18;
      MakeMeasurementReqFrame
                (param_1,local_58,local_54 + 1,uVar7,5,0,uVar4,
                 uVar8 | 2 | (*(byte *)((int)param_4 + 0xd) & 1) << 4,9,0xffff);
      MeasureReqInsert(param_1,uVar4);
      MiniportMMRequest(param_1,0x81,local_58,local_54[0]);
      if (local_58 != (void *)0x0) {
        os_free_mem();
        return;
      }
    }
  }
  else if (2 < DebugLevel) {
    printk("%s() allocate memory failed\n","RRM_EnqueueTxStreamMeasureReq");
  }
  return;
}

