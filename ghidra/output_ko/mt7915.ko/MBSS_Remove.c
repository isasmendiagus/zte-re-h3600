// module: mt7915.ko
// function: MBSS_Remove @ 0x522ec
// size: 208 bytes
//

void MBSS_Remove(int param_1)

{
  int iVar1;
  int iVar2;
  int *piVar3;
  uint uVar4;
  uint uVar5;
  bool bVar6;
  
  if (param_1 == 0) {
    return;
  }
  uVar5 = (uint)(byte)"======== Badnode detector =============\nvow_bn_en = <0/1> 0:dieable, 1:enable\nvow_bn_mon_period = <period> ms\nvow_bn_fallback_th = <count>\nvow_bn_per_th = <TX PER>\n======== Airtime counter test =============\nvow_counter_test = <0/1> 0:dieable, 1:enable\nvow_counter_test_period = <period> ms\nvow_counter_test_band = <band>\nvow_counter_test_avgcnt = <average num> sec\nvow_counter_test_target = <wlanidx>\n======== DVT =============\nvow_dvt_en = <0/1> 0:dieable, 1:enable\nvow_monitor_sta = <STA num>\nvow_show_sta = <STA num>\nvow_monitor_bss = <BSS num>\nvow_monitor_mbss = <MBSS num>\nvow_show_mbss = <MBSS num>\nvow_avg_num = <average num> sec\n======== RED ===========\nvow_set_red_en = <0/1> 0:disable, 1:enable\nvow_set_red_show_sta = <STA num>\nvow_set_red_tar_delay = <tarDelay> us\n======== WATF ===========\nvow_watf_en = <0/1> 0:disable, 1:enable\nvow_watf_q = <level>-<quantum> unit 256us\nvow_watf_add_entry = <level>-<Addr>\nvow_watf_del_entry = <Addr>\n"
                      [param_1 + 0xda];
  iVar2 = hc_get_chip_bcn_max_num(*(undefined4 *)(param_1 + 0xa797a0));
  bVar6 = SBORROW4(uVar5,0x1f);
  iVar1 = uVar5 - 0x1f;
  if (uVar5 < 0x20) {
    bVar6 = SBORROW4(uVar5,iVar2);
    iVar1 = uVar5 - iVar2;
  }
  if (iVar1 < 0 == bVar6) {
    uVar5 = hc_get_chip_bcn_max_num(*(undefined4 *)(param_1 + 0xa797a0));
    if ((int)uVar5 < 2) {
      return;
    }
  }
  else if (uVar5 < 2) {
    return;
  }
  uVar4 = 1;
  piVar3 = (int *)("%s: Allocate memory fail!!!\n" + param_1 + 0xc);
  do {
    uVar4 = uVar4 + 1;
    bcn_buf_deinit(param_1,piVar3 + 0x252);
    if (*piVar3 != 0) {
      RtmpOSNetDevProtect(1);
      RtmpOSNetDevDetach(*piVar3);
      RtmpOSNetDevProtect(0);
      wdev_deinit(param_1,piVar3);
      RtmpOSNetDevFree(*piVar3);
      *piVar3 = 0;
    }
    piVar3 = piVar3 + 0x160d;
  } while (uVar4 != uVar5);
  return;
}

