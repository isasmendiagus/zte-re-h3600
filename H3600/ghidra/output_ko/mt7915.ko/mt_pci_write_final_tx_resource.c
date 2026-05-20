// module: mt7915.ko
// function: mt_pci_write_final_tx_resource @ 0x1c9c24
// size: 76 bytes
//

void mt_pci_write_final_tx_resource(int param_1,byte *param_2,undefined2 param_3,uint param_4)

{
  int iVar1;
  
  iVar1 = hc_get_hif_ctrl(*(undefined4 *)(param_1 + 0xa797a0));
  iVar1 = *(int *)(*(int *)(iVar1 + 8) + (uint)*param_2 * 4);
  if (param_4 < *(ushort *)(iVar1 + 0x5a)) {
    **(undefined2 **)(*(int *)(iVar1 + 0xc) + param_4 * 0x24 + 0x1c) = param_3;
  }
  return;
}

