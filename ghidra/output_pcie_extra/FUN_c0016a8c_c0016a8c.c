// FUN_c0016a8c @ c0016a8c

/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */

undefined4 FUN_c0016a8c(void)

{
  undefined4 uVar1;
  
  if (_DAT_c069ea88 == 0) {
    uVar1 = 0xffffffff;
  }
  else {
    uVar1 = *(undefined4 *)(_DAT_c069ea88 + 0xec);
  }
  return uVar1;
}

