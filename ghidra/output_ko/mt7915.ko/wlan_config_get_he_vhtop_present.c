// module: mt7915.ko
// function: wlan_config_get_he_vhtop_present @ 0x2064c8
// size: 12 bytes
//

undefined1 wlan_config_get_he_vhtop_present(int param_1)

{
  return *(undefined1 *)(*(int *)(param_1 + 0xb10) + 0x6a);
}

