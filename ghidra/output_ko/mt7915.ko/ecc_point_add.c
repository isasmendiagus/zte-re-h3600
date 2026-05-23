// module: mt7915.ko
// function: ecc_point_add @ 0x218038
// size: 496 bytes
//

void ecc_point_add(undefined4 *param_1,undefined4 *param_2,int param_3,undefined4 param_4)

{
  int iVar1;
  undefined4 local_28;
  undefined4 local_24;
  undefined4 local_20;
  undefined4 local_1c [2];
  
  local_28 = 0;
  local_24 = 0;
  local_20 = 0;
  local_1c[0] = 0;
  if (3 < DebugLevel) {
    printk("==> %s()\n","ecc_point_add");
  }
  BigInteger_record_time_begin(ec_op_ti_rec);
  if (param_2 != (undefined4 *)0x0 && param_1 == (undefined4 *)0x0) {
    ecc_point_copy(param_2,param_4);
    return;
  }
  if (param_1 != (undefined4 *)0x0 && param_2 == (undefined4 *)0x0) {
    ecc_point_copy(param_1,param_4);
    return;
  }
  if (param_1 == (undefined4 *)0x0 && param_2 == (undefined4 *)0x0) {
LAB_00218148:
    ecc_point_free(param_4);
    return;
  }
  if ((param_1[2] == 0) || (param_2[2] == 0)) {
    iVar1 = Bignum_UnsignedCompare((BIGNUM *)*param_1,(BIGNUM *)*param_2);
    if (iVar1 == 0) {
      iVar1 = Bignum_UnsignedCompare((BIGNUM *)param_1[1],(BIGNUM *)param_2[1]);
      if (iVar1 != 0) goto LAB_00218148;
      ecc_point_double(param_1,param_3,param_4);
    }
    else {
      Bignum_Init(&local_24);
      Bignum_Init(&local_20);
      Bignum_Init(local_1c);
      Bignum_Mod_Sub_quick(*param_1,*param_2,*(undefined4 *)(param_3 + 4),&local_24);
      Bignum_Mod_Sub_quick(param_1[1],param_2[1],*(undefined4 *)(param_3 + 4),&local_20);
      Bignum_Mod_Div(local_20,local_24,*(undefined4 *)(param_3 + 4),local_1c);
      local_28 = ecc_point_add_cmm(param_1,param_2,local_1c[0],param_3);
      ecc_point_copy(local_28,param_4);
      Bignum_Free(&local_24);
      Bignum_Free(&local_20);
      Bignum_Free(local_1c);
      ecc_point_free(&local_28);
      BigInteger_record_time_end(ec_op_ti_rec);
    }
  }
  else {
    ecc_point_add_3d(param_1,param_2,param_3,param_4);
  }
  return;
}

