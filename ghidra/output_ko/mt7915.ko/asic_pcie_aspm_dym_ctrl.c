// module: mt7915.ko
// function: asic_pcie_aspm_dym_ctrl @ 0x134f1c
// size: 96 bytes
//

undefined4 asic_pcie_aspm_dym_ctrl(int param_1,uint param_2,int param_3,int param_4)

{
  int iVar1;
  undefined4 uVar2;
  
  iVar1 = hc_get_hif_type(*(undefined4 *)(param_1 + 0xa797a0));
  if (iVar1 != 2) {
    AsicNotSupportFunc(param_1,"asic_pcie_aspm_dym_ctrl");
    return 0;
  }
  uVar2 = mt_cmd_ext_pcie_aspm_dym_ctrl(param_1,param_2 | param_3 << 8 | param_4 << 0x10);
  return uVar2;
}

