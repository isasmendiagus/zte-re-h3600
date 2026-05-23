// module: mt7915.ko
// function: AndesBhSchedule @ 0x1a48e4
// size: 160 bytes
//

void AndesBhSchedule(int param_1)

{
  int iVar1;
  
  iVar1 = OS_TEST_BIT(0,param_1 + 0xa784a0);
  if (iVar1 == 0) {
    return;
  }
  iVar1 = AndesQueueLen(param_1 + 0xa7849c,param_1 + 0xa784f8);
  if ((iVar1 == 0) && (iVar1 = AndesQueueLen(param_1 + 0xa7849c,param_1 + 0xa784ec), iVar1 == 0)) {
    return;
  }
  iVar1 = OS_TEST_BIT(0,param_1 + 0xa784a0);
  if (iVar1 == 0) {
    return;
  }
  *(int *)(param_1 + 0xa784b4) = param_1;
  iVar1 = _test_and_set_bit(0,param_1 + 0xa784a8);
  if (iVar1 != 0) {
    return;
  }
  __tasklet_hi_schedule(param_1 + 0xa784a4);
  return;
}

