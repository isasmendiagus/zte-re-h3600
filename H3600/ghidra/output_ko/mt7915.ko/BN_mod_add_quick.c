// module: mt7915.ko
// function: BN_mod_add_quick @ 0x210f34
// size: 84 bytes
//

int BN_mod_add_quick(BIGNUM *r,BIGNUM *a,BIGNUM *b,BIGNUM *m)

{
  int iVar1;
  
  iVar1 = BN_uadd(r,a,b);
  if (iVar1 == 0) {
    return 0;
  }
  if ((m != (BIGNUM *)0x0 && r != (BIGNUM *)0x0) && (iVar1 = FUN_0020cef8(r,m), iVar1 < 0)) {
    return 1;
  }
  iVar1 = BN_usub(r,r,m);
  return iVar1;
}

