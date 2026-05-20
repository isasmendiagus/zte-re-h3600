// module: mt7915.ko
// function: WscSetupLockTimeout @ 0x201310
// size: 232 bytes
//

void WscSetupLockTimeout(undefined4 param_1,int param_2)

{
  int iVar1;
  uint uVar2;
  
  if (param_2 == 0) {
    return;
  }
  iVar1 = *(int *)(param_2 + 0x29e8);
  uVar2 = *(byte *)(param_2 + 0x1c54) & 0xf;
  if (iVar1 != 0) {
    *(undefined1 *)(param_2 + 0x2bd9) = 0;
    *(undefined1 *)(param_2 + 0x2ba0) = 0;
    WscBuildBeaconIE(iVar1,*(undefined1 *)(param_2 + 8),0,0,0,uVar2,0,0,0);
    WscBuildProbeRespIE(iVar1,3,*(undefined1 *)(param_2 + 8),0,0,0,*(undefined1 *)(param_2 + 0x1c54)
                        ,0,0,0);
    UpdateBeaconHandler(iVar1,"======== Badnode detector =============\nvow_bn_en = <0/1> 0:dieable, 1:enable\nvow_bn_mon_period = <period> ms\nvow_bn_fallback_th = <count>\nvow_bn_per_th = <TX PER>\n======== Airtime counter test =============\nvow_counter_test = <0/1> 0:dieable, 1:enable\nvow_counter_test_period = <period> ms\nvow_counter_test_band = <band>\nvow_counter_test_avgcnt = <average num> sec\nvow_counter_test_target = <wlanidx>\n======== DVT =============\nvow_dvt_en = <0/1> 0:dieable, 1:enable\nvow_monitor_sta = <STA num>\nvow_show_sta = <STA num>\nvow_monitor_bss = <BSS num>\nvow_monitor_mbss = <MBSS num>\nvow_show_mbss = <MBSS num>\nvow_avg_num = <average num> sec\n======== RED ===========\nvow_set_red_en = <0/1> 0:disable, 1:enable\nvow_set_red_show_sta = <STA num>\nvow_set_red_tar_delay = <tarDelay> us\n======== WATF ===========\nvow_watf_en = <0/1> 0:disable, 1:enable\nvow_watf_q = <level>-<quantum> unit 256us\nvow_watf_add_entry = <level>-<Addr>\nvow_watf_del_entry = <Addr>\n"
                              + uVar2 * 0x5834 + iVar1 + 0xe0,2);
    if (2 < DebugLevel) {
      printk("WscSetupLockTimeout!\n");
      return;
    }
  }
  return;
}

