// module: mt7915.ko
// function: asic_set_air_mon_idx @ 0x1365e0
// size: 92 bytes
//

undefined4
asic_set_air_mon_idx(int param_1,undefined4 param_2,undefined4 param_3,undefined4 param_4)

{
  int iVar1;
  undefined4 uVar2;
  
  iVar1 = hc_get_arch_ops(*(undefined4 *)(param_1 + 0xa797a0));
  if (*(code **)(iVar1 + 0x21c) != (code *)0x0) {
                    /* WARNING: Could not recover jumptable at 0x00136628. Too many branches */
                    /* WARNING: Treating indirect jump as call */
    uVar2 = (**(code **)(iVar1 + 0x21c))(param_1,param_2,param_3,param_4);
    return uVar2;
  }
  AsicNotSupportFunc(param_1,"asic_set_air_mon_idx");
  return 0;
}

