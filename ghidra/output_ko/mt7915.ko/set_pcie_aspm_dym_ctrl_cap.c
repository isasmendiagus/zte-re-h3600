// module: mt7915.ko
// function: set_pcie_aspm_dym_ctrl_cap @ 0xc4010
// size: 48 bytes
//

void set_pcie_aspm_dym_ctrl_cap(int param_1,int param_2)

{
  int iVar1;
  uint uVar2;
  
  iVar1 = hc_get_chip_cap(*(undefined4 *)(param_1 + 0xa797a0));
  if (param_2 == 0) {
    uVar2 = *(uint *)(iVar1 + 0x24) & 0xfffdffff;
  }
  else {
    uVar2 = *(uint *)(iVar1 + 0x24) | 0x20000;
  }
  *(uint *)(iVar1 + 0x24) = uVar2;
  return;
}

