// module: mt7915.ko
// function: StateMachinePerformAction @ 0x12ec1c
// size: 108 bytes
//

void StateMachinePerformAction(undefined4 param_1,int *param_2,int param_3,int param_4)

{
  int iVar1;
  code *UNRECOVERED_JUMPTABLE;
  
  if (((code *)param_2[5] != (code *)0x0) &&
     (iVar1 = (*(code *)param_2[5])(param_1,param_3), iVar1 == 1)) {
    return;
  }
  UNRECOVERED_JUMPTABLE =
       *(code **)(param_2[4] + (param_2[2] * param_4 + (*(int *)(param_3 + 0x904) - *param_2)) * 4);
  if (UNRECOVERED_JUMPTABLE != (code *)0x0) {
                    /* WARNING: Could not recover jumptable at 0x0012ec7c. Too many branches */
                    /* WARNING: Treating indirect jump as call */
    (*UNRECOVERED_JUMPTABLE)(param_1,param_3);
    return;
  }
  return;
}

