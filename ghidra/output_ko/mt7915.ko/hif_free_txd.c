// module: mt7915.ko
// function: hif_free_txd @ 0xaacb4
// size: 108 bytes
//

undefined4 hif_free_txd(int param_1)

{
  undefined4 uVar1;
  code *UNRECOVERED_JUMPTABLE;
  
  UNRECOVERED_JUMPTABLE = *(code **)(*(int *)(param_1 + 0xa797a0) + 0xab0);
  if (UNRECOVERED_JUMPTABLE != (code *)0x0) {
                    /* WARNING: Could not recover jumptable at 0x000aacdc. Too many branches */
                    /* WARNING: Treating indirect jump as call */
    uVar1 = (*UNRECOVERED_JUMPTABLE)();
    return uVar1;
  }
  if (-1 < DebugLevel) {
    printk("%s() not support !, caller=%pS, ad=%p, ctrl=%p\n","hif_free_txd");
  }
  return 0;
}

