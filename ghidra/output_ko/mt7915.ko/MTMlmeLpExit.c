// module: mt7915.ko
// function: MTMlmeLpExit @ 0x19a3ac
// size: 364 bytes
//

void MTMlmeLpExit(int param_1,undefined4 param_2,undefined4 param_3,undefined4 param_4)

{
  byte bVar1;
  int iVar2;
  int iVar3;
  int *piVar4;
  int iVar5;
  
  bVar1 = "======== Badnode detector =============\nvow_bn_en = <0/1> 0:dieable, 1:enable\nvow_bn_mon_period = <period> ms\nvow_bn_fallback_th = <count>\nvow_bn_per_th = <TX PER>\n======== Airtime counter test =============\nvow_counter_test = <0/1> 0:dieable, 1:enable\nvow_counter_test_period = <period> ms\nvow_counter_test_band = <band>\nvow_counter_test_avgcnt = <average num> sec\nvow_counter_test_target = <wlanidx>\n======== DVT =============\nvow_dvt_en = <0/1> 0:dieable, 1:enable\nvow_monitor_sta = <STA num>\nvow_show_sta = <STA num>\nvow_monitor_bss = <BSS num>\nvow_monitor_mbss = <MBSS num>\nvow_show_mbss = <MBSS num>\nvow_avg_num = <average num> sec\n======== RED ===========\nvow_set_red_en = <0/1> 0:disable, 1:enable\nvow_set_red_show_sta = <STA num>\nvow_set_red_tar_delay = <tarDelay> us\n======== WATF ===========\nvow_watf_en = <0/1> 0:disable, 1:enable\nvow_watf_q = <level>-<quantum> unit 256us\nvow_watf_add_entry = <level>-<Addr>\nvow_watf_del_entry = <Addr>\n"
          [param_1 + 0xda];
  DriverOwn();
  if (2 < DebugLevel) {
    printk("%s(%d)::PDMA\n","MTMlmeLpExit",0xb0,DebugLevel,param_4);
  }
  chip_set_hif_dma(param_1,2,1);
  RtmpOsMsDelay(100);
  if (2 < DebugLevel) {
    printk("%s(%d)::bDrvOwn(%d)\n","MTMlmeLpExit",0xb6,*(undefined1 *)(param_1 + 0xa7becc),param_4);
  }
  iVar2 = hc_get_chip_ops(*(undefined4 *)(param_1 + 0xa797a0));
  if (*(code **)(iVar2 + 0xa8) != (code *)0x0) {
    (**(code **)(iVar2 + 0xa8))(param_1);
  }
  *(uint *)(param_1 + 0xa39f84) = *(uint *)(param_1 + 0xa39f84) | 0x1000000;
  RTMP_RADIO_ON_OFF_CTRL(param_1,2,1);
  HcSetAllSupportedBandsRadioOn(param_1);
  _clear_bit(0,*(int *)(*(int *)(param_1 + 4) + 0x240) + 0x50);
  if (*(char *)(param_1 + 0x286285) != '\x01') {
    return;
  }
  iVar2 = hc_get_chip_bcn_max_num(*(undefined4 *)(param_1 + 0xa797a0));
  if (iVar2 < (int)(uint)bVar1) {
    hc_get_chip_bcn_max_num(*(undefined4 *)(param_1 + 0xa797a0));
  }
  piVar4 = (int *)("%s: Allocate memory fail!!!\n" + param_1 + 0xc);
  iVar2 = 1;
  while( true ) {
    iVar3 = hc_get_chip_bcn_max_num(*(undefined4 *)(param_1 + 0xa797a0));
    iVar5 = iVar2 + 1;
    if (iVar3 <= iVar2) break;
    iVar3 = *piVar4;
    piVar4 = piVar4 + 0x160d;
    iVar2 = iVar5;
    if (iVar3 != 0) {
      _clear_bit(0,*(int *)(iVar3 + 0x240) + 0x50);
    }
  }
  return;
}

