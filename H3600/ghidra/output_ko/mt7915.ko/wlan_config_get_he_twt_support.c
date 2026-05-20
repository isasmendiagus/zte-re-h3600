// module: mt7915.ko
// function: wlan_config_get_he_twt_support @ 0x20651c
// size: 12 bytes
//

undefined1 wlan_config_get_he_twt_support(int param_1)

{
  return *(undefined1 *)(*(int *)(param_1 + 0xb10) + 0x70);
}

