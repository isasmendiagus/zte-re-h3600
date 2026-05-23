// module: mt7915.ko
// function: DfsSwitchCheck @ 0x23278c
// size: 148 bytes
//

undefined4 DfsSwitchCheck(int param_1,uint param_2,int param_3)

{
  undefined4 uVar1;
  
  if (*(char *)(param_1 + (param_3 + 0x51bb9) * 0x20 + 8) == '\x02' && 0xe < param_2) {
    if (DebugLevel < 1) {
      uVar1 = 1;
    }
    else {
      printk("[DfsSwitchCheck]: DFS ByPass TX calibration.\n");
      uVar1 = 1;
    }
  }
  else {
    uVar1 = 0;
    if (2 < DebugLevel) {
      printk("[DfsSwitchCheck]: NON DFS calibration.\n");
    }
  }
  return uVar1;
}

