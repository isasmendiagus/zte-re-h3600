// module: mt7915.ko
// function: wlan_config_get_he_tx_stbc @ 0x2064d4
// size: 12 bytes
//

undefined1 wlan_config_get_he_tx_stbc(int param_1)

{
  return *(undefined1 *)(*(int *)(param_1 + 0xb10) + 0x65);
}

