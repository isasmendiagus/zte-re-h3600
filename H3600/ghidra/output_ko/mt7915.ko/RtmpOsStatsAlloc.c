// module: mt7915.ko
// function: RtmpOsStatsAlloc @ 0x245aa4
// size: 112 bytes
//

undefined4 RtmpOsStatsAlloc(int *param_1,int *param_2,undefined4 param_3,undefined4 param_4)

{
  os_alloc_mem(0,param_1,0x5c,param_4,param_4);
  if (*param_1 == 0) {
    return 0;
  }
  __memzero(*param_1,0x5c);
  os_alloc_mem(0,param_2,0x20);
  if (*param_2 != 0) {
    __memzero(*param_2,0x20);
    return 1;
  }
  os_free_mem(*param_1);
  return 0;
}

