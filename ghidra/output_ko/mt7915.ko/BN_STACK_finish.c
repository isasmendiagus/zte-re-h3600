// module: mt7915.ko
// function: BN_STACK_finish @ 0x20eca0
// size: 36 bytes
//

void BN_STACK_finish(int *param_1)

{
  if (*param_1 != 0) {
    os_free_mem();
  }
  *param_1 = 0;
  return;
}

