// module: mt7915.ko
// function: MeasureReqTabInit @ 0x13e5cc
// size: 120 bytes
//

undefined4 MeasureReqTabInit(int param_1)

{
  os_alloc_mem(param_1,param_1 + 0x795978,0x1104);
  if (*(int *)(param_1 + 0x795978) != 0) {
    __memzero(*(int *)(param_1 + 0x795978),0x1104);
    *(undefined4 *)(param_1 + 0x795974) = 0;
    return 0;
  }
  if (DebugLevel < 0) {
    return 1;
  }
  printk("%s Fail to alloc memory for pAd->CommonCfg.pMeasureReqTab.\n","MeasureReqTabInit");
  return 1;
}

