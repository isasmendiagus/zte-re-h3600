// module: mt7915.ko
// function: wlan_config_set_rx_stream @ 0x1064b4
// size: 12 bytes
//

void wlan_config_set_rx_stream(int param_1,undefined1 param_2)

{
  *(undefined1 *)(*(int *)(param_1 + 0xb10) + 4) = param_2;
  return;
}

