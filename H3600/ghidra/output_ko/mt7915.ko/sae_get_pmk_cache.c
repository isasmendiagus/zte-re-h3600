// module: mt7915.ko
// function: sae_get_pmk_cache @ 0x2094f0
// size: 304 bytes
//

undefined4 sae_get_pmk_cache(void)

{
  int *piVar1;
  undefined4 *in_r3;
  void *in_stack_00000000;
  undefined4 local_68;
  undefined4 local_64;
  undefined4 local_60;
  undefined4 uStack_5c;
  undefined4 uStack_58;
  undefined4 uStack_54;
  
  local_68 = 0;
  local_64 = 0x10;
  piVar1 = (int *)search_sae_instance();
  if (piVar1 == (int *)0x0) {
    if (2 < DebugLevel) {
      printk("%s(): pSaeIns not found\n","sae_get_pmk_cache");
      return 0;
    }
  }
  else {
    if (((*piVar1 == 3) && (piVar1[0x14] != 0)) && (piVar1[10] != 0)) {
      if (in_r3 != (undefined4 *)0x0) {
        Bignum_Init(&local_68);
        Bignum_Mod_Add_quick(piVar1[0x14],piVar1[10],piVar1[0x1e],&local_68);
        Bignum_BI2Bin_with_pad(local_68,&local_60,&local_64,0x10);
        Bignum_Free(&local_68);
        *in_r3 = local_60;
        in_r3[1] = uStack_5c;
        in_r3[2] = uStack_58;
        in_r3[3] = uStack_54;
      }
      if (in_stack_00000000 != (void *)0x0) {
        memmove(in_stack_00000000,piVar1 + 2,0x20);
        return 1;
      }
      return 1;
    }
    if (-1 < DebugLevel) {
      printk("%s(): get pmkid fail\n","sae_get_pmk_cache");
    }
  }
  return 0;
}

