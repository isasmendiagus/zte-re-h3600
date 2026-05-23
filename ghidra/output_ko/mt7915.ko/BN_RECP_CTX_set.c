// module: mt7915.ko
// function: BN_RECP_CTX_set @ 0x20f2b4
// size: 84 bytes
//

int BN_RECP_CTX_set(BN_RECP_CTX *recp,BIGNUM *rdiv,BN_CTX *ctx)

{
  BIGNUM *pBVar1;
  int iVar2;
  
  pBVar1 = BN_copy(&recp->N,rdiv);
  if (pBVar1 == (BIGNUM *)0x0) {
    return 0;
  }
  if (recp != (BN_RECP_CTX *)0xffffffec) {
    (recp->Nr).top = 0;
    (recp->Nr).neg = 0;
  }
  iVar2 = BN_num_bits(rdiv);
  recp->shift = 0;
  recp->num_bits = iVar2;
  return 1;
}

