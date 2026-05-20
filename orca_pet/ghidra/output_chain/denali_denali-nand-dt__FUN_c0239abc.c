// compatible: denali,denali-nand-dt
// function: FUN_c0239abc @ 0xc0239abc
// found via struct field ptr -> 0xc0239abc
// total struct-refs for compat: 2
//

undefined4 FUN_c0239abc(int param_1)

{
  int iVar1;
  
  iVar1 = *(int *)(param_1 + 0x68);
  FUN_c023a218(iVar1);
  FUN_c02c3d60(*(undefined4 *)(iVar1 + 0x688));
  return 0;
}

