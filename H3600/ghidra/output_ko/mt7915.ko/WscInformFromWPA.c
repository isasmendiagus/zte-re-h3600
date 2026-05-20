// module: mt7915.ko
// function: WscInformFromWPA @ 0x1e5538
// size: 260 bytes
//

void WscInformFromWPA(int param_1)

{
  int iVar1;
  int iVar2;
  undefined1 auStack_19 [5];
  
  if ((byte)"======== Badnode detector =============\nvow_bn_en = <0/1> 0:dieable, 1:enable\nvow_bn_mon_period = <period> ms\nvow_bn_fallback_th = <count>\nvow_bn_per_th = <TX PER>\n======== Airtime counter test =============\nvow_counter_test = <0/1> 0:dieable, 1:enable\nvow_counter_test_period = <period> ms\nvow_counter_test_band = <band>\nvow_counter_test_avgcnt = <average num> sec\nvow_counter_test_target = <wlanidx>\n======== DVT =============\nvow_dvt_en = <0/1> 0:dieable, 1:enable\nvow_monitor_sta = <STA num>\nvow_show_sta = <STA num>\nvow_monitor_bss = <BSS num>\nvow_monitor_mbss = <MBSS num>\nvow_show_mbss = <MBSS num>\nvow_avg_num = <average num> sec\n======== RED ===========\nvow_set_red_en = <0/1> 0:disable, 1:enable\nvow_set_red_show_sta = <STA num>\nvow_set_red_tar_delay = <tarDelay> us\n======== WATF ===========\nvow_watf_en = <0/1> 0:disable, 1:enable\nvow_watf_q = <level>-<quantum> unit 256us\nvow_watf_add_entry = <level>-<Addr>\nvow_watf_del_entry = <Addr>\n"
            [*(int *)(param_1 + 0xc) + 0xda] <= *(byte *)(param_1 + 0xe4)) {
    return;
  }
  iVar2 = *(int *)(param_1 + 8);
  if (DebugLevel < 3) {
    iVar1 = memcmp((void *)(param_1 + 0xec),(void *)(iVar2 + 0x2f39),6);
    if (iVar1 != 0) {
      return;
    }
  }
  else {
    printk("-----> WscInformFromWPA\n");
    iVar1 = memcmp((void *)(param_1 + 0xec),(void *)(iVar2 + 0x2f39),6);
    if (iVar1 != 0) goto LAB_001e5620;
  }
  __memzero(iVar2 + 0x2f39,6);
  RTMPCancelTimer(iVar2 + 0x3ab0,auStack_19);
  iVar1 = DebugLevel;
  *(undefined1 *)(iVar2 + 0x3aac) = 0;
  *(undefined1 *)(param_1 + 0xd24) = 0;
  *(undefined4 *)(iVar2 + 0x12f4) = 4;
  if (iVar1 < 3) {
    return;
  }
  printk("Reset EntryIfIdx to %d\n",0xff);
LAB_001e5620:
  if (2 < DebugLevel) {
    printk("<----- WscInformFromWPA\n");
  }
  return;
}

