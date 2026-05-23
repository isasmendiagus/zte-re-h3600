// compatible: zte,ZX279127-uart
// function: FUN_c01df8d8 @ 0xc01df8d8
// found via struct field ptr -> 0xc01df8d8
// total struct-refs for compat: 2
//

undefined4 FUN_c01df8d8(int param_1)

{
  int *piVar1;
  int *piVar2;
  int iVar3;
  
  iVar3 = *(int *)(param_1 + 0x68);
  FUN_c01de414(DAT_c01df914,iVar3);
  piVar1 = DAT_c01df918 + 0xe;
  piVar2 = DAT_c01df918;
  do {
    piVar2 = piVar2 + 1;
    if (*piVar2 == iVar3) {
      *piVar2 = 0;
    }
  } while (piVar2 != piVar1);
  return 0;
}

