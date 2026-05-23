// module: mt7915.ko
// function: os_kref_put @ 0x245bd0
// size: 100 bytes
//

undefined4 os_kref_put(int *param_1,code *param_2,undefined4 param_3,undefined4 param_4)

{
  bool bVar1;
  int iVar2;
  
  if (param_2 == (code *)0x0) {
    warn_slowpath_null("include/linux/kref.h",0x47,param_3,param_4,param_4);
  }
  DataMemoryBarrier(0xb);
  HintPreloadDataForWrite(param_1);
  do {
    iVar2 = *param_1;
    bVar1 = (bool)hasExclusiveAccess(param_1);
  } while (!bVar1);
  *param_1 = iVar2 + -1;
  DataMemoryBarrier(0xb);
  if (iVar2 + -1 == 0) {
    (*param_2)(param_1);
    return 1;
  }
  return 0;
}

