// module: mt7915.ko
// function: asic_get_nsts_by_mcs @ 0x134454
// size: 100 bytes
//

undefined4
asic_get_nsts_by_mcs
          (int param_1,undefined4 param_2,undefined4 param_3,undefined4 param_4,undefined1 param_5)

{
  int iVar1;
  undefined4 uVar2;
  
  iVar1 = hc_get_arch_ops(*(undefined4 *)(param_1 + 0xa797a0));
  if (*(code **)(iVar1 + 0x110) != (code *)0x0) {
                    /* WARNING: Could not recover jumptable at 0x001344a0. Too many branches */
                    /* WARNING: Treating indirect jump as call */
    uVar2 = (**(code **)(iVar1 + 0x110))(param_2,param_3,param_4,param_5);
    return uVar2;
  }
  AsicNotSupportFunc(param_1,"asic_get_nsts_by_mcs");
  return 0;
}

