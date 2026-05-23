// compatible: zte,zx279128-smp
// function: FUN_c0014d64 @ 0xc0014d64
// found via struct field ptr -> 0xc0014d64
// total struct-refs for compat: 2
//

/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */

void FUN_c0014d64(uint param_1,uint param_2)

{
  int iVar1;
  undefined4 uVar2;
  undefined4 uVar3;
  undefined4 *puVar4;
  
  iVar1 = _DAT_c069e998;
  if ((param_1 & 0x1f) != 0) {
    uVar3 = FUN_c047125c(0xc069e9c8);
    *(uint *)(iVar1 + 0x7f0) = param_1 & 0xffffffe0;
    param_1 = (param_1 & 0xffffffe0) + 0x20;
    FUN_c0471308(0xc069e9c8,uVar3);
  }
  if ((param_2 & 0x1f) != 0) {
    param_2 = param_2 & 0xffffffe0;
    uVar3 = FUN_c047125c(DAT_c0014de8);
    *(uint *)(iVar1 + 0x7f0) = param_2;
    FUN_c0471308(DAT_c0014de8,uVar3);
  }
  FUN_c0014cc0(iVar1 + 0x770,param_1,param_2);
  uVar3 = DAT_c0014cac;
  puVar4 = (undefined4 *)(iVar1 + DAT_c0676ad0);
  uVar2 = FUN_c047125c(DAT_c0014cac);
  *puVar4 = 0;
  FUN_c0471308(uVar3,uVar2);
  return;
}

