// module: mt7915.ko
// function: wlan_config_get_frag_thld @ 0x10655c
// size: 36 bytes
//

undefined4 wlan_config_get_frag_thld(int param_1)

{
  if ((param_1 != 0) && (*(int *)(param_1 + 0xb10) != 0)) {
    return *(undefined4 *)(*(int *)(param_1 + 0xb10) + 0x20);
  }
  return 0x92a;
}

