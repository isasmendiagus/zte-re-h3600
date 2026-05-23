// module: mt7915.ko
// function: HwCtrlSleepAutoWakeup @ 0xaef30
// size: 24 bytes
//

undefined4
HwCtrlSleepAutoWakeup(undefined4 param_1,int param_2,undefined4 param_3,undefined4 param_4)

{
  AsicSleepAutoWakeup(param_1,**(undefined4 **)(param_2 + 8),param_3,*(undefined4 **)(param_2 + 8),
                      param_4);
  return 0;
}

