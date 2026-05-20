// module: mt7915.ko
// function: hif_free_irq @ 0xaafb8
// size: 72 bytes
//

undefined4 hif_free_irq(int param_1)

{
  undefined4 uVar1;
  
  if (*(code **)(param_1 + 0xadc) != (code *)0x0) {
                    /* WARNING: Could not recover jumptable at 0x000aafc4. Too many branches */
                    /* WARNING: Treating indirect jump as call */
    uVar1 = (**(code **)(param_1 + 0xadc))();
    return uVar1;
  }
  if (DebugLevel < 0) {
    return 1;
  }
  printk("%s() not support !\n","hif_free_irq");
  return 1;
}

