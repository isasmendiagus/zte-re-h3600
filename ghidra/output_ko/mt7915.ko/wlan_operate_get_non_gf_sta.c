// module: mt7915.ko
// function: wlan_operate_get_non_gf_sta @ 0x107f2c
// size: 24 bytes
//

undefined2 wlan_operate_get_non_gf_sta(int param_1)

{
  undefined2 uVar1;
  
  if (param_1 == 0) {
    return 0;
  }
  uVar1 = 0;
  if (*(int *)(param_1 + 0xb14) != 0) {
    uVar1 = *(undefined2 *)(*(int *)(param_1 + 0xb14) + 0x50);
  }
  return uVar1;
}

