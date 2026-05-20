// module: mt7915.ko
// function: pci_kick_out_data_tx @ 0x1ca9fc
// size: 72 bytes
//

void pci_kick_out_data_tx(int param_1,undefined4 param_2,int param_3)

{
  int iVar1;
  
  iVar1 = hc_get_hif_ctrl(*(undefined4 *)(param_1 + 0xa797a0));
  iVar1 = *(int *)(*(int *)(iVar1 + 8) + param_3 * 4);
  _raw_spin_lock_bh(iVar1 + 0x34);
  hif_io_write32(*(undefined4 *)(param_1 + 0xa797a0),*(undefined4 *)(iVar1 + 0x24),
                 *(undefined4 *)(iVar1 + 0x28));
  _raw_spin_unlock_bh(iVar1 + 0x34);
  return;
}

