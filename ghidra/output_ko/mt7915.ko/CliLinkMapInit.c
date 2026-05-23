// module: mt7915.ko
// function: CliLinkMapInit @ 0x80d38
// size: 392 bytes
//

void CliLinkMapInit(int param_1)

{
  byte bVar1;
  uint uVar2;
  undefined *puVar3;
  undefined *puVar4;
  byte *pbVar5;
  char *pcVar6;
  undefined *puVar7;
  uint uVar8;
  uint uVar9;
  undefined *puVar10;
  undefined *puVar11;
  bool bVar12;
  
  puVar4 = &DAT_0036db58 + param_1;
  _raw_spin_lock_bh(&DAT_003686a4 + param_1);
  pcVar6 = "======== Badnode detector =============\nvow_bn_en = <0/1> 0:dieable, 1:enable\nvow_bn_mon_period = <period> ms\nvow_bn_fallback_th = <count>\nvow_bn_per_th = <TX PER>\n======== Airtime counter test =============\nvow_counter_test = <0/1> 0:dieable, 1:enable\nvow_counter_test_period = <period> ms\nvow_counter_test_band = <band>\nvow_counter_test_avgcnt = <average num> sec\nvow_counter_test_target = <wlanidx>\n======== DVT =============\nvow_dvt_en = <0/1> 0:dieable, 1:enable\nvow_monitor_sta = <STA num>\nvow_show_sta = <STA num>\nvow_monitor_bss = <BSS num>\nvow_monitor_mbss = <MBSS num>\nvow_show_mbss = <MBSS num>\nvow_avg_num = <average num> sec\n======== RED ===========\nvow_set_red_en = <0/1> 0:disable, 1:enable\nvow_set_red_show_sta = <STA num>\nvow_set_red_tar_delay = <tarDelay> us\n======== WATF ===========\nvow_watf_en = <0/1> 0:disable, 1:enable\nvow_watf_q = <level>-<quantum> unit 256us\nvow_watf_add_entry = <level>-<Addr>\nvow_watf_del_entry = <Addr>\n"
           + param_1 + 0xe0;
  puVar11 = &DAT_003686a8 + param_1;
  puVar10 = &DAT_003686ac + param_1;
  uVar9 = 0;
  puVar7 = puVar4;
  do {
    uVar8 = uVar9 & 0xff;
    uVar2 = hc_get_chip_bcn_max_num(*(undefined4 *)(param_1 + 0xa797a0));
    bVar12 = 0x1e < uVar8;
    if (uVar8 < 0x20) {
      bVar12 = uVar2 <= uVar8;
    }
    if (bVar12) {
      _raw_spin_unlock_bh(&DAT_003686a4 + param_1);
      return;
    }
    if (*(char *)(param_1 + 0x79504d) == '\x01') {
      if ((byte)(&DAT_003678f9)[param_1] != 0) {
        bVar1 = pcVar6[0x1a];
        puVar7 = puVar4 + (uint)(byte)(&DAT_003678f9)[param_1] * 0x2137b0 + -0x2137b0;
        puVar3 = puVar4;
        pbVar5 = &DAT_0036db72 + param_1;
        do {
          if (bVar1 < 0xf) {
            if (*pbVar5 < 0xf) goto LAB_00080e74;
          }
          else if (0xe < *pbVar5) {
LAB_00080e74:
            *(char **)(puVar10 + -4) = pcVar6;
            *(undefined **)(puVar11 + 4) = puVar3;
          }
          pbVar5 = pbVar5 + 0x2137b0;
          if (puVar3 == puVar7) break;
          puVar3 = &DAT_00581308 + (int)(puVar3 + (param_1 - (int)puVar4));
        } while( true );
      }
    }
    else {
      *(char **)(puVar10 + -4) = pcVar6;
      *(undefined **)(puVar11 + 4) = puVar7;
    }
    uVar9 = uVar9 + 1;
    pcVar6 = pcVar6 + 0x5834;
    puVar11 = puVar11 + 8;
    puVar10 = puVar10 + 8;
  } while( true );
}

