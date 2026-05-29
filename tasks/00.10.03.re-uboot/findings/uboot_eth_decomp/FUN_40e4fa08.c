/* ===== FUN FUN_40e4fa08 @ 40e4fa08 =====
 * callers: 40e4fc7c:FUN_40e4fc7c
 * callees: 40e2a1b4:FUN_40e2a1b4, 40e45ac0:FUN_40e45ac0, 40e4f580:FUN_40e4f580, 40e4f700:FUN_40e4f700
 */


/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */

void FUN_40e4fa08(uint param_1,undefined4 param_2,undefined4 param_3,undefined4 param_4)

{
  FUN_40e2a1b4(DAT_40e4fa8c/*=0x47f3eb6c*/,param_1,param_3,param_4,param_1,param_2);
  _DAT_94000050 = _DAT_94000050 & 0x7fffffff;
  if ((param_1 & 0xfffffffd) == 1) {
    FUN_40e4f580(DAT_40e4fa90/*=0x94000050[TOPCRM]*/,1,0x32,4,2);
  }
  else {
    FUN_40e4f700(DAT_40e4fa90/*=0x94000050[TOPCRM]*/,1,0x5d,DAT_40e4fa94/*=0x004fdf3b*/,5,3);
  }
  FUN_40e45ac0(0x32);
  FUN_40e2a1b4(DAT_40e4fa98/*=0x47f3eb8d*/);
  return;
}
