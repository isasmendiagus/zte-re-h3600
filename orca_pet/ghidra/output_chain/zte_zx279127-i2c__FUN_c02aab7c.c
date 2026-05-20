// compatible: zte,zx279127-i2c
// function: FUN_c02aab7c @ 0xc02aab7c
// found via struct field ptr -> 0xc02aab7c
// total struct-refs for compat: 2
//

int FUN_c02aab7c(int param_1,int param_2,undefined4 param_3,int param_4)

{
  int iVar1;
  int *piVar2;
  undefined1 local_14 [4];
  
  piVar2 = *(int **)(param_1 + 0x58);
  iVar1 = FUN_c0197174(param_3,10,local_14);
  if (-1 < iVar1) {
    iVar1 = (**(code **)(*piVar2 + 0x14))(piVar2,param_2 + 0x3f9603d0 >> 4);
    if (-1 < iVar1) {
      iVar1 = param_4;
    }
  }
  return iVar1;
}

