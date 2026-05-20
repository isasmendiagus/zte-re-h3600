// module: mt7915.ko
// function: PMF_PerformTxFrameAction @ 0x21aa88
// size: 536 bytes
//

undefined4
PMF_PerformTxFrameAction(int param_1,int param_2,int param_3,int param_4,undefined1 *param_5)

{
  int iVar1;
  int iVar2;
  char *pcVar3;
  
  iVar1 = hc_get_hif_type(*(undefined4 *)(param_1 + 0xa797a0));
  if (iVar1 != 2) {
    return 1;
  }
  if (*(char *)(param_1 + 0x286285) == '\x01') {
    iVar1 = MacTableLookup(param_1,param_2 + 4);
    if (*(char *)(param_1 + 0x286285) == '\0') goto LAB_0021ab90;
LAB_0021aba4:
    *param_5 = 0;
    if ((iVar1 != 0) &&
       (*(char *)(param_1 + (uint)*(ushort *)(iVar1 + 0xe0) * 0x620 + 0x2f762) != '\x01')) {
      return 1;
    }
  }
  else {
    if (*(char *)(param_1 + 0x286285) == '\0') {
LAB_0021ab90:
      iVar1 = MacTableLookup2(param_1,param_2 + 4,0);
      goto LAB_0021aba4;
    }
    iVar1 = 0;
    *param_5 = 0;
  }
  param_3 = param_3 - param_4;
  iVar2 = PMF_RobustFrameClassify(param_2,param_2 + 0x18,param_3 + -0x18,iVar1,0);
  if (iVar2 == 4) {
    *param_5 = 1;
    *(byte *)(param_2 + 1) = *(byte *)(param_2 + 1) | 0x40;
    return 1;
  }
  if (iVar2 != 5) {
    return 1;
  }
  if (*(char *)(param_1 + 0x286285) == '\x01') {
    if ((*(byte *)(param_2 + 4) & 1) == 0) {
      if (iVar1 != 0) {
        pcVar3 = "======== Badnode detector =============\nvow_bn_en = <0/1> 0:dieable, 1:enable\nvow_bn_mon_period = <period> ms\nvow_bn_fallback_th = <count>\nvow_bn_per_th = <TX PER>\n======== Airtime counter test =============\nvow_counter_test = <0/1> 0:dieable, 1:enable\nvow_counter_test_period = <period> ms\nvow_counter_test_band = <band>\nvow_counter_test_avgcnt = <average num> sec\nvow_counter_test_target = <wlanidx>\n======== DVT =============\nvow_dvt_en = <0/1> 0:dieable, 1:enable\nvow_monitor_sta = <STA num>\nvow_show_sta = <STA num>\nvow_monitor_bss = <BSS num>\nvow_monitor_mbss = <MBSS num>\nvow_show_mbss = <MBSS num>\nvow_avg_num = <average num> sec\n======== RED ===========\nvow_set_red_en = <0/1> 0:disable, 1:enable\nvow_set_red_show_sta = <STA num>\nvow_set_red_tar_delay = <tarDelay> us\n======== WATF ===========\nvow_watf_en = <0/1> 0:disable, 1:enable\nvow_watf_q = <level>-<quantum> unit 256us\nvow_watf_add_entry = <level>-<Addr>\nvow_watf_del_entry = <Addr>\n"
                 + (uint)*(byte *)(iVar1 + 0xe5) * 0x5834 + param_1 + 0xe0;
        goto LAB_0021ac10;
      }
LAB_0021ac78:
      pcVar3 = "Group%d airtime token: max %d(0x%08X), min %d(0x%08X)\n" + param_1 + 4;
      PMF_AddMMIE(pcVar3,param_2,param_3);
      if (pcVar3 == (char *)0x0) goto LAB_0021ab3c;
    }
    else {
      pcVar3 = (char *)wdev_search_by_address(param_1,param_2 + 10);
LAB_0021ac10:
      if (pcVar3 == (char *)0x0) goto LAB_0021ac78;
      pcVar3 = pcVar3 + 0x40c;
      PMF_AddMMIE(pcVar3,param_2,param_3);
    }
    if ((*(uint *)(pcVar3 + 7) & 0x200) == 0) {
      *param_5 = 3;
      goto LAB_0021ab48;
    }
  }
  else {
    PMF_AddMMIE(0,param_2,param_3);
  }
LAB_0021ab3c:
  *param_5 = 2;
LAB_0021ab48:
  if (0 < DebugLevel) {
    printk("%s, PMF GROUP ROBUST\n","PMF_PerformTxFrameAction");
  }
  return 1;
}

