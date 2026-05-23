// module: mt7915.ko
// function: wlan_config_get_ofdma_direction @ 0x20654c
// size: 12 bytes
//

undefined1 wlan_config_get_ofdma_direction(int param_1)

{
  return *(undefined1 *)(*(int *)(param_1 + 0xb10) + 0x76);
}

