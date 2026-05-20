// module: mt7915.ko
// function: wlan_config_get_tx_stream @ 0x10650c
// size: 12 bytes
//

undefined1 wlan_config_get_tx_stream(int param_1)

{
  return *(undefined1 *)(*(int *)(param_1 + 0xb10) + 3);
}

