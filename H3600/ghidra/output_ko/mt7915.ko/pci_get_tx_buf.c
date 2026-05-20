// module: mt7915.ko
// function: pci_get_tx_buf @ 0x1cc60c
// size: 88 bytes
//

int pci_get_tx_buf(undefined4 param_1,int param_2,int param_3,int param_4)

{
  int iVar1;
  
  iVar1 = hc_get_hif_ctrl();
  iVar1 = *(int *)(*(int *)(iVar1 + 8) + param_3 * 4);
  if (param_4 != 5) {
    return *(int *)(*(int *)(iVar1 + 0xc) + (*(uint *)(iVar1 + 0x28) & 0xffff) * 0x24 + 0x1c);
  }
  __memzero(param_2 + 0xc0,0x80);
  return param_2 + 0xc0;
}

