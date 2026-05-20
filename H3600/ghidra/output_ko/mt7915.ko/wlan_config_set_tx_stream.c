// module: mt7915.ko
// function: wlan_config_set_tx_stream @ 0x1064a8
// size: 12 bytes
//

void wlan_config_set_tx_stream(int param_1,undefined1 param_2)

{
  *(undefined1 *)(*(int *)(param_1 + 0xb10) + 3) = param_2;
  return;
}

