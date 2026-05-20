// module: mt7915.ko
// function: update_att_from_wdev @ 0x14e2a0
// size: 412 bytes
//

void update_att_from_wdev(int param_1,int param_2)

{
  int iVar1;
  undefined4 uVar2;
  undefined4 uVar3;
  
  wlan_operate_get_ht_bw(param_2);
  wlan_operate_get_vht_bw(param_2);
  iVar1 = wlan_config_get_ext_cha(param_1);
  if (iVar1 == 0xf) {
    uVar2 = wlan_config_get_ext_cha(param_2);
    wlan_config_set_ext_cha(param_1,uVar2);
  }
  uVar2 = wlan_config_get_etxbf(param_2);
  wlan_config_set_etxbf(param_1,uVar2);
  uVar2 = wlan_config_get_itxbf(param_2);
  wlan_config_set_itxbf(param_1,uVar2);
  uVar2 = wlan_config_get_ht_stbc(param_2);
  wlan_config_set_ht_stbc(param_1,uVar2);
  uVar2 = wlan_config_get_ht_ldpc(param_2);
  wlan_config_set_ht_ldpc(param_1,uVar2);
  uVar2 = wlan_config_get_vht_stbc(param_2);
  wlan_config_set_vht_stbc(param_1,uVar2);
  uVar2 = wlan_config_get_vht_ldpc(param_2);
  wlan_config_set_vht_ldpc(param_1,uVar2);
  uVar2 = wlan_config_get_ht_bw(param_2);
  uVar3 = wlan_config_get_vht_bw(param_2);
  wlan_config_set_ht_bw(param_1,uVar2);
  wlan_config_set_vht_bw(param_1,uVar3);
  uVar2 = wlan_config_get_cen_ch_2(param_2);
  wlan_config_set_cen_ch_2(param_1,uVar2);
  uVar2 = wlan_config_get_tx_stream(param_2);
  wlan_config_set_tx_stream(param_1,uVar2);
  uVar2 = wlan_config_get_rx_stream(param_2);
  wlan_config_set_rx_stream(param_1,uVar2);
  uVar2 = wlan_config_get_ba_tx_wsize(param_2);
  uVar3 = wlan_config_get_ba_rx_wsize(param_2);
  wlan_config_set_ba_txrx_wsize(param_1,uVar2,uVar3);
  uVar2 = wlan_config_get_he_twt_support(param_2);
  wlan_config_set_he_twt_support(param_1,uVar2);
  uVar2 = wlan_config_get_ba_enable(param_2);
  wlan_config_set_ba_enable(param_1,uVar2);
  *(undefined1 *)(param_1 + 0x1a) = *(undefined1 *)(param_2 + 0x1a);
  wlan_config_set_ch_band(param_1,*(undefined2 *)(param_2 + 0x18));
  *(undefined1 *)(param_1 + 0x8d4) = *(undefined1 *)(param_2 + 0x8d4);
  wlan_operate_update_ht_cap(param_1);
  return;
}

