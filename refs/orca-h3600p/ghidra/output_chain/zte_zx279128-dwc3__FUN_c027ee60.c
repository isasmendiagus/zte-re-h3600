// compatible: zte,zx279128-dwc3
// function: FUN_c027ee60 @ 0xc027ee60
// found via struct field ptr -> 0xc027ee60
// total struct-refs for compat: 2
//

undefined4 FUN_c027ee60(int param_1)

{
  int iVar1;
  undefined4 uVar2;
  
  iVar1 = *(int *)(param_1 + 0x68);
  uVar2 = *(undefined4 *)(iVar1 + 4);
  FUN_c02c3d60(uVar2);
  FUN_c02c3d34(uVar2);
  uVar2 = *(undefined4 *)(iVar1 + 8);
  FUN_c02c3d60(uVar2);
  FUN_c02c3d34(uVar2);
  uVar2 = *(undefined4 *)(iVar1 + 0xc);
  FUN_c02c3d60(uVar2);
  FUN_c02c3d34(uVar2);
  FUN_c01ed868(param_1 + 0x10,iVar1);
  *(undefined4 *)(param_1 + 0x68) = 0;
  FUN_c01e6f88(param_1 + 0x10,0,&LAB_c027ee4c);
  return 0;
}

