// module: mt7915.ko
// function: wlan_config_get_ht_protect_en @ 0x106828
// size: 36 bytes
//

undefined1 wlan_config_get_ht_protect_en(int param_1)

{
  if ((param_1 != 0) && (*(int *)(param_1 + 0xb10) != 0)) {
    return *(undefined1 *)(*(int *)(param_1 + 0xb10) + 0x19);
  }
  return 1;
}

