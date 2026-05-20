// module: mt7915.ko
// function: hif_reset_txrx_mem @ 0xaad5c
// size: 52 bytes
//

void hif_reset_txrx_mem(int param_1)

{
  if (*(code **)(param_1 + 0xabc) != (code *)0x0) {
                    /* WARNING: Could not recover jumptable at 0x000aad68. Too many branches */
                    /* WARNING: Treating indirect jump as call */
    (**(code **)(param_1 + 0xabc))();
    return;
  }
  if (DebugLevel < 0) {
    return;
  }
  printk("%s() not support !\n","hif_reset_txrx_mem");
  return;
}

