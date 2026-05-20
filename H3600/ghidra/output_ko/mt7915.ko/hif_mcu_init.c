// module: mt7915.ko
// function: hif_mcu_init @ 0xab004
// size: 52 bytes
//

void hif_mcu_init(int param_1)

{
  if (*(code **)(param_1 + 0xaec) != (code *)0x0) {
                    /* WARNING: Could not recover jumptable at 0x000ab010. Too many branches */
                    /* WARNING: Treating indirect jump as call */
    (**(code **)(param_1 + 0xaec))();
    return;
  }
  if (DebugLevel < 0) {
    return;
  }
  printk("%s() not support !\n","hif_mcu_init");
  return;
}

