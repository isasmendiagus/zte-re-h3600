// module: mt7915.ko
// function: asic_dump_wtbl_base_info @ 0x1363c4
// size: 48 bytes
//

void asic_dump_wtbl_base_info(int param_1)

{
  int iVar1;
  
  iVar1 = hc_get_arch_ops(*(undefined4 *)(param_1 + 0xa797a0));
  if (*(code **)(iVar1 + 0x1dc) == (code *)0x0) {
    return;
  }
                    /* WARNING: Could not recover jumptable at 0x001363f0. Too many branches */
                    /* WARNING: Treating indirect jump as call */
  (**(code **)(iVar1 + 0x1dc))(param_1);
  return;
}

