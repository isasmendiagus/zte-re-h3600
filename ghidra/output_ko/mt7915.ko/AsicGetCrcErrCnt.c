// module: mt7915.ko
// function: AsicGetCrcErrCnt @ 0x131bb8
// size: 68 bytes
//

undefined4 AsicGetCrcErrCnt(int param_1)

{
  undefined4 *puVar1;
  undefined4 uVar2;
  
  puVar1 = (undefined4 *)hc_get_arch_ops(*(undefined4 *)(param_1 + 0xa797a0));
  if ((code *)*puVar1 != (code *)0x0) {
                    /* WARNING: Could not recover jumptable at 0x00131be8. Too many branches */
                    /* WARNING: Treating indirect jump as call */
    uVar2 = (*(code *)*puVar1)();
    return uVar2;
  }
  AsicNotSupportFunc(param_1,"AsicGetCrcErrCnt");
  return 0;
}

