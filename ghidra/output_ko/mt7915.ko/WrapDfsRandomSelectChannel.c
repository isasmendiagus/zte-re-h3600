// module: mt7915.ko
// function: WrapDfsRandomSelectChannel @ 0x234640
// size: 152 bytes
//

void WrapDfsRandomSelectChannel(int param_1,undefined4 param_2,undefined4 param_3,int param_4)

{
  char cVar1;
  int iVar2;
  
  if (*(char *)(param_1 + 0x7953f1) == '\0') {
LAB_002346ac:
    DfsRandomSelectChannel(param_1,param_1 + 0x795130,param_2,param_3,param_4);
    return;
  }
  iVar2 = param_1 + 0x795000 + param_4;
  if (*(char *)(iVar2 + 0x130) == *(char *)(param_1 + 0x7953f1)) {
    cVar1 = *(char *)(param_1 + 0x7953f2);
    if (*(char *)(iVar2 + 0x134) == cVar1) {
      *(undefined1 *)(param_1 + 0x7953f1) = 0;
      *(undefined1 *)(param_1 + 0x7953f2) = 0;
      *(undefined2 *)(param_1 + 0x7953f4) = 0;
      goto LAB_002346ac;
    }
  }
  else {
    cVar1 = *(char *)(param_1 + 0x7953f2);
  }
  *(char *)(param_1 + param_4 + 0x795134) = cVar1;
  return;
}

