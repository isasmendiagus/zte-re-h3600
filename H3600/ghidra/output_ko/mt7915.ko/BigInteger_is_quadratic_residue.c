// module: mt7915.ko
// function: BigInteger_is_quadratic_residue @ 0x1feeb0
// size: 140 bytes
//

undefined4 BigInteger_is_quadratic_residue(undefined4 param_1,undefined4 param_2,undefined4 param_3)

{
  undefined4 uVar1;
  undefined4 local_20;
  undefined4 local_1c [2];
  
  local_1c[0] = 0;
  local_20 = 0;
  FUN_001fae18(local_1c);
  BigInteger_Copy(param_2,&local_20);
  BigInteger_minus_one(local_20);
  BigInteger_Shift_Right1(local_20,&local_20);
  BigInteger_Montgomery_ExpMod_with_mont(param_1,local_20,param_2,param_3,local_1c);
  uVar1 = BigInteger_is_one(local_1c[0]);
  release_temporal_usage_big_interger(&local_20);
  release_temporal_usage_big_interger(local_1c);
  return uVar1;
}

