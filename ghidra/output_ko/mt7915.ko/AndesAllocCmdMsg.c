// module: mt7915.ko
// function: AndesAllocCmdMsg @ 0x1a4180
// size: 4 bytes
//

void AndesAllocCmdMsg(int param_1)

{
  code *UNRECOVERED_JUMPTABLE;
  
  UNRECOVERED_JUMPTABLE = *(code **)(*(int *)(param_1 + 0xa797a0) + 0xb00);
  if (UNRECOVERED_JUMPTABLE != (code *)0x0) {
                    /* WARNING: Could not recover jumptable at 0x000ab3d4. Too many branches */
                    /* WARNING: Treating indirect jump as call */
    (*UNRECOVERED_JUMPTABLE)();
    return;
  }
  AndesAllocCmdMsgGe();
  return;
}

