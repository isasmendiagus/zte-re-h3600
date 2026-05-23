// module: mt7915.ko
// function: set_rrm_capabilities @ 0x220688
// size: 248 bytes
//

undefined4 set_rrm_capabilities(int *param_1,undefined4 *param_2)

{
  undefined4 uVar1;
  uint uVar2;
  int iVar3;
  
  uVar2 = (uint)*(byte *)(*param_1 + 0x3c);
  if (uVar2 < *(byte *)((int)param_1 + 0x2b7242)) {
    iVar3 = uVar2 * 0x5834;
    uVar1 = param_2[1];
    *(undefined4 *)
     ((int)param_1 +
     (int)("The entry Level %d - %02x:%02x:%02x:%02x:%02x:%02x is set complete!\n" + iVar3 + 0x27))
         = *param_2;
    *(undefined4 *)
     ((int)param_1 +
     (int)("The entry Level %d - %02x:%02x:%02x:%02x:%02x:%02x is set complete!\n" + iVar3 + 0x2b))
         = uVar1;
    *(uint *)((int)param_1 + iVar3 + 0x2b7de3) =
         *(uint *)((int)param_1 + iVar3 + 0x2b7deb) & *(uint *)((int)param_1 + iVar3 + 0x2b7de3);
    *(uint *)((int)param_1 + iVar3 + 0x2b7de7) =
         *(uint *)((int)param_1 + iVar3 + 0x2b7def) & *(uint *)((int)param_1 + iVar3 + 0x2b7de7);
    if (*(char *)((int)param_1 + iVar3 + 0x2b7d69) != '\x01') {
      return 0;
    }
    UpdateBeaconHandler(param_1,(char *)((int)param_1 +
                                        (int)(
                                             "======== Badnode detector =============\nvow_bn_en = <0/1> 0:dieable, 1:enable\nvow_bn_mon_period = <period> ms\nvow_bn_fallback_th = <count>\nvow_bn_per_th = <TX PER>\n======== Airtime counter test =============\nvow_counter_test = <0/1> 0:dieable, 1:enable\nvow_counter_test_period = <period> ms\nvow_counter_test_band = <band>\nvow_counter_test_avgcnt = <average num> sec\nvow_counter_test_target = <wlanidx>\n======== DVT =============\nvow_dvt_en = <0/1> 0:dieable, 1:enable\nvow_monitor_sta = <STA num>\nvow_show_sta = <STA num>\nvow_monitor_bss = <BSS num>\nvow_monitor_mbss = <MBSS num>\nvow_show_mbss = <MBSS num>\nvow_avg_num = <average num> sec\n======== RED ===========\nvow_set_red_en = <0/1> 0:disable, 1:enable\nvow_set_red_show_sta = <STA num>\nvow_set_red_tar_delay = <tarDelay> us\n======== WATF ===========\nvow_watf_en = <0/1> 0:disable, 1:enable\nvow_watf_q = <level>-<quantum> unit 256us\nvow_watf_add_entry = <level>-<Addr>\nvow_watf_del_entry = <Addr>\n"
                                             + iVar3 + 0xe0)),2);
    return 0;
  }
  if (DebugLevel < 1) {
    return 1;
  }
  printk("Unknow If index (%d)",uVar2);
  return 1;
}

