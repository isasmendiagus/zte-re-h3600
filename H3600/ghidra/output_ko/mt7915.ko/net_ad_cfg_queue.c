// module: mt7915.ko
// function: net_ad_cfg_queue @ 0x25b0fc
// size: 512 bytes
//

undefined4 net_ad_cfg_queue(int param_1,int param_2,undefined4 param_3,undefined4 param_4)

{
  byte bVar1;
  int iVar2;
  int iVar3;
  int iVar4;
  int *piVar5;
  int iVar6;
  
  iVar2 = RtmpOsGetNetDevPriv(*(undefined4 *)(param_1 + 4));
  if (iVar2 != 0) {
    bVar1 = "======== Badnode detector =============\nvow_bn_en = <0/1> 0:dieable, 1:enable\nvow_bn_mon_period = <period> ms\nvow_bn_fallback_th = <count>\nvow_bn_per_th = <TX PER>\n======== Airtime counter test =============\nvow_counter_test = <0/1> 0:dieable, 1:enable\nvow_counter_test_period = <period> ms\nvow_counter_test_band = <band>\nvow_counter_test_avgcnt = <average num> sec\nvow_counter_test_target = <wlanidx>\n======== DVT =============\nvow_dvt_en = <0/1> 0:dieable, 1:enable\nvow_monitor_sta = <STA num>\nvow_show_sta = <STA num>\nvow_monitor_bss = <BSS num>\nvow_monitor_mbss = <MBSS num>\nvow_show_mbss = <MBSS num>\nvow_avg_num = <average num> sec\n======== RED ===========\nvow_set_red_en = <0/1> 0:disable, 1:enable\nvow_set_red_show_sta = <STA num>\nvow_set_red_tar_delay = <tarDelay> us\n======== WATF ===========\nvow_watf_en = <0/1> 0:disable, 1:enable\nvow_watf_q = <level>-<quantum> unit 256us\nvow_watf_add_entry = <level>-<Addr>\nvow_watf_del_entry = <Addr>\n"
            [iVar2 + 0xda];
    if (param_2 == 0) {
      iVar4 = *(int *)(*(int *)(iVar2 + 4) + 0x240);
      if (iVar4 == 0) {
        warn_slowpath_null("include/linux/netdevice.h",0xa06);
        printk(&_LC20);
      }
      else {
        _set_bit(0,iVar4 + 0x50);
      }
      if (*(char *)(iVar2 + 0x286285) == '\x01') {
        iVar4 = hc_get_chip_bcn_max_num(*(undefined4 *)(iVar2 + 0xa797a0));
        if (iVar4 < (int)(uint)bVar1) {
          hc_get_chip_bcn_max_num(*(undefined4 *)(iVar2 + 0xa797a0));
        }
        piVar5 = (int *)("%s: Allocate memory fail!!!\n" + iVar2 + 0xc);
        for (iVar4 = 1; iVar3 = hc_get_chip_bcn_max_num(*(undefined4 *)(iVar2 + 0xa797a0)),
            iVar4 < iVar3; iVar4 = iVar4 + 1) {
          if (*piVar5 != 0) {
            iVar3 = *(int *)(*piVar5 + 0x240);
            if (iVar3 == 0) {
              warn_slowpath_null("include/linux/netdevice.h",0xa06);
              printk(&_LC20);
            }
            else {
              _set_bit(0,iVar3 + 0x50);
            }
          }
          piVar5 = piVar5 + 0x160d;
        }
      }
      *(uint *)(iVar2 + 0xa39f84) = *(uint *)(iVar2 + 0xa39f84) | 0x800000;
      chip_set_hif_dma(iVar2,2,0,iVar2 + 0xa39000,param_4);
    }
    else {
      chip_set_hif_dma(iVar2,2,1,
                       "======== Rx Config =============\nvow_rx_counter_clr = <n>\nvow_rx_airtime_en = <0/1> 0:dieable, 1:enable\nvow_rx_ed_offset = <val> 1.024(5b)\nvow_rx_obss_backoff = <val> 1.024(16b)\nvow_rx_wmm_backoff = <WMM set>-<WMM AC>-<val>\nvow_om_wmm_backoff = <WMM AC>-<val>\nvow_repeater_wmm_backoff = <WMM AC>-<val>\nvow_rx_non_qos_backoff = <val>\nvow_rx_bss_wmmset = <MBSS idx>-<0/1/2/3>\nvow_rx_om_wmm_sel = <OM idx>-<val> 0:RX WMM(1to1), 1:OM wmm\n======== Airtime estimator =============\nvow_at_est_en = <0/1> 0:dieable, 1:enable\nvow_at_mon_period = <period> ms\n"
                       + iVar2 + 0xc0,param_4);
      *(uint *)(iVar2 + 0xa39f84) = *(uint *)(iVar2 + 0xa39f84) & 0xff7fffff;
      _clear_bit(0,*(int *)(*(int *)(iVar2 + 4) + 0x240) + 0x50);
      if (*(char *)(iVar2 + 0x286285) == '\x01') {
        iVar4 = hc_get_chip_bcn_max_num(*(undefined4 *)(iVar2 + 0xa797a0));
        if (iVar4 < (int)(uint)bVar1) {
          hc_get_chip_bcn_max_num(*(undefined4 *)(iVar2 + 0xa797a0));
        }
        piVar5 = (int *)("%s: Allocate memory fail!!!\n" + iVar2 + 0xc);
        iVar4 = 1;
        while( true ) {
          iVar3 = hc_get_chip_bcn_max_num(*(undefined4 *)(iVar2 + 0xa797a0));
          iVar6 = iVar4 + 1;
          if (iVar3 <= iVar4) break;
          iVar3 = *piVar5;
          piVar5 = piVar5 + 0x160d;
          iVar4 = iVar6;
          if (iVar3 != 0) {
            _clear_bit(0,*(int *)(iVar3 + 0x240) + 0x50);
          }
        }
      }
    }
    return 0;
  }
  return 0x606;
}

