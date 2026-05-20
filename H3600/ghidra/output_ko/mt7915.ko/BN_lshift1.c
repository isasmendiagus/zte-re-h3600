// module: mt7915.ko
// function: BN_lshift1 @ 0x2108d8
// size: 24 bytes
//

int BN_lshift1(BIGNUM *r,BIGNUM *a)

{
  int iVar1;
  
  if (a != (BIGNUM *)0x0 && r != (BIGNUM *)0x0) {
    iVar1 = FUN_0020d528();
    return iVar1;
  }
  return 0;
}

