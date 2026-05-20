// module: mt7915.ko
// function: wlan_config_set_ht_protect_en @ 0x1066c8
// size: 16 bytes
//

void wlan_config_set_ht_protect_en(int param_1,undefined1 param_2)

{
  if (*(int *)(param_1 + 0xb10) != 0) {
    *(undefined1 *)(*(int *)(param_1 + 0xb10) + 0x19) = param_2;
  }
  return;
}

