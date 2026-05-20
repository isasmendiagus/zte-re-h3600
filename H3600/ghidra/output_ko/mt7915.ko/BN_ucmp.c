// module: mt7915.ko
// function: BN_ucmp @ 0x20d980
// size: 24 bytes
//

int BN_ucmp(BIGNUM *a,BIGNUM *b)

{
  int iVar1;
  
  if (b != (BIGNUM *)0x0 && a != (BIGNUM *)0x0) {
    iVar1 = FUN_0020cef8();
    return iVar1;
  }
  return 0;
}

