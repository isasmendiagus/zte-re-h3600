// module: mt7915.ko
// function: pci_free_txd @ 0x1cccc0
// size: 168 bytes
//

undefined4 pci_free_txd(int *param_1,int param_2,undefined4 param_3,undefined4 param_4)

{
  ushort uVar1;
  int iVar2;
  uint uVar3;
  int iVar4;
  
  iVar2 = hc_get_hif_ctrl(param_1[0x29e5e8]);
  iVar2 = *(int *)(*(int *)(iVar2 + 8) + param_2 * 4);
  uVar1 = *(ushort *)(iVar2 + 0x5a);
  _raw_spin_lock_bh(iVar2 + 0x38);
  hif_io_read32(param_1[0x29e5e8],*(undefined4 *)(iVar2 + 4),iVar2 + 8);
  uVar3 = *(uint *)(iVar2 + 0x10);
  while (*(uint *)(iVar2 + 8) != uVar3) {
    iVar4 = *(int *)(iVar2 + 0xc) + uVar3 * 0x24;
    linux_pci_unmap_single
              (*(undefined4 *)(*param_1 + 0xc),*(undefined4 *)(iVar4 + 0x20),
               *(undefined4 *)(iVar4 + 0x18),0xff00,param_4);
    uVar3 = *(int *)(iVar2 + 0x10) + 1;
    *(uint *)(iVar2 + 0x10) = uVar3;
    if (uVar1 <= uVar3) {
      *(undefined4 *)(iVar2 + 0x10) = 0;
      uVar3 = 0;
    }
  }
  _raw_spin_unlock_bh(iVar2 + 0x38);
  return 0;
}

