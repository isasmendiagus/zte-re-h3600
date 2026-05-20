// module: mt7915.ko
// function: AsicSetWmmParam @ 0x132c14
// size: 100 bytes
//

undefined4 AsicSetWmmParam(int param_1,undefined4 param_2,undefined4 param_3,undefined4 param_4)

{
  int iVar1;
  undefined4 uVar2;
  
  iVar1 = hc_get_arch_ops(*(undefined4 *)(param_1 + 0xa797a0));
  if (*(code **)(iVar1 + 0x8c) != (code *)0x0) {
                    /* WARNING: Could not recover jumptable at 0x00132c60. Too many branches */
                    /* WARNING: Treating indirect jump as call */
    uVar2 = (**(code **)(iVar1 + 0x8c))(param_1,param_2,param_3,param_4);
    return uVar2;
  }
  AsicNotSupportFunc(param_1,"AsicSetWmmParam");
  return 1;
}

