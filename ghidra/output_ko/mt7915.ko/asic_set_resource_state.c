// module: mt7915.ko
// function: asic_set_resource_state @ 0x135f74
// size: 76 bytes
//

void asic_set_resource_state(int param_1,undefined4 param_2,undefined4 param_3)

{
  int iVar1;
  
  iVar1 = hc_get_arch_ops(*(undefined4 *)(param_1 + 0xa797a0));
  if (*(code **)(iVar1 + 0x160) != (code *)0x0) {
                    /* WARNING: Could not recover jumptable at 0x00135fb0. Too many branches */
                    /* WARNING: Treating indirect jump as call */
    (**(code **)(iVar1 + 0x160))(param_1,param_2,param_3);
    return;
  }
  AsicNotSupportFunc(param_1,"asic_set_resource_state");
  return;
}

