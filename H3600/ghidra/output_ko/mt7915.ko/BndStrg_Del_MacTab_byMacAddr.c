// module: mt7915.ko
// function: BndStrg_Del_MacTab_byMacAddr @ 0x9cb04
// size: 556 bytes
//

undefined4 BndStrg_Del_MacTab_byMacAddr(int param_1,undefined4 param_2,undefined1 *param_3)

{
  int *piVar1;
  int iVar2;
  undefined2 local_42;
  undefined4 local_40;
  undefined4 local_3c;
  undefined1 auStack_38 [28];
  
  local_40 = 0;
  local_3c = 0;
  if (param_3 == (undefined1 *)0x0) {
    if (-1 < DebugLevel) {
      printk("Del_MacTab_byMacAddr pucStaMac is null.\n");
    }
  }
  else {
    piVar1 = (int *)MacTableLookup(param_1,param_3);
    if (piVar1 == (int *)0x0) {
      if (-1 < DebugLevel) {
        printk("the STA is not in MacTab mac=%02x:%02x:%02x:%02x:%02x:%02x\n",*param_3,param_3[1],
               param_3[2],param_3[3],param_3[4],param_3[5]);
      }
    }
    else {
      if (2 < DebugLevel) {
        printk("BandSteering kick out 2.4G sta\nmac=%02x:%02x:%02x:%02x:%02x:%02x\n",
               (char)piVar1[0x3b],*(undefined1 *)((int)piVar1 + 0xed),
               *(undefined1 *)((int)piVar1 + 0xee),*(undefined1 *)((int)piVar1 + 0xef),
               (char)piVar1[0x3c],*(undefined1 *)((int)piVar1 + 0xf1));
      }
      local_42 = 1;
      iVar2 = os_alloc_mem(param_1,&local_40,0x900);
      if (iVar2 == 0) {
        iVar2 = param_1 + (uint)*(byte *)((int)piVar1 + 0xe5) * 0x5834;
        MgtMacHeaderInit(param_1,auStack_38,0xc,0,piVar1 + 0x3b,
                         "======== Badnode detector =============\nvow_bn_en = <0/1> 0:dieable, 1:enable\nvow_bn_mon_period = <period> ms\nvow_bn_fallback_th = <count>\nvow_bn_per_th = <TX PER>\n======== Airtime counter test =============\nvow_counter_test = <0/1> 0:dieable, 1:enable\nvow_counter_test_period = <period> ms\nvow_counter_test_band = <band>\nvow_counter_test_avgcnt = <average num> sec\nvow_counter_test_target = <wlanidx>\n======== DVT =============\nvow_dvt_en = <0/1> 0:dieable, 1:enable\nvow_monitor_sta = <STA num>\nvow_show_sta = <STA num>\nvow_monitor_bss = <BSS num>\nvow_monitor_mbss = <MBSS num>\nvow_show_mbss = <MBSS num>\nvow_avg_num = <average num> sec\n======== RED ===========\nvow_set_red_en = <0/1> 0:disable, 1:enable\nvow_set_red_show_sta = <STA num>\nvow_set_red_tar_delay = <tarDelay> us\n======== WATF ===========\nvow_watf_en = <0/1> 0:disable, 1:enable\nvow_watf_q = <level>-<quantum> unit 256us\nvow_watf_add_entry = <level>-<Addr>\nvow_watf_del_entry = <Addr>\n"
                         + iVar2 + 0xfb,
                         "======== Badnode detector =============\nvow_bn_en = <0/1> 0:dieable, 1:enable\nvow_bn_mon_period = <period> ms\nvow_bn_fallback_th = <count>\nvow_bn_per_th = <TX PER>\n======== Airtime counter test =============\nvow_counter_test = <0/1> 0:dieable, 1:enable\nvow_counter_test_period = <period> ms\nvow_counter_test_band = <band>\nvow_counter_test_avgcnt = <average num> sec\nvow_counter_test_target = <wlanidx>\n======== DVT =============\nvow_dvt_en = <0/1> 0:dieable, 1:enable\nvow_monitor_sta = <STA num>\nvow_show_sta = <STA num>\nvow_monitor_bss = <BSS num>\nvow_monitor_mbss = <MBSS num>\nvow_show_mbss = <MBSS num>\nvow_avg_num = <average num> sec\n======== RED ===========\nvow_set_red_en = <0/1> 0:disable, 1:enable\nvow_set_red_show_sta = <STA num>\nvow_set_red_tar_delay = <tarDelay> us\n======== WATF ===========\nvow_watf_en = <0/1> 0:disable, 1:enable\nvow_watf_q = <level>-<quantum> unit 256us\nvow_watf_add_entry = <level>-<Addr>\nvow_watf_del_entry = <Addr>\n"
                         + iVar2 + 0x101);
        MakeOutgoingFrame(local_40,&local_3c,0x18,auStack_38,2,&local_42,0xffffffff);
        MiniportMMRequest(param_1,0,local_40,local_3c);
        os_free_mem(local_40);
        if (*piVar1 == 0x20001) {
          __ZTE_STA_Assoc_Process
                    (param_1,0x11,0,0,local_42,0,piVar1,"BndStrg_Del_MacTab_byMacAddr",0x3da);
        }
        MacTableDeleteEntry(param_1,(short)piVar1[0x38],piVar1 + 0x3b);
        return 1;
      }
      if (2 < DebugLevel) {
        printk(" MlmeAllocateMemory fail  ..\nwe wont kick off any STA this time in 2G");
      }
    }
  }
  return 0;
}

