// module: mt7915.ko
// function: wlan_config_set_frag_thld @ 0x1066e8
// size: 16 bytes
//

void wlan_config_set_frag_thld(int param_1,undefined4 param_2)

{
  if (*(int *)(param_1 + 0xb10) != 0) {
    *(undefined4 *)(*(int *)(param_1 + 0xb10) + 0x20) = param_2;
  }
  return;
}

