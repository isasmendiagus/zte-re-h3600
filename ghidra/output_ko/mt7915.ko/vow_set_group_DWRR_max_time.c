// module: mt7915.ko
// function: vow_set_group_DWRR_max_time @ 0x4131c
// size: 32 bytes
//

undefined4 vow_set_group_DWRR_max_time(int param_1)

{
  undefined4 uVar1;
  
  if ((*(uint *)(param_1 + 0xa797a8) & 2) == 0) {
    return 0;
  }
  uVar1 = FUN_000403f8();
  return uVar1;
}

