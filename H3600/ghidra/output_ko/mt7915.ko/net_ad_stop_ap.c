// module: mt7915.ko
// function: net_ad_stop_ap @ 0x25b36c
// size: 292 bytes
//

undefined4 net_ad_stop_ap(int param_1)

{
  byte bVar1;
  int iVar2;
  undefined4 uVar3;
  int iVar4;
  int iVar5;
  int *piVar6;
  undefined1 uStack_21;
  
  iVar2 = RtmpOsGetNetDevPriv(*(undefined4 *)(param_1 + 4));
  if (iVar2 == 0) {
    uVar3 = 0x606;
  }
  else {
    bVar1 = "======== Badnode detector =============\nvow_bn_en = <0/1> 0:dieable, 1:enable\nvow_bn_mon_period = <period> ms\nvow_bn_fallback_th = <count>\nvow_bn_per_th = <TX PER>\n======== Airtime counter test =============\nvow_counter_test = <0/1> 0:dieable, 1:enable\nvow_counter_test_period = <period> ms\nvow_counter_test_band = <band>\nvow_counter_test_avgcnt = <average num> sec\nvow_counter_test_target = <wlanidx>\n======== DVT =============\nvow_dvt_en = <0/1> 0:dieable, 1:enable\nvow_monitor_sta = <STA num>\nvow_show_sta = <STA num>\nvow_monitor_bss = <BSS num>\nvow_monitor_mbss = <MBSS num>\nvow_show_mbss = <MBSS num>\nvow_avg_num = <average num> sec\n======== RED ===========\nvow_set_red_en = <0/1> 0:disable, 1:enable\nvow_set_red_show_sta = <STA num>\nvow_set_red_tar_delay = <tarDelay> us\n======== WATF ===========\nvow_watf_en = <0/1> 0:disable, 1:enable\nvow_watf_q = <level>-<quantum> unit 256us\nvow_watf_add_entry = <level>-<Addr>\nvow_watf_del_entry = <Addr>\n"
            [iVar2 + 0xda];
    uVar3 = net_ad_cfg_queue(param_1,0);
    if (*(char *)(iVar2 + 0x286285) == '\x01') {
      iVar4 = hc_get_chip_bcn_max_num(*(undefined4 *)(iVar2 + 0xa797a0));
      if (iVar4 < (int)(uint)bVar1) {
        hc_get_chip_bcn_max_num(*(undefined4 *)(iVar2 + 0xa797a0));
      }
      piVar6 = (int *)("%s: Allocate memory fail!!!\n" + iVar2 + 0xc);
      iVar4 = 1;
      while( true ) {
        iVar5 = hc_get_chip_bcn_max_num(*(undefined4 *)(iVar2 + 0xa797a0));
        if (iVar5 <= iVar4) break;
        if (*piVar6 != 0) {
          piVar6[0x237] = 0;
        }
        piVar6 = piVar6 + 0x160d;
        iVar4 = iVar4 + 1;
      }
    }
    chip_set_hif_dma(iVar2,2,1);
    APStop(iVar2,"======== Badnode detector =============\nvow_bn_en = <0/1> 0:dieable, 1:enable\nvow_bn_mon_period = <period> ms\nvow_bn_fallback_th = <count>\nvow_bn_per_th = <TX PER>\n======== Airtime counter test =============\nvow_counter_test = <0/1> 0:dieable, 1:enable\nvow_counter_test_period = <period> ms\nvow_counter_test_band = <band>\nvow_counter_test_avgcnt = <average num> sec\nvow_counter_test_target = <wlanidx>\n======== DVT =============\nvow_dvt_en = <0/1> 0:dieable, 1:enable\nvow_monitor_sta = <STA num>\nvow_show_sta = <STA num>\nvow_monitor_bss = <BSS num>\nvow_monitor_mbss = <MBSS num>\nvow_show_mbss = <MBSS num>\nvow_avg_num = <average num> sec\n======== RED ===========\nvow_set_red_en = <0/1> 0:disable, 1:enable\nvow_set_red_show_sta = <STA num>\nvow_set_red_tar_delay = <tarDelay> us\n======== WATF ===========\nvow_watf_en = <0/1> 0:disable, 1:enable\nvow_watf_q = <level>-<quantum> unit 256us\nvow_watf_add_entry = <level>-<Addr>\nvow_watf_del_entry = <Addr>\n"
                 + iVar2 + 0xe0,0);
    *(uint *)(iVar2 + 0xa39f84) = *(uint *)(iVar2 + 0xa39f84) & 0xffffffbf;
    RTMPCancelTimer(iVar2 + 0x82910c,&uStack_21);
    *(uint *)(iVar2 + 0xa39f84) = *(uint *)(iVar2 + 0xa39f84) | 4;
  }
  return uVar3;
}

