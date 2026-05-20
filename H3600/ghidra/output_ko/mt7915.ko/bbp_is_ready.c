// module: mt7915.ko
// function: bbp_is_ready @ 0x171f7c
// size: 44 bytes
//

undefined4 bbp_is_ready(int param_1)

{
  undefined4 uVar1;
  code *UNRECOVERED_JUMPTABLE;
  
  if ((*(undefined4 **)("Get_RBIST_IQ_Data_Proc" + param_1) != (undefined4 *)0x0) &&
     (UNRECOVERED_JUMPTABLE = (code *)**(undefined4 **)("Get_RBIST_IQ_Data_Proc" + param_1),
     UNRECOVERED_JUMPTABLE != (code *)0x0)) {
                    /* WARNING: Could not recover jumptable at 0x00171f9c. Too many branches */
                    /* WARNING: Treating indirect jump as call */
    uVar1 = (*UNRECOVERED_JUMPTABLE)();
    return uVar1;
  }
  return 0;
}

