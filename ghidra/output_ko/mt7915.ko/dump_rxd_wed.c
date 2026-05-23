// module: mt7915.ko
// function: dump_rxd_wed @ 0x1cf0f4
// size: 156 bytes
//

void dump_rxd_wed(undefined4 param_1,undefined4 *param_2,undefined4 param_3,undefined4 param_4)

{
  undefined4 extraout_r2;
  
  if (DebugLevel < 1) {
    return;
  }
  printk("RxD:\n");
  if (DebugLevel < 1) {
    return;
  }
  printk("\tRxD DW0: 0x%x\n",*param_2);
  if (DebugLevel < 1) {
    return;
  }
  printk("\tRxD DW1: 0x%x\n",param_2[1]);
  if (DebugLevel < 1) {
    return;
  }
  printk("\tRxD DW2: 0x%x\n",param_2[2]);
  if (DebugLevel < 1) {
    return;
  }
  printk("\tRxD DW3: 0x%x\n",param_2[3],extraout_r2,param_4);
  return;
}

