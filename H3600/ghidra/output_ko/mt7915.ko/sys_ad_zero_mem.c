// module: mt7915.ko
// function: sys_ad_zero_mem @ 0x25eae8
// size: 12 bytes
//

void sys_ad_zero_mem(undefined4 param_1,int param_2)

{
  if (param_2 == 0) {
    return;
  }
  __memzero();
  return;
}

