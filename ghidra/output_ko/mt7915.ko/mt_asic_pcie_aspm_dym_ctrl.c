// module: mt7915.ko
// function: mt_asic_pcie_aspm_dym_ctrl @ 0x19b004
// size: 168 bytes
//

void mt_asic_pcie_aspm_dym_ctrl
               (int param_1,undefined4 param_2,undefined4 param_3,undefined4 param_4)

{
  int iVar1;
  int iVar2;
  
  iVar1 = hc_get_chip_ops(*(undefined4 *)(param_1 + 0xa797a0));
  iVar2 = get_pcie_aspm_dym_ctrl_cap(param_1);
  if (iVar2 == 0) {
    if (DebugLevel < 3) {
      return;
    }
    printk("%s::retun since cap=0\n","mt_asic_pcie_aspm_dym_ctrl");
    return;
  }
  if (*(code **)(iVar1 + 0x44) != (code *)0x0) {
                    /* WARNING: Could not recover jumptable at 0x0019b084. Too many branches */
                    /* WARNING: Treating indirect jump as call */
    (**(code **)(iVar1 + 0x44))(param_1,param_2,param_3,param_4);
    return;
  }
  if (DebugLevel < 3) {
    return;
  }
  printk("For this chip, no specified dynamic aspm ctrl function!\n");
  return;
}

