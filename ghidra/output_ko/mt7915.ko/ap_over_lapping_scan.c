// module: mt7915.ko
// function: ap_over_lapping_scan @ 0x1109c
// size: 144 bytes
//

void ap_over_lapping_scan(int param_1,int param_2)

{
  if (param_2 == 0) {
    if (DebugLevel < 0) {
      return;
    }
    printk("%s() Invalid Mbss\n","ap_over_lapping_scan");
    return;
  }
  if (*(char *)(param_1 + 0x795947) == '\x01') {
    if (DebugLevel < 3) {
      return;
    }
    printk("Disable 20/40 BSSCoex Channel Scan(BssCoex=%d, 40MHzIntolerant=%d)\n",
           *(undefined1 *)(param_1 + 0x79564e));
    return;
  }
  if (*(char *)(param_1 + 0x79564e) != '\x01') {
    return;
  }
  if (DebugLevel < 1) {
    return;
  }
  printk("Enable 20/40 BSSCoex Channel Scan(BssCoex=%d)\n");
  return;
}

