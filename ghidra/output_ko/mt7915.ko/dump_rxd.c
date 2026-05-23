// module: mt7915.ko
// function: dump_rxd @ 0x1cee80
// size: 172 bytes
//

void dump_rxd(undefined4 param_1,undefined4 *param_2)

{
  if (DebugLevel < 1) {
    return;
  }
  printk("RxD:\n");
  if (DebugLevel < 1) {
    return;
  }
  printk("\tSDPtr0/SDLen0/LastSec0=0x%x/0x%x/0x%x\n",*param_2,
         (uint)*(byte *)((int)param_2 + 6) | (*(byte *)((int)param_2 + 7) & 0x3f) << 8,
         ((uint)*(byte *)((int)param_2 + 7) << 0x19) >> 0x1f);
  if (DebugLevel < 1) {
    return;
  }
  printk("\tSDPtr1/SDLen1/LastSec1=0x%x/0x%x/0x%x\n",param_2[2],
         (uint)*(byte *)(param_2 + 1) | (*(byte *)((int)param_2 + 5) & 0x3f) << 8,
         ((uint)*(byte *)((int)param_2 + 5) << 0x19) >> 0x1f);
  if (DebugLevel < 1) {
    return;
  }
  printk("\tDDONE=0x%x\n",*(byte *)((int)param_2 + 7) >> 7);
  return;
}

