// module: mt7915.ko
// function: RtmpEnqueueNullFrame @ 0x12cc98
// size: 524 bytes
//

void RtmpEnqueueNullFrame
               (int param_1,undefined4 param_2,int param_3,uint param_4,byte param_5,char param_6,
               char param_7,byte param_8)

{
  byte *pbVar1;
  undefined2 uVar2;
  int iVar3;
  char cVar4;
  byte bVar5;
  undefined4 uVar6;
  int iVar7;
  byte *local_2c [2];
  
  cVar4 = *(char *)(param_1 + 0x286285);
  if (cVar4 == '\x01') {
    iVar7 = MacTableLookup();
    cVar4 = *(char *)(param_1 + 0x286285);
  }
  else {
    iVar7 = 0;
  }
  if (cVar4 == '\0') {
    iVar7 = MacTableLookup2(param_1,param_2);
  }
  iVar3 = os_alloc_mem(param_1,local_2c,0x900);
  pbVar1 = local_2c[0];
  if (iVar3 == 0) {
    if ((iVar7 == 0) || (iVar7 = *(int *)(*(int *)(iVar7 + 8) + 0x14), iVar7 != 1 && iVar7 != 0x20))
    {
      if (*(char *)(param_1 + 0x286285) == '\0') {
        local_2c[0][1] = local_2c[0][1] & 0xfd | 1;
      }
    }
    else {
      iVar7 = param_1 + (uint)param_5 * 0x5834;
      MgtMacHeaderInit(param_1,local_2c[0],4,0,param_2,
                       "======== Badnode detector =============\nvow_bn_en = <0/1> 0:dieable, 1:enable\nvow_bn_mon_period = <period> ms\nvow_bn_fallback_th = <count>\nvow_bn_per_th = <TX PER>\n======== Airtime counter test =============\nvow_counter_test = <0/1> 0:dieable, 1:enable\nvow_counter_test_period = <period> ms\nvow_counter_test_band = <band>\nvow_counter_test_avgcnt = <average num> sec\nvow_counter_test_target = <wlanidx>\n======== DVT =============\nvow_dvt_en = <0/1> 0:dieable, 1:enable\nvow_monitor_sta = <STA num>\nvow_show_sta = <STA num>\nvow_monitor_bss = <BSS num>\nvow_monitor_mbss = <MBSS num>\nvow_show_mbss = <MBSS num>\nvow_avg_num = <average num> sec\n======== RED ===========\nvow_set_red_en = <0/1> 0:disable, 1:enable\nvow_set_red_show_sta = <STA num>\nvow_set_red_tar_delay = <tarDelay> us\n======== WATF ===========\nvow_watf_en = <0/1> 0:disable, 1:enable\nvow_watf_q = <level>-<quantum> unit 256us\nvow_watf_add_entry = <level>-<Addr>\nvow_watf_del_entry = <Addr>\n"
                       + iVar7 + 0xfb,
                       "======== Badnode detector =============\nvow_bn_en = <0/1> 0:dieable, 1:enable\nvow_bn_mon_period = <period> ms\nvow_bn_fallback_th = <count>\nvow_bn_per_th = <TX PER>\n======== Airtime counter test =============\nvow_counter_test = <0/1> 0:dieable, 1:enable\nvow_counter_test_period = <period> ms\nvow_counter_test_band = <band>\nvow_counter_test_avgcnt = <average num> sec\nvow_counter_test_target = <wlanidx>\n======== DVT =============\nvow_dvt_en = <0/1> 0:dieable, 1:enable\nvow_monitor_sta = <STA num>\nvow_show_sta = <STA num>\nvow_monitor_bss = <BSS num>\nvow_monitor_mbss = <MBSS num>\nvow_show_mbss = <MBSS num>\nvow_avg_num = <average num> sec\n======== RED ===========\nvow_set_red_en = <0/1> 0:disable, 1:enable\nvow_set_red_show_sta = <STA num>\nvow_set_red_tar_delay = <tarDelay> us\n======== WATF ===========\nvow_watf_en = <0/1> 0:disable, 1:enable\nvow_watf_q = <level>-<quantum> unit 256us\nvow_watf_add_entry = <level>-<Addr>\nvow_watf_del_entry = <Addr>\n"
                       + iVar7 + 0x101);
      pbVar1[1] = pbVar1[1] & 0xfe | 2;
    }
    *pbVar1 = *pbVar1 & 0xf3 | 8;
    if (param_6 == '\0') {
      uVar6 = 0x18;
      *pbVar1 = *pbVar1 & 0xf | 0x40;
    }
    else {
      uVar6 = 0x1a;
      pbVar1[0x19] = 0;
      if (param_7 == '\0') {
        bVar5 = 0;
      }
      else {
        bVar5 = 0x10;
      }
      *pbVar1 = *pbVar1 & 0xf | 0xc0;
      pbVar1[0x18] = bVar5 | param_8;
    }
    uVar2 = RTMPCalcDuration(param_1,param_3,uVar6);
    *(undefined2 *)(pbVar1 + 2) = uVar2;
    if (3 < DebugLevel) {
      printk("send NULL Frame @%d Mbps to AID#%d...\n",RateIdToMbps[param_3],param_4 & 0x3f);
    }
    MiniportMMRequest(param_1,WMM_UP2AC_MAP._7_1_,pbVar1,uVar6);
    os_free_mem(local_2c[0]);
  }
  return;
}

