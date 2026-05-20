// module: mt7915.ko
// function: asic_init_wtbl @ 0x135ce8
// size: 76 bytes
//

undefined4 asic_init_wtbl(int param_1,undefined4 param_2)

{
  int iVar1;
  undefined4 uVar2;
  
  iVar1 = hc_get_arch_ops(*(undefined4 *)(param_1 + 0xa797a0));
  if (*(code **)(iVar1 + 0x104) != (code *)0x0) {
                    /* WARNING: Could not recover jumptable at 0x00135d20. Too many branches */
                    /* WARNING: Treating indirect jump as call */
    uVar2 = (**(code **)(iVar1 + 0x104))(param_1,param_2);
    return uVar2;
  }
  AsicNotSupportFunc(param_1,"asic_init_wtbl");
  return 0;
}

