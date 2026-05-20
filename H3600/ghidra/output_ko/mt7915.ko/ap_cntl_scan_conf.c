// module: mt7915.ko
// function: ap_cntl_scan_conf @ 0x4ad28
// size: 244 bytes
//

void ap_cntl_scan_conf(void *param_1)

{
  char *pcVar1;
  uint uVar2;
  int iVar3;
  uint uVar4;
  int iVar5;
  undefined2 local_1a;
  
  iVar3 = *(int *)((int)param_1 + 0x92c);
  local_1a = 0;
  iVar5 = *(int *)(iVar3 + 8);
  if (iVar5 == 0) {
    printk(&_LC0,0x40);
    dump_stack();
  }
  uVar2 = 0;
  uVar4 = (uint)(byte)"======== Badnode detector =============\nvow_bn_en = <0/1> 0:dieable, 1:enable\nvow_bn_mon_period = <period> ms\nvow_bn_fallback_th = <count>\nvow_bn_per_th = <TX PER>\n======== Airtime counter test =============\nvow_counter_test = <0/1> 0:dieable, 1:enable\nvow_counter_test_period = <period> ms\nvow_counter_test_band = <band>\nvow_counter_test_avgcnt = <average num> sec\nvow_counter_test_target = <wlanidx>\n======== DVT =============\nvow_dvt_en = <0/1> 0:dieable, 1:enable\nvow_monitor_sta = <STA num>\nvow_show_sta = <STA num>\nvow_monitor_bss = <BSS num>\nvow_monitor_mbss = <MBSS num>\nvow_show_mbss = <MBSS num>\nvow_avg_num = <average num> sec\n======== RED ===========\nvow_set_red_en = <0/1> 0:disable, 1:enable\nvow_set_red_show_sta = <STA num>\nvow_set_red_tar_delay = <tarDelay> us\n======== WATF ===========\nvow_watf_en = <0/1> 0:disable, 1:enable\nvow_watf_q = <level>-<quantum> unit 256us\nvow_watf_add_entry = <level>-<Addr>\nvow_watf_del_entry = <Addr>\n"
                      [iVar5 + 0xda];
  os_move_mem(&local_1a,param_1,2);
  *(undefined1 *)(iVar3 + 0xbb4) = 0;
  cntl_fsm_state_transition(iVar3,0,"ap_cntl_scan_conf");
  AsicSetSyncModeAndEnable(iVar5,*(undefined2 *)(&DAT_00794c50 + iVar5),0,1);
  if (uVar4 != 0) {
    pcVar1 = "======== Badnode detector =============\nvow_bn_en = <0/1> 0:dieable, 1:enable\nvow_bn_mon_period = <period> ms\nvow_bn_fallback_th = <count>\nvow_bn_per_th = <TX PER>\n======== Airtime counter test =============\nvow_counter_test = <0/1> 0:dieable, 1:enable\nvow_counter_test_period = <period> ms\nvow_counter_test_band = <band>\nvow_counter_test_avgcnt = <average num> sec\nvow_counter_test_target = <wlanidx>\n======== DVT =============\nvow_dvt_en = <0/1> 0:dieable, 1:enable\nvow_monitor_sta = <STA num>\nvow_show_sta = <STA num>\nvow_monitor_bss = <BSS num>\nvow_monitor_mbss = <MBSS num>\nvow_show_mbss = <MBSS num>\nvow_avg_num = <average num> sec\n======== RED ===========\nvow_set_red_en = <0/1> 0:disable, 1:enable\nvow_set_red_show_sta = <STA num>\nvow_set_red_tar_delay = <tarDelay> us\n======== WATF ===========\nvow_watf_en = <0/1> 0:disable, 1:enable\nvow_watf_q = <level>-<quantum> unit 256us\nvow_watf_add_entry = <level>-<Addr>\nvow_watf_del_entry = <Addr>\n"
             + iVar5 + 0xe0;
    do {
      while (uVar2 = uVar2 + 1, *(char *)(iVar3 + 0xb1c) != '\0') {
        UpdateBeaconHandler(iVar5,pcVar1,5);
        pcVar1 = pcVar1 + 0x5834;
        if (uVar4 == uVar2) {
          return;
        }
      }
      pcVar1 = pcVar1 + 0x5834;
    } while (uVar4 != uVar2);
  }
  return;
}

