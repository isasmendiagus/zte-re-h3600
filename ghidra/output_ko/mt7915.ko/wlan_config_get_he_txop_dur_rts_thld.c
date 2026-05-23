// module: mt7915.ko
// function: wlan_config_get_he_txop_dur_rts_thld @ 0x206510
// size: 12 bytes
//

undefined2 wlan_config_get_he_txop_dur_rts_thld(int param_1)

{
  return *(undefined2 *)(*(int *)(param_1 + 0xb10) + 0x6e);
}

