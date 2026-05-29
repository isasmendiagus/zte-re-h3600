/* ===== FUN FUN_40e50ed4 @ 40e50ed4 =====
 * callers: 40e50f20:FUN_40e50f20
 * callees: 40e50eb0:FUN_40e50eb0
 */


undefined4 FUN_40e50ed4(void)

{
  int iVar1;
  int iVar2;
  int iVar3;
  
  iVar1 = DAT_40e50f08/*=0x47f5969c*/;
  iVar2 = 0;
  do {
    *(undefined4 *)(iVar1 + iVar2 * 4) = 0xffffffff;
    iVar3 = iVar2 + 1;
    FUN_40e50eb0(iVar2,0);
    iVar2 = iVar3;
  } while (iVar3 != 4);
  return 0;
}
