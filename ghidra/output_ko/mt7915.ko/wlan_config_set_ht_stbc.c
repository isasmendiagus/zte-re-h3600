// module: mt7915.ko
// function: wlan_config_set_ht_stbc @ 0x106628
// size: 16 bytes
//

void wlan_config_set_ht_stbc(int param_1,undefined1 param_2)

{
  if (*(int *)(param_1 + 0xb10) != 0) {
    *(undefined1 *)(*(int *)(param_1 + 0xb10) + 0x16) = param_2;
  }
  return;
}

