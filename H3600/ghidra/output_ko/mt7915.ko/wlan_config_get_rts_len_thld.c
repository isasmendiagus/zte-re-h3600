// module: mt7915.ko
// function: wlan_config_get_rts_len_thld @ 0x1068ac
// size: 36 bytes
//

undefined4 wlan_config_get_rts_len_thld(int param_1)

{
  if ((param_1 != 0) && (*(int *)(param_1 + 0xb10) != 0)) {
    return *(undefined4 *)(*(int *)(param_1 + 0xb10) + 0x28);
  }
  return 0x92b;
}

