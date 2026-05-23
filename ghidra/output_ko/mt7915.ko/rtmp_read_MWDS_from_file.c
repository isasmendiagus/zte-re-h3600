// module: mt7915.ko
// function: rtmp_read_MWDS_from_file @ 0x9ed14
// size: 468 bytes
//

void rtmp_read_MWDS_from_file(int param_1,undefined4 param_2,undefined4 param_3)

{
  bool bVar1;
  bool bVar2;
  int iVar3;
  int iVar4;
  char *pcVar5;
  uint uVar6;
  
  iVar3 = RTMPGetKeyParameter("ApMWDS",param_2,0x100,param_3,1);
  if (((iVar3 != 0) && (iVar3 = rstrtok(param_2,&_LC3), iVar3 != 0)) &&
     ("======== Badnode detector =============\nvow_bn_en = <0/1> 0:dieable, 1:enable\nvow_bn_mon_period = <period> ms\nvow_bn_fallback_th = <count>\nvow_bn_per_th = <TX PER>\n======== Airtime counter test =============\nvow_counter_test = <0/1> 0:dieable, 1:enable\nvow_counter_test_period = <period> ms\nvow_counter_test_band = <band>\nvow_counter_test_avgcnt = <average num> sec\nvow_counter_test_target = <wlanidx>\n======== DVT =============\nvow_dvt_en = <0/1> 0:dieable, 1:enable\nvow_monitor_sta = <STA num>\nvow_show_sta = <STA num>\nvow_monitor_bss = <BSS num>\nvow_monitor_mbss = <MBSS num>\nvow_show_mbss = <MBSS num>\nvow_avg_num = <average num> sec\n======== RED ===========\nvow_set_red_en = <0/1> 0:disable, 1:enable\nvow_set_red_show_sta = <STA num>\nvow_set_red_tar_delay = <tarDelay> us\n======== WATF ===========\nvow_watf_en = <0/1> 0:disable, 1:enable\nvow_watf_q = <level>-<quantum> unit 256us\nvow_watf_add_entry = <level>-<Addr>\nvow_watf_del_entry = <Addr>\n"
      [param_1 + 0xda] != '\0')) {
    uVar6 = 0;
    do {
      iVar4 = simple_strtol(iVar3,0,10);
      iVar3 = DebugLevel;
      "!!! Link UP, Port Not Secured! ignore this set::OID_802_11_BSSID_LIST_SCAN\n"
      [(uint)(byte)(&DAT_003678c8)[param_1 + uVar6] * 0x5834 + param_1 + 0x48] = iVar4 != 0;
      if (2 < iVar3) {
        printk("ApMWDS=%d\n",iVar4);
      }
      iVar3 = rstrtok(0,&_LC3);
      uVar6 = uVar6 + 1 & 0xff;
    } while ((iVar3 != 0) &&
            (uVar6 < (byte)"======== Badnode detector =============\nvow_bn_en = <0/1> 0:dieable, 1:enable\nvow_bn_mon_period = <period> ms\nvow_bn_fallback_th = <count>\nvow_bn_per_th = <TX PER>\n======== Airtime counter test =============\nvow_counter_test = <0/1> 0:dieable, 1:enable\nvow_counter_test_period = <period> ms\nvow_counter_test_band = <band>\nvow_counter_test_avgcnt = <average num> sec\nvow_counter_test_target = <wlanidx>\n======== DVT =============\nvow_dvt_en = <0/1> 0:dieable, 1:enable\nvow_monitor_sta = <STA num>\nvow_show_sta = <STA num>\nvow_monitor_bss = <BSS num>\nvow_monitor_mbss = <MBSS num>\nvow_show_mbss = <MBSS num>\nvow_avg_num = <average num> sec\n======== RED ===========\nvow_set_red_en = <0/1> 0:disable, 1:enable\nvow_set_red_show_sta = <STA num>\nvow_set_red_tar_delay = <tarDelay> us\n======== WATF ===========\nvow_watf_en = <0/1> 0:disable, 1:enable\nvow_watf_q = <level>-<quantum> unit 256us\nvow_watf_add_entry = <level>-<Addr>\nvow_watf_del_entry = <Addr>\n"
                           [param_1 + 0xda]));
  }
  iVar3 = RTMPGetKeyParameter("ApCliMWDS",param_2,0x100,param_3,1);
  if ((iVar3 != 0) && (iVar3 = rstrtok(param_2,&_LC3), iVar3 != 0)) {
    pcVar5 = s__m__d_t_id__x__d__d__m_id__d__ts_00371ab0 + param_1;
    bVar1 = false;
    do {
      iVar3 = simple_strtol(iVar3,0,10);
      *pcVar5 = iVar3 != 0;
      pcVar5 = pcVar5 + 0x2137b0;
      if (2 < DebugLevel) {
        printk("ApCliMWDS=%d\n",iVar3);
      }
      iVar3 = rstrtok(0,&_LC3);
      if (iVar3 == 0) {
        bVar1 = true;
      }
      bVar2 = !bVar1;
      bVar1 = true;
    } while (bVar2);
    return;
  }
  return;
}

