// compatible: zte,zx279127-i2c
// function: FUN_c02a9ef0 @ 0xc02a9ef0
// found via struct field ptr -> 0xc02a9ef0
// total struct-refs for compat: 2
//

int FUN_c02a9ef0(int param_1,int param_2,undefined4 param_3,int param_4)

{
  int iVar1;
  int *piVar2;
  undefined1 local_14 [4];
  
  piVar2 = *(int **)(param_1 + 0x58);
  iVar1 = FUN_c0196bc0(param_3,10,local_14);
  if (-1 < iVar1) {
    iVar1 = (**(code **)(*piVar2 + 0x14))(piVar2,param_2 + 0x3f9705dc >> 4);
    if (-1 < iVar1) {
      iVar1 = param_4;
    }
  }
  return iVar1;
}

