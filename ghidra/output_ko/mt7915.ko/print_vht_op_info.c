// module: mt7915.ko
// function: print_vht_op_info @ 0x203928
// size: 188 bytes
//

void print_vht_op_info(byte *param_1)

{
  char *apcStack_20 [5];
  
  apcStack_20[0] = "20/40M";
  apcStack_20[1] = &DAT_003124e4;
  apcStack_20[2] = &DAT_003124e8;
  apcStack_20[3] = "80+80M";
  if ((0 < DebugLevel) &&
     (printk("VHT Operation Infomation: 0x%02X%02X%02X\n",*param_1,param_1[1],param_1[2]),
     0 < DebugLevel)) {
    printk("     - Channel Width: %u (%s)\n",(uint)*param_1,apcStack_20[*param_1]);
    if (0 < DebugLevel) {
      printk("     - Channel Center Frequency Segment 0: %u\n",param_1[1]);
      if (0 < DebugLevel) {
        printk("     - Channel Center Frequency Segment 1: %u\n",param_1[2]);
        return;
      }
    }
  }
  return;
}

