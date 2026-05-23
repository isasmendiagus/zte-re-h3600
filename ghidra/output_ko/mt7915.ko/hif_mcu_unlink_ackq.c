// module: mt7915.ko
// function: hif_mcu_unlink_ackq @ 0xab504
// size: 68 bytes
//

void hif_mcu_unlink_ackq(int param_1)

{
  code *UNRECOVERED_JUMPTABLE;
  
  UNRECOVERED_JUMPTABLE = *(code **)(*(int *)(*(int *)(param_1 + 0x1c) + 0xa797a0) + 0xafc);
  if (UNRECOVERED_JUMPTABLE != (code *)0x0) {
                    /* WARNING: Could not recover jumptable at 0x000ab520. Too many branches */
                    /* WARNING: Treating indirect jump as call */
    (*UNRECOVERED_JUMPTABLE)();
    return;
  }
  if (DebugLevel < 0) {
    return;
  }
  printk("%s() not support !\n","hif_mcu_unlink_ackq");
  return;
}

