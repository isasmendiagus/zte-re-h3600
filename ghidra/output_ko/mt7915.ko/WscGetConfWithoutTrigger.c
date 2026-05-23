// module: mt7915.ko
// function: WscGetConfWithoutTrigger @ 0x1eb114
// size: 616 bytes
//

undefined4 WscGetConfWithoutTrigger(int param_1,int *param_2,int param_3)

{
  byte bVar1;
  int iVar2;
  uint uVar3;
  int iVar4;
  undefined4 uVar5;
  char *pcVar6;
  uint uVar7;
  
  bVar1 = *(byte *)(param_2 + 0x715);
  uVar3 = hc_get_chip_bcn_max_num(*(undefined4 *)(param_1 + 0xa797a0));
  uVar7 = bVar1 & 0xf;
  if (uVar7 < uVar3) {
    iVar4 = uVar7 * 0x5834;
    pcVar6 = "======== Badnode detector =============\nvow_bn_en = <0/1> 0:dieable, 1:enable\nvow_bn_mon_period = <period> ms\nvow_bn_fallback_th = <count>\nvow_bn_per_th = <TX PER>\n======== Airtime counter test =============\nvow_counter_test = <0/1> 0:dieable, 1:enable\nvow_counter_test_period = <period> ms\nvow_counter_test_band = <band>\nvow_counter_test_avgcnt = <average num> sec\nvow_counter_test_target = <wlanidx>\n======== DVT =============\nvow_dvt_en = <0/1> 0:dieable, 1:enable\nvow_monitor_sta = <STA num>\nvow_show_sta = <STA num>\nvow_monitor_bss = <BSS num>\nvow_monitor_mbss = <MBSS num>\nvow_show_mbss = <MBSS num>\nvow_avg_num = <average num> sec\n======== RED ===========\nvow_set_red_en = <0/1> 0:disable, 1:enable\nvow_set_red_show_sta = <STA num>\nvow_set_red_tar_delay = <tarDelay> us\n======== WATF ===========\nvow_watf_en = <0/1> 0:disable, 1:enable\nvow_watf_q = <level>-<quantum> unit 256us\nvow_watf_add_entry = <level>-<Addr>\nvow_watf_del_entry = <Addr>\n"
             + param_1 + iVar4 + 0xe0;
    if (pcVar6 != (char *)0x0) {
      if (*(int *)("Get_System_CapNode_Info" + param_1 + 4) == 0) {
        RtmpOSWrielessEventSend
                  (*(undefined4 *)
                    (
                    "======== Badnode detector =============\nvow_bn_en = <0/1> 0:dieable, 1:enable\nvow_bn_mon_period = <period> ms\nvow_bn_fallback_th = <count>\nvow_bn_per_th = <TX PER>\n======== Airtime counter test =============\nvow_counter_test = <0/1> 0:dieable, 1:enable\nvow_counter_test_period = <period> ms\nvow_counter_test_band = <band>\nvow_counter_test_avgcnt = <average num> sec\nvow_counter_test_target = <wlanidx>\n======== DVT =============\nvow_dvt_en = <0/1> 0:dieable, 1:enable\nvow_monitor_sta = <STA num>\nvow_show_sta = <STA num>\nvow_monitor_bss = <BSS num>\nvow_monitor_mbss = <MBSS num>\nvow_show_mbss = <MBSS num>\nvow_avg_num = <average num> sec\n======== RED ===========\nvow_set_red_en = <0/1> 0:disable, 1:enable\nvow_set_red_show_sta = <STA num>\nvow_set_red_tar_delay = <tarDelay> us\n======== WATF ===========\nvow_watf_en = <0/1> 0:disable, 1:enable\nvow_watf_q = <level>-<quantum> unit 256us\nvow_watf_add_entry = <level>-<Addr>\nvow_watf_del_entry = <Addr>\n"
                    + param_1 + iVar4 + 0xe0),1,0x19,0,0,0);
      }
      else {
        RtmpOSWrielessEventSend
                  (*(undefined4 *)
                    (
                    "======== Badnode detector =============\nvow_bn_en = <0/1> 0:dieable, 1:enable\nvow_bn_mon_period = <period> ms\nvow_bn_fallback_th = <count>\nvow_bn_per_th = <TX PER>\n======== Airtime counter test =============\nvow_counter_test = <0/1> 0:dieable, 1:enable\nvow_counter_test_period = <period> ms\nvow_counter_test_band = <band>\nvow_counter_test_avgcnt = <average num> sec\nvow_counter_test_target = <wlanidx>\n======== DVT =============\nvow_dvt_en = <0/1> 0:dieable, 1:enable\nvow_monitor_sta = <STA num>\nvow_show_sta = <STA num>\nvow_monitor_bss = <BSS num>\nvow_monitor_mbss = <MBSS num>\nvow_show_mbss = <MBSS num>\nvow_avg_num = <average num> sec\n======== RED ===========\nvow_set_red_en = <0/1> 0:disable, 1:enable\nvow_set_red_show_sta = <STA num>\nvow_set_red_tar_delay = <tarDelay> us\n======== WATF ===========\nvow_watf_en = <0/1> 0:disable, 1:enable\nvow_watf_q = <level>-<quantum> unit 256us\nvow_watf_add_entry = <level>-<Addr>\nvow_watf_del_entry = <Addr>\n"
                    + param_1 + iVar4 + 0xe0),1,0x1c,0,0,0);
      }
    }
  }
  else {
    pcVar6 = (char *)0x0;
  }
  iVar2 = DebugLevel;
  iVar4 = param_2[2];
  if (*param_2 == 0) {
    *(undefined1 *)(param_2 + 0xa79) = 0;
    uVar5 = 0;
    if (2 < iVar2) {
      printk("WscGetConfForUpnp:: WPS is disabled.\n");
    }
  }
  else {
    if (param_3 != 0) {
      _WscStop(param_1,0,param_2,0);
    }
    if (param_2[1] == 1) {
      uVar5 = 0;
    }
    else {
      uVar5 = 4;
    }
    WscBuildBeaconIE(param_1,(char)iVar4,1,uVar5,*(undefined2 *)((int)param_2 + 10),
                     *(byte *)(param_2 + 0x715) & 0xf,0,0,0);
    WscBuildProbeRespIE(param_1,3,(char)iVar4,1,uVar5,*(undefined2 *)((int)param_2 + 10),
                        (char)param_2[0x715],0,0,0);
    if (pcVar6 != (char *)0x0) {
      UpdateBeaconHandler(param_1,pcVar6,2);
    }
    RTMPSetTimer(param_2 + 0x717,120000);
    *(undefined1 *)((int)param_2 + 0x1c5b) = 1;
    param_2[3] = 3;
    if (param_3 != 0) {
      WscSendUPnPConfReqMsg
                (param_1,uVar7,
                 "Set::OID_802_11_SET_PASSPHRASE, Failed (len less than 8 or greater than 64)!!\n" +
                 param_1 + uVar7 * 0x5834 + 0x34,
                 "======== Badnode detector =============\nvow_bn_en = <0/1> 0:dieable, 1:enable\nvow_bn_mon_period = <period> ms\nvow_bn_fallback_th = <count>\nvow_bn_per_th = <TX PER>\n======== Airtime counter test =============\nvow_counter_test = <0/1> 0:dieable, 1:enable\nvow_counter_test_period = <period> ms\nvow_counter_test_band = <band>\nvow_counter_test_avgcnt = <average num> sec\nvow_counter_test_target = <wlanidx>\n======== DVT =============\nvow_dvt_en = <0/1> 0:dieable, 1:enable\nvow_monitor_sta = <STA num>\nvow_show_sta = <STA num>\nvow_monitor_bss = <BSS num>\nvow_monitor_mbss = <MBSS num>\nvow_show_mbss = <MBSS num>\nvow_avg_num = <average num> sec\n======== RED ===========\nvow_set_red_en = <0/1> 0:disable, 1:enable\nvow_set_red_show_sta = <STA num>\nvow_set_red_tar_delay = <tarDelay> us\n======== WATF ===========\nvow_watf_en = <0/1> 0:disable, 1:enable\nvow_watf_q = <level>-<quantum> unit 256us\nvow_watf_add_entry = <level>-<Addr>\nvow_watf_del_entry = <Addr>\n"
                 + param_1 + uVar7 * 0x5834 + 0x101,3,0,0);
    }
    iVar4 = DebugLevel;
    uVar5 = 1;
    *(undefined1 *)(param_2 + 0xa79) = 1;
    *(undefined1 *)(param_2 + 0xaf8) = 1;
    if (2 < iVar4) {
      printk("%s:: trigger WSC state machine\n","WscGetConfWithoutTrigger");
    }
  }
  return uVar5;
}

