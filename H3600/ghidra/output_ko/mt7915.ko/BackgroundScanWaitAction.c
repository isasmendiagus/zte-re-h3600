// module: mt7915.ko
// function: BackgroundScanWaitAction @ 0x22cd30
// size: 72 bytes
//

void BackgroundScanWaitAction(int param_1)

{
  if (2 < DebugLevel) {
    printk("%s ===============>\n","BackgroundScanWaitAction");
  }
  *(undefined4 *)(param_1 + 0xa79184) = 4;
  return;
}

