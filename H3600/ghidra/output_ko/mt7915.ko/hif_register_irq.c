// module: mt7915.ko
// function: hif_register_irq @ 0xaaf6c
// size: 72 bytes
//

undefined4 hif_register_irq(int param_1)

{
  undefined4 uVar1;
  
  if (*(code **)(param_1 + 0xad8) != (code *)0x0) {
                    /* WARNING: Could not recover jumptable at 0x000aaf78. Too many branches */
                    /* WARNING: Treating indirect jump as call */
    uVar1 = (**(code **)(param_1 + 0xad8))();
    return uVar1;
  }
  if (DebugLevel < 0) {
    return 1;
  }
  printk("%s() not support !\n","hif_register_irq");
  return 1;
}

