// compatible: snps,dwc3
// function: FUN_c027c7d8 @ 0xc027c7d8
// found via struct field ptr -> 0xc027c7d8
// total struct-refs for compat: 2
//

undefined4 FUN_c027c7d8(int param_1,undefined4 param_2,undefined4 param_3,undefined4 param_4)

{
  int *piVar1;
  int iVar2;
  int iVar3;
  
  iVar3 = *(int *)(param_1 + 0x68);
  piVar1 = (int *)FUN_c01ed784(param_1,0x200,0,param_4,param_4);
  *piVar1 = *piVar1 + -0xc100;
  FUN_c027dfe8(iVar3);
  FUN_c027c64c(iVar3);
  FUN_c027c514(iVar3);
  FUN_c027c664(iVar3);
  iVar2 = *(int *)(iVar3 + 0x2e4);
  if ((iVar2 != 0) && (*(code **)(iVar2 + 0x48) != (code *)0x0)) {
    (**(code **)(iVar2 + 0x48))(iVar2,1);
  }
  iVar2 = *(int *)(iVar3 + 0x2e8);
  if ((iVar2 != 0) && (*(code **)(iVar2 + 0x48) != (code *)0x0)) {
    (**(code **)(iVar2 + 0x48))(iVar2,1);
  }
  FUN_c027c790(iVar3);
  FUN_c01f32cc(param_1 + 0x10,4);
  FUN_c01f39c8(param_1 + 0x10,1);
  return 0;
}

