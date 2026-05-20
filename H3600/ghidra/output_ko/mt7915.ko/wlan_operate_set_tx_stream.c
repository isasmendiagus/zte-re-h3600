// module: mt7915.ko
// function: wlan_operate_set_tx_stream @ 0x1076ac
// size: 16 bytes
//

undefined4 wlan_operate_set_tx_stream(int param_1,undefined1 param_2)

{
  *(undefined1 *)(*(int *)(param_1 + 0xb14) + 5) = param_2;
  return 0;
}

