// module: mt7915.ko
// function: asic_calculate_ecc @ 0x13648c
// size: 88 bytes
//

void asic_calculate_ecc(int param_1,undefined4 param_2,undefined4 param_3,undefined4 param_4)

{
  int iVar1;
  
  iVar1 = hc_get_arch_ops(*(undefined4 *)(param_1 + 0xa797a0));
  if (*(code **)(iVar1 + 0x1e8) == (code *)0x0) {
    return;
  }
                    /* WARNING: Could not recover jumptable at 0x001364e0. Too many branches */
                    /* WARNING: Treating indirect jump as call */
  (**(code **)(iVar1 + 0x1e8))(param_1,param_2,param_3,param_4);
  return;
}

