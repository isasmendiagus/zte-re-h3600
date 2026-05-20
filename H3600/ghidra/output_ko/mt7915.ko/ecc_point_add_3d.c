// module: mt7915.ko
// function: ecc_point_add_3d @ 0x217ab0
// size: 1412 bytes
//

void ecc_point_add_3d(undefined4 *param_1,undefined4 *param_2,int param_3,undefined4 param_4)

{
  int iVar1;
  int local_38;
  int local_34;
  int local_30;
  int local_2c;
  int local_28;
  int local_24;
  int local_20;
  undefined4 *local_1c;
  
  local_38 = 0;
  local_34 = 0;
  local_30 = 0;
  local_2c = 0;
  local_28 = 0;
  local_24 = 0;
  local_20 = 0;
  local_1c = (undefined4 *)0x0;
  if (param_2 != (undefined4 *)0x0 && param_1 == (undefined4 *)0x0) {
    ecc_point_copy(param_2,param_4);
    return;
  }
  if (param_1 != (undefined4 *)0x0 && param_2 == (undefined4 *)0x0) {
    ecc_point_copy(param_1,param_4);
    return;
  }
  if (param_1 == (undefined4 *)0x0 && param_2 == (undefined4 *)0x0) {
LAB_00217b28:
    ecc_point_free(param_4);
    return;
  }
  Bignum_Init(&local_38);
  Bignum_Init(&local_34);
  Bignum_Init(&local_30);
  Bignum_Init(&local_2c);
  Bignum_Init(&local_28);
  Bignum_Init(&local_24);
  Bignum_Init(&local_20);
  if (((((local_38 == 0) || (local_34 == 0)) || (local_30 == 0)) ||
      ((local_2c == 0 || (local_28 == 0)))) || ((local_24 == 0 || (local_20 == 0)))) {
    if (2 < DebugLevel) {
      printk("%s: allocate fail\n","ecc_point_add_3d");
    }
    Bignum_Free(&local_38);
    Bignum_Free(&local_34);
    Bignum_Free(&local_30);
    Bignum_Free(&local_2c);
    Bignum_Free(&local_28);
    Bignum_Free(&local_24);
    Bignum_Free(&local_20);
    goto LAB_00217b28;
  }
  if (*(char *)(param_2 + 3) == '\0') {
    Bignum_Mod_Square(param_2[2],*(undefined4 *)(param_3 + 4),&local_38);
    Bignum_Mod_Mul(*param_1,local_38,*(undefined4 *)(param_3 + 4),&local_34);
    Bignum_Mod_Mul(local_38,param_2[2],*(undefined4 *)(param_3 + 4),&local_38);
    Bignum_Mod_Mul(param_1[1],local_38,*(undefined4 *)(param_3 + 4),&local_30);
  }
  else {
    Bignum_Copy(*param_1,&local_34);
    Bignum_Copy(param_1[1],&local_30);
  }
  if (*(char *)(param_1 + 3) == '\0') {
    Bignum_Mod_Square(param_1[2],*(undefined4 *)(param_3 + 4),&local_38);
    Bignum_Mod_Mul(*param_2,local_38,*(undefined4 *)(param_3 + 4),&local_2c);
    Bignum_Mod_Mul(local_38,param_1[2],*(undefined4 *)(param_3 + 4),&local_38);
    Bignum_Mod_Mul(param_2[1],local_38,*(undefined4 *)(param_3 + 4),&local_28);
  }
  else {
    Bignum_Copy(*param_2,&local_2c);
    Bignum_Copy(param_2[1],&local_28);
  }
  Bignum_Mod_Sub_quick(local_34,local_2c,*(undefined4 *)(param_3 + 4),&local_24);
  Bignum_Mod_Sub_quick(local_30,local_28,*(undefined4 *)(param_3 + 4),&local_20);
  iVar1 = Bignum_is_zero(local_24);
  if (iVar1 == 0) {
    Bignum_Mod_Add_quick(local_34,local_2c,*(undefined4 *)(param_3 + 4),&local_34);
    Bignum_Mod_Add_quick(local_30,local_28,*(undefined4 *)(param_3 + 4),&local_30);
    if ((local_1c != (undefined4 *)0x0) || (FUN_0021705c(&local_1c), local_1c != (undefined4 *)0x0))
    {
      Bignum_Init();
      Bignum_Init(local_1c + 1);
      Bignum_Init(local_1c + 2);
      if (*(char *)(param_1 + 3) == '\0') {
        if (*(char *)(param_2 + 3) == '\0') {
          Bignum_Mod_Mul(param_1[2],param_2[2],*(undefined4 *)(param_3 + 4),&local_38);
        }
        else {
          Bignum_Copy(param_1[2],&local_38);
        }
      }
      else {
        if (*(char *)(param_2 + 3) != '\0') {
          Bignum_Copy(local_24,local_1c + 2);
          goto LAB_00217df8;
        }
        Bignum_Copy(param_2[2],&local_38);
      }
      Bignum_Mod_Mul(local_38,local_24,*(undefined4 *)(param_3 + 4),local_1c + 2);
LAB_00217df8:
      *(undefined1 *)(local_1c + 3) = 0;
      Bignum_Mod_Square(local_20,*(undefined4 *)(param_3 + 4),&local_38);
      Bignum_Mod_Square(local_24,*(undefined4 *)(param_3 + 4),&local_28);
      Bignum_Mod_Mul(local_34,local_28,*(undefined4 *)(param_3 + 4),&local_2c);
      Bignum_Mod_Sub_quick(local_38,local_2c,*(undefined4 *)(param_3 + 4),local_1c);
      Bignum_Mod_Shift_Left1(*local_1c,*(undefined4 *)(param_3 + 4),&local_38);
      Bignum_Mod_Sub_quick(local_2c,local_38,*(undefined4 *)(param_3 + 4),&local_38);
      Bignum_Mod_Mul(local_38,local_20,*(undefined4 *)(param_3 + 4),&local_38);
      Bignum_Mod_Mul(local_28,local_24,*(undefined4 *)(param_3 + 4),&local_24);
      Bignum_Mod_Mul(local_30,local_24,*(undefined4 *)(param_3 + 4),&local_34);
      Bignum_Mod_Sub_quick(local_38,local_34,*(undefined4 *)(param_3 + 4),&local_38);
      iVar1 = Bignum_is_odd(local_38);
      if (iVar1 != 0) {
        Bignum_Add(local_38,*(undefined4 *)(param_3 + 4),&local_2c);
        Bignum_Copy(local_2c,&local_38);
      }
      Bignum_Shift_Right1(local_38,local_1c + 1);
      Bignum_Free(&local_38);
      Bignum_Free(&local_34);
      Bignum_Free(&local_30);
      Bignum_Free(&local_2c);
      Bignum_Free(&local_28);
      Bignum_Free(&local_24);
      Bignum_Free(&local_20);
      ecc_point_copy(local_1c,param_4);
      ecc_point_free(&local_1c);
      return;
    }
    if (-1 < DebugLevel) {
      printk("%s: ecc allocate fail\n","ecc_point_add_3d");
    }
  }
  else {
    iVar1 = Bignum_is_zero(local_20);
    if (iVar1 != 0) {
      ecc_point_double_3d(param_1,param_3,param_4);
      goto LAB_00217c9c;
    }
  }
  ecc_point_free(param_4);
LAB_00217c9c:
  Bignum_Free(&local_38);
  Bignum_Free(&local_34);
  Bignum_Free(&local_30);
  Bignum_Free(&local_2c);
  Bignum_Free(&local_28);
  Bignum_Free(&local_24);
  Bignum_Free(&local_20);
  return;
}

