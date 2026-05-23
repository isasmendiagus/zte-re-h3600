// module: mt7915.ko
// function: BN_new @ 0x20d34c
// size: 76 bytes
//

/* WARNING: Unknown calling convention -- yet parameter storage is locked */

BIGNUM * BN_new(void)

{
  BIGNUM *local_c [2];
  
  os_alloc_mem(0,local_c,0x14);
  if (local_c[0] != (BIGNUM *)0x0) {
    local_c[0]->d = (ulong *)0x0;
    local_c[0]->top = 0;
    local_c[0]->dmax = 0;
    local_c[0]->flags = 1;
    local_c[0]->neg = 0;
  }
  return local_c[0];
}

