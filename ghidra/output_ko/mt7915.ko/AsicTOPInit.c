// module: mt7915.ko
// function: AsicTOPInit @ 0x1348e4
// size: 60 bytes
//

void AsicTOPInit(int param_1)

{
  int iVar1;
  
  iVar1 = hc_get_arch_ops(*(undefined4 *)(param_1 + 0xa797a0));
  if (*(code **)(iVar1 + 0xe8) != (code *)0x0) {
                    /* WARNING: Could not recover jumptable at 0x00134910. Too many branches */
                    /* WARNING: Treating indirect jump as call */
    (**(code **)(iVar1 + 0xe8))();
    return;
  }
  AsicNotSupportFunc(param_1,"AsicTOPInit");
  return;
}

