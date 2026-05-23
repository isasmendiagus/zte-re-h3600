// module: mt7915.ko
// function: asic_update_mib_bucket @ 0x1344fc
// size: 60 bytes
//

void asic_update_mib_bucket(int param_1)

{
  int iVar1;
  
  iVar1 = hc_get_arch_ops(*(undefined4 *)(param_1 + 0xa797a0));
  if (*(code **)(iVar1 + 0x11c) != (code *)0x0) {
                    /* WARNING: Could not recover jumptable at 0x00134528. Too many branches */
                    /* WARNING: Treating indirect jump as call */
    (**(code **)(iVar1 + 0x11c))();
    return;
  }
  AsicNotSupportFunc(param_1,"asic_update_mib_bucket");
  return;
}

