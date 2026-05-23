// module: mt7915.ko
// function: pci_get_rx_resource_pending_num @ 0x1d05d0
// size: 88 bytes
//

int pci_get_rx_resource_pending_num(int param_1,int param_2)

{
  int iVar1;
  uint uVar2;
  uint uVar3;
  int iVar4;
  
  iVar1 = hc_get_hif_ctrl(*(undefined4 *)(param_1 + 0xa797a0));
  iVar1 = *(int *)(*(int *)(iVar1 + 4) + param_2 * 4);
  _raw_spin_lock_bh(iVar1 + 0x54);
  uVar3 = *(uint *)(iVar1 + 0x10);
  uVar2 = *(uint *)(iVar1 + 0xc);
  if (uVar3 < uVar2) {
    iVar4 = -uVar3;
  }
  else {
    iVar4 = *(ushort *)(iVar1 + 0x14) - uVar3;
  }
  _raw_spin_unlock_bh(iVar1 + 0x54);
  return uVar2 + iVar4;
}

