// module: mt7915.ko
// function: RlmCalCacheTxIqInfo @ 0x1c86fc
// size: 104 bytes
//

undefined4 RlmCalCacheTxIqInfo(uint *param_1,void *param_2,int param_3)

{
  if (param_3 == 0x514) {
    if (param_1 != (uint *)0x0) {
      os_move_mem(param_1 + 0x39,param_2,0x514);
      *param_1 = *param_1 | 2;
      return 1;
    }
  }
  else if (3 < DebugLevel) {
    printk("P_TXIQ_CAL_INFO_T: length mismatch=%d\n",param_3);
  }
  return 0;
}

