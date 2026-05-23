// module: switch.ko
// function: npu_drv_indev_learn @ 0x20340
// size: 24 bytes
//

undefined4 npu_drv_indev_learn(undefined4 param_1,int param_2,int param_3)

{
  *(short *)(param_2 + 0x98) =
       (short)*(undefined4 *)(param_3 + 0x24) - (short)*(undefined4 *)(param_3 + 0x28);
  return 0;
}

