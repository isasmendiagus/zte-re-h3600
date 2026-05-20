// module: mt7915.ko
// function: set_rid_value @ 0x17f3fc
// size: 56 bytes
//

/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */

void set_rid_value(int param_1,uint param_2)

{
  DataSynchronizationBarrier(0xe);
  if (___aeabi_idivmod != (code *)0x0) {
    (*___aeabi_idivmod)();
  }
  *(uint *)(*(int *)(param_1 + 0xbc) + 0xd7090) = param_2 | 0x80000000;
  return;
}

