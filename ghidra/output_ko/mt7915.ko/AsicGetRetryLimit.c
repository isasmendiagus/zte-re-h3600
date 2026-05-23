// module: mt7915.ko
// function: AsicGetRetryLimit @ 0x133318
// size: 76 bytes
//

undefined4 AsicGetRetryLimit(int param_1,undefined4 param_2)

{
  int iVar1;
  undefined4 uVar2;
  
  iVar1 = hc_get_arch_ops(*(undefined4 *)(param_1 + 0xa797a0));
  if (*(code **)(iVar1 + 0xa4) != (code *)0x0) {
                    /* WARNING: Could not recover jumptable at 0x00133350. Too many branches */
                    /* WARNING: Treating indirect jump as call */
    uVar2 = (**(code **)(iVar1 + 0xa4))(param_1,param_2);
    return uVar2;
  }
  AsicNotSupportFunc(param_1,"AsicGetRetryLimit");
  return 0;
}

