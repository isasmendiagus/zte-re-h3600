// module: mt7915.ko
// function: BigInteger_Montgomery_ExpMod32 @ 0x1fef3c
// size: 380 bytes
//

void BigInteger_Montgomery_ExpMod32
               (undefined4 param_1,undefined4 param_2,undefined4 param_3,undefined4 param_4)

{
  int iVar1;
  undefined4 local_2c;
  int local_28;
  undefined4 local_24 [2];
  
  local_2c = 0;
  local_28 = 0;
  local_24[0] = 0;
  if (2 < DebugLevel) {
    printk("==> %s()\n","BigInteger_Montgomery_ExpMod32");
  }
  bi_op_ti_rec._136_4_ = jiffies;
  BigInteger_Copy(param_1,&local_2c);
  BigInteger_Copy(param_2,&local_28);
  BigInteger_Bin2BI(&_LANCHOR1,1,local_24);
  while( true ) {
    iVar1 = BigInteger_is_zero(local_28);
    if (iVar1 != 0) break;
    if (((local_28 == 0) || (*(int *)(local_28 + 0x18) == 0)) ||
       ((**(uint **)(local_28 + 0xc) & 1) == 0)) {
      BigInteger_Mod_Mul(local_2c,local_2c);
      BigInteger_Shift_Right1(local_28,&local_28);
    }
    else {
      BigInteger_Mod_Mul(local_24[0],local_2c,param_3,local_24);
      BigInteger_minus_one(local_28);
    }
  }
  BigInteger_Copy(local_24[0],param_4,param_3,&local_2c);
  BigInteger_Free(&local_2c);
  BigInteger_Free(&local_28);
  BigInteger_Free(local_24);
  bi_op_ti_rec._136_4_ = jiffies - bi_op_ti_rec._136_4_;
  if (bi_op_ti_rec._140_4_ != -1) {
    iVar1 = bi_op_ti_rec._140_4_ + 1;
    bi_op_ti_rec._132_4_ =
         __aeabi_uidiv(bi_op_ti_rec._132_4_ * bi_op_ti_rec._140_4_ + bi_op_ti_rec._136_4_,iVar1);
    bi_op_ti_rec._140_4_ = iVar1;
  }
  return;
}

