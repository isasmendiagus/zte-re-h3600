// module: switch.ko
// function: npu_drv_outdev_learn @ 0x20358
// size: 16 bytes
//

undefined4 npu_drv_outdev_learn(undefined4 param_1,int param_2)

{
  *(undefined2 *)(param_2 + 0x9a) = 0;
  return 0;
}

