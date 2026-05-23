// module: mt7915.ko
// function: pci_tx_dma_done_handle @ 0x1ce060
// size: 208 bytes
//

undefined4 pci_tx_dma_done_handle(int param_1,undefined4 param_2)

{
  int iVar1;
  int iVar2;
  int iVar3;
  int iVar4;
  int iVar5;
  
  iVar3 = (int)(short)param_2;
  iVar4 = *(int *)("Get_RBIST_Raw_Data_Proc" + param_1 + 0x14);
  iVar1 = hc_get_hif_ctrl(*(undefined4 *)(param_1 + 0xa797a0));
  iVar5 = *(int *)(*(int *)(iVar1 + 8) + iVar3 * 4);
  hif_free_txd(param_1,param_2);
  iVar1 = hc_get_hif_ctrl(*(undefined4 *)(param_1 + 0xa797a0));
  iVar1 = *(int *)(*(int *)(iVar1 + 8) + iVar3 * 4);
  iVar2 = *(uint *)(iVar1 + 0x10) - 1;
  if (*(uint *)(iVar1 + 0x10) <= *(uint *)(iVar1 + 0x28)) {
    iVar2 = iVar2 + (uint)*(ushort *)(iVar1 + 0x5a);
  }
  if (*(uint *)(iVar5 + 0x1c) <= iVar2 - *(uint *)(iVar1 + 0x28)) {
    iVar1 = hc_get_hif_ctrl(*(undefined4 *)(param_1 + 0xa797a0));
    if ((*(uint *)(*(int *)(*(int *)(iVar1 + 8) + iVar3 * 4) + 0x14) & 1) != 0) {
      iVar1 = hc_get_hif_ctrl(*(undefined4 *)(param_1 + 0xa797a0));
      _clear_bit(0,*(int *)(*(int *)(iVar1 + 8) + iVar3 * 4) + 0x14);
      (**(code **)(iVar4 + 0x3c))(param_1,*(undefined1 *)(iVar5 + 0x59));
      return 0;
    }
  }
  return 0;
}

