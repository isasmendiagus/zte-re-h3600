// module: mt7915.ko
// function: wlan_config_get_fixed_mcs @ 0x10653c
// size: 12 bytes
//

undefined1 wlan_config_get_fixed_mcs(int param_1)

{
  return *(undefined1 *)(*(int *)(param_1 + 0xb10) + 0x10);
}

