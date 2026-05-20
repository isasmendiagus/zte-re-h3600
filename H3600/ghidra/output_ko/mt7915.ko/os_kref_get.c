// module: mt7915.ko
// function: os_kref_get @ 0x245b74
// size: 92 bytes
//

void os_kref_get(int *param_1)

{
  bool bVar1;
  int iVar2;
  
  DataMemoryBarrier(0xb);
  HintPreloadDataForWrite(param_1);
  do {
    iVar2 = *param_1;
    bVar1 = (bool)hasExclusiveAccess(param_1);
  } while (!bVar1);
  *param_1 = iVar2 + 1;
  DataMemoryBarrier(0xb);
  if (iVar2 + 1 < 2) {
    if (_LANCHOR3 == '\0') {
      warn_slowpath_null("include/linux/kref.h",0x2f);
      _LANCHOR3 = 1;
      return;
    }
    return;
  }
  return;
}

