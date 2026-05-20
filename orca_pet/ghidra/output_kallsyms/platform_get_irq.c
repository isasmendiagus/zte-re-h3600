// kallsyms symbol: platform_get_irq
// string @ 0xc05feb8c, .value @ 0xc05ef818 = 0xc01ec070
// Function: FUN_c01ec070 @ 0xc01ec070
//

int FUN_c01ec070(int param_1,int param_2)

{
  int iVar1;
  int iVar2;
  int *piVar3;
  bool bVar4;
  
  if (*(int *)(param_1 + 0x124) != 0) {
    iVar1 = FUN_c02c0d38();
    iVar2 = iVar1 + 0x205;
    if (iVar1 != -0x205) {
      iVar2 = iVar1;
    }
    if (iVar2 < 0 == (iVar1 == -0x205 && SBORROW4(iVar1,-0x205))) {
      return iVar1;
    }
  }
  if (*(int *)(param_1 + 0x168) != 0) {
    piVar3 = *(int **)(param_1 + 0x16c);
    iVar2 = 0;
    do {
      iVar2 = iVar2 + 1;
      if (((piVar3[3] & 0x1f00U) == 0x400) && (bVar4 = param_2 == 0, param_2 = param_2 + -1, bVar4))
      {
        if (piVar3 == (int *)0x0) {
          return -6;
        }
        if ((piVar3[3] & 0xffU) != 0) {
          iVar2 = thunk_FUN_c004bd84(*piVar3);
          *(uint *)(iVar2 + 0x10) = piVar3[3] & 0xfU | *(uint *)(iVar2 + 0x10) & 0xfffffff0;
          return *piVar3;
        }
        return *piVar3;
      }
      piVar3 = piVar3 + 7;
    } while (iVar2 != *(int *)(param_1 + 0x168));
  }
  return -6;
}

