// compatible: snps,dwc3
// function: FUN_c00aa818 @ 0xc00aa818
// found via struct field ptr -> 0xc00aa818
// total struct-refs for compat: 2
//

void FUN_c00aa818(int param_1)

{
  uint uVar1;
  
  if (*(int *)(param_1 + 0x40) != 0) {
    FUN_c00bbb50();
  }
  uVar1 = *(uint *)(param_1 + 8);
  FUN_c00aa548(param_1);
  uVar1 = uVar1 & 0xfffff;
  FUN_c047121c(DAT_c00aa7f8);
  FUN_c0183548(DAT_c00aa7fc,uVar1);
  if ((int)uVar1 < (int)DAT_c06835a0) {
    DAT_c06835a0 = uVar1;
  }
  FUN_c04712ec(DAT_c00aa7f8);
  return;
}

