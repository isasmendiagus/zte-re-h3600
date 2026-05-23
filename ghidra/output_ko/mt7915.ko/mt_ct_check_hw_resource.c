// module: mt7915.ko
// function: mt_ct_check_hw_resource @ 0x1c936c
// size: 196 bytes
//

undefined4 mt_ct_check_hw_resource(int param_1,undefined4 param_2,int param_3)

{
  int iVar1;
  undefined4 uVar2;
  uint uVar3;
  uint uVar4;
  undefined4 uVar5;
  
  iVar1 = hc_get_hif_ctrl(*(undefined4 *)(param_1 + 0xa797a0));
  uVar5 = *(undefined4 *)(iVar1 + 0x94);
  iVar1 = *(int *)(*(int *)(iVar1 + 8) + param_3 * 4);
  uVar2 = HcGetBandByWdev(param_2);
  uVar2 = token_tx_get_queue_by_band(uVar5,uVar2);
  uVar3 = pci_get_tx_resource_free_num_nolock(param_1,param_3);
  if (uVar3 < *(uint *)(iVar1 + 0x18)) {
    pci_inc_resource_full_cnt(param_1,param_3);
    pci_set_resource_state(param_1,param_3,0);
    return 1;
  }
  uVar3 = token_tx_get_free_cnt(uVar2);
  uVar4 = token_tx_get_lwmark(uVar2);
  if (uVar4 <= uVar3) {
    return 0;
  }
  token_tx_inc_full_cnt(uVar2);
  token_tx_set_state(uVar2,0);
  return 3;
}

