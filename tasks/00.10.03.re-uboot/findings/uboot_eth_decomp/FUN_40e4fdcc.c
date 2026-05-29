/* ===== FUN FUN_40e4fdcc @ 40e4fdcc =====
 * callers: 40e4fe04:FUN_40e4fe04, 40e50c40:FUN_40e50c40
 * callees: 40e45ac0:FUN_40e45ac0
 */


/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */

void FUN_40e4fdcc(uint param_1)

{
  _DAT_92000008 = _DAT_92000008 & ~param_1;
  FUN_40e45ac0(10);
  _DAT_92000008 = 0xffffffff;
  return;
}
