// module: mt7915.ko
// function: hif_reset_task_group @ 0xaaf20
// size: 72 bytes
//

undefined4 hif_reset_task_group(int param_1)

{
  undefined4 uVar1;
  
  if (*(code **)(param_1 + 0xad4) != (code *)0x0) {
                    /* WARNING: Could not recover jumptable at 0x000aaf2c. Too many branches */
                    /* WARNING: Treating indirect jump as call */
    uVar1 = (**(code **)(param_1 + 0xad4))();
    return uVar1;
  }
  if (DebugLevel < 0) {
    return 1;
  }
  printk("%s() not support !\n","hif_reset_task_group");
  return 1;
}

