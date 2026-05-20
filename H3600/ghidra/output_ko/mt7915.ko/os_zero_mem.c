// module: mt7915.ko
// function: os_zero_mem @ 0x245b14
// size: 12 bytes
//

void os_zero_mem(undefined4 param_1,int param_2)

{
  if (param_2 == 0) {
    return;
  }
  __memzero();
  return;
}

