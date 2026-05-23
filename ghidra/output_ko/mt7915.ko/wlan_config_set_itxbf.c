// module: mt7915.ko
// function: wlan_config_set_itxbf @ 0x1064cc
// size: 12 bytes
//

void wlan_config_set_itxbf(int param_1,undefined1 param_2)

{
  *(undefined1 *)(*(int *)(param_1 + 0xb10) + 0xb) = param_2;
  return;
}

