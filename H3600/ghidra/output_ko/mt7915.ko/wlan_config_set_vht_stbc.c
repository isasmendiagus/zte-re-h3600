// module: mt7915.ko
// function: wlan_config_set_vht_stbc @ 0x1069e4
// size: 12 bytes
//

void wlan_config_set_vht_stbc(int param_1,undefined1 param_2)

{
  *(undefined1 *)(*(int *)(param_1 + 0xb10) + 0x5d) = param_2;
  return;
}

