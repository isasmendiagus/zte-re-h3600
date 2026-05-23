// module: mt7915.ko
// function: hif_kick_out_cmd_msg @ 0xab0cc
// size: 84 bytes
//

undefined4 hif_kick_out_cmd_msg(int param_1)

{
  undefined4 uVar1;
  code *UNRECOVERED_JUMPTABLE;
  
  UNRECOVERED_JUMPTABLE = *(code **)(*(int *)(param_1 + 0xa797a0) + 0xb04);
  if (UNRECOVERED_JUMPTABLE != (code *)0x0) {
                    /* WARNING: Could not recover jumptable at 0x000ab0e4. Too many branches */
                    /* WARNING: Treating indirect jump as call */
    uVar1 = (*UNRECOVERED_JUMPTABLE)();
    return uVar1;
  }
  if (DebugLevel < 0) {
    return 0;
  }
  printk("%s() not support !\n","hif_kick_out_cmd_msg");
  return 0;
}

