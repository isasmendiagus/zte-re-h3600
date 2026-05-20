// module: mt7915.ko
// function: wlan_operate_set_non_gf_sta @ 0x107c40
// size: 28 bytes
//

undefined4 wlan_operate_set_non_gf_sta(int param_1,undefined2 param_2)

{
  if ((param_1 != 0) && (*(int *)(param_1 + 0xb14) != 0)) {
    *(undefined2 *)(*(int *)(param_1 + 0xb14) + 0x50) = param_2;
  }
  return 0;
}

