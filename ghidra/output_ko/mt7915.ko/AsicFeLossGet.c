// module: mt7915.ko
// function: AsicFeLossGet @ 0x133184
// size: 64 bytes
//

void AsicFeLossGet(int param_1,undefined4 param_2,undefined4 param_3)

{
  int iVar1;
  
  iVar1 = hc_get_arch_ops(*(undefined4 *)(param_1 + 0xa797a0));
  if (*(code **)(iVar1 + 0x94) == (code *)0x0) {
    return;
  }
                    /* WARNING: Could not recover jumptable at 0x001331c0. Too many branches */
                    /* WARNING: Treating indirect jump as call */
  (**(code **)(iVar1 + 0x94))(param_1,param_2,param_3);
  return;
}

