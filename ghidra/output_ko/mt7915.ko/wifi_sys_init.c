// module: mt7915.ko
// function: wifi_sys_init @ 0x1044dc
// size: 88 bytes
//

void wifi_sys_init(int param_1)

{
  *(int *)(param_1 + 0xa7bed8) = param_1 + 0xa7bed8;
  *(int *)(param_1 + 0xa7bedc) = param_1 + 0xa7bed8;
  *(int *)(param_1 + 0xa7bef0) = param_1 + 0xa7bef0;
  *(int *)(param_1 + 0xa7bef4) = param_1 + 0xa7bef0;
  *(int *)(param_1 + 0xa7bee4) = param_1 + 0xa7bee4;
  *(int *)(param_1 + 0xa7bee8) = param_1 + 0xa7bee4;
  *(undefined4 *)(param_1 + 0xa7bf00) = 0;
  *(undefined4 *)(param_1 + 0xa7bed4) = 0;
  *(undefined4 *)(param_1 + 0xa7beec) = 0;
  *(undefined4 *)(param_1 + 0xa7bee0) = 0;
  *(undefined4 *)(param_1 + 0xa7bef8) = 0;
  *(undefined4 *)(param_1 + 0xa7befc) = 0;
  return;
}

