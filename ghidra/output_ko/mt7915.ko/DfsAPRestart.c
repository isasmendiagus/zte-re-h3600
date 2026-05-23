// module: mt7915.ko
// function: DfsAPRestart @ 0x231ecc
// size: 112 bytes
//

undefined4 DfsAPRestart(int param_1,int param_2)

{
  int iVar1;
  uint uVar2;
  
  iVar1 = **(int **)(param_2 + 4);
  *(char *)(param_1 + 0x7953f0) = (char)((uint)iVar1 >> 0x10);
  APStartUp(param_1,"======== Badnode detector =============\nvow_bn_en = <0/1> 0:dieable, 1:enable\nvow_bn_mon_period = <period> ms\nvow_bn_fallback_th = <count>\nvow_bn_per_th = <TX PER>\n======== Airtime counter test =============\nvow_counter_test = <0/1> 0:dieable, 1:enable\nvow_counter_test_period = <period> ms\nvow_counter_test_band = <band>\nvow_counter_test_avgcnt = <average num> sec\nvow_counter_test_target = <wlanidx>\n======== DVT =============\nvow_dvt_en = <0/1> 0:dieable, 1:enable\nvow_monitor_sta = <STA num>\nvow_show_sta = <STA num>\nvow_monitor_bss = <BSS num>\nvow_monitor_mbss = <MBSS num>\nvow_show_mbss = <MBSS num>\nvow_avg_num = <average num> sec\n======== RED ===========\nvow_set_red_en = <0/1> 0:disable, 1:enable\nvow_set_red_show_sta = <STA num>\nvow_set_red_tar_delay = <tarDelay> us\n======== WATF ===========\nvow_watf_en = <0/1> 0:disable, 1:enable\nvow_watf_q = <level>-<quantum> unit 256us\nvow_watf_add_entry = <level>-<Addr>\nvow_watf_del_entry = <Addr>\n"
                    + ((uint)(iVar1 << 0x10) >> 0x18) * 0x5834 + param_1 + 0xe0,1);
  uVar2 = 0;
  if (*(char *)(param_1 + 0x79504d) != '\0') {
    uVar2 = (uint)(iVar1 << 8) >> 0x18;
  }
  MtCmdSetDfsTxStart(param_1,uVar2);
  return 0;
}

