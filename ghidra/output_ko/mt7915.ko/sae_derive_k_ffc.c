// module: mt7915.ko
// function: sae_derive_k_ffc @ 0x2084ac
// size: 316 bytes
//

undefined4 sae_derive_k_ffc(int param_1,undefined4 param_2)

{
  int iVar1;
  undefined4 uVar2;
  undefined4 local_28;
  undefined4 local_24;
  undefined4 local_20;
  undefined4 local_1c [2];
  
  local_28 = 0;
  local_24 = 0;
  local_20 = 0;
  local_1c[0] = 0x400;
  if (4 < DebugLevel) {
    printk("==> %s()\n","sae_derive_k_ffc");
  }
  uVar2 = *(undefined4 *)(param_1 + 0x5c);
  Bignum_Init(&local_28);
  Bignum_Init(&local_24);
  Bignum_Init(&local_20);
  Bignum_Montgomery_ExpMod
            (uVar2,*(undefined4 *)(param_1 + 0x28),*(undefined4 *)(param_1 + 0x74),&local_24);
  Bignum_Mod_Mul(local_24,*(undefined4 *)(param_1 + 0x58),*(undefined4 *)(param_1 + 0x74),&local_20)
  ;
  Bignum_Montgomery_ExpMod
            (local_20,*(undefined4 *)(param_1 + 0x60),*(undefined4 *)(param_1 + 0x74),&local_28);
  iVar1 = Bignum_is_one(local_28);
  if (iVar1 == 0) {
    Bignum_BI2Bin_with_pad(local_28,param_2,local_1c,*(undefined4 *)(param_1 + 100));
    hex_dump_with_lvl(&_LC27,param_2,local_1c[0],SAE_DEBUG_LEVEL);
  }
  else {
    Bignum_Free(&local_28);
    if (-1 < DebugLevel) {
      printk("%s(): K should not be one\n","sae_derive_k_ffc");
    }
  }
  Bignum_Free(&local_28);
  Bignum_Free(&local_24);
  Bignum_Free(&local_20);
  return 1;
}

