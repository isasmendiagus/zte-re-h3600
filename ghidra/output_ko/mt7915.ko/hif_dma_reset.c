// module: mt7915.ko
// function: hif_dma_reset @ 0xaade0
// size: 52 bytes
//

void hif_dma_reset(int param_1)

{
  if (*(code **)(param_1 + 0xae0) != (code *)0x0) {
                    /* WARNING: Could not recover jumptable at 0x000aadec. Too many branches */
                    /* WARNING: Treating indirect jump as call */
    (**(code **)(param_1 + 0xae0))();
    return;
  }
  if (DebugLevel < 0) {
    return;
  }
  printk("%s() not support !\n","hif_dma_reset");
  return;
}

