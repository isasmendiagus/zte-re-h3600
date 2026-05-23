// module: mt7915.ko
// function: mt7916_hif_init @ 0x188f84
// size: 184 bytes
//

/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */

void mt7916_hif_init(undefined4 *param_1,undefined4 param_2,undefined4 param_3,undefined4 param_4)

{
  int iVar1;
  
  *param_1 = 0xd20084;
  iVar1 = DebugLevel;
  param_1[1] = 0xd708c;
  param_1[0x31] = tx_ring_layout_pcie1;
  *(undefined1 *)(param_1 + 4) = 1;
  *(undefined1 *)((int)param_1 + 0x11) = 2;
  param_1[0x36] = mt7916_isr;
  param_1[0x1b1] = 0xc0;
  param_1[0x32] = rx_ring_layout_pcie1;
  if (0 < iVar1) {
    printk("<--%s()\n","mt7916_hif_init",0xc0,mt7916_isr,param_4);
  }
  iVar1 = multi_hif_entry_id_get(param_1);
  DataSynchronizationBarrier(0xe);
  if (___aeabi_idivmod != (code *)0x0) {
    (*___aeabi_idivmod)();
  }
  *(uint *)(param_1[0x2f] + 0xd7090) = iVar1 + 1U | 0x80000000;
  return;
}

