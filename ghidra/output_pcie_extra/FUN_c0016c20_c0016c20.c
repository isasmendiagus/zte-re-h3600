// FUN_c0016c20 @ c0016c20

/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */

uint FUN_c0016c20(void)

{
  if (_DAT_c069ea88 != 0) {
    FUN_c046ab98(s_wan_port___0x_x_c0585dac,*(undefined2 *)(_DAT_c069ea88 + 0x92));
    return (uint)*(ushort *)(_DAT_c069ea88 + 0x92);
  }
  FUN_c046ab98(s_wan_port_error___c0585d98);
  return 0xffffffff;
}

