// module: mt7915.ko
// function: BigInteger_Mod_Add @ 0x1fe41c
// size: 68 bytes
//

void BigInteger_Mod_Add(undefined4 param_1,undefined4 param_2,undefined4 param_3,undefined4 param_4)

{
  undefined4 local_14;
  
  local_14 = 0;
  BigInteger_Add(param_1,param_2,&local_14);
  BigInteger_Mod(local_14,param_3,param_4);
  release_temporal_usage_big_interger(&local_14);
  return;
}

