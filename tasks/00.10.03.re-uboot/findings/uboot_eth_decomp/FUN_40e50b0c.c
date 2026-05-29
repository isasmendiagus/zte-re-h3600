/* ===== FUN FUN_40e50b0c @ 40e50b0c =====
 * callers: 40e4fda4:FUN_40e4fda4
 * callees: 40e50a60:FUN_40e50a60, 40e50a9c:FUN_40e50a9c, 40e50b34:FUN_40e50b34
 */


void FUN_40e50b0c(void)

{
  int iVar1;
  
  FUN_40e50b34();
  FUN_40e50a9c();
  FUN_40e50a60();
  iVar1 = DAT_40e50b30/*=0x923a0000[ETH_TM2]*/;
  *(undefined4 *)(DAT_40e50b30/*=0x923a0000[ETH_TM2]*/ + 0x10) = 0;
  *(undefined4 *)(iVar1 + 0x14) = 0;
  return;
}
