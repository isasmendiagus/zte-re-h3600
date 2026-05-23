// module: mt7915.ko
// function: BigInteger_Mod_Sub_quick @ 0x1fe584
// size: 100 bytes
//

void BigInteger_Mod_Sub_quick
               (undefined4 param_1,undefined4 param_2,undefined4 param_3,undefined4 param_4)

{
  int local_14;
  
  local_14 = 0;
  BigInteger_Sub(param_1,param_2,&local_14);
  if ((local_14 == 0) || (*(int *)(local_14 + 0x1c) != -1)) {
    BigInteger_Copy(local_14,param_4);
  }
  else {
    BigInteger_Add(local_14,param_3,param_4);
  }
  release_temporal_usage_big_interger(&local_14);
  return;
}

