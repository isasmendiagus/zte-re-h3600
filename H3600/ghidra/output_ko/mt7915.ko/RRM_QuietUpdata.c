// module: mt7915.ko
// function: RRM_QuietUpdata @ 0x220500
// size: 184 bytes
//

void RRM_QuietUpdata(int param_1,undefined4 param_2,undefined4 param_3,undefined4 param_4)

{
  char *pcVar1;
  undefined4 extraout_r2;
  char cVar2;
  char *pcVar3;
  int iVar4;
  
  if ("======== Badnode detector =============\nvow_bn_en = <0/1> 0:dieable, 1:enable\nvow_bn_mon_period = <period> ms\nvow_bn_fallback_th = <count>\nvow_bn_per_th = <TX PER>\n======== Airtime counter test =============\nvow_counter_test = <0/1> 0:dieable, 1:enable\nvow_counter_test_period = <period> ms\nvow_counter_test_band = <band>\nvow_counter_test_avgcnt = <average num> sec\nvow_counter_test_target = <wlanidx>\n======== DVT =============\nvow_dvt_en = <0/1> 0:dieable, 1:enable\nvow_monitor_sta = <STA num>\nvow_show_sta = <STA num>\nvow_monitor_bss = <BSS num>\nvow_monitor_mbss = <MBSS num>\nvow_show_mbss = <MBSS num>\nvow_avg_num = <average num> sec\n======== RED ===========\nvow_set_red_en = <0/1> 0:disable, 1:enable\nvow_set_red_show_sta = <STA num>\nvow_set_red_tar_delay = <tarDelay> us\n======== WATF ===========\nvow_watf_en = <0/1> 0:disable, 1:enable\nvow_watf_q = <level>-<quantum> unit 256us\nvow_watf_add_entry = <level>-<Addr>\nvow_watf_del_entry = <Addr>\n"
      [param_1 + 0xda] == '\0') {
    return;
  }
  iVar4 = 0;
  pcVar3 = "%u-%02x:%02x:%02x:%02x:%02x:%02x" + param_1 + 0x1c;
  do {
    if ((*(int *)(pcVar3 + -0xb2c) != 0) &&
       ((*(uint *)(*(int *)(pcVar3 + -0xb2c) + 0x138) & 1) != 0)) {
      cVar2 = pcVar3[0x68];
      if (cVar2 == '\0') {
        if (pcVar3[-8] == '\0') {
          cVar2 = pcVar3[0x6b];
          pcVar1 = pcVar3;
          if (cVar2 == '\0') {
            pcVar3[-8] = '\x01';
            cVar2 = pcVar3[0x6a];
            pcVar1 = pcVar3 + 0x34;
          }
          RTMPSetTimer(pcVar1,cVar2,param_3,0,param_4);
          cVar2 = pcVar3[0x68];
          param_3 = extraout_r2;
          if (cVar2 != '\0') goto LAB_002205a8;
        }
        pcVar3[0x68] = pcVar3[0x69];
      }
      else {
LAB_002205a8:
        pcVar3[0x68] = cVar2 + -1;
      }
    }
    iVar4 = iVar4 + 1;
    pcVar3 = pcVar3 + 0x5834;
    if ((int)(uint)(byte)"======== Badnode detector =============\nvow_bn_en = <0/1> 0:dieable, 1:enable\nvow_bn_mon_period = <period> ms\nvow_bn_fallback_th = <count>\nvow_bn_per_th = <TX PER>\n======== Airtime counter test =============\nvow_counter_test = <0/1> 0:dieable, 1:enable\nvow_counter_test_period = <period> ms\nvow_counter_test_band = <band>\nvow_counter_test_avgcnt = <average num> sec\nvow_counter_test_target = <wlanidx>\n======== DVT =============\nvow_dvt_en = <0/1> 0:dieable, 1:enable\nvow_monitor_sta = <STA num>\nvow_show_sta = <STA num>\nvow_monitor_bss = <BSS num>\nvow_monitor_mbss = <MBSS num>\nvow_show_mbss = <MBSS num>\nvow_avg_num = <average num> sec\n======== RED ===========\nvow_set_red_en = <0/1> 0:disable, 1:enable\nvow_set_red_show_sta = <STA num>\nvow_set_red_tar_delay = <tarDelay> us\n======== WATF ===========\nvow_watf_en = <0/1> 0:disable, 1:enable\nvow_watf_q = <level>-<quantum> unit 256us\nvow_watf_add_entry = <level>-<Addr>\nvow_watf_del_entry = <Addr>\n"
                         [param_1 + 0xda] <= iVar4) {
      return;
    }
  } while( true );
}

