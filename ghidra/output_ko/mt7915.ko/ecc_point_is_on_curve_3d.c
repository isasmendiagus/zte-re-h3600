// module: mt7915.ko
// function: ecc_point_is_on_curve_3d @ 0x218aa0
// size: 520 bytes
//

bool ecc_point_is_on_curve_3d(int param_1,undefined4 *param_2)

{
  int iVar1;
  bool bVar2;
  BIGNUM *local_2c;
  BIGNUM *local_28;
  BIGNUM *local_24;
  undefined4 local_20;
  undefined4 local_1c [2];
  
  local_2c = (BIGNUM *)0x0;
  local_28 = (BIGNUM *)0x0;
  local_24 = (BIGNUM *)0x0;
  local_20 = 0;
  local_1c[0] = 0;
  if (2 < DebugLevel) {
    printk("==> %s()\n","ecc_point_is_on_curve_3d");
  }
  if (param_2[2] == 0) {
    bVar2 = false;
    if (-1 < DebugLevel) {
      printk("ecc_point_is_on_curve_3d: z is NULL\n");
    }
  }
  else {
    Bignum_Init(&local_2c);
    Bignum_Init(&local_28);
    Bignum_Init(&local_24);
    Bignum_Init(&local_20);
    Bignum_Init(local_1c);
    Bignum_Mod_Square(*param_2,*(undefined4 *)(param_1 + 4),&local_2c);
    Bignum_Mod_Square(param_2[2],*(undefined4 *)(param_1 + 4),&local_20);
    Bignum_Mod_Square(local_20,*(undefined4 *)(param_1 + 4),local_1c);
    Bignum_Mod_Mul(local_1c[0],local_20,*(undefined4 *)(param_1 + 4),&local_20);
    Bignum_Mod_Mul(*(undefined4 *)(param_1 + 0xc),local_1c[0],*(undefined4 *)(param_1 + 4),local_1c)
    ;
    Bignum_Mod_Add(local_2c,local_1c[0],*(undefined4 *)(param_1 + 4),&local_2c);
    Bignum_Mod_Mul(*param_2,local_2c,*(undefined4 *)(param_1 + 4),&local_2c);
    Bignum_Mod_Mul(*(undefined4 *)(param_1 + 0x10),local_20,*(undefined4 *)(param_1 + 4),&local_20);
    Bignum_Mod_Add(local_2c,local_20,*(undefined4 *)(param_1 + 4),&local_2c);
    Bignum_Mod_Square(param_2[1],*(undefined4 *)(param_1 + 4),&local_28);
    Bignum_Sub(*(undefined4 *)(param_1 + 4),param_2[1],&local_24);
    Bignum_Mod_Square(local_24,*(undefined4 *)(param_1 + 4),&local_24);
    iVar1 = Bignum_UnsignedCompare(local_28,local_2c);
    if (iVar1 == 0) {
      bVar2 = true;
    }
    else {
      iVar1 = Bignum_UnsignedCompare(local_24,local_2c);
      bVar2 = iVar1 == 0;
    }
    Bignum_Free(&local_2c);
    Bignum_Free(&local_28);
    Bignum_Free(&local_24);
    Bignum_Free(&local_20);
    Bignum_Free(local_1c);
    if (2 < DebugLevel) {
      printk("%s(): res = %d\n","ecc_point_is_on_curve_3d",bVar2);
    }
  }
  return bVar2;
}

