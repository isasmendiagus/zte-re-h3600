// compatible: zte,zx279127-i2c
// function: FUN_c02a8e10 @ 0xc02a8e10
// found via struct field ptr -> 0xc02a8e10
// total struct-refs for compat: 2
//

undefined4 FUN_c02a8e10(int param_1)

{
  int iVar1;
  
  iVar1 = *(int *)(param_1 + 0x68);
  *(undefined4 *)(param_1 + 0x68) = 0;
  FUN_c02a6d50(iVar1 + 0x18);
  if (*(int *)(iVar1 + 4) != 0) {
    FUN_c004ccd4(*(int *)(iVar1 + 4),iVar1);
  }
  FUN_c00a35dc(iVar1);
  return 0;
}

