// module: mt7915.ko
// function: dump_vht_op @ 0x2023b4
// size: 280 bytes
//

void dump_vht_op(undefined4 param_1,undefined1 *param_2)

{
  if (0 < DebugLevel) {
    printk("Dump VHT_OP IE\n");
  }
  hex_dump("VHT OP IE Raw Data",param_2,5);
  if (DebugLevel < 1) {
    return;
  }
  printk("VHT Operation Info Field\n");
  if (0 < DebugLevel) {
    printk("\tChannelWidth=%d\n",*param_2);
    if (DebugLevel < 1) {
      return;
    }
    printk("\tChannelCenterFrequency Seg 0=%d\n",param_2[1]);
    if (DebugLevel < 1) {
      return;
    }
    printk("\tChannelCenterFrequency Seg 1=%d\n",param_2[2]);
    if (DebugLevel < 1) {
      return;
    }
    printk("VHT Basic MCS Set Field\n");
  }
  if (DebugLevel < 1) {
    return;
  }
  printk("\tRxMCS Map_1SS=%d\n",param_2[3] & 3);
  if (DebugLevel < 1) {
    return;
  }
  printk("\tRxMCS Map_2SS=%d\n",((uint)(byte)param_2[3] << 0x1c) >> 0x1e);
  return;
}

