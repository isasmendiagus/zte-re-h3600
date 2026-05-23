// module: mt7915.ko
// function: AndesIncErrorCount @ 0x1a448c
// size: 144 bytes
//

void AndesIncErrorCount(int param_1,int param_2,undefined4 param_3,undefined4 param_4)

{
  int iVar1;
  
  iVar1 = OS_TEST_BIT(0,param_1 + 4);
  if (iVar1 == 0) {
    return;
  }
  if (param_2 == 1) {
    *(int *)(param_1 + 0x6c) = *(int *)(param_1 + 0x6c) + 1;
    return;
  }
  if (param_2 == 0) {
    *(int *)(param_1 + 0x68) = *(int *)(param_1 + 0x68) + 1;
    return;
  }
  if (param_2 == 2) {
    *(int *)(param_1 + 0x70) = *(int *)(param_1 + 0x70) + 1;
    return;
  }
  if (DebugLevel < 0) {
    return;
  }
  printk("%s:unknown cmd_msg_error_type(%d)\n","AndesIncErrorCount",param_2,param_4);
  return;
}

