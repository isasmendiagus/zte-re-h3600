// module: mt7915.ko
// function: BN_MONT_CTX_new @ 0x20eb98
// size: 60 bytes
//

/* WARNING: Unknown calling convention -- yet parameter storage is locked */

BN_MONT_CTX * BN_MONT_CTX_new(void)

{
  BN_MONT_CTX *local_c [2];
  
  os_alloc_mem(0,local_c,0x4c);
  if (local_c[0] != (BN_MONT_CTX *)0x0) {
    BN_MONT_CTX_init(local_c[0]);
    local_c[0]->flags = 1;
  }
  return local_c[0];
}

