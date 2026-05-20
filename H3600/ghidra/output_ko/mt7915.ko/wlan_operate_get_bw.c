// module: mt7915.ko
// function: wlan_operate_get_bw @ 0x1075f8
// size: 12 bytes
//

undefined1 wlan_operate_get_bw(int param_1)

{
  return *(undefined1 *)(*(int *)(param_1 + 0xb14) + 2);
}

