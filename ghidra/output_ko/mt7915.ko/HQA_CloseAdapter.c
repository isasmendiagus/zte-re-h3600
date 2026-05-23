// module: mt7915.ko
// function: HQA_CloseAdapter @ 0x26e214
// size: 144 bytes
//

undefined4 HQA_CloseAdapter(int param_1,undefined4 param_2,undefined4 param_3)

{
  undefined4 uVar1;
  code *UNRECOVERED_JUMPTABLE;
  int iVar2;
  
  iVar2 = *(int *)(param_1 + 0xa39fd4);
  if (2 < DebugLevel) {
    printk(&_LC11,"HQA_CloseAdapter");
  }
  *(undefined1 *)(param_1 + 0xa3b8b6) = 0;
  FUN_0026cdd0(param_3,param_2,2);
  UNRECOVERED_JUMPTABLE = *(code **)(iVar2 + 4);
  if (UNRECOVERED_JUMPTABLE != (code *)0x0) {
                    /* WARNING: Could not recover jumptable at 0x0026e278. Too many branches */
                    /* WARNING: Treating indirect jump as call */
    uVar1 = (*UNRECOVERED_JUMPTABLE)(param_1);
    return uVar1;
  }
  return 1;
}

