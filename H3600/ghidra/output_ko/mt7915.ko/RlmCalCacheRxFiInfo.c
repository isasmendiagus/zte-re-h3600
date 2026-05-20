// module: mt7915.ko
// function: RlmCalCacheRxFiInfo @ 0x1c87dc
// size: 128 bytes
//

undefined4 RlmCalCacheRxFiInfo(uint *param_1,void *param_2,int param_3)

{
  if (param_2 == (void *)0x0) {
    return 0;
  }
  if (param_3 == 0x364) {
    if (param_1 != (uint *)0x0) {
      os_move_mem(param_1 + 0x2c3,param_2,0x364);
      *param_1 = *param_1 | 8;
      return 1;
    }
  }
  else if (3 < DebugLevel) {
    printk("P_RXFI_CAL_INFO_T: length mismatch=%d\n",param_3);
    return 0;
  }
  return 0;
}

