// module: mt7915.ko
// function: WscStateMachineInit @ 0x1e0d3c
// size: 776 bytes
//

void WscStateMachineInit(int param_1,undefined4 param_2,undefined4 param_3)

{
  int iVar1;
  char cVar2;
  uint uVar3;
  char *pcVar4;
  byte bVar5;
  int iVar6;
  
  bVar5 = 0;
  StateMachineInit(param_2,param_3,1,3,Drop,0,0x22);
  StateMachineSetAction(param_2,0,0x23,WscEAPOLStartAction);
  StateMachineSetAction(param_2,0,0x22,WscEAPAction);
  StateMachineSetAction(param_2,0,0x24,WscEAPAction);
  cVar2 = *(char *)(param_1 + 0x286285);
  if (cVar2 == '\x01') {
    while( true ) {
      uVar3 = hc_get_chip_bcn_max_num(*(undefined4 *)(param_1 + 0xa797a0));
      iVar1 = (uint)bVar5 * 0x5834;
      iVar6 = param_1 + iVar1;
      pcVar4 = "4/home/ws/zx279128s/packages/function/wlan/mtk/drivers/MT7915_V7.0.1.0/mt_wifi_ap/../mt_wifi/embedded/fsm/ap_mgmt_cntl.c:%d assert pAdfailed\n"
               + iVar6 + 0x2b;
      if (uVar3 <= bVar5) break;
      *(char **)(
                "PIN authentication or communication error occurs!!\nRegistrar does NOT accept the same PIN again!(PIN:%08u)\n"
                + iVar6 + 100) =
           "======== Badnode detector =============\nvow_bn_en = <0/1> 0:dieable, 1:enable\nvow_bn_mon_period = <period> ms\nvow_bn_fallback_th = <count>\nvow_bn_per_th = <TX PER>\n======== Airtime counter test =============\nvow_counter_test = <0/1> 0:dieable, 1:enable\nvow_counter_test_period = <period> ms\nvow_counter_test_band = <band>\nvow_counter_test_avgcnt = <average num> sec\nvow_counter_test_target = <wlanidx>\n======== DVT =============\nvow_dvt_en = <0/1> 0:dieable, 1:enable\nvow_monitor_sta = <STA num>\nvow_show_sta = <STA num>\nvow_monitor_bss = <BSS num>\nvow_monitor_mbss = <MBSS num>\nvow_show_mbss = <MBSS num>\nvow_avg_num = <average num> sec\n======== RED ===========\nvow_set_red_en = <0/1> 0:disable, 1:enable\nvow_set_red_show_sta = <STA num>\nvow_set_red_tar_delay = <tarDelay> us\n======== WATF ===========\nvow_watf_en = <0/1> 0:disable, 1:enable\nvow_watf_q = <level>-<quantum> unit 256us\nvow_watf_add_entry = <level>-<Addr>\nvow_watf_del_entry = <Addr>\n"
           + param_1 + iVar1 + 0xe0;
      *(int *)(
              "PIN authentication or communication error occurs!!\nRegistrar does NOT accept the same PIN again!(PIN:%08u)\n"
              + iVar6 + 0x60) = param_1;
      "%s(): FIXME!!!Unexpected frame send to MgmtRing, need to assign the length!\n"[iVar6 + 0x30]
           = bVar5;
      WscInitCommonTimers(param_1,pcVar4);
      "Set::RT_OID_802_11_COUNTRY_REGION (A:%d  B/G:%d)\n"[iVar6 + 4] = '\0';
      RTMPInitTimer(param_1,"%-10d, %d, %d%%\n" + param_1 + iVar1 + 0x10,
                    rtmp_timer_WscUpdatePortCfgTimeout,pcVar4,0);
      "Set::RT_OID_802_11_COUNTRY_REGION (A:%d  B/G:%d)\n"[iVar6 + 4] = '\0';
      RTMPInitTimer(param_1,"Set::RT_OID_802_11_COUNTRY_REGION (A:%d  B/G:%d)\n" +
                            param_1 + iVar1 + 8,rtmp_timer_WscSetupLockTimeout,pcVar4,0);
      "Set::OID_802_11_BSSID_LIST_SCAN, TxCnt = %d\n"[iVar6 + 8] = '\0';
      bVar5 = bVar5 + 1;
    }
    *(int *)(s__s_0x_x_0x_x__d__d__s_00371824 + param_1) = param_1;
    *(undefined **)(s__s_0x_x_0x_x__d__d__s_00371824 + param_1 + 4) = &DAT_0036db58 + param_1;
    (&DAT_00370a90)[param_1] = 0x30;
    WscInitCommonTimers(param_1,&DAT_0036ee3c + param_1);
    WscInitClientTimers(param_1,&DAT_0036ee3c + param_1);
    (&DAT_00584240)[param_1] = 0x31;
    *(int *)(&DAT_00584fd4 + param_1) = param_1;
    *(undefined **)(&DAT_00584fd8 + param_1) = &DAT_00581308 + param_1;
    WscInitCommonTimers(param_1,&DAT_005825ec + param_1);
    WscInitClientTimers(param_1,&DAT_005825ec + param_1);
    RTMPInitTimer(param_1,param_1 + 0x36da54,rtmp_timer_ConWpsApCliMonitorTimeout,param_1,0);
    (&DAT_0036da88)[param_1] = 0;
    cVar2 = *(char *)(param_1 + 0x286285);
  }
  if ((cVar2 == '\0') && (uVar3 = 0, *(char *)(param_1 + 0x794ab9) != '\0')) {
    do {
      iVar1 = param_1 + uVar3 * 0x2137b0;
      *(int *)(s__s_0x_x_0x_x__d__d__s_00371824 + iVar1) = param_1;
      *(undefined **)(s__s_0x_x_0x_x__d__d__s_00371824 + iVar1 + 4) =
           &DAT_0036db58 + param_1 + uVar3 * 0x2137b0;
      (&DAT_00370a90)[iVar1] = (char)uVar3;
      WscInitCommonTimers(param_1,&DAT_0036ee3c + iVar1);
      uVar3 = uVar3 + 1 & 0xff;
      WscInitClientTimers(param_1,&DAT_0036ee3c + iVar1);
    } while (uVar3 < *(byte *)(param_1 + 0x794ab9));
  }
  return;
}

