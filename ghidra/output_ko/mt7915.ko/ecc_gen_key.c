// module: mt7915.ko
// function: ecc_gen_key @ 0x2191ac
// size: 384 bytes
//

undefined4 ecc_gen_key(undefined4 param_1,int param_2,int *param_3,undefined4 param_4,int *param_5)

{
  int iVar1;
  int iVar2;
  int local_18;
  int local_14;
  
  local_18 = 0;
  local_14 = 0;
  iVar2 = *param_3;
  if (*param_3 == 0) {
    Bignum_Init(&local_18);
    if (local_18 == 0) {
      if (DebugLevel < 1) {
        return 0;
      }
      printk("%s, cannot alloc BN for priv\n","ecc_gen_key");
      return 0;
    }
    *param_3 = local_18;
    iVar2 = local_18;
  }
  do {
    local_18 = iVar2;
    iVar2 = Bignum_Get_rand_range(*(undefined4 *)(param_2 + 8),local_18);
    if (iVar2 == 0) {
      if (DebugLevel < 1) {
        return 0;
      }
      printk("%s, derive priv_key failed\n","ecc_gen_key");
      return 0;
    }
    iVar1 = Bignum_is_zero(local_18);
    iVar2 = local_18;
  } while (iVar1 != 0);
  iVar2 = *param_5;
  if (*param_5 == 0) {
    if ((local_14 == 0) && (FUN_0021705c(&local_14), local_14 == 0)) {
      if (0 < DebugLevel) {
        printk("%s, cannot alloc POINT for pub\n","ecc_gen_key");
      }
      return 0;
    }
    *param_5 = local_14;
    iVar2 = local_14;
  }
  local_14 = iVar2;
  ecc_point_mul_windowed(param_4,local_18,param_2,&local_14);
  ecc_point_3d_to_2d(param_2,local_14);
  return 1;
}

