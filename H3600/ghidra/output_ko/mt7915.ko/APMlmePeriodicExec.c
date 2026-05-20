// module: mt7915.ko
// function: APMlmePeriodicExec @ 0x1727c
// size: 1084 bytes
//

void APMlmePeriodicExec(int param_1)

{
  ushort uVar1;
  int iVar2;
  int iVar3;
  uint uVar4;
  undefined4 uVar5;
  ushort *puVar6;
  byte bVar7;
  byte bVar8;
  int *piVar9;
  char *pcVar10;
  undefined *puVar11;
  int iVar12;
  int iVar13;
  char local_2a [6];
  
  iVar2 = HcIsRfSupport(param_1,2);
  vow_display_info_periodic(param_1);
  iVar3 = hc_get_chip_ops(*(undefined4 *)(param_1 + 0xa797a0));
  if (*(code **)(iVar3 + 0x84) != (code *)0x0) {
    (**(code **)(iVar3 + 0x84))(param_1,&DAT_0036b7fc + param_1);
  }
  iVar3 = hc_get_chip_ops(*(undefined4 *)(param_1 + 0xa797a0));
  if (*(code **)(iVar3 + 0x6c) != (code *)0x0) {
    (**(code **)(iVar3 + 0x6c))(param_1);
  }
  iVar3 = hc_get_chip_ops(*(undefined4 *)(param_1 + 0xa797a0));
  if (*(code **)(iVar3 + 0x80) != (code *)0x0) {
    (**(code **)(iVar3 + 0x80))(param_1);
  }
  if (*(uint *)(param_1 + 0x829214) % 10 == 0) {
    MacTableMaintenance(param_1);
    RTMPMaintainPMKIDCache(param_1);
    bVar7 = 0;
    if ("======== Badnode detector =============\nvow_bn_en = <0/1> 0:dieable, 1:enable\nvow_bn_mon_period = <period> ms\nvow_bn_fallback_th = <count>\nvow_bn_per_th = <TX PER>\n======== Airtime counter test =============\nvow_counter_test = <0/1> 0:dieable, 1:enable\nvow_counter_test_period = <period> ms\nvow_counter_test_band = <band>\nvow_counter_test_avgcnt = <average num> sec\nvow_counter_test_target = <wlanidx>\n======== DVT =============\nvow_dvt_en = <0/1> 0:dieable, 1:enable\nvow_monitor_sta = <STA num>\nvow_show_sta = <STA num>\nvow_monitor_bss = <BSS num>\nvow_monitor_mbss = <MBSS num>\nvow_show_mbss = <MBSS num>\nvow_avg_num = <average num> sec\n======== RED ===========\nvow_set_red_en = <0/1> 0:disable, 1:enable\nvow_set_red_show_sta = <STA num>\nvow_set_red_tar_delay = <tarDelay> us\n======== WATF ===========\nvow_watf_en = <0/1> 0:disable, 1:enable\nvow_watf_q = <level>-<quantum> unit 256us\nvow_watf_add_entry = <level>-<Addr>\nvow_watf_del_entry = <Addr>\n"
        [param_1 + 0xda] != '\0') {
      do {
        bVar8 = bVar7 + 1;
        a4_proxy_maintain(param_1,bVar7);
        bVar7 = bVar8;
      } while (bVar8 < (byte)"======== Badnode detector =============\nvow_bn_en = <0/1> 0:dieable, 1:enable\nvow_bn_mon_period = <period> ms\nvow_bn_fallback_th = <count>\nvow_bn_per_th = <TX PER>\n======== Airtime counter test =============\nvow_counter_test = <0/1> 0:dieable, 1:enable\nvow_counter_test_period = <period> ms\nvow_counter_test_band = <band>\nvow_counter_test_avgcnt = <average num> sec\nvow_counter_test_target = <wlanidx>\n======== DVT =============\nvow_dvt_en = <0/1> 0:dieable, 1:enable\nvow_monitor_sta = <STA num>\nvow_show_sta = <STA num>\nvow_monitor_bss = <BSS num>\nvow_monitor_mbss = <MBSS num>\nvow_show_mbss = <MBSS num>\nvow_avg_num = <average num> sec\n======== RED ===========\nvow_set_red_en = <0/1> 0:disable, 1:enable\nvow_set_red_show_sta = <STA num>\nvow_set_red_tar_delay = <tarDelay> us\n======== WATF ===========\nvow_watf_en = <0/1> 0:disable, 1:enable\nvow_watf_q = <level>-<quantum> unit 256us\nvow_watf_add_entry = <level>-<Addr>\nvow_watf_del_entry = <Addr>\n"
                             [param_1 + 0xda]);
    }
    *(undefined4 *)(param_1 + 0xa7cbe4) = 0;
  }
  AutoChannelSelCheck(param_1);
  if ((((*(uint *)(param_1 + 0x82921c) & 1) != 0) ||
      (ApCliIfMonitor(param_1), (*(uint *)(param_1 + 0x82921c) & 1) != 0)) &&
     ((&DAT_003678fb)[param_1] == '\0')) {
    ApCliIfUp(param_1);
  }
  if ((&DAT_0036790d)[param_1] != '\0') {
    RTMPRepeaterReconnectionCheck(param_1);
  }
  iVar3 = jiffies;
  puVar11 = &DAT_00580e8e + param_1;
  iVar12 = 6000 - jiffies;
  piVar9 = (int *)(&DAT_00580308 + param_1);
  do {
    if (((char)piVar9[2] == '\x01') && (iVar12 + *piVar9 < 0)) {
      *(undefined1 *)(piVar9 + 2) = 0;
    }
    pcVar10 = (char *)((int)piVar9 + 0xb86);
    piVar9 = piVar9 + 0x84dec;
    if (((*pcVar10 == '\x01') &&
        (uVar1 = *(ushort *)(puVar11 + -0x56), uVar4 = HcGetMaxStaNum(param_1), uVar1 < uVar4)) &&
       (iVar13 = (uint)*(ushort *)(puVar11 + -0x56) * 0x14c0 + param_1 + 0xa1d20, iVar13 != 0)) {
      MlmeCalculateChannelQuality(param_1,iVar13,iVar3);
    }
    puVar11 = puVar11 + 0x2137b0;
  } while (piVar9 != (int *)(param_1 + 0x9a7268));
  if ("======== Badnode detector =============\nvow_bn_en = <0/1> 0:dieable, 1:enable\nvow_bn_mon_period = <period> ms\nvow_bn_fallback_th = <count>\nvow_bn_per_th = <TX PER>\n======== Airtime counter test =============\nvow_counter_test = <0/1> 0:dieable, 1:enable\nvow_counter_test_period = <period> ms\nvow_counter_test_band = <band>\nvow_counter_test_avgcnt = <average num> sec\nvow_counter_test_target = <wlanidx>\n======== DVT =============\nvow_dvt_en = <0/1> 0:dieable, 1:enable\nvow_monitor_sta = <STA num>\nvow_show_sta = <STA num>\nvow_monitor_bss = <BSS num>\nvow_monitor_mbss = <MBSS num>\nvow_show_mbss = <MBSS num>\nvow_avg_num = <average num> sec\n======== RED ===========\nvow_set_red_en = <0/1> 0:disable, 1:enable\nvow_set_red_show_sta = <STA num>\nvow_set_red_tar_delay = <tarDelay> us\n======== WATF ===========\nvow_watf_en = <0/1> 0:disable, 1:enable\nvow_watf_q = <level>-<quantum> unit 256us\nvow_watf_add_entry = <level>-<Addr>\nvow_watf_del_entry = <Addr>\n"
      [param_1 + 0xda] != '\0') {
    iVar3 = 0;
    pcVar10 = "======== Badnode detector =============\nvow_bn_en = <0/1> 0:dieable, 1:enable\nvow_bn_mon_period = <period> ms\nvow_bn_fallback_th = <count>\nvow_bn_per_th = <TX PER>\n======== Airtime counter test =============\nvow_counter_test = <0/1> 0:dieable, 1:enable\nvow_counter_test_period = <period> ms\nvow_counter_test_band = <band>\nvow_counter_test_avgcnt = <average num> sec\nvow_counter_test_target = <wlanidx>\n======== DVT =============\nvow_dvt_en = <0/1> 0:dieable, 1:enable\nvow_monitor_sta = <STA num>\nvow_show_sta = <STA num>\nvow_monitor_bss = <BSS num>\nvow_monitor_mbss = <MBSS num>\nvow_show_mbss = <MBSS num>\nvow_avg_num = <average num> sec\n======== RED ===========\nvow_set_red_en = <0/1> 0:disable, 1:enable\nvow_set_red_show_sta = <STA num>\nvow_set_red_tar_delay = <tarDelay> us\n======== WATF ===========\nvow_watf_en = <0/1> 0:disable, 1:enable\nvow_watf_q = <level>-<quantum> unit 256us\nvow_watf_add_entry = <level>-<Addr>\nvow_watf_del_entry = <Addr>\n"
              + param_1 + 0xe0;
    do {
      iVar3 = iVar3 + 1;
      if (((pcVar10 != (char *)0x0) && (pcVar10[0xaa8] != '\0')) &&
         (iVar12 = wlan_config_get_ht_protect_en(pcVar10), iVar12 != 0)) {
        ApUpdateCapabilityAndErpIe(param_1,pcVar10);
        APUpdateOperationMode(param_1,pcVar10);
      }
      pcVar10 = pcVar10 + 0x5834;
    } while (iVar3 < (int)(uint)(byte)"======== Badnode detector =============\nvow_bn_en = <0/1> 0:dieable, 1:enable\nvow_bn_mon_period = <period> ms\nvow_bn_fallback_th = <count>\nvow_bn_per_th = <TX PER>\n======== Airtime counter test =============\nvow_counter_test = <0/1> 0:dieable, 1:enable\nvow_counter_test_period = <period> ms\nvow_counter_test_band = <band>\nvow_counter_test_avgcnt = <average num> sec\nvow_counter_test_target = <wlanidx>\n======== DVT =============\nvow_dvt_en = <0/1> 0:dieable, 1:enable\nvow_monitor_sta = <STA num>\nvow_show_sta = <STA num>\nvow_monitor_bss = <BSS num>\nvow_monitor_mbss = <MBSS num>\nvow_show_mbss = <MBSS num>\nvow_avg_num = <average num> sec\n======== RED ===========\nvow_set_red_en = <0/1> 0:disable, 1:enable\nvow_set_red_show_sta = <STA num>\nvow_set_red_tar_delay = <tarDelay> us\n======== WATF ===========\nvow_watf_en = <0/1> 0:disable, 1:enable\nvow_watf_q = <level>-<quantum> unit 256us\nvow_watf_add_entry = <level>-<Addr>\nvow_watf_del_entry = <Addr>\n"
                                      [param_1 + 0xda]);
  }
  if ((iVar2 != 0) && (*(char *)(param_1 + 0x795074) == '\x01')) {
    iVar2 = 0;
    local_2a[0] = '\0';
    local_2a[1] = 0;
    if ("======== Badnode detector =============\nvow_bn_en = <0/1> 0:dieable, 1:enable\nvow_bn_mon_period = <period> ms\nvow_bn_fallback_th = <count>\nvow_bn_per_th = <TX PER>\n======== Airtime counter test =============\nvow_counter_test = <0/1> 0:dieable, 1:enable\nvow_counter_test_period = <period> ms\nvow_counter_test_band = <band>\nvow_counter_test_avgcnt = <average num> sec\nvow_counter_test_target = <wlanidx>\n======== DVT =============\nvow_dvt_en = <0/1> 0:dieable, 1:enable\nvow_monitor_sta = <STA num>\nvow_show_sta = <STA num>\nvow_monitor_bss = <BSS num>\nvow_monitor_mbss = <MBSS num>\nvow_show_mbss = <MBSS num>\nvow_avg_num = <average num> sec\n======== RED ===========\nvow_set_red_en = <0/1> 0:disable, 1:enable\nvow_set_red_show_sta = <STA num>\nvow_set_red_tar_delay = <tarDelay> us\n======== WATF ===========\nvow_watf_en = <0/1> 0:disable, 1:enable\nvow_watf_q = <level>-<quantum> unit 256us\nvow_watf_add_entry = <level>-<Addr>\nvow_watf_del_entry = <Addr>\n"
        [param_1 + 0xda] != '\0') {
      pcVar10 = "======== Badnode detector =============\nvow_bn_en = <0/1> 0:dieable, 1:enable\nvow_bn_mon_period = <period> ms\nvow_bn_fallback_th = <count>\nvow_bn_per_th = <TX PER>\n======== Airtime counter test =============\nvow_counter_test = <0/1> 0:dieable, 1:enable\nvow_counter_test_period = <period> ms\nvow_counter_test_band = <band>\nvow_counter_test_avgcnt = <average num> sec\nvow_counter_test_target = <wlanidx>\n======== DVT =============\nvow_dvt_en = <0/1> 0:dieable, 1:enable\nvow_monitor_sta = <STA num>\nvow_show_sta = <STA num>\nvow_monitor_bss = <BSS num>\nvow_monitor_mbss = <MBSS num>\nvow_show_mbss = <MBSS num>\nvow_avg_num = <average num> sec\n======== RED ===========\nvow_set_red_en = <0/1> 0:disable, 1:enable\nvow_set_red_show_sta = <STA num>\nvow_set_red_tar_delay = <tarDelay> us\n======== WATF ===========\nvow_watf_en = <0/1> 0:disable, 1:enable\nvow_watf_q = <level>-<quantum> unit 256us\nvow_watf_add_entry = <level>-<Addr>\nvow_watf_del_entry = <Addr>\n"
                + param_1 + 0xe0;
      do {
        if ((pcVar10 != (char *)0x0) && (*(int *)(pcVar10 + 0xabc) != 0)) {
          iVar3 = HcGetBandByWdev(pcVar10);
          iVar13 = param_1 + iVar3 * 0x20;
          iVar12 = param_1 + (short)iVar3 * 0x20;
          if (iVar13 != -0xa37724) {
            if (*(char *)(iVar12 + 0xa37728) == '\x02') {
              puVar6 = (ushort *)(iVar12 + 0xa37726);
              if (local_2a[iVar3] != '\x01') {
                uVar1 = *puVar6;
                local_2a[iVar3] = '\x01';
                *puVar6 = uVar1 + 1;
                if (*(ushort *)(iVar13 + 0xa3772c) < uVar1) {
                  *puVar6 = 0;
                  uVar5 = HcGetBandByWdev(pcVar10);
                  MlmeEnqueue(param_1,0x2c,0,0,0,uVar5);
                  AsicSetSyncModeAndEnable(param_1,*(undefined2 *)(&DAT_00794c50 + param_1),0,1);
                  *(undefined1 *)(iVar12 + 0xa37728) = 0;
                }
              }
            }
            else {
              *(int *)(iVar13 + 0xa37734) = *(int *)(iVar13 + 0xa37734) + 1;
            }
          }
        }
        iVar2 = iVar2 + 1;
        pcVar10 = pcVar10 + 0x5834;
      } while (iVar2 < (int)(uint)(byte)"======== Badnode detector =============\nvow_bn_en = <0/1> 0:dieable, 1:enable\nvow_bn_mon_period = <period> ms\nvow_bn_fallback_th = <count>\nvow_bn_per_th = <TX PER>\n======== Airtime counter test =============\nvow_counter_test = <0/1> 0:dieable, 1:enable\nvow_counter_test_period = <period> ms\nvow_counter_test_band = <band>\nvow_counter_test_avgcnt = <average num> sec\nvow_counter_test_target = <wlanidx>\n======== DVT =============\nvow_dvt_en = <0/1> 0:dieable, 1:enable\nvow_monitor_sta = <STA num>\nvow_show_sta = <STA num>\nvow_monitor_bss = <BSS num>\nvow_monitor_mbss = <MBSS num>\nvow_show_mbss = <MBSS num>\nvow_avg_num = <average num> sec\n======== RED ===========\nvow_set_red_en = <0/1> 0:disable, 1:enable\nvow_set_red_show_sta = <STA num>\nvow_set_red_tar_delay = <tarDelay> us\n======== WATF ===========\nvow_watf_en = <0/1> 0:disable, 1:enable\nvow_watf_q = <level>-<quantum> unit 256us\nvow_watf_add_entry = <level>-<Addr>\nvow_watf_del_entry = <Addr>\n"
                                        [param_1 + 0xda]);
    }
  }
  DfsNonOccupancyCountDown(param_1);
  DfsOutBandCacCountUpdate(param_1);
  return;
}

