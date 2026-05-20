// module: mt7915.ko
// function: Set_AP_WmmCapable_Proc @ 0x2bb34
// size: 228 bytes
//

undefined4 Set_AP_WmmCapable_Proc(int *param_1,undefined4 param_2)

{
  char cVar1;
  int iVar2;
  int iVar3;
  
  iVar2 = *param_1;
  cVar1 = os_str_tol(param_2,0,10);
  iVar3 = *(int *)(iVar2 + 0x3c);
  if ((cVar1 != '\x01') && (cVar1 != '\0')) {
    return 0;
  }
  *(char *)(param_1 + iVar3 * 0x160d + 0xadec7) = cVar1;
  *(char *)((int)param_1 + *(int *)(iVar2 + 0x3c) * 0x5834 + 0x2bba7a) =
       (char)param_1[*(int *)(iVar2 + 0x3c) * 0x160d + 0xadec7];
  SetCommonHtVht(param_1,(char *)((int)param_1 +
                                 (int)(
                                      "======== Badnode detector =============\nvow_bn_en = <0/1> 0:dieable, 1:enable\nvow_bn_mon_period = <period> ms\nvow_bn_fallback_th = <count>\nvow_bn_per_th = <TX PER>\n======== Airtime counter test =============\nvow_counter_test = <0/1> 0:dieable, 1:enable\nvow_counter_test_period = <period> ms\nvow_counter_test_band = <band>\nvow_counter_test_avgcnt = <average num> sec\nvow_counter_test_target = <wlanidx>\n======== DVT =============\nvow_dvt_en = <0/1> 0:dieable, 1:enable\nvow_monitor_sta = <STA num>\nvow_show_sta = <STA num>\nvow_monitor_bss = <BSS num>\nvow_monitor_mbss = <MBSS num>\nvow_show_mbss = <MBSS num>\nvow_avg_num = <average num> sec\n======== RED ===========\nvow_set_red_en = <0/1> 0:disable, 1:enable\nvow_set_red_show_sta = <STA num>\nvow_set_red_tar_delay = <tarDelay> us\n======== WATF ===========\nvow_watf_en = <0/1> 0:disable, 1:enable\nvow_watf_q = <level>-<quantum> unit 256us\nvow_watf_add_entry = <level>-<Addr>\nvow_watf_del_entry = <Addr>\n"
                                      + iVar3 * 0x5834 + 0xe0)));
  if (DebugLevel < 3) {
    return 1;
  }
  printk("IF(ra%d) Set_WmmCapable_Proc::(bWmmCapable=%d)\n",*(undefined4 *)(iVar2 + 0x3c),
         (char)param_1[iVar3 * 0x160d + 0xadec7]);
  return 1;
}

