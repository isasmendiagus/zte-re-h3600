// module: mt7915.ko
// function: wlan_config_get_vht_sgi @ 0x106a50
// size: 12 bytes
//

undefined1 wlan_config_get_vht_sgi(int param_1)

{
  return *(undefined1 *)(*(int *)(param_1 + 0xb10) + 0x5f);
}

