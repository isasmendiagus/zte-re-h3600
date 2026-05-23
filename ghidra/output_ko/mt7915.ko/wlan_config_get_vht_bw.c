// module: mt7915.ko
// function: wlan_config_get_vht_bw @ 0x106a2c
// size: 12 bytes
//

undefined1 wlan_config_get_vht_bw(int param_1)

{
  return *(undefined1 *)(*(int *)(param_1 + 0xb10) + 0x5c);
}

