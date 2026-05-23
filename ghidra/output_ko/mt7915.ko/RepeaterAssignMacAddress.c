// module: mt7915.ko
// function: RepeaterAssignMacAddress @ 0x81914
// size: 636 bytes
//

undefined4 RepeaterAssignMacAddress(int param_1,int param_2,uint *param_3,uint *param_4)

{
  bool bVar1;
  int iVar2;
  undefined1 *__s1;
  int iVar3;
  int iVar4;
  char *pcVar5;
  uint uVar6;
  uint uVar7;
  undefined4 local_34;
  undefined2 local_30;
  uint local_2e;
  undefined2 local_2a;
  
  local_30 = (undefined2)param_3[1];
  local_34 = *param_3;
  if (param_2 == 1) {
    if (-1 < DebugLevel) {
      printk("todo !!!\n");
    }
  }
  else if (param_2 == 2) {
    __s1 = VENDOR_DEFINED_OUI_ADDR;
    iVar3 = 1;
    bVar1 = false;
    local_2e = local_34;
    local_2a = local_30;
    do {
      iVar4 = iVar3 + -1;
      iVar2 = memcmp(__s1,param_3,3);
      if (iVar2 == 0) {
        if (iVar4 == 2) break;
        uVar6 = (uint)(byte)"======== Badnode detector =============\nvow_bn_en = <0/1> 0:dieable, 1:enable\nvow_bn_mon_period = <period> ms\nvow_bn_fallback_th = <count>\nvow_bn_per_th = <TX PER>\n======== Airtime counter test =============\nvow_counter_test = <0/1> 0:dieable, 1:enable\nvow_counter_test_period = <period> ms\nvow_counter_test_band = <band>\nvow_counter_test_avgcnt = <average num> sec\nvow_counter_test_target = <wlanidx>\n======== DVT =============\nvow_dvt_en = <0/1> 0:dieable, 1:enable\nvow_monitor_sta = <STA num>\nvow_show_sta = <STA num>\nvow_monitor_bss = <BSS num>\nvow_monitor_mbss = <MBSS num>\nvow_show_mbss = <MBSS num>\nvow_avg_num = <average num> sec\n======== RED ===========\nvow_set_red_en = <0/1> 0:disable, 1:enable\nvow_set_red_show_sta = <STA num>\nvow_set_red_tar_delay = <tarDelay> us\n======== WATF ===========\nvow_watf_en = <0/1> 0:disable, 1:enable\nvow_watf_q = <level>-<quantum> unit 256us\nvow_watf_add_entry = <level>-<Addr>\nvow_watf_del_entry = <Addr>\n"
                            [param_1 + 0xda];
        local_2e = CONCAT13(local_2e._3_1_,*(undefined3 *)((int)__s1 + 3));
        iVar4 = iVar3;
        if (uVar6 == 0) goto LAB_000819b0;
        uVar7 = 0;
        pcVar5 = "======== Badnode detector =============\nvow_bn_en = <0/1> 0:dieable, 1:enable\nvow_bn_mon_period = <period> ms\nvow_bn_fallback_th = <count>\nvow_bn_per_th = <TX PER>\n======== Airtime counter test =============\nvow_counter_test = <0/1> 0:dieable, 1:enable\nvow_counter_test_period = <period> ms\nvow_counter_test_band = <band>\nvow_counter_test_avgcnt = <average num> sec\nvow_counter_test_target = <wlanidx>\n======== DVT =============\nvow_dvt_en = <0/1> 0:dieable, 1:enable\nvow_monitor_sta = <STA num>\nvow_show_sta = <STA num>\nvow_monitor_bss = <BSS num>\nvow_monitor_mbss = <MBSS num>\nvow_show_mbss = <MBSS num>\nvow_avg_num = <average num> sec\n======== RED ===========\nvow_set_red_en = <0/1> 0:disable, 1:enable\nvow_set_red_show_sta = <STA num>\nvow_set_red_tar_delay = <tarDelay> us\n======== WATF ===========\nvow_watf_en = <0/1> 0:disable, 1:enable\nvow_watf_q = <level>-<quantum> unit 256us\nvow_watf_add_entry = <level>-<Addr>\nvow_watf_del_entry = <Addr>\n"
                 + param_1 + 0xfb;
        while( true ) {
          iVar2 = memcmp(pcVar5,&local_2e,6);
          pcVar5 = pcVar5 + 0x5834;
          if (iVar2 == 0) break;
          uVar7 = uVar7 + 1;
          if (uVar7 == uVar6) goto LAB_000819b0;
        }
        if ((int)uVar6 <= (int)uVar7) goto LAB_000819b0;
        bVar1 = true;
      }
      else if (bVar1) {
        uVar6 = (uint)(byte)"======== Badnode detector =============\nvow_bn_en = <0/1> 0:dieable, 1:enable\nvow_bn_mon_period = <period> ms\nvow_bn_fallback_th = <count>\nvow_bn_per_th = <TX PER>\n======== Airtime counter test =============\nvow_counter_test = <0/1> 0:dieable, 1:enable\nvow_counter_test_period = <period> ms\nvow_counter_test_band = <band>\nvow_counter_test_avgcnt = <average num> sec\nvow_counter_test_target = <wlanidx>\n======== DVT =============\nvow_dvt_en = <0/1> 0:dieable, 1:enable\nvow_monitor_sta = <STA num>\nvow_show_sta = <STA num>\nvow_monitor_bss = <BSS num>\nvow_monitor_mbss = <MBSS num>\nvow_show_mbss = <MBSS num>\nvow_avg_num = <average num> sec\n======== RED ===========\nvow_set_red_en = <0/1> 0:disable, 1:enable\nvow_set_red_show_sta = <STA num>\nvow_set_red_tar_delay = <tarDelay> us\n======== WATF ===========\nvow_watf_en = <0/1> 0:disable, 1:enable\nvow_watf_q = <level>-<quantum> unit 256us\nvow_watf_add_entry = <level>-<Addr>\nvow_watf_del_entry = <Addr>\n"
                            [param_1 + 0xda];
        local_2e = CONCAT13(local_2e._3_1_,*(undefined3 *)__s1);
        if (uVar6 == 0) goto LAB_000819b0;
        uVar7 = 0;
        pcVar5 = "======== Badnode detector =============\nvow_bn_en = <0/1> 0:dieable, 1:enable\nvow_bn_mon_period = <period> ms\nvow_bn_fallback_th = <count>\nvow_bn_per_th = <TX PER>\n======== Airtime counter test =============\nvow_counter_test = <0/1> 0:dieable, 1:enable\nvow_counter_test_period = <period> ms\nvow_counter_test_band = <band>\nvow_counter_test_avgcnt = <average num> sec\nvow_counter_test_target = <wlanidx>\n======== DVT =============\nvow_dvt_en = <0/1> 0:dieable, 1:enable\nvow_monitor_sta = <STA num>\nvow_show_sta = <STA num>\nvow_monitor_bss = <BSS num>\nvow_monitor_mbss = <MBSS num>\nvow_show_mbss = <MBSS num>\nvow_avg_num = <average num> sec\n======== RED ===========\nvow_set_red_en = <0/1> 0:disable, 1:enable\nvow_set_red_show_sta = <STA num>\nvow_set_red_tar_delay = <tarDelay> us\n======== WATF ===========\nvow_watf_en = <0/1> 0:disable, 1:enable\nvow_watf_q = <level>-<quantum> unit 256us\nvow_watf_add_entry = <level>-<Addr>\nvow_watf_del_entry = <Addr>\n"
                 + param_1 + 0xfb;
        while( true ) {
          iVar2 = memcmp(pcVar5,&local_2e,6);
          pcVar5 = pcVar5 + 0x5834;
          if (iVar2 == 0) break;
          uVar7 = uVar7 + 1;
          if (uVar7 == uVar6) goto LAB_000819b0;
        }
        if ((int)uVar6 <= (int)uVar7) goto LAB_000819b0;
      }
      else {
        bVar1 = false;
      }
      __s1 = (undefined1 *)((int)__s1 + 3);
      iVar3 = iVar3 + 1;
    } while (iVar3 != 4);
    iVar4 = 0;
LAB_000819b0:
    local_34 = CONCAT13(local_34._3_1_,*(undefined3 *)(VENDOR_DEFINED_OUI_ADDR + iVar4 * 3));
  }
  iVar3 = RTMPLookupRepeaterCliEntry_NoLock(param_1,0,&local_34,1);
  if (iVar3 != 0) {
    _raw_spin_unlock_bh(&DAT_00367914 + param_1);
    if (-1 < DebugLevel) {
      printk("ReptCLI duplicate Insert %02x:%02x:%02x:%02x:%02x:%02x !\n",local_34 & 0xff,
             local_34._1_1_,local_34._2_1_,local_34 >> 0x18,(undefined1)local_30,local_30._1_1_);
    }
    return 0;
  }
  *param_4 = local_34;
  *(undefined2 *)(param_4 + 1) = local_30;
  return 1;
}

