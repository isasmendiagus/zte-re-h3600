// module: mt7915.ko
// function: hw_ctrl_pcie_aspm_dym_ctrl @ 0xaee60
// size: 32 bytes
//

undefined4
hw_ctrl_pcie_aspm_dym_ctrl(undefined4 param_1,int param_2,undefined4 param_3,undefined4 param_4)

{
  undefined1 *puVar1;
  
  puVar1 = *(undefined1 **)(param_2 + 8);
  asic_pcie_aspm_dym_ctrl(param_1,*puVar1,puVar1[1],puVar1[2],param_4);
  return 0;
}

