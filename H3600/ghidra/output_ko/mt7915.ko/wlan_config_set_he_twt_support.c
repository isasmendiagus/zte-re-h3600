// module: mt7915.ko
// function: wlan_config_set_he_twt_support @ 0x2063c4
// size: 12 bytes
//

void wlan_config_set_he_twt_support(int param_1,undefined1 param_2)

{
  *(undefined1 *)(*(int *)(param_1 + 0xb10) + 0x70) = param_2;
  return;
}

