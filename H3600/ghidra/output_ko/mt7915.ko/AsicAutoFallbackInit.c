// module: mt7915.ko
// function: AsicAutoFallbackInit @ 0x131e0c
// size: 68 bytes
//

undefined4 AsicAutoFallbackInit(int param_1)

{
  int iVar1;
  undefined4 uVar2;
  
  iVar1 = hc_get_arch_ops(*(undefined4 *)(param_1 + 0xa797a0));
  if (*(code **)(iVar1 + 0x10) != (code *)0x0) {
                    /* WARNING: Could not recover jumptable at 0x00131e3c. Too many branches */
                    /* WARNING: Treating indirect jump as call */
    uVar2 = (**(code **)(iVar1 + 0x10))();
    return uVar2;
  }
  AsicNotSupportFunc(param_1,"AsicAutoFallbackInit");
  return 0;
}

