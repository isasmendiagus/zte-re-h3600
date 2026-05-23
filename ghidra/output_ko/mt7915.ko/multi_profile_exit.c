// module: mt7915.ko
// function: multi_profile_exit @ 0x166cd8
// size: 44 bytes
//

void multi_profile_exit(int param_1)

{
  if (*(int *)(param_1 + 0xa7cbdc) != 0) {
    os_free_mem();
  }
  *(undefined4 *)(param_1 + 0xa7cbdc) = 0;
  return;
}

