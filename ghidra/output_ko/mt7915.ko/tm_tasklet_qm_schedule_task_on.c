// module: mt7915.ko
// function: tm_tasklet_qm_schedule_task_on @ 0x1508b8
// size: 96 bytes
//

undefined4 tm_tasklet_qm_schedule_task_on(int param_1,undefined4 param_2,int param_3,int param_4)

{
  code *pcVar1;
  
  if ((param_3 == 0) && (*(char *)(param_1 + param_4 + 0x285bac) != '\0')) {
    if (param_4 == 0) {
      pcVar1 = tx_deq0_schedule_cpu;
    }
    else {
      pcVar1 = tx_deq1_schedule_cpu;
    }
    smp_call_function_single(param_2,pcVar1,param_1,0,param_4);
  }
  return 0;
}

