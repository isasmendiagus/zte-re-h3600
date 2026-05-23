// module: mt7915.ko
// function: wlan_config_set_he_txop_dur_rts_thld @ 0x206354
// size: 16 bytes
//

void wlan_config_set_he_txop_dur_rts_thld(int param_1,undefined2 param_2)

{
  if (*(int *)(param_1 + 0xb10) != 0) {
    *(undefined2 *)(*(int *)(param_1 + 0xb10) + 0x6e) = param_2;
  }
  return;
}

