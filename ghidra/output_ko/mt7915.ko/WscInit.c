// module: mt7915.ko
// function: WscInit @ 0x1e5b9c
// size: 632 bytes
//

void WscInit(int param_1,int param_2,uint param_3)

{
  char cVar1;
  byte bVar2;
  bool bVar3;
  undefined4 uVar4;
  char *pcVar5;
  uint uVar6;
  
  if (*(char *)(param_1 + 0x286285) == '\x01') {
    uVar6 = param_3 & 0xf;
    if (param_2 == 0) {
      pcVar5 = "======== Badnode detector =============\nvow_bn_en = <0/1> 0:dieable, 1:enable\nvow_bn_mon_period = <period> ms\nvow_bn_fallback_th = <count>\nvow_bn_per_th = <TX PER>\n======== Airtime counter test =============\nvow_counter_test = <0/1> 0:dieable, 1:enable\nvow_counter_test_period = <period> ms\nvow_counter_test_band = <band>\nvow_counter_test_avgcnt = <average num> sec\nvow_counter_test_target = <wlanidx>\n======== DVT =============\nvow_dvt_en = <0/1> 0:dieable, 1:enable\nvow_monitor_sta = <STA num>\nvow_show_sta = <STA num>\nvow_monitor_bss = <BSS num>\nvow_monitor_mbss = <MBSS num>\nvow_show_mbss = <MBSS num>\nvow_avg_num = <average num> sec\n======== RED ===========\nvow_set_red_en = <0/1> 0:disable, 1:enable\nvow_set_red_show_sta = <STA num>\nvow_set_red_tar_delay = <tarDelay> us\n======== WATF ===========\nvow_watf_en = <0/1> 0:disable, 1:enable\nvow_watf_q = <level>-<quantum> unit 256us\nvow_watf_add_entry = <level>-<Addr>\nvow_watf_del_entry = <Addr>\n"
               + uVar6 * 0x5834 + param_1 + 0xe0;
    }
    else if (uVar6 < 2) {
      pcVar5 = &DAT_0036db58 + param_1 + uVar6 * 0x2137b0;
    }
    else {
      pcVar5 = (char *)0x0;
    }
    bVar3 = false;
  }
  else {
    if (*(char *)(param_1 + 0x286285) != '\0') {
      return;
    }
    if (1 < (param_3 & 0xf)) {
      return;
    }
    bVar3 = true;
    pcVar5 = &DAT_0036db58 + param_1 + (param_3 & 0xf) * 0x2137b0;
  }
  uVar6 = param_3 & 0xf;
  if (pcVar5 != (char *)0x0) {
    if (*(int *)(pcVar5 + 0x1300) == 0) {
      if (pcVar5[0x12fd] == '\0') {
        uVar4 = GenerateWpsPinCode(param_1,param_2,param_3);
        pcVar5[0x1304] = '\b';
        *(undefined4 *)(pcVar5 + 0x1300) = uVar4;
      }
      else {
        pcVar5[0x1304] = '\x04';
        uVar4 = WscRandomGen4digitPinCode(param_1);
        *(undefined4 *)(pcVar5 + 0x1300) = uVar4;
      }
    }
    pcVar5[0x1354] = '\x10';
    pcVar5[0x1355] = ' ';
    pcVar5[0x3edc] = '\0';
    pcVar5[0x3edd] = '\0';
    pcVar5[0x12f0] = '\x01';
    pcVar5[0x12f1] = '\0';
    pcVar5[0x12f2] = '\0';
    pcVar5[0x12f3] = '\0';
    if (bVar3) {
      if (pcVar5[0x3e14] != '\0') goto LAB_001e5dfc;
      if (pcVar5[0x3e15] != '\0') {
        return;
      }
    }
    else if ((*(int *)(pcVar5 + 0x12e4) == 0) ||
            ((pcVar5[0x3e14] == '\0' && (pcVar5[0x3e15] != '\0')))) {
      if (param_2 == 0) {
        pcVar5[0xee0] = '\0';
        pcVar5[0xee1] = '\0';
        pcVar5[0x10e2] = '\0';
        pcVar5[0x10e3] = '\0';
        return;
      }
LAB_001e5dfc:
      WscInitRegistrarPair(param_1,pcVar5 + 0x12e4,uVar6);
      return;
    }
    WscInitRegistrarPair(param_1,pcVar5 + 0x12e4,uVar6);
    if (!bVar3 && param_2 == 0) {
      cVar1 = pcVar5[0x12ec];
      bVar2 = pcVar5[0x2f38];
      WscBuildBeaconIE(param_1,cVar1,0,0,0,uVar6,0,0,0);
      WscBuildProbeRespIE(param_1,3,cVar1,0,0,0,param_3,0,0,0);
      UpdateBeaconHandler(param_1,"======== Badnode detector =============\nvow_bn_en = <0/1> 0:dieable, 1:enable\nvow_bn_mon_period = <period> ms\nvow_bn_fallback_th = <count>\nvow_bn_per_th = <TX PER>\n======== Airtime counter test =============\nvow_counter_test = <0/1> 0:dieable, 1:enable\nvow_counter_test_period = <period> ms\nvow_counter_test_band = <band>\nvow_counter_test_avgcnt = <average num> sec\nvow_counter_test_target = <wlanidx>\n======== DVT =============\nvow_dvt_en = <0/1> 0:dieable, 1:enable\nvow_monitor_sta = <STA num>\nvow_show_sta = <STA num>\nvow_monitor_bss = <BSS num>\nvow_monitor_mbss = <MBSS num>\nvow_show_mbss = <MBSS num>\nvow_avg_num = <average num> sec\n======== RED ===========\nvow_set_red_en = <0/1> 0:disable, 1:enable\nvow_set_red_show_sta = <STA num>\nvow_set_red_tar_delay = <tarDelay> us\n======== WATF ===========\nvow_watf_en = <0/1> 0:disable, 1:enable\nvow_watf_q = <level>-<quantum> unit 256us\nvow_watf_add_entry = <level>-<Addr>\nvow_watf_del_entry = <Addr>\n"
                                  + (bVar2 & 0xf) * 0x5834 + param_1 + 0xe0,2);
      return;
    }
  }
  return;
}

