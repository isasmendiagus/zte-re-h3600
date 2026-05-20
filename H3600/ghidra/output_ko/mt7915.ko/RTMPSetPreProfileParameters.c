// module: mt7915.ko
// function: RTMPSetPreProfileParameters @ 0xef52c
// size: 56 bytes
//

bool RTMPSetPreProfileParameters(void)

{
  int local_c [2];
  
  os_alloc_mem(0,local_c,0x800);
  if (local_c[0] != 0) {
    os_free_mem(local_c[0]);
  }
  return local_c[0] == 0;
}

