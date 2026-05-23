// module: mt7915.ko
// function: twt_ctrl_exit @ 0x16a854
// size: 48 bytes
//

void twt_ctrl_exit(int param_1)

{
  *(int *)(param_1 + 0x30c8) = param_1 + 0x30c8;
  *(int *)(param_1 + 0x30cc) = param_1 + 0x30c8;
  *(int *)(param_1 + 0x30c0) = param_1 + 0x30c0;
  *(int *)(param_1 + 0x30c4) = param_1 + 0x30c0;
  os_zero_mem(param_1 + 0x2c38,0x4a0);
  return;
}

