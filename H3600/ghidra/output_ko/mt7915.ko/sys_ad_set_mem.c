// module: mt7915.ko
// function: sys_ad_set_mem @ 0x25eaf4
// size: 20 bytes
//

void sys_ad_set_mem(void *param_1,size_t param_2,int param_3)

{
  if (param_2 == 0) {
    return;
  }
  memset(param_1,param_3,param_2);
  return;
}

