// module: mt7915.ko
// function: Bignum_UnsignedCompare @ 0x20c3e4
// size: 4 bytes
//

int Bignum_UnsignedCompare(BIGNUM *a,BIGNUM *b)

{
  int iVar1;
  
  if (b != (BIGNUM *)0x0 && a != (BIGNUM *)0x0) {
    iVar1 = FUN_0020cef8();
    return iVar1;
  }
  return 0;
}

