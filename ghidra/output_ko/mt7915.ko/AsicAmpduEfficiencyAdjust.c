// module: mt7915.ko
// function: AsicAmpduEfficiencyAdjust @ 0x135bac
// size: 108 bytes
//

undefined4 AsicAmpduEfficiencyAdjust(int param_1,undefined4 param_2)

{
  undefined1 uVar1;
  int iVar2;
  undefined4 uVar3;
  int iVar4;
  
  if (param_1 == 0) {
    return 0;
  }
  iVar4 = *(int *)(param_1 + 8);
  uVar1 = HcGetWmmIdx(iVar4,param_1);
  iVar2 = hc_get_arch_ops(*(undefined4 *)(iVar4 + 0xa797a0));
  if (*(code **)(iVar2 + 0x1d4) != (code *)0x0) {
                    /* WARNING: Could not recover jumptable at 0x00135bfc. Too many branches */
                    /* WARNING: Treating indirect jump as call */
    uVar3 = (**(code **)(iVar2 + 0x1d4))(iVar4,uVar1,param_2);
    return uVar3;
  }
  AsicNotSupportFunc(iVar4,"AsicAmpduEfficiencyAdjust");
  return 0;
}

