// FUN_c0015058 @ c0015058

/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */

void FUN_c0015058(uint param_1,int param_2,undefined4 param_3,undefined4 param_4)

{
  int iVar1;
  undefined4 uVar2;
  uint uVar3;
  
  iVar1 = _DAT_c069e998;
  if (_DAT_c069e9d0 <= param_2 - (param_1 & 0xffffffe0)) {
    FUN_c0014f68(_DAT_c069e998,0x7fc,_DAT_c069e9d0,param_4);
    return;
  }
  uVar2 = FUN_c047125c(0xc069e9c8);
  uVar2 = FUN_c0014fd4((uint *)(iVar1 + 0x7f0),param_1 & 0xffffffe0,param_2,uVar2);
  uVar3 = *(uint *)(iVar1 + 0x7f0);
  while ((uVar3 & 1) != 0) {
    uVar3 = *(uint *)(iVar1 + 0x7f0);
  }
  *(undefined4 *)(iVar1 + 0x730) = 0;
  uVar3 = *(uint *)(iVar1 + 0x730);
  while ((uVar3 & 1) != 0) {
    uVar3 = *(uint *)(iVar1 + 0x730);
  }
  FUN_c0471308(DAT_c00150fc,uVar2,uVar3,param_4);
  return;
}

