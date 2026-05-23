// module: mt7915.ko
// function: ZTE_AirMonitorWork @ 0x159fb0
// size: 324 bytes
//

void ZTE_AirMonitorWork(int param_1,int param_2,undefined4 param_3,undefined4 param_4)

{
  undefined4 uVar1;
  int iVar2;
  short sVar3;
  char *pcVar4;
  int iVar5;
  
  if (0 < DebugLevel) {
    printk("%s : band_idx=%d\n","ZTE_AirMonitorWork",param_2);
  }
  if (param_1 == 0) {
    return;
  }
  iVar5 = param_1 + param_2;
  pcVar4 = "======== Badnode detector =============\nvow_bn_en = <0/1> 0:dieable, 1:enable\nvow_bn_mon_period = <period> ms\nvow_bn_fallback_th = <count>\nvow_bn_per_th = <TX PER>\n======== Airtime counter test =============\nvow_counter_test = <0/1> 0:dieable, 1:enable\nvow_counter_test_period = <period> ms\nvow_counter_test_band = <band>\nvow_counter_test_avgcnt = <average num> sec\nvow_counter_test_target = <wlanidx>\n======== DVT =============\nvow_dvt_en = <0/1> 0:dieable, 1:enable\nvow_monitor_sta = <STA num>\nvow_show_sta = <STA num>\nvow_monitor_bss = <BSS num>\nvow_monitor_mbss = <MBSS num>\nvow_show_mbss = <MBSS num>\nvow_avg_num = <average num> sec\n======== RED ===========\nvow_set_red_en = <0/1> 0:disable, 1:enable\nvow_set_red_show_sta = <STA num>\nvow_set_red_tar_delay = <tarDelay> us\n======== WATF ===========\nvow_watf_en = <0/1> 0:disable, 1:enable\nvow_watf_q = <level>-<quantum> unit 256us\nvow_watf_add_entry = <level>-<Addr>\nvow_watf_del_entry = <Addr>\n"
           + (uint)*(byte *)(iVar5 + 0xa376ad) * 0x5834 + param_1 + 0xe0;
  if (*(char *)(iVar5 + 0xa376a5) == '\x01') {
    uVar1 = get_scan_ctrl_by_wdev(param_1,pcVar4);
    iVar2 = NextChannel(param_1,uVar1,*(undefined1 *)(iVar5 + 0xa376a7),pcVar4);
    if (iVar2 != 0) {
      wlan_operate_scan(pcVar4,iVar2);
      *(char *)(iVar5 + 0xa376a7) = (char)iVar2;
      sVar3 = *(short *)(param_1 + (param_2 + 0x51bb90) * 2);
      if (sVar3 == 0) {
        sVar3 = 200;
      }
      RTMPSetTimer(param_1 + param_2 * 0x34 + 0xa376b0,sVar3);
      return;
    }
  }
  ZTE_ReportSTARssiInfo(param_1,param_2);
  ZTE_Set_Enable_Air_Monitor_Proc(param_1,&_LC148,param_2);
  if (*(char *)(iVar5 + 0xa376ab) == *(char *)(iVar5 + 0xa376a9)) {
    return;
  }
  scan_ch_restore(param_1,1,pcVar4,param_4);
  return;
}

