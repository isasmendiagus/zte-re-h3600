// module: mt7915.ko
// function: wlan_operate_set_frag_thld @ 0x107d90
// size: 28 bytes
//

undefined4 wlan_operate_set_frag_thld(int param_1,undefined4 param_2)

{
  if ((param_1 != 0) && (*(int *)(param_1 + 0xb14) != 0)) {
    *(undefined4 *)(*(int *)(param_1 + 0xb14) + 0x10) = param_2;
  }
  return 0;
}

