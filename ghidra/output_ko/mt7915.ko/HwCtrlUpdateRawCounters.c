// module: mt7915.ko
// function: HwCtrlUpdateRawCounters @ 0xaee90
// size: 68 bytes
//

undefined4 HwCtrlUpdateRawCounters(undefined4 param_1)

{
  if (3 < DebugLevel) {
    printk("%s(line:%d)\n","HwCtrlUpdateRawCounters",299);
  }
  asic_update_raw_counters(param_1);
  return 0;
}

