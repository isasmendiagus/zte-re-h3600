/* ===== FUN FUN_40e4fe04 @ 40e4fe04 =====
 * callers: 40e50440:FUN_40e50440
 * callees: 40e45ac0:FUN_40e45ac0, 40e4fda4:FUN_40e4fda4, 40e4fdcc:FUN_40e4fdcc
 */


undefined4 FUN_40e4fe04(void)

{
  int *piVar1;
  int iVar2;
  
  piVar1 = DAT_40e4fe54/*=0x47f5960c*/;
  if (*DAT_40e4fe54/*=0x47f5960c*/ == 0) {
    FUN_40e4fdcc(0xffffffff);
    FUN_40e4fda4();
    iVar2 = DAT_40e4fe58/*=0x92040000*/;
    *(uint *)(DAT_40e4fe58/*=0x92040000*/ + 0x18) = *(uint *)(DAT_40e4fe58/*=0x92040000*/ + 0x18) & 0xfffffffc;
    *(undefined4 *)(iVar2 + 0x1c) = 0xf;
    FUN_40e45ac0(0x14);
    *piVar1 = 1;
  }
  return 0;
}
