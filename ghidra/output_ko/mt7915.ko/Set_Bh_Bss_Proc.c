// module: mt7915.ko
// function: Set_Bh_Bss_Proc @ 0x2b5d4
// size: 252 bytes
//

undefined4 Set_Bh_Bss_Proc(int *param_1,undefined4 param_2)

{
  int iVar1;
  char cVar2;
  undefined4 uVar3;
  int iVar4;
  int iVar5;
  uint uVar6;
  
  cVar2 = os_str_tol(param_2,0,10);
  if ((*(int *)(*param_1 + 0x38) - 0x100U & 0xfffffeff) == 0) {
    uVar6 = (uint)*(byte *)(*param_1 + 0x3c);
    iVar5 = uVar6 * 0x5834;
    iVar4 = HcGetBandByWdev((char *)((int)param_1 +
                                    (int)(
                                         "======== Badnode detector =============\nvow_bn_en = <0/1> 0:dieable, 1:enable\nvow_bn_mon_period = <period> ms\nvow_bn_fallback_th = <count>\nvow_bn_per_th = <TX PER>\n======== Airtime counter test =============\nvow_counter_test = <0/1> 0:dieable, 1:enable\nvow_counter_test_period = <period> ms\nvow_counter_test_band = <band>\nvow_counter_test_avgcnt = <average num> sec\nvow_counter_test_target = <wlanidx>\n======== DVT =============\nvow_dvt_en = <0/1> 0:dieable, 1:enable\nvow_monitor_sta = <STA num>\nvow_show_sta = <STA num>\nvow_monitor_bss = <BSS num>\nvow_monitor_mbss = <MBSS num>\nvow_show_mbss = <MBSS num>\nvow_avg_num = <average num> sec\n======== RED ===========\nvow_set_red_en = <0/1> 0:disable, 1:enable\nvow_set_red_show_sta = <STA num>\nvow_set_red_tar_delay = <tarDelay> us\n======== WATF ===========\nvow_watf_en = <0/1> 0:disable, 1:enable\nvow_watf_q = <level>-<quantum> unit 256us\nvow_watf_add_entry = <level>-<Addr>\nvow_watf_del_entry = <Addr>\n"
                                         + iVar5 + 0xe0)));
    if (cVar2 == '\0') {
      *(byte *)((int)param_1 + iVar5 + 0x2bb1a5) = *(byte *)((int)param_1 + iVar5 + 0x2bb1a5) & 0xbf
      ;
      iVar1 = DebugLevel;
    }
    else {
      *(byte *)((int)param_1 + iVar5 + 0x2bb1a5) = *(byte *)((int)param_1 + iVar5 + 0x2bb1a5) | 0x40
      ;
      iVar1 = DebugLevel;
      param_1[(int)("mt_cmd_get_sta_tx_statistic" + iVar4)] =
           (int)param_1 +
           (int)(
                "======== Badnode detector =============\nvow_bn_en = <0/1> 0:dieable, 1:enable\nvow_bn_mon_period = <period> ms\nvow_bn_fallback_th = <count>\nvow_bn_per_th = <TX PER>\n======== Airtime counter test =============\nvow_counter_test = <0/1> 0:dieable, 1:enable\nvow_counter_test_period = <period> ms\nvow_counter_test_band = <band>\nvow_counter_test_avgcnt = <average num> sec\nvow_counter_test_target = <wlanidx>\n======== DVT =============\nvow_dvt_en = <0/1> 0:dieable, 1:enable\nvow_monitor_sta = <STA num>\nvow_show_sta = <STA num>\nvow_monitor_bss = <BSS num>\nvow_monitor_mbss = <MBSS num>\nvow_show_mbss = <MBSS num>\nvow_avg_num = <average num> sec\n======== RED ===========\nvow_set_red_en = <0/1> 0:disable, 1:enable\nvow_set_red_show_sta = <STA num>\nvow_set_red_tar_delay = <tarDelay> us\n======== WATF ===========\nvow_watf_en = <0/1> 0:disable, 1:enable\nvow_watf_q = <level>-<quantum> unit 256us\nvow_watf_add_entry = <level>-<Addr>\nvow_watf_del_entry = <Addr>\n"
                + iVar5 + 0xe0);
    }
    if (iVar1 < 1) {
      uVar3 = 1;
    }
    else {
      printk("%s %s bandIdx = %d ,DevOwnRole 0x%x\n","Set_Bh_Bss_Proc",
             param_1[uVar6 * 0x160d + 0xadc92],iVar4,
             *(undefined1 *)((int)param_1 + uVar6 * 0x5834 + 0x2bb1a5));
      uVar3 = 1;
    }
  }
  else {
    uVar3 = 0;
  }
  return uVar3;
}

