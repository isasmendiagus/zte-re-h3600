// module: mt7915.ko
// function: wlan_config_set_vht_ldpc @ 0x1069f0
// size: 12 bytes
//

void wlan_config_set_vht_ldpc(int param_1,undefined1 param_2)

{
  *(undefined1 *)(*(int *)(param_1 + 0xb10) + 0x5e) = param_2;
  return;
}

