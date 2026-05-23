// module: mt7915.ko
// function: Wsc2MinsTimeOutAction @ 0x1e3900
// size: 1228 bytes
//

void Wsc2MinsTimeOutAction(undefined4 param_1,uint *param_2)

{
  undefined4 uVar1;
  int iVar2;
  char *pcVar3;
  uint uVar4;
  uint uVar5;
  undefined *puVar6;
  uint uVar7;
  undefined *puVar8;
  char *pcVar9;
  undefined1 auStack_29 [5];
  
  if (DebugLevel < 3) {
    if (param_2 == (uint *)0x0) {
      return;
    }
  }
  else {
    printk("-----> Wsc2MinsTimeOutAction\n");
    if (param_2 == (uint *)0x0) goto joined_r0x001e3a58;
  }
  uVar5 = param_2[0xa7b];
  if (uVar5 == 0) {
    printk(&_LC68,0x1231);
    dump_stack();
  }
  uVar7 = param_2[0xa7a];
  if (uVar7 == 0) {
    if (DebugLevel < 3) {
      return;
    }
    printk("pAd is NULL!\n");
  }
  else {
    iVar2 = DebugLevel;
    if (param_2[0xa39] != 0) {
      if (0 < DebugLevel) {
        printk("CON_WPS: Reset the status to default.\n");
      }
      iVar2 = DebugLevel;
      param_2[0xa39] = 0;
    }
    if (*(char *)(uVar7 + 0x286285) == '\x01') {
      if (*(int *)(uVar5 + 0x14) == 2) {
        puVar6 = &DAT_0036db58 + uVar7 + ((byte)param_2[0x715] & 0xf) * 0x2137b0;
        puVar8 = (undefined *)0x2;
      }
      else {
        puVar6 = (undefined *)0x0;
        puVar8 = puVar6;
      }
    }
    else if (*(char *)(uVar7 + 0x286285) == '\0') {
      puVar6 = &DAT_0036db58 + uVar7;
      puVar8 = (undefined *)0x2;
    }
    else {
      puVar6 = (undefined *)0x0;
      puVar8 = (undefined *)0xff;
    }
    if (2 < iVar2) {
      pcVar3 = "TRUE, reset WscState to WSC_STATE_OFF";
      if (*(char *)((int)param_2 + 0x1c5b) == '\0') {
        pcVar3 = "FALSE";
      }
      printk("Wsc2MinsTimerRunning is %s\n",pcVar3);
    }
    *(undefined1 *)(param_2 + 0xa67) = 1;
    if (*(char *)((int)param_2 + 0x1c5b) != '\0') {
      *(undefined1 *)(param_2 + 0xa79) = 0;
      *(undefined1 *)(param_2 + 0x9f2) = 0;
      RTMPCancelTimer(param_2 + 0x9f3,auStack_29);
      if (puVar8 == (undefined *)0x0) {
        uVar5 = param_2[2];
        uVar4 = (byte)param_2[0x715] & 0xf;
        if (uVar4 < (byte)"======== Badnode detector =============\nvow_bn_en = <0/1> 0:dieable, 1:enable\nvow_bn_mon_period = <period> ms\nvow_bn_fallback_th = <count>\nvow_bn_per_th = <TX PER>\n======== Airtime counter test =============\nvow_counter_test = <0/1> 0:dieable, 1:enable\nvow_counter_test_period = <period> ms\nvow_counter_test_band = <band>\nvow_counter_test_avgcnt = <average num> sec\nvow_counter_test_target = <wlanidx>\n======== DVT =============\nvow_dvt_en = <0/1> 0:dieable, 1:enable\nvow_monitor_sta = <STA num>\nvow_show_sta = <STA num>\nvow_monitor_bss = <BSS num>\nvow_monitor_mbss = <MBSS num>\nvow_show_mbss = <MBSS num>\nvow_avg_num = <average num> sec\n======== RED ===========\nvow_set_red_en = <0/1> 0:disable, 1:enable\nvow_set_red_show_sta = <STA num>\nvow_set_red_tar_delay = <tarDelay> us\n======== WATF ===========\nvow_watf_en = <0/1> 0:disable, 1:enable\nvow_watf_q = <level>-<quantum> unit 256us\nvow_watf_add_entry = <level>-<Addr>\nvow_watf_del_entry = <Addr>\n"
                          [uVar7 + 0xda]) {
          pcVar9 = "======== Badnode detector =============\nvow_bn_en = <0/1> 0:dieable, 1:enable\nvow_bn_mon_period = <period> ms\nvow_bn_fallback_th = <count>\nvow_bn_per_th = <TX PER>\n======== Airtime counter test =============\nvow_counter_test = <0/1> 0:dieable, 1:enable\nvow_counter_test_period = <period> ms\nvow_counter_test_band = <band>\nvow_counter_test_avgcnt = <average num> sec\nvow_counter_test_target = <wlanidx>\n======== DVT =============\nvow_dvt_en = <0/1> 0:dieable, 1:enable\nvow_monitor_sta = <STA num>\nvow_show_sta = <STA num>\nvow_monitor_bss = <BSS num>\nvow_monitor_mbss = <MBSS num>\nvow_show_mbss = <MBSS num>\nvow_avg_num = <average num> sec\n======== RED ===========\nvow_set_red_en = <0/1> 0:disable, 1:enable\nvow_set_red_show_sta = <STA num>\nvow_set_red_tar_delay = <tarDelay> us\n======== WATF ===========\nvow_watf_en = <0/1> 0:disable, 1:enable\nvow_watf_q = <level>-<quantum> unit 256us\nvow_watf_add_entry = <level>-<Addr>\nvow_watf_del_entry = <Addr>\n"
                   + uVar4 * 0x5834 + uVar7 + 0xe0;
          pcVar3 = pcVar9;
          WscBuildBeaconIE(param_2[0xa7a],(char)uVar5,0,0,0,uVar4,0,0,0);
          WscBuildProbeRespIE(param_2[0xa7a],3,(char)uVar5,0,0,0,(char)param_2[0x715],0,0,0,pcVar9,
                              pcVar3);
          UpdateBeaconHandler(param_2[0xa7a],pcVar9,2);
        }
        if ((*param_2 & 2) == 0) {
          param_2[4] = 0;
        }
      }
      *(undefined1 *)((int)param_2 + 0x1c53) = 0;
      *(undefined1 *)((int)param_2 + 0x1c5b) = 0;
      param_2[9] = 0;
      param_2[3] = 1;
      if ((char)param_2[0xa0f] != '\0') {
        *(undefined1 *)(param_2 + 0xa0f) = 0;
        RTMPCancelTimer(param_2 + 0xa10,auStack_29);
      }
      if ((char)param_2[0xa01] != '\0') {
        *(undefined1 *)(param_2 + 0xa01) = 0;
        RTMPCancelTimer(param_2 + 0xa02,auStack_29);
      }
      if (puVar8 == (undefined *)0x2) {
        puVar6[0x213172] = 0;
        RTMPZeroMemory(puVar6 + 0x4140,0x20);
        puVar6[0x4160] = (&DAT_0057ff7e)[uVar7];
        RTMPMoveMemory(puVar6 + 0x4140,uVar7 + 0x57ff5e,(&DAT_0057ff7e)[uVar7]);
        if (((*(uint *)(puVar6 + 0x212464) & 1) == 0) && (*param_2 != 1)) {
          AsicDisableSync(uVar7,0);
          WscBuildBeaconIE(uVar7,(char)param_2[2],0,0,0,0,0,0,2);
          WscBuildProbeRespIE(uVar7,2,(char)param_2[2],0,0,0,0,0,0,2);
          UpdateBeaconHandler(uVar7,&DAT_0036db58 + uVar7,1);
          AsicEnableIbssSync(uVar7,*(undefined2 *)(&DAT_00794c50 + uVar7),0,2);
        }
        else {
          FUN_001e0304(uVar7,puVar6);
        }
        *param_2 = 0;
        param_2[4] = 0;
      }
    }
    if ((((puVar6 == (undefined *)0x0) || ((*(uint *)(puVar6 + 0x212464) & 0x80) == 0)) ||
        (param_2[4] != 0)) || (param_2[3] != 0x22)) {
      param_2[4] = 0;
      param_2[3] = 2;
      *(undefined1 *)(param_2 + 0xa4b) = 0;
      uVar1 = HcGetBandByWdev(param_2[0xa7b]);
      RTMPSetLED(uVar7,0xc,uVar1);
      if (DebugLevel < 3) {
        return;
      }
      printk("WscConnectTimeout --> Fail to connect\n");
    }
    else {
      if (DebugLevel < 3) {
        return;
      }
      printk("WscConnectTimeout --> Connection OK\n");
    }
  }
joined_r0x001e3a58:
  if (2 < DebugLevel) {
    printk("<----- Wsc2MinsTimeOutAction\n");
  }
  return;
}

