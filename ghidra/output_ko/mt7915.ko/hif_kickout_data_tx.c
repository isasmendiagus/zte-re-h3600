// module: mt7915.ko
// function: hif_kickout_data_tx @ 0xab124
// size: 64 bytes
//

void hif_kickout_data_tx(int param_1)

{
  code *UNRECOVERED_JUMPTABLE;
  
  UNRECOVERED_JUMPTABLE = *(code **)(*(int *)(param_1 + 0xa797a0) + 0xb0c);
  if (UNRECOVERED_JUMPTABLE != (code *)0x0) {
                    /* WARNING: Could not recover jumptable at 0x000ab13c. Too many branches */
                    /* WARNING: Treating indirect jump as call */
    (*UNRECOVERED_JUMPTABLE)();
    return;
  }
  if (DebugLevel < 0) {
    return;
  }
  printk("%s() not support !\n","hif_kickout_data_tx");
  return;
}

