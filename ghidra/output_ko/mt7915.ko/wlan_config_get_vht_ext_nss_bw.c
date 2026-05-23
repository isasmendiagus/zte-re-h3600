// module: mt7915.ko
// function: wlan_config_get_vht_ext_nss_bw @ 0x106a68
// size: 12 bytes
//

undefined1 wlan_config_get_vht_ext_nss_bw(int param_1)

{
  return *(undefined1 *)(*(int *)(param_1 + 0xb10) + 0x61);
}

