// module: mt7915.ko
// function: rtmp_set_channel @ 0xd8ec8
// size: 2084 bytes
//

undefined4 rtmp_set_channel(int param_1,int param_2,uint param_3)

{
  undefined1 uVar1;
  int iVar2;
  int iVar3;
  int iVar4;
  undefined4 uVar5;
  uint uVar6;
  int iVar7;
  char cVar8;
  undefined1 *puVar9;
  char *pcVar10;
  bool bVar11;
  char *local_dc;
  undefined1 local_cc;
  undefined4 local_cb;
  undefined4 local_c7;
  undefined4 local_c3;
  undefined4 local_bf;
  undefined1 local_a4;
  undefined1 local_a3;
  undefined1 local_a2;
  undefined1 local_a1;
  undefined1 local_a0;
  undefined1 local_9f;
  
  iVar2 = GetStaCfgByWdev();
  (&DAT_0036b830)[param_1] = 0;
  if (param_2 == 0) {
    if (-1 < DebugLevel) {
      printk("%s: wdev == NULL!\n","rtmp_set_channel");
      return 0;
    }
    return 0;
  }
  iVar3 = IsHcRadioCurStatOffByWdev(param_2);
  if (iVar3 == 0) {
    puVar9 = *(undefined1 **)(param_2 + 0x3fe4);
    if (puVar9 == (undefined1 *)0x0) {
      if (DebugLevel < 0) {
        return 0;
      }
      printk("%s:  wdev  pDot11h is null\n","rtmp_set_channel");
      return 0;
    }
    uVar1 = *(undefined1 *)(param_2 + 0x1a);
    *(char *)(param_2 + 0x1a) = (char)param_3;
    wdev_sync_prim_ch(*(undefined4 *)(param_2 + 8),param_2);
    if ((*(char *)(param_1 + 0x795074) == '\x01') &&
       (iVar3 = CheckNonOccupancyChannel(param_1,param_2,0), iVar3 == 0)) {
      if (-1 < DebugLevel) {
        printk("%s: Can not update channel(%d), restoring old channel(%d)\n","rtmp_set_channel",
               *(undefined1 *)(param_2 + 0x1a),uVar1);
      }
      *(undefined1 *)(param_2 + 0x1a) = uVar1;
      wdev_sync_prim_ch(*(undefined4 *)(param_2 + 8),param_2);
      if (*(char *)(param_1 + 0x795404) == '\0') {
        return 0;
      }
    }
    iVar3 = HcGetBandByWdev(param_2);
    iVar4 = hc_get_channel_ctrl(*(undefined4 *)(param_1 + 0xa797a0),iVar3);
    cVar8 = *(char *)(param_1 + 0x79504d);
    if (cVar8 == '\x01') {
      iVar7 = RadarChannelCheck(param_1,*(undefined1 *)(param_2 + 0x1a));
      if ((iVar7 != 0) && (*(char *)(iVar4 + 0x49c) == '\0')) {
        *(undefined1 *)(param_1 + iVar3 + 0x7953e9) = 1;
        DfsBuildChannelList(param_1,param_2);
      }
      cVar8 = *(char *)(param_1 + 0x79504d);
    }
    if (*(int *)(param_2 + 0x14) == 1) {
      uVar6 = (uint)*(byte *)(param_2 + 0xe);
LAB_000d9200:
      pcVar10 = "======== Badnode detector =============\nvow_bn_en = <0/1> 0:dieable, 1:enable\nvow_bn_mon_period = <period> ms\nvow_bn_fallback_th = <count>\nvow_bn_per_th = <TX PER>\n======== Airtime counter test =============\nvow_counter_test = <0/1> 0:dieable, 1:enable\nvow_counter_test_period = <period> ms\nvow_counter_test_band = <band>\nvow_counter_test_avgcnt = <average num> sec\nvow_counter_test_target = <wlanidx>\n======== DVT =============\nvow_dvt_en = <0/1> 0:dieable, 1:enable\nvow_monitor_sta = <STA num>\nvow_show_sta = <STA num>\nvow_monitor_bss = <BSS num>\nvow_monitor_mbss = <MBSS num>\nvow_show_mbss = <MBSS num>\nvow_avg_num = <average num> sec\n======== RED ===========\nvow_set_red_en = <0/1> 0:disable, 1:enable\nvow_set_red_show_sta = <STA num>\nvow_set_red_tar_delay = <tarDelay> us\n======== WATF ===========\nvow_watf_en = <0/1> 0:disable, 1:enable\nvow_watf_q = <level>-<quantum> unit 256us\nvow_watf_add_entry = <level>-<Addr>\nvow_watf_del_entry = <Addr>\n"
                + uVar6 * 0x5834 + param_1 + 0xe0;
      local_dc = pcVar10;
      if (pcVar10 != (char *)0x0) {
        local_dc = *(char **)pcVar10;
      }
    }
    else if ((*(byte *)(param_1 + 0x286294) & 3) == 3 && *(int *)(param_2 + 0x14) == 2) {
      pcVar10 = (char *)0x0;
      local_dc = pcVar10;
      if ("======== Badnode detector =============\nvow_bn_en = <0/1> 0:dieable, 1:enable\nvow_bn_mon_period = <period> ms\nvow_bn_fallback_th = <count>\nvow_bn_per_th = <TX PER>\n======== Airtime counter test =============\nvow_counter_test = <0/1> 0:dieable, 1:enable\nvow_counter_test_period = <period> ms\nvow_counter_test_band = <band>\nvow_counter_test_avgcnt = <average num> sec\nvow_counter_test_target = <wlanidx>\n======== DVT =============\nvow_dvt_en = <0/1> 0:dieable, 1:enable\nvow_monitor_sta = <STA num>\nvow_show_sta = <STA num>\nvow_monitor_bss = <BSS num>\nvow_monitor_mbss = <MBSS num>\nvow_show_mbss = <MBSS num>\nvow_avg_num = <average num> sec\n======== RED ===========\nvow_set_red_en = <0/1> 0:disable, 1:enable\nvow_set_red_show_sta = <STA num>\nvow_set_red_tar_delay = <tarDelay> us\n======== WATF ===========\nvow_watf_en = <0/1> 0:disable, 1:enable\nvow_watf_q = <level>-<quantum> unit 256us\nvow_watf_add_entry = <level>-<Addr>\nvow_watf_del_entry = <Addr>\n"
          [param_1 + 0xda] != '\0') {
        pcVar10 = "======== Badnode detector =============\nvow_bn_en = <0/1> 0:dieable, 1:enable\nvow_bn_mon_period = <period> ms\nvow_bn_fallback_th = <count>\nvow_bn_per_th = <TX PER>\n======== Airtime counter test =============\nvow_counter_test = <0/1> 0:dieable, 1:enable\nvow_counter_test_period = <period> ms\nvow_counter_test_band = <band>\nvow_counter_test_avgcnt = <average num> sec\nvow_counter_test_target = <wlanidx>\n======== DVT =============\nvow_dvt_en = <0/1> 0:dieable, 1:enable\nvow_monitor_sta = <STA num>\nvow_show_sta = <STA num>\nvow_monitor_bss = <BSS num>\nvow_monitor_mbss = <MBSS num>\nvow_show_mbss = <MBSS num>\nvow_avg_num = <average num> sec\n======== RED ===========\nvow_set_red_en = <0/1> 0:disable, 1:enable\nvow_set_red_show_sta = <STA num>\nvow_set_red_tar_delay = <tarDelay> us\n======== WATF ===========\nvow_watf_en = <0/1> 0:disable, 1:enable\nvow_watf_q = <level>-<quantum> unit 256us\nvow_watf_add_entry = <level>-<Addr>\nvow_watf_del_entry = <Addr>\n"
                  + param_1 + 0xfa;
        uVar6 = 0;
        do {
          if ((*pcVar10 == *(char *)(param_2 + 0x1a)) && (pcVar10[0xe] != '\0')) goto LAB_000d9200;
          uVar6 = uVar6 + 1;
          pcVar10 = pcVar10 + 0x5834;
        } while (uVar6 != (byte)("======== Badnode detector =============\nvow_bn_en = <0/1> 0:dieable, 1:enable\nvow_bn_mon_period = <period> ms\nvow_bn_fallback_th = <count>\nvow_bn_per_th = <TX PER>\n======== Airtime counter test =============\nvow_counter_test = <0/1> 0:dieable, 1:enable\nvow_counter_test_period = <period> ms\nvow_counter_test_band = <band>\nvow_counter_test_avgcnt = <average num> sec\nvow_counter_test_target = <wlanidx>\n======== DVT =============\nvow_dvt_en = <0/1> 0:dieable, 1:enable\nvow_monitor_sta = <STA num>\nvow_show_sta = <STA num>\nvow_monitor_bss = <BSS num>\nvow_monitor_mbss = <MBSS num>\nvow_show_mbss = <MBSS num>\nvow_avg_num = <average num> sec\n======== RED ===========\nvow_set_red_en = <0/1> 0:disable, 1:enable\nvow_set_red_show_sta = <STA num>\nvow_set_red_tar_delay = <tarDelay> us\n======== WATF ===========\nvow_watf_en = <0/1> 0:disable, 1:enable\nvow_watf_q = <level>-<quantum> unit 256us\nvow_watf_add_entry = <level>-<Addr>\nvow_watf_del_entry = <Addr>\n"
                                 [param_1 + 0xda] - 1) + 1);
        pcVar10 = (char *)0x0;
        local_dc = (char *)0x0;
      }
    }
    else {
      pcVar10 = (char *)0x0;
      local_dc = pcVar10;
    }
    if ((*(char *)(param_1 + 0x286285) == '\x01') && ((&DAT_003678fb)[param_1] == '\0')) {
      (&DAT_003678fb)[param_1] = 1;
    }
    if (((cVar8 == '\0') ||
        (iVar3 = SwitchChSanityCheckDBDC(param_1,param_2,uVar1,param_3), iVar3 == 0)) &&
       (iVar3 = SwitchChSanityCheck(param_1,uVar1,param_3), iVar3 != 1)) {
      if (*(char *)(param_1 + 0x286285) != '\x01') {
        bVar11 = *(char *)(param_1 + 0x286285) != '\0';
        if (1 < DebugLevel) {
LAB_000d9654:
          printk("This channel is out of channel list, nothing to do!\n ");
          cVar8 = *(char *)(param_1 + 0x286285);
          goto LAB_000d909c;
        }
LAB_000d9104:
        if (!bVar11) {
          return 0;
        }
LAB_000d9144:
        if (2 < DebugLevel) {
          printk("Set_Channel_Proc_by_Wdev::(Channel=%d)\n",param_3);
        }
        goto LAB_000d902c;
      }
      param_3 = FirstChannel(param_1,param_2);
      if (DebugLevel < 2) {
        cVar8 = *(char *)(param_1 + 0x286285);
        bVar11 = false;
        if (cVar8 != '\0') {
          bVar11 = true;
        }
      }
      else {
        printk("This channel is out of channel list, set as the first channel(%d)\n ",param_3);
        cVar8 = *(char *)(param_1 + 0x286285);
        bVar11 = cVar8 != '\0';
        if (1 < DebugLevel) goto LAB_000d9654;
      }
LAB_000d909c:
      if (cVar8 != '\x01') goto LAB_000d9104;
      if (bVar11) goto LAB_000d92a8;
      uVar5 = 0;
    }
    else {
      cVar8 = *(char *)(param_1 + 0x286285);
      if (cVar8 != '\0') {
LAB_000d9134:
        if (cVar8 == '\x01') {
LAB_000d92a8:
          if ((param_3 < 0xf) || (*(char *)(param_1 + 0x795074) != '\x01')) {
            wlan_operate_set_prim_ch(param_2,*(undefined1 *)(param_2 + 0x1a));
            if (pcVar10 != (char *)0x0) {
              APStop(param_1,pcVar10,1);
              APStartUp(param_1,pcVar10,1);
            }
          }
          else {
            puVar9[5] = uVar1;
            if (pcVar10 == (char *)0x0) {
              if (-1 < DebugLevel) {
                printk("Only Change CLI Channel to %d!\n",*(undefined1 *)(param_2 + 0x1a));
              }
              wlan_operate_set_prim_ch(param_2,*(undefined1 *)(param_2 + 0x1a));
              (&DAT_003678fb)[param_1] = 0;
              return 1;
            }
            if ((puVar9[4] == '\x02') ||
               ((local_dc != (char *)0x0 && ((*(uint *)(local_dc + 0x138) & 1) == 0)))) {
              puVar9[4] = 1;
              APStop(param_1,pcVar10);
              iVar2 = DfsStopWifiCheck(param_1,param_2);
              if (iVar2 != 0) {
                if (DebugLevel < 1) {
                  return 0;
                }
                printk("[%s] Stop AP Startup\n","rtmp_set_channel");
                return 0;
              }
              if ((*(ushort *)(param_2 + 0x18) & 0xb1) == 0) {
                uVar5 = 1;
              }
              else {
                uVar5 = 2;
              }
              iVar2 = HcGetBandByWdev(param_2);
              if (0 < DebugLevel) {
                printk("%s 2.4G channel switch RFIC = %d\n","rtmp_set_channel",uVar5);
              }
              iVar2 = iVar2 * 0xaf5d8 + param_1;
              local_cc = 0x29;
              local_cb = *(undefined4 *)(iVar2 + 0x82929a);
              local_c3 = *(undefined4 *)(iVar2 + 0x8292a2);
              local_c7 = *(undefined4 *)(iVar2 + 0x82929e);
              local_bf = *(undefined4 *)(iVar2 + 0x8292a6);
              uVar5 = HcGetChannelByRf(param_1,uVar5);
              local_a4 = (undefined1)uVar5;
              if (0 < DebugLevel) {
                printk("%s 2.4G channel to switch = %d\n","rtmp_set_channel",uVar5);
              }
              local_a3 = wlan_config_get_ht_bw
                                   ("======== Badnode detector =============\nvow_bn_en = <0/1> 0:dieable, 1:enable\nvow_bn_mon_period = <period> ms\nvow_bn_fallback_th = <count>\nvow_bn_per_th = <TX PER>\n======== Airtime counter test =============\nvow_counter_test = <0/1> 0:dieable, 1:enable\nvow_counter_test_period = <period> ms\nvow_counter_test_band = <band>\nvow_counter_test_avgcnt = <average num> sec\nvow_counter_test_target = <wlanidx>\n======== DVT =============\nvow_dvt_en = <0/1> 0:dieable, 1:enable\nvow_monitor_sta = <STA num>\nvow_show_sta = <STA num>\nvow_monitor_bss = <BSS num>\nvow_monitor_mbss = <MBSS num>\nvow_show_mbss = <MBSS num>\nvow_avg_num = <average num> sec\n======== RED ===========\nvow_set_red_en = <0/1> 0:disable, 1:enable\nvow_set_red_show_sta = <STA num>\nvow_set_red_tar_delay = <tarDelay> us\n======== WATF ===========\nvow_watf_en = <0/1> 0:disable, 1:enable\nvow_watf_q = <level>-<quantum> unit 256us\nvow_watf_add_entry = <level>-<Addr>\nvow_watf_del_entry = <Addr>\n"
                                    + param_1 + 0xe0);
              local_a2 = wlan_config_get_vht_bw
                                   ("======== Badnode detector =============\nvow_bn_en = <0/1> 0:dieable, 1:enable\nvow_bn_mon_period = <period> ms\nvow_bn_fallback_th = <count>\nvow_bn_per_th = <TX PER>\n======== Airtime counter test =============\nvow_counter_test = <0/1> 0:dieable, 1:enable\nvow_counter_test_period = <period> ms\nvow_counter_test_band = <band>\nvow_counter_test_avgcnt = <average num> sec\nvow_counter_test_target = <wlanidx>\n======== DVT =============\nvow_dvt_en = <0/1> 0:dieable, 1:enable\nvow_monitor_sta = <STA num>\nvow_show_sta = <STA num>\nvow_monitor_bss = <BSS num>\nvow_monitor_mbss = <MBSS num>\nvow_show_mbss = <MBSS num>\nvow_avg_num = <average num> sec\n======== RED ===========\nvow_set_red_en = <0/1> 0:disable, 1:enable\nvow_set_red_show_sta = <STA num>\nvow_set_red_tar_delay = <tarDelay> us\n======== WATF ===========\nvow_watf_en = <0/1> 0:disable, 1:enable\nvow_watf_q = <level>-<quantum> unit 256us\nvow_watf_add_entry = <level>-<Addr>\nvow_watf_del_entry = <Addr>\n"
                                    + param_1 + 0xe0);
              local_a1 = *(undefined1 *)(param_1 + 0x795075);
              local_a0 = GetCountryRegionFromCountryCode(param_1 + 0x794c31);
              local_9f = "SetPartProfileParameters"[param_1 + 0x18] == 'D';
              RtmpOSWrielessEventSend(*(undefined4 *)(param_1 + 4),1,0x955,0,&local_cc,0xa4);
              APStartUp(param_1,pcVar10,1);
            }
            else {
              iVar2 = *(int *)(param_2 + 0x14);
              if ((iVar2 - 0x10U & 0xffffffef) == 0 || (iVar2 == 4 || iVar2 == 1)) {
                NotifyChSwAnnToPeerAPs(param_1,&ZERO_MAC_ADDR,param_1 + 0x794b5b,1,param_3);
                *puVar9 = 0;
                puVar9[6] = (char)param_3;
                puVar9[4] = 1;
                iVar2 = HcUpdateCsaCntByChannel(param_1,uVar1);
                if (iVar2 != 0) goto LAB_000d9038;
              }
              else {
                wlan_operate_set_prim_ch(param_2,*(undefined1 *)(param_2 + 0x1a));
                APStop(param_1,pcVar10,1);
                APStartUp(param_1,pcVar10,1);
              }
            }
          }
        }
        goto LAB_000d9144;
      }
      if (iVar2 != 0) {
        *(char *)(iVar2 + 0x4165) = (char)param_3;
      }
      wlan_operate_set_prim_ch(param_2,param_3);
      if (2 < DebugLevel) {
        uVar5 = wlan_operate_get_cen_ch_1(param_2);
        printk("%s(): CtrlChannel(%d), CentralChannel(%d)\n","rtmp_set_channel",param_3,uVar5);
        cVar8 = *(char *)(param_1 + 0x286285);
        goto LAB_000d9134;
      }
      if (*(char *)(param_1 + 0x286285) == '\x01') goto LAB_000d92a8;
LAB_000d902c:
      uVar5 = 1;
      if (*(char *)(param_1 + 0x286285) != '\x01') goto LAB_000d9038;
    }
    (&DAT_003678fb)[param_1] = 0;
  }
  else {
LAB_000d9038:
    uVar5 = 1;
  }
  return uVar5;
}

