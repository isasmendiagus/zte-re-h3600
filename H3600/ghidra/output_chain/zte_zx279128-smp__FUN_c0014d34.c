// compatible: zte,zx279128-smp
// function: FUN_c0014d34 @ 0xc0014d34
// found via struct field ptr -> 0xc0014d34
// total struct-refs for compat: 2
//

/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */

void FUN_c0014d34(uint param_1,undefined4 param_2)

{
  undefined4 uVar1;
  int iVar2;
  undefined4 uVar3;
  undefined4 *puVar4;
  
  iVar2 = _DAT_c069e998;
  FUN_c0014cc0(_DAT_c069e998 + 0x7f0,param_1 & 0xffffffe0,param_2);
  uVar1 = DAT_c0014cac;
  puVar4 = (undefined4 *)(iVar2 + DAT_c0676ad0);
  uVar3 = FUN_c047125c(DAT_c0014cac);
  *puVar4 = 0;
  FUN_c0471308(uVar1,uVar3);
  return;
}

