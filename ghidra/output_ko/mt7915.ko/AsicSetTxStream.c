// module: mt7915.ko
// function: AsicSetTxStream @ 0x134130
// size: 84 bytes
//

undefined4
AsicSetTxStream(int param_1,undefined4 param_2,undefined4 param_3,undefined4 param_4,
               undefined1 param_5)

{
  int iVar1;
  undefined4 uVar2;
  
  iVar1 = hc_get_arch_ops(*(undefined4 *)(param_1 + 0xa797a0));
  if (*(code **)(iVar1 + 200) != (code *)0x0) {
                    /* WARNING: Could not recover jumptable at 0x00134170. Too many branches */
                    /* WARNING: Treating indirect jump as call */
    uVar2 = (**(code **)(iVar1 + 200))(param_1,param_2,param_5);
    return uVar2;
  }
  AsicNotSupportFunc(param_1,"AsicSetTxStream");
  return 0;
}

