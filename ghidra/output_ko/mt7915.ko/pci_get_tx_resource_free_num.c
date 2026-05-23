// module: mt7915.ko
// function: pci_get_tx_resource_free_num @ 0x1ca858
// size: 76 bytes
//

int pci_get_tx_resource_free_num(undefined4 param_1,int param_2)

{
  ushort uVar1;
  int iVar2;
  uint uVar3;
  int iVar4;
  
  iVar2 = hc_get_hif_ctrl();
  iVar4 = *(int *)(*(int *)(iVar2 + 8) + param_2 * 4);
  uVar1 = *(ushort *)(iVar4 + 0x5a);
  _raw_spin_lock_bh(iVar4 + 0x34);
  uVar3 = *(uint *)(iVar4 + 0x28);
  iVar2 = *(uint *)(iVar4 + 0x10) - 1;
  if (*(uint *)(iVar4 + 0x10) <= uVar3) {
    iVar2 = iVar2 + (uint)uVar1;
  }
  _raw_spin_unlock_bh(iVar4 + 0x34);
  return iVar2 - uVar3;
}

