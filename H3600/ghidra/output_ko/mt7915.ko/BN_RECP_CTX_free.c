// module: mt7915.ko
// function: BN_RECP_CTX_free @ 0x20f284
// size: 48 bytes
//

void BN_RECP_CTX_free(BN_RECP_CTX *recp)

{
  if (recp == (BN_RECP_CTX *)0x0) {
    return;
  }
  BN_free(&recp->N);
  BN_free(&recp->Nr);
  if ((recp->flags & 1U) == 0) {
    return;
  }
  os_free_mem(recp);
  return;
}

