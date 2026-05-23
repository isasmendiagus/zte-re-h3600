// module: mt7915.ko
// function: RRM_EnqueueNeighborRep @ 0x21de40
// size: 1224 bytes
//

void RRM_EnqueueNeighborRep(int param_1,int param_2,undefined4 param_3)

{
  int iVar1;
  int *piVar2;
  int iVar3;
  uint uVar4;
  uint uVar5;
  char *pcVar6;
  uint uVar7;
  ushort uVar8;
  int iVar9;
  ushort uVar10;
  byte bVar11;
  ushort uVar12;
  void *__s1;
  int iVar13;
  uint uVar14;
  undefined1 local_68;
  void *local_60;
  int local_5c;
  undefined4 local_57;
  undefined4 local_53;
  undefined2 local_4f;
  undefined4 local_4d;
  undefined2 local_49;
  uint local_47;
  undefined1 local_43;
  byte local_42;
  undefined1 local_41;
  undefined1 auStack_40 [28];
  
  local_60 = (void *)0x0;
  if (((param_2 == 0) || (iVar9 = *(int *)(param_2 + 8), iVar9 == 0)) ||
     ((byte)"======== Badnode detector =============\nvow_bn_en = <0/1> 0:dieable, 1:enable\nvow_bn_mon_period = <period> ms\nvow_bn_fallback_th = <count>\nvow_bn_per_th = <TX PER>\n======== Airtime counter test =============\nvow_counter_test = <0/1> 0:dieable, 1:enable\nvow_counter_test_period = <period> ms\nvow_counter_test_band = <band>\nvow_counter_test_avgcnt = <average num> sec\nvow_counter_test_target = <wlanidx>\n======== DVT =============\nvow_dvt_en = <0/1> 0:dieable, 1:enable\nvow_monitor_sta = <STA num>\nvow_show_sta = <STA num>\nvow_monitor_bss = <BSS num>\nvow_monitor_mbss = <MBSS num>\nvow_show_mbss = <MBSS num>\nvow_avg_num = <average num> sec\n======== RED ===========\nvow_set_red_en = <0/1> 0:disable, 1:enable\nvow_set_red_show_sta = <STA num>\nvow_set_red_tar_delay = <tarDelay> us\n======== WATF ===========\nvow_watf_en = <0/1> 0:disable, 1:enable\nvow_watf_q = <level>-<quantum> unit 256us\nvow_watf_add_entry = <level>-<Addr>\nvow_watf_del_entry = <Addr>\n"
            [param_1 + 0xda] <= *(byte *)(param_2 + 0xe4))) {
    if (-1 < DebugLevel) {
      printk("%s: Invalid STA.\n","RRM_EnqueueNeighborRep");
    }
  }
  else {
    iVar1 = os_alloc_mem(param_1,&local_60,0x900);
    if ((iVar1 == 0) && (local_60 != (void *)0x0)) {
      iVar1 = param_1 + (uint)*(byte *)(param_2 + 0xe4) * 0x5834;
      MgtMacHeaderInit(param_1,auStack_40,0xd,0,param_2 + 0xec,
                       "======== Badnode detector =============\nvow_bn_en = <0/1> 0:dieable, 1:enable\nvow_bn_mon_period = <period> ms\nvow_bn_fallback_th = <count>\nvow_bn_per_th = <TX PER>\n======== Airtime counter test =============\nvow_counter_test = <0/1> 0:dieable, 1:enable\nvow_counter_test_period = <period> ms\nvow_counter_test_band = <band>\nvow_counter_test_avgcnt = <average num> sec\nvow_counter_test_target = <wlanidx>\n======== DVT =============\nvow_dvt_en = <0/1> 0:dieable, 1:enable\nvow_monitor_sta = <STA num>\nvow_show_sta = <STA num>\nvow_monitor_bss = <BSS num>\nvow_monitor_mbss = <MBSS num>\nvow_show_mbss = <MBSS num>\nvow_avg_num = <average num> sec\n======== RED ===========\nvow_set_red_en = <0/1> 0:disable, 1:enable\nvow_set_red_show_sta = <STA num>\nvow_set_red_tar_delay = <tarDelay> us\n======== WATF ===========\nvow_watf_en = <0/1> 0:disable, 1:enable\nvow_watf_q = <level>-<quantum> unit 256us\nvow_watf_add_entry = <level>-<Addr>\nvow_watf_del_entry = <Addr>\n"
                       + iVar1 + 0xfb,
                       "======== Badnode detector =============\nvow_bn_en = <0/1> 0:dieable, 1:enable\nvow_bn_mon_period = <period> ms\nvow_bn_fallback_th = <count>\nvow_bn_per_th = <TX PER>\n======== Airtime counter test =============\nvow_counter_test = <0/1> 0:dieable, 1:enable\nvow_counter_test_period = <period> ms\nvow_counter_test_band = <band>\nvow_counter_test_avgcnt = <average num> sec\nvow_counter_test_target = <wlanidx>\n======== DVT =============\nvow_dvt_en = <0/1> 0:dieable, 1:enable\nvow_monitor_sta = <STA num>\nvow_show_sta = <STA num>\nvow_monitor_bss = <BSS num>\nvow_monitor_mbss = <MBSS num>\nvow_show_mbss = <MBSS num>\nvow_avg_num = <average num> sec\n======== RED ===========\nvow_set_red_en = <0/1> 0:disable, 1:enable\nvow_set_red_show_sta = <STA num>\nvow_set_red_tar_delay = <tarDelay> us\n======== WATF ===========\nvow_watf_en = <0/1> 0:disable, 1:enable\nvow_watf_q = <level>-<quantum> unit 256us\nvow_watf_add_entry = <level>-<Addr>\nvow_watf_del_entry = <Addr>\n"
                       + iVar1 + 0x101);
      memmove(local_60,auStack_40,0x18);
      local_5c = 0x18;
      InsertActField(param_1,(int)local_60 + 0x18,&local_5c,5,5);
      InsertDialogToken(param_1,(int)local_60 + local_5c,&local_5c,param_3);
      uVar5 = (uint)*(byte *)(param_2 + 0xe5);
      if (*(int *)(
                  "Query::RT_OID_802_11_QUERY_APSD_SETTING (=0x%lx,APSDCap=%d,AC_BE=%d,AC_BK=%d,AC_VI=%d,AC_VO=%d,MAXSPLen=%d)\n"
                  + uVar5 * 0x5834 + param_1 + 0x60) != 0) {
        uVar14 = 0;
        do {
          if ("%u-%02x:%02x:%02x:%02x:%02x:%02x"
              [(uint)*(byte *)(param_2 + 0xe4) * 0x5834 + param_1 + 0x12] == '\x01') {
            iVar1 = 6;
          }
          else {
            iVar1 = 0;
          }
          if (0x8ff < (uint)(local_5c + 0xd + iVar1)) break;
          iVar1 = param_1 + uVar5 * 0x5834 + uVar14 * 0x2d;
          bVar11 = "Query::RT_OID_802_11_QUERY_APSD_SETTING (=0x%lx,APSDCap=%d,AC_BE=%d,AC_BK=%d,AC_VI=%d,AC_VO=%d,MAXSPLen=%d)\n"
                   [iVar1 + 0x6b];
          pcVar6 = "Query::RT_OID_802_11_QUERY_APSD_SETTING (=0x%lx,APSDCap=%d,AC_BE=%d,AC_BK=%d,AC_VI=%d,AC_VO=%d,MAXSPLen=%d)\n"
                   + iVar1 + 100;
          local_53 = *(undefined4 *)pcVar6;
          local_4f = *(undefined2 *)
                      (
                      "Query::RT_OID_802_11_QUERY_APSD_SETTING (=0x%lx,APSDCap=%d,AC_BE=%d,AC_BK=%d,AC_VI=%d,AC_VO=%d,MAXSPLen=%d)\n"
                      + iVar1 + 0x68);
          if (0xe < bVar11) {
            pcVar6 = &DAT_00000009;
          }
          local_68 = SUB41(pcVar6,0);
          if (bVar11 < 0xf) {
            local_68 = 7;
          }
          local_57._0_2_ =
               CONCAT11(("Query::RT_OID_802_11_QUERY_APSD_SETTING (=0x%lx,APSDCap=%d,AC_BE=%d,AC_BK=%d,AC_VI=%d,AC_VO=%d,MAXSPLen=%d)\n"
                         [iVar1 + 0x6c] & 1U) << 3 |
                        ("Query::RT_OID_802_11_QUERY_APSD_SETTING (=0x%lx,APSDCap=%d,AC_BE=%d,AC_BK=%d,AC_VI=%d,AC_VO=%d,MAXSPLen=%d)\n"
                         [iVar1 + 0x6d] & 1U) << 4,5);
          local_57 = (uint)(ushort)local_57;
          piVar2 = (int *)get_scan_tab_by_wdev(param_1,iVar9);
          iVar1 = *piVar2;
          if (iVar1 == 0) {
            uVar8 = 0;
            uVar10 = 0;
            uVar12 = 0;
            uVar4 = 0;
            uVar7 = 0;
          }
          else {
            __s1 = (void *)((int)piVar2 + 0xe);
            iVar13 = 0;
            do {
              iVar3 = memcmp(__s1,&local_53,6);
              __s1 = (void *)((int)__s1 + 0xaf4);
              if (iVar3 == 0) {
                uVar12 = *(ushort *)((int)piVar2 + iVar13 * 0xaf4 + 0x92);
                uVar5 = (uint)uVar12;
                bVar11 = *(byte *)(piVar2 + iVar13 * 0x2bd + 5);
                if (bVar11 < 0xf) {
                  local_68 = 7;
                }
                else {
                  local_68 = 9;
                }
                local_57._0_2_ =
                     CONCAT11(local_57._1_1_ & 0xfc | (byte)((uVar5 << 0x11) >> 0x1f) |
                              (byte)(uVar12 >> 0xf) << 1,
                              (byte)local_57 & 0xf | (byte)(((uVar5 << 0x17) >> 0x1f) << 4) |
                              (byte)(((uVar5 << 0x16) >> 0x1f) << 5) |
                              (byte)(((uVar5 << 0x14) >> 0x1f) << 6) |
                              (byte)(((uVar5 << 0x13) >> 0x1f) << 7));
                uVar8 = (ushort)*(byte *)((int)piVar2 + iVar13 * 0xaf4 + 0x6c7);
                if ("%u-%02x:%02x:%02x:%02x:%02x:%02x"
                    [(uint)*(byte *)(param_2 + 0xe5) * 0x5834 + param_1 + 0x12] == '\0') {
                  uVar12 = 0;
                  uVar4 = 0;
                  uVar7 = 0;
                  uVar10 = 1;
                }
                else {
                  uVar12 = *(ushort *)(piVar2 + iVar13 * 0x2bd + 8);
                  uVar4 = (uint)*(byte *)(piVar2 + iVar13 * 0x2bd + 0x141) * 0x10000 +
                          (uint)*(byte *)((int)piVar2 + iVar13 * 0xaf4 + 0x505) * 0x1000000 +
                          (uint)*(byte *)((int)piVar2 + iVar13 * 0xaf4 + 0x502) +
                          (uint)*(byte *)((int)piVar2 + iVar13 * 0xaf4 + 0x503) * 0x100;
                  uVar7 = (uint)*(byte *)(piVar2 + iVar13 * 0x2bd + 0x140) * 0x10000 +
                          (uint)*(byte *)((int)piVar2 + iVar13 * 0xaf4 + 0x501) * 0x1000000 +
                          (uint)*(byte *)((int)piVar2 + iVar13 * 0xaf4 + 0x4fe) +
                          (uint)*(byte *)((int)piVar2 + iVar13 * 0xaf4 + 0x4ff) * 0x100;
                  uVar10 = 1;
                }
                goto LAB_0021e178;
              }
              iVar13 = iVar13 + 1;
            } while (iVar13 != iVar1);
            uVar12 = 0;
            uVar7 = 0;
            uVar4 = 0;
            uVar10 = uVar12;
            uVar8 = uVar12;
          }
LAB_0021e178:
          local_43 = (undefined1)uVar8;
          local_4d = local_53;
          local_49 = local_4f;
          local_41 = local_68;
          local_47 = local_57;
          local_42 = bVar11;
          RRM_InsertNeighborRepIE(param_1,(int)local_60 + local_5c,&local_5c,0xd,&local_4d);
          uVar5 = (uint)*(byte *)(param_2 + 0xe5);
          if ("%u-%02x:%02x:%02x:%02x:%02x:%02x"[uVar5 * 0x5834 + param_1 + 0x12] == '\0') {
            uVar10 = 0;
          }
          if (uVar10 != 0) {
            uVar5 = uVar7;
            if (uVar4 <= uVar7) {
              uVar5 = uVar4;
            }
            if (uVar4 <= uVar7) {
              uVar4 = uVar7;
            }
            RRM_InsertNeighborTSFOffsetSubIE
                      (param_1,(int)local_60 + local_5c,&local_5c,uVar4 - uVar5 & 0xffff,uVar12);
            uVar5 = (uint)*(byte *)(param_2 + 0xe5);
          }
          uVar14 = uVar14 + 1;
        } while (uVar14 < *(uint *)(
                                   "Query::RT_OID_802_11_QUERY_APSD_SETTING (=0x%lx,APSDCap=%d,AC_BE=%d,AC_BK=%d,AC_VI=%d,AC_VO=%d,MAXSPLen=%d)\n"
                                   + uVar5 * 0x5834 + param_1 + 0x60));
      }
      if (-1 < DebugLevel) {
        printk("%s() : send Neighbor RSP\n","RRM_EnqueueNeighborRep");
      }
      MiniportMMRequest(param_1,0x81,local_60,local_5c);
      if (local_60 != (void *)0x0) {
        os_free_mem();
      }
    }
    else if (2 < DebugLevel) {
      printk("%s() allocate memory failed\n","RRM_EnqueueNeighborRep");
    }
  }
  return;
}

