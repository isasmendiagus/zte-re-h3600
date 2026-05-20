// module: mt7915.ko
// function: AdapterBlockAllocateMemory @ 0x244984
// size: 64 bytes
//

undefined4 AdapterBlockAllocateMemory(undefined4 param_1,int *param_2,int param_3)

{
  int iVar1;
  
  iVar1 = vmalloc(param_3);
  *param_2 = iVar1;
  if (iVar1 != 0) {
    if (param_3 != 0) {
      __memzero(iVar1,param_3);
    }
    return 0;
  }
  return 1;
}

