// compatible: snps,dwc3
// function: FUN_c027d434 @ 0xc027d434
// found via struct field ptr -> 0xc027d434
// total struct-refs for compat: 2
//

undefined4 FUN_c027d434(int param_1,undefined4 param_2,undefined4 param_3,undefined4 param_4)

{
  int *piVar1;
  int iVar2;
  int iVar3;
  
  iVar3 = *(int *)(param_1 + 0x68);
  piVar1 = (int *)FUN_c01eb908(param_1,0x200,0,param_4,param_4);
  *piVar1 = *piVar1 + -0xc100;
  FUN_c027ec44(iVar3);
  FUN_c027d2a8(iVar3);
  FUN_c027d170(iVar3);
  FUN_c027d2c0(iVar3);
  iVar2 = *(int *)(iVar3 + 0x2e4);
  if ((iVar2 != 0) && (*(code **)(iVar2 + 0x48) != (code *)0x0)) {
    (**(code **)(iVar2 + 0x48))(iVar2,1);
  }
  iVar2 = *(int *)(iVar3 + 0x2e8);
  if ((iVar2 != 0) && (*(code **)(iVar2 + 0x48) != (code *)0x0)) {
    (**(code **)(iVar2 + 0x48))(iVar2,1);
  }
  FUN_c027d3ec(iVar3);
  FUN_c01f1450(param_1 + 0x10,4);
  FUN_c01f1b4c(param_1 + 0x10,1);
  return 0;
}

