// kallsyms symbol: zx_mdio_read
// string @ 0xc05f1933, .value @ 0xc05ec6f8 = 0xc00175b8
// Function: FUN_c00175b8 @ 0xc00175b8
//

/* WARNING: Removing unreachable block (ram,0xc0017680) */
/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */

uint FUN_c00175b8(int param_1,uint param_2)

{
  uint uVar1;
  uint local_1c;
  
  FUN_c0470238(0xc06ae9c0);
  _DAT_f0801010 = 0;
  _DAT_f0801014 =
       (_DAT_f0801014 & 0xffffb3e0 | 0x800 | param_2) & 0xfffffc1f | param_1 << 5 | 0x4000;
  local_1c = 0;
  do {
    local_1c = local_1c + 1;
  } while (local_1c < 10000);
  if (local_1c == 10000) {
    FUN_c046918c(s_mdio_read_timeout_c0584f38);
  }
  uVar1 = _DAT_f0801008;
  _DAT_f0801010 = 0;
  _DAT_f0801014 = _DAT_f0801014 & 0xffffbfff;
  FUN_c047030c(0xc06ae9c0);
  return uVar1 & 0xffff;
}

