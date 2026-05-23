// module: mt7915.ko
// function: os_fill_mem @ 0x245b24
// size: 20 bytes
//

void os_fill_mem(void *param_1,size_t param_2,int param_3)

{
  if (param_2 == 0) {
    return;
  }
  memset(param_1,param_3,param_2);
  return;
}

