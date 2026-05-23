// module: mt7915.ko
// function: Dot11HCntDownTimeoutAction @ 0x10117c
// size: 576 bytes
//

undefined4 Dot11HCntDownTimeoutAction(int param_1,int param_2)

{
  bool bVar1;
  int iVar2;
  undefined4 uVar3;
  int iVar4;
  char *pcVar5;
  char *pcVar6;
  undefined1 local_c4;
  undefined4 local_c3;
  undefined4 local_bf;
  undefined4 local_bb;
  undefined4 local_b7;
  undefined1 local_9c;
  undefined1 local_9b;
  undefined1 local_9a;
  undefined1 local_99;
  undefined1 local_98;
  undefined1 local_97;
  
  pcVar6 = "======== Badnode detector =============\nvow_bn_en = <0/1> 0:dieable, 1:enable\nvow_bn_mon_period = <period> ms\nvow_bn_fallback_th = <count>\nvow_bn_per_th = <TX PER>\n======== Airtime counter test =============\nvow_counter_test = <0/1> 0:dieable, 1:enable\nvow_counter_test_period = <period> ms\nvow_counter_test_band = <band>\nvow_counter_test_avgcnt = <average num> sec\nvow_counter_test_target = <wlanidx>\n======== DVT =============\nvow_dvt_en = <0/1> 0:dieable, 1:enable\nvow_monitor_sta = <STA num>\nvow_show_sta = <STA num>\nvow_monitor_bss = <BSS num>\nvow_monitor_mbss = <MBSS num>\nvow_show_mbss = <MBSS num>\nvow_avg_num = <average num> sec\n======== RED ===========\nvow_set_red_en = <0/1> 0:disable, 1:enable\nvow_set_red_show_sta = <STA num>\nvow_set_red_tar_delay = <tarDelay> us\n======== WATF ===========\nvow_watf_en = <0/1> 0:disable, 1:enable\nvow_watf_q = <level>-<quantum> unit 256us\nvow_watf_add_entry = <level>-<Addr>\nvow_watf_del_entry = <Addr>\n"
           + param_1 + 0xe0;
  iVar2 = HcGetBandByWdev(pcVar6);
  iVar4 = iVar2 * 0xaf5d8 + param_1;
  local_c4 = 0x29;
  local_c3 = *(undefined4 *)(iVar4 + 0x82929a);
  local_bb = *(undefined4 *)(iVar4 + 0x8292a2);
  local_bf = *(undefined4 *)(iVar4 + 0x82929e);
  local_b7 = *(undefined4 *)(iVar4 + 0x8292a6);
  bVar1 = **(byte **)(param_2 + 4) < 0x20;
  pcVar5 = pcVar6;
  if (bVar1) {
    pcVar5 = "======== Badnode detector =============\nvow_bn_en = <0/1> 0:dieable, 1:enable\nvow_bn_mon_period = <period> ms\nvow_bn_fallback_th = <count>\nvow_bn_per_th = <TX PER>\n======== Airtime counter test =============\nvow_counter_test = <0/1> 0:dieable, 1:enable\nvow_counter_test_period = <period> ms\nvow_counter_test_band = <band>\nvow_counter_test_avgcnt = <average num> sec\nvow_counter_test_target = <wlanidx>\n======== DVT =============\nvow_dvt_en = <0/1> 0:dieable, 1:enable\nvow_monitor_sta = <STA num>\nvow_show_sta = <STA num>\nvow_monitor_bss = <BSS num>\nvow_monitor_mbss = <MBSS num>\nvow_show_mbss = <MBSS num>\nvow_avg_num = <average num> sec\n======== RED ===========\nvow_set_red_en = <0/1> 0:disable, 1:enable\nvow_set_red_show_sta = <STA num>\nvow_set_red_tar_delay = <tarDelay> us\n======== WATF ===========\nvow_watf_en = <0/1> 0:disable, 1:enable\nvow_watf_q = <level>-<quantum> unit 256us\nvow_watf_add_entry = <level>-<Addr>\nvow_watf_del_entry = <Addr>\n"
             + (uint)**(byte **)(param_2 + 4) * 0x5834 + param_1 + 0xe0;
  }
  if ((pcVar5 != (char *)0x0) && (iVar4 = *(int *)(pcVar5 + 0x3fe4), iVar4 != 0)) {
    DedicatedZeroWaitStop(param_1,0);
    *(undefined1 *)(iVar4 + 4) = 2;
    APStop(param_1,pcVar5,bVar1);
    iVar4 = DfsStopWifiCheck(param_1,pcVar5);
    if (iVar4 == 0) {
      APStartUp(param_1,pcVar5,bVar1);
      if (*(char *)(param_1 + 0x79504d) == '\0') {
        MtCmdSetDfsTxStart(param_1);
      }
      else {
        uVar3 = HcGetBandByWdev(pcVar5);
        MtCmdSetDfsTxStart(param_1,uVar3);
      }
      DfsSetCacRemainingTime(param_1,pcVar5);
      DfsReportCollision(param_1);
      if ((*(ushort *)(pcVar5 + 0x18) & 0xb1) == 0) {
        uVar3 = 1;
      }
      else {
        uVar3 = 2;
      }
      local_9c = HcGetChannelByRf(param_1,uVar3);
      local_9b = wlan_config_get_ht_bw(pcVar6);
      local_9a = wlan_config_get_vht_bw(pcVar6);
      local_99 = *(undefined1 *)(param_1 + 0x795075);
      local_98 = GetCountryRegionFromCountryCode(param_1 + 0x794c31);
      local_97 = "SetPartProfileParameters"[param_1 + 0x18] == 'D';
      RtmpOSWrielessEventSend(*(undefined4 *)(param_1 + 4),1,0x955,0,&local_c4,0xa4);
    }
    else if (0 < DebugLevel) {
      printk("[%s] Stop AP Startup\n","Dot11HCntDownTimeoutAction");
    }
  }
  (&DAT_0036b830)[param_1] = 0;
  if ((&DAT_0036b844)[param_1] != '\0') {
    complete(&DAT_0036b834 + param_1);
    iVar2 = HcGetAutoChCtrlbyBandIdx(param_1,iVar2);
    if (iVar2 != 0) {
      *(undefined4 *)(iVar2 + 0x58) = 0;
    }
  }
  return 0;
}

