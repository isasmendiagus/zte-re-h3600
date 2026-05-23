// module: mt7915.ko
// function: asic_dump_rmac_info @ 0x1361b0
// size: 56 bytes
//

void asic_dump_rmac_info(int param_1,undefined4 param_2)

{
  int iVar1;
  
  iVar1 = hc_get_arch_ops(*(undefined4 *)(param_1 + 0xa797a0));
  if (*(code **)(iVar1 + 0x1ac) == (code *)0x0) {
    return;
  }
                    /* WARNING: Could not recover jumptable at 0x001361e4. Too many branches */
                    /* WARNING: Treating indirect jump as call */
  (**(code **)(iVar1 + 0x1ac))(param_1,param_2);
  return;
}

