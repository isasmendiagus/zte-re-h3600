// module: mt7915.ko
// function: DfsZeroHandOffRecovery @ 0x2380a8
// size: 116 bytes
//

void DfsZeroHandOffRecovery(undefined4 param_1,int param_2)

{
  if (param_2 == 0) {
    return;
  }
  if (*(int *)(param_2 + 0x3fe4) == 0) {
    return;
  }
  if (*(char *)(*(int *)(param_2 + 0x3fe4) + 4) != '\x02') {
    return;
  }
  mtRddControl(param_1,0x38,0,0,0);
  if (DebugLevel < 3) {
    return;
  }
  printk("%s: Resume BF.\n","DfsZeroHandOffRecovery");
  return;
}

