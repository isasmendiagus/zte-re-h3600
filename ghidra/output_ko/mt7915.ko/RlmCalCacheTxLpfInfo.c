// module: mt7915.ko
// function: RlmCalCacheTxLpfInfo @ 0x1c8698
// size: 100 bytes
//

undefined4 RlmCalCacheTxLpfInfo(uint *param_1,void *param_2,int param_3)

{
  if (param_3 == 0xe0) {
    if (param_1 != (uint *)0x0) {
      os_move_mem(param_1 + 1,param_2,0xe0);
      *param_1 = *param_1 | 1;
      return 1;
    }
  }
  else if (3 < DebugLevel) {
    printk("P_TXLPF_CAL_INFO_T: length mismatch=%d\n",param_3);
  }
  return 0;
}

