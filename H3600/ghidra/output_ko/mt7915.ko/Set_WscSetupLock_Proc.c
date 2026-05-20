// module: mt7915.ko
// function: Set_WscSetupLock_Proc @ 0x32594
// size: 392 bytes
//

undefined4 Set_WscSetupLock_Proc(int *param_1,undefined4 param_2)

{
  byte bVar1;
  int iVar2;
  int iVar3;
  byte local_19;
  
  iVar3 = *param_1;
  bVar1 = os_str_tol(param_2,0,10);
  iVar2 = *(int *)(iVar3 + 0x3c);
  if (bVar1 == 0) {
    *(undefined1 *)((int)param_1 + iVar2 * 0x5834 + 0x2bb106) = 0;
    local_19 = bVar1;
    if ((char)param_1[iVar2 * 0x160d + 0xaec33] != '\0') {
      RTMPCancelTimer(param_1 + iVar2 * 0x160d + 0xaec26,&local_19);
    }
    WscSetupLockTimeout(0,param_1 + iVar2 * 0x160d + 0xae14b,0,0);
  }
  else {
    *(undefined1 *)((int)param_1 + iVar2 * 0x5834 + 0x2bb105) = 1;
    WscBuildBeaconIE(param_1,(char)param_1[iVar2 * 0x160d + 0xae14d],0,0,0,
                     *(undefined1 *)(iVar3 + 0x3c),0,0,0);
    WscBuildProbeRespIE(param_1,3,(char)param_1[iVar2 * 0x160d + 0xae14d],0,0,0,
                        *(undefined1 *)(iVar3 + 0x3c),0,0,0);
    UpdateBeaconHandler(param_1,(char *)((int)param_1 +
                                        (int)(
                                             "======== Badnode detector =============\nvow_bn_en = <0/1> 0:dieable, 1:enable\nvow_bn_mon_period = <period> ms\nvow_bn_fallback_th = <count>\nvow_bn_per_th = <TX PER>\n======== Airtime counter test =============\nvow_counter_test = <0/1> 0:dieable, 1:enable\nvow_counter_test_period = <period> ms\nvow_counter_test_band = <band>\nvow_counter_test_avgcnt = <average num> sec\nvow_counter_test_target = <wlanidx>\n======== DVT =============\nvow_dvt_en = <0/1> 0:dieable, 1:enable\nvow_monitor_sta = <STA num>\nvow_show_sta = <STA num>\nvow_monitor_bss = <BSS num>\nvow_monitor_mbss = <MBSS num>\nvow_show_mbss = <MBSS num>\nvow_avg_num = <average num> sec\n======== RED ===========\nvow_set_red_en = <0/1> 0:disable, 1:enable\nvow_set_red_show_sta = <STA num>\nvow_set_red_tar_delay = <tarDelay> us\n======== WATF ===========\nvow_watf_en = <0/1> 0:disable, 1:enable\nvow_watf_q = <level>-<quantum> unit 256us\nvow_watf_add_entry = <level>-<Addr>\nvow_watf_del_entry = <Addr>\n"
                                             + iVar2 * 0x5834 + 0xe0)),2);
  }
  if (2 < DebugLevel) {
    printk("Set_WscSetupLock_Proc::(bSetupLock=%d)\n",
           *(undefined1 *)((int)param_1 + *(int *)(iVar3 + 0x3c) * 0x5834 + 0x2bb105));
  }
  return 1;
}

