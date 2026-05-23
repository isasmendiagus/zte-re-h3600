// module: mt7915.ko
// function: WscSkipTurnOffLEDTimer @ 0x1ed0d8
// size: 48 bytes
//

void WscSkipTurnOffLEDTimer(undefined4 param_1,int param_2)

{
  int iVar1;
  
  iVar1 = DebugLevel;
  *(undefined1 *)(param_2 + 0x292c) = 0;
  if (iVar1 < 3) {
    return;
  }
  printk("%s: Allow the NIC to turn off the WPS LED again.\n","WscSkipTurnOffLEDTimer");
  return;
}

