// module: mt7915.ko
// function: MgmtTableSetMcastEntry @ 0x148930
// size: 288 bytes
//

void MgmtTableSetMcastEntry(int param_1,int param_2)

{
  int iVar1;
  
  iVar1 = param_1 + param_2 * 0x14c0;
  *(undefined4 *)(iVar1 + 0xa1d20) = 0x400;
  *(undefined4 *)(iVar1 + 0xa1e1c) = 2;
  *(short *)(iVar1 + 0xa1e18) = (short)param_2;
  *(short *)(iVar1 + 0xa1e00) = (short)param_2;
  *(undefined1 *)(iVar1 + 0xa2818) = 0;
  *(undefined1 *)(iVar1 + 0xa289f) = *(undefined1 *)(param_1 + 0x794cd5);
  *(undefined1 *)(iVar1 + 0xa1e0c) = 1;
  *(byte *)(iVar1 + 0xa1ddd) = *(byte *)(iVar1 + 0xa1ddd) & 0x1f | 0x20;
  *(byte *)(iVar1 + 0xa1ddc) = *(byte *)(iVar1 + 0xa1ddc) & 0xc0 | 3;
  memmove((void *)(iVar1 + 0xa1e0c),&BROADCAST_ADDR,6);
  if (*(char *)(param_1 + 0x286285) == '\x01') {
    *(char **)(iVar1 + 0xa1d28) =
         "======== Badnode detector =============\nvow_bn_en = <0/1> 0:dieable, 1:enable\nvow_bn_mon_period = <period> ms\nvow_bn_fallback_th = <count>\nvow_bn_per_th = <TX PER>\n======== Airtime counter test =============\nvow_counter_test = <0/1> 0:dieable, 1:enable\nvow_counter_test_period = <period> ms\nvow_counter_test_band = <band>\nvow_counter_test_avgcnt = <average num> sec\nvow_counter_test_target = <wlanidx>\n======== DVT =============\nvow_dvt_en = <0/1> 0:dieable, 1:enable\nvow_monitor_sta = <STA num>\nvow_show_sta = <STA num>\nvow_monitor_bss = <BSS num>\nvow_monitor_mbss = <MBSS num>\nvow_show_mbss = <MBSS num>\nvow_avg_num = <average num> sec\n======== RED ===========\nvow_set_red_en = <0/1> 0:disable, 1:enable\nvow_set_red_show_sta = <STA num>\nvow_set_red_tar_delay = <tarDelay> us\n======== WATF ===========\nvow_watf_en = <0/1> 0:disable, 1:enable\nvow_watf_q = <level>-<quantum> unit 256us\nvow_watf_add_entry = <level>-<Addr>\nvow_watf_del_entry = <Addr>\n"
         + param_1 + 0xe0;
    return;
  }
  if (*(char *)(param_1 + 0x286285) != '\0') {
    return;
  }
  *(undefined **)(iVar1 + 0xa1d28) = &DAT_0036db58 + param_1;
  return;
}

