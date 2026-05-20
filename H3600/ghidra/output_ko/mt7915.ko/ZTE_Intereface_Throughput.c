// module: mt7915.ko
// function: ZTE_Intereface_Throughput @ 0x1579a8
// size: 296 bytes
//

void ZTE_Intereface_Throughput(int param_1)

{
  byte bVar1;
  uint uVar2;
  int iVar3;
  uint uVar4;
  uint uVar5;
  uint uVar6;
  uint *puVar7;
  int iVar8;
  int iVar9;
  int iVar10;
  
  bVar1 = "======== Badnode detector =============\nvow_bn_en = <0/1> 0:dieable, 1:enable\nvow_bn_mon_period = <period> ms\nvow_bn_fallback_th = <count>\nvow_bn_per_th = <TX PER>\n======== Airtime counter test =============\nvow_counter_test = <0/1> 0:dieable, 1:enable\nvow_counter_test_period = <period> ms\nvow_counter_test_band = <band>\nvow_counter_test_avgcnt = <average num> sec\nvow_counter_test_target = <wlanidx>\n======== DVT =============\nvow_dvt_en = <0/1> 0:dieable, 1:enable\nvow_monitor_sta = <STA num>\nvow_show_sta = <STA num>\nvow_monitor_bss = <BSS num>\nvow_monitor_mbss = <MBSS num>\nvow_show_mbss = <MBSS num>\nvow_avg_num = <average num> sec\n======== RED ===========\nvow_set_red_en = <0/1> 0:disable, 1:enable\nvow_set_red_show_sta = <STA num>\nvow_set_red_tar_delay = <tarDelay> us\n======== WATF ===========\nvow_watf_en = <0/1> 0:disable, 1:enable\nvow_watf_q = <level>-<quantum> unit 256us\nvow_watf_add_entry = <level>-<Addr>\nvow_watf_del_entry = <Addr>\n"
          [param_1 + 0xda];
  uVar2 = hc_get_chip_bcn_max_num(*(undefined4 *)(param_1 + 0xa797a0));
  if (uVar2 < bVar1) {
    uVar2 = hc_get_chip_bcn_max_num(*(undefined4 *)(param_1 + 0xa797a0));
  }
  else {
    uVar2 = (uint)(byte)"======== Badnode detector =============\nvow_bn_en = <0/1> 0:dieable, 1:enable\nvow_bn_mon_period = <period> ms\nvow_bn_fallback_th = <count>\nvow_bn_per_th = <TX PER>\n======== Airtime counter test =============\nvow_counter_test = <0/1> 0:dieable, 1:enable\nvow_counter_test_period = <period> ms\nvow_counter_test_band = <band>\nvow_counter_test_avgcnt = <average num> sec\nvow_counter_test_target = <wlanidx>\n======== DVT =============\nvow_dvt_en = <0/1> 0:dieable, 1:enable\nvow_monitor_sta = <STA num>\nvow_show_sta = <STA num>\nvow_monitor_bss = <BSS num>\nvow_monitor_mbss = <MBSS num>\nvow_show_mbss = <MBSS num>\nvow_avg_num = <average num> sec\n======== RED ===========\nvow_set_red_en = <0/1> 0:disable, 1:enable\nvow_set_red_show_sta = <STA num>\nvow_set_red_tar_delay = <tarDelay> us\n======== WATF ===========\nvow_watf_en = <0/1> 0:disable, 1:enable\nvow_watf_q = <level>-<quantum> unit 256us\nvow_watf_add_entry = <level>-<Addr>\nvow_watf_del_entry = <Addr>\n"
                        [param_1 + 0xda];
  }
  if (uVar2 == 0) {
    iVar8 = 0;
    iVar9 = 0;
    iVar10 = 0;
  }
  else {
    iVar9 = 0;
    iVar10 = 0;
    puVar7 = (uint *)("[RTMPSetInformation][BandIdx=%d] Ndis802_11OFDM24\n" + param_1 + 0x10);
    iVar8 = 0;
    do {
      while( true ) {
        if ((puVar7[-0x10f5] == 0) || ((*(uint *)(puVar7[-0x10f5] + 0x138) & 1) == 0)) break;
        iVar3 = HcGetBandByWdev(puVar7 + -0x10f5);
        uVar5 = puVar7[5];
        uVar4 = puVar7[1];
        if (iVar3 == 0) {
          iVar10 = iVar10 + puVar7[3];
        }
        else {
          iVar9 = iVar9 + puVar7[3];
        }
        uVar6 = puVar7[2];
        puVar7[2] = puVar7[6];
        uVar6 = puVar7[6] - uVar6;
        *puVar7 = uVar5 - uVar4 >> 7;
        puVar7[1] = uVar5;
        iVar8 = (uVar5 + iVar8 + uVar6) - uVar4;
        puVar7[-1] = uVar6 >> 7;
        puVar7 = puVar7 + 0x160d;
        if (puVar7 == (uint *)("[RTMPSetInformation][BandIdx=%d] Ndis802_11OFDM24\n" +
                              uVar2 * 0x5834 + param_1 + 0x10)) {
          _LANCHOR2 = iVar8;
          DAT_005f3d38 = iVar10;
          DAT_005f3d3c = iVar9;
          return;
        }
      }
      puVar7 = puVar7 + 0x160d;
    } while (puVar7 != (uint *)("[RTMPSetInformation][BandIdx=%d] Ndis802_11OFDM24\n" +
                               uVar2 * 0x5834 + param_1 + 0x10));
  }
  _LANCHOR2 = iVar8;
  DAT_005f3d38 = iVar10;
  DAT_005f3d3c = iVar9;
  return;
}

