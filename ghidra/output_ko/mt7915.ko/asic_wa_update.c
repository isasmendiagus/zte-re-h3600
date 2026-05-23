// module: mt7915.ko
// function: asic_wa_update @ 0x13645c
// size: 48 bytes
//

void asic_wa_update(int param_1)

{
  int iVar1;
  
  iVar1 = hc_get_arch_ops(*(undefined4 *)(param_1 + 0xa797a0));
  if (*(code **)(iVar1 + 0x1e4) == (code *)0x0) {
    return;
  }
                    /* WARNING: Could not recover jumptable at 0x00136488. Too many branches */
                    /* WARNING: Treating indirect jump as call */
  (**(code **)(iVar1 + 0x1e4))(param_1);
  return;
}

