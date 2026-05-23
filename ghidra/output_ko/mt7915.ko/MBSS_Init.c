// module: mt7915.ko
// function: MBSS_Init @ 0x5217c
// size: 368 bytes
//

void MBSS_Init(int param_1,undefined4 param_2)

{
  int iVar1;
  int iVar2;
  uint uVar3;
  int *piVar4;
  char *pcVar5;
  uint uVar6;
  uint uVar7;
  bool bVar8;
  
  uVar7 = (uint)(byte)"======== Badnode detector =============\nvow_bn_en = <0/1> 0:dieable, 1:enable\nvow_bn_mon_period = <period> ms\nvow_bn_fallback_th = <count>\nvow_bn_per_th = <TX PER>\n======== Airtime counter test =============\nvow_counter_test = <0/1> 0:dieable, 1:enable\nvow_counter_test_period = <period> ms\nvow_counter_test_band = <band>\nvow_counter_test_avgcnt = <average num> sec\nvow_counter_test_target = <wlanidx>\n======== DVT =============\nvow_dvt_en = <0/1> 0:dieable, 1:enable\nvow_monitor_sta = <STA num>\nvow_show_sta = <STA num>\nvow_monitor_bss = <BSS num>\nvow_monitor_mbss = <MBSS num>\nvow_show_mbss = <MBSS num>\nvow_avg_num = <average num> sec\n======== RED ===========\nvow_set_red_en = <0/1> 0:disable, 1:enable\nvow_set_red_show_sta = <STA num>\nvow_set_red_tar_delay = <tarDelay> us\n======== WATF ===========\nvow_watf_en = <0/1> 0:disable, 1:enable\nvow_watf_q = <level>-<quantum> unit 256us\nvow_watf_add_entry = <level>-<Addr>\nvow_watf_del_entry = <Addr>\n"
                      [param_1 + 0xda];
  iVar1 = hc_get_chip_bcn_max_num(*(undefined4 *)(param_1 + 0xa797a0));
  bVar8 = SBORROW4(uVar7,0x1f);
  iVar2 = uVar7 - 0x1f;
  if (uVar7 < 0x20) {
    bVar8 = SBORROW4(uVar7,iVar1);
    iVar2 = uVar7 - iVar1;
  }
  if (iVar2 < 0 == bVar8) {
    uVar7 = hc_get_chip_bcn_max_num(*(undefined4 *)(param_1 + 0xa797a0));
  }
  MBSS_init_11v_param(param_1);
  if ((&DAT_0036db48)[param_1] != '\x01') {
    if (1 < (int)uVar7) {
      pcVar5 = "%s: Allocate memory fail!!!\n" + param_1 + 0xc;
      uVar3 = 1;
      do {
        pcVar5[0] = '\0';
        pcVar5[1] = '\0';
        pcVar5[2] = '\0';
        pcVar5[3] = '\0';
        pcVar5[0x954] = '\0';
        pcVar5[0x955] = '\0';
        pcVar5[0x956] = '\0';
        pcVar5[0x957] = '\0';
        uVar6 = uVar3 + 1;
        mbss_create_vif(param_1,param_2,uVar3);
        wdev_attr_update_mac(param_1,pcVar5);
        pcVar5 = pcVar5 + 0x5834;
        uVar3 = uVar6;
      } while (uVar6 != uVar7);
    }
    (&DAT_0036db48)[param_1] = 1;
    return;
  }
  if (*(char *)(param_1 + 0x79504c) == '\0') {
    return;
  }
  if (uVar7 != 0) {
    piVar4 = (int *)(
                    "======== Badnode detector =============\nvow_bn_en = <0/1> 0:dieable, 1:enable\nvow_bn_mon_period = <period> ms\nvow_bn_fallback_th = <count>\nvow_bn_per_th = <TX PER>\n======== Airtime counter test =============\nvow_counter_test = <0/1> 0:dieable, 1:enable\nvow_counter_test_period = <period> ms\nvow_counter_test_band = <band>\nvow_counter_test_avgcnt = <average num> sec\nvow_counter_test_target = <wlanidx>\n======== DVT =============\nvow_dvt_en = <0/1> 0:dieable, 1:enable\nvow_monitor_sta = <STA num>\nvow_show_sta = <STA num>\nvow_monitor_bss = <BSS num>\nvow_monitor_mbss = <MBSS num>\nvow_show_mbss = <MBSS num>\nvow_avg_num = <average num> sec\n======== RED ===========\nvow_set_red_en = <0/1> 0:disable, 1:enable\nvow_set_red_show_sta = <STA num>\nvow_set_red_tar_delay = <tarDelay> us\n======== WATF ===========\nvow_watf_en = <0/1> 0:disable, 1:enable\nvow_watf_q = <level>-<quantum> unit 256us\nvow_watf_add_entry = <level>-<Addr>\nvow_watf_del_entry = <Addr>\n"
                    + param_1 + 0xe0);
    uVar3 = 0;
    do {
      iVar2 = *piVar4;
      piVar4 = piVar4 + 0x160d;
      if (iVar2 != 0) {
        uVar3 = uVar3 + 1;
      }
    } while (piVar4 != (int *)(
                              "======== Badnode detector =============\nvow_bn_en = <0/1> 0:dieable, 1:enable\nvow_bn_mon_period = <period> ms\nvow_bn_fallback_th = <count>\nvow_bn_per_th = <TX PER>\n======== Airtime counter test =============\nvow_counter_test = <0/1> 0:dieable, 1:enable\nvow_counter_test_period = <period> ms\nvow_counter_test_band = <band>\nvow_counter_test_avgcnt = <average num> sec\nvow_counter_test_target = <wlanidx>\n======== DVT =============\nvow_dvt_en = <0/1> 0:dieable, 1:enable\nvow_monitor_sta = <STA num>\nvow_show_sta = <STA num>\nvow_monitor_bss = <BSS num>\nvow_monitor_mbss = <MBSS num>\nvow_show_mbss = <MBSS num>\nvow_avg_num = <average num> sec\n======== RED ===========\nvow_set_red_en = <0/1> 0:disable, 1:enable\nvow_set_red_show_sta = <STA num>\nvow_set_red_tar_delay = <tarDelay> us\n======== WATF ===========\nvow_watf_en = <0/1> 0:disable, 1:enable\nvow_watf_q = <level>-<quantum> unit 256us\nvow_watf_add_entry = <level>-<Addr>\nvow_watf_del_entry = <Addr>\n"
                              + uVar7 * 0x5834 + param_1 + 0xe0));
    if ((int)uVar3 < (int)uVar7) {
      do {
        if (0 < DebugLevel) {
          printk("Add MBSSID IF =%d\n",uVar3);
        }
        uVar6 = uVar3 + 1;
        mbss_create_vif(param_1,param_2,uVar3);
        uVar3 = uVar6;
      } while (uVar6 != uVar7);
      return;
    }
    return;
  }
  return;
}

