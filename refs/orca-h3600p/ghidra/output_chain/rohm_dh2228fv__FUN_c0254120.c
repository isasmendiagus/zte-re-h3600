// compatible: rohm,dh2228fv
// function: FUN_c0254120 @ 0xc0254120
// found via struct field ptr -> 0xc0254120
// total struct-refs for compat: 2
//

undefined4 FUN_c0254120(undefined4 *param_1)

{
  int iVar1;
  int iVar2;
  
  iVar2 = param_1[0x1a];
  iVar1 = *(int *)(iVar2 + 0x58);
  FUN_c046918c(s_SPI_s__d_removed_c05b3bf4,*param_1,param_1[1]);
  FUN_c0253e80(iVar1);
  *(undefined4 *)(*(int *)(*(int *)(iVar1 + 0x28) + 4) + 4) = 0;
  FUN_c02c3d60(*(undefined4 *)(iVar1 + 0x2c));
  thunk_FUN_c02c54dc(*(undefined4 *)(iVar1 + 0x2c));
  if (iVar2 != 0) {
    FUN_c01e6ecc(iVar2);
  }
  FUN_c00a3824(iVar2);
  FUN_c00a3824(*(undefined4 *)(iVar1 + 0x28));
  param_1[0x1a] = 0;
  return 0;
}

