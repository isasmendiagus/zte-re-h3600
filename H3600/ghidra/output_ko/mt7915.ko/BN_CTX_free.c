// module: mt7915.ko
// function: BN_CTX_free @ 0x20efe0
// size: 60 bytes
//

void BN_CTX_free(BN_CTX *c)

{
  if (c == (BN_CTX *)0x0) {
    return;
  }
  if (*(int *)(c + 0x14) != 0) {
    os_free_mem();
  }
  *(undefined4 *)(c + 0x14) = 0;
  BN_POOL_finish(c);
  os_free_mem(c);
  return;
}

