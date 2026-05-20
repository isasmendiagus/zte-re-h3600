// module: rtkatm.ko
// function: RecalPerVCNumber @ 0x10de4
// size: 56 bytes
//

void RecalPerVCNumber(int param_1,int param_2)

{
  int *piVar1;
  int iVar2;
  int iVar3;
  
  iVar3 = param_1 + 0x3c0;
  iVar2 = 0;
  do {
    piVar1 = (int *)(param_1 + 0x10);
    param_1 = param_1 + 0x3c;
    if (*piVar1 != 0) {
      iVar2 = iVar2 + 1;
    }
  } while (param_1 != iVar3);
  if (iVar2 + param_2 < 0x11) {
    total_pvc_number = iVar2 + param_2;
  }
  return;
}

