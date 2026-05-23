// module: mt7915.ko
// function: wlan_config_set_ofdma_user_cnt @ 0x20640c
// size: 12 bytes
//

void wlan_config_set_ofdma_user_cnt(int param_1,undefined1 param_2)

{
  *(undefined1 *)(*(int *)(param_1 + 0xb10) + 0x74) = param_2;
  return;
}

