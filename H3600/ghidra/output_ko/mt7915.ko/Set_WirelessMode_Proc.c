// module: mt7915.ko
// function: Set_WirelessMode_Proc @ 0xdc418
// size: 4 bytes
//

int Set_WirelessMode_Proc(int *param_1,undefined4 param_2)

{
  undefined1 uVar1;
  ushort uVar2;
  int iVar3;
  undefined4 uVar4;
  undefined4 uVar5;
  int iVar6;
  int iVar7;
  int *piVar8;
  char *pcVar9;
  undefined *puVar10;
  int iVar11;
  char cVar12;
  uint uVar13;
  
  uVar1 = os_str_tol(param_2,0,10);
  uVar2 = cfgmode_2_wmode(uVar1);
  iVar11 = *param_1;
  iVar3 = wmode_valid_and_correct(param_1);
  if (iVar3 != 0) {
    cVar12 = *(char *)((int)param_1 + 0x286285);
    if (cVar12 == '\x01') {
      iVar7 = *(int *)(iVar11 + 0x3c);
      *(ushort *)(param_1 + (int)(WtcGetWcidLinkType + iVar7 * 0x160d)) = uVar2;
      iVar3 = RT_CfgSetMbssWirelessMode(param_1,param_2);
      if (iVar3 == 0) goto LAB_000dc2a8;
      if (*(char *)((int)param_1 + 0x2b7242) != '\0') {
        uVar13 = 0;
        piVar8 = param_1 + 0xadc98;
        do {
          uVar13 = uVar13 + 1;
          iVar6 = wmode_band_equal((short)*piVar8,uVar2);
          if (iVar6 != 0) {
            *(undefined1 *)(piVar8 + 0x22f) = *(undefined1 *)((int)piVar8 + 0x481a);
          }
          piVar8 = piVar8 + 0x160d;
        } while (uVar13 < *(byte *)((int)param_1 + 0x2b7242));
      }
      if (2 < DebugLevel) {
        printk("Set_Cmm_WirelessMode_Proc::(BSS%d=%d)\n",*(undefined4 *)(iVar11 + 0x3c),
               (short)param_1[(int)(WtcGetWcidLinkType + iVar7 * 0x160d)]);
      }
      pcVar9 = (char *)((int)param_1 +
                       (int)(
                            "======== Badnode detector =============\nvow_bn_en = <0/1> 0:dieable, 1:enable\nvow_bn_mon_period = <period> ms\nvow_bn_fallback_th = <count>\nvow_bn_per_th = <TX PER>\n======== Airtime counter test =============\nvow_counter_test = <0/1> 0:dieable, 1:enable\nvow_counter_test_period = <period> ms\nvow_counter_test_band = <band>\nvow_counter_test_avgcnt = <average num> sec\nvow_counter_test_target = <wlanidx>\n======== DVT =============\nvow_dvt_en = <0/1> 0:dieable, 1:enable\nvow_monitor_sta = <STA num>\nvow_show_sta = <STA num>\nvow_monitor_bss = <BSS num>\nvow_monitor_mbss = <MBSS num>\nvow_show_mbss = <MBSS num>\nvow_avg_num = <average num> sec\n======== RED ===========\nvow_set_red_en = <0/1> 0:disable, 1:enable\nvow_set_red_show_sta = <STA num>\nvow_set_red_tar_delay = <tarDelay> us\n======== WATF ===========\nvow_watf_en = <0/1> 0:disable, 1:enable\nvow_watf_q = <level>-<quantum> unit 256us\nvow_watf_add_entry = <level>-<Addr>\nvow_watf_del_entry = <Addr>\n"
                            + iVar7 * 0x5834 + 0xe0));
      HcAcquireRadioForWdev(param_1,pcVar9);
      uVar4 = HcGetBandByWdev(pcVar9);
      uVar4 = hc_get_channel_ctrl(param_1[0x29e5e8],uVar4);
      hc_set_ChCtrlChListStat(uVar4,0);
      BuildChannelList(param_1,pcVar9);
      RTMPSetPhyMode(param_1,pcVar9,uVar2);
      RTMPUpdateRateInfo(uVar2,(char *)((int)param_1 +
                                       (int)(
                                            "Wrong format, vow_watf_q=[Level]-[Quantum]\n[Level] should be among 0 to 3 !\n[Quantum] unit is 256us.\n"
                                            + iVar7 * 0x5834 + 0x36)));
      UpdateBeaconHandler(param_1,pcVar9,2);
      cVar12 = *(char *)((int)param_1 + 0x286285);
    }
    else {
      iVar3 = 1;
    }
    if (cVar12 != '\0') {
      return iVar3;
    }
    piVar8 = param_1 + *(int *)(iVar11 + 0x3c) * 0x84dec;
    puVar10 = (undefined *)
              ((int)param_1 + (int)(&DAT_0036db58 + *(int *)(iVar11 + 0x3c) * 0x2137b0));
    *(ushort *)(piVar8 + 0xdb6dc) = uVar2;
    uVar4 = get_scan_tab_by_wdev(param_1,puVar10);
    iVar3 = RT_CfgSetWirelessMode(param_1,param_2,puVar10);
    if (iVar3 != 0) {
      HcAcquireRadioForWdev(param_1,puVar10);
      uVar5 = HcGetBandByWdev(puVar10);
      uVar5 = hc_get_channel_ctrl(param_1[0x29e5e8],uVar5);
      hc_set_ChCtrlChListStat(uVar5,0);
      BuildChannelList(param_1,puVar10);
      RTMPSetPhyMode(param_1,puVar10,uVar2);
      RTMPUpdateRateInfo(uVar2,&DAT_0036e636 + (int)piVar8);
      BssTableInit(uVar4);
      piVar8[0xdb9c2] = 0;
      wlan_config_set_ba_enable(puVar10,(uVar2 & 0x18) != 0);
      if ((char)piVar8[0xdc6ee] == '\0') {
        MlmeUpdateTxRates(param_1,0,0);
        UpdateBeaconHandler(param_1,puVar10,1);
        AsicEnableIbssSync(param_1,(short)param_1[0x1e5314],0,2);
        return iVar3;
      }
      return iVar3;
    }
  }
LAB_000dc2a8:
  if (-1 < DebugLevel) {
    printk("Set_WirelessMode_Proc::parameters out of range\n");
  }
  return 0;
}

