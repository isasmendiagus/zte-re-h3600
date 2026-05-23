// module: mt7915.ko
// function: hif_get_tx_resource_free_num @ 0xab2d8
// size: 72 bytes
//

undefined4 hif_get_tx_resource_free_num(int param_1)

{
  undefined4 uVar1;
  
  if (*(code **)(param_1 + 0xac8) != (code *)0x0) {
                    /* WARNING: Could not recover jumptable at 0x000ab2e4. Too many branches */
                    /* WARNING: Treating indirect jump as call */
    uVar1 = (**(code **)(param_1 + 0xac8))();
    return uVar1;
  }
  if (DebugLevel < 0) {
    return 0;
  }
  printk("%s() not support !\n","hif_get_tx_resource_free_num");
  return 0;
}

