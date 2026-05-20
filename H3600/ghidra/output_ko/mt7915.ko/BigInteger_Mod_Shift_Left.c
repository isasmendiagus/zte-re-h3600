// module: mt7915.ko
// function: BigInteger_Mod_Shift_Left @ 0x1febc8
// size: 120 bytes
//

void BigInteger_Mod_Shift_Left
               (undefined4 param_1,uint param_2,undefined4 param_3,undefined4 param_4)

{
  undefined1 local_19;
  undefined4 local_18;
  undefined4 local_14;
  
  local_19 = (undefined1)(1 << (param_2 & 0xff));
  local_18 = 0;
  local_14 = 0;
  BigInteger_Bin2BI(&local_19,1,&local_14);
  BigInteger_Mod_Mul(param_1,local_14,param_3,&local_18);
  BigInteger_Copy(local_18,param_4);
  release_temporal_usage_big_interger(&local_14);
  release_temporal_usage_big_interger(&local_18);
  return;
}

