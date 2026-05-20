// module: mt7915.ko
// function: BN_GENCB_new @ 0x20e144
// size: 36 bytes
//

undefined4 BN_GENCB_new(void)

{
  undefined4 local_c [2];
  
  os_alloc_mem(0,local_c,0xc);
  return local_c[0];
}

