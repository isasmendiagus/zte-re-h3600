// module: mt7915.ko
// function: hif_get_tx_buf @ 0xab28c
// size: 72 bytes
//

undefined4 hif_get_tx_buf(int param_1)

{
  undefined4 uVar1;
  
  if (*(code **)(param_1 + 0xac4) != (code *)0x0) {
                    /* WARNING: Could not recover jumptable at 0x000ab298. Too many branches */
                    /* WARNING: Treating indirect jump as call */
    uVar1 = (**(code **)(param_1 + 0xac4))();
    return uVar1;
  }
  if (DebugLevel < 0) {
    return 0;
  }
  printk("%s() not support !\n","hif_get_tx_buf");
  return 0;
}

