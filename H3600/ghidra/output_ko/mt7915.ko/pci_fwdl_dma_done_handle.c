// module: mt7915.ko
// function: pci_fwdl_dma_done_handle @ 0x1ccaa0
// size: 272 bytes
//

undefined4 pci_fwdl_dma_done_handle(int *param_1,int param_2)

{
  int iVar1;
  undefined4 *puVar2;
  uint uVar3;
  int iVar4;
  int iVar5;
  uint uVar6;
  
  iVar1 = hc_get_hif_ctrl(param_1[0x29e5e8]);
  iVar1 = *(int *)(*(int *)(iVar1 + 8) + param_2 * 4);
  _raw_spin_lock_bh(iVar1 + 0x38);
  hif_io_read32(param_1[0x29e5e8],*(undefined4 *)(iVar1 + 4),iVar1 + 8);
  uVar3 = *(uint *)(iVar1 + 0x10);
  uVar6 = *(uint *)(iVar1 + 8);
  while (uVar3 != uVar6) {
    while( true ) {
      iVar5 = *(int *)(iVar1 + 0xc) + uVar3 * 0x24;
      iVar4 = *(int *)(iVar5 + 0xc);
      puVar2 = *(undefined4 **)(iVar5 + 4);
      if (iVar4 == 0) break;
      linux_pci_unmap_single
                (*(undefined4 *)(*param_1 + 0xc),*puVar2,
                 (uint)*(byte *)((int)puVar2 + 6) | (*(byte *)((int)puVar2 + 7) & 0x3f) << 8,0xff00)
      ;
      RTMPFreeNdisPacket(param_1,iVar4);
      *(undefined4 *)(*(int *)(iVar1 + 0xc) + *(int *)(iVar1 + 0x10) * 0x24 + 0xc) = 0;
      uVar3 = *(int *)(iVar1 + 0x10) + 1;
      uVar6 = *(uint *)(iVar1 + 8);
      *(uint *)(iVar1 + 0x10) = uVar3;
      if (*(ushort *)(iVar1 + 0x5a) <= uVar3) {
        *(undefined4 *)(iVar1 + 0x10) = 0;
        uVar3 = 0;
      }
      if (uVar3 == uVar6) goto LAB_001ccb84;
    }
    uVar3 = uVar3 + 1;
    *(uint *)(iVar1 + 0x10) = uVar3;
    if (*(ushort *)(iVar1 + 0x5a) <= uVar3) {
      *(undefined4 *)(iVar1 + 0x10) = 0;
      uVar3 = 0;
    }
  }
LAB_001ccb84:
  _raw_spin_unlock_bh(iVar1 + 0x38);
  return 0;
}

