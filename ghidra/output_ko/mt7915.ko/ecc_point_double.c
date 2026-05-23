// module: mt7915.ko
// function: ecc_point_double @ 0x217944
// size: 356 bytes
//

void ecc_point_double(undefined4 *param_1,int param_2,undefined4 param_3)

{
  undefined4 local_20;
  undefined4 local_1c;
  undefined4 local_18;
  undefined4 local_14;
  
  local_20 = 0;
  local_1c = 0;
  local_18 = 0;
  local_14 = 0;
  if (3 < DebugLevel) {
    printk("==> %s()\n","ecc_point_double");
  }
  BigInteger_record_time_begin(0x5f4ae8);
  if (param_1 == (undefined4 *)0x0) {
    ecc_point_free(param_3);
  }
  else if (param_1[2] == 0) {
    Bignum_Init(&local_1c);
    Bignum_Init(&local_18);
    Bignum_Init(&local_14);
    Bignum_Mod_Square(*param_1,*(undefined4 *)(param_2 + 4),&local_1c);
    Bignum_Mod_Add_quick(local_1c,local_1c,*(undefined4 *)(param_2 + 4),&local_18);
    Bignum_Mod_Add_quick(local_1c,local_18,*(undefined4 *)(param_2 + 4),&local_18);
    Bignum_Mod_Add(local_18,*(undefined4 *)(param_2 + 0xc),*(undefined4 *)(param_2 + 4),&local_1c);
    Bignum_Mod_Add_quick(param_1[1],param_1[1],*(undefined4 *)(param_2 + 4),&local_18);
    Bignum_Mod_Div(local_1c,local_18,*(undefined4 *)(param_2 + 4),&local_14);
    local_20 = ecc_point_add_cmm(param_1,param_1,local_14,param_2);
    ecc_point_copy(local_20,param_3);
    Bignum_Free(&local_1c);
    Bignum_Free(&local_18);
    Bignum_Free(&local_14);
    ecc_point_free(&local_20);
    BigInteger_record_time_end(0x5f4ae8);
  }
  else {
    ecc_point_double_3d(param_1,param_2,param_3);
  }
  return;
}

