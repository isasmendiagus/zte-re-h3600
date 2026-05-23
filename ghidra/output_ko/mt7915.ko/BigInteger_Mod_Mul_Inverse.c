// module: mt7915.ko
// function: BigInteger_Mod_Mul_Inverse @ 0x1ff504
// size: 560 bytes
//

void BigInteger_Mod_Mul_Inverse(int param_1,int param_2,undefined4 param_3)

{
  int iVar1;
  undefined4 local_3c;
  undefined4 local_38;
  undefined4 local_34;
  undefined4 local_30;
  undefined4 local_2c;
  undefined4 local_28;
  int local_24 [2];
  
  local_3c = 0;
  local_38 = 0;
  local_34 = 0;
  local_30 = 0;
  local_2c = 0;
  local_28 = 0;
  local_24[0] = 0;
  if (2 < DebugLevel) {
    printk("==> %s()\n","BigInteger_Mod_Mul_Inverse");
  }
  bi_op_ti_rec._124_4_ = jiffies;
  BigInteger_Init(&local_3c);
  BigInteger_Init(&local_38);
  if (param_1 == 0) {
    BigInteger_Bin2BI(test,0xc0,&local_3c);
  }
  else {
    BigInteger_Copy(param_2,&local_3c);
  }
  if (param_2 == 0) {
    BigInteger_Bin2BI(test2,0xb,&local_38);
  }
  else {
    BigInteger_Mod(param_1,param_2,&local_38);
  }
  BigInteger_DWtoBI(1,&local_30);
  BigInteger_DWtoBI(0,&local_28);
  BigInteger_DWtoBI(0,&local_2c);
  BigInteger_DWtoBI(1,local_24);
  BigInteger_Euclidean_Div(local_3c,local_38,local_30,local_2c,local_28,local_24[0]);
  iVar1 = BigInteger_is_one(local_38);
  if (iVar1 == 0) {
    if (0 < DebugLevel) {
      printk(&_LC25);
    }
    release_temporal_usage_big_interger(param_3);
  }
  else if ((local_24[0] == 0) || (*(int *)(local_24[0] + 0x1c) != -1)) {
    BigInteger_Copy(local_24[0],param_3);
  }
  else {
    BigInteger_Add(local_24[0],param_2,&local_34);
    BigInteger_Copy(local_34,param_3);
  }
  release_temporal_usage_big_interger(&local_3c);
  release_temporal_usage_big_interger(&local_38);
  release_temporal_usage_big_interger(&local_34);
  release_temporal_usage_big_interger(&local_30);
  release_temporal_usage_big_interger(&local_2c);
  release_temporal_usage_big_interger(&local_28);
  release_temporal_usage_big_interger(local_24);
  bi_op_ti_rec._124_4_ = jiffies - bi_op_ti_rec._124_4_;
  if (bi_op_ti_rec._128_4_ != -1) {
    iVar1 = bi_op_ti_rec._128_4_ + 1;
    bi_op_ti_rec._120_4_ =
         __aeabi_uidiv(bi_op_ti_rec._120_4_ * bi_op_ti_rec._128_4_ + bi_op_ti_rec._124_4_,iVar1);
    bi_op_ti_rec._128_4_ = iVar1;
  }
  return;
}

