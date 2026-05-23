// FUN_c00151a8 @ c00151a8

/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */

void FUN_c00151a8(uint param_1,uint param_2,undefined4 param_3,undefined4 param_4)

{
  int iVar1;
  undefined4 uVar2;
  uint uVar3;
  
  iVar1 = _DAT_c069e998;
  uVar2 = FUN_c047125c(0xc069e9c8);
  if (((param_1 | param_2) & 0x1f) != 0) {
    if ((param_1 & 0x1f) != 0) {
      *(uint *)(iVar1 + 0x7f0) = param_1 & 0xffffffe0;
      param_1 = (param_1 & 0xffffffe0) + 0x20;
    }
    if ((param_2 & 0x1f) != 0) {
      param_2 = param_2 & 0xffffffe0;
      uVar3 = *(uint *)(iVar1 + 0x7f0);
      while ((uVar3 & 1) != 0) {
        uVar3 = *(uint *)(iVar1 + 0x7f0);
      }
      *(uint *)(iVar1 + 0x7f0) = param_2;
    }
  }
  uVar2 = FUN_c0014fd4((uint *)(iVar1 + 0x770),param_1,param_2,uVar2);
  uVar3 = *(uint *)(iVar1 + 0x770);
  while ((uVar3 & 1) != 0) {
    uVar3 = *(uint *)(iVar1 + 0x770);
  }
  *(undefined4 *)(iVar1 + 0x730) = 0;
  uVar3 = *(uint *)(iVar1 + 0x730);
  while ((uVar3 & 1) != 0) {
    uVar3 = *(uint *)(iVar1 + 0x730);
  }
  FUN_c0471308(DAT_c0015274,uVar2,uVar3,param_4);
  return;
}

