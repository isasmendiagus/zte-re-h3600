// module: mt7915.ko
// function: tm_tasklet_qm_schedule_task @ 0x150834
// size: 132 bytes
//

undefined4 tm_tasklet_qm_schedule_task(int param_1,int param_2,int param_3)

{
  int iVar1;
  int iVar2;
  
  if (param_2 == 0) {
    if (*(char *)(param_1 + param_3 + 0x285bac) == '\0') {
      return 0;
    }
    iVar2 = 0x285bb0;
    param_1 = param_1 + param_3 * 0x14;
  }
  else {
    if (param_2 != 1) {
      return 0;
    }
    iVar2 = 0x285bdc;
  }
  iVar1 = _test_and_set_bit(0,param_1 + iVar2 + 4);
  if (iVar1 != 0) {
    return 0;
  }
  __tasklet_hi_schedule(param_1 + iVar2);
  return 0;
}

