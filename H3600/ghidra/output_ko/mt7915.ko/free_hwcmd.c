// module: mt7915.ko
// function: free_hwcmd @ 0xb1edc
// size: 72 bytes
//

void free_hwcmd(int param_1,undefined4 param_2,undefined4 param_3,undefined4 param_4)

{
  undefined4 extraout_r1;
  undefined4 extraout_r1_00;
  undefined4 extraout_r2;
  undefined4 extraout_r2_00;
  
  if (*(char *)(param_1 + -0x28) != '\0') {
    complete(param_1 + -0x24);
    param_2 = extraout_r1_00;
    param_3 = extraout_r2_00;
  }
  if (*(int *)(param_1 + -0x30) != 0) {
    os_free_mem();
    *(undefined4 *)(param_1 + -0x30) = 0;
    param_2 = extraout_r1;
    param_3 = extraout_r2;
  }
  os_free_mem(param_1 + -0x38,param_2,param_3,param_4);
  return;
}

