// module: mt7915.ko
// function: rlmCalCacheInit @ 0x1c8604
// size: 96 bytes
//

undefined4 rlmCalCacheInit(undefined4 param_1,undefined4 *param_2)

{
  int iVar1;
  
  iVar1 = os_alloc_mem(param_1,param_2,0x3df8);
  if (iVar1 == 0) {
    os_zero_mem(*param_2,0x3df8);
    return 1;
  }
  if (DebugLevel < 1) {
    return 0;
  }
  printk("fail to alloca rlmCalCache size=%zu\n",0x3df8);
  return 0;
}

