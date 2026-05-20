// module: mt7915.ko
// function: ap_peer_reassoc_req_action @ 0x51724
// size: 8 bytes
//

/* WARNING: Removing unreachable block (ram,0x0004fa2c) */
/* WARNING: Removing unreachable block (ram,0x0004fa44) */
/* WARNING: Removing unreachable block (ram,0x0004fa48) */
/* WARNING: Removing unreachable block (ram,0x0004fa4c) */
/* WARNING: Removing unreachable block (ram,0x0004ef18) */
/* WARNING: Removing unreachable block (ram,0x0004f858) */

void ap_peer_reassoc_req_action(int param_1,int param_2)

{
  short sVar1;
  ushort uVar2;
  bool bVar3;
  bool bVar4;
  bool bVar5;
  byte bVar6;
  char cVar7;
  ushort uVar8;
  uint uVar9;
  int iVar10;
  int iVar11;
  undefined4 uVar12;
  undefined4 uVar13;
  undefined4 uVar14;
  int iVar15;
  uint uVar16;
  int iVar17;
  int iVar18;
  byte *pbVar19;
  undefined1 *__src;
  byte bVar20;
  uint uVar21;
  uint uVar22;
  char *pcVar23;
  undefined1 *puVar24;
  int iVar25;
  void *__src_00;
  size_t __n;
  int iVar26;
  uint uVar27;
  uint uVar28;
  uint uVar29;
  bool bVar30;
  ushort *puVar31;
  undefined1 *puVar32;
  byte *pbVar33;
  byte *pbStack_158;
  uint uStack_13c;
  undefined4 uStack_12c;
  undefined1 uStack_10c;
  byte bStack_10b;
  undefined1 uStack_10a;
  undefined1 uStack_109;
  undefined1 uStack_108;
  undefined1 uStack_107;
  ushort uStack_106;
  ushort uStack_104;
  ushort uStack_102;
  undefined1 *puStack_100;
  int iStack_fc;
  int iStack_f8;
  undefined1 *puStack_f4;
  int iStack_f0;
  undefined1 auStack_ec [12];
  int iStack_e0;
  undefined4 uStack_dc;
  undefined1 auStack_d8 [4];
  undefined4 uStack_d4;
  int iStack_d0;
  undefined4 uStack_cc;
  int iStack_c8;
  undefined1 uStack_c4;
  undefined1 uStack_c2;
  ushort uStack_c0;
  int iStack_b8;
  int aiStack_b0 [3];
  undefined2 uStack_a4;
  
  iVar25 = 0;
  puStack_100 = (undefined1 *)0x0;
  uStack_104 = 0;
  uStack_102 = 0;
  iStack_fc = 0;
  iStack_f8 = 0;
  uStack_10c = 0;
  iStack_e0 = 0;
  uStack_dc = 0;
  auStack_d8 = (undefined1  [4])0x0;
  uStack_d4 = 0;
  iStack_d0 = 0;
  uStack_cc = 0;
  if ((&DAT_003687e5)[param_1] == '\x01') {
    if (DebugLevel < 3) {
      return;
    }
    printk("Disallow new Association\n");
    puVar32 = puStack_100;
LAB_0004efb4:
    if (puVar32 == (undefined1 *)0x0) {
      return;
    }
    if (uStack_104 == 0) goto LAB_0004efc8;
  }
  else {
    os_alloc_mem(0,&puStack_100,0x310);
    if (puStack_100 == (undefined1 *)0x0) {
      if (DebugLevel < 0) {
        return;
      }
      printk("%s(): mem alloc failed\n","ap_cmm_peer_assoc_req_action");
      iVar25 = 0;
      puVar32 = puStack_100;
      goto LAB_0004efb4;
    }
    __memzero(puStack_100,0x310);
    puVar32 = puStack_100;
    iVar25 = FUN_0004e3dc(param_1,1,param_2,*(undefined4 *)(param_2 + 0x908),puStack_100);
    if (iVar25 == 0) {
      iVar25 = 0;
      puVar32 = puStack_100;
      goto LAB_0004efb4;
    }
    iVar25 = MacTableLookup(param_1,puStack_100 + 6);
    if (iVar25 == 0) {
      puVar32 = puStack_100;
      if (-1 < DebugLevel) {
        printk("NoAuth MAC - %02x:%02x:%02x:%02x:%02x:%02x\n",puStack_100[6],puStack_100[7],
               puStack_100[8],puStack_100[9],puStack_100[10],puStack_100[0xb]);
        puVar32 = puStack_100;
      }
      goto LAB_0004efb4;
    }
    bVar20 = *(byte *)(iVar25 + 0xe4);
    uVar9 = hc_get_chip_bcn_max_num(*(undefined4 *)(param_1 + 0xa797a0));
    if ((uVar9 <= bVar20) || (0x1f < *(byte *)(iVar25 + 0xe4))) {
      puVar32 = puStack_100;
      if (-1 < DebugLevel) {
        printk("%s():pEntry bounding invalid wdev(apidx=%d)\n","ap_cmm_peer_assoc_req_action",
               *(undefined1 *)(iVar25 + 0xe4));
        puVar32 = puStack_100;
      }
      goto LAB_0004efb4;
    }
    if (3 < DebugLevel) {
      printk("%s():pEntry->func_tb_idx=%d\n","ap_cmm_peer_assoc_req_action");
    }
    iVar10 = wdev_search_by_address(param_1,puStack_100);
    if (iVar10 == 0) {
      puVar32 = puStack_100;
      if (-1 < DebugLevel) {
        printk("Wrong Addr1 - %02x:%02x:%02x:%02x:%02x:%02x\n",*puStack_100,puStack_100[1],
               puStack_100[2],puStack_100[3],puStack_100[4],puStack_100[5]);
        puVar32 = puStack_100;
      }
      goto LAB_0004efb4;
    }
    cVar7 = *(char *)(iVar10 + 0xe);
    iVar11 = DebugLevel;
    if (cVar7 != *(char *)(iVar25 + 0xe4)) {
      if (-1 < DebugLevel) {
        puVar32 = (undefined1 *)(uint)*(byte *)(iVar25 + 0xee);
        printk("%s : @@ ERROR 1! - MAC=%02x:%02x:%02x:%02x:%02x:%02x, wdev->func_idx=%d, pEntry->func_tb_idx=%d, pEntry->wcid=%d\n"
               ,"ap_cmm_peer_assoc_req_action",*(undefined1 *)(iVar25 + 0xec),
               *(undefined1 *)(iVar25 + 0xed),puVar32,*(undefined1 *)(iVar25 + 0xef),
               *(undefined1 *)(iVar25 + 0xf0),*(undefined1 *)(iVar25 + 0xf1),cVar7,
               *(char *)(iVar25 + 0xe4),*(undefined2 *)(iVar25 + 0xe0));
        cVar7 = *(char *)(iVar10 + 0xe);
      }
      iVar11 = DebugLevel;
      *(char *)(iVar25 + 0xe4) = cVar7;
      *(undefined1 *)(iVar25 + 0xe5) = *(undefined1 *)(iVar10 + 0xe);
    }
    if ((iVar10 != *(int *)(iVar25 + 8) && *(int *)(iVar25 + 8) != 0) &&
       (*(int *)(iVar25 + 8) = iVar10, -1 < iVar11)) {
      puVar32 = (undefined1 *)(uint)*(byte *)(iVar25 + 0xee);
      printk("%s : @@ ERROR 2! MAC=%02x:%02x:%02x:%02x:%02x:%02x, pEntry->wcid=%d\n",
             "ap_cmm_peer_assoc_req_action",*(undefined1 *)(iVar25 + 0xec),
             *(undefined1 *)(iVar25 + 0xed),puVar32,*(undefined1 *)(iVar25 + 0xef),
             *(undefined1 *)(iVar25 + 0xf0),*(undefined1 *)(iVar25 + 0xf1),
             *(undefined2 *)(iVar25 + 0xe0));
      iVar11 = DebugLevel;
    }
    pbStack_158 = (byte *)(iVar10 + 0xade);
    uVar29 = (uint)*(byte *)(iVar10 + 0xe);
    uVar9 = (uint)(byte)puStack_100[0x37] + (uint)(byte)puStack_100[0x44];
    uVar27 = (uint)*(ushort *)(iVar25 + 0xe2);
    sVar1 = *(short *)(iVar10 + 0x18);
    if (uVar9 < (uint)*(byte *)(iVar10 + 0xade) + (uint)*(byte *)(iVar10 + 0xaeb)) {
      pbStack_158 = puStack_100 + 0x37;
      if (2 < iVar11) {
        printk("%s(): Support rate follow STA\'s settings\n","ap_cmm_peer_assoc_req_action",uVar9,
               pbStack_158,puVar32);
      }
    }
    else if (2 < iVar11) {
      printk("%s(): Support rate follow AP\'s settings\n","ap_cmm_peer_assoc_req_action",uVar9,sVar1
             ,puVar32);
    }
    iVar11 = wlan_operate_get_addht(iVar10);
    if ((*(uint *)(iVar10 + 0xb18) & 0x200000) == 0) {
      puVar32 = puStack_100;
      if (-1 < DebugLevel) {
        printk("%s(): AP is not ready, disallow new Association\n","ap_cmm_peer_assoc_req_action");
        puVar32 = puStack_100;
      }
      goto LAB_0004efb4;
    }
    if (*(short *)(iVar25 + 0xe0) == *(short *)(&DAT_002963c2 + param_1)) {
      if (2 < DebugLevel) {
        printk("\n%s: Clear Wcid = %d FragBuffer !!!!!\n","ap_cmm_peer_assoc_req_action",
               *(short *)(iVar25 + 0xe0),DebugLevel,puVar32);
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
    auStack_d8._0_2_ = sVar1;
    uStack_dc._0_3_ = CONCAT12(*(undefined1 *)(iVar10 + 0x1a),(undefined2)uStack_dc);
    uStack_dc = CONCAT31(uStack_dc._1_3_,1);
    iStack_d0 = iVar10;
    if ((((*(int *)(iVar25 + 0x1430) != 0) || (*(char *)(iVar25 + 0x1434) != '\0')) ||
        (*(int *)(iVar25 + 0x1438) != 0)) || (*(char *)(iVar25 + 0x143c) != '\0')) {
      if (-1 < DebugLevel) {
        printk("@@@ %s(): (wcid=%u), HTC_ICVErrCnt(%u), HTC_AAD_OM_Freeze(%u), HTC_AAD_OM_CountDown(%u),  HTC_AAD_OM_Freeze(%u) is in Asso. stage!\n"
               ,"ap_cmm_peer_assoc_req_action",*(undefined2 *)(iVar25 + 0xe0),
               *(int *)(iVar25 + 0x1430),*(undefined1 *)(iVar25 + 0x1434),
               *(undefined4 *)(iVar25 + 0x1438),*(undefined1 *)(iVar25 + 0x143c));
      }
      *(undefined4 *)(iVar25 + 0x1430) = 0;
      *(undefined1 *)(iVar25 + 0x1434) = 0;
      *(undefined4 *)(iVar25 + 0x1438) = 0;
      *(undefined1 *)(iVar25 + 0x143c) = 0;
    }
    if (*pbStack_158 == 0) {
LAB_0004f364:
      bVar4 = true;
    }
    else {
      bVar20 = pbStack_158[1] & 0x7f;
      if ((bVar20 - 2 & 0xfd) == 0 || (bVar20 == 0x16 || bVar20 == 0xb)) {
        pbVar19 = pbStack_158 + 1;
        do {
          if (pbVar19 == pbStack_158 + (byte)(*pbStack_158 - 1) + 1) goto LAB_0004f364;
          pbVar19 = pbVar19 + 1;
          bVar20 = *pbVar19 & 0x7f;
        } while ((bVar20 - 2 & 0xfd) == 0 || (bVar20 == 0x16 || bVar20 == 0xb));
      }
      bVar4 = false;
    }
    uStack_13c = *(int *)(param_2 + 0x908) - 0x1e;
    if (uStack_13c < 0x101) {
      uStack_13c = uStack_13c & 0xffff;
      __n = uStack_13c - 4;
    }
    else {
      __n = 0xfc;
      uStack_13c = 0x100;
    }
    memmove((void *)(iVar25 + 0x11f4),(void *)(param_2 + 0x18),4);
    memmove((void *)(iVar25 + 0x11f8),(void *)(param_2 + 0x22),__n);
    *(uint *)(iVar25 + 0x12f4) = uStack_13c;
    param_2 = param_2 + 0x918;
    uVar12 = ConvertToRssi(param_1,param_2,0);
    uVar13 = ConvertToRssi(param_1,param_2,1);
    uVar14 = ConvertToRssi(param_1,param_2,2);
    iVar15 = RTMPMaxRssi(param_1,uVar12,uVar13,uVar14);
    if (3 < DebugLevel) {
      printk("ra[%d] ASSOC_REQ Threshold = %d, PktMaxRssi=%d\n",(uint)*(byte *)(iVar25 + 0xe4),
             (int)"RT_OID_WSC_SET_PROFILE:: ProfileCnt = %d\n"
                  [(uint)*(byte *)(iVar25 + 0xe4) * 0x5834 + param_1 + 0x18],iVar15);
    }
    iVar18 = (int)"RT_OID_WSC_SET_PROFILE:: ProfileCnt = %d\n"
                  [(uint)*(byte *)(iVar25 + 0xe4) * 0x5834 + param_1 + 0x18];
    iVar26 = 0;
    if (iVar18 != 0) {
      iVar26 = iVar15 - iVar18;
    }
    if (iVar26 < 0 == (iVar18 != 0 && SBORROW4(iVar15,iVar18))) {
      bVar5 = false;
      if (2 < DebugLevel) {
        bVar5 = false;
        printk("Accept RSSI: ===> %d, %d\n",iVar18,iVar15);
      }
    }
    else if (DebugLevel < 0) {
      bVar5 = true;
    }
    else {
      bVar5 = true;
      printk("Reject this ASSOC_REQ due to Weak Signal.\n");
    }
    if ((*(char *)(param_1 + uVar27 * 0x620 + 0x2f762) == '\x01') &&
       (*(char *)(iVar25 + 0x562) == '\x01')) {
      uStack_104 = 0x1e;
      bVar3 = false;
    }
    else {
      if ((*(short *)(iVar25 + 0xf8) != 0) &&
         (((*(uint *)(iVar25 + 0x17c) & 3) != 3 || (*(char *)(iVar25 + 0x710) == '\x01')))) {
        memset(aiStack_b0,0,0x88);
        *(undefined1 *)(iVar25 + 0x515) = 0;
        __memzero(iVar25 + 0x34a,0x58);
        os_zero_mem(aiStack_b0,0x88);
        aiStack_b0[0] = 1;
        uStack_a4 = *(undefined2 *)(iVar25 + 0xe0);
        HW_ADDREMOVE_KEYTABLE(param_1,aiStack_b0);
        if (((*(uint *)(iVar25 + 0x17c) & 0x10048) != 0) || (*(char *)(iVar25 + 0x710) == '\x01')) {
          DOT1X_InternalCmdAction(param_1,iVar25,0);
        }
      }
      puVar32 = puStack_100;
      *(undefined1 *)(iVar25 + 0xd25) = 0;
      *(undefined1 *)(iVar25 + 0xd24) = puStack_100[0x193];
      if ((*(char *)(iVar10 + 0x3e15) == '\0') || (*(char *)(iVar10 + 0x3e14) != '\0')) {
        if (*(byte *)(iVar25 + 0xe4) <
            (byte)"======== Badnode detector =============\nvow_bn_en = <0/1> 0:dieable, 1:enable\nvow_bn_mon_period = <period> ms\nvow_bn_fallback_th = <count>\nvow_bn_per_th = <TX PER>\n======== Airtime counter test =============\nvow_counter_test = <0/1> 0:dieable, 1:enable\nvow_counter_test_period = <period> ms\nvow_counter_test_band = <band>\nvow_counter_test_avgcnt = <average num> sec\nvow_counter_test_target = <wlanidx>\n======== DVT =============\nvow_dvt_en = <0/1> 0:dieable, 1:enable\nvow_monitor_sta = <STA num>\nvow_show_sta = <STA num>\nvow_monitor_bss = <BSS num>\nvow_monitor_mbss = <MBSS num>\nvow_show_mbss = <MBSS num>\nvow_avg_num = <average num> sec\n======== RED ===========\nvow_set_red_en = <0/1> 0:disable, 1:enable\nvow_set_red_show_sta = <STA num>\nvow_set_red_tar_delay = <tarDelay> us\n======== WATF ===========\nvow_watf_en = <0/1> 0:disable, 1:enable\nvow_watf_q = <level>-<quantum> unit 256us\nvow_watf_add_entry = <level>-<Addr>\nvow_watf_del_entry = <Addr>\n"
                  [param_1 + 0xda]) {
          iVar15 = memcmp((void *)(iVar25 + 0xec),(void *)(iVar10 + 0x2f39),6);
          if (iVar15 == 0) {
            RTMPZeroMemory((void *)(iVar10 + 0x2f39),6);
            RTMPCancelTimer(iVar10 + 0x3ab0,aiStack_b0);
            *(undefined1 *)(iVar10 + 0x3aac) = 0;
            puVar32 = puStack_100;
          }
        }
        if (((puVar32[0x191] == '\0') && ((*(uint *)(iVar10 + 0x2c) & 0x12cf8) != 0)) &&
           (*(int *)(iVar10 + 0x12e4) != 0)) {
          *(undefined1 *)(iVar25 + 0xd24) = 1;
        }
      }
      if (((uint)(byte)"pStaCfg->WpaPassPhrase"[param_1 + uVar29 * 0x5834 + 5] !=
           (uint)(byte)puVar32[0x16]) ||
         (iVar15 = memcmp(puVar32 + 0x17,
                          "Set::OID_802_11_SET_PASSPHRASE, Failed (len less than 8 or greater than 64)!!\n"
                          + param_1 + uVar29 * 0x5834 + 0x34,
                          (uint)(byte)"pStaCfg->WpaPassPhrase"[param_1 + uVar29 * 0x5834 + 5]),
         iVar15 != 0)) goto LAB_0004efb4;
      if ((((*(char *)(iVar25 + 0xd24) == '\0') ||
           ((*(int *)(iVar10 + 0x12e4) == 0 || (*(char *)(iVar10 + 0x3e15) == '\0')))) ||
          (*(char *)(iVar10 + 0x3e14) == '\0')) ||
         (iVar15 = memcmp((void *)(iVar10 + 0x2f39),&ZERO_MAC_ADDR,6), iVar15 != 0)) {
        iVar15 = ApCheckAccessControlList(param_1,puVar32 + 6,*(undefined1 *)(iVar25 + 0xe4));
        if (iVar15 == 0) {
          bVar3 = true;
        }
        else {
          iVar15 = ApCheckMapBlackList(param_1,puStack_100 + 6,*(undefined1 *)(iVar25 + 0xe4));
          bVar3 = iVar15 == 0;
        }
      }
      else {
        bVar3 = false;
      }
      if (2 < DebugLevel) {
        printk("%s - MBSS(%d), receive %s request from %02x:%02x:%02x:%02x:%02x:%02x\n","ReASSOC",
               *(undefined1 *)(iVar25 + 0xe4),"ReASSOC",puStack_100[6],puStack_100[7],puStack_100[8]
               ,puStack_100[9],puStack_100[10],puStack_100[0xb]);
      }
      __ZTE_STA_Assoc_Process(param_1,3,0,0,0,0,iVar25,"ap_cmm_peer_assoc_req_action",0x754);
      puStack_f4 = auStack_ec;
      SupportRate(pbStack_158,&puStack_f4,&uStack_10a,&uStack_10c);
      *(undefined1 *)(iVar25 + 0xb7c) = uStack_10a;
      uVar9 = (byte)puStack_100[0x240] & 4;
      RTMPSetSupportMCS(param_1,1,iVar25,pbStack_158,uVar9,puStack_100 + 0x2a4,puStack_100 + 0x274,
                        (byte)puStack_100[0x240] & 1);
      puVar32 = puStack_100;
      uVar21 = (uint)*(byte *)(iVar25 + 0xe4);
      uVar16 = dot11_2_ra_rate(uStack_10c);
      uVar8 = *(ushort *)
               (
               "======== Badnode detector =============\nvow_bn_en = <0/1> 0:dieable, 1:enable\nvow_bn_mon_period = <period> ms\nvow_bn_fallback_th = <count>\nvow_bn_per_th = <TX PER>\n======== Airtime counter test =============\nvow_counter_test = <0/1> 0:dieable, 1:enable\nvow_counter_test_period = <period> ms\nvow_counter_test_band = <band>\nvow_counter_test_avgcnt = <average num> sec\nvow_counter_test_target = <wlanidx>\n======== DVT =============\nvow_dvt_en = <0/1> 0:dieable, 1:enable\nvow_monitor_sta = <STA num>\nvow_show_sta = <STA num>\nvow_monitor_bss = <BSS num>\nvow_monitor_mbss = <MBSS num>\nvow_show_mbss = <MBSS num>\nvow_avg_num = <average num> sec\n======== RED ===========\nvow_set_red_en = <0/1> 0:disable, 1:enable\nvow_set_red_show_sta = <STA num>\nvow_set_red_tar_delay = <tarDelay> us\n======== WATF ===========\nvow_watf_en = <0/1> 0:disable, 1:enable\nvow_watf_q = <level>-<quantum> unit 256us\nvow_watf_add_entry = <level>-<Addr>\nvow_watf_del_entry = <Addr>\n"
               + uVar21 * 0x5834 + param_1 + 0xf8);
      bVar30 = uVar16 == 3;
      if (uVar16 < 4) {
        bVar30 = (uVar8 & 0xfff7) == 4;
      }
      if (((bVar30) || (((uVar8 & 0xffc7) == 0 && ((*(uint *)(puVar32 + 0x240) & 1) == 0)))) ||
         (((uVar8 & 0x20) != 0 &&
          (((0xe < (byte)"======== Badnode detector =============\nvow_bn_en = <0/1> 0:dieable, 1:enable\nvow_bn_mon_period = <period> ms\nvow_bn_fallback_th = <count>\nvow_bn_per_th = <TX PER>\n======== Airtime counter test =============\nvow_counter_test = <0/1> 0:dieable, 1:enable\nvow_counter_test_period = <period> ms\nvow_counter_test_band = <band>\nvow_counter_test_avgcnt = <average num> sec\nvow_counter_test_target = <wlanidx>\n======== DVT =============\nvow_dvt_en = <0/1> 0:dieable, 1:enable\nvow_monitor_sta = <STA num>\nvow_show_sta = <STA num>\nvow_monitor_bss = <BSS num>\nvow_monitor_mbss = <MBSS num>\nvow_show_mbss = <MBSS num>\nvow_avg_num = <average num> sec\n======== RED ===========\nvow_set_red_en = <0/1> 0:disable, 1:enable\nvow_set_red_show_sta = <STA num>\nvow_set_red_tar_delay = <tarDelay> us\n======== WATF ===========\nvow_watf_en = <0/1> 0:disable, 1:enable\nvow_watf_q = <level>-<quantum> unit 256us\nvow_watf_add_entry = <level>-<Addr>\nvow_watf_del_entry = <Addr>\n"
                         [uVar21 * 0x5834 + param_1 + 0xfa] &&
            ((*(uint *)(puVar32 + 0x240) & 4) == 0)) && (*(char *)(param_1 + 0x79596c) != '\0'))))))
      {
        uVar8 = 0x12;
LAB_0004f738:
        uVar16 = (uint)*(byte *)(iVar25 + 0xe4);
        uStack_104 = uVar8;
      }
      else {
        if (*(int *)(iVar25 + 0xfc) - 1U < 2) {
          uVar2 = *(ushort *)(iVar25 + 0xe0);
          uStack_102 = *(ushort *)(iVar25 + 0xf8);
          *(undefined4 *)(iVar25 + 0xae8) = 0;
          *(undefined4 *)((uint)uVar2 * 0x620 + param_1 + 0x2f954) = 0;
          *(undefined4 *)(iVar25 + 0xb04) = 0;
          *(undefined4 *)(iVar25 + 0xaec) = 0;
          if (*(char *)(iVar25 + 0xd24) == '\0') {
            uVar8 = WPAValidateRSNIE("======== Badnode detector =============\nvow_bn_en = <0/1> 0:dieable, 1:enable\nvow_bn_mon_period = <period> ms\nvow_bn_fallback_th = <count>\nvow_bn_per_th = <TX PER>\n======== Airtime counter test =============\nvow_counter_test = <0/1> 0:dieable, 1:enable\nvow_counter_test_period = <period> ms\nvow_counter_test_band = <band>\nvow_counter_test_avgcnt = <average num> sec\nvow_counter_test_target = <wlanidx>\n======== DVT =============\nvow_dvt_en = <0/1> 0:dieable, 1:enable\nvow_monitor_sta = <STA num>\nvow_show_sta = <STA num>\nvow_monitor_bss = <BSS num>\nvow_monitor_mbss = <MBSS num>\nvow_show_mbss = <MBSS num>\nvow_avg_num = <average num> sec\n======== RED ===========\nvow_set_red_en = <0/1> 0:disable, 1:enable\nvow_set_red_show_sta = <STA num>\nvow_set_red_tar_delay = <tarDelay> us\n======== WATF ===========\nvow_watf_en = <0/1> 0:disable, 1:enable\nvow_watf_q = <level>-<quantum> unit 256us\nvow_watf_add_entry = <level>-<Addr>\nvow_watf_del_entry = <Addr>\n"
                                     + uVar21 * 0x5834 + param_1 + 0x10c,iVar25 + 0x17c,
                                     puVar32 + 0x92,puVar32[0x191]);
            if (uVar8 != 0) {
LAB_00051398:
              if (DebugLevel < 0) goto LAB_0004f738;
              printk("%s : invalid status code(%d) !!!\n","APBuildAssociation",uVar8);
              uVar16 = (uint)*(byte *)(iVar25 + 0xe4);
              uStack_104 = uVar8;
              goto LAB_0004f74c;
            }
            uVar22 = *(uint *)(iVar25 + 0x17c);
            if ((uVar22 & 0x2000) != 0) {
              uVar28 = iVar25 + 0xec;
              uVar9 = uVar28;
              iVar15 = is_rsne_pmkid_cache_match
                                 (puVar32 + 0x92,puVar32[0x191],&DAT_003687fc + param_1,
                                  *(undefined1 *)(iVar25 + 0xe4),uVar28,aiStack_b0);
              if ((iVar15 != 0) && (aiStack_b0[0] == -1)) {
                uVar8 = 0x35;
                goto LAB_00051398;
              }
              uVar22 = *(uint *)(iVar25 + 0x17c);
              if ((uVar22 & 0x2000) != 0) {
                uVar9 = 0;
                iVar15 = sae_get_pmk_cache("pci_sw_int_handler" + param_1,
                                           "======== Badnode detector =============\nvow_bn_en = <0/1> 0:dieable, 1:enable\nvow_bn_mon_period = <period> ms\nvow_bn_fallback_th = <count>\nvow_bn_per_th = <TX PER>\n======== Airtime counter test =============\nvow_counter_test = <0/1> 0:dieable, 1:enable\nvow_counter_test_period = <period> ms\nvow_counter_test_band = <band>\nvow_counter_test_avgcnt = <average num> sec\nvow_counter_test_target = <wlanidx>\n======== DVT =============\nvow_dvt_en = <0/1> 0:dieable, 1:enable\nvow_monitor_sta = <STA num>\nvow_show_sta = <STA num>\nvow_monitor_bss = <BSS num>\nvow_monitor_mbss = <MBSS num>\nvow_show_mbss = <MBSS num>\nvow_avg_num = <average num> sec\n======== RED ===========\nvow_set_red_en = <0/1> 0:disable, 1:enable\nvow_set_red_show_sta = <STA num>\nvow_set_red_tar_delay = <tarDelay> us\n======== WATF ===========\nvow_watf_en = <0/1> 0:disable, 1:enable\nvow_watf_q = <level>-<quantum> unit 256us\nvow_watf_add_entry = <level>-<Addr>\nvow_watf_del_entry = <Addr>\n"
                                           + uVar21 * 0x5834 + param_1 + 0x101,uVar28,0,0);
                if (iVar15 == 0) {
                  uVar8 = 1;
                  goto LAB_00051398;
                }
                uVar22 = *(uint *)(iVar25 + 0x17c);
              }
            }
            if (uVar22 == 0) {
              *(undefined4 *)(iVar25 + 0x17c) = 1;
              *(uint *)(iVar25 + 0x2c4) = *(uint *)(iVar25 + 0x2c4) | 1;
              *(uint *)(iVar25 + 0x3a4) = *(uint *)(iVar25 + 0x3a4) | 1;
            }
            if (2 < DebugLevel) {
              uVar9 = *(uint *)(iVar25 + 0x2c4);
              printk("%s : (AID#%d AKM=0x%x, PairwiseCipher=0x%x)\n","APBuildAssociation",
                     *(undefined2 *)(iVar25 + 0xf8),*(undefined4 *)(iVar25 + 0x17c),uVar9);
            }
          }
          memmove((void *)(iVar25 + 0x9d9),puVar32 + 0x92,(uint)(byte)puVar32[0x191]);
          cVar7 = puVar32[0x191];
          *(char *)(iVar25 + 0x9d8) = cVar7;
          if (uStack_102 != 0) {
            if ((cVar7 == '\0') && ((*(uint *)(iVar25 + 0x17c) & 0x12cf8) != 0)) {
              uVar16 = (uint)*(byte *)(iVar25 + 0xe4);
              iVar15 = uVar16 * 0x5834 + param_1;
              if (((*(int *)(
                            "4/home/ws/zx279128s/packages/function/wlan/mtk/drivers/MT7915_V7.0.1.0/mt_wifi_ap/../mt_wifi/embedded/fsm/ap_mgmt_cntl.c:%d assert pAdfailed\n"
                            + iVar15 + 0x2b) == 0) || (*(char *)(iVar25 + 0xd24) == '\0')) ||
                 (("%-10d, %d, %d%%\n"[iVar15 + 0xc] == '\0' &&
                  ("%-10d, %d, %d%%\n"[iVar15 + 0xd] != '\0')))) {
                if (DebugLevel < 3) {
                  uStack_104 = 0xc;
                }
                else {
                  printk("ASSOC - WSC_STATE_MACHINE is OFF.<WscConfMode = %d, apidx =%d>\n",
                         *(int *)(
                                 "4/home/ws/zx279128s/packages/function/wlan/mtk/drivers/MT7915_V7.0.1.0/mt_wifi_ap/../mt_wifi/embedded/fsm/ap_mgmt_cntl.c:%d assert pAdfailed\n"
                                 + iVar15 + 0x2b),uVar16,DebugLevel,uVar9);
                  uVar16 = (uint)*(byte *)(iVar25 + 0xe4);
                  uStack_104 = 0xc;
                }
                goto LAB_0004f74c;
              }
              *(undefined4 *)(iVar25 + 0xfc) = 2;
              *(undefined4 *)(iVar25 + 0x100) = 0;
              *(undefined1 *)((uint)uVar2 * 0x620 + param_1 + 0x2f762) = 2;
              if ((*(uint *)(iVar25 + 0x17c) & 0x2090) == 0) {
                if (((*(uint *)(iVar25 + 0x17c) & 0x10048) != 0) ||
                   ("Airtime control --> %s(%d)\n"[uVar21 * 0x5834 + param_1 + 0x18] == '\x01')) {
                  *(undefined4 *)(iVar25 + 0xadc) = 1;
                  *(undefined1 *)(iVar25 + 0x514) = 4;
                }
              }
              else {
                *(undefined4 *)(iVar25 + 0xadc) = 1;
                *(undefined1 *)(iVar25 + 0x514) = 7;
              }
            }
            else {
              iVar15 = hc_get_chip_cap(*(undefined4 *)(param_1 + 0xa797a0));
              uVar21 = (uint)*(byte *)(iVar25 + 0xe4);
              if ((byte)"======== Badnode detector =============\nvow_bn_en = <0/1> 0:dieable, 1:enable\nvow_bn_mon_period = <period> ms\nvow_bn_fallback_th = <count>\nvow_bn_per_th = <TX PER>\n======== Airtime counter test =============\nvow_counter_test = <0/1> 0:dieable, 1:enable\nvow_counter_test_period = <period> ms\nvow_counter_test_band = <band>\nvow_counter_test_avgcnt = <average num> sec\nvow_counter_test_target = <wlanidx>\n======== DVT =============\nvow_dvt_en = <0/1> 0:dieable, 1:enable\nvow_monitor_sta = <STA num>\nvow_show_sta = <STA num>\nvow_monitor_bss = <BSS num>\nvow_monitor_mbss = <MBSS num>\nvow_show_mbss = <MBSS num>\nvow_avg_num = <average num> sec\n======== RED ===========\nvow_set_red_en = <0/1> 0:disable, 1:enable\nvow_set_red_show_sta = <STA num>\nvow_set_red_tar_delay = <tarDelay> us\n======== WATF ===========\nvow_watf_en = <0/1> 0:disable, 1:enable\nvow_watf_q = <level>-<quantum> unit 256us\nvow_watf_add_entry = <level>-<Addr>\nvow_watf_del_entry = <Addr>\n"
                        [param_1 + 0xda] <= uVar21) {
                printk(&_LC51,0x6d,puVar32 + 0x240,
                       (uint)(byte)"======== Badnode detector =============\nvow_bn_en = <0/1> 0:dieable, 1:enable\nvow_bn_mon_period = <period> ms\nvow_bn_fallback_th = <count>\nvow_bn_per_th = <TX PER>\n======== Airtime counter test =============\nvow_counter_test = <0/1> 0:dieable, 1:enable\nvow_counter_test_period = <period> ms\nvow_counter_test_band = <band>\nvow_counter_test_avgcnt = <average num> sec\nvow_counter_test_target = <wlanidx>\n======== DVT =============\nvow_dvt_en = <0/1> 0:dieable, 1:enable\nvow_monitor_sta = <STA num>\nvow_show_sta = <STA num>\nvow_monitor_bss = <BSS num>\nvow_monitor_mbss = <MBSS num>\nvow_show_mbss = <MBSS num>\nvow_avg_num = <average num> sec\n======== RED ===========\nvow_set_red_en = <0/1> 0:disable, 1:enable\nvow_set_red_show_sta = <STA num>\nvow_set_red_tar_delay = <tarDelay> us\n======== WATF ===========\nvow_watf_en = <0/1> 0:disable, 1:enable\nvow_watf_q = <level>-<quantum> unit 256us\nvow_watf_add_entry = <level>-<Addr>\nvow_watf_del_entry = <Addr>\n"
                                   [param_1 + 0xda],uVar9);
                dump_stack();
                uVar21 = (uint)*(byte *)(iVar25 + 0xe4);
              }
              iVar26 = param_1 + uVar21 * 0x5834;
              pcVar23 = "======== Badnode detector =============\nvow_bn_en = <0/1> 0:dieable, 1:enable\nvow_bn_mon_period = <period> ms\nvow_bn_fallback_th = <count>\nvow_bn_per_th = <TX PER>\n======== Airtime counter test =============\nvow_counter_test = <0/1> 0:dieable, 1:enable\nvow_counter_test_period = <period> ms\nvow_counter_test_band = <band>\nvow_counter_test_avgcnt = <average num> sec\nvow_counter_test_target = <wlanidx>\n======== DVT =============\nvow_dvt_en = <0/1> 0:dieable, 1:enable\nvow_monitor_sta = <STA num>\nvow_show_sta = <STA num>\nvow_monitor_bss = <BSS num>\nvow_monitor_mbss = <MBSS num>\nvow_show_mbss = <MBSS num>\nvow_avg_num = <average num> sec\n======== RED ===========\nvow_set_red_en = <0/1> 0:disable, 1:enable\nvow_set_red_show_sta = <STA num>\nvow_set_red_tar_delay = <tarDelay> us\n======== WATF ===========\nvow_watf_en = <0/1> 0:disable, 1:enable\nvow_watf_q = <level>-<quantum> unit 256us\nvow_watf_add_entry = <level>-<Addr>\nvow_watf_del_entry = <Addr>\n"
                        + param_1 + uVar21 * 0x5834 + 0xe0;
              bVar20 = "======== Badnode detector =============\nvow_bn_en = <0/1> 0:dieable, 1:enable\nvow_bn_mon_period = <period> ms\nvow_bn_fallback_th = <count>\nvow_bn_per_th = <TX PER>\n======== Airtime counter test =============\nvow_counter_test = <0/1> 0:dieable, 1:enable\nvow_counter_test_period = <period> ms\nvow_counter_test_band = <band>\nvow_counter_test_avgcnt = <average num> sec\nvow_counter_test_target = <wlanidx>\n======== DVT =============\nvow_dvt_en = <0/1> 0:dieable, 1:enable\nvow_monitor_sta = <STA num>\nvow_show_sta = <STA num>\nvow_monitor_bss = <BSS num>\nvow_monitor_mbss = <MBSS num>\nvow_show_mbss = <MBSS num>\nvow_avg_num = <average num> sec\n======== RED ===========\nvow_set_red_en = <0/1> 0:disable, 1:enable\nvow_set_red_show_sta = <STA num>\nvow_set_red_tar_delay = <tarDelay> us\n======== WATF ===========\nvow_watf_en = <0/1> 0:disable, 1:enable\nvow_watf_q = <level>-<quantum> unit 256us\nvow_watf_add_entry = <level>-<Addr>\nvow_watf_del_entry = <Addr>\n"
                       [iVar26 + 0xfa];
              uVar8 = *(ushort *)(iVar25 + 0xe0);
              uVar2 = *(ushort *)
                       (
                       "======== Badnode detector =============\nvow_bn_en = <0/1> 0:dieable, 1:enable\nvow_bn_mon_period = <period> ms\nvow_bn_fallback_th = <count>\nvow_bn_per_th = <TX PER>\n======== Airtime counter test =============\nvow_counter_test = <0/1> 0:dieable, 1:enable\nvow_counter_test_period = <period> ms\nvow_counter_test_band = <band>\nvow_counter_test_avgcnt = <average num> sec\nvow_counter_test_target = <wlanidx>\n======== DVT =============\nvow_dvt_en = <0/1> 0:dieable, 1:enable\nvow_monitor_sta = <STA num>\nvow_show_sta = <STA num>\nvow_monitor_bss = <BSS num>\nvow_monitor_mbss = <MBSS num>\nvow_show_mbss = <MBSS num>\nvow_avg_num = <average num> sec\n======== RED ===========\nvow_set_red_en = <0/1> 0:disable, 1:enable\nvow_set_red_show_sta = <STA num>\nvow_set_red_tar_delay = <tarDelay> us\n======== WATF ===========\nvow_watf_en = <0/1> 0:disable, 1:enable\nvow_watf_q = <level>-<quantum> unit 256us\nvow_watf_add_entry = <level>-<Addr>\nvow_watf_del_entry = <Addr>\n"
                       + iVar26 + 0xf8);
              *(undefined4 *)(iVar25 + 0x100) = 0;
              *(undefined4 *)(iVar25 + 0xfc) = 2;
              uVar9 = (uint)(byte)"Wrong format, vow_watf_q=[Level]-[Quantum]\n[Level] should be among 0 to 3 !\n[Quantum] unit is 256us.\n"
                                  [iVar26 + 0x5d];
              if (uVar16 <= (byte)"Wrong format, vow_watf_q=[Level]-[Quantum]\n[Level] should be among 0 to 3 !\n[Quantum] unit is 256us.\n"
                                  [iVar26 + 0x5d]) {
                uVar9 = uVar16;
              }
              *(char *)(iVar25 + 0xb7d) = (char)uVar9;
              MacTableSetEntryPhyCfg(param_1,iVar25);
              *(undefined2 *)(iVar25 + 0xaf6) = *(undefined2 *)(puVar32 + 0x12);
              if ((*(uint *)(iVar25 + 0x17c) & 0x2090) == 0) {
                if (((*(uint *)(iVar25 + 0x17c) & 0x10048) != 0) ||
                   ("Airtime control --> %s(%d)\n"[iVar26 + 0x18] == '\x01')) {
                  *(undefined4 *)(iVar25 + 0xadc) = 1;
                  *(undefined1 *)(iVar25 + 0x514) = 4;
                }
              }
              else {
                *(undefined4 *)(iVar25 + 0xadc) = 1;
                *(undefined1 *)(iVar25 + 0x514) = 7;
              }
              MacTableSetEntryRaCap(param_1,iVar25,puVar32 + 0x260);
              if ((*(uint *)(puVar32 + 0x240) & 4) != 0) {
                MacTableEntryCheck2GVHT(param_1,iVar25);
              }
              *(undefined1 *)((uint)uVar8 * 0x620 + param_1 + 0x2f762) = 2;
              if (("%s: avgcnt = %d\n"[uVar21 * 0x5834 + param_1] == '\0') ||
                 (puVar32[0x192] == '\0')) {
                *(uint *)(iVar25 + 0xb4) = *(uint *)(iVar25 + 0xb4) & 0xfffffffe;
              }
              else {
                *(uint *)(iVar25 + 0xb4) = *(uint *)(iVar25 + 0xb4) | 1;
              }
              iVar26 = DebugLevel;
              if (((*(char *)(param_1 + 0x795984) == '\0') ||
                  ((*(uint *)(iVar25 + 0x2c4) & 0x1e) == 0)) ||
                 ((*(uint *)(iVar25 + 0x2c4) & 0x20) != 0)) {
                uVar9 = *(uint *)(puVar32 + 0x240);
              }
              else {
                uVar9 = *(uint *)(puVar32 + 0x240) & 0xfffffffa;
                *(uint *)(puVar32 + 0x240) = uVar9;
                if (2 < iVar26) {
                  printk("%s : Force the STA as Non-HT mode\n","update_associated_mac_entry");
                  uVar9 = *(uint *)(puVar32 + 0x240);
                }
              }
              if ((((uVar9 & 1) == 0) || ("%s: per %u.\n"[uVar21 * 0x5834 + param_1 + 1] == '\0'))
                 || ((uVar2 & 0x18) == 0)) {
                *(undefined1 *)(param_1 + 0x285942) = 1;
                __memzero(iVar25 + 0xca4,0x1a);
                *(byte *)(iVar25 + 0xbfe) = *(byte *)(iVar25 + 0xbfe) & 0xfb;
                *(undefined4 *)(iVar25 + 0xc04) = 0;
                __memzero(iVar25 + 0xd14,0xc);
                *(undefined2 *)(iVar25 + 0xc08) = 0;
                *(undefined2 *)(iVar25 + 0xc0a) = 0;
                *(undefined2 *)(iVar25 + 0xc0c) = 0;
                uStack_12c = 0;
                *(undefined2 *)(iVar25 + 0xc0e) = 0;
                *(byte *)(iVar25 + 0xbfe) = *(byte *)(iVar25 + 0xbfe) & 0xf7;
              }
              else {
                puVar24 = puVar32 + 0x274;
                ht_mode_adjust(param_1,iVar25,puVar24);
                if ((puVar32[0x194] & 1) != 0) {
                  *(undefined1 *)(iVar25 + 0xd11) = 1;
                }
                if ((puVar32[0x196] & 8) != 0) {
                  *(undefined1 *)(iVar25 + 0xd22) = 1;
                }
                if ((puVar32[0x275] & 0x40) != 0) {
                  iVar26 = wlan_operate_get_ht_bw(pcVar23);
                  iVar18 = wlan_config_get_ht_bw(pcVar23);
                  iVar17 = wlan_operate_get_ext_cha(pcVar23);
                  bVar30 = bVar20 == 0xe;
                  if (bVar20 < 0xf) {
                    bVar30 = iVar18 == 1;
                  }
                  *(undefined1 *)(iVar25 + 0xd12) = 1;
                  *(undefined1 *)(param_1 + 0x285948) = 1;
                  if (((bVar30) && (*(char *)(param_1 + 0x79564e) == '\x01')) &&
                     (iVar26 != 0 && iVar17 != 0)) {
                    *(byte *)(param_1 + 0x7956b4) = *(byte *)(param_1 + 0x7956b4) | 4;
                    wlan_operate_set_ht_bw(pcVar23,0,0);
                    iVar26 = DebugLevel;
                    *(byte *)(param_1 + 0x795652) = *(byte *)(param_1 + 0x795652) | 2;
                    if (3 < iVar26) {
                      printk("%s, Update Beacon for mbss_idx:%d\n","update_associated_mac_entry",
                             *(undefined1 *)(iVar25 + 0xe4));
                    }
                    UpdateBeaconHandler(param_1,pcVar23,2);
                  }
                  if (2 < DebugLevel) {
                    printk("pEntry set 40MHz Intolerant as 1\n");
                  }
                  Handle_BSS_Width_Trigger_Events(param_1,bVar20);
                }
                if (((ushort)((ushort)(0xe < bVar20) & uVar2 >> 5) == 0) ||
                   ((*(uint *)(puVar32 + 0x240) & 4) == 0)) {
                  uStack_12c = mt_WrapClientSupportsETxBF(param_1,puVar32 + 0x289);
                }
                else {
                  uStack_12c = mt_WrapClientSupportsVhtETxBF(param_1,puVar32 + 0x2a4);
                }
                *(undefined1 *)(iVar25 + 0x14b8) = (undefined1)uStack_12c;
                bVar6 = get_ht_max_mcs("%s: per %u.\n" + param_1 + uVar21 * 0x5834 + 3,
                                       puVar32 + 0x277);
                *(byte *)(iVar25 + 0xbe) = *(byte *)(iVar25 + 0xbe) & 0xc0 | bVar6 & 0x3f;
                iVar26 = param_1 + uVar21 * 0x5834;
                if (((&DAT_002b7af6)[iVar26] & 0x7f) != 0x21) {
                  if (2 < DebugLevel) {
                    printk("@@@ IF-ra%d DesiredTransmitSetting.field.MCS = %d\n",
                           *(undefined1 *)(iVar25 + 0xe4),(&DAT_002b7af6)[iVar26] & 0x7f);
                  }
                  iVar26 = uVar21 * 0x5834 + param_1;
                  set_ht_fixed_mcs(iVar25,(&DAT_002b7af6)[iVar26] & 0x7f,
                                   "%s: period = %d\n"[iVar26 + 2] & 0x3f);
                }
                set_sta_ht_cap(param_1,iVar25,puVar24);
                memmove((void *)(iVar25 + 0xca4),puVar24,0x1a);
                if ((*(uint *)(puVar32 + 0x240) & 4) != 0) {
                  __src = puVar32 + 0x2a4;
                  puVar24 = (undefined1 *)0x0;
                  if ((*(uint *)(puVar32 + 0x240) & 8) != 0) {
                    puVar24 = puVar32 + 0x2b0;
                  }
                  vht_mode_adjust(param_1,iVar25,__src,puVar24);
                  dot11_vht_mcs_to_internal_mcs(param_1,pcVar23,__src,iVar25 + 0xbe);
                  if (3 < DebugLevel) {
                    uVar12 = get_phymode_str(*(byte *)(iVar25 + 0xbf) >> 5);
                    uVar13 = get_bw_str(((uint)*(ushort *)(iVar25 + 0xbe) << 0x17) >> 0x1e);
                    printk("%s(): Peer\'s PhyCap=>Mode:%s, BW:%s, NSS:%d, MCS:%d\n",
                           "update_associated_mac_entry",uVar12,uVar13,
                           ((*(byte *)(iVar25 + 0xbe) & 0x3f) >> 4) + 1,
                           *(byte *)(iVar25 + 0xbe) & 0xf);
                  }
                  set_vht_cap(param_1,iVar25,__src);
                  memmove((void *)(iVar25 + 0xd14),__src,0xc);
                }
                iVar26 = DebugLevel;
                if ((*(uint *)(puVar32 + 0x2b4) & 0xff8000) == 0x10000) {
                  bVar6 = puVar32[0x2b5];
                  *(undefined1 *)(iVar25 + 0xd20) = 1;
                  *(byte *)(iVar25 + 0xd21) = bVar6;
                  if (0 < iVar26) {
                    printk("%s(): Peer\'s OperatingMode=>RxNssType: %d, RxNss: %d, ChBW: %d\n",
                           "update_associated_mac_entry",bVar6 >> 7,((uint)bVar6 << 0x19) >> 0x1d,
                           bVar6 & 3);
                    goto LAB_00050f20;
                  }
                }
                else {
                  *(undefined1 *)(iVar25 + 0xd20) = 0;
LAB_00050f20:
                  if (0 < DebugLevel) {
                    printk("%s(): Peer\'s bw: %d, extChanOffset: %d, RecomWidth: %d\n",
                           "update_associated_mac_entry",
                           ((uint)*(ushort *)(iVar25 + 0xbe) << 0x17) >> 0x1e,
                           (byte)puVar32[0x28f] & 3,((uint)(byte)puVar32[0x28f] << 0x1d) >> 0x1f);
                  }
                }
                bVar30 = bVar20 == 0xe;
                if (bVar20 < 0xf) {
                  bVar30 = (*(ushort *)(iVar25 + 0xbe) & 0x180) == 0x80;
                }
                if (((bVar30) && ((*(uint *)(puVar32 + 0x240) & 2) != 0)) &&
                   (bVar20 = puVar32[0x28f], (bVar20 & 7) == 0)) {
                  *(byte *)(iVar25 + 0xd21) =
                       *(byte *)(iVar25 + 0xd21) & 0x7c | bVar20 & 3 | bVar20 << 7;
                  cVar7 = wlan_operate_get_rx_stream(pcVar23);
                  iVar26 = DebugLevel;
                  bVar20 = *(byte *)(iVar25 + 0xd21);
                  *(undefined1 *)(iVar25 + 0xd20) = 1;
                  bVar6 = cVar7 - 1U & 7;
                  *(byte *)(iVar25 + 0xd21) = bVar20 & 0x8f | bVar6 << 4;
                  if (0 < iVar26) {
                    printk("%s(): Special Peer\'s OperatingMode=>RxNssType: %d, RxNss: %d, ChBW: %d\n"
                           ,"update_associated_mac_entry",bVar20 >> 7,bVar6,bVar20 & 3);
                  }
                }
                if (((uVar2 & 0x1c0) != 0) && ((*(uint *)(puVar32 + 0x240) & 0x10) != 0)) {
                  update_peer_he_caps(iVar25,puVar32 + 0x240);
                  he_mode_adjust(pcVar23,iVar25);
                }
              }
              *(undefined2 *)(iVar25 + 0x176) = 0;
              *(undefined1 *)(iVar25 + 0xb7f) = *(undefined1 *)(iVar25 + 0xb7d);
              *(undefined2 *)(iVar25 + 0xbc) = *(undefined2 *)(iVar25 + 0xbe);
              if (*(char *)(iVar15 + 0x96) != '\0') {
                chip_tx_bf_init(param_1,iVar25,puVar32,uStack_12c);
              }
              if (*(int *)(iVar15 + 0x30) == 2) {
                iVar15 = uVar21 * 0x5834 + param_1;
                if ("%s: period = %d\n"[iVar15] == '\x01') {
                  *(undefined1 *)(iVar25 + 0xb7e) = 1;
                }
                else {
                  bVar20 = "%s: period = %d\n"[iVar15 + 2];
                  *(undefined1 *)(iVar25 + 0xb7e) = 0;
                  *(byte *)(iVar25 + 0xbc) = *(byte *)(iVar25 + 0xbc) & 0xc0 | bVar20 & 0x3f;
                  if (0x7f < *(byte *)(iVar25 + 0xbd)) {
                    bVar20 = (&DAT_002b7af6)[iVar15];
                    cVar7 = wlan_operate_get_tx_stream(pcVar23);
                    *(byte *)(iVar25 + 0xbc) =
                         *(byte *)(iVar25 + 0xbc) & 0xc0 |
                         (bVar20 & 0x7f) + (cVar7 + -1) * '\x10' & 0x3f;
                  }
                  RTMPUpdateLegacyTxSetting
                            (((uint)(byte)(&DAT_002b7af7)[uVar21 * 0x5834 + param_1] << 0x1a) >>
                             0x1d,iVar25);
                }
              }
              if ((*(byte *)(iVar25 + 0xbf) & 0xc0) == 0) {
                *(undefined1 *)(param_1 + 0x285942) = 1;
              }
              _raw_spin_lock_bh(param_1 + 0x285958);
              nonerp_sta_num(iVar25,0);
              _raw_spin_unlock_bh(param_1 + 0x285958);
              ApUpdateCapabilityAndErpIe(param_1,pcVar23);
              APUpdateOperationMode(param_1,pcVar23);
            }
            uStack_104 = 0;
            if (*(int *)(iVar25 + 0xfc) == 2) {
              update_sta_conn_state(*(undefined4 *)(iVar25 + 8),iVar25);
            }
            uVar16 = (uint)*(byte *)(iVar25 + 0xe4);
            goto LAB_0004f74c;
          }
        }
        uVar16 = (uint)*(byte *)(iVar25 + 0xe4);
        uStack_104 = 0x11;
      }
LAB_0004f74c:
      if ((uVar16 < (byte)"======== Badnode detector =============\nvow_bn_en = <0/1> 0:dieable, 1:enable\nvow_bn_mon_period = <period> ms\nvow_bn_fallback_th = <count>\nvow_bn_per_th = <TX PER>\n======== Airtime counter test =============\nvow_counter_test = <0/1> 0:dieable, 1:enable\nvow_counter_test_period = <period> ms\nvow_counter_test_band = <band>\nvow_counter_test_avgcnt = <average num> sec\nvow_counter_test_target = <wlanidx>\n======== DVT =============\nvow_dvt_en = <0/1> 0:dieable, 1:enable\nvow_monitor_sta = <STA num>\nvow_show_sta = <STA num>\nvow_monitor_bss = <BSS num>\nvow_monitor_mbss = <MBSS num>\nvow_show_mbss = <MBSS num>\nvow_avg_num = <average num> sec\n======== RED ===========\nvow_set_red_en = <0/1> 0:disable, 1:enable\nvow_set_red_show_sta = <STA num>\nvow_set_red_tar_delay = <tarDelay> us\n======== WATF ===========\nvow_watf_en = <0/1> 0:disable, 1:enable\nvow_watf_q = <level>-<quantum> unit 256us\nvow_watf_add_entry = <level>-<Addr>\nvow_watf_del_entry = <Addr>\n"
                          [param_1 + 0xda]) && (*(char *)(iVar10 + 0xb21) == '\x01')) {
        uVar12 = *(undefined4 *)(puStack_100 + 0x1a3);
        *(undefined4 *)(iVar25 + 0x11ec) = *(undefined4 *)(puStack_100 + 0x19f);
        *(undefined4 *)(iVar25 + 0x11f0) = uVar12;
      }
      if (((*(uint *)(puStack_100 + 0x240) & 4) != 0) && ((*(ushort *)(iVar10 + 0x18) & 0x20) != 0))
      {
        if (3 < DebugLevel) {
          printk("%s():Peer is VHT capable device!\n","ap_cmm_peer_assoc_req_action");
        }
        memmove((void *)(iVar25 + 0xc84),puStack_100 + 0x194,0xb);
        if (3 < DebugLevel) {
          printk("\tOperatingModeNotification=%d\n",
                 ((uint)*(byte *)(iVar25 + 0xc8b) << 0x19) >> 0x1f);
        }
      }
    }
    iVar15 = os_alloc_mem(param_1,&iStack_fc,0x900);
    puVar32 = puStack_100;
    if (iVar15 != 0) goto LAB_0004efb4;
    if (2 < DebugLevel) {
      printk("%s - Send %s response (Status=%d)...\n","ReASSOC","ReASSOC",uStack_104);
    }
    __ZTE_STA_Assoc_Process
              (param_1,4,0,0,uStack_104 + 200,0,iVar25,"ap_cmm_peer_assoc_req_action",0x7bd);
    uStack_106 = *(ushort *)("pStaCfg->WpaPassPhrase" + uVar29 * 0x5834 + param_1 + 8);
    uStack_102 = ~((ushort)~(ushort)(((uint)uStack_102 << 0x12) >> 0x10) >> 2);
    if ((((*(char *)(iVar10 + 0x3e15) == '\0') || (*(char *)(iVar10 + 0x3e14) != '\0')) &&
        (*(int *)(iVar10 + 0x12e4) != 0)) && ((*(ushort *)(puStack_100 + 0x12) & 0x10) != 0)) {
      uStack_106 = uStack_106 | 0x10;
    }
    bStack_10b = *pbStack_158;
    if (bVar4) {
      bStack_10b = 4;
    }
    if ((bool)(bVar3 | bVar5)) {
      MgtMacHeaderInit(param_1,aiStack_b0,3,0,puStack_100 + 6,iVar10 + 0x1b,iVar10 + 0x21);
      uStack_104 = 1;
      MakeOutgoingFrame(iStack_fc,&iStack_f8,0x18,aiStack_b0,2,&uStack_106,2,&uStack_104,2,
                        &uStack_102,1,&SupRateIe,1,&bStack_10b,bStack_10b,pbStack_158 + 1,0xffffffff
                       );
      MiniportMMRequest(param_1,0,iStack_fc,iStack_f8);
      os_free_mem(iStack_fc);
      MacTableDeleteEntry(param_1,*(undefined2 *)(iVar25 + 0xe0),iVar25 + 0xec);
      puVar32 = puStack_100;
      if ((bVar5) &&
         (iVar25 = MacTableLookup(param_1,puStack_100 + 6), puVar32 = puStack_100, iVar25 != 0)) {
        MacTableDeleteEntry(param_1,*(undefined2 *)(iVar25 + 0xe0),iVar25 + 0xec);
        puVar32 = puStack_100;
      }
      goto LAB_0004efb4;
    }
    MgtMacHeaderInit(param_1,aiStack_b0,3,0,puStack_100 + 6,iVar10 + 0x1b,(void *)(iVar10 + 0x21));
    uVar9 = (uint)bStack_10b;
    pbVar19 = pbStack_158 + 1;
    puVar32 = &SupRateIe;
    puVar31 = &uStack_102;
    pbVar33 = &bStack_10b;
    uVar12 = 1;
    uVar13 = 1;
    uVar14 = 0xffffffff;
    MakeOutgoingFrame(iStack_fc,&iStack_f8,0x18,aiStack_b0,2,&uStack_106,2,&uStack_104,2,puVar31,1,
                      &SupRateIe,1,pbVar33,uVar9,pbVar19,0xffffffff);
    if (pbStack_158[0xd] != 0) {
      bVar4 = (bool)(bVar4 ^ 1);
      if (sVar1 == 2) {
        bVar4 = false;
      }
      if (bVar4) {
        MakeOutgoingFrame(iStack_fc + iStack_f8,&iStack_c8,1,&ExtRateIe,1,pbStack_158 + 0xd,
                          pbStack_158[0xd],pbStack_158 + 0xe,0xffffffff,puVar31,uVar12,puVar32,
                          uVar13,pbVar33,uVar9,pbVar19,uVar14);
        iStack_f8 = iStack_f8 + iStack_c8;
      }
    }
    if (*(char *)(param_1 + 0xa7cbfa) == '\x01') {
      MAP_InsertMapCapIE(param_1,iVar10,iStack_fc + iStack_f8,&iStack_f8);
      MAP_InsertMapZteIE(param_1,iVar10,iStack_fc + iStack_f8,&iStack_f8);
    }
    if (*(char *)(iVar10 + 0xb21) == '\x01') {
      RRM_InsertRRMEnCapIE
                (param_1,iVar10,iStack_fc + iStack_f8,&iStack_f8,*(undefined1 *)(iVar25 + 0xe4));
    }
    if ((*(uint *)(iVar25 + 0xb4) & 1) != 0) {
      iStack_e0 = iStack_fc + iStack_f8;
      iVar15 = build_wmm_cap_ie(param_1,&iStack_e0);
      iStack_f8 = iStack_f8 + iVar15;
    }
    if (uStack_104 == 0x1e) {
      uStack_109 = 0x38;
      uStack_108 = 5;
      uStack_107 = 3;
      iStack_c8 = 0x400;
      MakeOutgoingFrame(iStack_fc + iStack_f8,&iStack_f0,1,&uStack_109,1,&uStack_108,1,&uStack_107,4
                        ,&iStack_c8,0xffffffff);
      iStack_f8 = iStack_f8 + iStack_f0;
    }
    if ((((*(uint *)(puStack_100 + 0x240) & 1) != 0) && ((*(ushort *)(iVar10 + 0x18) & 0x18) != 0))
       && (*(char *)(iVar10 + 0x891) != '\0')) {
      auStack_d8[2] = 0;
      iStack_e0 = iStack_fc + iStack_f8;
      iVar15 = build_ht_ies(param_1,&iStack_e0);
      iStack_f8 = iVar15 + iStack_f8;
      if ((*(int *)(puStack_100 + 0x260) == 0) || (*(char *)(param_1 + 0xa39fbb) == '\x01')) {
        iStack_e0 = iStack_fc + iStack_f8;
        auStack_d8[2] = 1;
        iVar15 = build_ht_ies(param_1,&iStack_e0);
        iStack_f8 = iStack_f8 + iVar15;
      }
      if (((*(uint *)(puStack_100 + 0x240) & 4) != 0) && ((*(ushort *)(iVar10 + 0x18) & 0x20) != 0))
      {
        uStack_c4 = 1;
        iStack_c8 = iStack_fc + iStack_f8;
        uStack_c2 = *(undefined1 *)(iVar10 + 0x1a);
        uStack_c0 = *(ushort *)(iVar10 + 0x18);
        iStack_b8 = iVar10;
        uVar12 = wlan_config_get_etxbf(iVar10);
        iVar15 = HcIsBfCapSupport(iVar10);
        if (iVar15 == 0) {
          wlan_config_set_etxbf(iVar10);
        }
        txbf_bfee_cap_set(1,((uint)(byte)puStack_100[0x2a5] << 0x1c) >> 0x1f,puStack_100[0x2a6] & 7)
        ;
        iVar15 = build_vht_ies(param_1,&iStack_c8);
        iStack_f8 = iStack_f8 + iVar15;
        wlan_config_set_etxbf(iVar10,uVar12);
      }
    }
    uVar9 = *(uint *)(iVar25 + 100);
    if ((((uVar9 & 0x18) != 0) && ((*(ushort *)(iVar10 + 0x18) & 0x1c0) != 0)) &&
       (*(char *)(iVar10 + 0x891) != '\0')) {
      iVar15 = add_assoc_rsp_he_ies(iVar10,iStack_fc,iStack_f8);
      if (0 < DebugLevel) {
        printk("add he assoc_rsp, len=%d\n",iVar15);
      }
      iStack_f8 = iStack_f8 + iVar15;
      iVar15 = wlan_config_get_asic_twt_caps(iVar10);
      if ((((iVar15 == 0) || (iVar15 = wlan_config_get_he_twt_support(iVar10), iVar15 == 0)) ||
          (((puStack_100[0x19d] & 0x20) == 0 ||
           (((*(uint *)(iVar25 + 0x78) & 2) == 0 || (puStack_100[0x22e] != -0x28)))))) ||
         (puStack_100[0x22f] == '\0')) {
        uVar9 = *(uint *)(iVar25 + 100);
      }
      else {
        iVar15 = add_assoc_reassoc_rsp_twt_ie
                           (iVar10,*(undefined2 *)(iVar25 + 0xe0),iStack_fc + iStack_f8);
        if (0 < DebugLevel) {
          printk("add twt ie in assoc_rsp, len=%d\n",iVar15);
        }
        uVar9 = *(uint *)(iVar25 + 100);
        iStack_f8 = iStack_f8 + iVar15;
      }
    }
    iStack_e0 = iStack_fc + iStack_f8;
    if ((uVar9 & 0x18) == 0) {
      uVar12 = 1;
    }
    else if ((*(ushort *)(iVar10 + 0x18) & 0x1c0) == 0) {
      uVar12 = 1;
    }
    else {
      uVar12 = 0;
    }
    iVar15 = build_extended_cap_ie(param_1,&iStack_e0,uVar12);
    iStack_f8 = iStack_f8 + iVar15;
    if ((puStack_100[0x196] & 8) != 0) {
      *(undefined1 *)(iVar25 + 0x13b4) = 1;
    }
    iVar15 = HcGetBandByWdev(iVar10);
    if (*(int *)(param_1 + (iVar15 + 0xd9e3a) * 4) == 0) {
LAB_0004fe80:
      puStack_100[0x196] = puStack_100[0x196] & 0xbf;
    }
    else {
      iVar26 = uVar29 * 0x5834 + param_1;
      uVar9 = *(uint *)(
                       "Set::OID_802_11_SET_PASSPHRASE, Failed (len less than 8 or greater than 64)!!\n"
                       + iVar26 + 0x2c);
      iVar15 = HcGetBandByWdev(iVar10);
      if ((uVar9 != (byte)(&DAT_003678f2)[param_1 + iVar15]) ||
         (iVar15 = HcGetBandByWdev(iVar10),
         (*(uint *)(param_1 + (iVar15 + 0xd9e3a) * 4) &
         ~(1 << (*(uint *)(
                          "Set::OID_802_11_SET_PASSPHRASE, Failed (len less than 8 or greater than 64)!!\n"
                          + iVar26 + 0x30) & 0xff))) == 0)) goto LAB_0004fe80;
      puStack_100[0x196] = puStack_100[0x196] | 0x40;
    }
    iVar15 = build_vendor_ie(param_1,iVar10,iStack_fc + iStack_f8,4);
    iStack_f8 = iStack_f8 + iVar15;
    if (*(char *)(iVar25 + 0xd24) != '\0') {
      iStack_f0 = 0;
      uStack_107 = 0;
      iStack_c8 = 0;
      os_alloc_mem(0,&iStack_f0,0x200);
      if (iStack_f0 != 0) {
        __memzero(iStack_f0,0x200);
        WscBuildAssocRespIE(param_1,*(undefined1 *)(iVar25 + 0xe4),0,iStack_f0,&uStack_107);
        MakeOutgoingFrame(iStack_fc + iStack_f8,&iStack_c8,uStack_107,iStack_f0,0xffffffff);
        iStack_f8 = iStack_f8 + iStack_c8;
        os_free_mem(iStack_f0);
      }
    }
    MiniportMMRequest(param_1,0,iStack_fc,iStack_f8);
    os_free_mem(iStack_fc);
    if (uStack_104 == 0x1e) {
      PMF_MlmeSAQueryReq(param_1,iVar25);
    }
    if (uStack_104 != 0) {
LAB_000500d8:
      puVar32 = puStack_100;
      if (*(int *)(iVar25 + 8) != 0) {
        if (uStack_104 != 0) goto LAB_0005010c;
        if ((*(uint *)(*(int *)(iVar25 + 8) + 0x2c) & 7) == 0) {
          if (puStack_100 == (undefined1 *)0x0) {
            return;
          }
          goto LAB_0004efc8;
        }
        ZTE_Notify_Node_AD(1,iVar25);
        __ZTE_STA_Assoc_Process(param_1,0xe,0,0,0,0,iVar25,"ap_cmm_peer_assoc_req_action",0xbfe);
        puVar32 = puStack_100;
        if ((&DAT_0036b920)[param_1] != '\0') {
          BndStrg_NotifyStaConnectedMsg(param_1,iVar25);
          puVar32 = puStack_100;
        }
      }
      goto LAB_0004efb4;
    }
    if (*(int *)(iVar25 + 0xfc) == 2) {
      iVar15 = wdev_do_conn_act(*(undefined4 *)(iVar25 + 8),iVar25);
      if ((iVar15 != 1) && (-1 < DebugLevel)) {
        printk("%s():connect action fail!!\n","ap_cmm_peer_assoc_req_action");
      }
      if (uStack_104 != 0) goto LAB_000500d8;
    }
    if ((((*(uint *)(iVar25 + 0x17c) & 0x12cf8) == 0) && (*(char *)(iVar10 + 0x5c0) != '\x01')) &&
       ((*(char *)(iVar25 + 0xd24) == '\0' || ((*(uint *)(iVar10 + 0x2c) & 0x12cf8) == 0)))) {
      *(undefined1 *)(uVar27 * 0x620 + param_1 + 0x2f762) = 1;
    }
    *(undefined1 *)(iVar25 + 0xaf8) = 0;
    *(undefined1 *)((uint)*(ushort *)(iVar25 + 0xe0) * 0x620 + param_1 + 0x2f763) = 0;
    OS_CLEAR_BIT(0,iVar10 + 0x88c);
    if (*(int *)(iVar10 + 0x88c) != 0) {
      iVar26 = *(int *)(iVar10 + 0xabc);
      iVar15 = hdev_obj_state_ready(iVar26);
      if (iVar15 == 0) {
        if (-1 < DebugLevel) {
          printk("%s(): wdev=%d, hobj is not ready!\n","ap_cmm_peer_assoc_req_action",
                 *(undefined1 *)(iVar10 + 0xc));
        }
      }
      else if (*(char *)(iVar10 + 0x1a) == *(char *)(*(int *)(*(int *)(iVar26 + 8) + 4) + 4)) {
        OS_CLEAR_BIT(1,iVar10 + 0x88c);
      }
    }
    __src_00 = (void *)(iVar25 + 0xec);
    iVar15 = 6;
    do {
      IAPP_L2_Update_Frame_Send(param_1,__src_00,*(undefined1 *)(*(int *)(iVar25 + 8) + 0xc));
      iVar15 = iVar15 + -1;
    } while (iVar15 != 0);
    if (2 < DebugLevel) {
      printk("####### Send L2 Frame Mac=%02x:%02x:%02x:%02x:%02x:%02x\n",
             *(undefined1 *)(iVar25 + 0xec),*(undefined1 *)(iVar25 + 0xed),
             *(undefined1 *)(iVar25 + 0xee),*(undefined1 *)(iVar25 + 0xef),
             *(undefined1 *)(iVar25 + 0xf0),*(undefined1 *)(iVar25 + 0xf1));
    }
    *(undefined1 *)(iVar25 + 0xae6) = 1;
    *(undefined2 *)(iVar25 + 0xcc0) = 0;
    iVar15 = uVar27 * 0x620 + param_1 + 0x2f6a0;
    if (0x3f < *(byte *)(iVar25 + 0xbf)) {
      *(uint *)(iVar25 + 0xb4) = *(uint *)(iVar25 + 0xb4) | 1;
      if (((*(byte *)(iVar10 + 0x1a) < 0xf) && ((*(byte *)(iVar11 + 1) & 3) != 0)) &&
         ((puStack_100[0x274] & 2) != 0)) {
        SendBeaconRequest(param_1,*(undefined2 *)(iVar25 + 0xe0));
      }
      ba_ori_session_start(param_1,iVar15,5);
    }
    uVar9 = *(uint *)(iVar25 + 0x17c);
    if ((uVar9 & 0x2090) == 0) {
      if ((uVar9 & 0x10040) == 0) {
        if ((((uVar9 & 0x10048) != 0) ||
            ((*(char *)(iVar25 + 0x710) == '\x01' && (*(char *)(iVar25 + 0xd24) == '\0')))) &&
           (*(char *)(iVar25 + 0x17b) == '\0')) {
          *(undefined1 *)(iVar25 + 0x17b) = 2;
          RTMPSetTimer(iVar25 + 0x404,100);
        }
      }
      else {
        iVar11 = is_rsne_pmkid_cache_match
                           (puStack_100 + 0x92,puStack_100[0x191],&DAT_003687fc + param_1,
                            *(undefined1 *)(iVar25 + 0xe4),__src_00,&iStack_c8);
        if (iVar11 != 0) {
          process_pmkid(param_1,iVar10,iVar25,iStack_c8);
        }
      }
    }
    else {
      iVar11 = is_rsne_pmkid_cache_match
                         (puStack_100 + 0x92,puStack_100[0x191],&DAT_003687fc + param_1,
                          *(undefined1 *)(iVar25 + 0xe4),__src_00,&iStack_c8);
      if (iVar11 == 0) {
LAB_000503cc:
        if ((*(char *)(iVar25 + 0xd24) != '\0') || (puStack_100[0x191] == '\0')) {
          puVar32 = puStack_100;
          if (2 < DebugLevel) {
            printk("ASSOC - IF(ra%d) This is a WPS Client.\n\n",*(undefined1 *)(iVar25 + 0xe4));
            puVar32 = puStack_100;
          }
          goto LAB_0004efb4;
        }
      }
      else {
        store_pmkid_cache_in_sec_config(param_1,iVar25,iStack_c8);
        if (2 < DebugLevel) {
          printk("ASSOC - CacheIdx = %d\n",iStack_c8);
          goto LAB_000503cc;
        }
        puVar32 = puStack_100;
        if ((*(char *)(iVar25 + 0xd24) != '\0') || (puStack_100[0x191] == '\0')) goto LAB_0004efb4;
      }
      *(undefined1 *)(iVar25 + 0xd24) = 0;
      *(undefined1 *)(iVar25 + 0xd25) = 3;
      __memzero(iVar10 + 0x2f39,6);
      if (*(char *)(iVar25 + 0xd24) == '\0') {
        os_move_mem((void *)(iVar25 + 0x4a0),(void *)(iVar10 + 0x21),6);
        os_move_mem((void *)(iVar25 + 0x4a6),__src_00,6);
        if ((*(uint *)(iVar25 + 0x17c) & 0x2000) == 0) {
          os_move_mem((void *)(iVar25 + 0x30a),(void *)(iVar10 + 0x1ba),0x20);
        }
        RTMPSetTimer(iVar25 + 0x404,100);
      }
    }
    if ((iVar15 != 0) && (*(char *)(uVar27 * 0x620 + param_1 + 0x2f762) == '\x01')) {
      MWDSAPPeerEnable(param_1,iVar25);
    }
    if (uStack_104 == 0) {
      if (*(int *)(iVar25 + 0xfc) == 2) {
        greenap_check_peer_connection_at_link_up_down(param_1,iVar10);
      }
      goto LAB_000500d8;
    }
LAB_0005010c:
    puVar32 = puStack_100;
    if (puStack_100 == (undefined1 *)0x0) {
      return;
    }
  }
  __ZTE_STA_Assoc_Process
            (param_1,0x13,puVar32 + 6,0,uStack_104 + 200,0,iVar25,"ap_cmm_peer_assoc_req_action",
             0xc2e);
  puVar32 = puStack_100;
LAB_0004efc8:
  os_free_mem(puVar32);
  return;
}

