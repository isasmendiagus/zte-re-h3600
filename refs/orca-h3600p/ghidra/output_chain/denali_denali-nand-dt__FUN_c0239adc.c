// compatible: denali,denali-nand-dt
// function: FUN_c0239adc @ 0xc0239adc
// found via struct field ptr -> 0xc0239adc
// total struct-refs for compat: 2
//

undefined4 FUN_c0239adc(int param_1)

{
  int iVar1;
  
  iVar1 = *(int *)(param_1 + 0x68);
  FUN_c023c8f4(iVar1);
  FUN_c02c3d60(*(undefined4 *)(iVar1 + 0x630));
  return 0;
}

