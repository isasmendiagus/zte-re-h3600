// module: mt7915.ko
// function: wlan_config_set_ext_cha @ 0x10661c
// size: 12 bytes
//

void wlan_config_set_ext_cha(int param_1,undefined1 param_2)

{
  *(undefined1 *)(*(int *)(param_1 + 0xb10) + 0x14) = param_2;
  return;
}

