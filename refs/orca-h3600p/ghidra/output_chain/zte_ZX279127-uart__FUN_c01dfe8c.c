// compatible: zte,ZX279127-uart
// function: FUN_c01dfe8c @ 0xc01dfe8c
// found via struct field ptr -> 0xc01dfe8c
// total struct-refs for compat: 2
//

undefined4 FUN_c01dfe8c(int param_1)

{
  int *piVar1;
  int *piVar2;
  int iVar3;
  
  iVar3 = *(int *)(param_1 + 0x68);
  FUN_c01de9c8(DAT_c01dfec8,iVar3);
  piVar1 = DAT_c01dfecc + 0xe;
  piVar2 = DAT_c01dfecc;
  do {
    piVar2 = piVar2 + 1;
    if (*piVar2 == iVar3) {
      *piVar2 = 0;
    }
  } while (piVar2 != piVar1);
  return 0;
}

