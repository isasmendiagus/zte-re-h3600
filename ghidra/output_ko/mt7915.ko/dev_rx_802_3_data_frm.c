// module: mt7915.ko
// function: dev_rx_802_3_data_frm @ 0xcc968
// size: 208 bytes
//

void dev_rx_802_3_data_frm(int param_1,int param_2)

{
  int iVar1;
  int iVar2;
  byte *pbVar3;
  
  iVar2 = *(int *)(param_2 + 0x1c);
  pbVar3 = *(byte **)(param_2 + 0x10);
  iVar1 = FUN_000c5084();
  if (iVar1 == 0) {
    wlan_dbg_set_last_error(0,1,0x1b1f,"dev_rx_802_3_data_frm");
  }
  else {
    iVar1 = (**(code **)(*(int *)(*(int *)(iVar1 + 8) + 0x904) + 0x70))
                      (param_1,*(int *)(iVar1 + 8),param_2);
    if (iVar1 != 0) {
      return;
    }
  }
  if ((((*(byte *)(iVar2 + 1) & 2) == 0) && ((*pbVar3 & 0x10) != 0)) &&
     ((uint)*(byte *)(param_2 + 0x52) <
      (uint)(byte)"======== Badnode detector =============\nvow_bn_en = <0/1> 0:dieable, 1:enable\nvow_bn_mon_period = <period> ms\nvow_bn_fallback_th = <count>\nvow_bn_per_th = <TX PER>\n======== Airtime counter test =============\nvow_counter_test = <0/1> 0:dieable, 1:enable\nvow_counter_test_period = <period> ms\nvow_counter_test_band = <band>\nvow_counter_test_avgcnt = <average num> sec\nvow_counter_test_target = <wlanidx>\n======== DVT =============\nvow_dvt_en = <0/1> 0:dieable, 1:enable\nvow_monitor_sta = <STA num>\nvow_show_sta = <STA num>\nvow_monitor_bss = <BSS num>\nvow_monitor_mbss = <MBSS num>\nvow_show_mbss = <MBSS num>\nvow_avg_num = <average num> sec\n======== RED ===========\nvow_set_red_en = <0/1> 0:disable, 1:enable\nvow_set_red_show_sta = <STA num>\nvow_set_red_tar_delay = <tarDelay> us\n======== WATF ===========\nvow_watf_en = <0/1> 0:disable, 1:enable\nvow_watf_q = <level>-<quantum> unit 256us\nvow_watf_add_entry = <level>-<Addr>\nvow_watf_del_entry = <Addr>\n"
                  [param_1 + 0xda])) {
    iVar1 = (uint)*(byte *)(param_2 + 0x52) * 0x5834 + param_1;
    *(int *)("[RTMPSetInformation][BandIdx=%d] Ndis802_11OFDM24\n" + iVar1 + 0x30) =
         *(int *)("[RTMPSetInformation][BandIdx=%d] Ndis802_11OFDM24\n" + iVar1 + 0x30) + 1;
    iVar1 = (uint)*(byte *)(param_2 + 0x52) * 0x5834 + param_1;
    *(int *)("[RTMPSetInformation][BandIdx=%d] Ndis802_11OFDM24\n" + iVar1 + 0x2c) =
         *(int *)("[RTMPSetInformation][BandIdx=%d] Ndis802_11OFDM24\n" + iVar1 + 0x2c) + 1;
  }
  RTMPFreeNdisPacket(param_1,*(undefined4 *)(param_2 + 0x38));
  return;
}

