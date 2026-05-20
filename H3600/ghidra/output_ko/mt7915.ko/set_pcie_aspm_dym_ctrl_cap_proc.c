// module: mt7915.ko
// function: set_pcie_aspm_dym_ctrl_cap_proc @ 0xdeac0
// size: 204 bytes
//

undefined4
set_pcie_aspm_dym_ctrl_cap_proc
          (int param_1,undefined4 param_2,undefined4 param_3,undefined4 param_4)

{
  int iVar1;
  undefined4 uVar2;
  
  iVar1 = os_str_tol(param_2,0,10,param_4,param_4);
  if (iVar1 == 0) {
    mt_asic_pcie_aspm_dym_ctrl(param_1,0,0,0);
    if (*(char *)(param_1 + 0x79504d) != '\0') {
      mt_asic_pcie_aspm_dym_ctrl(param_1,1,0,0);
    }
    set_pcie_aspm_dym_ctrl_cap(param_1,0);
  }
  else {
    if (iVar1 != 1) {
      return 0;
    }
    set_pcie_aspm_dym_ctrl_cap(param_1,1);
  }
  if (DebugLevel < 3) {
    return 1;
  }
  uVar2 = get_pcie_aspm_dym_ctrl_cap(param_1);
  printk("%s=%d\n","set_pcie_aspm_dym_ctrl_cap_proc",uVar2);
  return 1;
}

