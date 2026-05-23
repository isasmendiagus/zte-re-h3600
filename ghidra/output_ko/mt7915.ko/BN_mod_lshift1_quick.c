// module: mt7915.ko
// function: BN_mod_lshift1_quick @ 0x2111bc
// size: 100 bytes
//

int BN_mod_lshift1_quick(BIGNUM *r,BIGNUM *a,BIGNUM *m)

{
  int iVar1;
  
  if (a == (BIGNUM *)0x0 || r == (BIGNUM *)0x0) {
    return 0;
  }
  iVar1 = FUN_0020d528();
  if (iVar1 != 0) {
    iVar1 = BN_cmp(r,m);
    if (-1 < iVar1) {
      iVar1 = BN_sub(r,r,m);
      return iVar1;
    }
    return 1;
  }
  return 0;
}

