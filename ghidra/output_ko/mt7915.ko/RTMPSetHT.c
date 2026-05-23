// module: mt7915.ko
// function: RTMPSetHT @ 0x138360
// size: 680 bytes
//

void RTMPSetHT(int param_1,int param_2,undefined4 param_3)

{
  int iVar1;
  int iVar2;
  int iVar3;
  char cVar4;
  uint uVar5;
  undefined4 uVar6;
  
  iVar1 = wlan_operate_get_ht_cap(param_3);
  iVar2 = hc_get_chip_cap(*(undefined4 *)(param_1 + 0xa797a0));
  iVar3 = CHAN_PropertyCheck(param_1,*(undefined1 *)(param_2 + 0xb),0x30);
  if (iVar3 == 1) {
    *(undefined1 *)(param_2 + 8) = 0;
  }
  else if (*(char *)(param_2 + 6) == '\x03') {
    iVar3 = CHAN_PropertyCheck(param_1,*(undefined1 *)(param_2 + 0xb),0x20);
    if (iVar3 == 1) {
      *(undefined1 *)(param_2 + 6) = 1;
    }
  }
  else if ((*(char *)(param_2 + 6) == '\x01') &&
          (iVar3 = CHAN_PropertyCheck(param_1,*(undefined1 *)(param_2 + 0xb),0x10), iVar3 == 1)) {
    *(undefined1 *)(param_2 + 6) = 3;
  }
  if (2 < DebugLevel) {
    printk("RTMPSetHT : HT_mode(%d), ExtOffset(%d), MCS(%d), BW(%d), STBC(%d), SHORTGI(%d)\n",
           *(undefined1 *)(param_2 + 5),*(undefined1 *)(param_2 + 6),*(undefined1 *)(param_2 + 7),
           *(undefined1 *)(param_2 + 8),*(undefined1 *)(param_2 + 9),*(undefined1 *)(param_2 + 10));
  }
  RTMPZeroMemory(param_1 + 0x795642,1);
  iVar3 = wlan_operate_get_rx_stream(param_3);
  if (iVar3 == 3) {
LAB_001384b4:
    *(undefined1 *)(iVar1 + 5) = 0xff;
LAB_001384bc:
    *(undefined1 *)(iVar1 + 4) = 0xff;
  }
  else {
    if (iVar3 == 4) {
      *(undefined1 *)(iVar1 + 6) = 0xff;
      goto LAB_001384b4;
    }
    if (iVar3 == 2) goto LAB_001384bc;
  }
  *(undefined1 *)(iVar1 + 3) = 0xff;
  if (*(char *)(param_1 + 0x795947) == '\0') {
LAB_001384d8:
    if (*(char *)(param_2 + 8) == '\x01') {
      cVar4 = *(char *)(param_2 + 6);
      *(undefined1 *)(iVar1 + 7) = 1;
      if (cVar4 == '\x03') {
        uVar6 = 3;
      }
      else {
        uVar6 = 1;
      }
      wlan_config_set_ht_bw(param_3,1);
      if (*(byte *)(param_2 + 0xb) < 0xf) {
        *(byte *)(iVar1 + 1) = *(byte *)(iVar1 + 1) | 0x10;
      }
      wlan_operate_set_ht_bw(param_3,1,uVar6);
      cVar4 = *(char *)(iVar2 + 0x96);
      goto joined_r0x00138530;
    }
  }
  else if (*(char *)(param_2 + 8) == '\x01') {
    *(undefined1 *)(param_2 + 8) = 0;
    wlan_config_set_40M_intolerant(param_3);
    goto LAB_001384d8;
  }
  wlan_operate_set_ht_bw(param_3,0,0);
  cVar4 = *(char *)(iVar2 + 0x96);
joined_r0x00138530:
  if (cVar4 != '\0') {
    mt_WrapSetETxBFCap(param_1,param_3,iVar1 + 0x15);
  }
  cVar4 = *(char *)(param_1 + 0x286285);
  if (cVar4 == '\x01') {
    if ("======== Badnode detector =============\nvow_bn_en = <0/1> 0:dieable, 1:enable\nvow_bn_mon_period = <period> ms\nvow_bn_fallback_th = <count>\nvow_bn_per_th = <TX PER>\n======== Airtime counter test =============\nvow_counter_test = <0/1> 0:dieable, 1:enable\nvow_counter_test_period = <period> ms\nvow_counter_test_band = <band>\nvow_counter_test_avgcnt = <average num> sec\nvow_counter_test_target = <wlanidx>\n======== DVT =============\nvow_dvt_en = <0/1> 0:dieable, 1:enable\nvow_monitor_sta = <STA num>\nvow_show_sta = <STA num>\nvow_monitor_bss = <BSS num>\nvow_monitor_mbss = <MBSS num>\nvow_show_mbss = <MBSS num>\nvow_avg_num = <average num> sec\n======== RED ===========\nvow_set_red_en = <0/1> 0:disable, 1:enable\nvow_set_red_show_sta = <STA num>\nvow_set_red_tar_delay = <tarDelay> us\n======== WATF ===========\nvow_watf_en = <0/1> 0:disable, 1:enable\nvow_watf_q = <level>-<quantum> unit 256us\nvow_watf_add_entry = <level>-<Addr>\nvow_watf_del_entry = <Addr>\n"
        [param_1 + 0xda] != '\0') {
      uVar5 = 0;
      do {
        RTMPSetIndividualHT(param_1,uVar5 & 0xff);
        uVar5 = uVar5 + 1;
      } while ((int)uVar5 <
               (int)(uint)(byte)"======== Badnode detector =============\nvow_bn_en = <0/1> 0:dieable, 1:enable\nvow_bn_mon_period = <period> ms\nvow_bn_fallback_th = <count>\nvow_bn_per_th = <TX PER>\n======== Airtime counter test =============\nvow_counter_test = <0/1> 0:dieable, 1:enable\nvow_counter_test_period = <period> ms\nvow_counter_test_band = <band>\nvow_counter_test_avgcnt = <average num> sec\nvow_counter_test_target = <wlanidx>\n======== DVT =============\nvow_dvt_en = <0/1> 0:dieable, 1:enable\nvow_monitor_sta = <STA num>\nvow_show_sta = <STA num>\nvow_monitor_bss = <BSS num>\nvow_monitor_mbss = <MBSS num>\nvow_show_mbss = <MBSS num>\nvow_avg_num = <average num> sec\n======== RED ===========\nvow_set_red_en = <0/1> 0:disable, 1:enable\nvow_set_red_show_sta = <STA num>\nvow_set_red_tar_delay = <tarDelay> us\n======== WATF ===========\nvow_watf_en = <0/1> 0:disable, 1:enable\nvow_watf_q = <level>-<quantum> unit 256us\nvow_watf_add_entry = <level>-<Addr>\nvow_watf_del_entry = <Addr>\n"
                                [param_1 + 0xda]);
    }
    RTMPSetIndividualHT(param_1,0x30);
    RTMPSetIndividualHT(param_1,0x31);
    cVar4 = *(char *)(param_1 + 0x286285);
  }
  if ((cVar4 == '\0') && (uVar5 = 0, *(char *)(param_1 + 0x794ab9) != '\0')) {
    do {
      RTMPSetIndividualHT(param_1,uVar5 & 0xff);
      uVar5 = uVar5 + 1;
    } while ((int)uVar5 < (int)(uint)*(byte *)(param_1 + 0x794ab9));
  }
  dump_ht_cap(param_3);
  return;
}

