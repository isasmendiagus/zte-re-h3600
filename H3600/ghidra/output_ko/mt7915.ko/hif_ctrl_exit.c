// module: mt7915.ko
// function: hif_ctrl_exit @ 0x1df6e8
// size: 4 bytes
//

void hif_ctrl_exit(int param_1)

{
  OS_SPIN_LOCK(&DAT_005f3d24);
  if (*(int *)(param_1 + -0x20) != 0) {
    *(undefined4 *)(*(int *)(param_1 + -0x20) + 4) = *(undefined4 *)(param_1 + -0x1c);
  }
  if (*(undefined4 **)(param_1 + -0x1c) != (undefined4 *)0x0) {
    **(undefined4 **)(param_1 + -0x1c) = *(undefined4 *)(param_1 + -0x20);
  }
  *(undefined4 *)(param_1 + -0x20) = 0;
  *(undefined4 *)(param_1 + -0x1c) = 0;
  OS_SPIN_UNLOCK(&DAT_005f3d24);
  os_free_mem(param_1 + -0x20);
  return;
}

