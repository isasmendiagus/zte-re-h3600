// module: mt7915.ko
// function: wlan_config_set_vht_ext_nss_bw @ 0x106a14
// size: 12 bytes
//

void wlan_config_set_vht_ext_nss_bw(int param_1,undefined1 param_2)

{
  *(undefined1 *)(*(int *)(param_1 + 0xb10) + 0x61) = param_2;
  return;
}

