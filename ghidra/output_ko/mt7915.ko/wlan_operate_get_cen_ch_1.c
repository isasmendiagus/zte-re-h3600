// module: mt7915.ko
// function: wlan_operate_get_cen_ch_1 @ 0x10771c
// size: 12 bytes
//

undefined1 wlan_operate_get_cen_ch_1(int param_1)

{
  return *(undefined1 *)(*(int *)(param_1 + 0xb14) + 3);
}

