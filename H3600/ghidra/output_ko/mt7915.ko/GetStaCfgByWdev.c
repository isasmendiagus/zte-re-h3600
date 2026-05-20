// module: mt7915.ko
// function: GetStaCfgByWdev @ 0x14a9d8
// size: 72 bytes
//

int GetStaCfgByWdev(undefined4 param_1,int param_2)

{
  int iVar1;
  
  if (param_2 == 0) {
    return 0;
  }
  iVar1 = *(int *)(param_2 + 4);
  if (iVar1 == 0) {
    return 0;
  }
  if (*(int *)(param_2 + 0x14) == 2) {
    return iVar1;
  }
  if (*(int *)(param_2 + 0x14) == 0x100) {
    return *(int *)(*(int *)(iVar1 + 0x4140) + 4);
  }
  return 0;
}

