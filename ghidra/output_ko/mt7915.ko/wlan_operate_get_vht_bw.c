// module: mt7915.ko
// function: wlan_operate_get_vht_bw @ 0x1082f0
// size: 12 bytes
//

undefined1 wlan_operate_get_vht_bw(int param_1)

{
  return *(undefined1 *)(*(int *)(param_1 + 0xb14) + 0x52);
}

