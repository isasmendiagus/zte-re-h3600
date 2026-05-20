// module: mt7915.ko
// function: BN_free @ 0x20d2dc
// size: 76 bytes
//

void BN_free(BIGNUM *a)

{
  uint uVar1;
  
  if (a == (BIGNUM *)0x0) {
    return;
  }
  uVar1 = a->flags;
  if (((uVar1 & 2) == 0) && (a->d != (ulong *)0x0)) {
    os_free_mem();
    uVar1 = a->flags;
  }
  if ((uVar1 & 1) != 0) {
    os_free_mem(a);
    return;
  }
  a->d = (ulong *)0x0;
  return;
}

