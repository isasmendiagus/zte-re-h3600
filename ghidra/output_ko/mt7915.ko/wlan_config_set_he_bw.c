// module: mt7915.ko
// function: wlan_config_set_he_bw @ 0x206348
// size: 12 bytes
//

void wlan_config_set_he_bw(int param_1,undefined1 param_2)

{
  *(undefined1 *)(*(int *)(param_1 + 0xb10) + 100) = param_2;
  return;
}

