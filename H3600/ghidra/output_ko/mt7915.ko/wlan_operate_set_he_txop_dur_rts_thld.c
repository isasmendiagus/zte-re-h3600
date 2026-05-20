// module: mt7915.ko
// function: wlan_operate_set_he_txop_dur_rts_thld @ 0x206144
// size: 24 bytes
//

undefined4 wlan_operate_set_he_txop_dur_rts_thld(int param_1,undefined4 param_2)

{
  if (param_1 != 0 && *(int *)(param_1 + 0xb14) != 0) {
    *(undefined4 *)(*(int *)(param_1 + 0xb14) + 100) = param_2;
  }
  return 0;
}

