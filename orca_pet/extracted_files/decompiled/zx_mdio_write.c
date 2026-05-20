// kallsyms symbol: zx_mdio_write
// string @ 0xc05f1925, .value @ 0xc05ec700 = 0xc001770c
// Function: FUN_c001770c @ 0xc001770c
//

/* WARNING: Removing unreachable block (ram,0xc00177d8) */
/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */

void FUN_c001770c(int param_1,uint param_2,undefined4 param_3)

{
  uint local_18;
  
  FUN_c0470238(0xc06ae9c0);
  _DAT_f0801010 = 0;
  _DAT_f0801014 = _DAT_f0801014 & 0xffffb000 | 0x400 | param_1 << 5 | param_2 | 0x4000;
  local_18 = 0;
  do {
    local_18 = local_18 + 1;
  } while (local_18 < 10000);
  _DAT_f0801004 = param_3;
  if (local_18 == 10000) {
    FUN_c046918c(s_mdio_write_timeout_c0584f4c);
  }
  _DAT_f0801010 = 0;
  _DAT_f0801014 = _DAT_f0801014 & 0xffffbfff;
  FUN_c047030c(0xc06ae9c0);
  return;
}

