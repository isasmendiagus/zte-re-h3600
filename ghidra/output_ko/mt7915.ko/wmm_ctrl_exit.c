// module: mt7915.ko
// function: wmm_ctrl_exit @ 0xad7a4
// size: 52 bytes
//

undefined4 wmm_ctrl_exit(int param_1)

{
  if (*(int *)(param_1 + 4) != 0) {
    os_free_mem(*(int *)(param_1 + 4));
    *(undefined4 *)(param_1 + 4) = 0;
    return 0;
  }
  return 0;
}

