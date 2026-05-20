// module: mt7915.ko
// function: HQA_OpenAdapter @ 0x26e2a8
// size: 148 bytes
//

undefined4 HQA_OpenAdapter(int param_1,undefined4 param_2,undefined4 param_3)

{
  undefined4 uVar1;
  undefined4 *puVar2;
  
  puVar2 = *(undefined4 **)(param_1 + 0xa39fd4);
  if (2 < DebugLevel) {
    printk(&_LC11,"HQA_OpenAdapter");
  }
  *(undefined1 *)(param_1 + 0xa3b8b6) = 1;
  FUN_0026cdd0(param_3,param_2,2,0);
  if ((code *)*puVar2 != (code *)0x0) {
                    /* WARNING: Could not recover jumptable at 0x0026e310. Too many branches */
                    /* WARNING: Treating indirect jump as call */
    uVar1 = (*(code *)*puVar2)(param_1);
    return uVar1;
  }
  return 1;
}

