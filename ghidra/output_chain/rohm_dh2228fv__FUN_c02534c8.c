// compatible: rohm,dh2228fv
// function: FUN_c02534c8 @ 0xc02534c8
// found via struct field ptr -> 0xc02534c8
// total struct-refs for compat: 2
//

undefined4 FUN_c02534c8(undefined4 *param_1)

{
  int iVar1;
  int iVar2;
  
  iVar2 = param_1[0x1a];
  iVar1 = *(int *)(iVar2 + 0x58);
  FUN_c046ab98(s_SPI_s__d_removed_c05b4f20,*param_1,param_1[1]);
  FUN_c0253228(iVar1);
  *(undefined4 *)(*(int *)(*(int *)(iVar1 + 0x28) + 4) + 4) = 0;
  FUN_c02c30d4(*(undefined4 *)(iVar1 + 0x2c));
  thunk_FUN_c02c4850(*(undefined4 *)(iVar1 + 0x2c));
  if (iVar2 != 0) {
    FUN_c01e8d48(iVar2);
  }
  FUN_c00a35dc(iVar2);
  FUN_c00a35dc(*(undefined4 *)(iVar1 + 0x28));
  param_1[0x1a] = 0;
  return 0;
}

