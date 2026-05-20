// module: mt7915.ko
// function: UserCfgInit @ 0x13a678
// size: 6464 bytes
//

void UserCfgInit(int param_1)

{
  undefined1 uVar1;
  char cVar2;
  int iVar3;
  int iVar4;
  uint uVar5;
  undefined2 *puVar6;
  undefined2 *puVar7;
  undefined4 *puVar8;
  undefined4 *puVar9;
  undefined4 *puVar10;
  undefined2 *puVar11;
  int *piVar12;
  undefined1 *puVar13;
  int *piVar14;
  char *pcVar15;
  undefined1 *puVar16;
  int iVar17;
  uint uVar18;
  undefined4 *puVar19;
  undefined4 uVar20;
  undefined2 *puVar21;
  undefined *puVar22;
  char *pcVar23;
  undefined2 *puVar24;
  bool bVar25;
  undefined4 *local_64;
  undefined4 *local_60;
  undefined1 *local_5c;
  undefined4 *local_58;
  undefined4 *local_54;
  undefined1 *local_50;
  undefined4 *local_4c;
  int local_38;
  
  iVar3 = hc_get_arch_ops(*(undefined4 *)(param_1 + 0xa797a0));
  iVar4 = hc_get_chip_cap(*(undefined4 *)(param_1 + 0xa797a0));
  if (2 < DebugLevel) {
    printk("--> UserCfgInit\n");
  }
  wpf_init(param_1);
  *(undefined4 *)(param_1 + 0x794ae4) = 0;
  *(undefined4 *)(param_1 + 0x794c9c) = 0xf;
  *(undefined4 *)(param_1 + 0x794ca0) = 0xf;
  *(undefined1 *)(param_1 + 0x28595c) = 4;
  if ((iVar3 != 0) && (*(code **)(iVar3 + 0x208) != (code *)0x0)) {
    (**(code **)(iVar3 + 0x208))(param_1);
  }
  os_zero_mem(param_1 + 0x794cde,0x45);
  puVar13 = (undefined1 *)(param_1 + 0xa377a5);
  os_zero_mem(param_1 + 0x794d68,0xa1);
  os_zero_mem(param_1 + 0xa7c218,0xc);
  *(undefined4 *)(param_1 + 0xa7c220) = 0;
  *(undefined1 *)(param_1 + 0x285a2c) = 0;
  do {
    uVar18 = 0;
    puVar16 = puVar13;
    while( true ) {
      uVar5 = hc_get_chip_bcn_max_num(*(undefined4 *)(param_1 + 0xa797a0));
      bVar25 = uVar5 <= uVar18;
      uVar18 = uVar18 + 1;
      if (bVar25) break;
      *puVar16 = 0;
      puVar16[-1] = 0;
      puVar16 = puVar16 + 0x124;
    }
    puVar13 = puVar13 + 0x49;
  } while (puVar13 != (undefined1 *)(param_1 + 0xa378c9));
  *(undefined1 *)(param_1 + 0x794b54) = 0;
  "Set_IRR_TTG"[param_1 + 0xb] = '\0';
  ("SetPartProfileParameters" + param_1 + 0x18)[0] = '\0';
  ("SetPartProfileParameters" + param_1 + 0x18)[1] = '\0';
  "auth_fsm_reset"[param_1 + 5] = '\0';
  "rtmp_read_dot11v_mbssid_cfg_from_file"[param_1 + 0x1e] = '\x01';
  *(undefined1 *)(param_1 + 0xa39fb5) = 0;
  *(undefined1 *)(param_1 + 0xa39fb6) = 0;
  *(undefined1 *)(param_1 + 0xa39fb7) = 0;
  *(undefined1 *)(param_1 + 0xa39fb8) = 0;
  *(undefined1 *)(param_1 + 0xa39fb9) = 0;
  *(undefined1 *)(param_1 + 0xa39fba) = 0;
  *(undefined2 *)(param_1 + 0x794c4a) = 10;
  *(undefined1 *)(param_1 + 0x794cd7) = 100;
  *(undefined1 *)(param_1 + 0x794cd8) = 100;
  *(undefined1 *)(param_1 + 0x794cd9) = 100;
  *(undefined1 *)(param_1 + 0x795041) = 100;
  *(undefined1 *)(param_1 + 0x795042) = 100;
  *(undefined1 *)(param_1 + 0x795068) = 0;
  *(undefined4 *)(param_1 + 0x795064) = 2;
  *(undefined1 *)(param_1 + 0xa39fa1) = 0;
  *(undefined1 *)(param_1 + 0x795071) = 1;
  *(undefined4 *)(param_1 + 0x79506c) = 0;
  *(undefined1 *)(param_1 + 0x794c49) = 0xff;
  *(undefined4 *)(param_1 + 0x79512c) = 0;
  "BssEntrySet"[param_1 + 3] = '\x04';
  if (*(char *)(param_1 + 0x286285) == '\0') {
    "BssEntrySet"[param_1 + 4] = '\n';
  }
  else if (*(char *)(param_1 + 0x286285) == '\x01') {
    "BssEntrySet"[param_1 + 4] = '\x06';
  }
  os_zero_mem(&DAT_0036b848 + param_1,8);
  os_zero_mem(&DAT_0036b850 + param_1,8);
  uVar18 = 0;
  hc_init_ACSChCtrl(param_1);
  pcVar15 = "%s: avgcnt = %d\n" + param_1 + 4;
  while( true ) {
    uVar5 = hc_get_chip_bcn_max_num(*(undefined4 *)(param_1 + 0xa797a0));
    bVar25 = 0x1f < uVar18;
    if (uVar18 != 0x20) {
      bVar25 = uVar5 <= uVar18;
    }
    uVar18 = uVar18 + 1;
    if (bVar25) break;
    *pcVar15 = '\0';
    pcVar15 = pcVar15 + 0x5834;
  }
  *(undefined1 *)(param_1 + 0x794cc5) = 0;
  *(undefined4 *)(param_1 + 0x794cc8) = 0;
  *(undefined1 *)(param_1 + 0x794cc6) = 0;
  *(undefined1 *)(param_1 + 0xa39fbb) = 0;
  *(undefined1 *)(param_1 + 0x79507d) = 0;
  *(undefined2 *)(param_1 + 0x79569e) = 0x14;
  *(undefined2 *)(param_1 + 0x7956a0) = 10;
  *(undefined1 *)(param_1 + 0x79564f) = 0;
  *(undefined1 *)(param_1 + 0x795688) = 0;
  *(undefined2 *)(param_1 + 0x7956a6) = 0x14;
  *(undefined2 *)(param_1 + 0x7956a2) = 300;
  *(undefined2 *)(param_1 + 0x7956a4) = 200;
  *(undefined2 *)(param_1 + 0x7956a8) = 5;
  *(undefined2 *)(param_1 + 0x7956aa) = 0x19;
  *(undefined1 *)(param_1 + 0x79564e) = 1;
  *(undefined4 *)(param_1 + 0x7956ac) = 0x5dc;
  *(undefined1 *)(param_1 + 0x795651) = 0xb5;
  __memzero(param_1 + 0x79568c,8);
  *(undefined1 *)(param_1 + 0x795689) = 0;
  __memzero(param_1 + 0x795694,8);
  *(undefined1 *)(param_1 + 0x795948) = 1;
  *(undefined1 *)(param_1 + 0x795945) = 1;
  *(undefined1 *)(param_1 + 0x795949) = 0;
  *(undefined1 *)(param_1 + 0x795946) = 0;
  uVar18 = 0;
  if (*(int *)("Get_RBIST_IQ_Data_Proc" + param_1 + 8) == 0x28720200) {
    uVar1 = 0xd;
  }
  else {
    uVar1 = 7;
  }
  *(undefined1 *)(param_1 + 0x795950) = uVar1;
  *(undefined4 *)(param_1 + 0x795048) = *(undefined4 *)(param_1 + 0x795044);
  *(undefined1 *)(param_1 + 0x794cd0) = 4;
  *(undefined2 *)(&DAT_00794c50 + param_1) = 100;
  *(undefined2 *)(param_1 + 0x795988) = 2;
  *(undefined1 *)(param_1 + 0x795990) = 2;
  *(undefined2 *)(param_1 + 0x79598a) = 0xffba;
  *(undefined2 *)(param_1 + 0x79598c) = 0x5a;
  *(undefined2 *)(param_1 + 0x79598e) = 0x6e;
  *(undefined1 *)(param_1 + 0x795984) = 1;
  *(undefined1 *)(param_1 + 0x7959a4) = 0;
  *(undefined1 *)(param_1 + 0x7959a5) = 0;
  *(undefined4 *)(param_1 + 0x794b50) = 100;
  *(undefined4 *)(param_1 + 0x794b4c) = 500;
  *(undefined1 *)(param_1 + 0x795951) = 0;
  *(uint *)(param_1 + 0x795124) = *(uint *)(param_1 + 0x795124) & 0xffffffed | 0x20;
  *(undefined1 *)(param_1 + 0xa39fa0) = 0;
  *(undefined4 *)(param_1 + 0xa39fa4) = 0xffffffff;
  greenap_init(param_1);
  cVar2 = *(char *)(param_1 + 0x286285);
  if (cVar2 == '\x01') {
    iVar3 = hc_get_chip_bcn_max_num(*(undefined4 *)(param_1 + 0xa797a0));
    "======== Badnode detector =============\nvow_bn_en = <0/1> 0:dieable, 1:enable\nvow_bn_mon_period = <period> ms\nvow_bn_fallback_th = <count>\nvow_bn_per_th = <TX PER>\n======== Airtime counter test =============\nvow_counter_test = <0/1> 0:dieable, 1:enable\nvow_counter_test_period = <period> ms\nvow_counter_test_band = <band>\nvow_counter_test_avgcnt = <average num> sec\nvow_counter_test_target = <wlanidx>\n======== DVT =============\nvow_dvt_en = <0/1> 0:dieable, 1:enable\nvow_monitor_sta = <STA num>\nvow_show_sta = <STA num>\nvow_monitor_bss = <BSS num>\nvow_monitor_mbss = <MBSS num>\nvow_show_mbss = <MBSS num>\nvow_avg_num = <average num> sec\n======== RED ===========\nvow_set_red_en = <0/1> 0:disable, 1:enable\nvow_set_red_show_sta = <STA num>\nvow_set_red_tar_delay = <tarDelay> us\n======== WATF ===========\nvow_watf_en = <0/1> 0:disable, 1:enable\nvow_watf_q = <level>-<quantum> unit 256us\nvow_watf_add_entry = <level>-<Addr>\nvow_watf_del_entry = <Addr>\n"
    [param_1 + 0xda] = (char)iVar3;
    if (iVar3 != 0) {
      do {
        local_38 = param_1 + 0x795a84;
        iVar3 = uVar18 * 0x5834;
        iVar17 = param_1 + iVar3;
        MAP_Init(param_1,"======== Badnode detector =============\nvow_bn_en = <0/1> 0:dieable, 1:enable\nvow_bn_mon_period = <period> ms\nvow_bn_fallback_th = <count>\nvow_bn_per_th = <TX PER>\n======== Airtime counter test =============\nvow_counter_test = <0/1> 0:dieable, 1:enable\nvow_counter_test_period = <period> ms\nvow_counter_test_band = <band>\nvow_counter_test_avgcnt = <average num> sec\nvow_counter_test_target = <wlanidx>\n======== DVT =============\nvow_dvt_en = <0/1> 0:dieable, 1:enable\nvow_monitor_sta = <STA num>\nvow_show_sta = <STA num>\nvow_monitor_bss = <BSS num>\nvow_monitor_mbss = <MBSS num>\nvow_show_mbss = <MBSS num>\nvow_avg_num = <average num> sec\n======== RED ===========\nvow_set_red_en = <0/1> 0:disable, 1:enable\nvow_set_red_show_sta = <STA num>\nvow_set_red_tar_delay = <tarDelay> us\n======== WATF ===========\nvow_watf_en = <0/1> 0:disable, 1:enable\nvow_watf_q = <level>-<quantum> unit 256us\nvow_watf_add_entry = <level>-<Addr>\nvow_watf_del_entry = <Addr>\n"
                         + param_1 + iVar3 + 0xe0);
        pcVar15 = "[RTMPSetInformation][BandIdx=%d] Ndis802_11DS\n" + iVar17 + 0x28;
        pcVar15[0] = '`';
        pcVar15[1] = -0x16;
        pcVar15[2] = '\0';
        pcVar15[3] = '\0';
        "Ac1 --> %uus(%u)\n"[iVar17 + 0xc] = '\0';
        "Ac1 --> %uus(%u)\n"[iVar17 + 0xb] = '\0';
        "Airtime control --> %s(%d)\n"[iVar17 + 0x18] = '\0';
        "Ac0 --> %uus(%u)\n"[iVar17 + 0xe] = '\0';
        ("%s: target = %d\n" + iVar17 + 0x12)[0] = '\0';
        ("%s: target = %d\n" + iVar17 + 0x12)[1] = '\0';
        "%s: period = %d\n"[iVar17] = '\x01';
        (&DAT_002b7af6)[iVar17] = (&DAT_002b7af6)[iVar17] & 0x80 | 0x21;
        "vow_watf_q_lv0: %d\n"[iVar17 + 0x10] = '\0';
        "pStaCfg->WpaPassPhrase"[iVar17 + 10] = '\0';
        "pStaCfg->WpaPassPhrase"[iVar17 + 0xb] = '\0';
        pcVar15 = "!!! Link UP, Port Not Secured! ignore this set::OID_802_11_BSSID_LIST_SCAN\n" +
                  iVar17 + 0x44;
        pcVar15[0] = -1;
        pcVar15[1] = '\0';
        pcVar15[2] = '\0';
        pcVar15[3] = '\0';
        __memzero("4/home/ws/zx279128s/packages/function/wlan/mtk/drivers/MT7915_V7.0.1.0/mt_wifi_ap/../mt_wifi/embedded/fsm/ap_mgmt_sync.c:%d assert 0failed\n"
                  + iVar17 + 0xb,0x1be0);
        pcVar23 = "%s: Recv Auth from %02x:%02x:%02x:%02x:%02x:%02x\n" + param_1 + iVar3 + 0x2b;
        __memzero(local_38,0x88);
        pcVar15 = "4/home/ws/zx279128s/packages/function/wlan/mtk/drivers/MT7915_V7.0.1.0/mt_wifi_ap/../mt_wifi/embedded/fsm/ap_mgmt_cntl.c:%d assert pAdfailed\n"
                  + iVar17 + 0x2f;
        pcVar15[0] = '\x01';
        pcVar15[1] = '\0';
        pcVar15[2] = '\0';
        pcVar15[3] = '\0';
        "4/home/ws/zx279128s/packages/function/wlan/mtk/drivers/MT7915_V7.0.1.0/mt_wifi_ap/../mt_wifi/embedded/fsm/ap_mgmt_cntl.c:%d assert pAdfailed\n"
        [iVar17 + 0x33] = '\x01';
        (
        "4/home/ws/zx279128s/packages/function/wlan/mtk/drivers/MT7915_V7.0.1.0/mt_wifi_ap/../mt_wifi/embedded/fsm/ap_mgmt_cntl.c:%d assert pAdfailed\n"
        + iVar17 + 0x35)[0] = -0x74;
        (
        "4/home/ws/zx279128s/packages/function/wlan/mtk/drivers/MT7915_V7.0.1.0/mt_wifi_ap/../mt_wifi/embedded/fsm/ap_mgmt_cntl.c:%d assert pAdfailed\n"
        + iVar17 + 0x35)[1] = '#';
        "Disallow new Association\n"[iVar17 + 0x10] = '\x01';
        "%s(): FIXME!!!Unexpected frame send to MgmtRing, need to assign the length!\n"
        [iVar17 + 0x2c] = '\x01';
        "Set_WscPinCode_Proc:: Checksum is invalid\n"[iVar17] = '\0';
        *(undefined1 *)(param_1 + 0x795a81) = 0;
        pcVar15 = "4/home/ws/zx279128s/packages/function/wlan/mtk/drivers/MT7915_V7.0.1.0/mt_wifi_ap/../mt_wifi/embedded/fsm/ap_mgmt_cntl.c:%d assert pAdfailed\n"
                  + iVar17 + 0x2b;
        pcVar15[0] = '\0';
        pcVar15[1] = '\0';
        pcVar15[2] = '\0';
        pcVar15[3] = '\0';
        pcVar15 = "4/home/ws/zx279128s/packages/function/wlan/mtk/drivers/MT7915_V7.0.1.0/mt_wifi_ap/../mt_wifi/embedded/fsm/ap_mgmt_cntl.c:%d assert pAdfailed\n"
                  + iVar17 + 0x37;
        pcVar15[0] = '\0';
        pcVar15[1] = '\0';
        pcVar15[2] = '\0';
        pcVar15[3] = '\0';
        pcVar15 = "4/home/ws/zx279128s/packages/function/wlan/mtk/drivers/MT7915_V7.0.1.0/mt_wifi_ap/../mt_wifi/embedded/fsm/ap_mgmt_cntl.c:%d assert pAdfailed\n"
                  + iVar17 + 0x3b;
        pcVar15[0] = '\0';
        pcVar15[1] = '\0';
        pcVar15[2] = '\0';
        pcVar15[3] = '\0';
        pcVar15 = "4/home/ws/zx279128s/packages/function/wlan/mtk/drivers/MT7915_V7.0.1.0/mt_wifi_ap/../mt_wifi/embedded/fsm/ap_mgmt_cntl.c:%d assert pAdfailed\n"
                  + iVar17 + 0x3f;
        pcVar15[0] = '\0';
        pcVar15[1] = '\0';
        pcVar15[2] = '\0';
        pcVar15[3] = '\0';
        pcVar15 = "PIN authentication or communication error occurs!!\nRegistrar does NOT accept the same PIN again!(PIN:%08u)\n"
                  + iVar17 + 0x68;
        pcVar15[0] = '\0';
        pcVar15[1] = '\0';
        pcVar15[2] = '\0';
        pcVar15[3] = '\0';
        "4/home/ws/zx279128s/packages/function/wlan/mtk/drivers/MT7915_V7.0.1.0/mt_wifi_ap/../mt_wifi/embedded/fsm/ap_mgmt_cntl.c:%d assert pAdfailed\n"
        [iVar17 + 0x44] = '\0';
        pcVar15 = "4/home/ws/zx279128s/packages/function/wlan/mtk/drivers/MT7915_V7.0.1.0/mt_wifi_ap/../mt_wifi/embedded/fsm/ap_mgmt_cntl.c:%d assert pAdfailed\n"
                  + iVar17 + 0x47;
        pcVar15[0] = '\0';
        pcVar15[1] = '\0';
        pcVar15[2] = '\0';
        pcVar15[3] = '\0';
        pcVar15 = "4/home/ws/zx279128s/packages/function/wlan/mtk/drivers/MT7915_V7.0.1.0/mt_wifi_ap/../mt_wifi/embedded/fsm/ap_mgmt_cntl.c:%d assert pAdfailed\n"
                  + iVar17 + 0x4f;
        pcVar15[0] = '\0';
        pcVar15[1] = '\0';
        pcVar15[2] = '\0';
        pcVar15[3] = '\0';
        "%s(): FIXME!!!Unexpected frame send to MgmtRing, need to assign the length!\n"
        [iVar17 + 0x2d] = '\0';
        "Set_WscPinCode_Proc:: Checksum is invalid\n"[iVar17 + 0x25] = '\0';
        pcVar15 = "Set_WscPinCode_Proc:: Checksum is invalid\n" + iVar17 + 0x28;
        pcVar15[0] = '\0';
        pcVar15[1] = '\0';
        pcVar15[2] = '\0';
        pcVar15[3] = '\0';
        do {
          cVar2 = RandomByte(param_1);
          pcVar23 = pcVar23 + 1;
          *pcVar23 = cVar2;
        } while (pcVar23 != "Disallow new Association\n" + param_1 + iVar3 + 0xf);
        pcVar15 = "%s(): Dongle Packet)\n" + param_1 + iVar3 + 0xb;
        do {
          cVar2 = RandomByte(param_1);
          pcVar15 = pcVar15 + 1;
          *pcVar15 = cVar2;
        } while (pcVar15 != "%s():Err!! pTxBlk->pMacEntry is NULL!!\n" + param_1 + iVar3 + 3);
        iVar17 = uVar18 * 0x5834;
        __memzero("Set_WscPinCode_Proc:: Checksum is invalid\n" + param_1 + iVar17 + 1,0x24);
        __memzero("IF(ra0) Set_WscPinCode_Proc::(PinCode=%d)\n" + param_1 + iVar17 + 0x14,0x25);
        __memzero("IF(ra0) Set_WscPinCode_Proc::(PinCode=%d)\n" + param_1 + iVar17 + 4,0x10);
        iVar17 = param_1 + iVar17;
        (&DAT_002bb04d)[iVar17] = 0;
        "!!! Driver is in Monitor Mode now !!!\n"[iVar17 + 0x18] = '\0';
        "!!! Driver is in Monitor Mode now !!!\n"[iVar17 + 0x19] = '\0';
        ("!!! Driver is in Monitor Mode now !!!\n" + iVar17 + 0x24)[0] = -0x80;
        ("!!! Driver is in Monitor Mode now !!!\n" + iVar17 + 0x24)[1] = '\0';
        pcVar15 = "!!! Link UP, ignore this set::OID_802_11_BSSID_LIST_SCAN\n" + iVar17 + 0x18;
        pcVar15[0] = '\0';
        pcVar15[1] = '\0';
        pcVar15[2] = '\0';
        pcVar15[3] = '\0';
        pcVar15 = "!!! Link UP, ignore this set::OID_802_11_BSSID_LIST_SCAN\n" + iVar17 + 0x14;
        pcVar15[0] = '\0';
        pcVar15[1] = '\0';
        pcVar15[2] = '\0';
        pcVar15[3] = '\0';
        "!!! Link UP, ignore this set::OID_802_11_BSSID_LIST_SCAN\n"[iVar17 + 0x1c] = '\0';
        pcVar15 = "!!! Link UP, ignore this set::OID_802_11_BSSID_LIST_SCAN\n" + iVar17 + 0x10;
        pcVar15[0] = '\0';
        pcVar15[1] = '\0';
        pcVar15[2] = '\0';
        pcVar15[3] = '\0';
        "!!! Driver is in Monitor Mode now !!!\n"[iVar17 + 0x12] = '\0';
        "!!! Driver is in Monitor Mode now !!!\n"[iVar17 + 0x11] = '\0';
        "%-10d, %d, %d%%\n"[iVar17 + 0xc] = '\x01';
        ("%-10d, %d, %d%%\n" + iVar17 + 2)[0] = '\0';
        ("%-10d, %d, %d%%\n" + iVar17 + 2)[1] = '\0';
        ("%-10d, %d, %d%%\n" + iVar17)[0] = '\0';
        ("%-10d, %d, %d%%\n" + iVar17)[1] = '\0';
        pcVar15 = "%-10d, %d, %d%%\n" + iVar17 + 4;
        pcVar15[0] = '\0';
        pcVar15[1] = '\0';
        pcVar15[2] = '\0';
        pcVar15[3] = '\0';
        "%-10d, %d, %d%%\n"[iVar17 + 8] = '\0';
        "%-10d, %d, %d%%\n"[iVar17 + 0xd] = '\x01';
        pcVar15 = "!!! Driver is in Monitor Mode now !!!\n" + iVar17 + 0x14;
        pcVar15[0] = '<';
        pcVar15[1] = '\0';
        pcVar15[2] = '\0';
        pcVar15[3] = '\0';
        "!!! Driver is in Monitor Mode now !!!\n"[iVar17 + 0x13] = '\x03';
        "Query::OID_802_11_STATISTICS(mem alloc failed)\n"[iVar17 + 9] = '\0';
        "Query::OID_802_11_STATISTICS(mem alloc failed)\n"[iVar17 + 0xb] = '\0';
        "Query::OID_802_11_STATISTICS(mem alloc failed)\n"[iVar17 + 8] = '\0';
        "Query::OID_802_11_STATISTICS(mem alloc failed)\n"[iVar17 + 0xc] = '\0';
        "Query::OID_802_11_STATISTICS(mem alloc failed)\n"[iVar17 + 10] = '\0';
        "Query::OID_802_11_STATISTICS(mem alloc failed)\n"[iVar17 + 0xd] = '\0';
        ("Query::OID_802_11_STATISTICS(mem alloc failed)\n" + iVar17 + 0x1e)[0] = '\0';
        ("Query::OID_802_11_STATISTICS(mem alloc failed)\n" + iVar17 + 0x1e)[1] = '\0';
        __memzero("Query::OID_802_11_STATISTICS(mem alloc failed)\n" + iVar17 + 0xe,0x10);
        pcVar15 = "vow_watf_q_lv1: %d\n" + param_1 + iVar3 + 0x12;
        do {
          pcVar15 = pcVar15 + 1;
          *pcVar15 = '\0';
        } while (pcVar15 != "vow_watf_q_lv3: %d\n" + param_1 + iVar3 + 0xf);
        iVar3 = uVar18 * 0x5834 + param_1;
        uVar18 = uVar18 + 1 & 0xff;
        "Wrong format, vow_watf_q=[Level]-[Quantum]\n[Level] should be among 0 to 3 !\n[Quantum] unit is 256us.\n"
        [iVar3 + 0x65] =
             "Wrong format, vow_watf_q=[Level]-[Quantum]\n[Level] should be among 0 to 3 !\n[Quantum] unit is 256us.\n"
             [iVar3 + 0x65] & 0x1fU | 0x20;
        "Wrong format, vow_watf_q=[Level]-[Quantum]\n[Level] should be among 0 to 3 !\n[Quantum] unit is 256us.\n"
        [iVar3 + 100] =
             "Wrong format, vow_watf_q=[Level]-[Quantum]\n[Level] should be among 0 to 3 !\n[Quantum] unit is 256us.\n"
             [iVar3 + 100] & 0xc0;
      } while (uVar18 < (byte)"======== Badnode detector =============\nvow_bn_en = <0/1> 0:dieable, 1:enable\nvow_bn_mon_period = <period> ms\nvow_bn_fallback_th = <count>\nvow_bn_per_th = <TX PER>\n======== Airtime counter test =============\nvow_counter_test = <0/1> 0:dieable, 1:enable\nvow_counter_test_period = <period> ms\nvow_counter_test_band = <band>\nvow_counter_test_avgcnt = <average num> sec\nvow_counter_test_target = <wlanidx>\n======== DVT =============\nvow_dvt_en = <0/1> 0:dieable, 1:enable\nvow_monitor_sta = <STA num>\nvow_show_sta = <STA num>\nvow_monitor_bss = <BSS num>\nvow_monitor_mbss = <MBSS num>\nvow_show_mbss = <MBSS num>\nvow_avg_num = <average num> sec\n======== RED ===========\nvow_set_red_en = <0/1> 0:disable, 1:enable\nvow_set_red_show_sta = <STA num>\nvow_set_red_tar_delay = <tarDelay> us\n======== WATF ===========\nvow_watf_en = <0/1> 0:disable, 1:enable\nvow_watf_q = <level>-<quantum> unit 256us\nvow_watf_add_entry = <level>-<Addr>\nvow_watf_del_entry = <Addr>\n"
                              [param_1 + 0xda]);
    }
    *(undefined1 *)(param_1 + 0xa7cbfa) = 1;
    *(undefined4 *)(param_1 + 0xa86c5c) = 0;
    __memzero(&DAT_003687fc + param_1,0x3000);
    (&DAT_0036b89f)[param_1] = 0;
    (&DAT_0036b8a1)[param_1] = 0;
    (&DAT_0036b8a0)[param_1] = 1;
    *(undefined4 *)(&DAT_0036b90c + param_1) = 300;
    (&DAT_003687e5)[param_1] = 0;
    *(undefined1 *)(param_1 + 0x794b19) = 0;
    *(undefined1 *)(param_1 + 0x794b18) = 0xff;
    *(undefined1 *)(param_1 + 0x794b25) = 1;
    (&DAT_003678fa)[param_1] = 0;
    (&DAT_003678fc)[param_1] = 0;
    (&DAT_003678f9)[param_1] = 2;
    MAP_Init(param_1,&DAT_0036db58 + param_1,2);
    (&DAT_00580eae)[param_1] = 0;
    (&DAT_0036e430)[param_1] = 0;
    (&DAT_0036e408)[param_1] = 1;
    (&DAT_0036e406)[param_1] = (&DAT_0036e406)[param_1] & 0x80 | 0x21;
    (&DAT_00580310)[param_1] = 0;
    s_format__t_id_task_id_task_prempt_00371a7c[param_1 + 0xd] = '\0';
    MAP_Init(param_1,&DAT_00581308 + param_1,2);
    *(undefined1 *)(param_1 + 0x79465e) = 0;
    (&DAT_00581be0)[param_1] = 0;
    (&DAT_00581bb8)[param_1] = 1;
    (&DAT_00581bb6)[param_1] = (&DAT_00581bb6)[param_1] & 0x80 | 0x21;
    *(undefined1 *)(param_1 + 0x793ac0) = 0;
    (&DAT_00585239)[param_1] = 0;
    (&DAT_0036b916)[param_1] = 0;
    *(undefined1 *)(param_1 + 0xa7cbe8) = 1;
    *(undefined1 *)(param_1 + 0xa7cbea) = 1;
    *(undefined1 *)(param_1 + 0xa7cbe9) = 6;
    *(undefined1 *)(param_1 + 0xa7cbeb) = 6;
    cVar2 = *(char *)(param_1 + 0x286285);
  }
  if (cVar2 == '\0') {
    __memzero(param_1 + 0xa77bc9,6);
    *(undefined1 *)(param_1 + 0xa77bcf) = 0;
    *(undefined1 *)(param_1 + 0xa77bd0) = 0;
    __memzero(param_1 + 0xa77bd1,0x20);
    *(undefined1 *)(param_1 + 0xa77bf1) = 0;
    *(undefined1 *)(param_1 + 0xa77bf2) = 0;
  }
  ("rtmp_read_dot11v_mbssid_cfg_from_file" + param_1 + 0x16)[0] = 'd';
  ("rtmp_read_dot11v_mbssid_cfg_from_file" + param_1 + 0x16)[1] = '\0';
  ("rtmp_read_dot11v_mbssid_cfg_from_file" + param_1 + 0x18)[0] = '\0';
  ("rtmp_read_dot11v_mbssid_cfg_from_file" + param_1 + 0x18)[1] = '\x02';
  "rtmp_read_dot11v_mbssid_cfg_from_file"[param_1 + 0x14] = '\x01';
  "rtmp_read_dot11v_mbssid_cfg_from_file"[param_1 + 0x1a] = '\x04';
  *(undefined1 *)(param_1 + 0x829222) = 1;
  "rtmp_read_dot11v_mbssid_cfg_from_file"[param_1 + 0x1b] = '8';
  __memzero(param_1 + 0xa1920,0x1e4038);
  *(undefined4 *)(param_1 + 0x285928) = 0;
  *(undefined4 *)(param_1 + 0x285924) = 0;
  *(undefined4 *)(param_1 + 0x28592c) = 0;
  *(undefined4 *)(param_1 + 0x285958) = 0;
  entrytb_aid_bitmap_init(iVar4,param_1 + 0x28594c);
  *(undefined1 *)(param_1 + 0x79596d) = 0;
  (&DAT_0036b830)[param_1] = 0;
  *(undefined4 *)(&DAT_0036b910 + param_1) = 0x400;
  (&DAT_0036b844)[param_1] = 0;
  *(undefined4 *)(&DAT_0036b834 + param_1) = 0;
  __init_waitqueue_head(param_1 + 0x36b838,"&x->wait",&tx_temp_dbg);
  sae_cfg_init(param_1,"pci_sw_int_handler" + param_1);
  puVar8 = (undefined4 *)(param_1 + 0xa77c4c);
  puVar9 = (undefined4 *)(param_1 + 0x829930);
  "RadarStateCheck"[param_1 + 0xe] = '\0';
  "RadarStateCheck"[param_1 + 0xf] = '\x01';
  "RadarStateCheck"[param_1 + 0xc] = '\0';
  pcVar15 = "RadarStateCheck" + param_1 + 0xc;
  pcVar15[0] = '\0';
  pcVar15[1] = '\0';
  pcVar15[2] = '\0';
  pcVar15[3] = '\0';
  "auth_fsm_peer_auth_rsp_at_seq2_action"[param_1] = '\x1b';
  *(undefined4 *)((int)&DAT_00296ea0 + param_1) = 0;
  *(undefined4 *)((int)&DAT_00296e9c + param_1) = 0;
  pcVar15 = "get_channel_by_reference" + param_1;
  pcVar15[0] = '\0';
  pcVar15[1] = '\0';
  pcVar15[2] = '\0';
  pcVar15[3] = '\0';
  *(undefined4 *)((int)&DAT_00296ea4 + param_1) = 0;
  puVar10 = puVar8;
  do {
    uVar20 = *puVar10;
    puVar10 = puVar10 + 2;
    *puVar9 = uVar20;
    puVar9 = puVar9 + 0x2bd;
  } while (puVar9 != (undefined4 *)(param_1 + 0x8d8d30));
  puVar10 = (undefined4 *)(param_1 + 0x8d8f08);
  do {
    uVar20 = *puVar8;
    puVar8 = puVar8 + 2;
    *puVar10 = uVar20;
    puVar10 = puVar10 + 0x2bd;
  } while (puVar10 != (undefined4 *)(param_1 + 0x988308));
  *(undefined1 *)(param_1 + 0x8292f0) = 1;
  *(undefined1 *)(param_1 + 0x8d88c8) = 1;
  __memzero(param_1 + 0x795a84,0x88);
  *(undefined1 *)(param_1 + 0x795a81) = 0;
  hc_init_ChCtrl(param_1);
  if (2 < DebugLevel) {
    printk(&_LC19);
  }
  *(undefined1 *)(param_1 + 0x794c52) = 0;
  __memzero(param_1 + 0x794c53,0x3b);
  *(undefined1 *)(param_1 + 0x794c8e) = 0;
  DfsParamInit(param_1);
  if (*(char *)(param_1 + 0x286285) == '\x01') {
    *(undefined1 *)(param_1 + 0xa37728) = 2;
    *(undefined1 *)(param_1 + 0xa37748) = 2;
  }
  *(undefined2 *)(param_1 + 0xa3773c) = 0;
  *(undefined1 *)(param_1 + 0xa37724) = 0;
  *(undefined4 *)(param_1 + 0xa37740) = 0;
  *(undefined1 *)(param_1 + 0xa37744) = 0;
  *(undefined4 *)(param_1 + 0xa37760) = 0;
  *(undefined2 *)(param_1 + 0xa3775c) = 0;
  *(undefined2 *)(param_1 + 0xa3772c) = 0x41;
  *(undefined2 *)(param_1 + 0xa3774c) = 0x41;
  *(undefined1 *)(param_1 + 0xa37725) = 10;
  *(undefined1 *)(param_1 + 0xa37745) = 10;
  *(undefined1 *)(param_1 + 0xa37730) = 1;
  *(undefined1 *)(param_1 + 0xa37750) = 1;
  scan_partial_init(param_1);
  *(undefined4 *)(&DAT_00580ee4 + param_1) = 0;
  (&DAT_00580ee8)[param_1] = 0;
  *(undefined4 *)(param_1 + 0x794694) = 0;
  *(undefined1 *)(param_1 + 0x794698) = 0;
  (&DAT_003678fb)[param_1] = 0;
  (&DAT_003678fd)[param_1] = 0;
  (&DAT_003678ff)[param_1] = 0;
  (&DAT_003678fe)[param_1] = 0;
  (&DAT_00367900)[param_1] = 0;
  *(undefined1 *)(param_1 + 0x79596c) = 0;
  *(undefined1 *)(iVar4 + 0x146) = 0;
  *(undefined1 *)(param_1 + 0xa789e0) = 1;
  *(undefined1 *)(param_1 + 0x795b0d) = 0;
  *(undefined4 *)(param_1 + 0xa7c228) = 0;
  *(undefined4 *)(param_1 + 0xa7bf40) = 0;
  *(undefined4 *)(param_1 + 0xa7c214) = 0;
  *(undefined2 *)(param_1 + 0xa7c210) = 0;
  *(undefined1 *)(param_1 + 0xa7c224) = 0;
  *(undefined4 *)(param_1 + 0xa7c0a8) = 0;
  *(undefined1 *)(param_1 + 0xa7c225) = 0;
  *(undefined4 *)(param_1 + 0xa7c22c) = 0;
  *(undefined4 *)(param_1 + 0xa7c230) = 0;
  *(undefined4 *)(param_1 + 0xa7c234) = 0;
  *(undefined4 *)(param_1 + 0xa7c238) = 0;
  *(undefined1 *)(param_1 + 0x795b14) = 0x14;
  *(undefined1 *)(param_1 + 0x795b15) = 5;
  *(undefined1 *)(param_1 + 0x795b0e) = 0;
  *(undefined4 *)(param_1 + 0x795b10) = 10;
  vow_variable_reset(param_1);
  *(undefined1 *)(param_1 + 0xa7beca) = 2;
  *(char **)(param_1 + 0xa78aa0) = "/tmp/WifiSpectrum_IQ.txt";
  *(char **)(param_1 + 0xa78aa4) = "/tmp/WifiSpectrum_LNA_LPF.txt";
  *(char **)(param_1 + 0xa78aa8) = "/tmp/InPhySniffer.txt";
  *(undefined1 *)(param_1 + 0xa78a54) = 0;
  *(undefined4 *)(param_1 + 0xa78a58) = 0;
  *(undefined4 *)(param_1 + 0xa78a50) = 0;
  *(undefined4 *)(param_1 + 0xa78a64) = 0;
  *(undefined4 *)(param_1 + 0xa78a68) = 0;
  *(undefined4 *)(param_1 + 0xa78a78) = 0;
  *(undefined4 *)(param_1 + 0xa78a7c) = 0;
  *(undefined4 *)(param_1 + 0xa78a6c) = 0;
  *(undefined4 *)(param_1 + 0xa78a70) = 0;
  *(undefined4 *)(param_1 + 0xa78a74) = 0;
  *(undefined4 *)(param_1 + 0xa78a88) = 0;
  *(undefined4 *)(param_1 + 0xa78a8c) = 0;
  *(undefined4 *)(param_1 + 0xa78a90) = 0;
  iVar3 = hc_get_chip_cap(*(undefined4 *)(param_1 + 0xa797a0));
  iVar3 = *(int *)(iVar3 + 0x168) << 5;
  iVar4 = os_alloc_mem(param_1,param_1 + 0xa78acc,iVar3);
  if ((iVar4 != 0) && (-1 < DebugLevel)) {
    printk("%s : Not enough memory for dynamic allocating !!\n","UserCfgInit");
  }
  os_zero_mem(*(undefined4 *)(param_1 + 0xa78acc),iVar3);
  if (((*(byte *)(param_1 + 0x286294) & 3) == 3) || ((*(byte *)(param_1 + 0x286294) & 1) != 0)) {
    *(undefined1 *)(param_1 + 0x794ab8) = 1;
    if (*(char *)(param_1 + 0x79504d) != '\0') {
      *(undefined1 *)(param_1 + 0x794ab8) = 2;
    }
    if (*(char *)(param_1 + 0x286285) == '\0') {
      *(uint *)(param_1 + 0x794c4c) = *(uint *)(param_1 + 0x794c4c) | 3;
      *(undefined1 *)(param_1 + 0x795128) = 0;
      *(uint *)(param_1 + 0x795124) = *(uint *)(param_1 + 0x795124) & 0xffff7fff;
      ("RadarStateCheck" + param_1 + 2)[0] = '\0';
      ("RadarStateCheck" + param_1 + 2)[1] = '\0';
      ("RadarStateCheck" + param_1)[0] = '\0';
      ("RadarStateCheck" + param_1)[1] = '\0';
      *(undefined1 *)(param_1 + 0xa37728) = 0;
      *(undefined1 *)(param_1 + 0xa37748) = 0;
    }
    piVar14 = (int *)(s_TotalTimeForDump_0x_x____d_secs__00371a28 + param_1 + 8);
    local_5c = (undefined1 *)0x0;
    iVar3 = param_1;
    while( true ) {
      puVar22 = &DAT_00580dac + iVar3;
      (&DAT_00580018)[iVar3] = 0;
      *(undefined2 *)(&DAT_0057fffc + iVar3) = 0;
      *puVar22 = 1;
      (&DAT_0036e430)[iVar3] = 0;
      *(undefined2 *)(&DAT_00580010 + iVar3) = 0;
      *(undefined4 *)(&DAT_00580024 + iVar3) = 0;
      *(undefined4 *)(&DAT_00580028 + iVar3) = 0;
      *(undefined4 *)(&DAT_0058001c + iVar3) = 1;
      (&DAT_0036e3e0)[iVar3] = 2;
      *(undefined4 *)(&DAT_00580308 + iVar3) = 0;
      *(undefined4 *)(&DAT_0058030c + iVar3) = 0;
      (&DAT_00580310)[iVar3] = 0;
      (&DAT_00580311)[iVar3] = 0;
      (&DAT_00580020)[iVar3] = 0;
      __memzero(&DAT_00580d20 + iVar3,0x24);
      (&DAT_00580021)[iVar3] = 0;
      (s__RB_FULL__Free_Queue_List___00371ba4 + iVar3 + 0x18)[0] = '\0';
      (s__RB_FULL__Free_Queue_List___00371ba4 + iVar3 + 0x18)[1] = '\0';
      *(undefined2 *)(&DAT_0057fffe + iVar3) = 3;
      s__RB_FULL__Free_Queue_List___00371ba4[iVar3 + 0x14] = '\x01';
      (&DAT_00580ccd)[iVar3] = 0;
      iVar4 = param_1 + (int)local_5c * 0x2137b0;
      (&DAT_0036e408)[iVar3] = 1;
      (&DAT_0036e406)[iVar4] = (&DAT_0036e406)[iVar4] & 0x80 | 0x21;
      (&DAT_00580ccb)[iVar3] = 0;
      (&DAT_0036e48c)[iVar3] = 0;
      if (*(int *)(&DAT_0036e490 + iVar3) == 0) {
        os_alloc_mem(0,&DAT_0036e490 + iVar3,0x90);
      }
      else if (1 < DebugLevel) {
        printk("non-NULL pEapolPktFromAP 0x%p\n");
      }
      *(uint *)(&DAT_0057ffbc + iVar3) = *(uint *)(&DAT_0057ffbc + iVar3) & 0xfffffffe;
      *(undefined4 *)(&DAT_00580004 + iVar3) = 0;
      *(undefined4 *)(&DAT_00580008 + iVar3) = 0;
      (&DAT_0058000c)[iVar3] = 0;
      (&DAT_00580c91)[iVar3] = 1;
      (&DAT_00580c90)[iVar3] = 1;
      puVar13 = (undefined1 *)(iVar3 + 0x37099b);
      (&DAT_00580c92)[iVar3] = 1;
      (&DAT_00580c93)[iVar3] = 0;
      (&DAT_0057ffc1)[iVar3] = 0;
      (&DAT_00580cc9)[iVar3] = 1;
      uVar18 = jiffies;
      *(uint *)(&DAT_0058035c + iVar3) = jiffies;
      if (1000 < uVar18) {
        *(uint *)(&DAT_0058035c + iVar3) = uVar18 - 1000;
      }
      __memzero(param_1 + 0x794abb,0x21);
      *(undefined4 *)(&DAT_0036ee3c + iVar3) = 0;
      *(undefined4 *)(&DAT_0036ee40 + iVar3) = 1;
      (&DAT_0036ee44)[iVar3] = 1;
      *(undefined2 *)(&DAT_0036ee46 + iVar3) = 0x238c;
      *(undefined4 *)(&DAT_0036ee4c + iVar3) = 0;
      pcVar15 = s__s_0x_x_0x_x__d__d__s_00371824 + iVar3 + 8;
      *(undefined4 *)(&DAT_0036ee48 + iVar3) = 0;
      *(undefined4 *)(&DAT_0036ee50 + iVar3) = 0;
      pcVar15[0] = '\0';
      pcVar15[1] = '\0';
      pcVar15[2] = '\0';
      pcVar15[3] = '\0';
      (&DAT_0036ee55)[iVar3] = 0;
      *(undefined4 *)(&DAT_0036ee58 + iVar3) = 0;
      *(undefined4 *)(&DAT_0036ee60 + iVar3) = 0;
      __memzero(&DAT_0036eeac + iVar3,0x1be0);
      __memzero(&DAT_00370acc + iVar3,0x3a8);
      (&DAT_00370a8d)[iVar3] = 0;
      (&DAT_0036eea0)[iVar3] = 1;
      (&DAT_0036eea1)[iVar3] = 1;
      (&DAT_0036f254)[iVar3] = 1;
      (&DAT_00370a8c)[iVar3] = 1;
      (&DAT_00370a90)[iVar3] = 0;
      s__________________________________0037172c[iVar3 + 0x30] = '\x02';
      *(undefined1 *)(param_1 + 0x794b18) = 0xff;
      s__s_0x_x_0x_x__d__d__s_00371824[iVar3 + 0xc] = '\0';
      s__sQ__d__d__d_00371880[iVar3 + 0x15] = '\x02';
      s____addtional_information_0037195c[iVar3 + 1] = '\0';
      s_exp_main__maybe_jump_from_RST_00371a08[iVar3 + 0x14] = '\0';
      do {
        uVar1 = RandomByte(param_1);
        puVar13 = puVar13 + 1;
        *puVar13 = uVar1;
      } while (puVar13 != (undefined1 *)(iVar3 + 0x3709ab));
      pcVar15 = s_exp_main__maybe_jump_from_RST_00371a08 + iVar3 + 0x1c;
      piVar12 = (int *)(s_exp_main__maybe_jump_from_RST_00371a08 + iVar3 + 0x18);
      pcVar15[0] = '\0';
      pcVar15[1] = '\0';
      pcVar15[2] = '\0';
      pcVar15[3] = '\0';
      *piVar12 = 0;
      os_alloc_mem(param_1,piVar12,0x900);
      if (*piVar12 != 0) {
        __memzero(*piVar12,0x900);
      }
      pcVar15 = s_TotalTimeForDump_0x_x____d_secs__00371a28 + iVar3 + 4;
      pcVar15[0] = '\0';
      pcVar15[1] = '\0';
      pcVar15[2] = '\0';
      pcVar15[3] = '\0';
      *piVar14 = 0;
      os_alloc_mem(param_1,piVar14,0x900);
      if (*piVar14 != 0) {
        __memzero(*piVar14,0x900);
      }
      pcVar15 = s_TotalTimeForDump_0x_x____d_secs__00371a28 + iVar3 + 0x1c;
      pcVar23 = s_TotalTimeForDump_0x_x____d_secs__00371a28 + iVar3 + 0x18;
      s_exp_main__maybe_jump_from_RST_00371a08[iVar3 + 0x15] = '\0';
      (s_TotalTimeForDump_0x_x____d_secs__00371a28 + iVar3)[0] = -0x80;
      (s_TotalTimeForDump_0x_x____d_secs__00371a28 + iVar3)[1] = '\0';
      pcVar15[0] = '\0';
      pcVar15[1] = '\0';
      pcVar15[2] = '\0';
      pcVar15[3] = '\0';
      pcVar15 = s_TotalTimeForDump_0x_x____d_secs__00371a28 + iVar3 + 0x14;
      pcVar23[0] = '\0';
      pcVar23[1] = '\0';
      pcVar23[2] = '\0';
      pcVar23[3] = '\0';
      s_TotalTimeForDump_0x_x____d_secs__00371a28[iVar3 + 0x20] = '\0';
      pcVar15[0] = '\0';
      pcVar15[1] = '\0';
      pcVar15[2] = '\0';
      pcVar15[3] = '\0';
      s____addtional_information_0037195c[iVar3 + 0x10] = '\x01';
      (s____addtional_information_0037195c + iVar3 + 6)[0] = '\0';
      (s____addtional_information_0037195c + iVar3 + 6)[1] = '\0';
      pcVar15 = s____addtional_information_0037195c + iVar3 + 8;
      (s____addtional_information_0037195c + iVar3 + 4)[0] = '\0';
      (s____addtional_information_0037195c + iVar3 + 4)[1] = '\0';
      pcVar15[0] = '\0';
      pcVar15[1] = '\0';
      pcVar15[2] = '\0';
      pcVar15[3] = '\0';
      s____addtional_information_0037195c[iVar3 + 0xc] = '\0';
      s____addtional_information_0037195c[iVar3 + 0x11] = '\x01';
      s____addtional_information_0037195c[iVar3 + 0x12] = '\0';
      __memzero(iVar3 + 0x580312,8);
      (&DAT_00580cca)[iVar3] = 0;
      *(undefined4 *)(&DAT_0057ffb0 + iVar3) = 400;
      __memzero(iVar3 + 0x580032,0x40);
      *(undefined4 *)(&DAT_00580074 + iVar3) = 0;
      (&DAT_00580cce)[iVar3] = 0;
      (&DAT_0057ffc2)[iVar3] = 0;
      piVar14 = piVar14 + 0x84dec;
      (&DAT_00580360)[iVar3] = 0;
      (&DAT_0036e70c)[iVar3] = 0;
      s_ENTRY_cos_set_reset_handler_00371c00[iVar3 + 4] = '\x01';
      (&DAT_00580ccc)[iVar3] = 0;
      s_ENTRY_cos_set_reset_handler_00371c00[iVar3 + 5] = '\0';
      (&DAT_00371cbe)[iVar3] = 0;
      iVar3 = iVar3 + 0x2137b0;
      *puVar22 = 1;
      if (local_5c == (undefined1 *)0x1) break;
      local_5c = (undefined1 *)0x1;
    }
  }
  uVar18 = *(uint *)("Get_RBIST_IQ_Data_Proc" + param_1 + 0xc) & 0xffff;
  if (uVar18 == 0x7626) {
LAB_0013b9e8:
    *(undefined1 *)(param_1 + 0xa7c240) = 3;
  }
  else {
    if (uVar18 == 0x7615) {
      *(undefined1 *)(param_1 + 0xa7c240) = 1;
      goto LAB_0013af48;
    }
    if (uVar18 == 0x7622) {
      *(undefined1 *)(param_1 + 0xa7c240) = 2;
      goto LAB_0013af48;
    }
    if (uVar18 == 0x7663 || uVar18 == 0x7626) goto LAB_0013b9e8;
    *(undefined1 *)(param_1 + 0xa7c240) = 0;
  }
  if (uVar18 == 0x7915) {
    *(undefined1 *)(param_1 + 0xa7c240) = 5;
  }
LAB_0013af48:
  local_5c = (undefined1 *)(param_1 + 0xa7c240);
  puVar19 = (undefined4 *)(param_1 + 0xa7c244);
  puVar13 = (undefined1 *)(param_1 + 0xa7c242);
  puVar9 = (undefined4 *)(param_1 + 0xa7c24c);
  puVar8 = (undefined4 *)(param_1 + 0xa7c254);
  puVar10 = (undefined4 *)(param_1 + 0xa7c25c);
  local_64 = (undefined4 *)(param_1 + 0xa7c264);
  local_60 = (undefined4 *)(param_1 + 0xa7c274);
  local_4c = (undefined4 *)(param_1 + 0xa7c26c);
  local_50 = (undefined1 *)(param_1 + 0xa7c27f);
  local_58 = (undefined4 *)(param_1 + 0xa7c2bc);
  local_54 = (undefined4 *)(param_1 + 0xa7c2c4);
  bVar25 = false;
  iVar3 = param_1;
  while( true ) {
    puVar11 = (undefined2 *)(iVar3 + 0xa7c2b0);
    local_5c = local_5c + 1;
    *local_5c = 0;
    puVar21 = (undefined2 *)(iVar3 + 0xa7c2b4);
    puVar19 = puVar19 + 1;
    *puVar19 = 250000;
    puVar13 = puVar13 + 1;
    *puVar13 = 0;
    puVar9 = puVar9 + 1;
    *puVar9 = 0;
    puVar24 = (undefined2 *)(iVar3 + 0xa7c2b8);
    puVar8 = puVar8 + 1;
    *puVar8 = 0;
    puVar10 = puVar10 + 1;
    *puVar10 = 0x92;
    local_64 = local_64 + 1;
    *local_64 = 0x13c;
    puVar6 = (undefined2 *)(iVar3 + 0xa7c2bc);
    puVar7 = (undefined2 *)(iVar3 + 0xa7c2de);
    local_60 = local_60 + 1;
    *local_60 = 10;
    iVar3 = iVar3 + 2;
    local_4c = local_4c + 1;
    *local_4c = 10;
    local_50 = local_50 + 1;
    *local_50 = 1;
    *puVar11 = 500;
    *puVar21 = 0x32;
    *puVar24 = 500;
    *puVar6 = 0x32;
    local_58 = local_58 + 1;
    *local_58 = 0xb8;
    local_54 = local_54 + 1;
    *local_54 = 0x170;
    *puVar7 = 0;
    if (bVar25) break;
    bVar25 = true;
  }
  *(undefined4 *)(param_1 + 0xa7c2d0) = 0;
  *(undefined4 *)(param_1 + 0xa7c2d4) = 0;
  *(undefined4 *)(param_1 + 0xa7c2d8) = 0;
  (&DAT_00a7c241)[param_1] = 1;
  *(undefined2 *)(param_1 + 0xa7c2f8) = 0;
  *(undefined4 *)(param_1 + 0xa7c300) = 0;
  *(undefined1 *)(param_1 + 0xa7c2fe) = 0;
  *(undefined2 *)(param_1 + 0xa7c2fa) = 0;
  *(undefined2 *)(param_1 + 0xa7c2fc) = 0;
  *(undefined1 *)(param_1 + 0xa7c3d8) = 0;
  *(undefined1 *)(param_1 + 0xa7c41c) = 0;
  *(undefined1 *)(param_1 + 0xa7c420) = 0;
  *(undefined4 *)(param_1 + 0xa7c424) = 0;
  *(undefined1 *)(param_1 + 0xa7c428) = 0;
  *(undefined1 *)(param_1 + 0xa7c429) = 0;
  *(undefined1 *)(param_1 + 0xa7c42c) = 0;
  *(undefined1 *)(param_1 + 0xa7c430) = 0;
  *(undefined4 *)(param_1 + 0xa7c434) = 0;
  *(undefined1 *)(param_1 + 0xa7c438) = 0;
  *(undefined1 *)(param_1 + 0xa7c439) = 0;
  *(undefined1 *)(param_1 + 0xa7c554) = 0;
  *(undefined2 *)(param_1 + 0xa7c548) = 0x5dc;
  *(undefined2 *)(param_1 + 0xa7c546) = 900;
  *(undefined2 *)(param_1 + 0xa7c54c) = 0x76c;
  *(undefined2 *)(param_1 + 0xa7c54a) = 0x76c;
  *(undefined2 *)(param_1 + 0xa7c54e) = 0x20;
  *(undefined4 *)(param_1 + 0xa7c550) = 5;
  *(undefined1 *)(param_1 + 0x79503b) = 1;
  *(undefined1 *)(param_1 + 0x79503c) = 1;
  *(undefined1 *)(param_1 + 0xa376a4) = 0x1e;
  *(undefined1 *)(param_1 + 0xa7cc53) = 0;
  *(undefined1 *)(param_1 + 0xa7cc2c) = 0xff;
  *(undefined1 *)(param_1 + 0xa7cc2d) = 0xff;
  *(undefined1 *)(param_1 + 0xa7cc2e) = 0xff;
  *(undefined1 *)(param_1 + 0xa7cc2f) = 0xff;
  *(undefined1 *)(param_1 + 0xa7cc30) = 0xff;
  *(undefined1 *)(param_1 + 0xa7cc31) = 0xff;
  *(undefined4 *)(param_1 + 0xa7cc28) = 0xffffffff;
  builtin_strncpy((char *)(param_1 + 0xa7cc33),"/med",4);
  builtin_strncpy((char *)(param_1 + 0xa7cc3b),"da1/",4);
  builtin_strncpy((char *)(param_1 + 0xa7cc43),"og.b",4);
  builtin_strncpy((char *)(param_1 + 0xa7cc37),"ia/s",4);
  builtin_strncpy((char *)(param_1 + 0xa7cc3f),"fw_l",4);
  ((char *)(param_1 + 0xa7cc47))[0] = 'i';
  ((char *)(param_1 + 0xa7cc47))[1] = 'n';
  *(char *)(param_1 + 0xa7cc49) = '\0';
  *(undefined1 *)(param_1 + 0x795a80) = 0;
  *(undefined1 *)(param_1 + 0xa7d0b4) = 0;
  *(undefined2 *)(param_1 + 0xa7d0b6) = 0;
  *(undefined2 *)(param_1 + 0xa7d0b8) = 0x14;
  __memzero(param_1 + 0xa7d0bc,0xa0);
  *(undefined1 *)(param_1 + 0xa7d165) = 0;
  *(undefined1 *)(param_1 + 0xa7d166) = 0;
  *(undefined1 *)(param_1 + 0xa7d167) = 1;
  *(undefined1 *)(param_1 + 0xa7c544) = 0;
  *(undefined1 *)(param_1 + 0xa7c545) = 0;
  if (DebugLevel < 3) {
    return;
  }
  printk("<-- UserCfgInit\n");
  return;
}

