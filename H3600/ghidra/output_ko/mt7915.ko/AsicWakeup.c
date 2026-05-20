// module: mt7915.ko
// function: AsicWakeup @ 0x1323b8
// size: 108 bytes
//

void AsicWakeup(undefined4 param_1,undefined4 param_2,undefined4 param_3,undefined4 param_4)

{
  if (3 < DebugLevel) {
    printk("%s(%d): pStaCfg(0x%p)\n","AsicWakeup",0x207,param_3);
    if (3 < DebugLevel) {
      printk("--> AsicWakeup\n");
    }
  }
  hif_sta_wakeup(param_1,param_2,param_3,param_4);
  return;
}

