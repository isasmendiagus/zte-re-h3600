/* ===== FUN FUN_40e2a184 @ 40e2a184 =====
 * callers: 40e21070:FUN_40e21070, 40e21478:FUN_40e21478, 40e21914:FUN_40e21914, 40e21c68:FUN_40e21c68, 40e21d68:FUN_40e21d68, 40e21d7c:FUN_40e21d7c, 40e220e8:FUN_40e220e8, 40e22734:FUN_40e22734
 * callees: 40e40c20:FUN_40e40c20
 */


void FUN_40e2a184(void)

{
  int unaff_r8;
  
  if (*(int *)(unaff_r8 + 0x1c) == 0) {
    return;
  }
  if ((*(uint *)(unaff_r8 + 4) & 2) != 0) {
                    /* WARNING: Could not recover jumptable at 0x40e2a1a8. Too many branches */
                    /* WARNING: Treating indirect jump as call */
    (**(code **)(*(int *)(DAT_40e2a1b0/*=0x47f53fa0*/ + 4) + 0x24))();
    return;
  }
  FUN_40e40c20();
  return;
}
