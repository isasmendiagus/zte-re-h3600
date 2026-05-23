// compatible: snps,dwc3
// function: FUN_c00aaa9c @ 0xc00aaa9c
// found via struct field ptr -> 0xc00aaa9c
// total struct-refs for compat: 2
//

void FUN_c00aaa9c(int param_1)

{
  uint uVar1;
  
  if (*(int *)(param_1 + 0x40) != 0) {
    FUN_c00bbdd4();
  }
  uVar1 = *(uint *)(param_1 + 8);
  FUN_c00aa7cc(param_1);
  uVar1 = uVar1 & 0xfffff;
  FUN_c046feac(DAT_c00aaa7c);
  FUN_c0183808(DAT_c00aaa80,uVar1);
  if ((int)uVar1 < (int)DAT_c0693880) {
    DAT_c0693880 = uVar1;
  }
  FUN_c046ff7c(DAT_c00aaa7c);
  return;
}

