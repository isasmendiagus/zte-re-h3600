// module: mt7915.ko
// function: os_cmp_mem @ 0x245b38
// size: 4 bytes
//

/* WARNING: Unknown calling convention -- yet parameter storage is locked */

int os_cmp_mem(void *__s1,void *__s2,size_t __n)

{
  int iVar1;
  
  iVar1 = memcmp(__s1,__s2,__n);
  return iVar1;
}

