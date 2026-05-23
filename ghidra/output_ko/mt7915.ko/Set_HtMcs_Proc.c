// module: mt7915.ko
// function: Set_HtMcs_Proc @ 0xdfff4
// size: 1236 bytes
//

undefined4 Set_HtMcs_Proc(int *param_1,char *param_2)

{
  byte bVar1;
  int iVar2;
  char *pcVar3;
  undefined1 *puVar4;
  int iVar5;
  uint uVar6;
  uint uVar7;
  char *pcVar8;
  char cVar9;
  uint uVar10;
  int iVar11;
  uint uVar12;
  int iVar13;
  bool bVar14;
  bool bVar15;
  
  iVar11 = *param_1;
  pcVar3 = (char *)get_wdev_by_ioctl_idx_and_iftype
                             (param_1,*(undefined4 *)(iVar11 + 0x3c),*(undefined4 *)(iVar11 + 0x38))
  ;
  if (pcVar3 == (char *)0x0) {
    return 0;
  }
  puVar4 = (undefined1 *)rtstrchr(param_2,0x3a);
  if (puVar4 == (undefined1 *)0x0) {
    uVar12 = os_str_tol(param_2,0,10);
    uVar12 = uVar12 & 0xff;
    bVar14 = 0x1f < uVar12;
    if (uVar12 != 0x20) {
      bVar14 = 0xe < uVar12;
    }
    if (bVar14 && (uVar12 != 0x20 && uVar12 != 0xf)) {
      uVar12 = 0x21;
    }
  }
  else {
    *puVar4 = 0;
    if (2 < DebugLevel) {
      printk("%s(): ss_str=%s, mcs_str=%s\n","Set_HtMcs_Proc",param_2,puVar4 + 1);
    }
    if ((*param_2 == '\0') || (puVar4[1] == '\0')) {
      uVar12 = 0x21;
    }
    else {
      uVar12 = os_str_tol(puVar4 + 1,0,10);
      uVar6 = os_str_tol(param_2,0,10);
      uVar6 = uVar6 & 0xff;
      uVar7 = wlan_operate_get_tx_stream(pcVar3);
      uVar10 = uVar12 & 0xff;
      bVar15 = uVar7 <= uVar6;
      bVar14 = uVar6 == uVar7;
      if (!bVar15 || bVar14) {
        bVar15 = 6 < uVar10;
        bVar14 = uVar10 == 7;
      }
      if (!bVar15 || bVar14) {
        uVar12 = (uVar12 | (uVar6 - 1) * 0x10) & 0xff;
        if (2 < DebugLevel) {
          if (uVar12 == 0x21 && uVar6 == 0) goto LAB_000e048c;
          pcVar8 = "FALSE";
          goto LAB_000e0498;
        }
      }
      else {
        uVar6 = 0;
        if (DebugLevel < 3) {
          uVar12 = 0x21;
        }
        else {
LAB_000e048c:
          uVar12 = 0x21;
          pcVar8 = "TRUE";
LAB_000e0498:
          printk("%s(): %dSS-MCS%d, Auto=%s\n","Set_HtMcs_Proc",uVar6,uVar10,pcVar8);
        }
      }
      Set_FixedTxMode_Proc(param_1,&_LC438);
    }
  }
  iVar2 = DebugLevel;
  cVar9 = *(char *)((int)param_1 + 0x286285);
  if (cVar9 == '\x01') {
    iVar5 = *(int *)(iVar11 + 0x3c) * 0x5834;
    pcVar3 = (char *)((int)param_1 +
                     (int)(
                          "======== Badnode detector =============\nvow_bn_en = <0/1> 0:dieable, 1:enable\nvow_bn_mon_period = <period> ms\nvow_bn_fallback_th = <count>\nvow_bn_per_th = <TX PER>\n======== Airtime counter test =============\nvow_counter_test = <0/1> 0:dieable, 1:enable\nvow_counter_test_period = <period> ms\nvow_counter_test_band = <band>\nvow_counter_test_avgcnt = <average num> sec\nvow_counter_test_target = <wlanidx>\n======== DVT =============\nvow_dvt_en = <0/1> 0:dieable, 1:enable\nvow_monitor_sta = <STA num>\nvow_show_sta = <STA num>\nvow_monitor_bss = <BSS num>\nvow_monitor_mbss = <MBSS num>\nvow_show_mbss = <MBSS num>\nvow_avg_num = <average num> sec\n======== RED ===========\nvow_set_red_en = <0/1> 0:disable, 1:enable\nvow_set_red_show_sta = <STA num>\nvow_set_red_tar_delay = <tarDelay> us\n======== WATF ===========\nvow_watf_en = <0/1> 0:disable, 1:enable\nvow_watf_q = <level>-<quantum> unit 256us\nvow_watf_add_entry = <level>-<Addr>\nvow_watf_del_entry = <Addr>\n"
                          + iVar5 + 0xe0));
    *(byte *)((int)param_1 + iVar5 + 0x2b7af6) =
         *(byte *)((int)param_1 + iVar5 + 0x2b7af6) & 0x80 | (byte)(uVar12 & 0x7f);
    if (iVar2 < 3) goto LAB_000e0148;
    printk("Set_HtMcs_Proc::(HtMcs=%d) for ra%d\n",uVar12 & 0x7f,*(undefined4 *)(iVar11 + 0x3c));
    cVar9 = *(char *)((int)param_1 + 0x286285);
  }
  if (cVar9 != '\0') goto LAB_000e0148;
  iVar13 = *(int *)(iVar11 + 0x3c);
  iVar11 = iVar13 * 0x2137b0;
  pcVar3 = (char *)((int)param_1 + (int)(&DAT_0036db58 + iVar11));
  iVar5 = GetAssociatedAPByWdev(param_1,pcVar3);
  iVar2 = DebugLevel;
  if (iVar5 == 0) {
    printk(&_LC440,0x15f0);
    dump_stack();
    iVar2 = DebugLevel;
    *(byte *)((int)param_1 + iVar11 + 0x36e406) =
         *(byte *)((int)param_1 + iVar11 + 0x36e406) & 0x80 | (byte)uVar12 & 0x7f;
    *(bool *)(param_1 + iVar13 * 0x84dec + 0xdb902) = uVar12 == 0x21;
    if (2 < iVar2) {
      printk("Set_HtMcs_Proc::(HtMcs=%d, bAutoTxRateSwitch = %d)\n",
             *(byte *)((int)param_1 + iVar13 * 0x2137b0 + 0x36e406) & 0x7f);
    }
  }
  else {
    *(byte *)((int)param_1 + iVar11 + 0x36e406) =
         *(byte *)((int)param_1 + iVar11 + 0x36e406) & 0x80 | (byte)uVar12 & 0x7f;
    *(bool *)(param_1 + iVar13 * 0x84dec + 0xdb902) = uVar12 == 0x21;
    if (2 < iVar2) {
      printk("Set_HtMcs_Proc::(HtMcs=%d, bAutoTxRateSwitch = %d)\n",
             *(byte *)((int)param_1 + iVar13 * 0x2137b0 + 0x36e406) & 0x7f);
    }
    if (((*(ushort *)(param_1 + iVar13 * 0x84dec + 0xdb6dc) & 0x18) == 0) ||
       (*(byte *)(iVar5 + 0xbd) < 0x40)) {
      if ((*(byte *)((int)param_1 + iVar13 * 0x2137b0 + 0x36e406) & 0x7f) == 0x21) {
LAB_000e0250:
        *(byte *)((int)param_1 + iVar13 * 0x2137b0 + 0x36e406) =
             *(byte *)((int)param_1 + iVar13 * 0x2137b0 + 0x36e406) & 0x80 | 0x21;
        RTMPSetDesiredRates(param_1,pcVar3,0xffffffff);
      }
      else {
        if (3 < uVar12) {
          if (uVar12 < 8) goto LAB_000e0224;
          goto LAB_000e0250;
        }
        if ((*(byte *)((int)param_1 + iVar13 * 0x2137b0 + 0x36e407) & 0x38) == 8) {
          bVar1 = RateIdToMbps[uVar12];
        }
        else {
LAB_000e0224:
          if ((*(byte *)((int)param_1 + iVar13 * 0x2137b0 + 0x36e407) & 0x38) != 0x10)
          goto LAB_000e0250;
          bVar1 = RateIdToMbps[uVar12 + 4];
        }
        RTMPSetDesiredRates(param_1,pcVar3,(uint)bVar1 * 1000000);
      }
      if (2 < DebugLevel) {
        printk("Set_HtMcs_Proc::(FixedTxMode=%d)\n",
               ((uint)*(byte *)((int)param_1 + iVar13 * 0x2137b0 + 0x36e407) << 0x1a) >> 0x1d);
      }
    }
  }
  if ((param_1[0x1e5449] & 2U) != 0) {
    return 1;
  }
LAB_000e0148:
  SetCommonHtVht(param_1,pcVar3);
  return 1;
}

