// module: mt7915.ko
// function: BigInteger_Euclidean_Div @ 0x1fe5e8
// size: 320 bytes
//

void BigInteger_Euclidean_Div
               (undefined4 param_1,undefined4 param_2,undefined4 param_3,undefined4 param_4,
               undefined4 param_5,undefined4 param_6)

{
  int iVar1;
  undefined4 local_28;
  undefined4 local_24;
  undefined4 local_20;
  undefined4 local_1c;
  undefined4 local_18;
  undefined4 local_14;
  undefined4 local_10;
  undefined4 local_c;
  
  local_18 = 0;
  local_14 = 0;
  local_10 = 0;
  local_c = 0;
  local_28 = param_4;
  local_24 = param_3;
  local_20 = param_2;
  local_1c = param_1;
  if (2 < DebugLevel) {
    printk("==> %s()\n","BigInteger_Euclidean_Div");
  }
  while (iVar1 = BigInteger_is_one(local_20), iVar1 == 0) {
    iVar1 = BigInteger_is_zero(local_20);
    if (iVar1 != 0) break;
    BigInteger_Div(local_1c,local_20,&local_18,&local_14);
    BigInteger_Mul(param_5,local_18,&local_c);
    BigInteger_Sub(local_24,local_c,&local_10);
    BigInteger_Copy(param_5,&local_24);
    BigInteger_Copy(local_10,&param_5);
    BigInteger_Mul(param_6,local_18,&local_c);
    BigInteger_Sub(local_28,local_c,&local_10);
    BigInteger_Copy(param_6,&local_28);
    BigInteger_Copy(local_10,&param_6);
    BigInteger_Copy(local_20,&local_1c);
    BigInteger_Copy(local_14,&local_20);
  }
  release_temporal_usage_big_interger(&local_18);
  release_temporal_usage_big_interger(&local_14);
  release_temporal_usage_big_interger(&local_10);
  release_temporal_usage_big_interger(&local_c);
  return;
}

