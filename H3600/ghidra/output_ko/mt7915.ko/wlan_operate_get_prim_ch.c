// module: mt7915.ko
// function: wlan_operate_get_prim_ch @ 0x107604
// size: 12 bytes
//

undefined1 wlan_operate_get_prim_ch(int param_1)

{
  return *(undefined1 *)(*(int *)(param_1 + 0xb14) + 1);
}

