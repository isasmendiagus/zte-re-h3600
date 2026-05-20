// module: mt7915.ko
// function: sae_derive_commit_element_ffc @ 0x20864c
// size: 220 bytes
//

undefined4 sae_derive_commit_element_ffc(int param_1,int param_2)

{
  int iVar1;
  int local_20;
  undefined4 local_1c [2];
  
  iVar1 = *(int *)(param_1 + 0x5c);
  local_20 = 0;
  local_1c[0] = 0;
  if (4 < DebugLevel) {
    printk("==> %s()\n","sae_derive_commit_element_ffc");
  }
  if (iVar1 != 0 && param_2 != 0) {
    Bignum_Init(local_1c);
    Bignum_Montgomery_ExpMod(iVar1,param_2,*(undefined4 *)(param_1 + 0x74),local_1c);
    Bignum_Mod_Mul_Inverse(local_1c[0],*(undefined4 *)(param_1 + 0x74),&local_20);
    Bignum_Free(local_1c);
    if (local_20 != 0) {
      *(int *)(param_1 + 0x54) = local_20;
      Bignum_Free(local_1c);
      return 1;
    }
    if (-1 < DebugLevel) {
      printk("%s(): inverse fail\n","sae_derive_commit_element_ffc");
    }
  }
  return 0;
}

