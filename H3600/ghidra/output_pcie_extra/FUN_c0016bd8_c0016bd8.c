// FUN_c0016bd8 @ c0016bd8

/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */

uint FUN_c0016bd8(void)

{
  if (_DAT_c069ea88 != 0) {
    FUN_c046ab98(s_ponmode___0x_x_c0585d84,*(undefined2 *)(_DAT_c069ea88 + 0x68));
    return (uint)*(ushort *)(_DAT_c069ea88 + 0x68);
  }
  FUN_c046ab98(s_ponmode_error___c0585d70);
  return 0xffffffff;
}

