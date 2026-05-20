// module: mt7915.ko
// function: BigInteger_Montgomery_MulMod @ 0x1fd224
// size: 256 bytes
//

void BigInteger_Montgomery_MulMod
               (undefined4 param_1,undefined4 param_2,undefined4 param_3,undefined4 param_4,
               undefined4 param_5,int *param_6)

{
  int iVar1;
  undefined4 local_24;
  undefined4 local_20;
  undefined4 local_1c [2];
  
  local_24 = 0;
  local_20 = 0;
  local_1c[0] = 0;
  if (*param_6 == 0) {
    BigInteger_Init(param_6);
  }
  BigInteger_Mul(param_1,param_2,&local_24);
  BigInteger_Mul(local_24,param_4,&local_20);
  FUN_001fb6a8(local_20,param_5,param_6,local_1c);
  BigInteger_Mul(local_1c[0],param_3,param_6);
  BigInteger_Add(local_24,*param_6,local_1c);
  FUN_001fb6a8(local_1c[0],param_5,&local_20,param_6);
  iVar1 = BigInteger_UnsignedCompare(local_20,param_3);
  if (iVar1 < 0) {
    BigInteger_Copy(local_20,param_6);
  }
  else {
    BigInteger_Sub(local_20,param_3,param_6);
  }
  release_temporal_usage_big_interger(&local_24);
  release_temporal_usage_big_interger(&local_20);
  release_temporal_usage_big_interger(local_1c);
  return;
}

