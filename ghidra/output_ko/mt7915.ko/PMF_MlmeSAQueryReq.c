// module: mt7915.ko
// function: PMF_MlmeSAQueryReq @ 0x219874
// size: 684 bytes
//

void PMF_MlmeSAQueryReq(int param_1,int *param_2)

{
  undefined1 uVar1;
  undefined1 uVar2;
  char *pcVar3;
  char cVar4;
  undefined1 local_42;
  undefined1 local_41;
  int local_40;
  undefined4 local_3c;
  undefined1 auStack_38 [24];
  
  local_40 = 0;
  local_3c = 0;
  if (param_2 == (int *)0x0) {
    if (DebugLevel < 0) {
      return;
    }
    printk("[PMF]%s : Entry is NULL\n","PMF_MlmeSAQueryReq");
    return;
  }
  if (*(char *)((int)param_2 + 0x562) == '\0') {
    if (DebugLevel < 0) {
      return;
    }
    uVar2 = *(undefined1 *)((int)param_2 + 0xee);
    uVar1 = (undefined1)param_2[0x3b];
    pcVar3 = "[PMF]%s : Entry is not PMF capable, STA(%02x:%02x:%02x:%02x:%02x:%02x)\n";
  }
  else {
    if ((char)param_2[0x18a] == '\x02') {
      return;
    }
    os_alloc_mem(0,&local_40,0x800);
    if (local_40 == 0) {
      return;
    }
    cVar4 = *(char *)(param_1 + 0x286285);
    if (cVar4 == '\x01') {
      if (*param_2 == 2) {
        ApCliMgtMacHeaderInit
                  (param_1,auStack_38,0xd,0,param_2 + 0x3b,param_2 + 0x3b,(char)param_2[0x39]);
        cVar4 = *(char *)(param_1 + 0x286285);
      }
      else {
        MgtMacHeaderInit(param_1,auStack_38,0xd,0,param_2 + 0x3b,
                         "======== Badnode detector =============\nvow_bn_en = <0/1> 0:dieable, 1:enable\nvow_bn_mon_period = <period> ms\nvow_bn_fallback_th = <count>\nvow_bn_per_th = <TX PER>\n======== Airtime counter test =============\nvow_counter_test = <0/1> 0:dieable, 1:enable\nvow_counter_test_period = <period> ms\nvow_counter_test_band = <band>\nvow_counter_test_avgcnt = <average num> sec\nvow_counter_test_target = <wlanidx>\n======== DVT =============\nvow_dvt_en = <0/1> 0:dieable, 1:enable\nvow_monitor_sta = <STA num>\nvow_show_sta = <STA num>\nvow_monitor_bss = <BSS num>\nvow_monitor_mbss = <MBSS num>\nvow_show_mbss = <MBSS num>\nvow_avg_num = <average num> sec\n======== RED ===========\nvow_set_red_en = <0/1> 0:disable, 1:enable\nvow_set_red_show_sta = <STA num>\nvow_set_red_tar_delay = <tarDelay> us\n======== WATF ===========\nvow_watf_en = <0/1> 0:disable, 1:enable\nvow_watf_q = <level>-<quantum> unit 256us\nvow_watf_add_entry = <level>-<Addr>\nvow_watf_del_entry = <Addr>\n"
                         + (uint)*(byte *)(param_2 + 0x39) * 0x5834 + param_1 + 0x101,
                         "======== Badnode detector =============\nvow_bn_en = <0/1> 0:dieable, 1:enable\nvow_bn_mon_period = <period> ms\nvow_bn_fallback_th = <count>\nvow_bn_per_th = <TX PER>\n======== Airtime counter test =============\nvow_counter_test = <0/1> 0:dieable, 1:enable\nvow_counter_test_period = <period> ms\nvow_counter_test_band = <band>\nvow_counter_test_avgcnt = <average num> sec\nvow_counter_test_target = <wlanidx>\n======== DVT =============\nvow_dvt_en = <0/1> 0:dieable, 1:enable\nvow_monitor_sta = <STA num>\nvow_show_sta = <STA num>\nvow_monitor_bss = <BSS num>\nvow_monitor_mbss = <MBSS num>\nvow_show_mbss = <MBSS num>\nvow_avg_num = <average num> sec\n======== RED ===========\nvow_set_red_en = <0/1> 0:disable, 1:enable\nvow_set_red_show_sta = <STA num>\nvow_set_red_tar_delay = <tarDelay> us\n======== WATF ===========\nvow_watf_en = <0/1> 0:disable, 1:enable\nvow_watf_q = <level>-<quantum> unit 256us\nvow_watf_add_entry = <level>-<Addr>\nvow_watf_del_entry = <Addr>\n"
                         + (uint)*(byte *)(param_2 + 0x39) * 0x5834 + param_1 + 0x101);
        cVar4 = *(char *)(param_1 + 0x286285);
      }
    }
    if (cVar4 == '\0') {
      MgtMacHeaderInit(param_1,auStack_38,0xd,0,param_2 + 0x3b,param_1 + 0x794b5b,param_2 + 0x3b);
    }
    *(short *)((int)param_2 + 0x629) = *(short *)((int)param_2 + 0x629) + 1;
    local_42 = 8;
    local_41 = 0;
    MakeOutgoingFrame(local_40,&local_3c,0x18,auStack_38,1,&local_42,1,&local_41,2,
                      (short *)((int)param_2 + 0x629),0xffffffff);
    if (((char)param_2[0x18a] == '\0') && (RTMPSetTimer(param_2 + 0x170,1000), -1 < DebugLevel)) {
      printk("[PMF]%s -- SAQueryTimer\n","PMF_MlmeSAQueryReq");
    }
    *(undefined1 *)(param_2 + 0x18a) = 2;
    RTMPSetTimer(param_2 + 0x17d,200);
    MiniportMMRequest(param_1,0xd,local_40,local_3c);
    os_free_mem(local_40);
    if (DebugLevel < 0) {
      return;
    }
    uVar2 = *(undefined1 *)((int)param_2 + 0xee);
    uVar1 = (undefined1)param_2[0x3b];
    pcVar3 = "[PMF]%s - Send SA Query Request to STA(%02x:%02x:%02x:%02x:%02x:%02x)\n";
  }
  printk(pcVar3,"PMF_MlmeSAQueryReq",uVar1,*(undefined1 *)((int)param_2 + 0xed),uVar2,
         *(undefined1 *)((int)param_2 + 0xef),(char)param_2[0x3c],
         *(undefined1 *)((int)param_2 + 0xf1));
  return;
}

