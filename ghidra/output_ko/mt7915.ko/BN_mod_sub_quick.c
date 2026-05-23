// module: mt7915.ko
// function: BN_mod_sub_quick @ 0x211174
// size: 72 bytes
//

int BN_mod_sub_quick(BIGNUM *r,BIGNUM *a,BIGNUM *b,BIGNUM *m)

{
  int iVar1;
  
  iVar1 = BN_sub(r,a,b);
  if (iVar1 == 0) {
    return 0;
  }
  if ((r != (BIGNUM *)0x0) && (r->neg != 0)) {
    iVar1 = BN_add(r,r,m);
    return iVar1;
  }
  return 1;
}

