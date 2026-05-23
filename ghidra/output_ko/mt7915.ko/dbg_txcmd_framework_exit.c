// module: mt7915.ko
// function: dbg_txcmd_framework_exit @ 0x28de1c
// size: 44 bytes
//

void dbg_txcmd_framework_exit(int param_1,int param_2)

{
  *(int *)param_2 = param_2;
  *(int *)(param_2 + 4) = param_2;
  os_free_mem(param_2);
  *(undefined4 *)(param_1 + 0xa7d090) = 0;
  return;
}

