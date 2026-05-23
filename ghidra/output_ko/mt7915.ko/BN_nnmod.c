// module: mt7915.ko
// function: BN_nnmod @ 0x211d5c
// size: 132 bytes
//

int BN_nnmod(BIGNUM *r,BIGNUM *m,BIGNUM *d,BN_CTX *ctx)

{
  int iVar1;
  int iVar2;
  code *UNRECOVERED_JUMPTABLE;
  
  iVar1 = BN_div((BIGNUM *)0x0,r,m,d,ctx);
  iVar2 = 0;
  if (iVar1 != 0) {
    if ((r == (BIGNUM *)0x0) || (r->neg != 0)) {
      UNRECOVERED_JUMPTABLE = BN_sub;
      if (d->neg == 0) {
        UNRECOVERED_JUMPTABLE = BN_add;
      }
                    /* WARNING: Could not recover jumptable at 0x00211dd0. Too many branches */
                    /* WARNING: Treating indirect jump as call */
      iVar2 = (*UNRECOVERED_JUMPTABLE)(r,r,d);
      return iVar2;
    }
    iVar2 = 1;
  }
  return iVar2;
}

