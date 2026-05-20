// module: mt7915.ko
// function: hif_mcu_exit @ 0xab03c
// size: 52 bytes
//

void hif_mcu_exit(int param_1)

{
  if (*(code **)(param_1 + 0xaf0) != (code *)0x0) {
                    /* WARNING: Could not recover jumptable at 0x000ab048. Too many branches */
                    /* WARNING: Treating indirect jump as call */
    (**(code **)(param_1 + 0xaf0))();
    return;
  }
  if (DebugLevel < 0) {
    return;
  }
  printk("%s() not support !\n","hif_mcu_exit");
  return;
}

