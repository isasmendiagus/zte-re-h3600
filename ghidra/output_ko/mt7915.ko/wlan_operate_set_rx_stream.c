// module: mt7915.ko
// function: wlan_operate_set_rx_stream @ 0x1076bc
// size: 16 bytes
//

undefined4 wlan_operate_set_rx_stream(int param_1,undefined1 param_2)

{
  *(undefined1 *)(*(int *)(param_1 + 0xb14) + 6) = param_2;
  return 0;
}

