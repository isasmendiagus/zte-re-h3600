// module: mt7915.ko
// function: RTMPSetIndividualHT @ 0x137e40
// size: 1292 bytes
//

void RTMPSetIndividualHT(int param_1,uint param_2)

{
  char *pcVar1;
  int iVar2;
  uint uVar3;
  uint uVar4;
  char *pcVar5;
  char *pcVar6;
  bool bVar7;
  uint local_2c;
  
  if (3 < DebugLevel) {
    printk("%s(): apidx=%d\n","RTMPSetIndividualHT",param_2);
  }
  if (param_2 < 0x30) {
    if (*(char *)(param_1 + 0x286285) != '\x01') {
      bVar7 = param_2 == 1;
      if (param_2 < 2) {
        bVar7 = *(char *)(param_1 + 0x286285) == '\0';
      }
      if (!bVar7) {
        return;
      }
      iVar2 = param_1 + param_2 * 0x2137b0;
      pcVar5 = &DAT_0036db58 + param_1 + param_2 * 0x2137b0;
      local_2c = *(uint *)(&DAT_0036dccc + iVar2);
      pcVar6 = &DAT_0036e3e9 + iVar2;
      uVar4 = (byte)(&DAT_0036e406)[iVar2] & 0x7f;
      pcVar1 = pcVar5;
      if (pcVar5 == (char *)0x0) {
        return;
      }
      goto LAB_00137fc0;
    }
    if (param_2 < (byte)"======== Badnode detector =============\nvow_bn_en = <0/1> 0:dieable, 1:enable\nvow_bn_mon_period = <period> ms\nvow_bn_fallback_th = <count>\nvow_bn_per_th = <TX PER>\n======== Airtime counter test =============\nvow_counter_test = <0/1> 0:dieable, 1:enable\nvow_counter_test_period = <period> ms\nvow_counter_test_band = <band>\nvow_counter_test_avgcnt = <average num> sec\nvow_counter_test_target = <wlanidx>\n======== DVT =============\nvow_dvt_en = <0/1> 0:dieable, 1:enable\nvow_monitor_sta = <STA num>\nvow_show_sta = <STA num>\nvow_monitor_bss = <BSS num>\nvow_monitor_mbss = <MBSS num>\nvow_show_mbss = <MBSS num>\nvow_avg_num = <average num> sec\n======== RED ===========\nvow_set_red_en = <0/1> 0:disable, 1:enable\nvow_set_red_show_sta = <STA num>\nvow_set_red_tar_delay = <tarDelay> us\n======== WATF ===========\nvow_watf_en = <0/1> 0:disable, 1:enable\nvow_watf_q = <level>-<quantum> unit 256us\nvow_watf_add_entry = <level>-<Addr>\nvow_watf_del_entry = <Addr>\n"
                        [param_1 + 0xda]) {
      uVar4 = hc_get_chip_bcn_max_num(*(undefined4 *)(param_1 + 0xa797a0));
      bVar7 = 0x1e < param_2;
      if (param_2 < 0x20) {
        bVar7 = uVar4 <= param_2;
      }
      if (!bVar7) {
        pcVar5 = "======== Badnode detector =============\nvow_bn_en = <0/1> 0:dieable, 1:enable\nvow_bn_mon_period = <period> ms\nvow_bn_fallback_th = <count>\nvow_bn_per_th = <TX PER>\n======== Airtime counter test =============\nvow_counter_test = <0/1> 0:dieable, 1:enable\nvow_counter_test_period = <period> ms\nvow_counter_test_band = <band>\nvow_counter_test_avgcnt = <average num> sec\nvow_counter_test_target = <wlanidx>\n======== DVT =============\nvow_dvt_en = <0/1> 0:dieable, 1:enable\nvow_monitor_sta = <STA num>\nvow_show_sta = <STA num>\nvow_monitor_bss = <BSS num>\nvow_monitor_mbss = <MBSS num>\nvow_show_mbss = <MBSS num>\nvow_avg_num = <average num> sec\n======== RED ===========\nvow_set_red_en = <0/1> 0:disable, 1:enable\nvow_set_red_show_sta = <STA num>\nvow_set_red_tar_delay = <tarDelay> us\n======== WATF ===========\nvow_watf_en = <0/1> 0:disable, 1:enable\nvow_watf_q = <level>-<quantum> unit 256us\nvow_watf_add_entry = <level>-<Addr>\nvow_watf_del_entry = <Addr>\n"
                 + param_1 + param_2 * 0x5834 + 0xe0;
        if (pcVar5 == (char *)0x0) {
          return;
        }
        iVar2 = param_1 + param_2 * 0x5834;
        uVar4 = (byte)(&DAT_002b7af6)[iVar2] & 0x7f;
        local_2c = *(uint *)(
                            "======== Badnode detector =============\nvow_bn_en = <0/1> 0:dieable, 1:enable\nvow_bn_mon_period = <period> ms\nvow_bn_fallback_th = <count>\nvow_bn_per_th = <TX PER>\n======== Airtime counter test =============\nvow_counter_test = <0/1> 0:dieable, 1:enable\nvow_counter_test_period = <period> ms\nvow_counter_test_band = <band>\nvow_counter_test_avgcnt = <average num> sec\nvow_counter_test_target = <wlanidx>\n======== DVT =============\nvow_dvt_en = <0/1> 0:dieable, 1:enable\nvow_monitor_sta = <STA num>\nvow_show_sta = <STA num>\nvow_monitor_bss = <BSS num>\nvow_monitor_mbss = <MBSS num>\nvow_show_mbss = <MBSS num>\nvow_avg_num = <average num> sec\n======== RED ===========\nvow_set_red_en = <0/1> 0:disable, 1:enable\nvow_set_red_show_sta = <STA num>\nvow_set_red_tar_delay = <tarDelay> us\n======== WATF ===========\nvow_watf_en = <0/1> 0:disable, 1:enable\nvow_watf_q = <level>-<quantum> unit 256us\nvow_watf_add_entry = <level>-<Addr>\nvow_watf_del_entry = <Addr>\n"
                            + iVar2 + 0x254);
        "%s: avgcnt = %d\n"[iVar2] = '\x01';
        pcVar6 = "%s: per %u.\n" + iVar2 + 1;
        "%s: period = %d\n"[iVar2] = uVar4 == 0x21;
        goto LAB_00137fbc;
      }
    }
LAB_00137f30:
    if (DebugLevel < 0) {
      return;
    }
    pcVar1 = "%s: invalid apidx(%d)\n";
LAB_0013809c:
    printk(pcVar1,"RTMPSetIndividualHT",param_2);
    return;
  }
  uVar4 = param_2 - 0x30 & 0xff;
  if (1 < uVar4) {
    if (DebugLevel < 0) {
      return;
    }
    pcVar1 = "%s: invalid idx(%d)\n";
    param_2 = uVar4;
    goto LAB_0013809c;
  }
  pcVar5 = &DAT_0036db58 + param_1 + uVar4 * 0x2137b0;
  if (pcVar5 == (char *)0x0) {
    return;
  }
  iVar2 = param_1 + uVar4 * 0x2137b0;
  pcVar6 = &DAT_0036e3e9 + iVar2;
  uVar4 = (byte)(&DAT_0036e406)[iVar2] & 0x7f;
  local_2c = *(uint *)(&DAT_0036dccc + iVar2);
  (&DAT_0036e408)[iVar2] = uVar4 == 0x21;
LAB_00137fbc:
  pcVar1 = (char *)0x0;
LAB_00137fc0:
  if (pcVar6 == (char *)0x0) goto LAB_00137f30;
  iVar2 = wlan_operate_get_tx_stream(pcVar5);
  RTMPZeroMemory(pcVar6,0x1c);
  if (2 < DebugLevel) {
    printk("RTMPSetIndividualHT : Desired MCS = %d\n",uVar4);
  }
  if ((iVar2 == 1) && (uVar4 - 8 < 8)) {
    if (1 < DebugLevel) {
      printk("%s: MCS(%d) is invalid in 1S, reset it as MCS_7\n","RTMPSetIndividualHT",uVar4);
    }
    uVar4 = 7;
    uVar3 = wlan_config_get_ht_bw(pcVar5);
  }
  else {
    uVar3 = wlan_config_get_ht_bw(pcVar5);
    if (uVar3 == 0 && uVar4 == 0x20) {
      if (DebugLevel < 2) {
        uVar3 = 0;
        uVar4 = uVar3;
      }
      else {
        uVar3 = 0;
        printk("%s: MCS_32 is only supported in 40-MHz, reset it as MCS_0\n","RTMPSetIndividualHT");
        uVar4 = uVar3;
      }
    }
  }
  if ((((*(char *)(param_1 + 0x286285) != '\0' || pcVar1 == (char *)0x0) ||
       (param_2 != 0 || pcVar1[0x4060] != '\x01')) && (*(char *)(param_1 + 0x795984) != '\0')) &&
     (((local_2c & 0x1e) != 0 && ((local_2c & 0x20) == 0)))) {
    if (DebugLevel < 2) {
      return;
    }
    pcVar1 = "%s : Use legacy rate in WEP/TKIP encryption mode (apidx=%d)\n";
    goto LAB_0013809c;
  }
  if (*(char *)(param_1 + 0x795986) != '\0') {
    if (DebugLevel < 3) {
      return;
    }
    printk("%s : HT is disabled\n","RTMPSetIndividualHT");
    return;
  }
  *pcVar6 = '\x01';
  switch(iVar2) {
  case 1:
    if (uVar4 != 0x21) {
      if (uVar4 < 8) {
        pcVar6[2] = (char)(1 << uVar4);
      }
      break;
    }
    pcVar6[2] = -1;
LAB_001382d8:
    if (uVar3 != 1) goto LAB_00138134;
    goto LAB_001382bc;
  case 2:
    if (uVar4 == 0x21) {
      pcVar6[2] = -1;
      pcVar6[3] = -1;
      goto LAB_001382d8;
    }
    if (uVar4 < 0x10) {
LAB_00138114:
      pcVar6[(uVar4 >> 3) + 2] = (char)(1 << (uVar4 + (uVar4 >> 3) * -8 & 0xff));
    }
    break;
  case 3:
    if (uVar4 == 0x21) {
      pcVar6[2] = -1;
      pcVar6[3] = -1;
      pcVar6[4] = -1;
      goto LAB_001382d8;
    }
    if (uVar4 < 0x18) goto LAB_00138114;
    break;
  case 4:
    if (uVar4 == 0x21) {
      pcVar6[2] = -1;
      pcVar6[3] = -1;
      pcVar6[4] = -1;
      pcVar6[5] = -1;
      goto LAB_001382d8;
    }
    if (uVar4 < 0x20) goto LAB_00138114;
  }
  if ((uVar3 == 1) && (uVar4 - 0x20 < 2)) {
LAB_001382bc:
    pcVar6[6] = '\x01';
  }
LAB_00138134:
  MlmeUpdateHtTxRates(param_1,pcVar5);
  if ((*(ushort *)(pcVar5 + 0x18) & 0x20) != 0) {
    pcVar6[0x12] = '\x01';
    rtmp_set_vht(param_1,pcVar5,pcVar6);
  }
  if (DebugLevel < 3) {
    return;
  }
  printk("DesiredHtPhyInfo HtEn = %d, VhtEn = %d, vht_bw = %d\n",pcVar5[0x891],pcVar5[0x8a3],
         pcVar5[0x8a4]);
  return;
}

