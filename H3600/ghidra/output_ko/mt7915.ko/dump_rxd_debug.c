// module: mt7915.ko
// function: dump_rxd_debug @ 0x1cef2c
// size: 224 bytes
//

void dump_rxd_debug(undefined4 param_1,undefined4 *param_2)

{
  if (((0 < DebugLevel) && (printk("RxD:\n"), 0 < DebugLevel)) &&
     (printk("\tSDPtr0/SDLen0/LastSec0=0x%x/0x%x/0x%x\n",*param_2,
             (uint)*(byte *)((int)param_2 + 6) | (*(byte *)((int)param_2 + 7) & 0x3f) << 8,
             ((uint)*(byte *)((int)param_2 + 7) << 0x19) >> 0x1f), 0 < DebugLevel)) {
    printk("\tQID/DIDX/CIDX/SW_INFO=0x%x/0x%x/0x%x/0x%x\n",
           ((uint)*(byte *)((int)param_2 + 5) << 0x1a) >> 0x1e,
           (uint)*(byte *)(param_2 + 1) | (*(byte *)((int)param_2 + 5) & 0xf) << 8,
           (uint)*(byte *)(param_2 + 2) | (*(byte *)((int)param_2 + 9) & 0xf) << 8,
           (uint)*(byte *)((int)param_2 + 10) << 4 | (uint)(*(byte *)((int)param_2 + 9) >> 4) |
           (uint)*(byte *)((int)param_2 + 0xb) << 0xc);
    if (0 < DebugLevel) {
      printk("\tDDONE=0x%x\n",*(byte *)((int)param_2 + 7) >> 7);
      return;
    }
  }
  return;
}

