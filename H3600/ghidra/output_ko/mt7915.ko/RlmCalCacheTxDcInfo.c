// module: mt7915.ko
// function: RlmCalCacheTxDcInfo @ 0x1c8764
// size: 120 bytes
//

undefined4 RlmCalCacheTxDcInfo(uint *param_1,void *param_2,int param_3)

{
  if (param_3 == 0x514) {
    if (param_1 != (uint *)0x0) {
      os_move_mem(param_1 + 0x17e,param_2,0x514);
      *param_1 = *param_1 | 4;
      return 1;
    }
    return 1;
  }
  if (DebugLevel < 4) {
    return 0;
  }
  printk("P_TXDC_CAL_INFO_T: length mismatch=%d\n",param_3);
  return 0;
}

