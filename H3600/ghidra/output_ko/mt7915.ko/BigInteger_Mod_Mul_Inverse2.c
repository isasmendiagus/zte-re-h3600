// module: mt7915.ko
// function: BigInteger_Mod_Mul_Inverse2 @ 0x1fe72c
// size: 124 bytes
//

void BigInteger_Mod_Mul_Inverse2(void)

{
  int iVar1;
  undefined4 local_14;
  
  local_14 = 0;
  bi_op_ti_rec._124_4_ = jiffies;
  FUN_001fced0();
  release_temporal_usage_big_interger(&local_14);
  bi_op_ti_rec._124_4_ = jiffies - bi_op_ti_rec._124_4_;
  if (bi_op_ti_rec._128_4_ != -1) {
    iVar1 = bi_op_ti_rec._128_4_ + 1;
    bi_op_ti_rec._120_4_ =
         __aeabi_uidiv(bi_op_ti_rec._120_4_ * bi_op_ti_rec._128_4_ + bi_op_ti_rec._124_4_,iVar1);
    bi_op_ti_rec._128_4_ = iVar1;
  }
  return;
}

