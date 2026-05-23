// module: mt7915.ko
// function: AsicGetRxStat @ 0x134290
// size: 76 bytes
//

undefined4 AsicGetRxStat(int param_1,undefined4 param_2)

{
  int iVar1;
  undefined4 uVar2;
  
  iVar1 = hc_get_arch_ops(*(undefined4 *)(param_1 + 0xa797a0));
  if (*(code **)(iVar1 + 0xf4) != (code *)0x0) {
                    /* WARNING: Could not recover jumptable at 0x001342c8. Too many branches */
                    /* WARNING: Treating indirect jump as call */
    uVar2 = (**(code **)(iVar1 + 0xf4))(param_1,param_2);
    return uVar2;
  }
  AsicNotSupportFunc(param_1,"AsicGetRxStat");
  return 0;
}

