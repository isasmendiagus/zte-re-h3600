// module: mt7915.ko
// function: wlan_config_get_rx_stream @ 0x106518
// size: 12 bytes
//

undefined1 wlan_config_get_rx_stream(int param_1)

{
  return *(undefined1 *)(*(int *)(param_1 + 0xb10) + 4);
}

