// module: mt7915.ko
// function: BigInteger_Mod_Add_quick @ 0x1fe510
// size: 116 bytes
//

void BigInteger_Mod_Add_quick
               (undefined4 param_1,undefined4 param_2,undefined4 param_3,undefined4 param_4)

{
  int iVar1;
  undefined4 local_14;
  
  local_14 = 0;
  BigInteger_Add(param_1,param_2,&local_14);
  iVar1 = BigInteger_UnsignedCompare(local_14,param_3);
  if (-1 < iVar1) {
    BigInteger_Sub(local_14,param_3,param_4);
    release_temporal_usage_big_interger(&local_14);
    return;
  }
  BigInteger_Copy(local_14,param_4);
  release_temporal_usage_big_interger(&local_14);
  return;
}

