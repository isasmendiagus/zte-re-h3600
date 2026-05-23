// module: mt7915.ko
// function: MacTableDeleteEntry @ 0x14957c
// size: 2708 bytes
//

undefined4 MacTableDeleteEntry(int param_1,uint param_2,void *param_3)

{
  byte bVar1;
  ushort uVar2;
  uint uVar3;
  int iVar4;
  char *pcVar5;
  int *piVar6;
  int iVar7;
  int iVar8;
  int iVar9;
  void *__s1;
  int iVar10;
  int iVar11;
  int iVar12;
  undefined1 auStack_29 [5];
  
  if ((param_1 == 0) || (uVar3 = HcGetMaxStaNum(), uVar3 <= param_2)) {
    return 0;
  }
  if (0 < DebugLevel) {
    printk("%s(): wcid %d =====\n","MacTableDeleteEntry",param_2);
  }
  hc_get_chip_cap(*(undefined4 *)(param_1 + 0xa797a0));
  iVar4 = param_1 + param_2 * 0x14c0;
  iVar8 = *(int *)(iVar4 + 0xa1d28);
  iVar7 = param_1 + param_2 * 0x14c0 + 0xa1d20;
  if (iVar8 != 0 && *(int *)(iVar4 + 0xa1d20) != 0) {
    *(undefined1 *)(param_1 + (uint)*(ushort *)(iVar4 + 0xa1e02) * 0x620 + 0x2f762) = 2;
    ba_session_tear_down_all(param_1,*(undefined2 *)(iVar4 + 0xa1e00));
    iVar4 = *(int *)(iVar8 + 4);
    if ((iVar4 != 0) &&
       (((*(int *)(iVar8 + 0x14) == 2 ||
         ((*(int *)(iVar8 + 0x14) == 0x100 &&
          (iVar4 = *(int *)(*(int *)(iVar4 + 0x4140) + 4), iVar4 != 0)))) &&
        (iVar7 == *(int *)(iVar4 + 0x21246c) && *(int *)(iVar4 + 0x21246c) != 0)))) {
      *(undefined4 *)(iVar4 + 0x21246c) = 0;
    }
    iVar4 = wdev_do_disconn_act(*(undefined4 *)(param_2 * 0x14c0 + param_1 + 0xa1d28),iVar7);
    if ((iVar4 != 1) && (0 < DebugLevel)) {
      printk("%s(): STA disconnection fail!\n","mac_entry_disconn_act");
    }
  }
  _raw_spin_lock_bh(param_1 + 0x285958);
  iVar4 = param_2 * 0x14c0 + param_1;
  uVar3 = *(uint *)(iVar4 + 0xa1d20);
  if (uVar3 == 0) goto LAB_001498fc;
  if (*(int *)(iVar4 + 0xa31d0) != 0) {
    ZTE_tx_ctrl_rate_stat_destroy(param_1,iVar7);
    uVar3 = *(uint *)(iVar4 + 0xa1d20);
  }
  if ((uVar3 & 0xfffffbff) == 0) goto LAB_001498fc;
  iVar10 = param_1 + param_2 * 0x14c0;
  bVar1 = *(byte *)(iVar10 + 0xa1e04);
  pcVar5 = "======== Badnode detector =============\nvow_bn_en = <0/1> 0:dieable, 1:enable\nvow_bn_mon_period = <period> ms\nvow_bn_fallback_th = <count>\nvow_bn_per_th = <TX PER>\n======== Airtime counter test =============\nvow_counter_test = <0/1> 0:dieable, 1:enable\nvow_counter_test_period = <period> ms\nvow_counter_test_band = <band>\nvow_counter_test_avgcnt = <average num> sec\nvow_counter_test_target = <wlanidx>\n======== DVT =============\nvow_dvt_en = <0/1> 0:dieable, 1:enable\nvow_monitor_sta = <STA num>\nvow_show_sta = <STA num>\nvow_monitor_bss = <BSS num>\nvow_monitor_mbss = <MBSS num>\nvow_show_mbss = <MBSS num>\nvow_avg_num = <average num> sec\n======== RED ===========\nvow_set_red_en = <0/1> 0:disable, 1:enable\nvow_set_red_show_sta = <STA num>\nvow_set_red_tar_delay = <tarDelay> us\n======== WATF ===========\nvow_watf_en = <0/1> 0:disable, 1:enable\nvow_watf_q = <level>-<quantum> unit 256us\nvow_watf_add_entry = <level>-<Addr>\nvow_watf_del_entry = <Addr>\n"
           + (uint)bVar1 * 0x5834 + param_1 + 0xe0;
  MWDSAPPeerDisable(param_1,iVar7);
  iVar4 = DebugLevel;
  iVar8 = (uint)*(byte *)(iVar10 + 0xa1e04) * 0x5834 + param_1 +
          (((uint)*(ushort *)(iVar10 + 0xa1e18) << 0x15) >> 0x18);
  iVar11 = *(int *)(iVar10 + 0xa1d28);
  "vow_watf_q_lv1: %d\n"[iVar8 + 0x13] =
       "vow_watf_q_lv1: %d\n"[iVar8 + 0x13] &
       ~*(byte *)((int)&NUM_BIT8 + (*(ushort *)(iVar10 + 0xa1e18) & 7));
  __s1 = (void *)(param_1 + param_2 * 0x14c0 + 0xa1e0c);
  if (0 < iVar4) {
    printk("Del Sta:%pM\n",__s1);
  }
  iVar8 = param_2 * 0x14c0 + param_1;
  RtmpOSWrielessEventSend(**(undefined4 **)(iVar8 + 0xa1d28),1,4,0,__s1,6);
  iVar4 = memcmp(__s1,param_3,6);
  if (iVar4 != 0) {
    if (0 < DebugLevel) {
      printk("\n%s: Impossible Wcid = %d !!!!!\n","MacTableDeleteEntry",param_2);
    }
    ApUpdateCapabilityAndErpIe(param_1,pcVar5);
    goto LAB_001498fc;
  }
  if ("RT_OID_WSC_SET_MODE::unknown WscMode = %d\n"
      [(uint)*(byte *)(iVar8 + 0xa1e05) * 0x5834 + param_1 + 0xc] != '\0') {
    RemoveIPv4ProxyARPEntry(param_1,pcVar5,__s1);
    RemoveIPv6ProxyARPEntry(param_1,pcVar5,__s1);
  }
  iVar4 = param_2 * 0x14c0 + param_1;
  *(undefined1 *)(iVar4 + 0xa30d1) = 0;
  if (*(int *)(iVar4 + 0xa1d20) == 0x20001) {
    if (((*(uint *)(iVar4 + 0xa1e9c) & 0x10048) != 0) || (*(char *)(iVar11 + 0x5c0) == '\x01')) {
      DOT1X_InternalCmdAction(param_1,iVar7,0);
    }
    iVar8 = param_2 * 0x14c0 + param_1;
    IgmpGroupDelMembers(param_1,__s1,iVar11,*(undefined2 *)(iVar8 + 0xa1e00));
    iVar4 = (uint)*(byte *)(iVar8 + 0xa1e04) * 0x5834 + param_1;
    "pStaCfg->WpaPassPhrase"[iVar4 + 0xb] = "pStaCfg->WpaPassPhrase"[iVar4 + 0xb] + -1;
    (&DAT_0036b916)[param_1] = (&DAT_0036b916)[param_1] + -1;
    if (*(int *)(iVar8 + 0xa2820) != 0) {
      RepeaterDisconnectRootAP(param_1,*(int *)(iVar8 + 0xa2820),3);
      *(undefined4 *)(iVar8 + 0xa2820) = 0;
    }
  }
  iVar4 = param_2 * 0x14c0 + param_1;
  iVar8 = param_1 + (uint)(byte)(*(byte *)(iVar4 + 0xa1e10) ^
                                 *(byte *)(iVar4 + 0xa1e0c) ^ *(byte *)(iVar4 + 0xa1e0d) ^
                                 *(byte *)(iVar4 + 0xa1e0e) ^ *(byte *)(iVar4 + 0xa1e0f) ^
                                *(byte *)(iVar4 + 0xa1e11)) * 4;
  iVar4 = *(int *)(iVar8 + 0xa1920);
  if (iVar4 == 0) {
    printk(&_LC34,0x598);
    dump_stack();
LAB_00149984:
    printk(&_LC39,0x5a9);
    dump_stack();
  }
  else {
    if (iVar7 != iVar4) {
      do {
        iVar10 = iVar4;
        iVar4 = *(int *)(iVar10 + 0x10);
        if (iVar4 == 0) goto LAB_00149984;
      } while (iVar7 != iVar4);
      if (iVar10 != 0) {
        *(undefined4 *)(iVar10 + 0x10) = *(undefined4 *)(param_2 * 0x14c0 + param_1 + 0xa1d30);
        goto LAB_00149998;
      }
    }
    *(undefined4 *)(iVar8 + 0xa1920) = *(undefined4 *)(param_2 * 0x14c0 + param_1 + 0xa1d30);
  }
LAB_00149998:
  APCleanupPsQueue(param_1,param_1 + param_2 * 0x620 + 0x2f704);
  TRTableResetEntry(param_1,param_2);
  iVar4 = param_1 + param_2 * 0x14c0 + 0xa2838;
  do {
    iVar8 = iVar4 + 0x10;
    RtmpCleanupPsQueue(param_1,iVar4);
    iVar4 = iVar8;
  } while (iVar8 != param_1 + param_2 * 0x14c0 + 0xa2878);
  iVar4 = param_2 * 0x14c0 + param_1;
  *(undefined2 *)(iVar4 + 0xa2880) = 0;
  if (*(int *)(iVar4 + 0xa287c) != 0) {
    RTMPFreeNdisPacket(param_1);
    *(undefined4 *)(iVar4 + 0xa287c) = 0;
  }
  iVar4 = param_2 * 0x14c0 + param_1;
  *(undefined1 *)(iVar4 + 0xa2882) = 0;
  *(undefined1 *)(iVar4 + 0xa2883) = 0;
  RtmpAsicSleepHandle(param_1);
  if (2 < DebugLevel) {
    printk("uapsd> clear UAPSD queues!\n");
  }
  iVar9 = param_2 * 0x14c0 + 0xa2000;
  iVar4 = param_1 + param_2 * 0x14c0;
  iVar12 = param_1 + iVar9 + 0x124;
  *(undefined4 *)(iVar4 + 0xa281c) = 0;
  RTMPCancelTimer(iVar12,auStack_29);
  iVar8 = param_1 + iVar9 + 0x158;
  RTMPCancelTimer(iVar8,auStack_29);
  iVar10 = param_1 + iVar9 + 0x240;
  RTMPCancelTimer(iVar10,auStack_29);
  RTMPReleaseTimer(iVar12,auStack_29);
  RTMPReleaseTimer(iVar8,auStack_29);
  RTMPReleaseTimer(iVar10,auStack_29);
  iVar8 = param_1 + iVar9 + 0x2e0;
  iVar10 = param_1 + iVar9 + 0x314;
  RTMPCancelTimer(iVar8,auStack_29);
  RTMPCancelTimer(iVar10,auStack_29);
  RTMPReleaseTimer(iVar8,auStack_29);
  RTMPReleaseTimer(iVar10,auStack_29);
  if (*(int *)(iVar4 + 0xa1d20) == 0x20001) {
    iVar8 = (uint)bVar1 * 0x5834;
    iVar4 = memcmp(__s1,"%s(): FIXME!!!Unexpected frame send to MgmtRing, need to assign the length!\n"
                        + param_1 + iVar8 + 0x31,6);
    if (((iVar4 == 0) &&
        (iVar4 = param_1 + iVar8,
        "IF(ra0) Set_WscConfMode_Proc::(WscConfMode(0,1,2)=%d)\n"[iVar4 + 0xc] == '\x01')) &&
       (*(int *)(
                "4/home/ws/zx279128s/packages/function/wlan/mtk/drivers/MT7915_V7.0.1.0/mt_wifi_ap/../mt_wifi/embedded/fsm/ap_mgmt_cntl.c:%d assert pAdfailed\n"
                + iVar4 + 0x3b) != 0x18)) {
      RTMPCancelTimer("IF(ra0) Set_WscConfMode_Proc::(WscConfMode(0,1,2)=%d)\n" + iVar4 + 0x10,
                      auStack_29);
      "IF(ra0) Set_WscConfMode_Proc::(WscConfMode(0,1,2)=%d)\n"[iVar4 + 0xc] = '\0';
      "%s(): FIXME!!!Unexpected frame send to MgmtRing, need to assign the length!\n"[iVar4 + 0x2e]
           = '\0';
      __memzero("%s(): FIXME!!!Unexpected frame send to MgmtRing, need to assign the length!\n" +
                param_1 + iVar8 + 0x31,6);
    }
    iVar4 = param_2 * 0x14c0 + param_1;
    *(undefined1 *)(iVar4 + 0xa2a45) = 0;
    *(undefined1 *)(iVar4 + 0xa2a44) = 0;
  }
  __memzero(__s1,6);
  iVar4 = DebugLevel;
  *(short *)(param_1 + 0x285920) = *(short *)(param_1 + 0x285920) + -1;
  if (2 < iVar4) {
    printk("MacTableDeleteEntry1 - Total= %d\n");
  }
  ApUpdateCapabilityAndErpIe(param_1,pcVar5);
  if (*(ushort *)(&DAT_002963c2 + param_1) == param_2) {
    if (2 < DebugLevel) {
      printk("\n%s: Clear Wcid = %d FragBuffer !!!!!\n","MacTableDeleteEntry",param_2);
    }
    *(undefined4 *)(&DAT_002963b4 + param_1) = 0;
    *(undefined2 *)(&DAT_002963b8 + param_1) = 0;
    *(undefined4 *)(&DAT_002963bc + param_1) = 0;
    (&DAT_002963c5)[param_1] = 0;
    *(undefined2 *)(&DAT_002963ba + param_1) = 0;
    *(undefined2 *)(&DAT_002963c2 + param_1) = 0;
    *(undefined4 *)(&DAT_002963c8 + param_1) = 0;
    *(undefined4 *)(&DAT_002963cc + param_1) = 0;
    (&DAT_002963c4)[param_1] = 0;
  }
  iVar8 = param_2 * 0x14c0 + param_1;
  HcReleaseUcastWcid(param_1,*(undefined4 *)(iVar8 + 0xa1d28),param_2);
  iVar4 = *(int *)(param_1 + 0x28594c);
  uVar2 = *(ushort *)(iVar8 + 0xa1e18);
  if (iVar4 != 0) {
    uVar3 = (uint)(uVar2 >> 5);
    *(uint *)(iVar4 + uVar3 * 4) = *(uint *)(iVar4 + uVar3 * 4) & ~(1 << (uVar2 & 0x1f));
  }
  if ((*(int *)(param_2 * 0x14c0 + param_1 + 0xa1d20) == 0x20001) &&
     ((*(int *)(iVar11 + 0x14) - 0x2000U & 0xffffdfff) != 0)) {
    nonerp_sta_num(iVar7,1);
  }
  *(undefined4 *)(param_2 * 0x14c0 + param_1 + 0xa1d20) = 0;
  greenap_check_peer_connection_at_link_up_down(param_1,iVar11);
  twt_resource_release_at_link_down(iVar11,param_2);
LAB_001498fc:
  _raw_spin_unlock_bh(param_1 + 0x285958);
  if (*(short *)(param_1 + 0x285920) == 0) {
    piVar6 = (int *)(param_1 + 8);
    do {
      while( true ) {
        piVar6 = piVar6 + 1;
        if ((*piVar6 == 0) || (*(int *)(*piVar6 + 0x14) != 1)) break;
        iVar4 = wlan_operate_get_addht();
        *(byte *)(iVar4 + 2) = *(byte *)(iVar4 + 2) & 0xfc;
        if (piVar6 == (int *)(param_1 + 0x1a8)) goto LAB_00149958;
      }
    } while (piVar6 != (int *)(param_1 + 0x1a8));
  }
LAB_00149958:
  txbf_dyn_mech(param_1);
  return 1;
}

