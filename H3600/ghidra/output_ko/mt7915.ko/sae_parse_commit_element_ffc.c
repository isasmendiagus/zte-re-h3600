// module: mt7915.ko
// function: sae_parse_commit_element_ffc @ 0x2077ec
// size: 408 bytes
//

undefined4 sae_parse_commit_element_ffc(int param_1,int *param_2,uint param_3)

{
  int iVar1;
  undefined4 local_28;
  BIGNUM *local_24 [2];
  
  local_28 = 0;
  local_24[0] = (BIGNUM *)0x0;
  if (4 < DebugLevel) {
    printk("==> %s()\n","sae_parse_commit_element_ffc");
  }
  if ((uint)(*param_2 + *(int *)(param_1 + 100)) <= param_3) {
    Bignum_Bin2BI(*param_2,*(int *)(param_1 + 100),local_24);
    hex_dump_with_lvl("peer element:",*param_2,*(undefined4 *)(param_1 + 100),SAE_DEBUG_LEVEL2);
    if (local_24[0] != (BIGNUM *)0x0) {
      iVar1 = Bignum_is_zero();
      if ((iVar1 == 0) &&
         (iVar1 = Bignum_UnsignedCompare(local_24[0],*(BIGNUM **)(param_1 + 0x74)), iVar1 < 0)) {
        Bignum_Montgomery_ExpMod
                  (local_24[0],*(undefined4 *)(param_1 + 0x78),*(undefined4 *)(param_1 + 0x74),
                   &local_28);
        iVar1 = Bignum_is_one(local_28);
        if (iVar1 != 0) {
          *(BIGNUM **)(param_1 + 0x58) = local_24[0];
          *param_2 = *param_2 + *(int *)(param_1 + 100);
          Bignum_Free(&local_28);
          return 0;
        }
        if (DebugLevel < 0) goto LAB_00207844;
        printk("%s(): invalid peer element (scalar-op)\n","sae_parse_commit_element_ffc");
      }
      else {
        if (DebugLevel < 0) goto LAB_00207844;
        printk("%s(): invalid peer element\n","sae_parse_commit_element_ffc");
      }
    }
  }
  if (-1 < DebugLevel) {
    printk("%s(): fail\n","sae_parse_commit_element_ffc");
  }
LAB_00207844:
  Bignum_Free(&local_28);
  Bignum_Free(local_24);
  return 1;
}

