// module: mt7915.ko
// function: BN_clear_free @ 0x20d260
// size: 124 bytes
//

void BN_clear_free(BIGNUM *a)

{
  undefined4 extraout_r1;
  undefined4 extraout_r2;
  undefined4 in_r3;
  uint uVar1;
  
  if (a == (BIGNUM *)0x0) {
    return;
  }
  if (a->d != (ulong *)0x0) {
    if ((a->dmax & 0x3fffffffU) == 0) {
      uVar1 = a->flags;
      if ((uVar1 & 2) != 0) goto LAB_0020d294;
    }
    else {
      __memzero();
      uVar1 = a->flags;
      if (((uVar1 & 2) != 0) || (a->d == (ulong *)0x0)) goto LAB_0020d294;
    }
    os_free_mem();
  }
  uVar1 = a->flags;
LAB_0020d294:
  __memzero(a,0x14);
  if ((uVar1 & 1) == 0) {
    return;
  }
  os_free_mem(a,extraout_r1,extraout_r2,in_r3);
  return;
}

