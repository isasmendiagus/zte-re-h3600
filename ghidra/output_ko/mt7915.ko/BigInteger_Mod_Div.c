// module: mt7915.ko
// function: BigInteger_Mod_Div @ 0x1ff740
// size: 208 bytes
//

void BigInteger_Mod_Div(undefined4 param_1,undefined4 param_2,undefined4 param_3,undefined4 param_4)

{
  int iVar1;
  int local_24 [2];
  
  local_24[0] = 0;
  bi_op_ti_rec._100_4_ = jiffies;
  BigInteger_Mod_Mul_Inverse(param_2,param_3,local_24);
  if (local_24[0] == 0) {
    release_temporal_usage_big_interger(param_4);
    printk("BigInteger_Mod_Mul_Inverse fail!!\n");
  }
  else {
    BigInteger_Mod_Mul(param_1,local_24[0],param_3,local_24);
    BigInteger_Copy(local_24[0],param_4);
    release_temporal_usage_big_interger(local_24);
    bi_op_ti_rec._100_4_ = jiffies - bi_op_ti_rec._100_4_;
    if (bi_op_ti_rec._104_4_ != -1) {
      iVar1 = bi_op_ti_rec._104_4_ + 1;
      bi_op_ti_rec._96_4_ =
           __aeabi_uidiv(bi_op_ti_rec._96_4_ * bi_op_ti_rec._104_4_ + bi_op_ti_rec._100_4_,iVar1);
      bi_op_ti_rec._104_4_ = iVar1;
    }
  }
  return;
}

