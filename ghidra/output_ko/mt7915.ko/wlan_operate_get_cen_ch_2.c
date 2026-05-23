// module: mt7915.ko
// function: wlan_operate_get_cen_ch_2 @ 0x1076cc
// size: 12 bytes
//

undefined1 wlan_operate_get_cen_ch_2(int param_1)

{
  return *(undefined1 *)(*(int *)(param_1 + 0xb14) + 4);
}

