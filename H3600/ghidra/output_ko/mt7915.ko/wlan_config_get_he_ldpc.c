// module: mt7915.ko
// function: wlan_config_get_he_ldpc @ 0x2064ec
// size: 12 bytes
//

undefined1 wlan_config_get_he_ldpc(int param_1)

{
  return *(undefined1 *)(*(int *)(param_1 + 0xb10) + 0x67);
}

