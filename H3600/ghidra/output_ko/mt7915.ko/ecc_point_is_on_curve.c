// module: mt7915.ko
// function: ecc_point_is_on_curve @ 0x218934
// size: 356 bytes
//

bool ecc_point_is_on_curve(int param_1,undefined4 *param_2)

{
  int iVar1;
  bool bVar2;
  BIGNUM *local_1c;
  BIGNUM *local_18;
  BIGNUM *local_14;
  
  local_1c = (BIGNUM *)0x0;
  local_18 = (BIGNUM *)0x0;
  local_14 = (BIGNUM *)0x0;
  if (2 < DebugLevel) {
    printk("==> %s()\n","ecc_point_is_on_curve");
  }
  Bignum_Init(&local_1c);
  Bignum_Init(&local_18);
  Bignum_Init(&local_14);
  BigInteger_record_time_begin(0x5f4b0c);
  Bignum_Mod_Square(*param_2,*(undefined4 *)(param_1 + 4),&local_1c);
  Bignum_Mod_Add(local_1c,*(undefined4 *)(param_1 + 0xc),*(undefined4 *)(param_1 + 4),&local_1c);
  Bignum_Mod_Mul(*param_2,local_1c,*(undefined4 *)(param_1 + 4),&local_1c);
  Bignum_Mod_Add(local_1c,*(undefined4 *)(param_1 + 0x10),*(undefined4 *)(param_1 + 4),&local_1c);
  Bignum_Mod_Square(param_2[1],*(undefined4 *)(param_1 + 4),&local_18);
  Bignum_Sub(*(undefined4 *)(param_1 + 4),param_2[1],&local_14);
  Bignum_Mod_Square(local_14,*(undefined4 *)(param_1 + 4),&local_14);
  iVar1 = Bignum_UnsignedCompare(local_18,local_1c);
  if (iVar1 == 0) {
    bVar2 = true;
  }
  else {
    iVar1 = Bignum_UnsignedCompare(local_14,local_1c);
    bVar2 = iVar1 == 0;
  }
  Bignum_Free(&local_1c);
  Bignum_Free(&local_18);
  Bignum_Free(&local_14);
  BigInteger_record_time_end(0x5f4b0c);
  if (2 < DebugLevel) {
    printk("%s(): res = %d\n","ecc_point_is_on_curve",bVar2);
  }
  return bVar2;
}

