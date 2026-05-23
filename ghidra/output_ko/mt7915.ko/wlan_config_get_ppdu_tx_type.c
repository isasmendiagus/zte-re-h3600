// module: mt7915.ko
// function: wlan_config_get_ppdu_tx_type @ 0x206528
// size: 12 bytes
//

undefined1 wlan_config_get_ppdu_tx_type(int param_1)

{
  return *(undefined1 *)(*(int *)(param_1 + 0xb10) + 0x73);
}

