// module: mt7915.ko
// function: get_pcie_aspm_dym_ctrl_cap @ 0xc4040
// size: 32 bytes
//

uint get_pcie_aspm_dym_ctrl_cap(int param_1)

{
  int iVar1;
  
  iVar1 = hc_get_chip_cap(*(undefined4 *)(param_1 + 0xa797a0));
  return (uint)(*(int *)(iVar1 + 0x24) << 0xe) >> 0x1f;
}

