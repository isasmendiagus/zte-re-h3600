// module: mt7915.ko
// function: asic_show_mac_info @ 0x135ca8
// size: 60 bytes
//

void asic_show_mac_info(int param_1)

{
  int iVar1;
  
  iVar1 = hc_get_arch_ops(*(undefined4 *)(param_1 + 0xa797a0));
  if (*(code **)(iVar1 + 0x100) != (code *)0x0) {
                    /* WARNING: Could not recover jumptable at 0x00135cd4. Too many branches */
                    /* WARNING: Treating indirect jump as call */
    (**(code **)(iVar1 + 0x100))();
    return;
  }
  AsicNotSupportFunc(param_1,"asic_show_mac_info");
  return;
}

