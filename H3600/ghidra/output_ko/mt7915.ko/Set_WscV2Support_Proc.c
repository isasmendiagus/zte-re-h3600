// module: mt7915.ko
// function: Set_WscV2Support_Proc @ 0x2bd00
// size: 376 bytes
//

undefined4 Set_WscV2Support_Proc(int *param_1,undefined4 param_2)

{
  char cVar1;
  int iVar2;
  int iVar3;
  
  iVar3 = *param_1;
  cVar1 = os_str_tol(param_2,0,10);
  if (cVar1 == '\0') {
    *(undefined1 *)((int)param_1 + *(int *)(iVar3 + 0x3c) * 0x5834 + 0x2bb05d) = 0;
    WscInit(param_1,0,*(undefined1 *)(iVar3 + 0x3c));
    goto LAB_0002bd54;
  }
  *(undefined1 *)((int)param_1 + *(int *)(iVar3 + 0x3c) * 0x5834 + 0x2bb05d) = 1;
  iVar2 = *(int *)(iVar3 + 0x3c);
  if (((param_1[iVar2 * 0x160d + 0xadcef] & 0x1eU) == 0) ||
     (0x1f < (uint)param_1[iVar2 * 0x160d + 0xadcef])) {
    if (*(char *)((int)param_1 + iVar2 * 0x5834 + 0x2bb2d2) != '\0') goto LAB_0002bdd8;
    WscOnOff(param_1,*(undefined1 *)((int)param_1 + iVar2 * 0x5834 + 0x2b7256));
  }
  else {
LAB_0002bdd8:
    WscOnOff(param_1,*(undefined1 *)((int)param_1 + iVar2 * 0x5834 + 0x2b7256),1);
  }
  UpdateBeaconHandler(param_1,(char *)((int)param_1 +
                                      (int)(
                                           "======== Badnode detector =============\nvow_bn_en = <0/1> 0:dieable, 1:enable\nvow_bn_mon_period = <period> ms\nvow_bn_fallback_th = <count>\nvow_bn_per_th = <TX PER>\n======== Airtime counter test =============\nvow_counter_test = <0/1> 0:dieable, 1:enable\nvow_counter_test_period = <period> ms\nvow_counter_test_band = <band>\nvow_counter_test_avgcnt = <average num> sec\nvow_counter_test_target = <wlanidx>\n======== DVT =============\nvow_dvt_en = <0/1> 0:dieable, 1:enable\nvow_monitor_sta = <STA num>\nvow_show_sta = <STA num>\nvow_monitor_bss = <BSS num>\nvow_monitor_mbss = <MBSS num>\nvow_show_mbss = <MBSS num>\nvow_avg_num = <average num> sec\n======== RED ===========\nvow_set_red_en = <0/1> 0:disable, 1:enable\nvow_set_red_show_sta = <STA num>\nvow_set_red_tar_delay = <tarDelay> us\n======== WATF ===========\nvow_watf_en = <0/1> 0:disable, 1:enable\nvow_watf_q = <level>-<quantum> unit 256us\nvow_watf_add_entry = <level>-<Addr>\nvow_watf_del_entry = <Addr>\n"
                                           + iVar2 * 0x5834 + 0xe0)),2);
LAB_0002bd54:
  if (2 < DebugLevel) {
    printk("Set_WscV2Support_Proc::(bEnableWpsV2=%d)\n",
           *(undefined1 *)((int)param_1 + *(int *)(iVar3 + 0x3c) * 0x5834 + 0x2bb05d));
  }
  return 1;
}

