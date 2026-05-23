// module: mt7915.ko
// function: wlan_operate_get_tx_stream @ 0x107728
// size: 12 bytes
//

undefined1 wlan_operate_get_tx_stream(int param_1)

{
  return *(undefined1 *)(*(int *)(param_1 + 0xb14) + 5);
}

