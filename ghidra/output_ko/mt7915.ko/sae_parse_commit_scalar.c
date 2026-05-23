// module: mt7915.ko
// function: sae_parse_commit_scalar @ 0x209848
// size: 464 bytes
//

undefined4 sae_parse_commit_scalar(int *param_1,int *param_2,uint param_3)

{
  int iVar1;
  int *piVar2;
  BIGNUM *local_1c [2];
  
  piVar2 = (int *)param_1[0x5f];
  local_1c[0] = (BIGNUM *)0x0;
  if (4 < DebugLevel) {
    printk("==> %s()\n","sae_parse_commit_scalar");
  }
  if (param_3 < (uint)(*param_2 + param_1[0x19])) {
    if (-1 < DebugLevel) {
      printk("%s(): not enough data for scalar\n","sae_parse_commit_scalar");
    }
    return 1;
  }
  hex_dump_with_cat_and_lvl("peer scalar:",*param_2,param_1[0x19],0xf,0x20,4);
  Bignum_Bin2BI(*param_2,param_1[0x19],local_1c);
  if ((((piVar2 == (int *)0x0) || (*piVar2 != 3)) || ((BIGNUM *)piVar2[10] == (BIGNUM *)0x0)) ||
     (iVar1 = Bignum_UnsignedCompare(local_1c[0],(BIGNUM *)piVar2[10]), iVar1 != 0)) {
    if (((*param_1 == 2) && ((BIGNUM *)param_1[10] != (BIGNUM *)0x0)) &&
       (iVar1 = Bignum_UnsignedCompare(local_1c[0],(BIGNUM *)param_1[10]), iVar1 != 0)) {
      *(undefined1 *)((int)param_1 + 0x86) = 1;
    }
    iVar1 = Bignum_is_zero(local_1c[0]);
    if (((iVar1 == 0) && (iVar1 = Bignum_is_one(local_1c[0]), iVar1 == 0)) &&
       (iVar1 = Bignum_UnsignedCompare(local_1c[0],(BIGNUM *)param_1[0x1e]), iVar1 < 0)) {
      Bignum_Free(param_1 + 10);
      param_1[10] = (int)local_1c[0];
      *param_2 = *param_2 + param_1[0x19];
      return 0;
    }
    if (-1 < DebugLevel) {
      printk("%s(): Invalid peer scalar\n","sae_parse_commit_scalar");
    }
  }
  else if (-1 < DebugLevel) {
    printk("%s(): do not accept re-use of previous peer-commit-scalar\n","sae_parse_commit_scalar");
  }
  Bignum_Free(local_1c);
  return 1;
}

