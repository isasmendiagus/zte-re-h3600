// module: switch.ko
// function: npu_drv_free_flow @ 0x203e8
// size: 68 bytes
//

undefined4 npu_drv_free_flow(undefined4 param_1,int param_2)

{
  if ((1 < *(int *)(*(int *)(param_2 + 0x34) + 0x14) - 4U) && (*(int *)(param_2 + 0x9c) != 0)) {
    kfree();
    *(undefined4 *)(param_2 + 0x9c) = 0;
    return 0;
  }
  return 0;
}

