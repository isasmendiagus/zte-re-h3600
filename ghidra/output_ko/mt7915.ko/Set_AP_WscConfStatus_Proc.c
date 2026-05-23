// module: mt7915.ko
// function: Set_AP_WscConfStatus_Proc @ 0x2a910
// size: 640 bytes
//

undefined4 Set_AP_WscConfStatus_Proc(int *param_1,undefined4 param_2)

{
  byte bVar1;
  uint uVar2;
  uint uVar3;
  uint uVar4;
  undefined4 uVar5;
  int iVar6;
  
  uVar2 = *(uint *)(*param_1 + 0x3c);
  if (*(int *)(*param_1 + 0x38) == 0x400) {
    if (2 < DebugLevel) {
      printk("IF(apcli%d) Set_WscConfStatus_Proc:: Ap Client doesn\'t need this command.\n",
             uVar2 & 0xff);
    }
  }
  else {
    uVar2 = uVar2 & 0xff;
    if (((char)param_1[uVar2 * 0x160d + 0xaec17] == '\0') &&
       (*(char *)((int)param_1 + uVar2 * 0x5834 + 0x2bb05d) != '\0')) {
      *(undefined2 *)(param_1 + uVar2 * 0x160d + 0xae04a) = 0;
      *(undefined2 *)((int)param_1 + uVar2 * 0x5834 + 0x2b832a) = 0;
      return 0;
    }
    bVar1 = os_str_tol(param_2,0,10);
    iVar6 = uVar2 * 0x5834;
    uVar3 = param_1[uVar2 * 0x160d + 0xae154];
    if (param_1[uVar2 * 0x160d + 0xae14c] == 1) {
      uVar5 = 0;
    }
    else {
      uVar5 = 4;
    }
    uVar4 = (uint)bVar1;
    if (uVar4 - 1 < 2) {
      *(byte *)(param_1 + uVar2 * 0x160d + 0xae14d) = bVar1;
      WscBuildBeaconIE(param_1,uVar4,uVar3 & 0xff,uVar5,0,uVar2,0,0,0);
      WscBuildProbeRespIE(param_1,3,uVar4,uVar3 & 0xff,uVar5,0,uVar2,0,0,0);
      UpdateBeaconHandler(param_1,(char *)((int)param_1 +
                                          (int)(
                                               "======== Badnode detector =============\nvow_bn_en = <0/1> 0:dieable, 1:enable\nvow_bn_mon_period = <period> ms\nvow_bn_fallback_th = <count>\nvow_bn_per_th = <TX PER>\n======== Airtime counter test =============\nvow_counter_test = <0/1> 0:dieable, 1:enable\nvow_counter_test_period = <period> ms\nvow_counter_test_band = <band>\nvow_counter_test_avgcnt = <average num> sec\nvow_counter_test_target = <wlanidx>\n======== DVT =============\nvow_dvt_en = <0/1> 0:dieable, 1:enable\nvow_monitor_sta = <STA num>\nvow_show_sta = <STA num>\nvow_monitor_bss = <BSS num>\nvow_monitor_mbss = <MBSS num>\nvow_show_mbss = <MBSS num>\nvow_avg_num = <average num> sec\n======== RED ===========\nvow_set_red_en = <0/1> 0:disable, 1:enable\nvow_set_red_show_sta = <STA num>\nvow_set_red_tar_delay = <tarDelay> us\n======== WATF ===========\nvow_watf_en = <0/1> 0:disable, 1:enable\nvow_watf_q = <level>-<quantum> unit 256us\nvow_watf_add_entry = <level>-<Addr>\nvow_watf_del_entry = <Addr>\n"
                                               + iVar6 + 0xe0)),2);
      if (2 < DebugLevel) {
        printk("IF(%02x:%02x:%02x:%02x:%02x:%02x) Set_WscConfStatus_Proc::(WscConfStatus=%d)\n",
               *(undefined1 *)((int)param_1 + iVar6 + 0x2b7269),
               *(undefined1 *)((int)param_1 + iVar6 + 0x2b726a),
               *(undefined1 *)((int)param_1 + iVar6 + 0x2b726b),
               (char)param_1[uVar2 * 0x160d + 0xadc9b],
               *(undefined1 *)((int)param_1 + iVar6 + 0x2b726d),
               *(undefined1 *)((int)param_1 + iVar6 + 0x2b726e),
               (char)param_1[uVar2 * 0x160d + 0xae14d]);
      }
      return 1;
    }
    if ((2 < DebugLevel) &&
       (printk("IF(ra%d) Set_WscConfStatus_Proc:: Set failed!!(WscConfStatus=%s), WscConfStatus is 1 or 2\n"
               ,uVar2,param_2), 2 < DebugLevel)) {
      printk("IF(ra%d) Set_WscConfStatus_Proc:: WscConfStatus is not changed (%d)\n",uVar2,
             (char)param_1[uVar2 * 0x160d + 0xae14d]);
      return 0;
    }
  }
  return 0;
}

