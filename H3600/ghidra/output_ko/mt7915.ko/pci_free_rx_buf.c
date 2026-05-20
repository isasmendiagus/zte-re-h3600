// module: mt7915.ko
// function: pci_free_rx_buf @ 0x1ca790
// size: 128 bytes
//

void pci_free_rx_buf(undefined4 param_1,int param_2)

{
  int iVar1;
  undefined2 extraout_r1;
  undefined2 extraout_r1_00;
  
  iVar1 = hc_get_hif_ctrl();
  iVar1 = *(int *)(*(int *)(iVar1 + 4) + param_2 * 4);
  if (*(short *)(iVar1 + 0x2c) == 1) {
    __aeabi_idivmod(*(ushort *)(iVar1 + 0x22) + 1,*(undefined2 *)(iVar1 + 0x24));
    *(undefined2 *)(iVar1 + 0x22) = extraout_r1;
    return;
  }
  if (*(short *)(iVar1 + 0x2c) != 2) {
    if (DebugLevel < 0) {
      return;
    }
    printk("%s: fail, rx_ring->cur_free_buf_len = %d\n","pci_free_rx_buf");
    return;
  }
  __aeabi_idivmod(*(ushort *)(iVar1 + 0x42) + 1,*(undefined2 *)(iVar1 + 0x44));
  *(undefined2 *)(iVar1 + 0x42) = extraout_r1_00;
  return;
}

