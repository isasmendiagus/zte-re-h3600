// module: mt7915.ko
// function: BndStrg_MsgHandle @ 0x9dc14
// size: 416 bytes
//

undefined4 BndStrg_MsgHandle(int param_1,int param_2,int param_3)

{
  int iVar1;
  int iVar2;
  char cVar3;
  uint uVar4;
  undefined *puVar5;
  bool bVar6;
  undefined1 auStack_50 [64];
  
  iVar1 = hc_get_chip_bcn_max_num(*(undefined4 *)(param_1 + 0xa797a0));
  bVar6 = SBORROW4(param_3,0x1f);
  iVar2 = param_3 + -0x1f;
  if (param_3 < 0x20) {
    bVar6 = SBORROW4(param_3,iVar1);
    iVar2 = param_3 - iVar1;
  }
  if ((iVar2 < 0 == bVar6) ||
     ("======== Badnode detector =============\nvow_bn_en = <0/1> 0:dieable, 1:enable\nvow_bn_mon_period = <period> ms\nvow_bn_fallback_th = <count>\nvow_bn_per_th = <TX PER>\n======== Airtime counter test =============\nvow_counter_test = <0/1> 0:dieable, 1:enable\nvow_counter_test_period = <period> ms\nvow_counter_test_band = <band>\nvow_counter_test_avgcnt = <average num> sec\nvow_counter_test_target = <wlanidx>\n======== DVT =============\nvow_dvt_en = <0/1> 0:dieable, 1:enable\nvow_monitor_sta = <STA num>\nvow_show_sta = <STA num>\nvow_monitor_bss = <BSS num>\nvow_monitor_mbss = <MBSS num>\nvow_show_mbss = <MBSS num>\nvow_avg_num = <average num> sec\n======== RED ===========\nvow_set_red_en = <0/1> 0:disable, 1:enable\nvow_set_red_show_sta = <STA num>\nvow_set_red_tar_delay = <tarDelay> us\n======== WATF ===========\nvow_watf_en = <0/1> 0:disable, 1:enable\nvow_watf_q = <level>-<quantum> unit 256us\nvow_watf_add_entry = <level>-<Addr>\nvow_watf_del_entry = <Addr>\n"
      + param_1 + param_3 * 0x5834 + 0xe0 == (char *)0x0)) {
    if (-1 < DebugLevel) {
      printk(&_LC27,"Get_BndStrgTable",0x36,param_3);
    }
  }
  else {
    if ((*(ushort *)
          (
          "======== Badnode detector =============\nvow_bn_en = <0/1> 0:dieable, 1:enable\nvow_bn_mon_period = <period> ms\nvow_bn_fallback_th = <count>\nvow_bn_per_th = <TX PER>\n======== Airtime counter test =============\nvow_counter_test = <0/1> 0:dieable, 1:enable\nvow_counter_test_period = <period> ms\nvow_counter_test_band = <band>\nvow_counter_test_avgcnt = <average num> sec\nvow_counter_test_target = <wlanidx>\n======== DVT =============\nvow_dvt_en = <0/1> 0:dieable, 1:enable\nvow_monitor_sta = <STA num>\nvow_show_sta = <STA num>\nvow_monitor_bss = <BSS num>\nvow_monitor_mbss = <MBSS num>\nvow_show_mbss = <MBSS num>\nvow_avg_num = <average num> sec\n======== RED ===========\nvow_set_red_en = <0/1> 0:disable, 1:enable\nvow_set_red_show_sta = <STA num>\nvow_set_red_tar_delay = <tarDelay> us\n======== WATF ===========\nvow_watf_en = <0/1> 0:disable, 1:enable\nvow_watf_q = <level>-<quantum> unit 256us\nvow_watf_add_entry = <level>-<Addr>\nvow_watf_del_entry = <Addr>\n"
          + param_1 + param_3 * 0x5834 + 0xf8) & 0xb1) == 0) {
      cVar3 = '\x02';
    }
    else {
      cVar3 = '\x01';
    }
    if (((&DAT_0036b928)[param_1] == '\0') || ((&DAT_0036c992)[param_1] != cVar3)) {
      if ((&DAT_0036c9bc)[param_1] == '\0') {
        return 5;
      }
      if ((&DAT_0036da26)[param_1] != cVar3) {
        return 5;
      }
      puVar5 = &DAT_0036c9b8;
    }
    else {
      puVar5 = &DAT_0036b924;
    }
    puVar5 = puVar5 + param_1;
    if ((puVar5 != (undefined *)0x0) && (puVar5[4] != '\0')) {
      if (*(short *)(param_2 + 0x14) != 0x40) {
        return 1;
      }
      uVar4 = *(uint *)(((uint)auStack_50 & 0xffffe000) + 8);
      if (*(uint *)(param_2 + 0x10) < 0xffffffc0 && *(uint *)(param_2 + 0x10) + 0x40 <= uVar4) {
        uVar4 = 0;
      }
      if (uVar4 != 0) {
        __memzero(auStack_50,0x40);
        return 2;
      }
      iVar2 = __copy_from_user(auStack_50);
      if (iVar2 != 0) {
        return 2;
      }
      if (*(code **)(*(int *)(puVar5 + 0x1018) + 0x50) == (code *)0x0) {
        return 0;
      }
      (**(code **)(*(int *)(puVar5 + 0x1018) + 0x50))(param_1,puVar5,auStack_50);
      return 0;
    }
  }
  return 5;
}

