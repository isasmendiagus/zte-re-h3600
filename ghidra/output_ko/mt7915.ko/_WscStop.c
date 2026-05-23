// module: mt7915.ko
// function: _WscStop @ 0x1e563c
// size: 1024 bytes
//

void _WscStop(int param_1,int param_2,int param_3,int param_4)

{
  char cVar1;
  undefined4 uVar2;
  int iVar3;
  uint uVar4;
  int iVar5;
  undefined1 auStack_29 [5];
  
  if (*(char *)(param_1 + 0x286285) == '\x01') {
    iVar5 = 0;
    cVar1 = *(char *)(param_3 + 0x278d);
  }
  else {
    if (*(char *)(param_1 + 0x286285) == '\0') {
      iVar5 = 2;
      *(undefined1 *)(param_3 + 0x2788) = 0;
    }
    else {
      iVar5 = 0xff;
    }
    cVar1 = *(char *)(param_3 + 0x278d);
  }
  if (cVar1 == '\x01') {
    *(undefined1 *)(param_3 + 0x278d) = 0;
    RTMPCancelTimer(param_3 + 0x2794,auStack_29);
    *(undefined1 *)(param_3 + 0x278e) = 0;
  }
  if (*(char *)(param_3 + 0x2c44) != '\0') {
    *(undefined1 *)(param_3 + 0x2c44) = 0;
    RTMPCancelTimer(param_3 + 0x2c10,auStack_29);
  }
  *(undefined1 *)(param_3 + 0x278c) = 0;
  *(undefined4 *)(param_3 + 0x2c48) = 0;
  *(undefined4 *)(param_3 + 0x2790) = 0;
  if (*(char *)(param_3 + 0x1c5b) != '\0') {
    *(undefined1 *)(param_3 + 0x1c5b) = 0;
    RTMPCancelTimer(param_3 + 0x1c5c,auStack_29);
  }
  if (*(char *)(param_3 + 0x2b68) != '\0') {
    *(undefined1 *)(param_3 + 0x2b68) = 0;
    RTMPCancelTimer(param_3 + 0x2b34,auStack_29);
  }
  RTMPCancelTimer(param_3 + 0x27cc,auStack_29);
  *(undefined1 *)(param_3 + 0x27c8) = 0;
  if ((((*(byte *)(param_3 + 0x1c54) & 0xf) <
        (byte)"======== Badnode detector =============\nvow_bn_en = <0/1> 0:dieable, 1:enable\nvow_bn_mon_period = <period> ms\nvow_bn_fallback_th = <count>\nvow_bn_per_th = <TX PER>\n======== Airtime counter test =============\nvow_counter_test = <0/1> 0:dieable, 1:enable\nvow_counter_test_period = <period> ms\nvow_counter_test_band = <band>\nvow_counter_test_avgcnt = <average num> sec\nvow_counter_test_target = <wlanidx>\n======== DVT =============\nvow_dvt_en = <0/1> 0:dieable, 1:enable\nvow_monitor_sta = <STA num>\nvow_show_sta = <STA num>\nvow_monitor_bss = <BSS num>\nvow_monitor_mbss = <MBSS num>\nvow_show_mbss = <MBSS num>\nvow_avg_num = <average num> sec\n======== RED ===========\nvow_set_red_en = <0/1> 0:disable, 1:enable\nvow_set_red_show_sta = <STA num>\nvow_set_red_tar_delay = <tarDelay> us\n======== WATF ===========\nvow_watf_en = <0/1> 0:disable, 1:enable\nvow_watf_q = <level>-<quantum> unit 256us\nvow_watf_add_entry = <level>-<Addr>\nvow_watf_del_entry = <Addr>\n"
              [param_1 + 0xda]) && (iVar3 = MacTableLookup(param_1,param_3 + 0x1c55), iVar5 == 0))
     && (param_2 == 0 && iVar3 != 0)) {
    *(undefined1 *)(iVar3 + 0xd24) = 0;
  }
  __memzero(param_3 + 0x1c55,6);
  *(undefined4 *)(param_3 + 0x24) = 0;
  if (*(uint *)(param_3 + 0xc) != 0x101 && (*(uint *)(param_3 + 0xc) & 0xffffffdf) != 2) {
    *(undefined4 *)(param_3 + 0xc) = 0;
  }
  *(undefined4 *)(param_3 + 0x10) = 0;
  *(undefined1 *)(param_3 + 0x1c52) = 0;
  *(undefined1 *)(param_3 + 0x1c50) = 1;
  *(undefined1 *)(param_3 + 0x27c9) = 0;
  *(undefined1 *)(param_3 + 0x29e4) = 0;
  if (*(char *)(param_3 + 0x283c) != '\0') {
    *(undefined1 *)(param_3 + 0x283c) = 0;
    RTMPCancelTimer(param_3 + 0x2840,auStack_29);
  }
  if (*(char *)(param_3 + 0x2804) != '\0') {
    *(undefined1 *)(param_3 + 0x2804) = 0;
    RTMPCancelTimer(param_3 + 0x2808,auStack_29);
  }
  if ((param_2 == 0) ||
     (uVar4 = *(byte *)(param_3 + 0x1c54) & 0xf,
     (*(byte *)(param_3 + 0x1c54) & 0xf) != 0 && uVar4 != 1)) {
    cVar1 = *(char *)(param_3 + 0x28ac);
  }
  else {
    *(undefined4 *)(&DAT_00580ed8 + param_1 + uVar4 * 0x2137b0) = 0;
    cVar1 = *(char *)(param_3 + 0x28ac);
    *(undefined4 *)(param_3 + 0x28e4) = 0;
  }
  if (cVar1 != '\0') {
    *(undefined1 *)(param_3 + 0x28ac) = 0;
    RTMPCancelTimer(param_3 + 0x28b0,auStack_29);
  }
  if (iVar5 == 2) {
    (&DAT_00371cb8)[param_1] = (&DAT_00371c91)[param_1];
    __memzero((void *)(param_1 + 0x371c98),0x20);
    memmove((void *)(param_1 + 0x371c98),
            s_patch_common_sys_patch_common_mc_00371c50 + param_1 + 0x21,
            (uint)(byte)(&DAT_00371c91)[param_1]);
    *(undefined2 *)(param_3 + 0x176) = 0;
  }
  if (*(char *)(param_3 + 0x292d) != '\0') {
    if (param_2 == 0 || param_4 == 0) {
      *(undefined1 *)(param_3 + 0x292d) = 0;
      RTMPCancelTimer(param_3 + 0x2930,auStack_29);
    }
    else if (0 < DebugLevel) {
      printk("not cancel wsc LED Timer");
    }
  }
  if (*(char *)(param_3 + 0x2964) != '\0') {
    *(undefined1 *)(param_3 + 0x2964) = 0;
    RTMPCancelTimer(param_3 + 0x2968,auStack_29);
  }
  *(undefined1 *)(param_3 + 0x299c) = 0;
  uVar4 = *(byte *)(param_3 + 0x1c54) & 0xf;
  if (*(int *)(param_1 + 0xa7d1b4) != 1) {
    uVar4 = HcGetBandByWdev("======== Badnode detector =============\nvow_bn_en = <0/1> 0:dieable, 1:enable\nvow_bn_mon_period = <period> ms\nvow_bn_fallback_th = <count>\nvow_bn_per_th = <TX PER>\n======== Airtime counter test =============\nvow_counter_test = <0/1> 0:dieable, 1:enable\nvow_counter_test_period = <period> ms\nvow_counter_test_band = <band>\nvow_counter_test_avgcnt = <average num> sec\nvow_counter_test_target = <wlanidx>\n======== DVT =============\nvow_dvt_en = <0/1> 0:dieable, 1:enable\nvow_monitor_sta = <STA num>\nvow_show_sta = <STA num>\nvow_monitor_bss = <BSS num>\nvow_monitor_mbss = <MBSS num>\nvow_show_mbss = <MBSS num>\nvow_avg_num = <average num> sec\n======== RED ===========\nvow_set_red_en = <0/1> 0:disable, 1:enable\nvow_set_red_show_sta = <STA num>\nvow_set_red_tar_delay = <tarDelay> us\n======== WATF ===========\nvow_watf_en = <0/1> 0:disable, 1:enable\nvow_watf_q = <level>-<quantum> unit 256us\nvow_watf_add_entry = <level>-<Addr>\nvow_watf_del_entry = <Addr>\n"
                            + uVar4 * 0x5834 + param_1 + 0xe0);
  }
  *(undefined1 *)((int)&g_WPSLEDStatus + uVar4) = 5;
  if (param_4 == 0) {
    uVar2 = HcGetBandByWdev(*(undefined4 *)(param_3 + 0x29ec));
    RTMPSetLED(param_1,0xc,uVar2);
  }
  return;
}

