// module: mt7915.ko
// function: ge_get_swq_free_num @ 0xd21c0
// size: 48 bytes
//

int ge_get_swq_free_num(int param_1,int param_2)

{
  int iVar1;
  int iVar2;
  
  param_1 = param_1 + param_2 * 0x4018;
  iVar1 = *(int *)(param_1 + 0x28a34c);
  iVar2 = *(int *)(param_1 + 0x28a350);
  if (iVar1 < iVar2) {
    iVar1 = -iVar1;
  }
  else {
    iVar1 = 0x2000 - iVar1;
  }
  return iVar1 + iVar2;
}

