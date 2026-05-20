// module: mt7915.ko
// function: wlan_config_get_vht_ldpc @ 0x106a44
// size: 12 bytes
//

undefined1 wlan_config_get_vht_ldpc(int param_1)

{
  return *(undefined1 *)(*(int *)(param_1 + 0xb10) + 0x5e);
}

