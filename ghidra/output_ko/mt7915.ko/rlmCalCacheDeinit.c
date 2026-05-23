// module: mt7915.ko
// function: rlmCalCacheDeinit @ 0x1c8664
// size: 52 bytes
//

undefined4 rlmCalCacheDeinit(int *param_1)

{
  if (*param_1 != 0) {
    os_free_mem(*param_1);
    *param_1 = 0;
    return 1;
  }
  return 0;
}

