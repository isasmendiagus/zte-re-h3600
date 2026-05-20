// module: mt7915.ko
// function: DfsSetCalibration @ 0x235194
// size: 120 bytes
//

void DfsSetCalibration(undefined4 param_1,int param_2)

{
  if (param_2 != 0) {
    if (2 < DebugLevel) {
      printk("Disable DFS calibration in firmware.\n");
    }
    mtRddControl(param_1,0x35,0,0,0);
    return;
  }
  if (DebugLevel < 3) {
    return;
  }
  printk("Enable DFS calibration in firmware.\n");
  return;
}

