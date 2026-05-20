// module: mt7915.ko
// function: AsicSetTmrCR @ 0x134330
// size: 76 bytes
//

void AsicSetTmrCR(int param_1,undefined4 param_2,undefined4 param_3)

{
  int iVar1;
  
  iVar1 = hc_get_arch_ops(*(undefined4 *)(param_1 + 0xa797a0));
  if (*(code **)(iVar1 + 0xec) != (code *)0x0) {
                    /* WARNING: Could not recover jumptable at 0x0013436c. Too many branches */
                    /* WARNING: Treating indirect jump as call */
    (**(code **)(iVar1 + 0xec))(param_1,param_2,param_3);
    return;
  }
  AsicNotSupportFunc(param_1,"AsicSetTmrCR");
  return;
}

