// module: mt7915.ko
// function: filter_coefficient_ctrl @ 0x171f24
// size: 44 bytes
//

undefined4 filter_coefficient_ctrl(int param_1)

{
  undefined4 uVar1;
  code *UNRECOVERED_JUMPTABLE;
  
  if ((*(int *)("Get_RBIST_IQ_Data_Proc" + param_1) != 0) &&
     (UNRECOVERED_JUMPTABLE = *(code **)(*(int *)("Get_RBIST_IQ_Data_Proc" + param_1) + 8),
     UNRECOVERED_JUMPTABLE != (code *)0x0)) {
                    /* WARNING: Could not recover jumptable at 0x00171f44. Too many branches */
                    /* WARNING: Treating indirect jump as call */
    uVar1 = (*UNRECOVERED_JUMPTABLE)();
    return uVar1;
  }
  return 0;
}

