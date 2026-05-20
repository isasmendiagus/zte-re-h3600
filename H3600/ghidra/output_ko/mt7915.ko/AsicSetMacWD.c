// module: mt7915.ko
// function: AsicSetMacWD @ 0x1340e8
// size: 68 bytes
//

undefined4 AsicSetMacWD(int param_1)

{
  int iVar1;
  undefined4 uVar2;
  
  iVar1 = hc_get_arch_ops(*(undefined4 *)(param_1 + 0xa797a0));
  if (*(code **)(iVar1 + 0xe4) != (code *)0x0) {
                    /* WARNING: Could not recover jumptable at 0x00134118. Too many branches */
                    /* WARNING: Treating indirect jump as call */
    uVar2 = (**(code **)(iVar1 + 0xe4))();
    return uVar2;
  }
  AsicNotSupportFunc(param_1,"AsicSetMacWD");
  return 0;
}

