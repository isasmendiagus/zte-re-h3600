// module: mt7915.ko
// function: BigInteger_Mod_Mul @ 0x1fe150
// size: 92 bytes
//

void BigInteger_Mod_Mul(undefined4 param_1,undefined4 param_2,undefined4 param_3,undefined4 param_4)

{
  undefined4 local_1c;
  
  local_1c = 0;
  FUN_001fae18(&local_1c);
  BigInteger_Mul(param_1,param_2,&local_1c);
  BigInteger_Mod(local_1c,param_3,param_4);
  release_temporal_usage_big_interger(&local_1c);
  return;
}

