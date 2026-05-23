// compatible: zte,zx279127-i2c
// function: FUN_c02a9a90 @ 0xc02a9a90
// found via struct field ptr -> 0xc02a9a90
// total struct-refs for compat: 2
//

undefined4 FUN_c02a9a90(int param_1)

{
  int iVar1;
  
  iVar1 = *(int *)(param_1 + 0x68);
  *(undefined4 *)(param_1 + 0x68) = 0;
  FUN_c02a79ac(iVar1 + 0x18);
  if (*(int *)(iVar1 + 4) != 0) {
    FUN_c004cf1c(*(int *)(iVar1 + 4),iVar1);
  }
  FUN_c00a3824(iVar1);
  return 0;
}

