// module: mt7915.ko
// function: ap_peer_auth_req_at_idle_action @ 0x4ca24
// size: 3476 bytes
//

void ap_peer_auth_req_at_idle_action(int param_1,int param_2)

{
  bool bVar1;
  undefined1 uVar2;
  int iVar3;
  uint uVar4;
  int *piVar5;
  undefined4 uVar6;
  int iVar7;
  ushort uVar8;
  undefined1 *puVar9;
  char *pcVar10;
  int *local_124;
  undefined1 local_11a;
  undefined1 local_119;
  undefined4 local_118;
  undefined4 local_114;
  int *local_110;
  undefined2 local_10a;
  undefined2 local_108;
  undefined1 local_106;
  undefined1 local_105;
  undefined1 auStack_ba [6];
  undefined4 local_b4;
  undefined2 local_b0;
  ushort local_ae;
  short local_ac;
  undefined2 local_aa;
  
  local_118 = 0;
  local_114 = 0;
  local_11a = 0x10;
  local_119 = 0x80;
  iVar3 = FUN_0004c894(param_1,param_2,*(undefined4 *)(param_2 + 0x908),auStack_ba);
  if (3 < DebugLevel) {
    printk("%s: Recv Auth from %02x:%02x:%02x:%02x:%02x:%02x\n","ap_peer_auth_req_at_idle_action",
           local_b4 & 0xff,local_b4._1_1_,local_b4 >> 0x10 & 0xff,local_b4 >> 0x18,
           (undefined1)local_b0,local_b0._1_1_);
  }
  uVar4 = get_apidx_by_addr(param_1,auStack_ba);
  if (uVar4 != (byte)"======== Badnode detector =============\nvow_bn_en = <0/1> 0:dieable, 1:enable\nvow_bn_mon_period = <period> ms\nvow_bn_fallback_th = <count>\nvow_bn_per_th = <TX PER>\n======== Airtime counter test =============\nvow_counter_test = <0/1> 0:dieable, 1:enable\nvow_counter_test_period = <period> ms\nvow_counter_test_band = <band>\nvow_counter_test_avgcnt = <average num> sec\nvow_counter_test_target = <wlanidx>\n======== DVT =============\nvow_dvt_en = <0/1> 0:dieable, 1:enable\nvow_monitor_sta = <STA num>\nvow_show_sta = <STA num>\nvow_monitor_bss = <BSS num>\nvow_monitor_mbss = <MBSS num>\nvow_show_mbss = <MBSS num>\nvow_avg_num = <average num> sec\n======== RED ===========\nvow_set_red_en = <0/1> 0:disable, 1:enable\nvow_set_red_show_sta = <STA num>\nvow_set_red_tar_delay = <tarDelay> us\n======== WATF ===========\nvow_watf_en = <0/1> 0:disable, 1:enable\nvow_watf_q = <level>-<quantum> unit 256us\nvow_watf_add_entry = <level>-<Addr>\nvow_watf_del_entry = <Addr>\n"
                     [uVar4 * 0x5834 + param_1 + 0xee]) {
    printk(&_LC10,0x21f);
    dump_stack();
  }
  if ((&DAT_003687e5)[param_1] == '\x01') {
    if (DebugLevel < 3) {
      return;
    }
    printk("Disallow new Association\n");
    return;
  }
  if (iVar3 == 0) {
    return;
  }
  if ((byte)"======== Badnode detector =============\nvow_bn_en = <0/1> 0:dieable, 1:enable\nvow_bn_mon_period = <period> ms\nvow_bn_fallback_th = <count>\nvow_bn_per_th = <TX PER>\n======== Airtime counter test =============\nvow_counter_test = <0/1> 0:dieable, 1:enable\nvow_counter_test_period = <period> ms\nvow_counter_test_band = <band>\nvow_counter_test_avgcnt = <average num> sec\nvow_counter_test_target = <wlanidx>\n======== DVT =============\nvow_dvt_en = <0/1> 0:dieable, 1:enable\nvow_monitor_sta = <STA num>\nvow_show_sta = <STA num>\nvow_monitor_bss = <BSS num>\nvow_monitor_mbss = <MBSS num>\nvow_show_mbss = <MBSS num>\nvow_avg_num = <average num> sec\n======== RED ===========\nvow_set_red_en = <0/1> 0:disable, 1:enable\nvow_set_red_show_sta = <STA num>\nvow_set_red_tar_delay = <tarDelay> us\n======== WATF ===========\nvow_watf_en = <0/1> 0:disable, 1:enable\nvow_watf_q = <level>-<quantum> unit 256us\nvow_watf_add_entry = <level>-<Addr>\nvow_watf_del_entry = <Addr>\n"
            [param_1 + 0xda] <= uVar4) {
    if (DebugLevel < 3) {
      return;
    }
    printk("AUTH - Bssid not found\n");
    return;
  }
  iVar3 = uVar4 * 0x5834 + param_1;
  if (((*(uint *)("%u-%02x:%02x:%02x:%02x:%02x:%02x" + iVar3 + 8) & 0x200000) == 0) ||
     (*(uint *)("======== WATF LV%d\'s MAC Address List ========\n" + iVar3 + 0xc) < 3)) {
    if (DebugLevel < 0) {
      return;
    }
    printk("AP is not ready, disallow new Association (state:%d)\n",
           *(undefined4 *)
            ("======== WATF LV%d\'s MAC Address List ========\n" + uVar4 * 0x5834 + param_1 + 0xc));
    return;
  }
  if ((*(int *)(
               "======== Badnode detector =============\nvow_bn_en = <0/1> 0:dieable, 1:enable\nvow_bn_mon_period = <period> ms\nvow_bn_fallback_th = <count>\nvow_bn_per_th = <TX PER>\n======== Airtime counter test =============\nvow_counter_test = <0/1> 0:dieable, 1:enable\nvow_counter_test_period = <period> ms\nvow_counter_test_band = <band>\nvow_counter_test_avgcnt = <average num> sec\nvow_counter_test_target = <wlanidx>\n======== DVT =============\nvow_dvt_en = <0/1> 0:dieable, 1:enable\nvow_monitor_sta = <STA num>\nvow_show_sta = <STA num>\nvow_monitor_bss = <BSS num>\nvow_monitor_mbss = <MBSS num>\nvow_show_mbss = <MBSS num>\nvow_avg_num = <average num> sec\n======== RED ===========\nvow_set_red_en = <0/1> 0:disable, 1:enable\nvow_set_red_show_sta = <STA num>\nvow_set_red_tar_delay = <tarDelay> us\n======== WATF ===========\nvow_watf_en = <0/1> 0:disable, 1:enable\nvow_watf_q = <level>-<quantum> unit 256us\nvow_watf_add_entry = <level>-<Addr>\nvow_watf_del_entry = <Addr>\n"
               + iVar3 + 0xe0) == 0) ||
     ((*(uint *)(*(int *)(
                         "======== Badnode detector =============\nvow_bn_en = <0/1> 0:dieable, 1:enable\nvow_bn_mon_period = <period> ms\nvow_bn_fallback_th = <count>\nvow_bn_per_th = <TX PER>\n======== Airtime counter test =============\nvow_counter_test = <0/1> 0:dieable, 1:enable\nvow_counter_test_period = <period> ms\nvow_counter_test_band = <band>\nvow_counter_test_avgcnt = <average num> sec\nvow_counter_test_target = <wlanidx>\n======== DVT =============\nvow_dvt_en = <0/1> 0:dieable, 1:enable\nvow_monitor_sta = <STA num>\nvow_show_sta = <STA num>\nvow_monitor_bss = <BSS num>\nvow_monitor_mbss = <MBSS num>\nvow_show_mbss = <MBSS num>\nvow_avg_num = <average num> sec\n======== RED ===========\nvow_set_red_en = <0/1> 0:disable, 1:enable\nvow_set_red_show_sta = <STA num>\nvow_set_red_tar_delay = <tarDelay> us\n======== WATF ===========\nvow_watf_en = <0/1> 0:disable, 1:enable\nvow_watf_q = <level>-<quantum> unit 256us\nvow_watf_add_entry = <level>-<Addr>\nvow_watf_del_entry = <Addr>\n"
                         + iVar3 + 0xe0) + 0x138) & 1) == 0)) {
    if (DebugLevel < 3) {
      return;
    }
    printk("AUTH - Bssid IF didn\'t up yet.\n");
    return;
  }
  piVar5 = (int *)MacTableLookup(param_1,&local_b4);
  if ((piVar5 == (int *)0x0) || (*piVar5 != 0x20001)) {
    bVar1 = false;
  }
  else {
    uVar8 = *(ushort *)(piVar5 + 0x38);
    piVar5[0x2ba] = 0;
    if ((*(char *)((int)piVar5 + 0x562) == '\x01') &&
       (*(char *)((uint)uVar8 * 0x620 + param_1 + 0x2f762) == '\x01')) {
      iVar3 = HcGetBandByWdev("======== Badnode detector =============\nvow_bn_en = <0/1> 0:dieable, 1:enable\nvow_bn_mon_period = <period> ms\nvow_bn_fallback_th = <count>\nvow_bn_per_th = <TX PER>\n======== Airtime counter test =============\nvow_counter_test = <0/1> 0:dieable, 1:enable\nvow_counter_test_period = <period> ms\nvow_counter_test_band = <band>\nvow_counter_test_avgcnt = <average num> sec\nvow_counter_test_target = <wlanidx>\n======== DVT =============\nvow_dvt_en = <0/1> 0:dieable, 1:enable\nvow_monitor_sta = <STA num>\nvow_show_sta = <STA num>\nvow_monitor_bss = <BSS num>\nvow_monitor_mbss = <MBSS num>\nvow_show_mbss = <MBSS num>\nvow_avg_num = <average num> sec\n======== RED ===========\nvow_set_red_en = <0/1> 0:disable, 1:enable\nvow_set_red_show_sta = <STA num>\nvow_set_red_tar_delay = <tarDelay> us\n======== WATF ===========\nvow_watf_en = <0/1> 0:disable, 1:enable\nvow_watf_q = <level>-<quantum> unit 256us\nvow_watf_add_entry = <level>-<Addr>\nvow_watf_del_entry = <Addr>\n"
                              + (uint)*(byte *)(piVar5 + 0x39) * 0x5834 + param_1 + 0xe0);
      iVar7 = HcGetBandByChannel(param_1,*(undefined1 *)(param_2 + 0x91f));
      if (iVar3 == iVar7) {
        bVar1 = false;
      }
      else {
        if (-1 < DebugLevel) {
          printk("%s: wcid%d exist in Band%d but Recv Band%d, CH%d => SKIP\n",
                 "ap_peer_auth_req_at_idle_action",(short)piVar5[0x38],iVar3,iVar7,
                 *(undefined1 *)(param_2 + 0x91f));
        }
        ZTE_Notify_Node_AD(0,piVar5);
        bVar1 = false;
        wlan_dbg_save_staoffline_record(piVar5,3,0x273,"ap_peer_auth_req_at_idle_action");
        __ZTE_STA_Assoc_Process(param_1,0x11,0,0,3,0,piVar5,"ap_peer_auth_req_at_idle_action",0x275)
        ;
        MacTableDeleteEntry(param_1,(short)piVar5[0x38],piVar5 + 0x3b);
        piVar5 = (int *)0x0;
      }
    }
    else {
      if (((*(uint *)(
                     "======== Badnode detector =============\nvow_bn_en = <0/1> 0:dieable, 1:enable\nvow_bn_mon_period = <period> ms\nvow_bn_fallback_th = <count>\nvow_bn_per_th = <TX PER>\n======== Airtime counter test =============\nvow_counter_test = <0/1> 0:dieable, 1:enable\nvow_counter_test_period = <period> ms\nvow_counter_test_band = <band>\nvow_counter_test_avgcnt = <average num> sec\nvow_counter_test_target = <wlanidx>\n======== DVT =============\nvow_dvt_en = <0/1> 0:dieable, 1:enable\nvow_monitor_sta = <STA num>\nvow_show_sta = <STA num>\nvow_monitor_bss = <BSS num>\nvow_monitor_mbss = <MBSS num>\nvow_show_mbss = <MBSS num>\nvow_avg_num = <average num> sec\n======== RED ===========\nvow_set_red_en = <0/1> 0:disable, 1:enable\nvow_set_red_show_sta = <STA num>\nvow_set_red_tar_delay = <tarDelay> us\n======== WATF ===========\nvow_watf_en = <0/1> 0:disable, 1:enable\nvow_watf_q = <level>-<quantum> unit 256us\nvow_watf_add_entry = <level>-<Addr>\nvow_watf_del_entry = <Addr>\n"
                     + uVar4 * 0x5834 + param_1 + 0x10c) & 0xef00) == 0) && (local_ae - 2 < 4)) {
        return;
      }
      iVar3 = memcmp(auStack_ba,
                     "======== Badnode detector =============\nvow_bn_en = <0/1> 0:dieable, 1:enable\nvow_bn_mon_period = <period> ms\nvow_bn_fallback_th = <count>\nvow_bn_per_th = <TX PER>\n======== Airtime counter test =============\nvow_counter_test = <0/1> 0:dieable, 1:enable\nvow_counter_test_period = <period> ms\nvow_counter_test_band = <band>\nvow_counter_test_avgcnt = <average num> sec\nvow_counter_test_target = <wlanidx>\n======== DVT =============\nvow_dvt_en = <0/1> 0:dieable, 1:enable\nvow_monitor_sta = <STA num>\nvow_show_sta = <STA num>\nvow_monitor_bss = <BSS num>\nvow_monitor_mbss = <MBSS num>\nvow_show_mbss = <MBSS num>\nvow_avg_num = <average num> sec\n======== RED ===========\nvow_set_red_en = <0/1> 0:disable, 1:enable\nvow_set_red_show_sta = <STA num>\nvow_set_red_tar_delay = <tarDelay> us\n======== WATF ===========\nvow_watf_en = <0/1> 0:disable, 1:enable\nvow_watf_q = <level>-<quantum> unit 256us\nvow_watf_add_entry = <level>-<Addr>\nvow_watf_del_entry = <Addr>\n"
                     + (uint)*(byte *)(piVar5 + 0x39) * 0x5834 + param_1 + 0x101,6);
      if (iVar3 == 0) {
        ba_session_tear_down_all(param_1,(uint)uVar8);
        bVar1 = false;
      }
      else {
        ZTE_Notify_Node_AD(0,piVar5);
        wlan_dbg_save_staoffline_record(piVar5,3,0x28b,"ap_peer_auth_req_at_idle_action");
        local_124 = (int *)0x0;
        __ZTE_STA_Assoc_Process(param_1,0x11,0,0,3,0,piVar5,"ap_peer_auth_req_at_idle_action",0x28d)
        ;
        iVar3 = piVar5[0x3f];
        MacTableDeleteEntry(param_1,(short)piVar5[0x38],piVar5 + 0x3b);
        bVar1 = iVar3 == 2;
        if (DebugLevel < 2) goto LAB_0004cc08;
        printk("AUTH - Bssid does not match\n");
        piVar5 = local_124;
      }
    }
  }
  local_124 = piVar5;
  if (3 < DebugLevel) {
    printk("AUTH - MBSS(%d), Rcv AUTH seq#%d, Alg=%d, Status=%d from [wcid=%d]%02x:%02x:%02x:%02x:%02x:%02x\n"
           ,uVar4,local_ac,local_ae,local_aa,*(undefined2 *)(param_2 + 0x920),local_b4 & 0xff,
           local_b4 >> 8 & 0xff,local_b4 >> 0x10 & 0xff,local_b4 >> 0x18,(undefined1)local_b0,
           local_b0._1_1_);
  }
LAB_0004cc08:
  __ZTE_STA_Assoc_Process(param_1,1,&local_b4,uVar4,0,0,0,"ap_peer_auth_req_at_idle_action",0x2b8);
  iVar3 = uVar4 * 0x5834 + param_1;
  if (((((*(int *)(
                  "4/home/ws/zx279128s/packages/function/wlan/mtk/drivers/MT7915_V7.0.1.0/mt_wifi_ap/../mt_wifi/embedded/fsm/ap_mgmt_cntl.c:%d assert pAdfailed\n"
                  + iVar3 + 0x2b) == 0) || ("%-10d, %d, %d%%\n"[iVar3 + 0xd] == '\0')) ||
       ("%-10d, %d, %d%%\n"[iVar3 + 0xc] == '\0')) ||
      (*(int *)("[RTMPSetInformation][BandIdx=%d] Ndis802_11OFDM5\n" + iVar3 + 0x31) != 1)) &&
     (iVar3 = ApCheckAccessControlList(param_1,&local_b4,uVar4), iVar3 == 0)) {
    if (local_ac != 1) {
      printk(&_LC18,0x2c9);
      dump_stack();
    }
    if (local_124 == (int *)0x0) {
      FUN_0004c718(param_1,param_2,local_ae,local_ac + 1,1,"ap_peer_auth_req_at_idle_action",0x2ce);
    }
    else {
      printk(&_LC19,0x2ca);
      dump_stack();
      FUN_0004c718(param_1,param_2,local_ae,local_ac + 1,1,"ap_peer_auth_req_at_idle_action",0x2ce);
      MacTableDeleteEntry(param_1,(short)local_124[0x38],local_124 + 0x3b);
    }
    if (DebugLevel < 3) {
      return;
    }
    printk("Failed in ACL checking => send an AUTH seq#2 with Status code = %d\n",1);
    return;
  }
  if ((&DAT_0036b920)[param_1] != '\0') {
    uVar6 = Get_BndStrgTable(param_1,uVar4);
    local_10a = 0;
    local_108 = 0;
    if (*(char *)(param_2 + 0x918) == '\0') {
      uVar2 = 0;
    }
    else {
      uVar2 = ConvertToRssi(param_1,param_2 + 0x918);
    }
    local_10a = CONCAT11(local_10a._1_1_,uVar2);
    if (*(char *)(param_2 + 0x919) == '\0') {
      uVar2 = 0;
    }
    else {
      uVar2 = ConvertToRssi(param_1,param_2 + 0x918,1);
    }
    local_10a = CONCAT11(uVar2,(undefined1)local_10a);
    if (*(char *)(param_2 + 0x91a) == '\0') {
      uVar2 = 0;
    }
    else {
      uVar2 = ConvertToRssi(param_1,param_2 + 0x918,2);
    }
    local_108 = CONCAT11(local_108._1_1_,uVar2);
    if (*(char *)(param_2 + 0x91b) == '\0') {
      uVar2 = 0;
    }
    else {
      uVar2 = ConvertToRssi(param_1,param_2 + 0x918,3);
    }
    local_108 = CONCAT11(uVar2,(undefined1)local_108);
    iVar3 = BndStrg_CheckConnectionReq
                      (param_1,uVar6,&local_b4,*(undefined1 *)(param_2 + 0x904),&local_10a);
    if (iVar3 == 0) {
      FUN_0004c718(param_1,param_2,local_ae,local_ac + 1,1,"ap_peer_auth_req_at_idle_action",0x312);
      if (DebugLevel < 3) {
        return;
      }
      printk("AUTH - check failed.\n");
      return;
    }
  }
  iVar3 = uVar4 * 0x5834;
  pcVar10 = "======== Badnode detector =============\nvow_bn_en = <0/1> 0:dieable, 1:enable\nvow_bn_mon_period = <period> ms\nvow_bn_fallback_th = <count>\nvow_bn_per_th = <TX PER>\n======== Airtime counter test =============\nvow_counter_test = <0/1> 0:dieable, 1:enable\nvow_counter_test_period = <period> ms\nvow_counter_test_band = <band>\nvow_counter_test_avgcnt = <average num> sec\nvow_counter_test_target = <wlanidx>\n======== DVT =============\nvow_dvt_en = <0/1> 0:dieable, 1:enable\nvow_monitor_sta = <STA num>\nvow_show_sta = <STA num>\nvow_monitor_bss = <BSS num>\nvow_monitor_mbss = <MBSS num>\nvow_show_mbss = <MBSS num>\nvow_avg_num = <average num> sec\n======== RED ===========\nvow_set_red_en = <0/1> 0:disable, 1:enable\nvow_set_red_show_sta = <STA num>\nvow_set_red_tar_delay = <tarDelay> us\n======== WATF ===========\nvow_watf_en = <0/1> 0:disable, 1:enable\nvow_watf_q = <level>-<quantum> unit 256us\nvow_watf_add_entry = <level>-<Addr>\nvow_watf_del_entry = <Addr>\n"
            + param_1 + iVar3 + 0xe0;
  if (local_ae == 3) {
    if ((*(uint *)(
                  "======== Badnode detector =============\nvow_bn_en = <0/1> 0:dieable, 1:enable\nvow_bn_mon_period = <period> ms\nvow_bn_fallback_th = <count>\nvow_bn_per_th = <TX PER>\n======== Airtime counter test =============\nvow_counter_test = <0/1> 0:dieable, 1:enable\nvow_counter_test_period = <period> ms\nvow_counter_test_band = <band>\nvow_counter_test_avgcnt = <average num> sec\nvow_counter_test_target = <wlanidx>\n======== DVT =============\nvow_dvt_en = <0/1> 0:dieable, 1:enable\nvow_monitor_sta = <STA num>\nvow_show_sta = <STA num>\nvow_monitor_bss = <BSS num>\nvow_monitor_mbss = <MBSS num>\nvow_show_mbss = <MBSS num>\nvow_avg_num = <average num> sec\n======== RED ===========\nvow_set_red_en = <0/1> 0:disable, 1:enable\nvow_set_red_show_sta = <STA num>\nvow_set_red_tar_delay = <tarDelay> us\n======== WATF ===========\nvow_watf_en = <0/1> 0:disable, 1:enable\nvow_watf_q = <level>-<quantum> unit 256us\nvow_watf_add_entry = <level>-<Addr>\nvow_watf_del_entry = <Addr>\n"
                  + param_1 + iVar3 + 0x10c) & 0x2000) != 0) {
      if (local_124 == (int *)0x0) {
        sae_handle_auth(param_1,"pci_sw_int_handler" + param_1,param_2,
                        *(undefined4 *)(param_2 + 0x908),
                        "======== Badnode detector =============\nvow_bn_en = <0/1> 0:dieable, 1:enable\nvow_bn_mon_period = <period> ms\nvow_bn_fallback_th = <count>\nvow_bn_per_th = <TX PER>\n======== Airtime counter test =============\nvow_counter_test = <0/1> 0:dieable, 1:enable\nvow_counter_test_period = <period> ms\nvow_counter_test_band = <band>\nvow_counter_test_avgcnt = <average num> sec\nvow_counter_test_target = <wlanidx>\n======== DVT =============\nvow_dvt_en = <0/1> 0:dieable, 1:enable\nvow_monitor_sta = <STA num>\nvow_show_sta = <STA num>\nvow_monitor_bss = <BSS num>\nvow_monitor_mbss = <MBSS num>\nvow_show_mbss = <MBSS num>\nvow_avg_num = <average num> sec\n======== RED ===========\nvow_set_red_en = <0/1> 0:disable, 1:enable\nvow_set_red_show_sta = <STA num>\nvow_set_red_tar_delay = <tarDelay> us\n======== WATF ===========\nvow_watf_en = <0/1> 0:disable, 1:enable\nvow_watf_q = <level>-<quantum> unit 256us\nvow_watf_add_entry = <level>-<Addr>\nvow_watf_del_entry = <Addr>\n"
                        + param_1 + iVar3 + 0x259,
                        "vow_rx_time (Non-wifi/OBSS)\nvow_sta_conf = <wlanidx>\nvow_sta_conf\nvow_bss_conf = <group>\nvow_all_bss_conf\nvow_dump_sta (raw)\nvow_dump_bss_bitmap (raw)\nvow_dump_bss (raw)\nvow_dump_vow (raw)\nvow_show_sta_dtoken = <wlanidx> DWRR\nvow_show_bss_dtoken = <group> DWRR\nvow_show_bss_atoken = <group> airtime\nvow_show_bss_ltoken = <group> length\n"
                        + param_1 + iVar3 + 0x110,
                        "vow_rx_time (Non-wifi/OBSS)\nvow_sta_conf = <wlanidx>\nvow_sta_conf\nvow_bss_conf = <group>\nvow_all_bss_conf\nvow_dump_sta (raw)\nvow_dump_bss_bitmap (raw)\nvow_dump_bss (raw)\nvow_dump_vow (raw)\nvow_show_sta_dtoken = <wlanidx> DWRR\nvow_show_bss_dtoken = <group> DWRR\nvow_show_bss_atoken = <group> airtime\nvow_show_bss_ltoken = <group> length\n"
                        [param_1 + iVar3 + 0x10c],local_ac,local_aa,&local_110);
        if (local_110 == (int *)0x0) {
          return;
        }
        local_124 = (int *)MacTableInsertEntry(param_1,&local_b4,pcVar10,0x20001,1,1);
        piVar5 = local_124;
      }
      else {
        if ((*(char *)((int)local_124 + 0x562) == '\x01') &&
           (*(char *)((uint)*(ushort *)(local_124 + 0x38) * 0x620 + param_1 + 0x2f762) == '\x01')) {
          if ((char)local_124[0x18a] != '\0') {
            return;
          }
          FUN_0004c718(param_1,param_2,3,local_ac,0x1e,"ap_peer_auth_req_at_idle_action",0x41e);
          PMF_MlmeSAQueryReq(param_1,local_124);
          return;
        }
        iVar3 = param_1 + uVar4 * 0x5834;
        sae_handle_auth(param_1,"pci_sw_int_handler" + param_1,param_2,
                        *(undefined4 *)(param_2 + 0x908),
                        "======== Badnode detector =============\nvow_bn_en = <0/1> 0:dieable, 1:enable\nvow_bn_mon_period = <period> ms\nvow_bn_fallback_th = <count>\nvow_bn_per_th = <TX PER>\n======== Airtime counter test =============\nvow_counter_test = <0/1> 0:dieable, 1:enable\nvow_counter_test_period = <period> ms\nvow_counter_test_band = <band>\nvow_counter_test_avgcnt = <average num> sec\nvow_counter_test_target = <wlanidx>\n======== DVT =============\nvow_dvt_en = <0/1> 0:dieable, 1:enable\nvow_monitor_sta = <STA num>\nvow_show_sta = <STA num>\nvow_monitor_bss = <BSS num>\nvow_monitor_mbss = <MBSS num>\nvow_show_mbss = <MBSS num>\nvow_avg_num = <average num> sec\n======== RED ===========\nvow_set_red_en = <0/1> 0:disable, 1:enable\nvow_set_red_show_sta = <STA num>\nvow_set_red_tar_delay = <tarDelay> us\n======== WATF ===========\nvow_watf_en = <0/1> 0:disable, 1:enable\nvow_watf_q = <level>-<quantum> unit 256us\nvow_watf_add_entry = <level>-<Addr>\nvow_watf_del_entry = <Addr>\n"
                        + iVar3 + 0x259,
                        "vow_rx_time (Non-wifi/OBSS)\nvow_sta_conf = <wlanidx>\nvow_sta_conf\nvow_bss_conf = <group>\nvow_all_bss_conf\nvow_dump_sta (raw)\nvow_dump_bss_bitmap (raw)\nvow_dump_bss (raw)\nvow_dump_vow (raw)\nvow_show_sta_dtoken = <wlanidx> DWRR\nvow_show_bss_dtoken = <group> DWRR\nvow_show_bss_atoken = <group> airtime\nvow_show_bss_ltoken = <group> length\n"
                        + iVar3 + 0x110,
                        "vow_rx_time (Non-wifi/OBSS)\nvow_sta_conf = <wlanidx>\nvow_sta_conf\nvow_bss_conf = <group>\nvow_all_bss_conf\nvow_dump_sta (raw)\nvow_dump_bss_bitmap (raw)\nvow_dump_bss (raw)\nvow_dump_vow (raw)\nvow_show_sta_dtoken = <wlanidx> DWRR\nvow_show_bss_dtoken = <group> DWRR\nvow_show_bss_atoken = <group> airtime\nvow_show_bss_ltoken = <group> length\n"
                        [iVar3 + 0x10c],local_ac,local_aa,&local_110);
        piVar5 = local_110;
      }
      if (piVar5 == (int *)0x0) {
        return;
      }
      memmove((void *)((int)local_124 + 0x30a),local_110,0x20);
      iVar3 = 1;
      local_124[0x41] = 1;
      local_124[0x3f] = 1;
      if (bVar1) {
        iVar3 = 2;
      }
      *(undefined1 *)((int)local_124 + 0xea) = 0;
      if (bVar1) {
        local_124[0x40] = iVar3;
      }
      iVar3 = sae_get_pmk_cache("pci_sw_int_handler" + param_1,auStack_ba,&local_b4,&local_10a,0);
      if (iVar3 == 0) {
        return;
      }
      RTMPAddPMKIDCache(&DAT_003687fc + param_1,uVar4,local_124 + 0x3b,&local_10a,local_110,0x20);
      if (DebugLevel < 3) {
        return;
      }
      printk("WPA3PSK(SAE):(%02x:%02x:%02x:%02x:%02x:%02x)Calc PMKID=%02x:%02x:%02x:%02x:%02x:%02x\n"
             ,(char)local_124[0x3b],*(undefined1 *)((int)local_124 + 0xed),
             *(undefined1 *)((int)local_124 + 0xee),*(undefined1 *)((int)local_124 + 0xef),
             (char)local_124[0x3c],*(undefined1 *)((int)local_124 + 0xf1),(undefined1)local_10a,
             local_10a._1_1_,(undefined1)local_108,local_108._1_1_,local_106,local_105);
      return;
    }
  }
  else if (local_ae == 0) {
    if ((*(uint *)(
                  "======== Badnode detector =============\nvow_bn_en = <0/1> 0:dieable, 1:enable\nvow_bn_mon_period = <period> ms\nvow_bn_fallback_th = <count>\nvow_bn_per_th = <TX PER>\n======== Airtime counter test =============\nvow_counter_test = <0/1> 0:dieable, 1:enable\nvow_counter_test_period = <period> ms\nvow_counter_test_band = <band>\nvow_counter_test_avgcnt = <average num> sec\nvow_counter_test_target = <wlanidx>\n======== DVT =============\nvow_dvt_en = <0/1> 0:dieable, 1:enable\nvow_monitor_sta = <STA num>\nvow_show_sta = <STA num>\nvow_monitor_bss = <BSS num>\nvow_monitor_mbss = <MBSS num>\nvow_show_mbss = <MBSS num>\nvow_avg_num = <average num> sec\n======== RED ===========\nvow_set_red_en = <0/1> 0:disable, 1:enable\nvow_set_red_show_sta = <STA num>\nvow_set_red_tar_delay = <tarDelay> us\n======== WATF ===========\nvow_watf_en = <0/1> 0:disable, 1:enable\nvow_watf_q = <level>-<quantum> unit 256us\nvow_watf_add_entry = <level>-<Addr>\nvow_watf_del_entry = <Addr>\n"
                  + param_1 + iVar3 + 0x10c) & 2) == 0) {
      uVar8 = 0;
      if ((local_124 == (int *)0x0) &&
         (local_124 = (int *)MacTableInsertEntry(param_1,&local_b4,pcVar10,0x20001,1,1),
         uVar8 = local_ae, local_124 == (int *)0x0)) {
        return;
      }
      if ((*(char *)((int)local_124 + 0x562) == '\0') ||
         (*(char *)((uint)*(ushort *)(local_124 + 0x38) * 0x620 + param_1 + 0x2f762) != '\x01')) {
        local_124[0x41] = 1;
        local_124[0x3f] = 1;
        if (bVar1) {
          local_124[0x40] = 2;
        }
        *(undefined1 *)((int)local_124 + 0xea) = 0;
      }
      FUN_0004c718(param_1,param_2,uVar8,local_ac + 1,0,"ap_peer_auth_req_at_idle_action",0x489);
      __ZTE_STA_Assoc_Process(param_1,2,0,0,0,0,local_124,"ap_peer_auth_req_at_idle_action",0x48c);
      return;
    }
  }
  else if ((local_ae == 1) &&
          ((*(uint *)(
                     "======== Badnode detector =============\nvow_bn_en = <0/1> 0:dieable, 1:enable\nvow_bn_mon_period = <period> ms\nvow_bn_fallback_th = <count>\nvow_bn_per_th = <TX PER>\n======== Airtime counter test =============\nvow_counter_test = <0/1> 0:dieable, 1:enable\nvow_counter_test_period = <period> ms\nvow_counter_test_band = <band>\nvow_counter_test_avgcnt = <average num> sec\nvow_counter_test_target = <wlanidx>\n======== DVT =============\nvow_dvt_en = <0/1> 0:dieable, 1:enable\nvow_monitor_sta = <STA num>\nvow_show_sta = <STA num>\nvow_monitor_bss = <BSS num>\nvow_monitor_mbss = <MBSS num>\nvow_show_mbss = <MBSS num>\nvow_avg_num = <average num> sec\n======== RED ===========\nvow_set_red_en = <0/1> 0:disable, 1:enable\nvow_set_red_show_sta = <STA num>\nvow_set_red_tar_delay = <tarDelay> us\n======== WATF ===========\nvow_watf_en = <0/1> 0:disable, 1:enable\nvow_watf_q = <level>-<quantum> unit 256us\nvow_watf_add_entry = <level>-<Addr>\nvow_watf_del_entry = <Addr>\n"
                     + param_1 + iVar3 + 0x10c) & 6) != 0)) {
    if ((local_124 == (int *)0x0) &&
       (local_124 = (int *)MacTableInsertEntry(param_1,&local_b4,pcVar10,0x20001,1,1),
       local_124 == (int *)0x0)) {
      return;
    }
    puVar9 = (undefined1 *)(param_1 + 0x36daaf);
    local_124[0x3f] = 0;
    local_124[0x41] = 3;
    *(undefined1 *)((int)local_124 + 0xea) = 0;
    *(uint *)(&DAT_0036daa8 + param_1) = local_b4;
    *(undefined2 *)(&DAT_0036daac + param_1) = local_b0;
    do {
      uVar2 = RandomByte(param_1);
      puVar9 = puVar9 + 1;
      *puVar9 = uVar2;
    } while (puVar9 != (undefined1 *)(param_1 + 0x36db2f));
    local_ac = local_ac + 1;
    local_110 = (int *)((uint)local_110 & 0xffff0000);
    iVar3 = os_alloc_mem(param_1,&local_118,0x900);
    if (iVar3 != 0) {
      return;
    }
    if (2 < DebugLevel) {
      printk("AUTH - Send AUTH seq#2 (Challenge)\n");
    }
    iVar3 = param_1 + uVar4 * 0x5834;
    MgtMacHeaderInit(param_1,&local_10a,0xb,0,&local_b4,
                     "======== Badnode detector =============\nvow_bn_en = <0/1> 0:dieable, 1:enable\nvow_bn_mon_period = <period> ms\nvow_bn_fallback_th = <count>\nvow_bn_per_th = <TX PER>\n======== Airtime counter test =============\nvow_counter_test = <0/1> 0:dieable, 1:enable\nvow_counter_test_period = <period> ms\nvow_counter_test_band = <band>\nvow_counter_test_avgcnt = <average num> sec\nvow_counter_test_target = <wlanidx>\n======== DVT =============\nvow_dvt_en = <0/1> 0:dieable, 1:enable\nvow_monitor_sta = <STA num>\nvow_show_sta = <STA num>\nvow_monitor_bss = <BSS num>\nvow_monitor_mbss = <MBSS num>\nvow_show_mbss = <MBSS num>\nvow_avg_num = <average num> sec\n======== RED ===========\nvow_set_red_en = <0/1> 0:disable, 1:enable\nvow_set_red_show_sta = <STA num>\nvow_set_red_tar_delay = <tarDelay> us\n======== WATF ===========\nvow_watf_en = <0/1> 0:disable, 1:enable\nvow_watf_q = <level>-<quantum> unit 256us\nvow_watf_add_entry = <level>-<Addr>\nvow_watf_del_entry = <Addr>\n"
                     + iVar3 + 0xfb,
                     "======== Badnode detector =============\nvow_bn_en = <0/1> 0:dieable, 1:enable\nvow_bn_mon_period = <period> ms\nvow_bn_fallback_th = <count>\nvow_bn_per_th = <TX PER>\n======== Airtime counter test =============\nvow_counter_test = <0/1> 0:dieable, 1:enable\nvow_counter_test_period = <period> ms\nvow_counter_test_band = <band>\nvow_counter_test_avgcnt = <average num> sec\nvow_counter_test_target = <wlanidx>\n======== DVT =============\nvow_dvt_en = <0/1> 0:dieable, 1:enable\nvow_monitor_sta = <STA num>\nvow_show_sta = <STA num>\nvow_monitor_bss = <BSS num>\nvow_monitor_mbss = <MBSS num>\nvow_show_mbss = <MBSS num>\nvow_avg_num = <average num> sec\n======== RED ===========\nvow_set_red_en = <0/1> 0:disable, 1:enable\nvow_set_red_show_sta = <STA num>\nvow_set_red_tar_delay = <tarDelay> us\n======== WATF ===========\nvow_watf_en = <0/1> 0:disable, 1:enable\nvow_watf_q = <level>-<quantum> unit 256us\nvow_watf_add_entry = <level>-<Addr>\nvow_watf_del_entry = <Addr>\n"
                     + iVar3 + 0x101);
    MakeOutgoingFrame(local_118,&local_114,0x18,&local_10a,2,&local_ae,2,&local_ac,2,&local_110,1,
                      &local_11a,1,&local_119,0x80,&DAT_0036dab0 + param_1,0xffffffff);
    MiniportMMRequest(param_1,0,local_118,local_114);
    os_free_mem(local_118);
    return;
  }
  FUN_0004c718(param_1,param_2,local_ae,local_ac + 1,0xd,"ap_peer_auth_req_at_idle_action",0x4f2);
  if (local_124 != (int *)0x0) {
    MacTableDeleteEntry(param_1,(short)local_124[0x38],local_124 + 0x3b);
  }
  if (2 < DebugLevel) {
    printk("AUTH - Alg=%d, Seq=%d\n",local_ae,local_ac);
  }
  return;
}

