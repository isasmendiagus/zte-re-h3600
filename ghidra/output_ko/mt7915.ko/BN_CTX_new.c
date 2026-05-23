// module: mt7915.ko
// function: BN_CTX_new @ 0x20ef68
// size: 96 bytes
//

/* WARNING: Unknown calling convention -- yet parameter storage is locked */

BN_CTX * BN_CTX_new(void)

{
  BN_CTX *local_c [2];
  
  os_alloc_mem(0,local_c,0x30);
  if (local_c[0] != (BN_CTX *)0x0) {
    __memzero(local_c[0],0x30);
    *(undefined4 *)local_c[0] = 0;
    *(undefined4 *)(local_c[0] + 4) = 0;
    *(undefined4 *)(local_c[0] + 8) = 0;
    *(undefined4 *)(local_c[0] + 0xc) = 0;
    *(undefined4 *)(local_c[0] + 0x10) = 0;
    *(undefined4 *)(local_c[0] + 0x14) = 0;
    *(undefined4 *)(local_c[0] + 0x1c) = 0;
    *(undefined4 *)(local_c[0] + 0x18) = 0;
  }
  return local_c[0];
}

