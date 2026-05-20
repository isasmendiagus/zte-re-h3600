// module: mt7915.ko
// function: hdev_ctrl_exit @ 0xa8a88
// size: 44 bytes
//

void hdev_ctrl_exit(int param_1,undefined4 param_2,undefined4 param_3,undefined4 param_4)

{
  undefined4 extraout_r1;
  undefined4 extraout_r2;
  undefined4 uVar1;
  
  uVar1 = *(undefined4 *)(param_1 + 0xa797a0);
  HdevHwResourceExit(uVar1);
  *(undefined4 *)(param_1 + 0xa797a0) = 0;
  os_free_mem(uVar1,extraout_r1,extraout_r2,param_4);
  return;
}

