// module: mt7915.ko
// function: wlan_config_set_ppdu_tx_type @ 0x206400
// size: 12 bytes
//

void wlan_config_set_ppdu_tx_type(int param_1,undefined1 param_2)

{
  *(undefined1 *)(*(int *)(param_1 + 0xb10) + 0x73) = param_2;
  return;
}

