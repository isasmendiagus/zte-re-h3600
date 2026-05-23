// module: mt7915.ko
// function: hif_poll_txrx_empty @ 0xaae88
// size: 72 bytes
//

undefined4 hif_poll_txrx_empty(int param_1)

{
  undefined4 uVar1;
  
  if (*(code **)(param_1 + 0xac0) != (code *)0x0) {
                    /* WARNING: Could not recover jumptable at 0x000aae94. Too many branches */
                    /* WARNING: Treating indirect jump as call */
    uVar1 = (**(code **)(param_1 + 0xac0))();
    return uVar1;
  }
  if (DebugLevel < 0) {
    return 0;
  }
  printk("%s() not support !\n","hif_poll_txrx_empty");
  return 0;
}

