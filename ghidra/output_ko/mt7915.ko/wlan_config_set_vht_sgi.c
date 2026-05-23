// module: mt7915.ko
// function: wlan_config_set_vht_sgi @ 0x1069fc
// size: 12 bytes
//

void wlan_config_set_vht_sgi(int param_1,undefined1 param_2)

{
  *(undefined1 *)(*(int *)(param_1 + 0xb10) + 0x5f) = param_2;
  return;
}

