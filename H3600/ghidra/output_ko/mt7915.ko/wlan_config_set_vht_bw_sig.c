// module: mt7915.ko
// function: wlan_config_set_vht_bw_sig @ 0x106a08
// size: 12 bytes
//

void wlan_config_set_vht_bw_sig(int param_1,undefined1 param_2)

{
  *(undefined1 *)(*(int *)(param_1 + 0xb10) + 0x60) = param_2;
  return;
}

