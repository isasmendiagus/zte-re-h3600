// compatible: zte,zx279128-smp
// function: FUN_c0014d84 @ 0xc0014d84
// found via struct field ptr -> 0xc0014d84
// total struct-refs for compat: 2
//

/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */

void FUN_c0014d84(uint param_1,uint param_2)

{
  int iVar1;
  undefined4 uVar2;
  undefined4 uVar3;
  undefined4 *puVar4;
  
  iVar1 = _DAT_c06ae8b8;
  if ((param_1 & 0x1f) != 0) {
    uVar3 = FUN_c046feec(0xc06ae8e8);
    *(uint *)(iVar1 + 0x7f0) = param_1 & 0xffffffe0;
    param_1 = (param_1 & 0xffffffe0) + 0x20;
    FUN_c046ff98(0xc06ae8e8,uVar3);
  }
  if ((param_2 & 0x1f) != 0) {
    param_2 = param_2 & 0xffffffe0;
    uVar3 = FUN_c046feec(DAT_c0014e08);
    *(uint *)(iVar1 + 0x7f0) = param_2;
    FUN_c046ff98(DAT_c0014e08,uVar3);
  }
  FUN_c0014ce0(iVar1 + 0x770,param_1,param_2);
  uVar3 = DAT_c0014ccc;
  puVar4 = (undefined4 *)(iVar1 + DAT_c0674ad0);
  uVar2 = FUN_c046feec(DAT_c0014ccc);
  *puVar4 = 0;
  FUN_c046ff98(uVar3,uVar2);
  return;
}

