// module: mt7915.ko
// function: AsicGetFwSyncValue @ 0x135374
// size: 68 bytes
//

undefined4 AsicGetFwSyncValue(int param_1)

{
  int iVar1;
  undefined4 uVar2;
  
  iVar1 = hc_get_arch_ops(*(undefined4 *)(param_1 + 0xa797a0));
  if (*(code **)(iVar1 + 0xf8) != (code *)0x0) {
                    /* WARNING: Could not recover jumptable at 0x001353a4. Too many branches */
                    /* WARNING: Treating indirect jump as call */
    uVar2 = (**(code **)(iVar1 + 0xf8))();
    return uVar2;
  }
  AsicNotSupportFunc(param_1,"AsicGetFwSyncValue");
  return 0;
}

