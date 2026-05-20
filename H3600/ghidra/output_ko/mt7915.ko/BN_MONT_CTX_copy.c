// module: mt7915.ko
// function: BN_MONT_CTX_copy @ 0x20ec14
// size: 120 bytes
//

BN_MONT_CTX * BN_MONT_CTX_copy(BN_MONT_CTX *to,BN_MONT_CTX *from)

{
  BIGNUM *pBVar1;
  
  if (to == from) {
    return to;
  }
  pBVar1 = BN_copy(&to->RR,&from->RR);
  if (((pBVar1 != (BIGNUM *)0x0) && (pBVar1 = BN_copy(&to->N,&from->N), pBVar1 != (BIGNUM *)0x0)) &&
     (pBVar1 = BN_copy(&to->Ni,&from->Ni), pBVar1 != (BIGNUM *)0x0)) {
    to->ri = from->ri;
    to->n0[0] = from->n0[0];
    to->n0[1] = from->n0[1];
    return to;
  }
  return (BN_MONT_CTX *)0x0;
}

