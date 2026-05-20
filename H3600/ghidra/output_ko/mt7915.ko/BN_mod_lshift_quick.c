// module: mt7915.ko
// function: BN_mod_lshift_quick @ 0x211220
// size: 216 bytes
//

int BN_mod_lshift_quick(BIGNUM *r,BIGNUM *a,int n,BIGNUM *m)

{
  BIGNUM *pBVar1;
  int iVar2;
  int iVar3;
  
  if ((r == a) || (pBVar1 = BN_copy(r,a), pBVar1 != (BIGNUM *)0x0)) {
    while( true ) {
      if (n < 1) {
        return 1;
      }
      iVar2 = BN_num_bits(m);
      iVar3 = BN_num_bits(r);
      iVar2 = iVar2 - iVar3;
      if (iVar2 < 0) break;
      iVar3 = n;
      if ((n < iVar2) || (iVar3 = iVar2, iVar2 != 0)) {
        iVar2 = BN_lshift(r,r,iVar3);
        if (iVar2 == 0) {
          return 0;
        }
        n = n - iVar3;
      }
      else {
        if (r == (BIGNUM *)0x0) {
          return 0;
        }
        iVar2 = FUN_0020d528(r,r);
        if (iVar2 == 0) {
          return 0;
        }
        n = n + -1;
      }
      iVar2 = BN_cmp(r,m);
      if ((-1 < iVar2) && (iVar2 = BN_sub(r,r,m), iVar2 == 0)) {
        return 0;
      }
    }
  }
  return 0;
}

