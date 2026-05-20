// module: mt7915.ko
// function: ecc_point_3d_to_2d @ 0x21822c
// size: 376 bytes
//

void ecc_point_3d_to_2d(int param_1,undefined4 *param_2)

{
  int iVar1;
  undefined1 local_31;
  undefined4 local_30;
  undefined4 local_2c;
  undefined4 local_28;
  undefined4 local_24;
  undefined4 local_20;
  undefined4 local_1c [2];
  
  local_30 = 0;
  local_2c = 0;
  local_28 = 0;
  local_24 = 0;
  local_20 = 0;
  local_1c[0] = 0;
  local_31 = 1;
  if ((param_2 != (undefined4 *)0x0) && (*(char *)(param_2 + 3) == '\0')) {
    iVar1 = param_2[2];
    if (iVar1 == 0) {
      if (2 < DebugLevel) {
        printk("%s: z is null\n","ecc_point_3d_to_2d");
      }
    }
    else {
      Bignum_Init(&local_30);
      Bignum_Init(&local_2c);
      Bignum_Init(&local_28);
      Bignum_Init(&local_24);
      Bignum_Init(&local_20);
      Bignum_Init(local_1c);
      Bignum_Mod_Mul_Inverse(iVar1,*(undefined4 *)(param_1 + 4),&local_30);
      Bignum_Mod_Square(local_30,*(undefined4 *)(param_1 + 4),&local_2c);
      Bignum_Mod_Mul(*param_2,local_2c,*(undefined4 *)(param_1 + 4),&local_24);
      Bignum_Mod_Mul(local_2c,local_30,*(undefined4 *)(param_1 + 4),&local_28);
      Bignum_Mod_Mul(param_2[1],local_28,*(undefined4 *)(param_1 + 4),&local_20);
      Bignum_Bin2BI(&local_31,1,local_1c);
      Bignum_Copy(local_24,param_2);
      Bignum_Copy(local_20,param_2 + 1);
      Bignum_Copy(local_1c[0],param_2 + 2);
      *(undefined1 *)(param_2 + 3) = 1;
      Bignum_Free(&local_30);
      Bignum_Free(&local_2c);
      Bignum_Free(&local_28);
      Bignum_Free(&local_24);
      Bignum_Free(&local_20);
      Bignum_Free(local_1c);
    }
  }
  return;
}

