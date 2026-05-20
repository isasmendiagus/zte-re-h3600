// module: mt7915.ko
// function: os_equal_mem @ 0x245b3c
// size: 20 bytes
//

bool os_equal_mem(void *param_1,void *param_2,size_t param_3)

{
  int iVar1;
  
  iVar1 = memcmp(param_1,param_2,param_3);
  return iVar1 == 0;
}

