// module: mt7915.ko
// function: ecc_point_find_by_x @ 0x218cac
// size: 276 bytes
//

undefined4 ecc_point_find_by_x(int param_1,undefined4 param_2,undefined4 param_3,int param_4)

{
  int iVar1;
  undefined4 uVar2;
  int local_1c [2];
  
  local_1c[0] = 0;
  if (3 < DebugLevel) {
    printk("==> %s()\n","ecc_point_find_by_x");
  }
  BigInteger_record_time_begin(0x5f4b00);
  Bignum_Mod_Square(param_2,*(undefined4 *)(param_1 + 4),local_1c);
  Bignum_Mod_Add(local_1c[0],*(undefined4 *)(param_1 + 0xc),*(undefined4 *)(param_1 + 4),local_1c);
  Bignum_Mod_Mul(param_2,local_1c[0],*(undefined4 *)(param_1 + 4),local_1c);
  Bignum_Mod_Add(local_1c[0],*(undefined4 *)(param_1 + 0x10),*(undefined4 *)(param_1 + 4),local_1c);
  iVar1 = Bignum_is_quadratic_residue(local_1c[0],*(undefined4 *)(param_1 + 4));
  if (iVar1 == 0) {
    uVar2 = 0;
  }
  else if (param_4 == 0) {
    uVar2 = 1;
  }
  else {
    Bignum_Mod_Sqrt(local_1c[0],*(undefined4 *)(param_1 + 4),local_1c);
    if (local_1c[0] == 0) {
      Bignum_Free(param_3);
      uVar2 = 0;
    }
    else {
      Bignum_Copy(local_1c[0],param_3);
      uVar2 = 1;
    }
  }
  Bignum_Free(local_1c);
  BigInteger_record_time_end(0x5f4b00);
  return uVar2;
}

