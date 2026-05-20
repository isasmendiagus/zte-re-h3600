// module: mt7915.ko
// function: AsicGetTxTsc @ 0x133560
// size: 76 bytes
//

void AsicGetTxTsc(int param_1,undefined4 param_2,undefined4 param_3)

{
  int iVar1;
  
  iVar1 = hc_get_arch_ops(*(undefined4 *)(param_1 + 0xa797a0));
  if (*(code **)(iVar1 + 0xb0) != (code *)0x0) {
                    /* WARNING: Could not recover jumptable at 0x0013359c. Too many branches */
                    /* WARNING: Treating indirect jump as call */
    (**(code **)(iVar1 + 0xb0))(param_1,param_2,param_3);
    return;
  }
  AsicNotSupportFunc(param_1,"AsicGetTxTsc");
  return;
}

