// module: mt7915.ko
// function: BndStrg_Init @ 0x9d804
// size: 160 bytes
//

int BndStrg_Init(int param_1)

{
  byte bVar1;
  int iVar2;
  uint uVar3;
  
  bVar1 = "======== Badnode detector =============\nvow_bn_en = <0/1> 0:dieable, 1:enable\nvow_bn_mon_period = <period> ms\nvow_bn_fallback_th = <count>\nvow_bn_per_th = <TX PER>\n======== Airtime counter test =============\nvow_counter_test = <0/1> 0:dieable, 1:enable\nvow_counter_test_period = <period> ms\nvow_counter_test_band = <band>\nvow_counter_test_avgcnt = <average num> sec\nvow_counter_test_target = <wlanidx>\n======== DVT =============\nvow_dvt_en = <0/1> 0:dieable, 1:enable\nvow_monitor_sta = <STA num>\nvow_show_sta = <STA num>\nvow_monitor_bss = <BSS num>\nvow_monitor_mbss = <MBSS num>\nvow_show_mbss = <MBSS num>\nvow_avg_num = <average num> sec\n======== RED ===========\nvow_set_red_en = <0/1> 0:disable, 1:enable\nvow_set_red_show_sta = <STA num>\nvow_set_red_tar_delay = <tarDelay> us\n======== WATF ===========\nvow_watf_en = <0/1> 0:disable, 1:enable\nvow_watf_q = <level>-<quantum> unit 256us\nvow_watf_add_entry = <level>-<Addr>\nvow_watf_del_entry = <Addr>\n"
          [param_1 + 0xda];
  if (0 < DebugLevel) {
    printk(&_LC65,"BndStrg_Init");
  }
  if (bVar1 == 0) {
    iVar2 = 0;
  }
  else {
    uVar3 = 0;
    do {
      iVar2 = BndStrg_TableInit(param_1,uVar3);
      if ((iVar2 != 0) && (-1 < DebugLevel)) {
        printk("Error in %s(), error code = %d on apidx = %d\n","BndStrg_Init",iVar2,uVar3);
      }
      uVar3 = uVar3 + 1;
    } while (bVar1 != uVar3);
  }
  return iVar2;
}

