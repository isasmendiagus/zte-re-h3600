// module: mt7915.ko
// function: TpcReqTabInit @ 0x13ea94
// size: 120 bytes
//

undefined4 TpcReqTabInit(int param_1)

{
  os_alloc_mem(param_1,param_1 + 0x795980,0x204);
  if (*(int *)(param_1 + 0x795980) != 0) {
    __memzero(*(int *)(param_1 + 0x795980),0x204);
    *(undefined4 *)(param_1 + 0x79597c) = 0;
    return 0;
  }
  if (DebugLevel < 0) {
    return 1;
  }
  printk("%s Fail to alloc memory for pAd->CommonCfg.pTpcReqTab.\n","TpcReqTabInit");
  return 1;
}

