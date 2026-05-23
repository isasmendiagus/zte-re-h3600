// FUN_c0015834 @ c0015834

/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */

void FUN_c0015834(void)

{
  undefined4 uVar1;
  int iVar2;
  
  if (_DAT_c069dba0 == 0x8000000) {
    uVar1 = 0x147f000;
    iVar2 = 0xe7f000;
    _DAT_c069ea04 = 0x1800;
  }
  else {
    if (_DAT_c069dba0 != 0x10000000) {
      _DAT_c069ea10 = 0x26;
      _DAT_c069ea00 = 0x900;
      _DAT_c069ea04 = 0x3000;
      _DAT_c069ea08 = 0x2800;
      _DAT_c069ea0c = 0x200;
      FUN_c046ab98(s_ZX_RESERVE_MEM_SIZE_is__x___x_c0585a8c,0x2600000,0x26);
      return;
    }
    uVar1 = 0x18ff000;
    _DAT_c069ea04 = 0x2000;
    iVar2 = 0x12ff000;
  }
  _DAT_c069ea0c = 0x66;
  _DAT_c069ea08 = 0x2800;
  _DAT_c069ea00 = 0x900;
  _DAT_c069ea10 = iVar2 + 0x700000U >> 0x14;
  FUN_c046ab98(s_ZX_RESERVE_MEM_SIZE_is__x___x_c0585a8c,uVar1);
  return;
}

