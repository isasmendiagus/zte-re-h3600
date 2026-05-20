// module: mt7915.ko
// function: wlan_config_set_rts_len_thld @ 0x1066f8
// size: 16 bytes
//

void wlan_config_set_rts_len_thld(int param_1,undefined4 param_2)

{
  if (*(int *)(param_1 + 0xb10) != 0) {
    *(undefined4 *)(*(int *)(param_1 + 0xb10) + 0x28) = param_2;
  }
  return;
}

