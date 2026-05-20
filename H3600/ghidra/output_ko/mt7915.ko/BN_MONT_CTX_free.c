// module: mt7915.ko
// function: BN_MONT_CTX_free @ 0x20ebd4
// size: 64 bytes
//

void BN_MONT_CTX_free(BN_MONT_CTX *mont)

{
  if (mont == (BN_MONT_CTX *)0x0) {
    return;
  }
  BN_clear_free(&mont->RR);
  BN_clear_free(&mont->N);
  BN_clear_free(&mont->Ni);
  if ((mont->flags & 1U) == 0) {
    return;
  }
  os_free_mem(mont);
  return;
}

