// module: mt7915.ko
// function: WfHifSysExit @ 0x13a190
// size: 128 bytes
//

undefined4 WfHifSysExit(int param_1)

{
  uint uVar1;
  undefined4 local_14 [2];
  
  mt_wlan_hook_call(1,param_1,0);
  hif_reset_task_group(*(undefined4 *)(param_1 + 0xa797a0));
  hif_free_irq(*(undefined4 *)(param_1 + 0xa797a0));
  hif_reset_txrx_mem(*(undefined4 *)(param_1 + 0xa797a0));
  uVar1 = hc_get_asic_cap(*(undefined4 *)(param_1 + 0xa797a0));
  if ((uVar1 & 0x800) != 0) {
    local_14[0] = hc_get_ct_cb(*(undefined4 *)(param_1 + 0xa797a0));
    token_deinit(local_14);
  }
  hif_dma_reset(*(undefined4 *)(param_1 + 0xa797a0));
  FwOwn(param_1);
  return 0;
}

