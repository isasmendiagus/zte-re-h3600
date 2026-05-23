// module: mt7915.ko
// function: wlan_config_set_ofdma_direction @ 0x206424
// size: 12 bytes
//

void wlan_config_set_ofdma_direction(int param_1,undefined1 param_2)

{
  *(undefined1 *)(*(int *)(param_1 + 0xb10) + 0x76) = param_2;
  return;
}

