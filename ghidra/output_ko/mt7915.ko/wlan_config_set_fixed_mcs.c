// module: mt7915.ko
// function: wlan_config_set_fixed_mcs @ 0x1064d8
// size: 12 bytes
//

void wlan_config_set_fixed_mcs(int param_1,undefined1 param_2)

{
  *(undefined1 *)(*(int *)(param_1 + 0xb10) + 0x10) = param_2;
  return;
}

