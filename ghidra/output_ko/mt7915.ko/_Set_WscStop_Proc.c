// module: mt7915.ko
// function: _Set_WscStop_Proc @ 0x3bd38
// size: 1028 bytes
//

undefined4 _Set_WscStop_Proc(int *param_1,undefined4 param_2,int param_3,uint param_4)

{
  undefined1 uVar1;
  int iVar2;
  int *piVar3;
  
  if (param_3 == 1) {
    param_4 = param_4 & 0xff;
    if (param_1[0x29f46d] == 1) goto LAB_0003bf00;
    piVar3 = param_1 + param_4 * 0x160d + 0xae14b;
    if (DebugLevel < 3) {
      uVar1 = (undefined1)param_1[param_4 * 0x160d + 0xae14d];
    }
    else {
      printk("IF(ra%d) Set_WscStop_Proc:: This command is from ra interface now.\n",param_4);
      uVar1 = (undefined1)param_1[param_4 * 0x160d + 0xae14d];
    }
    WscBuildBeaconIE(param_1,uVar1,0,0,0,param_4,0,0,0);
    WscBuildProbeRespIE(param_1,3,uVar1,0,0,0,param_4,0,0,0);
    UpdateBeaconHandler(param_1,(char *)((int)param_1 +
                                        (int)(
                                             "======== Badnode detector =============\nvow_bn_en = <0/1> 0:dieable, 1:enable\nvow_bn_mon_period = <period> ms\nvow_bn_fallback_th = <count>\nvow_bn_per_th = <TX PER>\n======== Airtime counter test =============\nvow_counter_test = <0/1> 0:dieable, 1:enable\nvow_counter_test_period = <period> ms\nvow_counter_test_band = <band>\nvow_counter_test_avgcnt = <average num> sec\nvow_counter_test_target = <wlanidx>\n======== DVT =============\nvow_dvt_en = <0/1> 0:dieable, 1:enable\nvow_monitor_sta = <STA num>\nvow_show_sta = <STA num>\nvow_monitor_bss = <BSS num>\nvow_monitor_mbss = <MBSS num>\nvow_show_mbss = <MBSS num>\nvow_avg_num = <average num> sec\n======== RED ===========\nvow_set_red_en = <0/1> 0:disable, 1:enable\nvow_set_red_show_sta = <STA num>\nvow_set_red_tar_delay = <tarDelay> us\n======== WATF ===========\nvow_watf_en = <0/1> 0:disable, 1:enable\nvow_watf_q = <level>-<quantum> unit 256us\nvow_watf_add_entry = <level>-<Addr>\nvow_watf_del_entry = <Addr>\n"
                                             + param_4 * 0x5834 + 0xe0)),2);
  }
  else {
    param_4 = (uint)*(byte *)(*param_1 + 0x3c);
    if (param_3 == 0) {
      if (*(int *)(*param_1 + 0x38) != 0x400) {
        piVar3 = param_1 + param_4 * 0x160d + 0xae14b;
        if (2 < DebugLevel) goto LAB_0003c08c;
        iVar2 = param_1[param_4 * 0x160d + 0xae14d];
        WscBuildBeaconIE(param_1,(char)iVar2,0,0,0,param_4,0,0,0);
        WscBuildProbeRespIE(param_1,3,(char)iVar2,0,0,0,param_4,0,0,0);
        UpdateBeaconHandler(param_1,(char *)((int)param_1 +
                                            (int)(
                                                 "======== Badnode detector =============\nvow_bn_en = <0/1> 0:dieable, 1:enable\nvow_bn_mon_period = <period> ms\nvow_bn_fallback_th = <count>\nvow_bn_per_th = <TX PER>\n======== Airtime counter test =============\nvow_counter_test = <0/1> 0:dieable, 1:enable\nvow_counter_test_period = <period> ms\nvow_counter_test_band = <band>\nvow_counter_test_avgcnt = <average num> sec\nvow_counter_test_target = <wlanidx>\n======== DVT =============\nvow_dvt_en = <0/1> 0:dieable, 1:enable\nvow_monitor_sta = <STA num>\nvow_show_sta = <STA num>\nvow_monitor_bss = <BSS num>\nvow_monitor_mbss = <MBSS num>\nvow_show_mbss = <MBSS num>\nvow_avg_num = <average num> sec\n======== RED ===========\nvow_set_red_en = <0/1> 0:disable, 1:enable\nvow_set_red_show_sta = <STA num>\nvow_set_red_tar_delay = <tarDelay> us\n======== WATF ===========\nvow_watf_en = <0/1> 0:disable, 1:enable\nvow_watf_q = <level>-<quantum> unit 256us\nvow_watf_add_entry = <level>-<Addr>\nvow_watf_del_entry = <Addr>\n"
                                                 + param_4 * 0x5834 + 0xe0)),2);
LAB_0003be08:
        _WscStop(param_1,0,piVar3,0);
        goto LAB_0003bedc;
      }
LAB_0003bf00:
      piVar3 = param_1 + param_4 * 0x84dec + 0xdbb8f;
      if (2 < DebugLevel) {
        printk("IF(apcli%d) Set_WscStop_Proc:: This command is from apcli interface now.\n",param_4)
        ;
      }
      _WscStop(param_1,1,piVar3,0);
      param_1[param_4 * 0x84dec + 0xdbb8f] = 0;
      goto LAB_0003bedc;
    }
    piVar3 = param_1 + param_4 * 0x160d + 0xae14b;
    if (DebugLevel < 3) {
      iVar2 = param_1[param_4 * 0x160d + 0xae14d];
      WscBuildBeaconIE(param_1,(char)iVar2,0,0,0,param_4,0,0,0);
      WscBuildProbeRespIE(param_1,3,(char)iVar2,0,0,0,param_4,0,0,0);
      UpdateBeaconHandler(param_1,(char *)((int)param_1 +
                                          (int)(
                                               "======== Badnode detector =============\nvow_bn_en = <0/1> 0:dieable, 1:enable\nvow_bn_mon_period = <period> ms\nvow_bn_fallback_th = <count>\nvow_bn_per_th = <TX PER>\n======== Airtime counter test =============\nvow_counter_test = <0/1> 0:dieable, 1:enable\nvow_counter_test_period = <period> ms\nvow_counter_test_band = <band>\nvow_counter_test_avgcnt = <average num> sec\nvow_counter_test_target = <wlanidx>\n======== DVT =============\nvow_dvt_en = <0/1> 0:dieable, 1:enable\nvow_monitor_sta = <STA num>\nvow_show_sta = <STA num>\nvow_monitor_bss = <BSS num>\nvow_monitor_mbss = <MBSS num>\nvow_show_mbss = <MBSS num>\nvow_avg_num = <average num> sec\n======== RED ===========\nvow_set_red_en = <0/1> 0:disable, 1:enable\nvow_set_red_show_sta = <STA num>\nvow_set_red_tar_delay = <tarDelay> us\n======== WATF ===========\nvow_watf_en = <0/1> 0:disable, 1:enable\nvow_watf_q = <level>-<quantum> unit 256us\nvow_watf_add_entry = <level>-<Addr>\nvow_watf_del_entry = <Addr>\n"
                                               + param_4 * 0x5834 + 0xe0)),2);
    }
    else {
LAB_0003c08c:
      printk("IF(ra%d) Set_WscStop_Proc:: This command is from ra interface now.\n",param_4);
      iVar2 = piVar3[2];
      WscBuildBeaconIE(param_1,(char)iVar2,0,0,0,param_4,0,0,0);
      WscBuildProbeRespIE(param_1,3,(char)iVar2,0,0,0,param_4,0,0,0);
      UpdateBeaconHandler(param_1,param_1 + param_4 * 0x160d + 0xadc92,2);
      if (param_3 == 0) goto LAB_0003be08;
    }
  }
  _WscStop(param_1,0,piVar3,1);
LAB_0003bedc:
  iVar2 = DebugLevel;
  *(undefined1 *)(piVar3 + 0xa79) = 0;
  if (2 < iVar2) {
    printk("<===== Set_WscStop_Proc");
  }
  return 1;
}

