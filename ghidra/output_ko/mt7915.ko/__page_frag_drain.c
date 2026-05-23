// module: mt7915.ko
// function: __page_frag_drain @ 0x2601ac
// size: 44 bytes
//

void __page_frag_drain(int param_1,undefined4 param_2,int param_3)

{
  bool bVar1;
  int *piVar2;
  
  piVar2 = (int *)(param_1 + 0x10);
  HintPreloadDataForWrite(piVar2);
  do {
    bVar1 = (bool)hasExclusiveAccess(piVar2);
  } while (!bVar1);
  *piVar2 = *piVar2 - (param_3 + -1);
  __free_pages();
  return;
}

