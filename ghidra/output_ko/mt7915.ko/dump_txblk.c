// module: mt7915.ko
// function: dump_txblk @ 0xc5d2c
// size: 284 bytes
//

void dump_txblk(undefined4 param_1,int param_2)

{
  printk("TxBlk Info\n");
  printk("\twdev=%p\n",*(undefined4 *)(param_2 + 0x10));
  printk("\tWCID=%d\n",*(undefined2 *)(param_2 + 0x1e));
  printk("\tWMM_Idx=%d\n",*(undefined1 *)(param_2 + 2));
  printk("\tQueIdx=%d\n",*(undefined1 *)(param_2 + 1));
  printk("\tWMM_Set=%d\n",*(undefined1 *)(param_2 + 0x20));
  printk("\tpMacEntry=%p\n",*(undefined4 *)(param_2 + 0x14));
  if (*(int *)(param_2 + 0x14) != 0) {
    printk("\t\tpMacEntry->wcid=%d\n",*(undefined2 *)(*(int *)(param_2 + 0x14) + 0xe0));
    printk("\t\tpMacEntry->tr_tb_idx=%d\n",*(undefined2 *)(*(int *)(param_2 + 0x14) + 0xe2));
  }
  printk("\tTR_Entry=%p\n",*(undefined4 *)(param_2 + 8));
  if (*(int *)(param_2 + 8) != 0) {
    printk("\t\tTR_Entry->wcid=%d\n",*(undefined2 *)(*(int *)(param_2 + 8) + 8));
  }
  printk("\tOpMode=%d\n",*(undefined1 *)(param_2 + 0x6d));
  printk("\tTxFrameType=%d\n",*(undefined1 *)(param_2 + 5));
  printk("\tTotalFragNum=%d\n",*(undefined1 *)(param_2 + 4));
  printk("\tUserPriority=%d\n",*(undefined1 *)(param_2 + 0x1c));
  return;
}

