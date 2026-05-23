// module: mt7915.ko
// function: RlmCalCacheRxFdInfo @ 0x1c885c
// size: 160 bytes
//

undefined4 RlmCalCacheRxFdInfo(uint *param_1,void *param_2,int param_3,undefined4 param_4)

{
  if (param_2 != (void *)0x0) {
    if (param_3 == 0x548) {
      if (param_1 != (uint *)0x0 && *(uint *)((int)param_2 + 4) < 9) {
        os_move_mem(param_1 + *(uint *)((int)param_2 + 4) * 0x152 + 0x39c,param_2,0x548);
        *param_1 = *param_1 | 1 << (*(int *)((int)param_2 + 4) + 4U & 0xff);
        return 1;
      }
    }
    else if (3 < DebugLevel) {
      printk("P_RXFD_CAL_INFO_T: length mismatch=%d\n",param_3,param_3,DebugLevel,param_4);
      return 0;
    }
  }
  return 0;
}

