// module: mt7915.ko
// function: sys_io_write32 @ 0x1df4c0
// size: 48 bytes
//

/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */

void sys_io_write32(undefined4 *param_1,undefined4 param_2)

{
  DataSynchronizationBarrier(0xe);
  if (___aeabi_idivmod != (code *)0x0) {
    (*___aeabi_idivmod)();
  }
  *param_1 = param_2;
  return;
}

