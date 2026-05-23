// module: mt7915.ko
// function: wlan_config_set_etxbf @ 0x1064c0
// size: 12 bytes
//

void wlan_config_set_etxbf(int param_1,undefined1 param_2)

{
  *(undefined1 *)(*(int *)(param_1 + 0xb10) + 10) = param_2;
  return;
}

