// module: mt7915.ko
// function: AsicSleepAutoWakeup @ 0x132344
// size: 112 bytes
//

void AsicSleepAutoWakeup(undefined4 param_1,int param_2,undefined4 param_3,undefined4 param_4)

{
  if (3 < DebugLevel) {
    printk("%s(%d): pStaCfg(0x%p)\n","AsicSleepAutoWakeup",0x1ee,param_2);
  }
  *(undefined2 *)(param_2 + 0x2124a8) = *(undefined2 *)(param_2 + 0x2124a6);
  hif_sta_sleep_auto_wakeup(param_1,param_2,param_2 + 0x212000,param_4);
  return;
}

