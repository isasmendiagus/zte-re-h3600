// module: mt7915.ko
// function: mt_ct_get_hw_resource_free_num @ 0x19b218
// size: 268 bytes
//

undefined4
mt_ct_get_hw_resource_free_num(int param_1,int param_2,int param_3,uint *param_4,uint *param_5)

{
  undefined4 uVar1;
  uint uVar2;
  uint uVar3;
  uint uVar4;
  uint uVar5;
  undefined4 uVar6;
  int iVar7;
  undefined8 uVar8;
  
  uVar8 = hc_get_hif_ctrl(*(undefined4 *)(param_1 + 0xa797a0));
  uVar1 = (undefined4)((ulonglong)uVar8 >> 0x20);
  if (param_2 == 0) {
    uVar1 = 0;
  }
  uVar6 = *(undefined4 *)((int)uVar8 + 0x94);
  iVar7 = *(int *)(*(int *)((int)uVar8 + 8) + param_3 * 4);
  if (param_2 != 0) {
    uVar1 = HcGetBandByWdev(param_2,uVar1);
  }
  uVar1 = token_tx_get_queue_by_band(uVar6,uVar1);
  uVar2 = pci_get_tx_resource_free_num_nolock(param_1,param_3);
  uVar5 = *(uint *)(iVar7 + 0x18);
  if (uVar2 < uVar5) {
    pci_inc_resource_full_cnt(param_1,param_3);
    pci_set_resource_state(param_1,param_3,0);
    return 3;
  }
  uVar3 = token_tx_get_free_cnt(uVar1);
  uVar4 = token_tx_get_lwmark(uVar1);
  if (uVar4 <= uVar3) {
    iVar7 = token_tx_get_lwmark();
    uVar2 = (1 - uVar5) + uVar2;
    uVar3 = (uVar3 + 1) - iVar7;
    uVar5 = uVar3;
    if (uVar2 <= uVar3) {
      uVar5 = uVar2;
    }
    *param_4 = uVar5;
    *param_5 = uVar3;
    return 0;
  }
  token_tx_inc_full_cnt(uVar1);
  token_tx_set_state(uVar1,0);
  return 1;
}

