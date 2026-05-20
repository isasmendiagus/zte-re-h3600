// module: mt7915.ko
// function: _AndesQueueTailCmdMsg @ 0x1a4640
// size: 40 bytes
//

void _AndesQueueTailCmdMsg(int param_1,int param_2,undefined4 param_3)

{
  int iVar1;
  int *piVar2;
  
  *(undefined4 *)(param_2 + 0x18) = param_3;
  piVar2 = *(int **)(param_1 + 4);
  iVar1 = *piVar2;
  *(int **)(param_2 + 0x4c) = piVar2;
  *(int *)(param_2 + 0x48) = iVar1;
  *(int *)(*piVar2 + 4) = param_2 + 0x48;
  *piVar2 = param_2 + 0x48;
  return;
}

