// module: mt7915.ko
// function: ZeroWait_DFS_collision_report @ 0x237ec4
// size: 176 bytes
//

void ZeroWait_DFS_collision_report
               (undefined4 param_1,undefined4 param_2,undefined4 param_3,undefined4 param_4)

{
  if (DebugLevel < 1) {
    if (radar_detected_callback_func == (code *)0x0) {
      return;
    }
  }
  else {
    printk(&_LC182,"ZeroWait_DFS_collision_report",param_2,param_3,param_4);
    if (radar_detected_callback_func == (code *)0x0) {
      return;
    }
    if (0 < DebugLevel) {
      printk(&_LC183,"ZeroWait_DFS_collision_report");
    }
  }
                    /* WARNING: Could not recover jumptable at 0x00237f14. Too many branches */
                    /* WARNING: Treating indirect jump as call */
  (*radar_detected_callback_func)(param_2,param_3,param_4);
  return;
}

