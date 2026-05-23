// module: mt7915.ko
// function: sync_fsm_scan_req_action @ 0x10a8f0
// size: 1488 bytes
//

/* WARNING: Type propagation algorithm not settling */

void sync_fsm_scan_req_action(int param_1,int param_2)

{
  char *pcVar1;
  undefined1 uVar2;
  undefined1 *puVar3;
  int iVar4;
  int iVar5;
  undefined4 uVar6;
  int iVar7;
  uint uVar8;
  int *piVar9;
  int iVar10;
  char *pcVar11;
  undefined1 *local_90;
  byte *local_8c;
  undefined1 *local_88;
  char *local_80;
  int local_7c;
  int local_78;
  int *local_74;
  undefined1 uStack_6e;
  byte local_6d;
  undefined1 local_6c;
  undefined1 local_6b;
  undefined2 local_6a;
  undefined1 auStack_68 [12];
  undefined4 local_5c [3];
  undefined4 *******local_50;
  undefined4 *******local_4c;
  undefined1 auStack_48 [36];
  
  iVar10 = *(int *)(param_2 + 0x92c);
  local_6b = 0x85;
  puVar3 = (undefined1 *)get_scan_ctrl_by_wdev(param_1,iVar10);
  local_6a = 0;
  if (-1 < DebugLevel) {
    local_90 = (undefined1 *)(uint)(byte)puVar3[0x1c6];
    printk("SYNC - %s:[%d] LAST_CH: %d, BAND: %d\n","sync_fsm_scan_req_action",0x4bf,
           *(undefined1 *)(iVar10 + 0xbb6));
  }
  if (iVar10 == 0) {
    return;
  }
  iVar4 = HcGetBandByWdev(iVar10);
  if ((*(uint *)(param_1 + 0xa39f84) & 0x10000000) == 0) {
    if (2 < DebugLevel) {
      printk("SYNC - MlmeScanReqAction before Startup\n");
    }
    goto LAB_0010a968;
  }
  local_8c = &local_6d;
  local_90 = auStack_48;
  local_88 = &local_6b;
  iVar5 = MlmeScanReqSanity(param_1,param_2,*(undefined4 *)(param_2 + 0x908),&local_6c);
  if (iVar5 == 0) {
    if (-1 < DebugLevel) {
      printk("%s - MlmeScanReqAction() sanity check fail. BUG!!!\n","sync_fsm_scan_req_action");
    }
    goto LAB_0010a968;
  }
  local_80 = "======== Rx Config =============\nvow_rx_counter_clr = <n>\nvow_rx_airtime_en = <0/1> 0:dieable, 1:enable\nvow_rx_ed_offset = <val> 1.024(5b)\nvow_rx_obss_backoff = <val> 1.024(16b)\nvow_rx_wmm_backoff = <WMM set>-<WMM AC>-<val>\nvow_om_wmm_backoff = <WMM AC>-<val>\nvow_repeater_wmm_backoff = <WMM AC>-<val>\nvow_rx_non_qos_backoff = <val>\nvow_rx_bss_wmmset = <MBSS idx>-<0/1/2/3>\nvow_rx_om_wmm_sel = <OM idx>-<val> 0:RX WMM(1to1), 1:OM wmm\n======== Airtime estimator =============\nvow_at_est_en = <0/1> 0:dieable, 1:enable\nvow_at_mon_period = <period> ms\n"
             + param_1 + 0xc0;
  AsicDisableSync(param_1,0);
  pcVar1 = local_80;
  piVar9 = &DebugLevel;
  iVar5 = iVar10;
  if ("======== Badnode detector =============\nvow_bn_en = <0/1> 0:dieable, 1:enable\nvow_bn_mon_period = <period> ms\nvow_bn_fallback_th = <count>\nvow_bn_per_th = <TX PER>\n======== Airtime counter test =============\nvow_counter_test = <0/1> 0:dieable, 1:enable\nvow_counter_test_period = <period> ms\nvow_counter_test_band = <band>\nvow_counter_test_avgcnt = <average num> sec\nvow_counter_test_target = <wlanidx>\n======== DVT =============\nvow_dvt_en = <0/1> 0:dieable, 1:enable\nvow_monitor_sta = <STA num>\nvow_show_sta = <STA num>\nvow_monitor_bss = <BSS num>\nvow_monitor_mbss = <MBSS num>\nvow_show_mbss = <MBSS num>\nvow_avg_num = <average num> sec\n======== RED ===========\nvow_set_red_en = <0/1> 0:disable, 1:enable\nvow_set_red_show_sta = <STA num>\nvow_set_red_tar_delay = <tarDelay> us\n======== WATF ===========\nvow_watf_en = <0/1> 0:disable, 1:enable\nvow_watf_q = <level>-<quantum> unit 256us\nvow_watf_add_entry = <level>-<Addr>\nvow_watf_del_entry = <Addr>\n"
      [param_1 + 0xda] != '\0') {
    local_74 = &DebugLevel;
    uVar8 = 0;
    local_7c = iVar10;
    local_78 = param_2;
    do {
      pcVar11 = "======== Badnode detector =============\nvow_bn_en = <0/1> 0:dieable, 1:enable\nvow_bn_mon_period = <period> ms\nvow_bn_fallback_th = <count>\nvow_bn_per_th = <TX PER>\n======== Airtime counter test =============\nvow_counter_test = <0/1> 0:dieable, 1:enable\nvow_counter_test_period = <period> ms\nvow_counter_test_band = <band>\nvow_counter_test_avgcnt = <average num> sec\nvow_counter_test_target = <wlanidx>\n======== DVT =============\nvow_dvt_en = <0/1> 0:dieable, 1:enable\nvow_monitor_sta = <STA num>\nvow_show_sta = <STA num>\nvow_monitor_bss = <BSS num>\nvow_monitor_mbss = <MBSS num>\nvow_show_mbss = <MBSS num>\nvow_avg_num = <average num> sec\n======== RED ===========\nvow_set_red_en = <0/1> 0:disable, 1:enable\nvow_set_red_show_sta = <STA num>\nvow_set_red_tar_delay = <tarDelay> us\n======== WATF ===========\nvow_watf_en = <0/1> 0:disable, 1:enable\nvow_watf_q = <level>-<quantum> unit 256us\nvow_watf_add_entry = <level>-<Addr>\nvow_watf_del_entry = <Addr>\n"
                + param_1 + uVar8 * 0x5834 + 0xe0;
      if (((pcVar11 != (char *)0x0) && (iVar10 = HcGetBandByWdev(pcVar11), iVar10 == iVar4)) &&
         ("%u-%02x:%02x:%02x:%02x:%02x:%02x"[param_1 + uVar8 * 0x5834 + 0xc] != '\0')) {
        UpdateBeaconHandler(param_1,pcVar11,6);
      }
      uVar8 = uVar8 + 1 & 0xff;
      piVar9 = local_74;
      iVar5 = local_7c;
      param_2 = local_78;
    } while (uVar8 < (byte)pcVar1[0x242]);
  }
  uVar6 = jiffies;
  iVar10 = *(int *)(param_2 + 0x92c);
  *(undefined1 *)(iVar5 + 0xbb5) = 0;
  *(undefined4 *)(iVar5 + 0xbb0) = uVar6;
  RTMPCancelTimer(puVar3 + 0x148,&uStack_6e);
  puVar3[1] = local_6c;
  *puVar3 = local_6b;
  FUN_001082fc(iVar10);
  puVar3[3] = local_6d;
  memmove(puVar3 + 4,auStack_48,(uint)local_6d);
  if ((puVar3 + (int)(uint)(byte)puVar3[0x54])[0x4a] == '\0') {
    uVar2 = scan_find_next_channel(param_1,puVar3,*(undefined1 *)(iVar10 + 0xbb6));
    puVar3[2] = uVar2;
    if (*(int *)(puVar3 + 0x5c) == 1) goto LAB_0010ab10;
  }
  else {
    puVar3[2] = (puVar3 + (int)(uint)(byte)puVar3[0x54])[0x4a];
    if (2 < *piVar9) {
      local_90 = (undefined1 *)(uint)(byte)puVar3[0x54];
      printk("[%s][%d] start offchannel scan on %d : channel list index = %d\n",
             "sync_fsm_scan_req_action",0x4f3);
    }
    *(undefined4 *)(puVar3 + 0x5c) = 1;
LAB_0010ab10:
    *(undefined1 *)(param_1 + 0xa7c349) = 0;
  }
  if (*(char *)(param_1 + 0x286285) == '\x01') {
    iVar4 = HcGetBandByWdev(iVar10);
    puVar3 = (undefined1 *)hc_get_channel_ctrl(*(undefined4 *)(param_1 + 0xa797a0),iVar4);
    if ((&DAT_0036b824)[param_1 + iVar4] == '\x01') {
      APAutoChannelInit(param_1,iVar10);
      (&DAT_0036b860)[param_1] = *puVar3;
    }
  }
  if ((*(int *)(iVar10 + 0x14) == 2) &&
     (iVar4 = GetStaCfgByWdev(param_1,iVar10), (*(uint *)(iVar4 + 0x212464) & 0x81) == 0x81)) {
    uVar6 = GetAssociatedAPByWdev(param_1,iVar4);
    if (*(char *)(iVar4 + 0x2124c0) != '\0') {
      if (2 < *piVar9) {
        printk("%s:: H/W is in DOZE, wake up H/W before scanning\n","sync_fsm_scan_req_action");
      }
      RTMP_FORCE_WAKEUP(param_1,iVar4);
    }
    local_90 = (undefined1 *)0x1;
    RTMPSendNullFrame(param_1,uVar6,*(undefined1 *)(param_1 + 0x794cd0),
                      (uint)(*(int *)(param_1 + 0x795124) << 0x17) >> 0x1f);
    if (2 < *piVar9) {
      printk("MlmeScanReqAction -- Send PSM Data frame for off channel RM, SCAN_IN_PROGRESS=%d!\n",
             (uint)(*(int *)(param_1 + 0xa39f84) << 0x11) >> 0x1f);
    }
    if ((*(uint *)(((uint)&local_90 & 0xffffe000) + 4) & 0x1fff00) == 0) {
      iVar4 = 2;
      __init_waitqueue_head(auStack_68,"&_wait",ZeroSsid);
      while( true ) {
        local_5c[0] = 0;
        local_50 = &local_50;
        local_4c = &local_50;
        for (iVar5 = 1; iVar7 = prepare_to_wait_event(auStack_68,local_5c,1),
            iVar5 != 0 && iVar7 == 0; iVar5 = schedule_timeout(iVar5)) {
        }
        finish_wait(auStack_68,local_5c);
        if (iVar4 == 1) break;
        iVar4 = 1;
      }
    }
    else {
      RtmpusecDelay(20000);
    }
  }
  TriEventInit(param_1);
  puVar3 = (undefined1 *)get_scan_ctrl_by_wdev(*(undefined4 *)(iVar10 + 8),iVar10);
  iVar4 = *(int *)(puVar3 + 0x90);
  *(undefined4 *)(puVar3 + 0x90) = 1;
  if (*(undefined4 **)(puVar3 + 0xaf5d0) == (undefined4 *)0x0) {
    if (-1 < *piVar9) {
      printk("ScanCtrl->ScanReqwdev is NULL\n");
    }
  }
  else if (1 < *piVar9) {
    local_90 = *(undefined1 **)(SYNC_FSM_STATE_STR + iVar4 * 4);
    local_8c = (byte *)SYNC_FSM_STATE_STR._4_4_;
    printk("SYNC[%s, Band:%d, TYPE:%d]: [%s] ==============================================> [%s]\n"
           ,**(undefined4 **)(puVar3 + 0xaf5d0),puVar3[0x1c6],*puVar3);
  }
  iVar4 = scan_next_channel(param_1,iVar10,&local_6a);
  if ((iVar4 == 1) && ((char)local_6a == '\0')) {
    return;
  }
  puVar3 = (undefined1 *)get_scan_ctrl_by_wdev(*(undefined4 *)(iVar10 + 8),iVar10);
  iVar4 = *(int *)(puVar3 + 0x90);
  *(undefined4 *)(puVar3 + 0x90) = 0;
  if (*(undefined4 **)(puVar3 + 0xaf5d0) == (undefined4 *)0x0) {
    if (-1 < *piVar9) {
      printk("ScanCtrl->ScanReqwdev is NULL\n");
    }
  }
  else if (1 < *piVar9) {
    local_90 = *(undefined1 **)(SYNC_FSM_STATE_STR + iVar4 * 4);
    local_8c = (byte *)SYNC_FSM_STATE_STR._0_4_;
    printk("SYNC[%s, Band:%d, TYPE:%d]: [%s] ==============================================> [%s]\n"
           ,**(undefined4 **)(puVar3 + 0xaf5d0),puVar3[0x1c6],*puVar3);
  }
LAB_0010a968:
  cntl_scan_conf(iVar10,0x52);
  return;
}

