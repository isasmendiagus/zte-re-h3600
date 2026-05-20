// module: mt7915.ko
// function: hif_dma_disable @ 0xaae50
// size: 52 bytes
//

void hif_dma_disable(int param_1)

{
  if (*(code **)(param_1 + 0xae8) != (code *)0x0) {
                    /* WARNING: Could not recover jumptable at 0x000aae5c. Too many branches */
                    /* WARNING: Treating indirect jump as call */
    (**(code **)(param_1 + 0xae8))();
    return;
  }
  if (DebugLevel < 0) {
    return;
  }
  printk("%s() not support !\n","hif_dma_disable");
  return;
}

