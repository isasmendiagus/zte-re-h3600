// module: mt7915.ko
// function: mt_ct_get_hw_resource_state @ 0x1c9430
// size: 140 bytes
//

bool mt_ct_get_hw_resource_state
               (int param_1,undefined4 param_2,undefined4 param_3,undefined4 param_4)

{
  undefined1 uVar1;
  int iVar2;
  undefined4 uVar3;
  undefined4 uVar4;
  
  uVar3 = param_4;
  iVar2 = hc_get_hif_ctrl(*(undefined4 *)(param_1 + 0xa797a0));
  uVar1 = hif_get_resource_idx(*(undefined4 *)(param_1 + 0xa797a0),param_2,param_3,param_4,uVar3);
  uVar4 = *(undefined4 *)(iVar2 + 0x94);
  uVar3 = HcGetBandByWdev(param_2);
  uVar3 = token_tx_get_queue_by_band(uVar4,uVar3);
  iVar2 = pci_get_resource_state(param_1,uVar1);
  if (iVar2 != 0) {
    return true;
  }
  iVar2 = token_tx_get_state(uVar3);
  return iVar2 != 0;
}

