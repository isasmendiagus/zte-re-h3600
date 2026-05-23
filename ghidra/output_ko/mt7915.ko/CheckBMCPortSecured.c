// module: mt7915.ko
// function: CheckBMCPortSecured @ 0x19234
// size: 340 bytes
//

void CheckBMCPortSecured(int param_1,int param_2,int param_3)

{
  ushort uVar1;
  int iVar2;
  uint uVar3;
  uint uVar4;
  int iVar5;
  int *piVar6;
  char *pcVar7;
  uint uVar8;
  char cVar9;
  bool bVar10;
  
  uVar8 = (uint)*(byte *)(param_2 + 0xe4);
  uVar1 = *(ushort *)
           (
           "======== Badnode detector =============\nvow_bn_en = <0/1> 0:dieable, 1:enable\nvow_bn_mon_period = <period> ms\nvow_bn_fallback_th = <count>\nvow_bn_per_th = <TX PER>\n======== Airtime counter test =============\nvow_counter_test = <0/1> 0:dieable, 1:enable\nvow_counter_test_period = <period> ms\nvow_counter_test_band = <band>\nvow_counter_test_avgcnt = <average num> sec\nvow_counter_test_target = <wlanidx>\n======== DVT =============\nvow_dvt_en = <0/1> 0:dieable, 1:enable\nvow_monitor_sta = <STA num>\nvow_show_sta = <STA num>\nvow_monitor_bss = <BSS num>\nvow_monitor_mbss = <MBSS num>\nvow_show_mbss = <MBSS num>\nvow_avg_num = <average num> sec\n======== RED ===========\nvow_set_red_en = <0/1> 0:disable, 1:enable\nvow_set_red_show_sta = <STA num>\nvow_set_red_tar_delay = <tarDelay> us\n======== WATF ===========\nvow_watf_en = <0/1> 0:disable, 1:enable\nvow_watf_q = <level>-<quantum> unit 256us\nvow_watf_add_entry = <level>-<Addr>\nvow_watf_del_entry = <Addr>\n"
           + uVar8 * 0x5834 + param_1 + 0xf0);
  uVar3 = hc_get_chip_wtbl_no_matched_idx(*(undefined4 *)(param_1 + 0xa797a0));
  if (uVar1 != uVar3) {
    if (param_3 == 0) {
      piVar6 = (int *)(param_1 + 0xa1d20);
      pcVar7 = (char *)(param_1 + 0x2f762);
      uVar3 = 0;
      while (uVar4 = HcGetMaxStaNum(param_1), uVar3 < uVar4) {
        bVar10 = uVar3 != *(ushort *)(param_2 + 0xe0);
        uVar3 = uVar3 + 1;
        if ((((piVar6 != (int *)0x0 && bVar10) && (*piVar6 == 0x20001)) && (piVar6[0x3f] == 2)) &&
           ((*(byte *)(piVar6 + 0x39) == uVar8 && (*pcVar7 == '\x01')))) goto LAB_000192fc;
        piVar6 = piVar6 + 0x530;
        pcVar7 = pcVar7 + 0x620;
      }
      cVar9 = '\x02';
    }
    else {
LAB_000192fc:
      cVar9 = '\x01';
    }
    iVar2 = DebugLevel;
    iVar5 = uVar8 * 0x5834 + param_1;
    if ("%s: group %d, band %u.\n"[iVar5 + 0x10] != cVar9) {
      *(char *)(param_1 + (uint)*(ushort *)
                                 ("======== WATF LV%d\'s MAC Address List ========\n" + iVar5 + 0x1c
                                 ) * 0x620 + 0x2f762) = cVar9;
      "%s: group %d, band %u.\n"[iVar5 + 0x10] = cVar9;
      if (2 < iVar2) {
        printk("%s: bss_index = %d, wcid = %d, PortSecured = %d\n","CheckBMCPortSecured",uVar8,
               *(undefined2 *)("======== WATF LV%d\'s MAC Address List ========\n" + iVar5 + 0x1c),
               cVar9);
      }
    }
  }
  return;
}

