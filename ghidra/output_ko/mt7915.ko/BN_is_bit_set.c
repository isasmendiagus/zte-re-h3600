// module: mt7915.ko
// function: BN_is_bit_set @ 0x20db2c
// size: 28 bytes
//

int BN_is_bit_set(BIGNUM *a,int n)

{
  int iVar1;
  
  if (a != (BIGNUM *)0x0 && -1 < n) {
    iVar1 = FUN_0020cf74();
    return iVar1;
  }
  return 0;
}

