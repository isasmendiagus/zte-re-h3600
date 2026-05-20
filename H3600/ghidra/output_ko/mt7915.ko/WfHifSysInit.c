// module: mt7915.ko
// function: WfHifSysInit @ 0x13a09c
// size: 240 bytes
//

void WfHifSysInit(int param_1)

{
  uint uVar1;
  int iVar2;
  undefined4 local_1c;
  
  if (2 < DebugLevel) {
    printk("%s()-->\n","WfHifSysInit");
  }
  hif_dma_disable(*(undefined4 *)(param_1 + 0xa797a0));
  if (2 < DebugLevel) {
    printk("%s():Disable WPDMA\n","WfHifSysInit");
  }
  if (0 < DebugLevel) {
    printk("Use alloc_skb\n");
  }
  uVar1 = hc_get_asic_cap(*(undefined4 *)(param_1 + 0xa797a0));
  if ((uVar1 & 0x800) != 0) {
    token_init(&local_1c,param_1);
    hc_set_ct_cb(*(undefined4 *)(param_1 + 0xa797a0),local_1c);
  }
  iVar2 = hif_init_txrx_mem(*(undefined4 *)(param_1 + 0xa797a0));
  if ((iVar2 == 0) && (iVar2 = hif_register_irq(*(undefined4 *)(param_1 + 0xa797a0)), iVar2 == 0)) {
    hif_init_task_group(*(undefined4 *)(param_1 + 0xa797a0));
    return;
  }
  return;
}

