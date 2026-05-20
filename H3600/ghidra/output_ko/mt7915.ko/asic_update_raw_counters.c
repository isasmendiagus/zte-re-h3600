// module: mt7915.ko
// function: asic_update_raw_counters @ 0x1344bc
// size: 60 bytes
//

void asic_update_raw_counters(int param_1)

{
  int iVar1;
  
  iVar1 = hc_get_arch_ops(*(undefined4 *)(param_1 + 0xa797a0));
  if (*(code **)(iVar1 + 0x118) != (code *)0x0) {
                    /* WARNING: Could not recover jumptable at 0x001344e8. Too many branches */
                    /* WARNING: Treating indirect jump as call */
    (**(code **)(iVar1 + 0x118))();
    return;
  }
  AsicNotSupportFunc(param_1,"asic_update_raw_counters");
  return;
}

