// module: mt7915.ko
// function: wlan_operate_get_rts_len_thld @ 0x107f5c
// size: 24 bytes
//

undefined4 wlan_operate_get_rts_len_thld(int param_1)

{
  undefined4 uVar1;
  
  if (param_1 == 0) {
    return 0;
  }
  uVar1 = 0;
  if (*(int *)(param_1 + 0xb14) != 0) {
    uVar1 = *(undefined4 *)(*(int *)(param_1 + 0xb14) + 0x18);
  }
  return uVar1;
}

