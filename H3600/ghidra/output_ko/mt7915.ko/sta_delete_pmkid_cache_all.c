// module: mt7915.ko
// function: sta_delete_pmkid_cache_all @ 0x6bd70
// size: 916 bytes
//

void sta_delete_pmkid_cache_all(int param_1,int param_2)

{
  char cVar1;
  int iVar2;
  int iVar3;
  int iVar4;
  uint uVar5;
  char *pcVar6;
  int iVar7;
  char *pcVar8;
  int iVar9;
  int iVar10;
  int iVar11;
  int iVar12;
  
  iVar2 = hc_get_chip_cap(*(undefined4 *)(param_1 + 0xa797a0));
  pcVar6 = "======== Badnode detector =============\nvow_bn_en = <0/1> 0:dieable, 1:enable\nvow_bn_mon_period = <period> ms\nvow_bn_fallback_th = <count>\nvow_bn_per_th = <TX PER>\n======== Airtime counter test =============\nvow_counter_test = <0/1> 0:dieable, 1:enable\nvow_counter_test_period = <period> ms\nvow_counter_test_band = <band>\nvow_counter_test_avgcnt = <average num> sec\nvow_counter_test_target = <wlanidx>\n======== DVT =============\nvow_dvt_en = <0/1> 0:dieable, 1:enable\nvow_monitor_sta = <STA num>\nvow_show_sta = <STA num>\nvow_monitor_bss = <BSS num>\nvow_monitor_mbss = <MBSS num>\nvow_show_mbss = <MBSS num>\nvow_avg_num = <average num> sec\n======== RED ===========\nvow_set_red_en = <0/1> 0:disable, 1:enable\nvow_set_red_show_sta = <STA num>\nvow_set_red_tar_delay = <tarDelay> us\n======== WATF ===========\nvow_watf_en = <0/1> 0:disable, 1:enable\nvow_watf_q = <level>-<quantum> unit 256us\nvow_watf_add_entry = <level>-<Addr>\nvow_watf_del_entry = <Addr>\n"
           + param_1 + 0xd0;
  iVar3 = hc_get_chip_wtbl_max_num(*(undefined4 *)(param_1 + 0xa797a0));
  iVar10 = param_1 + param_2 * 0x2137b0 + 0x580000;
  iVar12 = iVar10 + 0x304;
  _raw_spin_lock_bh(pcVar6);
  iVar7 = iVar10 + 0x1a1;
  if (iVar3 != 0) {
    iVar11 = 0;
    pcVar8 = "pci_sw_int_handler" + param_1;
    iVar9 = 0;
    do {
      cVar1 = pcVar8[0x128];
      iVar9 = iVar9 + 1;
      if (cVar1 != '\0') {
        iVar4 = memcmp(pcVar8 + 0x160,&DAT_0036db73 + param_1 + param_2 * 0x2137b0,6);
        iVar11 = iVar11 + 1;
        if ((iVar4 == 0) && (pcVar8 != (char *)0x0 && cVar1 == '\x01')) {
          _raw_spin_unlock_bh(pcVar6);
          delete_sae_instance(pcVar8);
          _raw_spin_lock_bh(pcVar6);
        }
        if (*(int *)(
                    "======== Badnode detector =============\nvow_bn_en = <0/1> 0:dieable, 1:enable\nvow_bn_mon_period = <period> ms\nvow_bn_fallback_th = <count>\nvow_bn_per_th = <TX PER>\n======== Airtime counter test =============\nvow_counter_test = <0/1> 0:dieable, 1:enable\nvow_counter_test_period = <period> ms\nvow_counter_test_band = <band>\nvow_counter_test_avgcnt = <average num> sec\nvow_counter_test_target = <wlanidx>\n======== DVT =============\nvow_dvt_en = <0/1> 0:dieable, 1:enable\nvow_monitor_sta = <STA num>\nvow_show_sta = <STA num>\nvow_monitor_bss = <BSS num>\nvow_monitor_mbss = <MBSS num>\nvow_show_mbss = <MBSS num>\nvow_avg_num = <average num> sec\n======== RED ===========\nvow_set_red_en = <0/1> 0:disable, 1:enable\nvow_set_red_show_sta = <STA num>\nvow_set_red_tar_delay = <tarDelay> us\n======== WATF ===========\nvow_watf_en = <0/1> 0:disable, 1:enable\nvow_watf_q = <level>-<quantum> unit 256us\nvow_watf_add_entry = <level>-<Addr>\nvow_watf_del_entry = <Addr>\n"
                    + param_1 + 0xb0) == iVar11) break;
      }
      pcVar8 = pcVar8 + 0x188;
    } while (iVar9 != iVar3);
  }
  _raw_spin_unlock_bh(pcVar6);
  do {
    if (iVar12 == 0) {
      if (*(char *)(iVar7 + 0x56) == '\x01') goto LAB_0006bf04;
    }
    else {
      _raw_spin_lock_bh();
      if (*(char *)(iVar7 + 0x56) == '\x01') {
LAB_0006bf04:
        *(undefined1 *)(iVar7 + 0x56) = 0;
        iVar9 = param_1 + param_2 * 0x2137b0;
        if (*(int *)(&DAT_00580300 + iVar9) != 0) {
          *(int *)(&DAT_00580300 + iVar9) = *(int *)(&DAT_00580300 + iVar9) + -1;
        }
        if (iVar12 == 0) goto LAB_0006bed0;
      }
      _raw_spin_unlock_bh(iVar12);
    }
LAB_0006bed0:
    iVar7 = iVar7 + 0x57;
    if (iVar7 == iVar10 + 0x2fd) {
      if (((&DAT_0036790d)[param_1] == '\x01') &&
         (uVar5 = (uint)*(byte *)(iVar2 + 0x14a), uVar5 != 0)) {
        iVar7 = 0;
        iVar10 = 0;
        do {
          iVar12 = *(int *)(&DAT_003687a8 + param_1) + iVar7;
          if ((iVar12 != 0) && (*(char *)(iVar12 + 1) == '\x01')) {
            _raw_spin_lock_bh(pcVar6);
            if (iVar3 != 0) {
              iVar11 = 0;
              iVar9 = 0;
              pcVar8 = "pci_sw_int_handler" + param_1;
              do {
                cVar1 = pcVar8[0x128];
                iVar9 = iVar9 + 1;
                if (cVar1 != '\0') {
                  iVar4 = memcmp(pcVar8 + 0x160,(void *)(iVar12 + 0x83),6);
                  iVar11 = iVar11 + 1;
                  if ((iVar4 == 0) && (pcVar8 != (char *)0x0 && cVar1 == '\x01')) {
                    _raw_spin_unlock_bh(pcVar6);
                    delete_sae_instance(pcVar8);
                    _raw_spin_lock_bh(pcVar6);
                  }
                  if (*(int *)(
                              "======== Badnode detector =============\nvow_bn_en = <0/1> 0:dieable, 1:enable\nvow_bn_mon_period = <period> ms\nvow_bn_fallback_th = <count>\nvow_bn_per_th = <TX PER>\n======== Airtime counter test =============\nvow_counter_test = <0/1> 0:dieable, 1:enable\nvow_counter_test_period = <period> ms\nvow_counter_test_band = <band>\nvow_counter_test_avgcnt = <average num> sec\nvow_counter_test_target = <wlanidx>\n======== DVT =============\nvow_dvt_en = <0/1> 0:dieable, 1:enable\nvow_monitor_sta = <STA num>\nvow_show_sta = <STA num>\nvow_monitor_bss = <BSS num>\nvow_monitor_mbss = <MBSS num>\nvow_show_mbss = <MBSS num>\nvow_avg_num = <average num> sec\n======== RED ===========\nvow_set_red_en = <0/1> 0:disable, 1:enable\nvow_set_red_show_sta = <STA num>\nvow_set_red_tar_delay = <tarDelay> us\n======== WATF ===========\nvow_watf_en = <0/1> 0:disable, 1:enable\nvow_watf_q = <level>-<quantum> unit 256us\nvow_watf_add_entry = <level>-<Addr>\nvow_watf_del_entry = <Addr>\n"
                              + param_1 + 0xb0) == iVar11) break;
                }
                pcVar8 = pcVar8 + 0x188;
              } while (iVar9 != iVar3);
            }
            _raw_spin_unlock_bh(pcVar6);
            iVar9 = iVar12 + 0x414c;
            do {
              _raw_spin_lock_bh(iVar12 + 0x42ac);
              if (*(char *)(iVar9 + 0x56) == '\x01') {
                *(undefined1 *)(iVar9 + 0x56) = 0;
                if (*(int *)(iVar12 + 0x42a8) != 0) {
                  *(int *)(iVar12 + 0x42a8) = *(int *)(iVar12 + 0x42a8) + -1;
                }
              }
              iVar9 = iVar9 + 0x57;
              _raw_spin_unlock_bh(iVar12 + 0x42ac);
            } while (iVar9 != iVar12 + 0x42a8);
            uVar5 = (uint)*(byte *)(iVar2 + 0x14a);
          }
          iVar10 = iVar10 + 1;
          iVar7 = iVar7 + 0x42f4;
        } while (iVar10 < (int)uVar5);
      }
      return;
    }
  } while( true );
}

