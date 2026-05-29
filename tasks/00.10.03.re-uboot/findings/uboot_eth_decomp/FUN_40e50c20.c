/* ===== FUN FUN_40e50c20 @ 40e50c20 =====
 * callers: 40e50c40:FUN_40e50c40
 * callees: (none)
 */


void FUN_40e50c20(uint param_1)

{
  uint *puVar1;
  
  if (param_1 < 5) {
    puVar1 = (uint *)(param_1 * 0x40000 + -0x6de00000);
    *puVar1 = *puVar1 | 3;
  }
  return;
}
