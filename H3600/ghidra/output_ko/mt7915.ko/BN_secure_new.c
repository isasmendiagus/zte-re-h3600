// module: mt7915.ko
// function: BN_secure_new @ 0x20d398
// size: 28 bytes
//

void BN_secure_new(void)

{
  BIGNUM *pBVar1;
  
  pBVar1 = BN_new();
  if (pBVar1 != (BIGNUM *)0x0) {
    pBVar1->flags = pBVar1->flags | 8;
  }
  return;
}

