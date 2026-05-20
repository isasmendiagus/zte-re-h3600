// module: mt7915.ko
// function: wlan_config_get_vht_max_mpdu_len @ 0x106a74
// size: 12 bytes
//

undefined1 wlan_config_get_vht_max_mpdu_len(int param_1)

{
  return *(undefined1 *)(*(int *)(param_1 + 0xb10) + 0x62);
}

