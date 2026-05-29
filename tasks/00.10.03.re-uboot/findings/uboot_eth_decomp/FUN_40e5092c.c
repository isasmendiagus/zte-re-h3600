/* ===== FUN FUN_40e5092c @ 40e5092c =====
 * callers: 40e50978:FUN_40e50978
 * callees: (none)
 */


void FUN_40e5092c(void)

{
  int iVar1;
  int *piVar2;
  int iVar3;
  
  iVar1 = DAT_40e5096c/*=0x47f59648*/;
  iVar3 = 0;
  do {
    piVar2 = (int *)(iVar1 + iVar3);
    *piVar2 = (iVar3 + 0x20d00) * 0x2000;
    iVar3 = iVar3 + 8;
    piVar2[1] = 0;
  } while (iVar3 != 0x40);
  *(undefined4 *)(DAT_40e50974/*=0x47f59640*/ + 0x58) = DAT_40e50970/*=0x41c00000[RAM]*/;
  return;
}
