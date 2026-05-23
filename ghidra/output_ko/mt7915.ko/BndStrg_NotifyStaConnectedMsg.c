// module: mt7915.ko
// function: BndStrg_NotifyStaConnectedMsg @ 0x9e70c
// size: 460 bytes
//

void BndStrg_NotifyStaConnectedMsg(int param_1,int param_2)

{
  undefined *puVar1;
  int iVar2;
  int iVar3;
  char cVar4;
  uint uVar5;
  undefined4 *puVar6;
  bool bVar7;
  undefined1 local_58 [4];
  undefined1 local_54;
  undefined1 local_51;
  undefined4 local_4c;
  undefined2 local_48;
  
  uVar5 = (uint)*(byte *)(param_2 + 0xe4);
  iVar2 = hc_get_chip_bcn_max_num(*(undefined4 *)(param_1 + 0xa797a0));
  bVar7 = SBORROW4(uVar5,0x1f);
  iVar3 = uVar5 - 0x1f;
  if (uVar5 < 0x20) {
    bVar7 = SBORROW4(uVar5,iVar2);
    iVar3 = uVar5 - iVar2;
  }
  if ((iVar3 < 0 == bVar7) ||
     ("======== Badnode detector =============\nvow_bn_en = <0/1> 0:dieable, 1:enable\nvow_bn_mon_period = <period> ms\nvow_bn_fallback_th = <count>\nvow_bn_per_th = <TX PER>\n======== Airtime counter test =============\nvow_counter_test = <0/1> 0:dieable, 1:enable\nvow_counter_test_period = <period> ms\nvow_counter_test_band = <band>\nvow_counter_test_avgcnt = <average num> sec\nvow_counter_test_target = <wlanidx>\n======== DVT =============\nvow_dvt_en = <0/1> 0:dieable, 1:enable\nvow_monitor_sta = <STA num>\nvow_show_sta = <STA num>\nvow_monitor_bss = <BSS num>\nvow_monitor_mbss = <MBSS num>\nvow_show_mbss = <MBSS num>\nvow_avg_num = <average num> sec\n======== RED ===========\nvow_set_red_en = <0/1> 0:disable, 1:enable\nvow_set_red_show_sta = <STA num>\nvow_set_red_tar_delay = <tarDelay> us\n======== WATF ===========\nvow_watf_en = <0/1> 0:disable, 1:enable\nvow_watf_q = <level>-<quantum> unit 256us\nvow_watf_add_entry = <level>-<Addr>\nvow_watf_del_entry = <Addr>\n"
      + param_1 + uVar5 * 0x5834 + 0xe0 == (char *)0x0)) {
    if (-1 < DebugLevel) {
      printk(&_LC27,"Get_BndStrgTable",0x36,uVar5);
    }
  }
  else {
    if ((*(ushort *)
          (
          "======== Badnode detector =============\nvow_bn_en = <0/1> 0:dieable, 1:enable\nvow_bn_mon_period = <period> ms\nvow_bn_fallback_th = <count>\nvow_bn_per_th = <TX PER>\n======== Airtime counter test =============\nvow_counter_test = <0/1> 0:dieable, 1:enable\nvow_counter_test_period = <period> ms\nvow_counter_test_band = <band>\nvow_counter_test_avgcnt = <average num> sec\nvow_counter_test_target = <wlanidx>\n======== DVT =============\nvow_dvt_en = <0/1> 0:dieable, 1:enable\nvow_monitor_sta = <STA num>\nvow_show_sta = <STA num>\nvow_monitor_bss = <BSS num>\nvow_monitor_mbss = <MBSS num>\nvow_show_mbss = <MBSS num>\nvow_avg_num = <average num> sec\n======== RED ===========\nvow_set_red_en = <0/1> 0:disable, 1:enable\nvow_set_red_show_sta = <STA num>\nvow_set_red_tar_delay = <tarDelay> us\n======== WATF ===========\nvow_watf_en = <0/1> 0:disable, 1:enable\nvow_watf_q = <level>-<quantum> unit 256us\nvow_watf_add_entry = <level>-<Addr>\nvow_watf_del_entry = <Addr>\n"
          + param_1 + uVar5 * 0x5834 + 0xf8) & 0xb1) == 0) {
      cVar4 = '\x02';
    }
    else {
      cVar4 = '\x01';
    }
    if (((&DAT_0036b928)[param_1] == '\0') || ((&DAT_0036c992)[param_1] != cVar4)) {
      if ((&DAT_0036c9bc)[param_1] == '\0') {
        return;
      }
      if ((&DAT_0036da26)[param_1] != cVar4) {
        return;
      }
      puVar1 = &DAT_0036c9b8;
    }
    else {
      puVar1 = &DAT_0036b924;
    }
    puVar6 = (undefined4 *)(puVar1 + param_1);
    if (((puVar6 != (undefined4 *)0x0) && (*(char *)(puVar6 + 1) != '\0')) &&
       (*(char *)((int)puVar6 + 5) != '\0')) {
      if (*(char *)((int)puVar6 + 0x106e) == '\x01') {
        if (*(char *)((int)puVar6 + 0x1021) != '\0') {
          local_54 = 1;
          goto LAB_0009e84c;
        }
      }
      else if (*(char *)(puVar6 + 0x408) != '\0') {
        iVar3 = (**(code **)(puVar6[0x406] + 0x14))(puVar6,param_2 + 0xec);
        if (iVar3 != 0) {
          *(undefined4 *)(iVar3 + 0x10) = 0;
        }
        local_54 = *(undefined *)((int)puVar6 + 0x106e);
LAB_0009e84c:
        local_4c = *(undefined4 *)(param_2 + 0xec);
        local_48 = *(undefined2 *)(param_2 + 0xf0);
        local_58[0] = 0x21;
        local_51 = RTMPAvgRssi(param_1,param_2 + 0x108);
        RtmpOSWrielessEventSend(*puVar6,1,0x950,0,local_58,0x40);
        return;
      }
    }
  }
  return;
}

