// module: mt7915.ko
// function: wlan_config_get_ofdma_user_cnt @ 0x206534
// size: 12 bytes
//

undefined1 wlan_config_get_ofdma_user_cnt(int param_1)

{
  return *(undefined1 *)(*(int *)(param_1 + 0xb10) + 0x74);
}

