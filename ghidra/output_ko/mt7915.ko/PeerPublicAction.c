// module: mt7915.ko
// function: PeerPublicAction @ 0xa3104
// size: 2036 bytes
//

void PeerPublicAction(int param_1,int param_2)

{
  byte bVar1;
  ushort uVar2;
  int iVar3;
  int iVar4;
  uint uVar5;
  undefined4 uVar6;
  int iVar7;
  int iVar8;
  byte *pbVar9;
  undefined4 uVar10;
  byte *pbVar11;
  char cVar12;
  int iVar13;
  byte *pbVar14;
  int iVar15;
  ushort *puVar16;
  int iVar17;
  undefined1 auStack_44 [2];
  byte local_42;
  byte local_41;
  undefined4 local_40;
  
  cVar12 = *(char *)(param_2 + 0x19);
  iVar3 = GetStaCfgByWdev(param_1,*(undefined4 *)(param_2 + 0x92c));
  puVar16 = (ushort *)(param_2 + 0x920);
  iVar4 = hc_get_chip_cap(*(undefined4 *)(param_1 + 0xa797a0));
  uVar2 = *puVar16;
  uVar5 = HcGetMaxStaNum(param_1);
  if (uVar5 <= uVar2) {
    return;
  }
  if (cVar12 != '\0') {
    return;
  }
  uVar2 = *puVar16;
  uVar5 = HcGetMaxStaNum(param_1);
  if (uVar5 <= uVar2) {
    if (DebugLevel < 1) {
      return;
    }
    printk("%s, Wrong Wcid:%d !!! need to check the root cause!!!!","PeerPublicAction",*puVar16);
    return;
  }
  uVar5 = *(uint *)(param_2 + 0x908);
  iVar17 = *(int *)((uint)*puVar16 * 0x14c0 + param_1 + 0xa1d28);
  if (uVar5 < 0x1c) {
    if (DebugLevel < 0) {
      return;
    }
    printk("ACTION - 20/40 BSS Coexistence Management Frame length too short! len = %ld!\n",uVar5);
    return;
  }
  if (2 < DebugLevel) {
    printk("ACTION - 20/40 BSS Coexistence Management action---->\n");
    uVar5 = *(uint *)(param_2 + 0x908);
  }
  hex_dump("CoexistenceMgmtFrame",param_2,uVar5);
  if (*(uint *)(param_2 + 0x908) < 0x1e) {
    iVar13 = 0;
  }
  else {
    iVar13 = param_2 + 0x1d;
  }
  if ((*(char *)(param_1 + 0x79564e) == '\0') || (*(char *)(param_1 + 0x795947) == '\x01')) {
    if (DebugLevel < 3) {
      return;
    }
    printk("20/40 BSS CoexMgmt=%d, bForty_Mhz_Intolerant=%d, ignore this action!!\n",
           *(char *)(param_1 + 0x79564e),*(undefined1 *)(param_1 + 0x795947));
    return;
  }
  cVar12 = *(char *)(param_1 + 0x286285);
  if (cVar12 != '\x01') goto LAB_000a3264;
  if (*(int *)((uint)*puVar16 * 0x14c0 + param_1 + 0xa1d20) != 0x20001) {
    return;
  }
  if (iVar17 == 0) {
    uVar6 = 0;
    if (2 < DebugLevel) {
      printk("[PeerPublicAction] wdev = NULL\n",0x14c0);
    }
  }
  else {
    uVar6 = HcGetBandByWdev(iVar17);
  }
  iVar7 = hc_get_channel_ctrl(*(undefined4 *)(param_1 + 0xa797a0),uVar6);
  bVar1 = *(byte *)(param_2 + 0x1c);
  if ((bVar1 & 6) == 0) {
    if ((iVar13 != 0) && (uVar5 = (uint)*(byte *)(iVar13 + 1), 1 < uVar5)) {
      pbVar11 = (byte *)(iVar13 + 3);
      if (DebugLevel < 3) {
LAB_000a34b8:
        iVar15 = 0;
        iVar8 = DebugLevel;
        pbVar14 = pbVar11;
        do {
          iVar15 = iVar15 + 1;
          if (2 < iVar8) {
            printk(&_LC45,*pbVar14);
            uVar5 = (uint)*(byte *)(iVar13 + 1);
            iVar8 = DebugLevel;
          }
          pbVar14 = pbVar14 + 1;
        } while (iVar15 < (int)(uVar5 - 1));
      }
      else {
        printk("The pIntolerantReport len = %d, chlist=");
        uVar5 = (uint)*(byte *)(iVar13 + 1);
        if (0 < (int)(uVar5 - 1)) goto LAB_000a34b8;
      }
      if (2 < DebugLevel) {
        printk(&_LC46);
      }
      if ((iVar17 == 0) ||
         (iVar8 = GetBssCoexEffectedChRange
                            (param_1,iVar17,auStack_44,*(undefined1 *)(iVar17 + 0x1a)), iVar8 != 1))
      {
LAB_000a352c:
        *(byte *)(param_2 + 0x1c) = *(byte *)(param_2 + 0x1c) | 6;
        goto LAB_000a3334;
      }
      if (DebugLevel < 3) {
        iVar13 = *(byte *)(iVar13 + 1) - 1;
        if (iVar13 < 1) goto LAB_000a347c;
LAB_000a35c0:
        pbVar14 = pbVar11;
        do {
          pbVar9 = pbVar14 + 1;
          if ((*(byte *)(iVar7 + (uint)local_42 * 0x14) <= *pbVar14) &&
             (*pbVar14 <= *(byte *)((uint)local_41 * 0x14 + iVar7))) {
            if ((2 < DebugLevel) &&
               (printk("Found Intolerant channel in effect range=%d!\n"), 2 < DebugLevel)) {
              printk("After CoexChRange Check, bNeedFallBack=%d!\n",1);
            }
            goto LAB_000a352c;
          }
          pbVar14 = pbVar9;
        } while ((int)pbVar9 - (int)pbVar11 < iVar13);
      }
      else {
        printk("Check IntolerantReport Channel List in our effectedChList(%d~%d)\n",
               *(undefined1 *)(iVar7 + (uint)local_42 * 0x14),
               *(undefined1 *)(iVar7 + (uint)local_41 * 0x14));
        iVar13 = *(byte *)(iVar13 + 1) - 1;
        if (0 < iVar13) goto LAB_000a35c0;
      }
      if (2 < DebugLevel) {
        printk("After CoexChRange Check, bNeedFallBack=%d!\n",0);
        cVar12 = *(char *)(param_1 + 0x286285);
        goto LAB_000a3264;
      }
    }
  }
  else {
    if (2 < DebugLevel) {
      printk("BSS_2040_COEXIST: BSS20WidthReq=%d, Intolerant40=%d!\n",((uint)bVar1 << 0x1d) >> 0x1f,
             ((uint)bVar1 << 0x1e) >> 0x1f);
    }
LAB_000a3334:
    *(undefined1 *)(param_1 + 0x7956b4) = *(undefined1 *)(param_2 + 0x1c);
    bVar1 = *(byte *)(param_1 + 0x795652);
    *(byte *)(param_1 + 0x795652) = bVar1 | 2;
    if ((bVar1 & 1) == 0) {
      if (2 < DebugLevel) {
        printk("Fire the Bss2040CoexistTimer with timeout=%ld!\n",
               *(undefined4 *)(param_1 + 0x7956ac));
      }
      *(byte *)(param_1 + 0x795652) = *(byte *)(param_1 + 0x795652) | 1;
      RTMPSetTimer(param_1 + 0x795654,*(int *)(param_1 + 0x7956ac) * 1000 + 5000);
    }
    else {
      if (2 < DebugLevel) {
        printk("Already fallback to 20MHz, Extend the timeout of Bss2040CoexistTimer!\n");
      }
      RTMPModTimer(param_1 + 0x795654,*(int *)(param_1 + 0x7956ac) * 1000 + 5000);
    }
    if (*(char *)((uint)*puVar16 * 0x14c0 + param_1 + 0xa2a33) != '\0') {
      return;
    }
    if ("======== Badnode detector =============\nvow_bn_en = <0/1> 0:dieable, 1:enable\nvow_bn_mon_period = <period> ms\nvow_bn_fallback_th = <count>\nvow_bn_per_th = <TX PER>\n======== Airtime counter test =============\nvow_counter_test = <0/1> 0:dieable, 1:enable\nvow_counter_test_period = <period> ms\nvow_counter_test_band = <band>\nvow_counter_test_avgcnt = <average num> sec\nvow_counter_test_target = <wlanidx>\n======== DVT =============\nvow_dvt_en = <0/1> 0:dieable, 1:enable\nvow_monitor_sta = <STA num>\nvow_show_sta = <STA num>\nvow_monitor_bss = <BSS num>\nvow_monitor_mbss = <MBSS num>\nvow_show_mbss = <MBSS num>\nvow_avg_num = <average num> sec\n======== RED ===========\nvow_set_red_en = <0/1> 0:disable, 1:enable\nvow_set_red_show_sta = <STA num>\nvow_set_red_tar_delay = <tarDelay> us\n======== WATF ===========\nvow_watf_en = <0/1> 0:disable, 1:enable\nvow_watf_q = <level>-<quantum> unit 256us\nvow_watf_add_entry = <level>-<Addr>\nvow_watf_del_entry = <Addr>\n"
        [param_1 + 0xda] == '\0') {
      uVar5 = 0;
    }
    else {
      uVar5 = 0;
      do {
        SendBSS2040CoexistMgmtAction(param_1,0,uVar5 & 0xff,0);
        uVar5 = uVar5 + 1;
      } while ((int)uVar5 <
               (int)(uint)(byte)"======== Badnode detector =============\nvow_bn_en = <0/1> 0:dieable, 1:enable\nvow_bn_mon_period = <period> ms\nvow_bn_fallback_th = <count>\nvow_bn_per_th = <TX PER>\n======== Airtime counter test =============\nvow_counter_test = <0/1> 0:dieable, 1:enable\nvow_counter_test_period = <period> ms\nvow_counter_test_band = <band>\nvow_counter_test_avgcnt = <average num> sec\nvow_counter_test_target = <wlanidx>\n======== DVT =============\nvow_dvt_en = <0/1> 0:dieable, 1:enable\nvow_monitor_sta = <STA num>\nvow_show_sta = <STA num>\nvow_monitor_bss = <BSS num>\nvow_monitor_mbss = <MBSS num>\nvow_show_mbss = <MBSS num>\nvow_avg_num = <average num> sec\n======== RED ===========\nvow_set_red_en = <0/1> 0:disable, 1:enable\nvow_set_red_show_sta = <STA num>\nvow_set_red_tar_delay = <tarDelay> us\n======== WATF ===========\nvow_watf_en = <0/1> 0:disable, 1:enable\nvow_watf_q = <level>-<quantum> unit 256us\nvow_watf_add_entry = <level>-<Addr>\nvow_watf_del_entry = <Addr>\n"
                                [param_1 + 0xda]);
    }
    *(undefined1 *)((uint)*puVar16 * 0x14c0 + param_1 + 0xa2a31) = 1;
    *(undefined1 *)((uint)*puVar16 * 0x14c0 + param_1 + 0xa2a33) = 1;
    if (iVar17 != 0) {
      if (((*(byte *)(param_1 + 0x795652) & 2) != 0) && (*(char *)(param_1 + 0x795947) == '\0')) {
        uVar6 = wlan_config_get_ht_bw(iVar17);
        uVar10 = wlan_config_get_ext_cha(iVar17);
        if (2 < DebugLevel) {
          printk("DTIM Period reached, BSS20WidthReq=%d, Intolerant40=%d!\n",
                 ((uint)*(byte *)(param_1 + 0x7956b4) << 0x1d) >> 0x1f,
                 ((uint)*(byte *)(param_1 + 0x7956b4) << 0x1e) >> 0x1f);
        }
        *(byte *)(param_1 + 0x795652) = *(byte *)(param_1 + 0x795652) & 0xfd;
        if ((*(byte *)(param_1 + 0x7956b4) & 6) == 0) {
          zte_wlan_operate_set_ht_bw(iVar17,uVar6,uVar10);
        }
        else {
          zte_wlan_operate_set_ht_bw(iVar17,0,0);
        }
        if (2 < DebugLevel) {
          uVar6 = wlan_operate_get_ht_bw(iVar17);
          uVar10 = wlan_operate_get_ext_cha(iVar17);
          printk("\tNow RecomWidth=%d, ExtChanOffset=%d\n",uVar6,uVar10);
        }
        *(byte *)(param_1 + 0x795652) = *(byte *)(param_1 + 0x795652) | 4;
        if (*(char *)(iVar4 + 0x150) == '\x01') {
          __memzero(auStack_44,0x1c);
          local_40 = 2;
          RAParamUpdate(param_1,(uint)*puVar16 * 0x14c0 + param_1 + 0xa1d20,auStack_44);
        }
      }
      if (2 < DebugLevel) {
        printk("%s, ACTION_BSS_2040_COEXIST Update Beacon for idx:%d\n","PeerPublicAction",uVar5);
      }
      ZTE_UpdateBeaconHandler(param_1,iVar17,2);
    }
  }
LAB_000a347c:
  cVar12 = *(char *)(param_1 + 0x286285);
LAB_000a3264:
  if ((iVar3 != 0 && cVar12 == '\0') && ((*(uint *)(iVar3 + 0x212464) & 1) != 0)) {
    StaPublicAction(param_1,param_2 + 0x1c,*(undefined4 *)(param_2 + 0x92c));
  }
  return;
}

