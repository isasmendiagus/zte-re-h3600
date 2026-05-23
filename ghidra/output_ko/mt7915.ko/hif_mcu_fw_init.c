// module: mt7915.ko
// function: hif_mcu_fw_init @ 0xab204
// size: 64 bytes
//

void hif_mcu_fw_init(int param_1)

{
  code *UNRECOVERED_JUMPTABLE;
  
  UNRECOVERED_JUMPTABLE = *(code **)(*(int *)(param_1 + 0xa797a0) + 0xaf4);
  if (UNRECOVERED_JUMPTABLE != (code *)0x0) {
                    /* WARNING: Could not recover jumptable at 0x000ab21c. Too many branches */
                    /* WARNING: Treating indirect jump as call */
    (*UNRECOVERED_JUMPTABLE)();
    return;
  }
  if (DebugLevel < 0) {
    return;
  }
  printk("%s() not support !\n","hif_mcu_fw_init");
  return;
}

