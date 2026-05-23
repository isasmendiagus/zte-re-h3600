// module: mt7915.ko
// function: wlan_operate_get_frag_thld @ 0x1077c0
// size: 36 bytes
//

undefined4 wlan_operate_get_frag_thld(int param_1)

{
  if ((param_1 != 0) && (*(int *)(param_1 + 0xb14) != 0)) {
    return *(undefined4 *)(*(int *)(param_1 + 0xb14) + 0x10);
  }
  return 0x92a;
}

