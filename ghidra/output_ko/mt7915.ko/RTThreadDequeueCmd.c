// module: mt7915.ko
// function: RTThreadDequeueCmd @ 0xc4988
// size: 52 bytes
//

void RTThreadDequeueCmd(int *param_1,int *param_2)

{
  int iVar1;
  int iVar2;
  
  iVar1 = param_1[1];
  *param_2 = iVar1;
  if (iVar1 == 0) {
    return;
  }
  iVar2 = *param_1;
  iVar1 = *(int *)(param_1[1] + 0x10);
  *param_1 = iVar2 + -1;
  if (iVar2 + -1 == 0) {
    param_1[2] = 0;
  }
  param_1[1] = iVar1;
  return;
}

