// compatible: zte,zx279128-smp
// function: FUN_c0014d54 @ 0xc0014d54
// found via struct field ptr -> 0xc0014d54
// total struct-refs for compat: 2
//

/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */

void FUN_c0014d54(uint param_1,undefined4 param_2)

{
  undefined4 uVar1;
  int iVar2;
  undefined4 uVar3;
  undefined4 *puVar4;
  
  iVar2 = _DAT_c06ae8b8;
  FUN_c0014ce0(_DAT_c06ae8b8 + 0x7f0,param_1 & 0xffffffe0,param_2);
  uVar1 = DAT_c0014ccc;
  puVar4 = (undefined4 *)(iVar2 + DAT_c0674ad0);
  uVar3 = FUN_c046feec(DAT_c0014ccc);
  *puVar4 = 0;
  FUN_c046ff98(uVar1,uVar3);
  return;
}

