// module: mt7915.ko
// function: BigInteger_Mod_Sqrt @ 0x1ff0f4
// size: 1036 bytes
//

/* WARNING: Restarted to delay deadcode elimination for space: ram */

void BigInteger_Mod_Sqrt(undefined4 param_1,undefined4 param_2,undefined4 param_3,undefined4 param_4
                        )

{
  int iVar1;
  uint uVar2;
  uint uVar3;
  undefined4 *local_6c;
  undefined4 *local_54;
  int local_4c;
  undefined4 local_48;
  undefined4 local_44;
  undefined4 local_40;
  undefined4 local_3c;
  undefined4 local_38;
  undefined4 local_34;
  undefined4 local_30;
  undefined4 local_2c [2];
  
  local_4c = 0;
  local_48 = 0;
  local_44 = 0;
  local_40 = 0;
  local_3c = 0;
  local_38 = 0;
  local_34 = 0;
  local_30 = 0;
  local_2c[0] = 0;
  if (2 < DebugLevel) {
    printk("==> %s()\n","BigInteger_Mod_Sqrt");
  }
  bi_op_ti_rec._112_4_ = jiffies;
  iVar1 = BigInteger_is_quadratic_residue(param_1,param_2,param_3);
  if (iVar1 == 0) {
    release_temporal_usage_big_interger(param_4);
    return;
  }
  BigInteger_Copy(param_2,&local_4c);
  uVar2 = 0;
  BigInteger_minus_one(local_4c);
  while (((local_4c == 0 || (*(int *)(local_4c + 0x18) == 0)) ||
         ((**(uint **)(local_4c + 0xc) & 1) == 0))) {
    uVar2 = uVar2 + 1;
    BigInteger_Shift_Right1(local_4c,&local_4c);
  }
  BigInteger_Copy(local_4c,&local_48);
  BigInteger_Init(&local_44);
  BigInteger_Copy(local_48,&local_4c);
  BigInteger_plus_one(local_4c);
  BigInteger_Shift_Right1(local_4c,&local_4c);
  BigInteger_Montgomery_ExpMod_with_mont(param_1,local_4c,param_2,param_3,&local_44);
  BigInteger_Init(&local_40);
  BigInteger_Montgomery_ExpMod_with_mont(param_1,local_48,param_2,param_3,&local_40);
  iVar1 = BigInteger_is_one(local_40);
  if (iVar1 == 0) {
    BigInteger_Init(&local_3c);
    BigInteger_Init(&local_38);
    BigInteger_DWtoBI(1,&local_38);
    BigInteger_Copy(param_2,&local_4c);
    BigInteger_minus_one(local_4c);
    BigInteger_Shift_Right1(local_4c,&local_4c);
    do {
      BigInteger_plus_one(local_38);
      BigInteger_Montgomery_ExpMod_with_mont(local_38,local_4c,param_2,param_3,&local_30);
      BigInteger_plus_one(local_30);
      iVar1 = BigInteger_UnsignedCompare(local_30,param_2);
    } while (iVar1 != 0);
    BigInteger_Montgomery_ExpMod_with_mont(local_38,local_48,param_2,param_3,&local_3c);
    BigInteger_DWtoBI(1,&local_34);
    while (iVar1 = BigInteger_is_one(local_40), iVar1 == 0) {
      BigInteger_Copy(local_40,&local_30);
      uVar3 = 1;
      if (1 < uVar2) {
        while( true ) {
          BigInteger_Mod_Mul(local_30,local_30,param_2,&local_30);
          iVar1 = BigInteger_is_one(local_30);
          if (iVar1 != 0) break;
          uVar3 = uVar3 + 1;
          if (uVar3 == uVar2) goto LAB_001ff4d4;
        }
      }
      if (uVar3 == uVar2) {
LAB_001ff4d4:
        printk(&_LC24);
        BigInteger_Free(param_4);
        goto LAB_001ff42c;
      }
      BigInteger_Shift_Left(local_34,(uVar2 - 1) - uVar3,&local_30);
      BigInteger_Montgomery_ExpMod_with_mont(local_3c,local_30,param_2,param_3,local_2c);
      BigInteger_Mod_Mul(local_44,local_2c[0],param_2,&local_44);
      BigInteger_Mod_Mul(local_2c[0],local_2c[0],param_2,&local_3c);
      BigInteger_Mod_Mul(local_40,local_3c,param_2,&local_40);
      uVar2 = uVar3;
    }
  }
  BigInteger_Copy(param_1,&local_4c);
  BigInteger_Copy(local_44,param_4);
LAB_001ff42c:
  local_54 = &local_34;
  local_6c = local_2c;
  release_temporal_usage_big_interger(&local_4c);
  release_temporal_usage_big_interger(&local_48);
  release_temporal_usage_big_interger(&local_44);
  release_temporal_usage_big_interger(&local_40);
  release_temporal_usage_big_interger(local_54);
  release_temporal_usage_big_interger(&local_30);
  release_temporal_usage_big_interger(local_6c);
  release_temporal_usage_big_interger(&local_3c);
  release_temporal_usage_big_interger(&local_38);
  bi_op_ti_rec._112_4_ = jiffies - bi_op_ti_rec._112_4_;
  if (bi_op_ti_rec._116_4_ != -1) {
    iVar1 = bi_op_ti_rec._116_4_ + 1;
    bi_op_ti_rec._108_4_ =
         __aeabi_uidiv(bi_op_ti_rec._108_4_ * bi_op_ti_rec._116_4_ + bi_op_ti_rec._112_4_,iVar1);
    bi_op_ti_rec._116_4_ = iVar1;
  }
  return;
}

