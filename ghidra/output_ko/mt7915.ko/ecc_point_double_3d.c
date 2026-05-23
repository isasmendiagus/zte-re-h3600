// module: mt7915.ko
// function: ecc_point_double_3d @ 0x217550
// size: 1008 bytes
//

void ecc_point_double_3d(undefined4 *param_1,int param_2,undefined4 param_3)

{
  char cVar1;
  undefined4 uVar2;
  int local_2c;
  int local_28;
  int local_24;
  int local_20;
  undefined4 *local_1c [2];
  
  local_2c = 0;
  local_28 = 0;
  local_24 = 0;
  local_20 = 0;
  local_1c[0] = (undefined4 *)0x0;
  if (param_1 == (undefined4 *)0x0) {
LAB_0021780c:
    ecc_point_free(param_3);
    return;
  }
  Bignum_Init(&local_2c);
  Bignum_Init(&local_28);
  Bignum_Init(&local_24);
  Bignum_Init(&local_20);
  if ((((local_2c == 0) || (local_28 == 0)) || (local_24 == 0)) || (local_20 == 0)) {
    if (2 < DebugLevel) {
      printk("%s: allocate fail\n","ecc_point_double_3d");
    }
    Bignum_Free(&local_2c);
    Bignum_Free(&local_28);
    Bignum_Free(&local_24);
    Bignum_Free(&local_20);
    goto LAB_0021780c;
  }
  if ((local_1c[0] == (undefined4 *)0x0) &&
     (FUN_0021705c(local_1c), local_1c[0] == (undefined4 *)0x0)) {
    if (-1 < DebugLevel) {
      printk("%s: ecc allocate fail\n","ecc_point_double_3d");
    }
    goto LAB_0021780c;
  }
  Bignum_Init();
  Bignum_Init(local_1c[0] + 1);
  Bignum_Init(local_1c[0] + 2);
  if (*(char *)(param_1 + 3) == '\0') {
    if (*(char *)(param_2 + 0x24) != '\0') {
      Bignum_Mod_Square(param_1[2],*(undefined4 *)(param_2 + 4),&local_28);
      Bignum_Mod_Add_quick(*param_1,local_28,*(undefined4 *)(param_2 + 4),&local_2c);
      Bignum_Mod_Sub_quick(*param_1,local_28,*(undefined4 *)(param_2 + 4),&local_24);
      Bignum_Mod_Mul(local_2c,local_24,*(undefined4 *)(param_2 + 4),&local_28);
      Bignum_Mod_Shift_Left1(local_28,*(undefined4 *)(param_2 + 4),&local_2c);
      Bignum_Mod_Add_quick(local_2c,local_28,*(undefined4 *)(param_2 + 4),&local_28);
      cVar1 = *(char *)(param_1 + 3);
      uVar2 = param_1[1];
      goto joined_r0x002178cc;
    }
    Bignum_Mod_Square(*param_1,*(undefined4 *)(param_2 + 4),&local_2c);
    Bignum_Mod_Shift_Left1(local_2c,*(undefined4 *)(param_2 + 4),&local_28);
    Bignum_Mod_Add_quick(local_2c,local_28,*(undefined4 *)(param_2 + 4),&local_2c);
    Bignum_Mod_Square(param_1[2],*(undefined4 *)(param_2 + 4),&local_28);
    Bignum_Mod_Square(local_28,*(undefined4 *)(param_2 + 4),&local_28);
    Bignum_Mod_Mul(local_28,*(undefined4 *)(param_2 + 0xc),*(undefined4 *)(param_2 + 4),&local_28);
    Bignum_Mod_Add_quick(local_28,local_2c,*(undefined4 *)(param_2 + 4),&local_28);
  }
  else {
    Bignum_Mod_Square(*param_1,*(undefined4 *)(param_2 + 4),&local_2c);
    Bignum_Mod_Shift_Left1(local_2c,*(undefined4 *)(param_2 + 4),&local_28);
    Bignum_Mod_Add_quick(local_2c,local_28,*(undefined4 *)(param_2 + 4),&local_2c);
    Bignum_Mod_Add_quick
              (local_2c,*(undefined4 *)(param_2 + 0xc),*(undefined4 *)(param_2 + 4),&local_28);
  }
  cVar1 = *(char *)(param_1 + 3);
  uVar2 = param_1[1];
joined_r0x002178cc:
  if (cVar1 == '\0') {
    Bignum_Mod_Mul(uVar2,param_1[2],*(undefined4 *)(param_2 + 4),&local_2c);
  }
  else {
    Bignum_Copy(uVar2,&local_2c);
  }
  Bignum_Mod_Shift_Left1(local_2c,*(undefined4 *)(param_2 + 4),local_1c[0] + 2);
  *(undefined1 *)(local_1c[0] + 3) = 0;
  Bignum_Mod_Square(param_1[1],*(undefined4 *)(param_2 + 4),&local_20);
  Bignum_Mod_Mul(*param_1,local_20,*(undefined4 *)(param_2 + 4),&local_24);
  Bignum_Mod_Shift_Left(local_24,2,*(undefined4 *)(param_2 + 4),&local_24);
  Bignum_Mod_Shift_Left1(local_24,*(undefined4 *)(param_2 + 4),&local_2c);
  Bignum_Mod_Square(local_28,*(undefined4 *)(param_2 + 4),local_1c[0]);
  Bignum_Mod_Sub_quick(*local_1c[0],local_2c,*(undefined4 *)(param_2 + 4));
  Bignum_Mod_Square(local_20,*(undefined4 *)(param_2 + 4),&local_2c);
  Bignum_Mod_Shift_Left(local_2c,3,*(undefined4 *)(param_2 + 4),&local_20);
  Bignum_Mod_Sub_quick(local_24,*local_1c[0],*(undefined4 *)(param_2 + 4),&local_2c);
  Bignum_Mod_Mul(local_28,local_2c,*(undefined4 *)(param_2 + 4),&local_2c);
  Bignum_Mod_Sub_quick(local_2c,local_20,*(undefined4 *)(param_2 + 4),local_1c[0] + 1);
  Bignum_Free(&local_2c);
  Bignum_Free(&local_28);
  Bignum_Free(&local_24);
  Bignum_Free(&local_20);
  ecc_point_copy(local_1c[0],param_3);
  ecc_point_free(local_1c);
  return;
}

