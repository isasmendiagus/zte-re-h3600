/* ===== FUN FUN_40e50f20 @ 40e50f20 =====
 * callers: 40e4fda4:FUN_40e4fda4
 * callees: 40e45a90:FUN_40e45a90, 40e50b84:FUN_40e50b84, 40e50ed4:FUN_40e50ed4, 40e50f0c:FUN_40e50f0c
 */


void FUN_40e50f20(void)

{
  int iVar1;
  
  iVar1 = DAT_40e50f5c/*=0x921c0000*/;
  *(undefined4 *)(DAT_40e50f5c/*=0x921c0000*/ + 8) = 0xffffffff;
  FUN_40e45a90(1000);
  *(undefined4 *)(iVar1 + 0xc) = 0xffffffff;
  FUN_40e45a90(1000);
  FUN_40e50b84();
  FUN_40e50ed4();
  FUN_40e50f0c();
  *(undefined4 *)(iVar1 + 0x48) = 0;
  return;
}
