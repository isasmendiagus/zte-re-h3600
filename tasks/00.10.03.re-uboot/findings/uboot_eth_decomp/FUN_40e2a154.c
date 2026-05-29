/* ===== FUN FUN_40e2a154 @ 40e2a154 =====
 * callers: 40e27cc4:FUN_40e27cc4, 40e29744:FUN_40e29744, 40e2999c:FUN_40e2999c, 40e2ea98:FUN_40e2ea98, 40e2eb68:FUN_40e2eb68, 40e2f62c:FUN_40e2f62c, 40e2fa24:FUN_40e2fa24, 40e343a0:FUN_40e343a0
 * callees: 40e40c04:FUN_40e40c04
 */


void FUN_40e2a154(void)

{
  int unaff_r8;
  
  if (*(int *)(unaff_r8 + 0x1c) == 0) {
    return;
  }
  if ((*(uint *)(unaff_r8 + 4) & 2) != 0) {
                    /* WARNING: Could not recover jumptable at 0x40e2a178. Too many branches */
                    /* WARNING: Treating indirect jump as call */
    (**(code **)(*(int *)(DAT_40e2a180/*=0x47f53fa0*/ + 4) + 0x20))();
    return;
  }
  FUN_40e40c04();
  return;
}
