// module: mt7915.ko
// function: ApCliHandleRxBroadcastFrame @ 0x699f0
// size: 96 bytes
//

bool ApCliHandleRxBroadcastFrame(undefined4 param_1,int param_2,int param_3)

{
  int iVar1;
  void *__s1;
  
  iVar1 = GetStaCfgByWdev(param_1,*(undefined4 *)(param_3 + 8));
  __s1 = *(void **)(param_2 + 0x30);
  iVar1 = memcmp(__s1,(void *)(iVar1 + 0x1b),6);
  if ((iVar1 != 0) && (iVar1 = lookup_rept_entry(param_1,__s1), iVar1 == 0)) {
    return *(int *)(param_3 + 0xadc) == 0;
  }
  return false;
}

