// module: mt7915.ko
// function: WscPBCSessionOverlapCheck @ 0x1eb594
// size: 620 bytes
//

void WscPBCSessionOverlapCheck(int param_1,int param_2)

{
  int iVar1;
  char *pcVar2;
  uint uVar3;
  int *piVar4;
  int iVar5;
  
  iVar1 = param_1 + 0x795000 + param_2;
  *(undefined1 *)(param_1 + 0x795a81) = 0;
  iVar5 = DebugLevel;
  if (1 < *(byte *)(iVar1 + 0xab4)) {
    pcVar2 = (char *)(param_1 + param_2 * 4 + 0x795afe);
    piVar4 = (int *)(param_1 + param_2 * 0x10 + 0x795a84);
    iVar5 = param_2 * 0x18 + param_1 + 0x795ab7;
    do {
      pcVar2 = pcVar2 + 1;
      if ((*pcVar2 != '\0') && ((12000 - jiffies) + *piVar4 < 0)) {
        __memzero(iVar5,6);
        *piVar4 = 0;
        *pcVar2 = '\0';
        *(char *)(iVar1 + 0xab4) = *(char *)(iVar1 + 0xab4) + -1;
      }
      piVar4 = piVar4 + 1;
      iVar5 = iVar5 + 6;
    } while (pcVar2 != (char *)(param_1 + param_2 * 4 + 0x795b02));
    iVar5 = DebugLevel;
    if (1 < *(byte *)(param_1 + 0x795000 + param_2 + 0xab4)) {
      uVar3 = 0;
      if ("======== Badnode detector =============\nvow_bn_en = <0/1> 0:dieable, 1:enable\nvow_bn_mon_period = <period> ms\nvow_bn_fallback_th = <count>\nvow_bn_per_th = <TX PER>\n======== Airtime counter test =============\nvow_counter_test = <0/1> 0:dieable, 1:enable\nvow_counter_test_period = <period> ms\nvow_counter_test_band = <band>\nvow_counter_test_avgcnt = <average num> sec\nvow_counter_test_target = <wlanidx>\n======== DVT =============\nvow_dvt_en = <0/1> 0:dieable, 1:enable\nvow_monitor_sta = <STA num>\nvow_show_sta = <STA num>\nvow_monitor_bss = <BSS num>\nvow_monitor_mbss = <MBSS num>\nvow_show_mbss = <MBSS num>\nvow_avg_num = <average num> sec\n======== RED ===========\nvow_set_red_en = <0/1> 0:disable, 1:enable\nvow_set_red_show_sta = <STA num>\nvow_set_red_tar_delay = <tarDelay> us\n======== WATF ===========\nvow_watf_en = <0/1> 0:disable, 1:enable\nvow_watf_q = <level>-<quantum> unit 256us\nvow_watf_add_entry = <level>-<Addr>\nvow_watf_del_entry = <Addr>\n"
          [param_1 + 0xda] != '\0') {
        uVar3 = 0;
        do {
          iVar5 = HcGetBandByWdev("======== Badnode detector =============\nvow_bn_en = <0/1> 0:dieable, 1:enable\nvow_bn_mon_period = <period> ms\nvow_bn_fallback_th = <count>\nvow_bn_per_th = <TX PER>\n======== Airtime counter test =============\nvow_counter_test = <0/1> 0:dieable, 1:enable\nvow_counter_test_period = <period> ms\nvow_counter_test_band = <band>\nvow_counter_test_avgcnt = <average num> sec\nvow_counter_test_target = <wlanidx>\n======== DVT =============\nvow_dvt_en = <0/1> 0:dieable, 1:enable\nvow_monitor_sta = <STA num>\nvow_show_sta = <STA num>\nvow_monitor_bss = <BSS num>\nvow_monitor_mbss = <MBSS num>\nvow_show_mbss = <MBSS num>\nvow_avg_num = <average num> sec\n======== RED ===========\nvow_set_red_en = <0/1> 0:disable, 1:enable\nvow_set_red_show_sta = <STA num>\nvow_set_red_tar_delay = <tarDelay> us\n======== WATF ===========\nvow_watf_en = <0/1> 0:disable, 1:enable\nvow_watf_q = <level>-<quantum> unit 256us\nvow_watf_add_entry = <level>-<Addr>\nvow_watf_del_entry = <Addr>\n"
                                  + param_1 + uVar3 * 0x5834 + 0xe0);
          if (((iVar5 == param_2) &&
              (iVar5 = param_1 + uVar3 * 0x5834,
              *(int *)(
                      "4/home/ws/zx279128s/packages/function/wlan/mtk/drivers/MT7915_V7.0.1.0/mt_wifi_ap/../mt_wifi/embedded/fsm/ap_mgmt_cntl.c:%d assert pAdfailed\n"
                      + iVar5 + 0x2b) != 0)) &&
             ("PIN authentication or communication error occurs!!\nRegistrar does NOT accept the same PIN again!(PIN:%08u)\n"
              [iVar5 + 0x5c] == '\x01')) {
            if (2 < DebugLevel) {
              printk("%s(): found pAd->ApCfg.MBSSID[%d] WPS on\n","WscPBCSessionOverlapCheck",uVar3)
              ;
            }
            if (uVar3 < (byte)"======== Badnode detector =============\nvow_bn_en = <0/1> 0:dieable, 1:enable\nvow_bn_mon_period = <period> ms\nvow_bn_fallback_th = <count>\nvow_bn_per_th = <TX PER>\n======== Airtime counter test =============\nvow_counter_test = <0/1> 0:dieable, 1:enable\nvow_counter_test_period = <period> ms\nvow_counter_test_band = <band>\nvow_counter_test_avgcnt = <average num> sec\nvow_counter_test_target = <wlanidx>\n======== DVT =============\nvow_dvt_en = <0/1> 0:dieable, 1:enable\nvow_monitor_sta = <STA num>\nvow_show_sta = <STA num>\nvow_monitor_bss = <BSS num>\nvow_monitor_mbss = <MBSS num>\nvow_show_mbss = <MBSS num>\nvow_avg_num = <average num> sec\n======== RED ===========\nvow_set_red_en = <0/1> 0:disable, 1:enable\nvow_set_red_show_sta = <STA num>\nvow_set_red_tar_delay = <tarDelay> us\n======== WATF ===========\nvow_watf_en = <0/1> 0:disable, 1:enable\nvow_watf_q = <level>-<quantum> unit 256us\nvow_watf_add_entry = <level>-<Addr>\nvow_watf_del_entry = <Addr>\n"
                              [param_1 + 0xda]) {
              if (0 < DebugLevel) {
                printk("%s(): pAd->ApCfg.MBSSID[%d] WPS on, PBC Overlap detected\n",
                       "WscPBCSessionOverlapCheck",uVar3);
              }
              iVar5 = DebugLevel;
              *(undefined1 *)(param_1 + 0x795a81) = 1;
              goto LAB_001eb730;
            }
            break;
          }
          uVar3 = uVar3 + 1 & 0xff;
        } while (uVar3 < (byte)"======== Badnode detector =============\nvow_bn_en = <0/1> 0:dieable, 1:enable\nvow_bn_mon_period = <period> ms\nvow_bn_fallback_th = <count>\nvow_bn_per_th = <TX PER>\n======== Airtime counter test =============\nvow_counter_test = <0/1> 0:dieable, 1:enable\nvow_counter_test_period = <period> ms\nvow_counter_test_band = <band>\nvow_counter_test_avgcnt = <average num> sec\nvow_counter_test_target = <wlanidx>\n======== DVT =============\nvow_dvt_en = <0/1> 0:dieable, 1:enable\nvow_monitor_sta = <STA num>\nvow_show_sta = <STA num>\nvow_monitor_bss = <BSS num>\nvow_monitor_mbss = <MBSS num>\nvow_show_mbss = <MBSS num>\nvow_avg_num = <average num> sec\n======== RED ===========\nvow_set_red_en = <0/1> 0:disable, 1:enable\nvow_set_red_show_sta = <STA num>\nvow_set_red_tar_delay = <tarDelay> us\n======== WATF ===========\nvow_watf_en = <0/1> 0:disable, 1:enable\nvow_watf_q = <level>-<quantum> unit 256us\nvow_watf_add_entry = <level>-<Addr>\nvow_watf_del_entry = <Addr>\n"
                               [param_1 + 0xda]);
      }
      if (0 < DebugLevel) {
        printk("%s(): pAd->ApCfg.MBSSID[%d] WPS off, PBC Overlap is invalid\n",
               "WscPBCSessionOverlapCheck",uVar3);
      }
      iVar5 = DebugLevel;
      *(undefined1 *)(param_1 + 0x795a81) = 0;
    }
  }
LAB_001eb730:
  if (2 < iVar5) {
    printk("WscPBCSessionOverlapCheck : WscPBCStaProbeCount[%d] = %d\n",param_2,
           *(undefined1 *)(param_1 + param_2 + 0x795ab4));
    return;
  }
  return;
}

