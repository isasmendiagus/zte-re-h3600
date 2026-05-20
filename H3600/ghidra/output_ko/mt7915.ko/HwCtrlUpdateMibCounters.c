// module: mt7915.ko
// function: HwCtrlUpdateMibCounters @ 0xaf00c
// size: 68 bytes
//

undefined4 HwCtrlUpdateMibCounters(undefined4 param_1)

{
  if (3 < DebugLevel) {
    printk("%s(line:%d)\n","HwCtrlUpdateMibCounters",0x132);
  }
  asic_update_mib_bucket(param_1);
  return 0;
}

