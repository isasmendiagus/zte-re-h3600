// module: mt7915.ko
// function: asic_update_vlan_priority @ 0x1355ec
// size: 80 bytes
//

undefined4
asic_update_vlan_priority(int param_1,undefined4 param_2,undefined4 param_3,undefined4 param_4)

{
  int iVar1;
  undefined4 uVar2;
  
  iVar1 = hc_get_arch_ops(*(undefined4 *)(param_1 + 0xa797a0));
  if (*(code **)(iVar1 + 0x158) != (code *)0x0) {
                    /* WARNING: Could not recover jumptable at 0x00135630. Too many branches */
                    /* WARNING: Treating indirect jump as call */
    uVar2 = (**(code **)(iVar1 + 0x158))(param_1,param_2,param_3,param_4);
    return uVar2;
  }
  return 0;
}

