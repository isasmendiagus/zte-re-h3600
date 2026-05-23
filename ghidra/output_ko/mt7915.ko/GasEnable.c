// module: mt7915.ko
// function: GasEnable @ 0x22cc44
// size: 232 bytes
//

undefined1 GasEnable(int param_1,int param_2)

{
  undefined1 uVar1;
  int iVar2;
  uint uVar3;
  uint uVar4;
  uint uVar5;
  int iVar6;
  
  uVar5 = 0;
  do {
    uVar3 = hc_get_chip_bcn_max_num(*(undefined4 *)(param_1 + 0xa797a0));
    uVar4 = uVar5 & 0xff;
    iVar6 = uVar4 * 0x5834;
    uVar5 = uVar5 + 1;
    if (uVar3 <= uVar4) goto LAB_0022ccac;
    iVar2 = memcmp((void *)(param_2 + 4),
                   "======== Badnode detector =============\nvow_bn_en = <0/1> 0:dieable, 1:enable\nvow_bn_mon_period = <period> ms\nvow_bn_fallback_th = <count>\nvow_bn_per_th = <TX PER>\n======== Airtime counter test =============\nvow_counter_test = <0/1> 0:dieable, 1:enable\nvow_counter_test_period = <period> ms\nvow_counter_test_band = <band>\nvow_counter_test_avgcnt = <average num> sec\nvow_counter_test_target = <wlanidx>\n======== DVT =============\nvow_dvt_en = <0/1> 0:dieable, 1:enable\nvow_monitor_sta = <STA num>\nvow_show_sta = <STA num>\nvow_monitor_bss = <BSS num>\nvow_monitor_mbss = <MBSS num>\nvow_show_mbss = <MBSS num>\nvow_avg_num = <average num> sec\n======== RED ===========\nvow_set_red_en = <0/1> 0:disable, 1:enable\nvow_set_red_show_sta = <STA num>\nvow_set_red_tar_delay = <tarDelay> us\n======== WATF ===========\nvow_watf_en = <0/1> 0:disable, 1:enable\nvow_watf_q = <level>-<quantum> unit 256us\nvow_watf_add_entry = <level>-<Addr>\nvow_watf_del_entry = <Addr>\n"
                   + param_1 + iVar6 + 0x101,6);
  } while (iVar2 != 0);
  if ("RT_OID_WSC_SET_PROFILE:: ProfileCnt = %d\n" + param_1 + iVar6 + 0x1c == (char *)0x0) {
LAB_0022ccac:
    if (DebugLevel < 4) {
      uVar1 = 0;
    }
    else {
      printk("%s Can not find Peer Control DA=%02x:%02x:%02x:%02x:%02x:%02x\n","GasEnable",
             *(undefined1 *)(param_2 + 4),*(undefined1 *)(param_2 + 5),*(undefined1 *)(param_2 + 6),
             *(undefined1 *)(param_2 + 7),*(undefined1 *)(param_2 + 8),*(undefined1 *)(param_2 + 9))
      ;
      uVar1 = 0;
    }
  }
  else {
    uVar1 = (&_LC168)[param_1 + iVar6];
  }
  return uVar1;
}

