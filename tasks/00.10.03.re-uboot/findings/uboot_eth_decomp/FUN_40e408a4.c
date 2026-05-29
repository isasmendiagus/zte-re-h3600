/* ===== FUN FUN_40e408a4 @ 40e408a4 =====
 * callers: 40e40ae4:FUN_40e40ae4, 40e40bdc:FUN_40e40bdc, 40e40bf0:FUN_40e40bf0, 40e40c04:FUN_40e40c04, 40e40c20:FUN_40e40c20, 40e40c3c:FUN_40e40c3c
 * callees: 40e40d38:FUN_40e40d38, 40e46958:FUN_40e46958
 */


void FUN_40e408a4(void)

{
  int iVar1;
  int unaff_r8;
  
  if (((*(uint *)(unaff_r8 + 4) & 1) != 0) && (*DAT_40e408e0/*=0x47f56e3c*/ != 0)) {
    return;
  }
  iVar1 = FUN_40e40d38();
  if (iVar1 == 0) {
                    /* WARNING: Subroutine does not return */
    FUN_40e46958(DAT_40e408dc/*=0x47f3d868*/);
  }
  return;
}
