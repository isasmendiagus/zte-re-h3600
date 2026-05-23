// module: mt7915.ko
// function: ap_handle_mic_error_event @ 0x17d78
// size: 4 bytes
//

void ap_handle_mic_error_event(int param_1,int *param_2)

{
  int iVar1;
  int *piVar2;
  int unaff_r11;
  int iVar3;
  undefined1 auStack_29 [5];
  
  if (param_2 == (int *)0x0) {
    return;
  }
  if (*param_2 == 2 || *param_2 == 0x40001) {
    return;
  }
  if (*(byte *)(param_2 + 0x145) < 10) {
    return;
  }
  if (*(char *)((int)param_2 + 0x515) != '\x01') {
    return;
  }
  if (2 < DebugLevel) {
    printk("HandleCounterMeasure ===>\n");
  }
  *(undefined1 *)(param_2 + 0x2b6) = 1;
  if ((&DAT_003687e4)[param_1] != '\x01') {
    unaff_r11 = param_1 + 0x3687b0;
  }
  *(int *)(&DAT_003687f8 + param_1) = *(int *)(&DAT_003687f8 + param_1) + 1;
  if ((&DAT_003687e4)[param_1] == '\x01') {
    if (-1 < DebugLevel) {
      printk("Receive CM Attack Twice within 60 seconds ====>>>\n");
    }
    unaff_r11 = param_1 + 0x3687b0;
    iVar3 = param_1 + (uint)*(byte *)(param_2 + 0x39) * 0x5834;
    piVar2 = (int *)(param_1 + 0xa1d20);
    GenRandom(param_1,"======== Badnode detector =============\nvow_bn_en = <0/1> 0:dieable, 1:enable\nvow_bn_mon_period = <period> ms\nvow_bn_fallback_th = <count>\nvow_bn_per_th = <TX PER>\n======== Airtime counter test =============\nvow_counter_test = <0/1> 0:dieable, 1:enable\nvow_counter_test_period = <period> ms\nvow_counter_test_band = <band>\nvow_counter_test_avgcnt = <average num> sec\nvow_counter_test_target = <wlanidx>\n======== DVT =============\nvow_dvt_en = <0/1> 0:dieable, 1:enable\nvow_monitor_sta = <STA num>\nvow_show_sta = <STA num>\nvow_monitor_bss = <BSS num>\nvow_monitor_mbss = <MBSS num>\nvow_show_mbss = <MBSS num>\nvow_avg_num = <average num> sec\n======== RED ===========\nvow_set_red_en = <0/1> 0:disable, 1:enable\nvow_set_red_show_sta = <STA num>\nvow_set_red_tar_delay = <tarDelay> us\n======== WATF ===========\nvow_watf_en = <0/1> 0:disable, 1:enable\nvow_watf_q = <level>-<quantum> unit 256us\nvow_watf_add_entry = <level>-<Addr>\nvow_watf_del_entry = <Addr>\n"
                      + iVar3 + 0x101,
              "Set::RT_OID_802_11_TX_POWER_LEVEL_1 (BAND0) (=%d)\n" + iVar3 + 0x27);
    RTMPCancelTimer(unaff_r11,auStack_29);
    (&DAT_003687e4)[param_1] = 0;
    iVar3 = 0;
    while( true ) {
      iVar1 = HcGetMaxStaNum(param_1);
      if (iVar1 <= iVar3) break;
      if (*piVar2 == 0x20001) {
        __MlmeDeAuthAction(param_1,piVar2,0xe,0,"HandleCounterMeasure",0x7a);
      }
      piVar2 = piVar2 + 0x530;
      iVar3 = iVar3 + 1;
    }
    (&DAT_003687e5)[param_1] = 1;
  }
  RTMPSetTimer(unaff_r11,60000);
  (&DAT_003687e4)[param_1] = 1;
  *(undefined4 *)(&DAT_003687f0 + param_1) = *(undefined4 *)(&DAT_003687e8 + param_1);
  *(undefined4 *)(&DAT_003687f4 + param_1) = *(undefined4 *)(&DAT_003687ec + param_1);
  RTMP_GetCurrentSystemTime(&DAT_003687e8 + param_1);
  return;
}

