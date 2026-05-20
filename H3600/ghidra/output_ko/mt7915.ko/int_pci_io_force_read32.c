// module: mt7915.ko
// function: int_pci_io_force_read32 @ 0x1cad80
// size: 40 bytes
//

void int_pci_io_force_read32(undefined4 param_1,int param_2,undefined4 *param_3)

{
  int iVar1;
  undefined4 uVar2;
  
  iVar1 = hc_get_hif_ctrl();
  uVar2 = fixed_pci_read_u32(0,*(int *)(iVar1 + 0x84) + param_2);
  *param_3 = uVar2;
  return;
}

