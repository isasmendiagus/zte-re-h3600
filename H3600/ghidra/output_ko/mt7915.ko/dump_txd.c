// module: mt7915.ko
// function: dump_txd @ 0x1c8eac
// size: 324 bytes
//

void dump_txd(undefined4 param_1,undefined4 *param_2)

{
  if (DebugLevel < 1) {
    return;
  }
  printk("TxD:\n");
  if (0 < DebugLevel) {
    printk("\tSDPtr0=0x%x\n",*param_2);
    if (DebugLevel < 1) {
      return;
    }
    printk("\tSDLen0=0x%x\n",
           (uint)*(byte *)((int)param_2 + 6) | (*(byte *)((int)param_2 + 7) & 0x3f) << 8);
    if (DebugLevel < 1) goto LAB_001c8fa4;
    printk("\tLastSec0=0x%x\n",((uint)*(byte *)((int)param_2 + 7) << 0x19) >> 0x1f);
    if (DebugLevel < 1) {
      return;
    }
    printk("\tSDPtr1=0x%x\n",param_2[2]);
  }
  if (DebugLevel < 1) {
    return;
  }
  printk("\tSDLen1=0x%x\n",(uint)*(byte *)(param_2 + 1) | (*(byte *)((int)param_2 + 5) & 0x3f) << 8)
  ;
  if (DebugLevel < 1) {
    return;
  }
  printk("\tLastSec1=0x%x\n",((uint)*(byte *)((int)param_2 + 5) << 0x19) >> 0x1f);
LAB_001c8fa4:
  if (DebugLevel < 1) {
    return;
  }
  printk("\tDMADONE=0x%x\n",*(byte *)((int)param_2 + 7) >> 7);
  if (DebugLevel < 1) {
    return;
  }
  printk("\tBurst=0x%x\n",*(byte *)((int)param_2 + 5) >> 7);
  return;
}

