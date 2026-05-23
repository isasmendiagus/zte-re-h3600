// module: mt7915.ko
// function: show_pcie_aspm_dym_ctrl_cap_proc @ 0xe101c
// size: 56 bytes
//

undefined4 show_pcie_aspm_dym_ctrl_cap_proc(void)

{
  undefined4 uVar1;
  
  if (0 < DebugLevel) {
    uVar1 = get_pcie_aspm_dym_ctrl_cap();
    printk("\tflag_pcie_aspm_dym_ctrl_cap=%d\n",uVar1);
  }
  return 1;
}

