// module: mt7915.ko
// function: Show_MbssInfo_Display_Proc @ 0x33408
// size: 1252 bytes
//

undefined4 Show_MbssInfo_Display_Proc(int param_1,int param_2)

{
  char cVar1;
  int iVar2;
  undefined4 uVar3;
  undefined4 uVar4;
  undefined4 uVar5;
  char *pcVar6;
  char *pcVar7;
  char *pcVar8;
  undefined *puVar9;
  undefined4 *puVar10;
  char *pcVar11;
  char *pcVar12;
  int *piVar13;
  uint uVar14;
  int iVar15;
  uint uVar16;
  uint uVar17;
  uint uVar18;
  uint uVar19;
  uint uVar20;
  uint uVar21;
  bool bVar22;
  
  if (param_2 == 0) {
    cVar1 = '\0';
  }
  else {
    cVar1 = os_str_tol(param_2,0,10);
  }
  if (0 < DebugLevel) {
    printk("\n\tBssidNum=%d\n",
           "======== Badnode detector =============\nvow_bn_en = <0/1> 0:dieable, 1:enable\nvow_bn_mon_period = <period> ms\nvow_bn_fallback_th = <count>\nvow_bn_per_th = <TX PER>\n======== Airtime counter test =============\nvow_counter_test = <0/1> 0:dieable, 1:enable\nvow_counter_test_period = <period> ms\nvow_counter_test_band = <band>\nvow_counter_test_avgcnt = <average num> sec\nvow_counter_test_target = <wlanidx>\n======== DVT =============\nvow_dvt_en = <0/1> 0:dieable, 1:enable\nvow_monitor_sta = <STA num>\nvow_show_sta = <STA num>\nvow_monitor_bss = <BSS num>\nvow_monitor_mbss = <MBSS num>\nvow_show_mbss = <MBSS num>\nvow_avg_num = <average num> sec\n======== RED ===========\nvow_set_red_en = <0/1> 0:disable, 1:enable\nvow_set_red_show_sta = <STA num>\nvow_set_red_tar_delay = <tarDelay> us\n======== WATF ===========\nvow_watf_en = <0/1> 0:disable, 1:enable\nvow_watf_q = <level>-<quantum> unit 256us\nvow_watf_add_entry = <level>-<Addr>\nvow_watf_del_entry = <Addr>\n"
           [param_1 + 0xda]);
  }
  piVar13 = (int *)(param_1 + 0x3678e4);
  pcVar11 = "======== Badnode detector =============\nvow_bn_en = <0/1> 0:dieable, 1:enable\nvow_bn_mon_period = <period> ms\nvow_bn_fallback_th = <count>\nvow_bn_per_th = <TX PER>\n======== Airtime counter test =============\nvow_counter_test = <0/1> 0:dieable, 1:enable\nvow_counter_test_period = <period> ms\nvow_counter_test_band = <band>\nvow_counter_test_avgcnt = <average num> sec\nvow_counter_test_target = <wlanidx>\n======== DVT =============\nvow_dvt_en = <0/1> 0:dieable, 1:enable\nvow_monitor_sta = <STA num>\nvow_show_sta = <STA num>\nvow_monitor_bss = <BSS num>\nvow_monitor_mbss = <MBSS num>\nvow_show_mbss = <MBSS num>\nvow_avg_num = <average num> sec\n======== RED ===========\nvow_set_red_en = <0/1> 0:disable, 1:enable\nvow_set_red_show_sta = <STA num>\nvow_set_red_tar_delay = <tarDelay> us\n======== WATF ===========\nvow_watf_en = <0/1> 0:disable, 1:enable\nvow_watf_q = <level>-<quantum> unit 256us\nvow_watf_add_entry = <level>-<Addr>\nvow_watf_del_entry = <Addr>\n"
            + param_1 + 0xdb;
  puVar9 = &DAT_003678f0 + param_1;
  iVar15 = 0;
  iVar2 = DebugLevel;
  do {
    piVar13 = piVar13 + 1;
    if (*piVar13 == 0) {
      if (0 < iVar2) {
        printk("\t[B%d]: BssidNum=%2d\n",iVar15,*pcVar11);
        iVar2 = DebugLevel;
      }
    }
    else if (0 < iVar2) {
      printk("\t[B%d]: BssidNum=%2d, max_bssid_indicator=%d, bitmap=0x%08x, trans_bss_idx=%d\n",
             iVar15,*pcVar11,*puVar9,*piVar13,puVar9[2]);
      iVar2 = DebugLevel;
    }
    bVar22 = iVar15 != 1;
    iVar15 = 1;
    pcVar11 = pcVar11 + 1;
    puVar9 = puVar9 + 1;
  } while (bVar22);
  if (0 < iVar2) {
    printk("\n\tBSS Idx\t\tPhy Mode\tIF_addr\t\t\tgrp [max:%d]\n",
           *(undefined2 *)(param_1 + 0xa7bec8));
  }
  if ("======== Badnode detector =============\nvow_bn_en = <0/1> 0:dieable, 1:enable\nvow_bn_mon_period = <period> ms\nvow_bn_fallback_th = <count>\nvow_bn_per_th = <TX PER>\n======== Airtime counter test =============\nvow_counter_test = <0/1> 0:dieable, 1:enable\nvow_counter_test_period = <period> ms\nvow_counter_test_band = <band>\nvow_counter_test_avgcnt = <average num> sec\nvow_counter_test_target = <wlanidx>\n======== DVT =============\nvow_dvt_en = <0/1> 0:dieable, 1:enable\nvow_monitor_sta = <STA num>\nvow_show_sta = <STA num>\nvow_monitor_bss = <BSS num>\nvow_monitor_mbss = <MBSS num>\nvow_show_mbss = <MBSS num>\nvow_avg_num = <average num> sec\n======== RED ===========\nvow_set_red_en = <0/1> 0:disable, 1:enable\nvow_set_red_show_sta = <STA num>\nvow_set_red_tar_delay = <tarDelay> us\n======== WATF ===========\nvow_watf_en = <0/1> 0:disable, 1:enable\nvow_watf_q = <level>-<quantum> unit 256us\nvow_watf_add_entry = <level>-<Addr>\nvow_watf_del_entry = <Addr>\n"
      [param_1 + 0xda] != '\0') {
    pcVar11 = "======== Badnode detector =============\nvow_bn_en = <0/1> 0:dieable, 1:enable\nvow_bn_mon_period = <period> ms\nvow_bn_fallback_th = <count>\nvow_bn_per_th = <TX PER>\n======== Airtime counter test =============\nvow_counter_test = <0/1> 0:dieable, 1:enable\nvow_counter_test_period = <period> ms\nvow_counter_test_band = <band>\nvow_counter_test_avgcnt = <average num> sec\nvow_counter_test_target = <wlanidx>\n======== DVT =============\nvow_dvt_en = <0/1> 0:dieable, 1:enable\nvow_monitor_sta = <STA num>\nvow_show_sta = <STA num>\nvow_monitor_bss = <BSS num>\nvow_monitor_mbss = <MBSS num>\nvow_show_mbss = <MBSS num>\nvow_avg_num = <average num> sec\n======== RED ===========\nvow_set_red_en = <0/1> 0:disable, 1:enable\nvow_set_red_show_sta = <STA num>\nvow_set_red_tar_delay = <tarDelay> us\n======== WATF ===========\nvow_watf_en = <0/1> 0:disable, 1:enable\nvow_watf_q = <level>-<quantum> unit 256us\nvow_watf_add_entry = <level>-<Addr>\nvow_watf_del_entry = <Addr>\n"
              + param_1 + 0xe0;
    puVar9 = &DAT_003678c8 + param_1;
    pcVar12 = "Set::OID_802_11_SET_PASSPHRASE, Failed (len less than 8 or greater than 64)!!\n" +
              param_1 + 0x34;
    uVar14 = 0;
    do {
      iVar2 = wmode_2_str(*(undefined2 *)(pcVar11 + 0x18));
      iVar15 = HcGetBandByWdev(pcVar11);
      if (0 < DebugLevel) {
        uVar17 = (uint)(byte)pcVar11[0x1c];
        uVar18 = (uint)(byte)pcVar11[0x1d];
        uVar19 = (uint)(byte)pcVar11[0x1e];
        uVar20 = (uint)(byte)pcVar11[0x1f];
        uVar21 = (uint)(byte)pcVar11[0x20];
        uVar3 = *(undefined4 *)(pcVar12 + -4);
        uVar4 = *(undefined4 *)pcVar11;
        printk("\t%d\t%16s\t%02x:%02x:%02x:%02x:%02x:%02x\t%d\t(%s)",uVar14,iVar2,pcVar11[0x1b],
               uVar17,uVar18,uVar19,uVar20,uVar21,uVar3,uVar4);
        uVar16 = *(uint *)(param_1 + (iVar15 + 0xd9e3a) * 4);
        if (uVar16 == 0) {
          if (0 < DebugLevel) {
            printk("\t(Legacy)");
LAB_000336b8:
            if (0 < DebugLevel) {
              printk(&_LC220);
            }
          }
        }
        else if (0 < DebugLevel) {
          pcVar7 = *(char **)(pcVar12 + -8);
          pcVar8 = (char *)(uint)(byte)(&DAT_003678f2)[param_1 + iVar15];
          if (pcVar7 == pcVar8) {
            pcVar6 = "11vT";
          }
          else {
            pcVar7 = (char *)0x1;
            pcVar8 = "11vNT";
            pcVar6 = "11vCoH";
            if ((uVar16 & 1 << (*(uint *)(pcVar12 + -4) & 0xff)) != 0) {
              pcVar6 = pcVar8;
            }
          }
          printk("\t(%s)",pcVar6,pcVar7,pcVar8,uVar17,uVar18,uVar19,uVar20,uVar21,uVar3,uVar4);
          goto LAB_000336b8;
        }
      }
      if (((cVar1 != '\0') && (0 < DebugLevel)) &&
         (printk("\t\t\t - SSID: %s (H=%d), pfIdx: %2d\n",pcVar12,pcVar12[0x22],*puVar9),
         0 < DebugLevel)) {
        uVar16 = (uint)(byte)pcVar12[0x27];
        printk("\t\t\t - Band:%d (OM:0x%02x), Ch:%3d, Dtim:%2d, StaCount:%3d\n",iVar15,pcVar11[0x29]
               ,pcVar11[0x1a],pcVar12[0x23],uVar16);
        if (0 < DebugLevel) {
          uVar3 = GetAuthModeStr(*(undefined4 *)(pcVar11 + 0x2c));
          uVar4 = GetEncryModeStr(*(undefined4 *)(pcVar11 + 0x174));
          uVar5 = GetEncryModeStr(*(undefined4 *)(pcVar11 + 0x254));
          printk("\t\t\t - AuthMode: %s, Cipher(P:%s/G:%s), BmcIdx=0x%x\n",uVar3,uVar4,uVar5,
                 *(undefined2 *)(pcVar11 + 0x9a0),uVar16);
        }
      }
      if (iVar2 != 0) {
        os_free_mem(iVar2);
      }
      uVar14 = uVar14 + 1;
      pcVar11 = pcVar11 + 0x5834;
      pcVar12 = pcVar12 + 0x5834;
      puVar9 = puVar9 + 1;
    } while (uVar14 < (byte)"======== Badnode detector =============\nvow_bn_en = <0/1> 0:dieable, 1:enable\nvow_bn_mon_period = <period> ms\nvow_bn_fallback_th = <count>\nvow_bn_per_th = <TX PER>\n======== Airtime counter test =============\nvow_counter_test = <0/1> 0:dieable, 1:enable\nvow_counter_test_period = <period> ms\nvow_counter_test_band = <band>\nvow_counter_test_avgcnt = <average num> sec\nvow_counter_test_target = <wlanidx>\n======== DVT =============\nvow_dvt_en = <0/1> 0:dieable, 1:enable\nvow_monitor_sta = <STA num>\nvow_show_sta = <STA num>\nvow_monitor_bss = <BSS num>\nvow_monitor_mbss = <MBSS num>\nvow_show_mbss = <MBSS num>\nvow_avg_num = <average num> sec\n======== RED ===========\nvow_set_red_en = <0/1> 0:disable, 1:enable\nvow_set_red_show_sta = <STA num>\nvow_set_red_tar_delay = <tarDelay> us\n======== WATF ===========\nvow_watf_en = <0/1> 0:disable, 1:enable\nvow_watf_q = <level>-<quantum> unit 256us\nvow_watf_add_entry = <level>-<Addr>\nvow_watf_del_entry = <Addr>\n"
                            [param_1 + 0xda]);
  }
  if ((0 < DebugLevel) &&
     (printk("\n\tStaNum=%d\n",*(undefined1 *)(param_1 + 0x794ab8)), 0 < DebugLevel)) {
    printk("\n\tSTA Idx\t\tPhy Mode\tIF_addr\t\t\tBand\n");
  }
  if (*(char *)(param_1 + 0x794ab8) != '\0') {
    iVar2 = 0;
    puVar10 = (undefined4 *)(&DAT_0036db58 + param_1);
    do {
      iVar15 = wmode_2_str(*(undefined2 *)(puVar10 + 6));
      uVar3 = HcGetBandByWdev(puVar10);
      if (0 < DebugLevel) {
        printk("\t%d\t%16s\t%02x:%02x:%02x:%02x:%02x:%02x\t%d\t(%s)\n",iVar2,iVar15,
               *(undefined *)((int)puVar10 + 0x1b),*(undefined1 *)(puVar10 + 7),
               *(undefined *)((int)puVar10 + 0x1d),*(undefined *)((int)puVar10 + 0x1e),
               *(undefined *)((int)puVar10 + 0x1f),*(undefined1 *)(puVar10 + 8),uVar3,*puVar10);
      }
      iVar2 = iVar2 + 1;
      if (iVar15 != 0) {
        os_free_mem(iVar15);
      }
      puVar10 = puVar10 + 0x84dec;
    } while (iVar2 < (int)(uint)*(byte *)(param_1 + 0x794ab8));
  }
  return 1;
}

