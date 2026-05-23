// module: mt7915.ko
// function: sta_cntl_scan_conf @ 0x6fffc
// size: 512 bytes
//

void sta_cntl_scan_conf(void *param_1)

{
  byte bVar1;
  char cVar2;
  int iVar3;
  undefined4 uVar4;
  int iVar5;
  char *pcVar6;
  int iVar7;
  uint uVar8;
  int iVar9;
  short local_2a [3];
  
  iVar7 = *(int *)((int)param_1 + 0x92c);
  local_2a[0] = 0;
  iVar9 = *(int *)(iVar7 + 8);
  if (iVar9 == 0) {
    printk(&_LC5,0x7a4);
    dump_stack();
  }
  iVar3 = GetStaCfgByWdev(iVar9,iVar7);
  if (iVar3 == 0) {
    printk(&_LC1,0x7a5);
    dump_stack();
    return;
  }
  uVar4 = get_scan_tab_by_wdev(iVar9,iVar7);
  os_move_mem(local_2a,param_1,2);
  if ((((*(byte *)(iVar9 + 0x7956b5) & 1) != 0) && ((*(uint *)(iVar3 + 0x212464) & 1) != 0)) &&
     ((*(uint *)(iVar9 + 0x795124) & 0x40000) != 0)) {
    iVar5 = GetAssociatedAPByWdev(iVar9,iVar7);
    if (iVar5 == 0) {
      printk(&_LC6,0x7c0);
      dump_stack();
    }
    Update2040CoexistFrameAndNotify(iVar9,*(undefined2 *)(iVar5 + 0xe0),1);
  }
  if (local_2a[0] == 0) {
    bss_table_maintenance(iVar9,iVar3,uVar4,0x78,2);
  }
  cntl_fsm_state_transition(iVar7,0,"sta_cntl_scan_conf");
  AsicSetSyncModeAndEnable(iVar9,*(undefined2 *)(&DAT_00794c50 + iVar9),0,1);
  bVar1 = "======== Badnode detector =============\nvow_bn_en = <0/1> 0:dieable, 1:enable\nvow_bn_mon_period = <period> ms\nvow_bn_fallback_th = <count>\nvow_bn_per_th = <TX PER>\n======== Airtime counter test =============\nvow_counter_test = <0/1> 0:dieable, 1:enable\nvow_counter_test_period = <period> ms\nvow_counter_test_band = <band>\nvow_counter_test_avgcnt = <average num> sec\nvow_counter_test_target = <wlanidx>\n======== DVT =============\nvow_dvt_en = <0/1> 0:dieable, 1:enable\nvow_monitor_sta = <STA num>\nvow_show_sta = <STA num>\nvow_monitor_bss = <BSS num>\nvow_monitor_mbss = <MBSS num>\nvow_show_mbss = <MBSS num>\nvow_avg_num = <average num> sec\n======== RED ===========\nvow_set_red_en = <0/1> 0:disable, 1:enable\nvow_set_red_show_sta = <STA num>\nvow_set_red_tar_delay = <tarDelay> us\n======== WATF ===========\nvow_watf_en = <0/1> 0:disable, 1:enable\nvow_watf_q = <level>-<quantum> unit 256us\nvow_watf_add_entry = <level>-<Addr>\nvow_watf_del_entry = <Addr>\n"
          [iVar9 + 0xda];
  if (bVar1 != 0) {
    uVar8 = 0;
    pcVar6 = "======== Badnode detector =============\nvow_bn_en = <0/1> 0:dieable, 1:enable\nvow_bn_mon_period = <period> ms\nvow_bn_fallback_th = <count>\nvow_bn_per_th = <TX PER>\n======== Airtime counter test =============\nvow_counter_test = <0/1> 0:dieable, 1:enable\nvow_counter_test_period = <period> ms\nvow_counter_test_band = <band>\nvow_counter_test_avgcnt = <average num> sec\nvow_counter_test_target = <wlanidx>\n======== DVT =============\nvow_dvt_en = <0/1> 0:dieable, 1:enable\nvow_monitor_sta = <STA num>\nvow_show_sta = <STA num>\nvow_monitor_bss = <BSS num>\nvow_monitor_mbss = <MBSS num>\nvow_show_mbss = <MBSS num>\nvow_avg_num = <average num> sec\n======== RED ===========\nvow_set_red_en = <0/1> 0:disable, 1:enable\nvow_set_red_show_sta = <STA num>\nvow_set_red_tar_delay = <tarDelay> us\n======== WATF ===========\nvow_watf_en = <0/1> 0:disable, 1:enable\nvow_watf_q = <level>-<quantum> unit 256us\nvow_watf_add_entry = <level>-<Addr>\nvow_watf_del_entry = <Addr>\n"
             + iVar9 + 0xe0;
    do {
      uVar8 = uVar8 + 1;
      cVar2 = pcVar6[0x944];
      pcVar6[0x944] = '\0';
      if (pcVar6[0xb1c] != '\0') {
        UpdateBeaconHandler(iVar9,pcVar6,5);
      }
      pcVar6[0x944] = cVar2;
      pcVar6 = pcVar6 + 0x5834;
    } while (bVar1 != uVar8);
  }
  if ((((*(uint *)(iVar3 + 0x212464) & 1) != 0) && (*(int *)(iVar3 + 0x2124ac) != 0)) &&
     (*(char *)(iVar3 + 0x2124c0) == '\0')) {
    RTMP_SLEEP_FORCE_AUTO_WAKEUP(iVar9,iVar3);
    return;
  }
  return;
}

