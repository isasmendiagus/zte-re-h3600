// module: mt7915.ko
// function: ApCliAutoConnectBWAdjust @ 0x69e7c
// size: 1688 bytes
//

undefined4 ApCliAutoConnectBWAdjust(int param_1,int param_2,int param_3)

{
  bool bVar1;
  int iVar2;
  int iVar3;
  undefined4 uVar4;
  undefined4 uVar5;
  undefined4 uVar6;
  uint uVar7;
  uint uVar8;
  char *pcVar9;
  int iVar10;
  undefined4 uVar11;
  undefined4 uVar12;
  char *pcVar13;
  ushort uVar14;
  ushort uVar15;
  ushort uVar16;
  uint uVar17;
  ushort uVar18;
  
  if (param_1 == 0 || param_2 == 0) {
    if (param_1 == 0) {
      printk(&_LC38,0x78c);
      dump_stack();
    }
    if (param_2 == 0) {
      printk(&_LC39,0x78d);
      dump_stack();
    }
    if (param_3 != 0) {
      return 0;
    }
LAB_0006a004:
    printk(&_LC40,0x78e);
    dump_stack();
    return 0;
  }
  if (param_3 == 0) goto LAB_0006a004;
  iVar2 = hc_get_chip_cap(*(undefined4 *)(param_1 + 0xa797a0));
  iVar3 = GetStaCfgByWdev(param_1,param_2);
  if (iVar3 == 0) {
    printk(&_LC9,0x794);
    dump_stack();
  }
  if (2 < DebugLevel) {
    printk("BW info of root AP (%s):\n",param_3 + 0x95);
  }
  uVar4 = wlan_operate_get_ht_bw(param_2);
  uVar5 = wlan_operate_get_vht_bw(param_2);
  uVar6 = wlan_operate_get_ext_cha(param_2);
  uVar14 = *(ushort *)(param_2 + 0x18);
  uVar18 = (ushort)(*(char *)(param_2 + 0x1a) != *(char *)(param_3 + 0xc));
  uVar15 = uVar18;
  if (((uVar14 & 0x18) == 0) || ((*(uint *)(param_3 + 0xac8) & 2) == 0)) {
LAB_00069f9c:
    if (((uVar14 & 0x20) != 0) && ((*(uint *)(iVar2 + 0x2c) & 0xc00) != 0)) {
      uVar14 = 0;
      goto LAB_00069fb4;
    }
  }
  else {
    uVar7 = wlan_operate_get_ht_bw(param_2);
    iVar3 = wlan_config_get_ht_bw(param_2);
    uVar8 = wlan_operate_get_ext_cha(param_2);
    uVar17 = (uint)*(byte *)(param_3 + 0x50);
    if ((uVar18 == 0) && ((uVar17 & 3) == uVar8)) {
      uVar8 = (uVar17 << 0x1d) >> 0x1f;
      if (uVar7 == uVar8) {
        uVar14 = *(ushort *)(param_2 + 0x18);
        goto LAB_00069f9c;
      }
    }
    else {
      uVar8 = (uVar17 << 0x1d) >> 0x1f;
    }
    if (uVar8 == 1) {
      if (uVar7 == 0) {
        if ((&DAT_003678fc)[param_1] != '\x01') {
LAB_00069f94:
          uVar14 = *(ushort *)(param_2 + 0x18);
          uVar15 = 1;
          goto LAB_00069f9c;
        }
        if ("======== Badnode detector =============\nvow_bn_en = <0/1> 0:dieable, 1:enable\nvow_bn_mon_period = <period> ms\nvow_bn_fallback_th = <count>\nvow_bn_per_th = <TX PER>\n======== Airtime counter test =============\nvow_counter_test = <0/1> 0:dieable, 1:enable\nvow_counter_test_period = <period> ms\nvow_counter_test_band = <band>\nvow_counter_test_avgcnt = <average num> sec\nvow_counter_test_target = <wlanidx>\n======== DVT =============\nvow_dvt_en = <0/1> 0:dieable, 1:enable\nvow_monitor_sta = <STA num>\nvow_show_sta = <STA num>\nvow_monitor_bss = <BSS num>\nvow_monitor_mbss = <MBSS num>\nvow_show_mbss = <MBSS num>\nvow_avg_num = <average num> sec\n======== RED ===========\nvow_set_red_en = <0/1> 0:disable, 1:enable\nvow_set_red_show_sta = <STA num>\nvow_set_red_tar_delay = <tarDelay> us\n======== WATF ===========\nvow_watf_en = <0/1> 0:disable, 1:enable\nvow_watf_q = <level>-<quantum> unit 256us\nvow_watf_add_entry = <level>-<Addr>\nvow_watf_del_entry = <Addr>\n"
            [param_1 + 0xda] != '\0') {
          uVar7 = 0;
          do {
            pcVar9 = "======== Badnode detector =============\nvow_bn_en = <0/1> 0:dieable, 1:enable\nvow_bn_mon_period = <period> ms\nvow_bn_fallback_th = <count>\nvow_bn_per_th = <TX PER>\n======== Airtime counter test =============\nvow_counter_test = <0/1> 0:dieable, 1:enable\nvow_counter_test_period = <period> ms\nvow_counter_test_band = <band>\nvow_counter_test_avgcnt = <average num> sec\nvow_counter_test_target = <wlanidx>\n======== DVT =============\nvow_dvt_en = <0/1> 0:dieable, 1:enable\nvow_monitor_sta = <STA num>\nvow_show_sta = <STA num>\nvow_monitor_bss = <BSS num>\nvow_monitor_mbss = <MBSS num>\nvow_show_mbss = <MBSS num>\nvow_avg_num = <average num> sec\n======== RED ===========\nvow_set_red_en = <0/1> 0:disable, 1:enable\nvow_set_red_show_sta = <STA num>\nvow_set_red_tar_delay = <tarDelay> us\n======== WATF ===========\nvow_watf_en = <0/1> 0:disable, 1:enable\nvow_watf_q = <level>-<quantum> unit 256us\nvow_watf_add_entry = <level>-<Addr>\nvow_watf_del_entry = <Addr>\n"
                     + uVar7 * 0x5834 + param_1 + 0xe0;
            iVar3 = HcGetBandByWdev(pcVar9);
            iVar10 = HcGetBandByWdev(param_2);
            if (iVar3 == iVar10) {
              wlan_config_set_ht_bw(pcVar9,((uint)*(byte *)(param_3 + 0x50) << 0x1d) >> 0x1f);
              wlan_config_set_ext_cha(pcVar9,*(byte *)(param_3 + 0x50) & 3);
            }
            uVar7 = uVar7 + 1 & 0xff;
          } while (uVar7 < (byte)"======== Badnode detector =============\nvow_bn_en = <0/1> 0:dieable, 1:enable\nvow_bn_mon_period = <period> ms\nvow_bn_fallback_th = <count>\nvow_bn_per_th = <TX PER>\n======== Airtime counter test =============\nvow_counter_test = <0/1> 0:dieable, 1:enable\nvow_counter_test_period = <period> ms\nvow_counter_test_band = <band>\nvow_counter_test_avgcnt = <average num> sec\nvow_counter_test_target = <wlanidx>\n======== DVT =============\nvow_dvt_en = <0/1> 0:dieable, 1:enable\nvow_monitor_sta = <STA num>\nvow_show_sta = <STA num>\nvow_monitor_bss = <BSS num>\nvow_monitor_mbss = <MBSS num>\nvow_show_mbss = <MBSS num>\nvow_avg_num = <average num> sec\n======== RED ===========\nvow_set_red_en = <0/1> 0:disable, 1:enable\nvow_set_red_show_sta = <STA num>\nvow_set_red_tar_delay = <tarDelay> us\n======== WATF ===========\nvow_watf_en = <0/1> 0:disable, 1:enable\nvow_watf_q = <level>-<quantum> unit 256us\nvow_watf_add_entry = <level>-<Addr>\nvow_watf_del_entry = <Addr>\n"
                                 [param_1 + 0xda]);
          uVar17 = (uint)*(byte *)(param_3 + 0x50);
        }
        wlan_config_set_ht_bw(param_2,(uVar17 << 0x1d) >> 0x1f);
        wlan_operate_set_ht_bw
                  (param_2,((uint)*(byte *)(param_3 + 0x50) << 0x1d) >> 0x1f,
                   *(byte *)(param_3 + 0x50) & 3);
        wlan_config_set_ext_cha(param_2,*(byte *)(param_3 + 0x50) & 3);
      }
      else {
        if (iVar3 != 1) goto LAB_00069f94;
        if ("======== Badnode detector =============\nvow_bn_en = <0/1> 0:dieable, 1:enable\nvow_bn_mon_period = <period> ms\nvow_bn_fallback_th = <count>\nvow_bn_per_th = <TX PER>\n======== Airtime counter test =============\nvow_counter_test = <0/1> 0:dieable, 1:enable\nvow_counter_test_period = <period> ms\nvow_counter_test_band = <band>\nvow_counter_test_avgcnt = <average num> sec\nvow_counter_test_target = <wlanidx>\n======== DVT =============\nvow_dvt_en = <0/1> 0:dieable, 1:enable\nvow_monitor_sta = <STA num>\nvow_show_sta = <STA num>\nvow_monitor_bss = <BSS num>\nvow_monitor_mbss = <MBSS num>\nvow_show_mbss = <MBSS num>\nvow_avg_num = <average num> sec\n======== RED ===========\nvow_set_red_en = <0/1> 0:disable, 1:enable\nvow_set_red_show_sta = <STA num>\nvow_set_red_tar_delay = <tarDelay> us\n======== WATF ===========\nvow_watf_en = <0/1> 0:disable, 1:enable\nvow_watf_q = <level>-<quantum> unit 256us\nvow_watf_add_entry = <level>-<Addr>\nvow_watf_del_entry = <Addr>\n"
            [param_1 + 0xda] != '\0') {
          uVar7 = 0;
          do {
            iVar3 = HcGetBandByWdev("======== Badnode detector =============\nvow_bn_en = <0/1> 0:dieable, 1:enable\nvow_bn_mon_period = <period> ms\nvow_bn_fallback_th = <count>\nvow_bn_per_th = <TX PER>\n======== Airtime counter test =============\nvow_counter_test = <0/1> 0:dieable, 1:enable\nvow_counter_test_period = <period> ms\nvow_counter_test_band = <band>\nvow_counter_test_avgcnt = <average num> sec\nvow_counter_test_target = <wlanidx>\n======== DVT =============\nvow_dvt_en = <0/1> 0:dieable, 1:enable\nvow_monitor_sta = <STA num>\nvow_show_sta = <STA num>\nvow_monitor_bss = <BSS num>\nvow_monitor_mbss = <MBSS num>\nvow_show_mbss = <MBSS num>\nvow_avg_num = <average num> sec\n======== RED ===========\nvow_set_red_en = <0/1> 0:disable, 1:enable\nvow_set_red_show_sta = <STA num>\nvow_set_red_tar_delay = <tarDelay> us\n======== WATF ===========\nvow_watf_en = <0/1> 0:disable, 1:enable\nvow_watf_q = <level>-<quantum> unit 256us\nvow_watf_add_entry = <level>-<Addr>\nvow_watf_del_entry = <Addr>\n"
                                    + uVar7 * 0x5834 + param_1 + 0xe0);
            iVar10 = HcGetBandByWdev(param_2);
            if (iVar3 == iVar10) {
              wlan_config_set_ext_cha
                        ("======== Badnode detector =============\nvow_bn_en = <0/1> 0:dieable, 1:enable\nvow_bn_mon_period = <period> ms\nvow_bn_fallback_th = <count>\nvow_bn_per_th = <TX PER>\n======== Airtime counter test =============\nvow_counter_test = <0/1> 0:dieable, 1:enable\nvow_counter_test_period = <period> ms\nvow_counter_test_band = <band>\nvow_counter_test_avgcnt = <average num> sec\nvow_counter_test_target = <wlanidx>\n======== DVT =============\nvow_dvt_en = <0/1> 0:dieable, 1:enable\nvow_monitor_sta = <STA num>\nvow_show_sta = <STA num>\nvow_monitor_bss = <BSS num>\nvow_monitor_mbss = <MBSS num>\nvow_show_mbss = <MBSS num>\nvow_avg_num = <average num> sec\n======== RED ===========\nvow_set_red_en = <0/1> 0:disable, 1:enable\nvow_set_red_show_sta = <STA num>\nvow_set_red_tar_delay = <tarDelay> us\n======== WATF ===========\nvow_watf_en = <0/1> 0:disable, 1:enable\nvow_watf_q = <level>-<quantum> unit 256us\nvow_watf_add_entry = <level>-<Addr>\nvow_watf_del_entry = <Addr>\n"
                         + uVar7 * 0x5834 + param_1 + 0xe0,*(byte *)(param_3 + 0x50) & 3);
            }
            uVar7 = uVar7 + 1 & 0xff;
          } while (uVar7 < (byte)"======== Badnode detector =============\nvow_bn_en = <0/1> 0:dieable, 1:enable\nvow_bn_mon_period = <period> ms\nvow_bn_fallback_th = <count>\nvow_bn_per_th = <TX PER>\n======== Airtime counter test =============\nvow_counter_test = <0/1> 0:dieable, 1:enable\nvow_counter_test_period = <period> ms\nvow_counter_test_band = <band>\nvow_counter_test_avgcnt = <average num> sec\nvow_counter_test_target = <wlanidx>\n======== DVT =============\nvow_dvt_en = <0/1> 0:dieable, 1:enable\nvow_monitor_sta = <STA num>\nvow_show_sta = <STA num>\nvow_monitor_bss = <BSS num>\nvow_monitor_mbss = <MBSS num>\nvow_show_mbss = <MBSS num>\nvow_avg_num = <average num> sec\n======== RED ===========\nvow_set_red_en = <0/1> 0:disable, 1:enable\nvow_set_red_show_sta = <STA num>\nvow_set_red_tar_delay = <tarDelay> us\n======== WATF ===========\nvow_watf_en = <0/1> 0:disable, 1:enable\nvow_watf_q = <level>-<quantum> unit 256us\nvow_watf_add_entry = <level>-<Addr>\nvow_watf_del_entry = <Addr>\n"
                                 [param_1 + 0xda]);
          uVar17 = (uint)*(byte *)(param_3 + 0x50);
        }
        wlan_config_set_ext_cha(param_2,uVar17 & 3);
      }
    }
    else {
      if (uVar7 != 1) goto LAB_00069f94;
      wlan_operate_set_ht_bw(param_2,uVar8,0);
    }
    uVar15 = *(ushort *)(param_2 + 0x18) & 0x20;
    if (((*(ushort *)(param_2 + 0x18) & 0x20) == 0) ||
       (uVar15 = 0, (*(uint *)(iVar2 + 0x2c) & 0xc00) == 0)) {
      uVar14 = 1;
      goto LAB_0006a05c;
    }
    uVar14 = 1;
    uVar15 = uVar14;
LAB_00069fb4:
    if ((*(uint *)(param_3 + 0xac8) & 0xc) == 0xc) {
      iVar2 = wlan_operate_get_vht_bw(param_2);
      uVar7 = wlan_config_get_vht_bw(param_2);
      uVar11 = HcGetBandByWdev(param_2);
      pcVar9 = (char *)hc_get_channel_ctrl(*(undefined4 *)(param_1 + 0xa797a0),uVar11);
      iVar3 = check_vht_op_bw(param_3 + 0x7e);
      uVar16 = uVar15 ^ 1;
      if (iVar2 == iVar3) {
        uVar16 = 0;
      }
      if (uVar16 != 0 || uVar15 != 0) {
        switch(iVar3) {
        case 0:
          if (uVar7 != 0) {
LAB_0006a230:
            bVar1 = true;
LAB_0006a1cc:
            if ((byte)pcVar9[0x49c] != 0) {
              uVar8 = 0;
              pcVar13 = pcVar9;
              if (*pcVar9 != *(char *)(param_3 + 0xc)) {
                do {
                  uVar8 = uVar8 + 1;
                  if (uVar8 == (byte)pcVar9[0x49c]) goto LAB_0006a058;
                  pcVar13 = pcVar13 + 0x14;
                } while (*pcVar13 != *(char *)(param_3 + 0xc));
                if (0x3a < (int)uVar8) goto LAB_0006a058;
              }
              if (bVar1) {
                if (0 < DebugLevel) {
                  printk("(%s): Follow BW info of root AP (%s) from vht_bw = %d to %d. (MAX=%d)\n",
                         "ApCliAutoConnectBWAdjust",param_3 + 0x95,iVar2,iVar3,uVar7);
                }
                wlan_operate_set_vht_bw(param_2,iVar3);
              }
              else if ((*(uint *)(pcVar9 + uVar8 * 0x14 + 0x10) & 0x80) != 0) {
                wlan_operate_set_vht_bw(param_2,uVar7);
              }
              wlan_operate_set_cen_ch_2(param_2,*(undefined1 *)(param_3 + 0x80));
            }
LAB_0006a058:
            uVar15 = 1;
            goto LAB_0006a05c;
          }
          break;
        case 1:
          if (1 < uVar7) goto LAB_0006a230;
          break;
        case 2:
          if (uVar7 == 2) {
            bVar1 = false;
            goto LAB_0006a1cc;
          }
          break;
        case 3:
          if (uVar7 == 3) {
            wlan_operate_set_cen_ch_2(param_2,*(undefined1 *)(param_3 + 0x80));
            bVar1 = false;
            goto LAB_0006a1cc;
          }
        }
      }
    }
    if (uVar14 == 1) {
      uVar15 = 0;
      goto LAB_0006a05c;
    }
  }
  if (uVar18 == 0) {
    return 1;
  }
  uVar15 = 0;
  uVar14 = uVar15;
LAB_0006a05c:
  if ((2 < DebugLevel) &&
     (printk("%s:Adjust (%d %d %d)\n\r","ApCliAutoConnectBWAdjust",uVar18,uVar14,uVar15),
     2 < DebugLevel)) {
    uVar11 = wlan_operate_get_ht_bw(param_2);
    uVar12 = wlan_config_get_ht_bw(param_2);
    printk("%s:HT BW:%d to %d. MAX(%d)\n\r","ApCliAutoConnectBWAdjust",uVar4,uVar11,uVar12);
    if (2 < DebugLevel) {
      uVar4 = wlan_operate_get_vht_bw(param_2);
      uVar11 = wlan_config_get_vht_bw(param_2);
      printk("%s:VHT BW:%d to %d. MAX(%d)\n\r","ApCliAutoConnectBWAdjust",uVar5,uVar4,uVar11);
      if (2 < DebugLevel) {
        uVar4 = wlan_operate_get_ext_cha(param_2);
        printk("%s:EXT CH:%d to %d\n\r","ApCliAutoConnectBWAdjust",uVar6,uVar4,uVar11);
      }
    }
  }
  return 2;
}

