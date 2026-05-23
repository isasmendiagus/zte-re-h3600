// module: mt7915.ko
// function: hif_init_txrx_mem @ 0xaad94
// size: 72 bytes
//

undefined4 hif_init_txrx_mem(int param_1)

{
  undefined4 uVar1;
  
  if (*(code **)(param_1 + 0xab8) != (code *)0x0) {
                    /* WARNING: Could not recover jumptable at 0x000aada0. Too many branches */
                    /* WARNING: Treating indirect jump as call */
    uVar1 = (**(code **)(param_1 + 0xab8))();
    return uVar1;
  }
  if (DebugLevel < 0) {
    return 1;
  }
  printk("%s() not support !\n","hif_init_txrx_mem");
  return 1;
}

